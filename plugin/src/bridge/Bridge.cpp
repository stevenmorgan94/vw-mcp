//
//  Bridge.cpp
//
//  Threading rules:
//  - The server thread(s) NEVER call the SDK. They read and write the job table under gMu.
//  - Jobs run only on the main thread, from a default-mode run-loop timer (not common modes: a
//    modal dialog's loop must never run a job, crash C2).
//  - A second, common-mode timer only samples whether a modal window is up (gBusy), so the server
//    thread can refuse a job that a dialog has blocked for too long.
//

#include "Bridge.h"
#include "ScriptRunner.h"
#include "HeadlessHost.h"
#include "palette/StatusPalette.h"

#define CPPHTTPLIB_THREAD_POOL_COUNT 4
#include "../../third_party/cpp-httplib/httplib.h"

#include "safety/VsSignatures.generated.inc"   // kVsSignatures

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <filesystem>
#include <fstream>
#include <map>
#include <mutex>
#include <random>
#include <set>
#include <thread>

#if GS_MAC
#include <CoreFoundation/CoreFoundation.h>
#include <objc/message.h>
#include <objc/runtime.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace VwMcp
{
namespace Bridge
{
    using Clock = std::chrono::steady_clock;

    static const char*  kPluginVersion   = "0.1.0";   // keep in step with relay/package.json (tools/release.sh sets both)
    static const int    kPortFirst       = 47823;
    static const int    kPortLast        = 47830;
    static const double kBusyTimeoutSec  = 10.0;   // a job blocked this long by a dialog is refused (spec §3)
    static const int    kMaxWaitSec      = 25;
    static const size_t kActivityMax     = 50;
    static const size_t kCodeMax         = 20;          // jobs whose code is kept, in memory only (#27)
    static const size_t kCodeMaxBytes    = 1 << 20;     // longer code isn't kept

    enum class JobState { Queued, Running, Done };
    struct Job
    {
        JobRequest     req;
        std::string    client;
        JobState       state = JobState::Queued;
        nlohmann::json result;
        Clock::time_point submitted = Clock::now();
        std::string    internal;          // "saveScript": queued by the palette, never by HTTP
        std::string    internalName;
    };

    struct CodeRecord { int id; std::string at, client, lang, code; bool ok; };

    static std::mutex                   gMu;
    static std::condition_variable      gCv;
    static std::map<int, Job>           gJobs;
    static int                          gNextJobId = 1;
    static std::deque<nlohmann::json>   gActivity;                  // newest first
    static std::map<std::string, std::string> gClients;             // name -> last seen (ISO)
    static std::deque<CodeRecord>       gCodes;                     // newest first, kCodeMax

    static std::atomic<bool>            gPaused { false };          // refuse new jobs (#27)
    static std::atomic<bool>            gSaveFirst { false };       // save the drawing before its first job (#27)
    static std::set<std::string>        gSavedDocs;                 // main thread only

    static std::atomic<bool>            gBusy { false };
    static std::atomic<bool>            gDocOpen { false };
    static std::atomic<bool>            gSweep { false };
    static std::atomic<int>             gPort { 0 };

    static std::unique_ptr<httplib::Server> gServer;
    static std::thread                  gServerThread;
    static std::string                  gToken;
    static std::string                  gDiscoveryFile;
    static bool                         gStarted = false;

    // ---- small helpers ----------------------------------------------------------------
    static std::string NowIso()
    {
        std::time_t t = std::time(nullptr);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&t));
        return buf;
    }

    static std::string RandomToken()
    {
        std::random_device rd;
        static const char* hex = "0123456789abcdef";
        std::string s;
        for (int i = 0; i < 32; ++i) s += hex[rd() & 15];
        return s;
    }

    static const char* BusyReason() { return "Vectorworks is busy (a dialog is open)"; }

    static double AgeSec(const Job& j) { return std::chrono::duration<double>(Clock::now() - j.submitted).count(); }

    // Caller holds gMu.
    static void RecordActivity(int id, const Job& j, double ms)
    {
        const nlohmann::json& r = j.result;
        nlohmann::json a = { { "at", NowIso() }, { "jobId", id }, { "client", j.client }, { "lang", j.req.lang },
                             { "ms", (int)ms }, { "ok", r.value("ok", false) } };
        if (r.value("refused", false))
        {
            a["refused"] = true;
            a["function"] = r.contains("function") ? r["function"] : nullptr;
            a["class"] = r.value("class", "");
        }
        if (r.contains("guard") && r["guard"].contains("calls")) a["calls"] = r["guard"]["calls"];
        if (r.contains("guard") && r["guard"].contains("timeout")) a["timeout"] = true;
        if (r.contains("autoReset")) a["autoReset"] = r["autoReset"];
        if (r.contains("savedFirst")) a["savedFirst"] = r["savedFirst"];
        std::string err = r.value("error", "");
        if (!err.empty()) a["error"] = err.substr(0, 200);
        gActivity.push_front(a);
        if (gActivity.size() > kActivityMax) gActivity.pop_back();
    }

    // Caller holds gMu.
    static void Finish(int id, Job& j, nlohmann::json result)
    {
        j.result = std::move(result);
        j.state = JobState::Done;
        if (!j.internal.empty()) return;    // the palette collects it (TakeInternalResult)
        RecordActivity(id, j, AgeSec(j) * 1000.0);
        if (j.req.code.size() <= kCodeMaxBytes)
        {
            gCodes.push_front({ id, NowIso(), j.client, j.req.lang, j.req.code, j.result.value("ok", false) });
            if (gCodes.size() > kCodeMax) gCodes.pop_back();
        }
        gCv.notify_all();
    }

    // ---- settings (Plug-ins/Data/vw-mcp/settings.json) ----------------------------------
    static std::filesystem::path SettingsPath() { return std::filesystem::path(DataFolder()) / "settings.json"; }

    static void LoadSettings()
    {
        if (DataFolder().empty()) return;
        std::ifstream in(SettingsPath());
        if (!in) return;
        nlohmann::json s = nlohmann::json::parse(in, nullptr, false);
        if (!s.is_object()) return;
        gPaused = s.value("paused", false);
        gSaveFirst = s.value("saveFirst", false);
    }

    static void SaveSettings()
    {
        if (DataFolder().empty()) return;
        std::ofstream out(SettingsPath(), std::ios::trunc);
        if (out) out << nlohmann::json { { "paused", gPaused.load() }, { "saveFirst", gSaveFirst.load() } }.dump(2);
    }

    // ---- main thread ------------------------------------------------------------------
#if GS_MAC
    static CFRunLoopTimerRef gPumpTimer = nullptr;
    static CFRunLoopTimerRef gBusyTimer = nullptr;

    // [NSApp modalWindow] != nil, without Objective-C++.
    static bool IsModalWindowUp()
    {
        using MsgSendClass = id (*)(Class, SEL);
        using MsgSendId = id (*)(id, SEL);
        Class appClass = objc_getClass("NSApplication");
        if (!appClass) return false;
        id app = ((MsgSendClass)objc_msgSend)(appClass, sel_registerName("sharedApplication"));
        if (!app) return false;
        return ((MsgSendId)objc_msgSend)(app, sel_registerName("modalWindow")) != nullptr;
    }

    static void BusyTimerCB(CFRunLoopTimerRef, void*)
    {
        gBusy = IsModalWindowUp();
    }

    // Runs at most one queued job per pass, so VW stays responsive between jobs.
    static void PumpTimerCB(CFRunLoopTimerRef, void*)
    {
        gDocOpen = gSDK->IsDocumentOpen();
        gSweep = SweepMode();
        gBusy = IsModalWindowUp();

        int id = 0;
        JobRequest req;
        std::string internal, internalName;
        {
            std::lock_guard<std::mutex> lk(gMu);
            for (auto& [jid, j] : gJobs)
            {
                if (j.state != JobState::Queued) continue;
                if (gBusy)
                {
                    if (AgeSec(j) >= kBusyTimeoutSec)
                        Finish(jid, j, Refusal("busy", BusyReason(), "Close the dialog in Vectorworks, then retry."));
                    continue;
                }
                id = jid;
                req = j.req;
                internal = j.internal;
                internalName = j.internalName;
                j.state = JobState::Running;
                break;
            }
        }
        if (!id) return;

        nlohmann::json result, savedFirst;
        try
        {
            if (internal == "saveScript")
                result = SaveScriptResource(internalName, req.code);
            else
            {
                if (gSaveFirst && gDocOpen)
                    savedFirst = SaveActiveDocumentFirst(gSavedDocs);
                result = RunJob(req);
                if (!savedFirst.is_null()) result["savedFirst"] = savedFirst;
            }
        }
        catch (const std::exception& e) { result = { { "ok", false }, { "error", std::string("bridge exception: ") + e.what() } }; }
        catch (...) { result = { { "ok", false }, { "error", "bridge exception" } }; }

        std::lock_guard<std::mutex> lk(gMu);
        auto it = gJobs.find(id);
        if (it != gJobs.end()) Finish(id, it->second, std::move(result));
    }

    static CFRunLoopTimerRef AddTimer(double interval, CFRunLoopTimerCallBack cb, CFStringRef mode)
    {
        CFRunLoopTimerContext ctx = { 0, nullptr, nullptr, nullptr, nullptr };
        CFRunLoopTimerRef t = CFRunLoopTimerCreate(kCFAllocatorDefault, CFAbsoluteTimeGetCurrent() + interval,
                                                   interval, 0, 0, cb, &ctx);
        CFRunLoopAddTimer(CFRunLoopGetMain(), t, mode);
        return t;
    }

    static void RemoveTimer(CFRunLoopTimerRef& t)
    {
        if (!t) return;
        CFRunLoopTimerInvalidate(t);
        CFRelease(t);
        t = nullptr;
    }
#endif

    // ---- server thread ----------------------------------------------------------------
    static void SendJson(httplib::Response& res, const nlohmann::json& j, int status = 200)
    {
        res.status = status;
        res.set_content(j.dump(-1, ' ', false, nlohmann::json::error_handler_t::replace), "application/json");
    }

    nlohmann::json StatusJson()
    {
        nlohmann::json s = {
            { "ok", true }, { "plugin", "vw-mcp" }, { "pluginVersion", kPluginVersion },
            { "vwBuild", VectorworksBuild() }, { "engine", "ctx" }, { "guardVersion", kGuardVersion },
            { "sweepMode", gSweep.load() }, { "documentOpen", gDocOpen.load() },
            { "busy", gBusy ? nlohmann::json(BusyReason()) : nlohmann::json(nullptr) },
            { "port", gPort.load() }, { "pid", (int)getpid() },
            { "helpMenuItem", HelpMenuItemResult() },
            { "tableBuild", TableBuild() }, { "tableFunctions", TableFunctions() },
            { "paused", gPaused.load() }, { "saveFirst", gSaveFirst.load() },
        };
        std::lock_guard<std::mutex> lk(gMu);
        nlohmann::json clients = nlohmann::json::array();
        for (auto& [name, seen] : gClients) clients.push_back({ { "name", name }, { "lastSeen", seen } });
        s["clients"] = clients;
        std::set<int> withCode;
        nlohmann::json scripts = nlohmann::json::array();
        for (auto& c : gCodes)
        {
            withCode.insert(c.id);
            if (c.lang != "python" || !c.ok || scripts.size() >= 10) continue;
            // title: the first comment line; preview: the first line that does something
            std::string title, preview;
            int lines = 0;
            size_t pos = 0;
            while (pos <= c.code.size())
            {
                size_t e = c.code.find('\n', pos);
                std::string ln = c.code.substr(pos, e == std::string::npos ? std::string::npos : e - pos);
                pos = e == std::string::npos ? c.code.size() + 1 : e + 1;
                size_t b = ln.find_first_not_of(" \t\r");
                if (b == std::string::npos) continue;
                ++lines;
                ln = ln.substr(b);
                while (!ln.empty() && (ln.back() == '\r' || ln.back() == ' ')) ln.pop_back();
                if (ln[0] == '#')
                {
                    if (title.empty()) { size_t t = ln.find_first_not_of("# "); if (t != std::string::npos) title = ln.substr(t, 80); }
                }
                else if (preview.empty() && ln.rfind("import ", 0) != 0 && ln.rfind("from ", 0) != 0)
                    preview = ln.substr(0, 120);
            }
            scripts.push_back({ { "jobId", c.id }, { "at", c.at }, { "client", c.client }, { "title", title },
                                { "preview", preview }, { "lines", lines } });
        }
        nlohmann::json activity = nlohmann::json(gActivity);
        for (auto& a : activity)
            if (withCode.count(a.value("jobId", 0))) a["hasCode"] = true;
        s["activity"] = activity;
        s["scripts"] = scripts;
        s["scriptPalette"] = "vw-mcp Scripts";
        int queued = 0;
        for (auto& [id, j] : gJobs) if (j.state != JobState::Done && j.internal.empty()) ++queued;
        s["queued"] = queued;
        return s;
    }

    static void HandleSubmit(const httplib::Request& req, httplib::Response& res)
    {
        nlohmann::json a = nlohmann::json::parse(req.body, nullptr, false);
        if (a.is_discarded() || !a.is_object() || !a.contains("code") || !a["code"].is_string())
            return SendJson(res, { { "ok", false }, { "error", "Expected { code: string, lang?: 'python'|'ops', ... }" } }, 400);

        if (gPaused)
            return SendJson(res, Refusal("paused", "AI jobs are paused in Vectorworks (vw-mcp palette, Utility tab).",
                                         "Tell the user and wait: only they can turn AI jobs back on. Don't retry until they do."));
        Job j;
        j.req.code = a["code"].get<std::string>();
        j.req.lang = a.value("lang", std::string("python"));
        j.client = req.get_header_value("X-VW-MCP-Client");
        if (j.req.lang == "vectorscript" || j.req.lang == "vs")
            return SendJson(res, Refusal("language", "Only Python is supported: the safety layer can't see inside VectorScript."));
        for (const char* k : { "allowDocumentLevel", "allowUnclassified" })
            j.req.opts[k] = a.contains(k) && a[k].is_boolean() && a[k].get<bool>();
        j.req.opts["autoReset"] = !(a.contains("autoReset") && a["autoReset"].is_boolean() && !a["autoReset"].get<bool>());
        double timeoutSec = 30.0;
        if (a.contains("timeoutSec") && a["timeoutSec"].is_number())
            timeoutSec = std::clamp(a["timeoutSec"].get<double>(), 1.0, 300.0);
        j.req.opts["timeoutSec"] = timeoutSec;

        int id;
        {
            std::lock_guard<std::mutex> lk(gMu);
            id = gNextJobId++;
            gJobs.emplace(id, std::move(j));
        }
#if GS_MAC
        CFRunLoopWakeUp(CFRunLoopGetMain());
#endif
        SendJson(res, { { "ok", true }, { "deferred", true }, { "jobId", id } });
    }

    static void HandlePoll(const httplib::Request& req, httplib::Response& res)
    {
        int id = std::atoi(req.matches[1].str().c_str());
        int wait = req.has_param("wait") ? std::clamp(std::atoi(req.get_param_value("wait").c_str()), 0, kMaxWaitSec) : 0;
        auto deadline = Clock::now() + std::chrono::seconds(wait);

        std::unique_lock<std::mutex> lk(gMu);
        for (;;)
        {
            auto it = gJobs.find(id);
            if (it == gJobs.end() || !it->second.internal.empty())
                return SendJson(res, { { "ok", false }, { "error", "Unknown jobId (already retrieved or never created)" }, { "jobId", id } }, 404);
            Job& j = it->second;
            // While a modal loop runs, the pump timer doesn't fire: time the job out from here.
            if (j.state == JobState::Queued && gBusy && AgeSec(j) >= kBusyTimeoutSec)
                Finish(id, j, Refusal("busy", BusyReason(), "Close the dialog in Vectorworks, then retry."));
            if (j.state == JobState::Done)
            {
                nlohmann::json r = std::move(j.result);
                r["jobId"] = id;
                r["pending"] = false;
                gJobs.erase(it);
                lk.unlock();
                return SendJson(res, r);
            }
            if (Clock::now() >= deadline)
            {
                nlohmann::json r = { { "ok", true }, { "jobId", id }, { "pending", true } };
                if (gBusy) r["waiting"] = BusyReason();
                lk.unlock();
                return SendJson(res, r);
            }
            gCv.wait_until(lk, std::min(deadline, Clock::now() + std::chrono::milliseconds(250)));
        }
    }

    static bool WriteDiscoveryFile(int port)
    {
#if GS_MAC
        const char* home = getenv("HOME");
        if (!home) return false;
        std::filesystem::path dir = std::filesystem::path(home) / "Library/Application Support/vw-mcp/instances";
#else
        std::filesystem::path dir;   // TODO(#9): %APPDATA%\vw-mcp\instances
        return false;
#endif
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        std::filesystem::path f = dir / (std::to_string(getpid()) + ".json");
        nlohmann::json d = { { "pid", (int)getpid() }, { "port", port }, { "token", gToken },
                             { "vwBuild", VectorworksBuild() }, { "plugin", "vw-mcp" },
                             { "pluginVersion", kPluginVersion }, { "started", NowIso() } };
        {
            std::ofstream out(f, std::ios::trunc);
            if (!out) return false;
            out << d.dump(2);
        }
#if GS_MAC
        chmod(f.c_str(), 0600);   // the token lets a local process run Python in VW
#endif
        gDiscoveryFile = f.string();
        return true;
    }

    static void ServerMain()
    {
        httplib::Server& svr = *gServer;
        svr.new_task_queue = [] { return new httplib::ThreadPool(4); };
        // Exclusive bind: no SO_REUSEPORT (the default would let a second server share the port).
        svr.set_socket_options([](socket_t sock) {
            int yes = 1;
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&yes), sizeof(yes));
        });
        svr.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
            if (req.has_header("Origin"))
            {
                SendJson(res, { { "ok", false }, { "error", "Browser requests are not allowed" } }, 403);
                return httplib::Server::HandlerResponse::Handled;
            }
            if (req.get_header_value("Authorization") != "Bearer " + gToken)
            {
                SendJson(res, { { "ok", false }, { "error", "Missing or wrong token (see the vw-mcp discovery file)" } }, 401);
                return httplib::Server::HandlerResponse::Handled;
            }
            std::string client = req.get_header_value("X-VW-MCP-Client");
            if (!client.empty())
            {
                std::lock_guard<std::mutex> lk(gMu);
                gClients[client.substr(0, 80)] = NowIso();
            }
            return httplib::Server::HandlerResponse::Unhandled;
        });
        svr.Get("/status", [](const httplib::Request&, httplib::Response& res) { SendJson(res, StatusJson()); });
        svr.Post("/jobs", HandleSubmit);
        // The data the relay's vw_lookup_function reads, so it always matches what this plug-in enforces (#17).
        svr.Get("/safety-table", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(SafetyTableJson(), "application/json");
        });
        svr.Get("/signatures", [](const httplib::Request&, httplib::Response& res) {
            res.set_content(kVsSignatures, "application/json");
        });
        svr.Get(R"(/jobs/(\d+))", HandlePoll);

        for (int p = kPortFirst; p <= kPortLast; ++p)
        {
            if (svr.bind_to_port("127.0.0.1", p))
            {
                gPort = p;
                break;
            }
        }
        if (!gPort)
        {
            Log("bridge: no free port in 47823-47830; not listening");
            return;
        }
        if (!WriteDiscoveryFile(gPort))
            Log("bridge: could not write the discovery file");
        Log(("bridge: listening on 127.0.0.1:" + std::to_string(gPort.load())).c_str());
        svr.listen_after_bind();
    }

    // ---- palette Utility tab (#27) --------------------------------------------------------
    nlohmann::json JobCode(int id)
    {
        std::lock_guard<std::mutex> lk(gMu);
        for (auto& c : gCodes)
            if (c.id == id)
                return { { "ok", true }, { "jobId", c.id }, { "lang", c.lang }, { "client", c.client }, { "at", c.at },
                         { "jobOk", c.ok }, { "code", c.code } };
        return { { "ok", false }, { "error", "That job's code is no longer kept (only the last 20 jobs)." } };
    }

    void SetPaused(bool on)    { gPaused = on; SaveSettings(); Log(on ? "bridge: AI jobs paused" : "bridge: AI jobs resumed"); }
    void SetSaveFirst(bool on) { gSaveFirst = on; if (on) gSavedDocs.clear(); SaveSettings(); }

    nlohmann::json QueueSaveScript(int jobId, const std::string& name)
    {
        std::string n = name;
        for (auto& ch : n) if (ch == '\n' || ch == '\r' || ch == '\t') ch = ' ';
        while (!n.empty() && n.back() == ' ') n.pop_back();
        while (!n.empty() && n.front() == ' ') n.erase(0, 1);
        if (n.empty()) return { { "ok", false }, { "error", "Enter a name." } };
        if (n.size() > 63) return { { "ok", false }, { "error", "Names can be at most 63 characters." } };
        Job j;
        {
            std::lock_guard<std::mutex> lk(gMu);
            const CodeRecord* rec = nullptr;
            for (auto& c : gCodes) if (c.id == jobId) rec = &c;
            if (!rec) return { { "ok", false }, { "error", "That job's code is no longer kept (only the last 20 jobs)." } };
            if (rec->lang != "python") return { { "ok", false }, { "error", "Only Python jobs can be saved as scripts." } };
            char date[16];
            std::time_t now = std::time(nullptr);
            std::strftime(date, sizeof(date), "%Y-%m-%d", std::localtime(&now));
            // Don't repeat the name if the code already starts with it as a comment.
            std::string body = rec->code;
            if (body.rfind("# " + n + "\n", 0) == 0) body.erase(0, n.size() + 3);
            j.req.code = "# " + n + "\n"
                         "# Saved from vw-mcp on " + std::string(date) + " (job " + std::to_string(jobId) + (rec->client.empty() ? "" : ", " + rec->client) + ").\n"
                         "# Runs as an ordinary Vectorworks script, without vw-mcp's safety checks.\n"
                         "# Plug-in objects it creates or changes may keep their old 2D look: afterwards run\n"
                         "# Tools > Utilities > Reset All Plug-Ins (a reset inside this script has no effect).\n"
                         "import vs\n\n" + body;
            if (j.req.code.back() != '\n') j.req.code += '\n';
            j.req.lang = "python";
            j.internal = "saveScript";
            j.internalName = n;
            int id = gNextJobId++;
            gJobs.emplace(id, std::move(j));
#if GS_MAC
            CFRunLoopWakeUp(CFRunLoopGetMain());
#endif
            return { { "ok", true }, { "ticket", id } };
        }
    }

    nlohmann::json TakeInternalResult(int ticket)
    {
        std::lock_guard<std::mutex> lk(gMu);
        auto it = gJobs.find(ticket);
        if (it == gJobs.end() || it->second.internal.empty()) return { { "ok", false }, { "error", "Unknown ticket" } };
        if (it->second.state != JobState::Done) return { { "pending", true } };
        nlohmann::json r = std::move(it->second.result);
        gJobs.erase(it);
        return r;
    }

    void Start()
    {
        if (gStarted) return;
        gStarted = true;
        InitHostInfo();
        LoadSettings();
        gToken = RandomToken();
        gSweep = SweepMode();
#if GS_MAC
        // Default mode only for the pump (C2); common modes for the busy sampler (it never runs a job).
        gPumpTimer = AddTimer(0.05, PumpTimerCB, kCFRunLoopDefaultMode);
        gBusyTimer = AddTimer(0.25, BusyTimerCB, kCFRunLoopCommonModes);
#endif
        gServer = std::make_unique<httplib::Server>();
        gServerThread = std::thread(ServerMain);
    }

    void Stop()
    {
        if (!gStarted) return;
        gStarted = false;
        if (gServer) gServer->stop();
        if (gServerThread.joinable()) gServerThread.join();
        gServer.reset();
#if GS_MAC
        RemoveTimer(gPumpTimer);
        RemoveTimer(gBusyTimer);
#endif
        if (!gDiscoveryFile.empty())
        {
            std::error_code ec;
            std::filesystem::remove(gDiscoveryFile, ec);
        }
        Log("bridge: stopped");
    }
}
}
