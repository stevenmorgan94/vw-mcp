//
//  SdkScopes.h
//  RAII scopes every bridge job runs inside (main thread only).
//
#pragma once

namespace VwMcp
{
    // While a job runs, suppress the modal prompts that would open a nested event loop on the main
    // thread: the "cannot be undone" warning and the stop-on-warning halt. Alerts go to the mode bar
    // instead of a dialog. The user's settings are restored afterwards.
    struct ScriptDialogGuard
    {
        Boolean savedUndoWarn = true;
        Boolean savedStopOnWarn = false;
        Boolean savedAlertsOnModeBar = false;

        ScriptDialogGuard()
        {
            gSDK->GetProgramVariable(varShowUndoWarnings, &savedUndoWarn);
            gSDK->GetProgramVariable(varStopVSOnWarnings, &savedStopOnWarn);
            gSDK->GetProgramVariable(varShowAlertsOnModeBar, &savedAlertsOnModeBar);
            Boolean off = false, on = true;
            gSDK->SetProgramVariable(varShowUndoWarnings, &off);
            gSDK->SetProgramVariable(varStopVSOnWarnings, &off);
            gSDK->SetProgramVariable(varShowAlertsOnModeBar, &on);
        }
        ~ScriptDialogGuard()
        {
            gSDK->SetProgramVariable(varShowUndoWarnings, &savedUndoWarn);
            gSDK->SetProgramVariable(varStopVSOnWarnings, &savedStopOnWarn);
            gSDK->SetProgramVariable(varShowAlertsOnModeBar, &savedAlertsOnModeBar);
        }
    };

    // Each job is its own named undo step. Jobs run from an idle main-loop pass, not from inside a VW
    // command, so no undo event is open for them: a mutating call would otherwise reach a null undo
    // event and crash. VW can also leave a stale event open while idle; adding to it merges jobs into
    // one unfinished event that VW may later roll back wholesale, so that event is committed first.
    struct UndoEventScope
    {
        bool fOwnsEvent = false;
        bool fCommittedStale = false;

        explicit UndoEventScope(const TXString& name)
        {
            if (gSDK->IsCurrentlyBuildingAnUndoEvent())
            {
                gSDK->EndUndoEvent();
                fCommittedStale = true;
            }
            if (!gSDK->IsCurrentlyBuildingAnUndoEvent())
            {
                gSDK->SetUndoMethod(kUndoSwapObjects);
                gSDK->NameUndoEvent(name);
                fOwnsEvent = true;
            }
        }
        ~UndoEventScope()
        {
            if (fOwnsEvent)
                gSDK->EndUndoEvent();
        }
    };
}
