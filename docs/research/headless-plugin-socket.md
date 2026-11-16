# Headless VW 2027 plug-in serving a local socket (macOS + Windows)

**Question (issue #2):** with no web palette open, how does a Vectorworks 2027 plug-in accept local connections (HTTP or WebSocket on 127.0.0.1) and run jobs on the main thread?

**Status:** research, 2026-11-16. The design below is a recommendation. The items marked **verify** need a small prototype before anyone relies on them.

**How each claim is known**
- **[SDK]**: Vectorworks SDK 2027 headers (`SDKLib/Include/...`) or samples (`Source/Samples/...`), cited as file:line.
- **[docs]**: vendor documentation (Vectorworks `developer-sdk` repo, Microsoft Learn, Apple, the library's own README).
- **[observed]**: seen in the running Vectorworks 2027 (build 32.0.0) process or its shipped binaries on macOS, by reading symbol tables and memory maps only. Nothing here comes from decompiled code.
- **[current bridge]**: the existing SolotechSuite bridge that this project is split from.
- **[inferred]**: reasoning from the facts above.

---

## TL;DR: recommended design

1. **Launch hook.** Register an `IObjUpdateSupport` implementation in `GROUPID_ObjUpdateSupport`, the same way the SDK's UpdateManager sample does. Its `Init()` starts the server and does nothing else. `AcceptNotification(kNotifyApplicationShutdown)` / `kNotifyBeforeApplicationQuit` stops it. No menu, tool or palette is needed.
2. **Socket I/O on a background thread** (blocking accept/recv, inside the library). It never calls the SDK. It hands work to the main thread through a mutex-protected job queue and a **default-mode** main-loop wake-up (macOS: `CFRunLoopTimer` / `CFRunLoopPerformBlock` in `kCFRunLoopDefaultMode`; Windows: `PostMessage` to a message-only window). It answers polls and status from the shared table without the main thread, so `status` still responds while a modal dialog is up.
3. **Windows:** a message-only window plus `SetTimer` replaces the CFRunLoop timer. Modal loops on Windows **do** dispatch timers and posted messages, so the busy check is the only guard there. Check `IsWindowEnabled(GS_GetMainHWND())` and `GetGUIThreadInfo` flags. Read the version with `ISDK::GetHostInfo` on both platforms.
4. **Library: cpp-httplib** (MIT, single header, v0.66.0). It has HTTP/1.1 and an RFC 6455 WebSocket server in the same header. Override two defaults: exclusive bind (it shares ports via `SO_REUSEPORT` by default) and a small thread pool. Keep in mind that it ignores SIGPIPE process-wide.
5. **Transport: plain HTTP request/response**, `POST /jobs` then `GET /jobs/{id}?wait=N` (long-poll), plus `GET /status`. This fits the relay's existing submit-then-poll loop. Add a WebSocket route later only if push events are needed; it would sit on the same server.
6. **Ports:** use a port of its own (not 9100/9101, the SolotechSuite relay's, and never 9222, which Vectorworks' embedded Chromium already listens on). Bind exclusively and fall back through a small range. Write the chosen port and a random bearer token to a discovery file that the relay reads. Give the Python guard its own module name so it can't collide with SolotechSuite's `_vwguard`.

---

## 1. Which entry point runs at launch with no UI?

### What the SDK offers

- **There is no `IProviderModule` or `IApplicationEventSink` in SDK 2027.** A grep of `SDKLib/Include` for `IProviderModule`, `IApplicationEvent*`, `IHttpServer`, `IWebSocket` and similar returns nothing [SDK]. The extension groups that do exist are Menu, Tool, Parametric, VSFunctions, WebPalettes, Animation and WSFunctionOptions (`GROUPID_Extension*` in `Interfaces/VectorWorks/Extension/IExtension*.h`, e.g. `IExtensionMenu.h:18`, `IExtensionWebPalette.h:17`) [SDK]. The vendor's plug-in module page names the same four classic extension types (Menu, Parametric, Tool, VS functions) and gives `plugin_main` as the single entry point ([developer-sdk: Info/Plug-in Module.md](https://github.com/Vectorworks/developer-sdk/blob/main/Info/Plug-in%20Module.md)) [docs].
- **`plugin_module_main` actions** are `kPluginModuleInit = -1`, `kPluginModuleDeinit = -2`, `kVCOMRegisterInterfaces = -3`, `kVCOMQueryInterface = -4`, `kVCOMReleaseInterface = -5` (`Kernel/API/MiniCadHookIntf.h:923-928`). One return flag exists: `kDoNotCache = 32  // does not cache the plug-in VCOM modules. it will initialize the plug-in on each launch` (`MiniCadHookIntf.h:932-934`) [SDK].
  - **[inferred]** That comment implies VW normally *caches* a module's interface registrations. Without `kDoNotCache`, it may skip calling the module at all on a later launch. So `kPluginModuleInit` is **not** a reliable "VW has launched" hook on its own.
  - **[observed]** About 20 minutes after launch, the running VW 2027 had 127 of the 129 bundled `.vwlibrary` modules mapped (`vmmap`). Only the four `Credentials*` libraries were absent. So in practice most modules are loaded at launch, but nothing in the headers promises it.
  - `REGISTER_Interface` only calls `GS_VWRegisterInterface` on `kVCOMRegisterInterfaces`. The instance is created on `kVCOMQueryInterface` (`VWFC/PluginSupport/VWExtensions.h:239-268, 289-300`) [SDK]. So the code that runs is whatever VW *queries*.
  - **Gotcha:** the group overload of `REGISTER_Interface_NoCache` calls `GS_VWRegisterInterface(iid, moduleInfo, false)` and **drops the group id** (`VWExtensions.h:329-333`) [SDK]. Do not use it for a group registration.
- **Menu, Tool and Web-palette extensions** only get events when the user invokes them (menu `DoInterface`, palette open). They are not a launch hook.

### The recommended hook: `IObjUpdateSupport`

- `GROUPID_ObjUpdateSupport` and `IObjUpdateSupport::Init(IObjUpdateSupportContext*)` are declared at `Interfaces/VectorWorks/Extension/IObjUpdateSupport.h:127-137`. In `Init`, a provider declares interest: `AcceptState`, `AcceptNotification(Uint32)`, `AddDataPaneProvider`, `GetWebPaletteFrame` and others (`IObjUpdateSupport.h:30-124`). Afterwards VW calls `OnNotification` for the notifications it accepted (`:141`) [SDK].
- **SDK sample:** `Source/Samples/UpdateManager/Source/ModuleMain.cpp:35` registers it with `REGISTER_Interface<Updater::CUpdateSupport>( GROUPID_ObjUpdateSupport, Updater::IID_UpdateSupport, ... )`. `Updater/UpdateSupport.cpp:16-31` calls `AcceptNotification(kNotifyUndoEndEvent)` in `Init` [SDK]. `ProvidersSampleModule/Source/TesterModule/UpdateSupport.cpp:15-20` does the same with `'SELC'`. The notification constants are documented as "to be used with the IObjUpdateSupportContext interface. See the 'UpdateManager' sample" (`Kernel/Core/MCNotification.h:13-14`) [SDK].
- **Why it runs at launch [inferred]:** VW has to collect every provider's `AcceptState` and `AcceptNotification` registrations before it can route the first object event or notification. So it queries the whole group and calls `Init` at startup, with no user action and no UI.
- **First-party precedent [observed]:** the RTTI strings in the shipped `Vectorworks Remote`, `AIAssistant` and `NotesManager` plug-ins include `VCOMImmediateImpl<VectorWorks::Extension::IObjUpdateSupport>`. `Vectorworks Remote` also carries `kServerPortTxt_help` and `VectorworksAssistant::Server::IMessageListener`. That is a background-server feature with no palette, built on this hook (the socket itself appears to live in the core: the plug-in imports no socket functions).
- **Lifecycle notifications [SDK]** (`Kernel/Core/MCNotification.h`): `kNotifyApplicationShutdown = 'APSD'` (:204), `kNotifyBeforeApplicationQuit = 'BApQ'` (:284), `kNotifyDocOpen = 'dcop'` (:37), `kNotifyDocClose = 'DCLS'` (:28), `kNotifyDocChange = 'DOCC'` (:27), `kNotifyApplicationActivate = 'AppA'` (:167), `kNotifyDialogDisplayImminent = 'DlgO'` (:255). The first two give a clean teardown point. The document ones feed `/status`.
- **Shutdown rule [docs]:** the vendor wiki's `ISDK::UnregisterNotificationProcedure` page warns that a notification procedure must be unregistered before set-down, or VW crashes on the next notification. Apply the same discipline to the server: stop it on `APSD`/`BApQ`, with `kPluginModuleDeinit` as a backstop.

**Verify (prototype):** log a timestamp from `kPluginModuleInit`, `kVCOMRegisterInterfaces`, `IObjUpdateSupport::Init`, the first main-loop timer fire and the first `kNotifyDocOpen`. Do this on a cold launch and on a second, cached launch, on both macOS and Windows. This confirms that `Init` runs every launch without `kDoNotCache`. If it doesn't, return `kDoNotCache` from `kPluginModuleInit`.

### What is safe in `Init`, and when the main loop is ready

- **Safe:** reading a config or discovery file, building the server object, starting the background listener thread (it touches only sockets and does no SDK calls), and arming a one-shot default-mode main-loop timer (macOS) or creating the message-only window (Windows, see §3).
- **Not safe:** document access, the Python engine, creating UI, or anything that blocks. No document exists yet. The SolotechSuite bridge saw a `vs.*` call with **no document open crash VW (0x1c7)** [current bridge], so the job runner must keep the "no document → refuse" check.
- **Main loop readiness [docs]:** "If the run loop is not running at all, the timer never fires" ([Apple, Run Loops: Timers and modes](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html)). A timer armed in `Init` fires on the first default-mode pass once `NSApplication` runs, so the exact start time doesn't matter. The same is true on Windows: a posted message or `WM_TIMER` waits until the message loop pumps.

### The optional status palette

Keep a web-palette extension (`GROUPID_ExtensionWebPalettes`), opened from a menu command. It only reads status from the same in-process state: connections, last job, busy reason, VW build. It no longer carries the bridge, so closing it never disconnects anything.

---

## 2. Socket design and the hand-off to the main thread

### Thread-safety rules

- **[observed]** The core is not thread-safe for document access, and all document work runs on the main thread (internal reverse-engineering notes, VW 2027; consistent with every crash the current bridge has logged). The SDK headers mark only specific exceptions: `IWebBrowserDlg::CloseDialog` "can be used on the JS thread. It already accounts for main thread sync" (`Interfaces/VectorWorks/UI/IWebBrowserDlg.h:143`), and VWMM memory callbacks are "thread-safe" (`VWMM/VWMM.h:170, 358`). VCOM reference counts are `std::atomic` (`MiniCadHookIntf.h:1164-1166`), but that covers only `AddRef`/`Release`.
- **Rule:** the socket thread makes **no** `gSDK`/`GS_*` calls and no Python calls, and doesn't log through VW. It touches only its own mutex-protected structures.

### Option A, chosen: background thread with blocking I/O

The library owns the accept loop and a small worker pool. Handlers do only this:

| Request | Socket thread does | Main thread does |
|---|---|---|
| `POST /jobs` | Validate the auth token, assign a `jobId`, push it onto the queue (mutex), wake the main loop, return `{jobId}` | The deferred callback drains the queue and runs each job if not busy, then writes the result into the table (mutex) and signals a condition variable |
| `GET /jobs/{id}?wait=N` | Wait on the condition variable up to N s, then return `{done, result}` or `{pending}` | — |
| `GET /status` | Read a snapshot: the busy reason, `lastMainLoopTick` age, VW build, document open, guard table version | A 1 s default-mode heartbeat timer updates `lastMainLoopTick`, busy state and document state |

- **Why it's better than today:** polls are answered without the main thread. While a modal dialog is up, or VW is stuck inside a call, the relay still gets a truthful `{pending, busy:"dialog", mainLoopStalledFor: 12.3}` instead of a blind timeout. Today every poll goes through the palette's JS callback on the main thread (`McpBridge/server.mjs` `runJob` → `callPalette('execute_script', {poll})`) [current bridge].
- **The job model carries over:** today's `ScheduleDeferredScript` → `ArmDeferredTimer(jobId, 0)` → `DeferredJobTimerCB` (busy: re-arm 0.25 s up to `kDeferredBusyTimeoutSec`; otherwise `RunScriptNow`) (`Source/SolotechSuite/ExtSolotechSuite.cpp:2024-2085`) [current bridge]. The only changes: `gDeferredJobs` becomes mutex-guarded, because two threads touch it now (today's comment says it "needs no locking" because both callers ran on the main thread, `:1980-1982`), and the main thread never holds the lock while running a script.

### Waking the main thread on macOS: default mode only

- **[docs]** "The functions in Core Foundation are generally thread-safe and can be called from any thread" (Apple, *Thread safety of run loop objects*). `CFRunLoopAddTimer(CFRunLoopGetMain(), t, kCFRunLoopDefaultMode)` plus `CFRunLoopWakeUp`, or `CFRunLoopPerformBlock(main, kCFRunLoopDefaultMode, ^{…})` plus `CFRunLoopWakeUp`, from the socket thread is fine. Don't use `NSRunLoop` across threads (same page).
- **Do not use `dispatch_async(dispatch_get_main_queue())`.** CF services the main GCD queue in **every common mode**: `if (libdispatchQSafe && (CFRunLoopGetMain() == rl) && CFSetContainsValue(rl->_commonModes, rlm->_name)) dispatchPort = _dispatch_get_main_queue_port_4CF();` ([CFRunLoop.c:3069, swift-corelibs-foundation](https://github.com/swiftlang/swift-corelibs-foundation/blob/main/Sources/CoreFoundation/CFRunLoop.c)) [docs]. For Cocoa apps, the common modes "include the default, modal, and event tracking modes" (Apple, Table 3-1) [docs]. Main-queue blocks would run inside a modal dialog's loop. That is exactly crash C2, which the current bridge fixed by moving to default mode only (`ExtSolotechSuite.cpp:2034-2036`) [current bridge].
- A default-mode timer also stays quiet during menu tracking and window drags, because those are event-tracking mode.
- Keep `IsModalWindowUp()` (`[NSApp modalWindow] != nil`, `ExtSolotechSuite.cpp:1994-2006`) as a second check. VW's own nested loops can run in default mode, as the venue-build progress pump did (`gVenueBuildRunning`) [current bridge].

### Option B, rejected: main-run-loop socket (CFSocket / dispatch source)

- No threads at all, but every byte of I/O then rides on the main thread. A slow or half-open client stalls VW's UI. In default mode the socket is dead while a modal dialog is up, so `/status` can't answer. In common modes it runs during modals, which is the C2 hazard again.
- No Windows equivalent without `WSAAsyncSelect` on a window: a second platform-specific I/O stack.
- **[observed]** The shipped `BluebeamConnect` plug-in imports `socket/bind/listen/accept/select/recv/send` plus `this_thread::sleep_for` and has an `HTTP/1.1 200 OK` string. That looks like a short-lived blocking loopback listener run inside a command (e.g. an OAuth redirect), which isn't a model for a session-long server.

---

## 3. Windows equivalents

| Need | macOS today | Windows |
|---|---|---|
| Wake the main thread from the socket thread | `CFRunLoopAddTimer(main, …, kCFRunLoopDefaultMode)` | `PostMessage(gMsgWnd, WM_APP+1, 0, 0)` to a **message-only window** (`CreateWindowEx(…, HWND_MESSAGE, …)`) created on the main thread in `IObjUpdateSupport::Init` |
| Retry while busy (250 ms) | Re-arm the CF timer | `SetTimer(gMsgWnd, kRetryId, 250, nullptr)`, handled as `WM_TIMER` in that window's proc |
| Heartbeat (1 s) | Repeating default-mode CF timer | `SetTimer(gMsgWnd, kHeartbeatId, 1000, nullptr)` |
| Is a modal up? | `[NSApp modalWindow]` | `!IsWindowEnabled(GS_GetMainHWND(gCBP))`, **or** `GetGUIThreadInfo(mainTid)` has `GUI_INMENUMODE` / `GUI_INMOVESIZE` / `GUI_POPUPMENUMODE` / `GUI_SYSTEMMENUMODE`. Add `kNotifyDialogDisplayImminent` as a hint |
| VW version | `CFBundleShortVersionString` | `ISDK::GetHostInfo(...)` on both platforms; fallback `GetFileVersionInfoW` on `GetModuleFileNameW(nullptr)` |

**Evidence**
- **Timers need the thread's message loop [docs]:** "DispatchMessage calls the callback function … Therefore, you need to dispatch messages in the calling thread" ([SetTimer](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-settimer)). Minimum interval is `USER_TIMER_MINIMUM` (10 ms).
- **Modal loops on Windows *do* dispatch your messages [docs]:** "the system starts its own message loop … When the system retrieves a message that is not explicitly for the dialog box, it dispatches the message to the appropriate window" ([About Dialog Boxes: Modal Dialog Boxes](https://learn.microsoft.com/en-us/windows/win32/dlgbox/about-dialog-boxes)). **Windows has no counterpart to macOS's default-mode filtering**, so the posted message and `WM_TIMER` will fire while a dialog is up. The busy check in the handler is the *only* guard on Windows, and the handler must re-arm instead of running the job.
- **Modal dialogs disable their owner [docs]:** "the system automatically disables the window and any child windows belonging to it when it creates the modal dialog box. The owner window remains disabled until the dialog box is destroyed" (same page). That is why `IsWindowEnabled(mainHwnd)` works as a check for any well-behaved modal: Win32 `DialogBox`, `MessageBox` and MFC `DoModal`.
- **The main window handle [SDK]:** `extern "C" HWND GS_CALLBACK GS_GetMainHWND(CallBackPtr);  // Gets the Windows HWND … associated with the MiniCad application` (`Kernel/API/APIBase.Legacy.Defs.h:7197`). `OnlyWin/WinDefinitions.h:47` also declares `hMainWnd`, and `:51` declares `gl_InWinDialog  // Number of dialogs open`, but those are app globals that a plug-in DLL probably can't link against (**verify**). The SDK's Windows dialogs are MFC (`OnlyWin/GSDialog.h:13`, `OnlyWin/GSWinSDK.h:29-60`).
- **Version [SDK]:** `ISDK::GetHostInfo(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& outProductName, TXString& outProductVersion)` (`Interfaces/VectorWorks/ISDK.h:1918`) works on both platforms. **Verify** whether `outProductVersion` carries the build number (e.g. `882075`) that the safety table is stamped with. If not, keep `CFBundleShortVersionString` on macOS (`ExtSolotechSuite.cpp:1841-1849`) and read `VS_FIXEDFILEINFO` or `StringFileInfo\…\ProductVersion` from the exe on Windows.
- **Not checked:** the Windows build of VW 2027 wasn't available. Its UI toolkit (MFC vs. Qt for newer dialogs), whether every VW modal disables the main frame, and its nested message pumps during long operations are unknown. The Windows column above is a design that the prototype must confirm.

---

## 4. Server library

| Library | License | Shape | HTTP | WebSocket server | Notes |
|---|---|---|---|---|---|
| **cpp-httplib** (yhirose) | **MIT** | 1 header, C++11, v0.66.0 (2026-11-10), actively maintained | HTTP/1.1 | **Yes** (`svr.WebSocket("/ws", …)`, RFC 6455, no extensions) | Blocking I/O, thread pool. **Recommended** |
| IXWebSocket | BSD-3 | Library (several files), v12.1.0 | Minimal | Yes | Good WS, weak HTTP. Two libraries if you want both |
| uWebSockets | Apache-2.0 | Needs uSockets plus its own event loop | Yes | Yes | Wants to own an event loop. Overkill for one local client |
| civetweb | MIT (repo reports NOASSERTION) | C, few files, last release v1.16 (2023) | Yes | Yes | Older, larger attack surface |
| websocketpp | BSD (NOASSERTION) | Header-only but needs Asio | — | Yes | Last release 0.8.2 (2020). Effectively unmaintained |
| Mongoose | **GPLv2 / commercial** | 2 files | Yes | Yes | **Not permissive.** Don't embed in a public MIT project |

(License, release and activity from the GitHub API, 2026-11-16 [docs].)

**cpp-httplib: pros [docs, its README]**
- One header with no dependencies (TLS optional and not needed on loopback). MIT matches this repo's license.
- "A C++11 single-file header-only cross platform HTTP/HTTPS library". Builds the same on macOS (clang) and Windows (MSVC; link `ws2_32`).
- HTTP and WebSocket on one `Server`, so choosing HTTP now doesn't lock out WS later ([README-websocket.md](https://github.com/yhirose/cpp-httplib/blob/master/README-websocket.md)).
- Blocking I/O on its own thread pool fits Option A directly. Handlers can block on a condition variable for long-poll. `svr.stop()` from another thread makes `listen()` return, for a clean shutdown.

**cpp-httplib: cons and required overrides [docs, its README]**
1. **Port sharing by default.** "the server socket enables address/port reuse: `SO_REUSEPORT` … (Linux, macOS), and `SO_REUSEADDR` otherwise (Windows) … binding to a port that another server is already listening on also succeeds, and connections are distributed between them." Override with `set_socket_options` (`SO_REUSEADDR` only on macOS, `SO_EXCLUSIVEADDRUSE` on Windows) so a second VW instance **fails** to bind instead of silently sharing. See §5.
2. **SIGPIPE.** "the `Server` constructor … calls `signal(SIGPIPE, SIG_IGN)`, which affects the whole process." Inside VW that changes the host's signal disposition. It's harmless in practice (VW is a GUI app), but note it, and avoid TLS on loopback.
3. **Thread pool size.** The default is `max(8, hardware_concurrency-1)` threads, scaling up to 4×. "A connection holds its thread while it is served … and for the whole life of a WebSocket." Set `svr.new_task_queue = []{ return new httplib::ThreadPool(2, 4); }`. One relay doesn't need more.
4. Blocking I/O, HTTP/1.1 only, and WebSocket extensions unsupported. None of that matters for one local client.

### HTTP or WebSocket?

**Plain HTTP request/response, with long-poll.** Reasons:
- The relay already works as submit-then-poll (`runJob`: submit `{defer:true}`, then loop `{poll: jobId}` every `DEFER_POLL_INTERVAL_MS`, `McpBridge/server.mjs` ~141-160) [current bridge]. HTTP maps onto it one-for-one: `POST /jobs`, then `GET /jobs/{id}?wait=5`. Long-poll removes the poll-interval latency without push.
- It's stateless: either side can restart without reconnect logic, heartbeats or "a new palette connected, replacing the previous one" handling (`server.mjs:87-90`). It can be debugged with `curl`.
- WebSocket earns its place only for **unsolicited push** (selection changed, document closed, VW going down). Those are nice-to-haves. If needed later, add `svr.WebSocket("/events", …)` on the same server.
- **Alternative worth noting:** keep today's direction, with the plug-in as a *client* (cpp-httplib's `WebSocketClient`) dialing the relay's existing `:9100` server. That opens no listener in VW, and the relay protocol stays unchanged. But it needs a reconnect loop in C++, and it doesn't answer this ticket's "serve a socket" question. It's a fallback if a listening socket in VW turns out to be a problem: firewall prompts or a security review.

### Security (a local listener that executes code)

Any web page in the user's browser can send requests to `127.0.0.1:<port>`, and DNS rebinding can make a page look same-origin. Because `/jobs` runs Python inside VW:
- Bind `127.0.0.1` only (never `0.0.0.0`).
- Require `Authorization: Bearer <token>`. The token is random per VW session and written to the discovery file (user-only permissions), which the relay reads.
- Reject any request with an `Origin` header, or whose `Host` isn't `127.0.0.1:<port>` / `localhost:<port>` (`set_pre_routing_handler`).
- **Verify:** that a loopback-only listener inside VW triggers no macOS Application Firewall prompt and no Windows Defender Firewall prompt (both normally prompt only for non-loopback listeners).

---

## 5. Port conflicts with SolotechSuite (both installed)

**Facts**
- **[current bridge]** The SolotechSuite relay (Node) **listens** on WS `127.0.0.1:9100` (`SOLOTECH_WS_PORT`) and MCP HTTP `127.0.0.1:9101` (`SOLOTECH_HTTP_PORT`) (`McpBridge/server.mjs:35-36, 82, 339`). The palette is a **client** that dials `ws://127.0.0.1:9100` (`SourceHTML/src/mcp/bridgeClient.js:14`). Inside VW, SolotechSuite listens on nothing.
- **[observed]** The running VW 2027 process itself listens on `127.0.0.1:9222` (the embedded Chromium remote-debugging port) and `127.0.0.1:61412` (ephemeral; owner unconfirmed) (`lsof -iTCP -sTCP:LISTEN`).
- **[current bridge]** Builds exist per VW year (2026 and 2027), so **two VW instances can run at once**, each loading its own copy of the plug-in.

**Conflicts and fixes**
1. **No conflict in VW if vw-mcp avoids 9100/9101.** vw-mcp's plug-in is the only listener inside VW. Pick a default outside SolotechSuite's pair and away from 9222, e.g. `9310`, overridable by config.
2. **Two VW instances (2026 + 2027):** bind exclusively (see §4, override 1), so the second instance gets `EADDRINUSE`. Try `base … base+9`, then write `{pid, port, token, vwBuild, startedAt}` to a per-user discovery file, e.g. `~/Library/Application Support/vw-mcp/instances/<pid>.json` or `%APPDATA%\vw-mcp\instances\<pid>.json`. Delete it on `kNotifyApplicationShutdown`. The relay picks the instance (default: the newest, or the build the user names) and skips stale files whose PID is gone. **Without the exclusive-bind override, cpp-httplib's default `SO_REUSEPORT` lets both instances bind the same port, and the relay's requests would hit either VW at random.**
3. **vw-mcp's relay vs. SolotechSuite's relay:** if vw-mcp ships its own Node relay, it must not default to 9101 for MCP HTTP. Otherwise only one of the two relays starts.
4. **Two bridges in one VW (non-port, but the same root cause):** both plug-ins run Python in the shared `vs` interpreter. The SolotechSuite guard installs itself as `sys.modules['_vwguard']` and replaces it whenever `VERSION` differs (`ExtSolotechSuite.cpp` `BuildGuardedPython`, ~1852-1860) [current bridge]. If vw-mcp reuses that name with a different version, the two bridges keep overwriting each other's guard. **Use a distinct module name** (e.g. `_vwmcp_guard`) and a separate data folder (`Plug-ins/Data/vw-mcp/`, not `.../SolotechSuite/`). Jobs from both bridges are serialized on the main thread, so there is no data race, but neither bridge's busy check sees the other's job.
5. **Two copies of vw-mcp** (user folder plus workgroup folder) would both try to bind. Exclusive bind plus the discovery file turns that into a clear "already running (pid N)" log line instead of a silent split.

---

## Open items for the prototype ticket

1. Confirm `IObjUpdateSupport::Init` runs on every launch (cold and cached) on macOS and Windows, and record the order of `kPluginModuleInit` → `Init` → first default-mode timer → first `kNotifyDocOpen`.
2. Confirm `kNotifyApplicationShutdown` / `kNotifyBeforeApplicationQuit` arrive early enough to `svr.stop()` and join the thread with no hang at quit.
3. Windows: confirm `IsWindowEnabled(GS_GetMainHWND())` goes false for VW's own modal dialogs (including any Qt or web dialogs), and find out which VW long operations pump messages, where a `WM_TIMER` could fire mid-command.
4. Check what `ISDK::GetHostInfo` returns for `outProductVersion` (does it include the build number?).
5. Check for firewall prompts on first `listen()` on both OSes.

## Sources

- Vectorworks SDK 2027 headers and samples (local SDK checkout): `Kernel/API/MiniCadHookIntf.h`, `Kernel/API/APIBase.Legacy.Defs.h`, `Kernel/Core/MCNotification.h`, `Interfaces/VectorWorks/Extension/IObjUpdateSupport.h`, `Interfaces/VectorWorks/ISDK.h`, `Interfaces/VectorWorks/UI/IWebBrowserDlg.h`, `VWFC/PluginSupport/VWExtensions.h`, `VWMM/VWMM.h`, `OnlyWin/*.h`, `Source/Samples/UpdateManager`, `Source/Samples/ProvidersSampleModule`.
- Vectorworks developer docs: [developer-sdk / Info / Plug-in Module.md](https://github.com/Vectorworks/developer-sdk/blob/main/Info/Plug-in%20Module.md), [VCOM.md](https://github.com/Vectorworks/developer-sdk/blob/main/Info/VCOM%20(Vectorworks%20Component%20Object%20Model).md), developer.vectorworks.net `ISDK::UnregisterNotificationProcedure` (as summarized by search; the wiki now redirects to GitHub).
- Apple: [Threading Programming Guide: Run Loops](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/Multithreading/RunLoopManagement/RunLoopManagement.html). [swift-corelibs-foundation CFRunLoop.c](https://github.com/swiftlang/swift-corelibs-foundation/blob/main/Sources/CoreFoundation/CFRunLoop.c) (lines 1125, 3069).
- Microsoft Learn: [SetTimer](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-settimer), [About Dialog Boxes](https://learn.microsoft.com/en-us/windows/win32/dlgbox/about-dialog-boxes), [GetGUIThreadInfo / GUITHREADINFO](https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-guithreadinfo), [Message-only windows](https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features#message-only-windows).
- cpp-httplib: [README](https://github.com/yhirose/cpp-httplib) (v0.66.0: port sharing, SIGPIPE, thread pool), [README-websocket.md](https://github.com/yhirose/cpp-httplib/blob/master/README-websocket.md).
- Observed on VW 2027 32.0.0 (macOS, arm64): `vmmap` / `lsof` on the running process, and `nm -u` / `strings` on shipped plug-ins (`Vectorworks Remote`, `AIAssistant`, `NotesManager`, `BluebeamConnect`).
- Current bridge (SolotechSuite, branch `feat/mcp-hardening`): `Source/SolotechSuite/ExtSolotechSuite.cpp`, `Source/SolotechSuite_ModuleMain.cpp`, `McpBridge/server.mjs`, `SourceHTML/src/mcp/bridgeClient.js`.
