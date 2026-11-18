//
//  Bridge.h
//  The headless bridge: a loopback HTTP server on a background thread, a job queue, and a
//  main-thread pump that runs queued jobs on clean main-loop passes. See docs/research
//  (headless-plugin-socket) and issue #6.
//
//  Internal endpoints (used by the relay only, not a public API):
//    GET  /status            bridge state, connected AI clients, last 50 jobs, paused/saveFirst, saveable scripts
//    POST /jobs              { code, lang?, allowDocumentLevel?, allowUnclassified?, timeoutSec? } -> { jobId }
//    GET  /jobs/{id}?wait=N  long-poll (N <= 25 s) -> { pending:true } or the job result (one-shot)
//    GET  /safety-table      the embedded safety table;  GET /signatures  vs.* signatures
//  Every request needs "Authorization: Bearer <token>"; requests with an Origin header are refused.
//  The port and token are in the discovery file <Application Support>/vw-mcp/instances/<pid>.json.
//
#pragma once

namespace VwMcp
{
    namespace Bridge
    {
        void Start();   // main thread, at launch (IObjUpdateSupport::Init)
        void Stop();    // main thread, at application shutdown
        nlohmann::json StatusJson();   // the GET /status body; any thread

        // Palette Utility tab (#27); any thread. The save itself runs as an internal job on the pump.
        nlohmann::json JobCode(int jobId);                                   // { ok, code, lang, ... }
        void           SetPaused(bool on);                                   // refuse new jobs (class "paused")
        void           SetSaveFirst(bool on);                                // save each drawing before its first job
        nlohmann::json QueueSaveScript(int jobId, const std::string& name);  // { ok, ticket } | { ok:false, error }
        nlohmann::json TakeInternalResult(int ticket);                       // { pending:true } | the result

        // Research (#29): called by the hidden menu command's DoInterface; runs the pending job.
        void           RunPendingInMenu();
    }
}
