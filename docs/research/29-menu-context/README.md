# #29: can bridge jobs run inside a real menu command?

Research branch, never merged. VW 2027 32.0.0 (882075), macOS, 2026-11-17/18. Untitled throwaway drawings only.

## Answer

**Yes, a job can run inside a menu command, but it buys nothing.** All 13 crashers and hangs behave the same in the menu
context as from the bridge's timer. Don't move jobs to the menu path, and don't ship a workspace command.

## 1. Running a job inside a menu command

- A hidden menu extension (`ExtMenuVwMcpRunJob`, `DoInterface` runs the queued job) called with `gSDK->DoMenuName(universalName, 0)`
  from the pump timer **runs synchronously** (returns 0), *but only once the command is in the user's workspace*.
  Without it, `DoMenuName` returns -3 and runs nothing; the same holds for our Help-menu item (`AddSpecialMenuItem`) and for the
  menu title instead of the universal name. Matches SolotechSuite S20 and the hardening spec.
- Shipping it would mean editing every user's workspace (`IWorkspaceFile` + `SetWorkspaceFileToReload`) or a manual install step.
- Context probe in both paths: `IsCurrentlyBuildingAnUndoEvent` false, no modal window. The menu path adds no undo event of its own.

## 2. The 13 functions (guard off via SWEEP_MODE; `run.mjs`, `results.jsonl`)

| Function | Case | Menu | Timer | Sweep v2 said |
|---|---|---|---|---|
| AddVectorFillLayer | valid | crash | crash | crasher |
| DisplayContextHelpOfCurrentPlugin | valid | crash | crash | crasher |
| Plant_ReplacePlantParam | non-plant handle | crash | crash | crasher |
| SetConstraintValue | rect handle | crash | crash | crasher |
| CC_GetCircuitDest / Source | wrong object type | crash | crash | crasher |
| TBB_AttachRecords | no args | crash | crash | crasher |
| UprString | `UprString(1)` | crash | crash | crasher |
| RefreshResManager | valid | hang | hang | hang |
| **DisplayLayerScaleDialog** | valid; dialog cancelled | ok | ok (3/3) | crasher |
| **DisplayOrganizationDialog** | valid; dialog cancelled | ok | ok (3/3) | crasher |
| **SetTexSpaceEndCap** | text handle | ok | ok (3/3) | crasher |
| **RetrieveOpenGLPrefs** | valid | ok | ok (3/3) | hang |

The four in bold never reproduced (v2 recorded each once, `reproduced: null`); most likely v2 pinned a crash or
stall on the wrong job. The two dialog functions are still `interactive` (they open a modal); the other two look `safe`.

Not run: (a) the same cases as a user Run Script (needs mouse control). With menu == timer for every case, and the nine
real crashers all being bad or unsupported calls, a plain Run Script is expected to crash the same way. Event-only
functions weren't re-run either: they need a plug-in object or tool event, which neither path supplies.

## 4. Resetting plug-in objects created in the same run

Stage Decks created + filled red, then reset in the same job (`mk.py`, checked with `chk.py`: the 2D rect child's fill pattern):

- `vs.ResetObject(h)` in the same job: stale in both contexts.
- `vs.DoMenuTextByName('Reset All Plug-Ins', 0)` in the same job (Yes clicked): stale in both contexts. It does fix decks
  made by **earlier** jobs, in either context.

So there is no way to fix same-run PIOs from inside the run; the bridge's follow-up reset (#26) stays the fix, and a
handed-off script needs a follow-up job or the user's Reset All Plug-Ins.
