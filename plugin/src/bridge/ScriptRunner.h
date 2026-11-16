//
//  ScriptRunner.h
//  Runs one bridge job on the main thread: guarded Python (ctx engine) or native ops.
//
#pragma once

namespace VwMcp
{
    struct JobRequest
    {
        std::string    code;
        std::string    lang = "python";                    // "python" | "ops"
        nlohmann::json opts = nlohmann::json::object();    // allowDocumentLevel, allowUnclassified, timeoutSec
    };

    extern const int kGuardVersion;     // keep in step with VERSION in safety/vwguard.py

    // Main thread, once at launch: resolves the data folder and the running Vectorworks build.
    void InitHostInfo();

    const std::string& DataFolder();         // Plug-ins/Data/vw-mcp/ in the user folder
    const std::string& VectorworksBuild();   // e.g. "32.0.0 (882075)"
    const std::string& TableBuild();         // the build the safety table was swept on
    int                TableFunctions();     // entries in the safety table
    bool               SweepMode();
    // run_native_op `call` (#11): the class an ISDK method inherits from its vs.* twin, or "unclassified".
    void               IsdkClass(const std::string& fn, std::string& cls, std::string& via);          // the SWEEP_MODE marker exists (filesystem only: any thread)

    nlohmann::json Refusal(const std::string& cls, const std::string& reason, const std::string& advice = "");

    // Main thread only, on a clean main-loop pass.
    nlohmann::json RunJob(const JobRequest& job);
}
