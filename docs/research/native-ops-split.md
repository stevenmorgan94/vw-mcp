# Native ops: what moves to vw-mcp, and what stays in SolotechSuite

Research for issue #8. Question: go through `RunNativeOps`, `IsdkDispatch.inc` and the native op list, and decide which ops move to vw-mcp and which stay in SolotechSuite.

**Source read:** the SolotechSuite repo, branch `feat/mcp-hardening`, commit `50340c9`. All `file:line` references below point at that commit. The ISDK comparison uses the Vectorworks SDK 2026 and 2027 headers (`SDKLib/Include/Interfaces/VectorWorks/ISDK.h`).

## Short answer

- `RunNativeOps` has **20 op kinds**. **17 are generic**: 15 curated ops, `call` (generic ISDK dispatch) and `clearHandles`. **3 are Solotech-specific**: `venueBuildRequest`, `venueBuildStatus` and `generateSheets`.
- The generic ops depend only on the SDK, nlohmann::json and three helpers in `ExtSolotechSuite.cpp` (`ScriptDialogGuard`, `UndoEventScope`, `FinishCreatedObject`). They move as they are, after some small fixes.
- The Solotech ops are three `if` branches. Removing them also removes the `#include`s of `VenueLibraryBuild.inc` and `SheetGenerator.inc` from the native-ops unit. Nothing in the generic path calls into them.
- Three coupling points need work, all outside `RunNativeOps` itself:
  1. `IsDocumentBusy()` reads `gVenueBuildRunning`.
  2. `ReadDataFile()` (sweep marker, safety override) borrows `VenueBuild::DataFolder()`, which points at `Plug-ins/Data/SolotechSuite/`.
  3. Bridge names use Solotech branding: `solotechIntegrator`, `solotech-vw`, `SOLOTECH_*` environment variables.
- `IsdkDispatch.inc` is self-contained (12,307 lines, 1,726 ISDK methods). It can move as it is. However, vw-mcp targets VW 2027 only, so it should be **regenerated from the 2027 `ISDK.h`** by a new generator that is checked into the repo. The 2027 SDK adds 70 methods. About 41 of them fit the existing marshalling rules.
- Safety gap to close before a public release: the `call` path bypasses the vs safety table. It blocks only three name patterns, so modal calls (`AlertInform`, `DoMenuName`, `CloseDocument`, `Show*Dialog`, …) and null handles still reach the SDK.

## 1. Every op kind

Dispatch is a chain of `if ( kind == "…" )` branches in `RunNativeOps`, `Source/SolotechSuite/ExtSolotechSuite.cpp:1417-1800`. The relay advertises the curated list, `call` and `clearHandles` in the `run_native_op` tool description (`McpBridge/server.mjs:205-220`). It does **not** advertise the three Solotech ops. The relay has no per-op schema: `ops` is `z.union([z.string(), z.array(z.any())])`.

| Op | Verdict | Reason | Source |
|---|---|---|---|
| `call` | **generic** | Calls any of 1,726 ISDK methods by name through `DispatchIsdkCall`. Before dispatch it checks `IsBlockedIsdkCall`. Its handle arguments are `{"$h":id}`, `{"$name":…}` and `{"$layer":…}`. It needs a safety pass first; see §2.4. | `ExtSolotechSuite.cpp:1454-1470`, `IsdkDispatch.inc:12299` |
| `clearHandles` | **generic** | Clears `gHandleReg`, which `IsdkDispatch.inc` defines. | `ExtSolotechSuite.cpp:1490-1496`, `IsdkDispatch.inc:6` |
| `layer` | **generic** | Creates a design or sheet layer. A sheet layer can be sized in inches (`ovLayerSheetPaper*`). | `ExtSolotechSuite.cpp:1499-1524` |
| `viewport` | **generic** (clean up) | Creates a viewport on a named sheet layer, with optional `scale`, `name`, `crop`, `dx`/`dy`. It also returns probe diagnostics (`xpos`, `ypos`, `scaleReadback`, `vpBounds`, `cropBounds`) left over from the 2026-10-07 coordinate tests. Keep them or drop them, but document them. | `ExtSolotechSuite.cpp:1527-1601` |
| `delete`, `move`, `rotate` | **generic** | Act on a named object. Undo calls are correct (`AddBeforeSwapObject` before `DeleteObject(h,true)`; fixed for CRASH_LOG D1). | `ExtSolotechSuite.cpp:1604-1647` |
| `clearLayer` | **generic** (fix) | Deletes every object on a layer. **Bug:** it calls `DeleteObject(o, true)` without `AddBeforeSwapObject(o)`. CRASH_LOG D1 names that pattern as one cause of the silent rollback. Fix it while porting. | `ExtSolotechSuite.cpp:1650-1672`; `McpBridge/CRASH_LOG.md:172-175` |
| `duplicate` | **generic** | Duplicates a named object, with optional offset, `newName` and `layer`. CRASH_LOG verified it on symbol definitions. | `ExtSolotechSuite.cpp:1675-1705`; `CRASH_LOG.md:52` |
| `group` | **generic** | Groups named members, with optional name and layer. | `ExtSolotechSuite.cpp:1708-1738` |
| `rect`, `oval`, `rrect`, `line`, `locus`, `text`, `polygon` | **generic** | Native geometry, the crash-safe replacement for `vs.Rect` and friends (CRASH_LOG C8). All of them finish through `FinishCreatedObject`: class, name, weight, fill and pen colour, fill pattern, layer, undo. | `ExtSolotechSuite.cpp:1741-1792`, helper `:1323-1384`; `CRASH_LOG.md:142-161` |
| `venueBuildRequest` | **Solotech-specific, stays** | Writes `venue_build.json` for the Build Venue Library menu command. The venue library is Solotech data, and issue #1 lists it as out of scope. | `ExtSolotechSuite.cpp:1474-1478`, `VenueLibraryBuild.inc:721-737` |
| `venueBuildStatus` | **Solotech-specific, stays** | Reads `venue_build_last.json` and the log tail. | same; `VenueLibraryBuild.inc:738-754` |
| `generateSheets` | **Solotech-specific, stays** (a later generic candidate) | `SheetGen::Generate` uses only stock VW objects (sheet layers, the `Title Block Border` PIO, viewports), but its contract assumes the Solotech template: template sheet layers named by paper size ("ARCH D", "A1", …), each holding a Title Block Border, and an imperial architectural scale list. Its UI (`SheetGenDialog.inc`) stores state in a record format named "Solotech Sheet Generator" and tells the user to open "a drawing made from the Solotech template". Keep it in SolotechSuite for v1. If it is generalised later, the template convention becomes a parameter. | `ExtSolotechSuite.cpp:1481-1487`; `SheetGenerator.inc:1-20,74-86,175-190`; `SheetGenDialog.inc:35,224,518` |

Two things are not native ops and are not in scope here, but are worth knowing:

- **`VwemsHost.inc`** (the Pack-plan tab) has its own native edit applier, reached through `vwems_run`: lookup by `uuid`, then `layer`, `at`, `rotation`, `record`, `params` and `reset` (`VwemsHost.inc:136-200`). It is Solotech-specific, it does not go through `RunNativeOps`, and it stays. Its edit shape is generic, though, and would make a good later `edit` op for vw-mcp.
- **`execute_script` with `lang:"ops"`** still routes to `RunNativeOps` (`ExtSolotechSuite.cpp:1922`). The relay marks it as deprecated (`server.mjs:187-188`). Drop it in vw-mcp, so that `run_native_op` is the only way in.

## 2. Coupling points

### 2.1 Helpers the generic ops need (they move with them)

| Helper | Where | Coupling | Action |
|---|---|---|---|
| `ScriptDialogGuard` | `ExtSolotechSuite.cpp:1242-1268` | None (SDK program variables) | Move it. `RunScriptNow`, `VenueLibraryBuild.inc` and `VwemsHost.inc` also use it, so SolotechSuite keeps a copy. |
| `UndoEventScope` | `ExtSolotechSuite.cpp:1286-1318` | None. The undo name "MCP Native Ops" is unbranded. | Move it. SolotechSuite keeps a copy for `SheetGenDialog.inc` and `VwemsHost.inc`. |
| `FinishCreatedObject` | `ExtSolotechSuite.cpp:1323-1384` | None | Move it. |
| `IsBlockedIsdkCall` | `ExtSolotechSuite.cpp:1411-1415` | None | Move it, and replace it with a real table (§2.4). |
| `gHandleReg`, `gNextHandleId`, `ResolveHandle`, `J*`/`M*` marshal helpers | `IsdkDispatch.inc:6-28` | None. `MStr` duplicates `TXToStd` (`ExtSolotechSuite.cpp:1022`) and `VenueBuild::Std`. | Move them with the dispatch, and pull them out of the generated file into a hand-written header (§4). |
| Anonymous namespace | `RunNativeOps` and every `.inc` are textually included inside the `namespace {` that starts before `ScriptDialogGuard`. Several `.inc` comments rely on that. | Build-structure coupling | In vw-mcp, give each piece a real translation unit and header. Do not include `.inc` files into one 2,000-line `.cpp`. |

### 2.2 Globals and state that leak in from Solotech code

- **`gVenueBuildRunning`** is defined in `VenueLibraryBuild.inc:28`. `IsDocumentBusy()` and `DocumentBusyReason()` read it (`ExtSolotechSuite.cpp:2009-2016`) to keep deferred jobs, native ops included, away from the document during a venue build. That build pumps a progress bar, which lets the default-mode timer fire. Once the bridge lives in a separate plug-in, vw-mcp cannot see this flag.
  - **Action:** in vw-mcp, make `IsDocumentBusy()` a list of busy predicates: the modal-window check, plus anything that has registered. Options for SolotechSuite:
    - (a) vw-mcp publishes a small VCOM interface, e.g. `IVwMcpHost::SetBusy(reason)` / `ClearBusy()`, which SolotechSuite calls around `RunVenueLibraryBuild()`.
    - (b) Accept the risk for v1. The venue build is a manual menu command that the user starts.
  - This decision belongs in #6 or #10.
- **`ReadDataFile()`** (`ExtSolotechSuite.cpp:1814-1825`) reads the `SWEEP_MODE` marker and `vs-safety-override.json`. It builds the path with `VenueBuild::DataFolder()`, which is `Plug-ins/Data/SolotechSuite/` (`VenueLibraryBuild.inc:60-69`). This is not on the native-ops path, but the bridge core that ships with it needs it.
  - **Action:** add a vw-mcp-owned `DataFolder()` that returns `Plug-ins/Data/vw-mcp/`. Users who run the sweep or override the table will have to move their marker and override files.
- The `execute_script` busy and poll logic (`DeferredJob`, `gDeferredJobs`, `kDeferredBusyTimeoutSec`) is generic, but `VwemsHost.inc` uses it too (`VwemsHost.inc:24,219-221`). SolotechSuite keeps its own copy for vwems once the bridge leaves.

### 2.3 Solotech-branded names the generic path touches

| Name | Where | Rename to |
|---|---|---|
| JS object `solotechIntegrator`, function `execute_script` | `ExtSolotechSuite.cpp:61,82`; `SourceHTML/src/mcp/bridgeClient.js:134-141` | A vw-mcp-owned object, e.g. `vwMcp.execute_script`. The headless plug-in may not use a web palette at all (#2, #3). |
| MCP server id `solotech-vw` | `server.mjs:139` | `vw-mcp` (decided in #1) |
| Log prefix `[solotech-vw-mcp]` | `server.mjs:44` | `[vw-mcp]` |
| Env vars `SOLOTECH_WS_PORT`, `SOLOTECH_HTTP_PORT`, `SOLOTECH_CALL_TIMEOUT_MS`, `SOLOTECH_DEFER_POLL_MS` | `server.mjs:35-41` | `VW_MCP_*` |
| launchd label `com.solotech.vw-mcp`, log `solotech-vw-mcp.log` | `McpBridge/README.md` "Managing the relay" | A neutral reverse-DNS label |
| Data folder `Plug-ins/Data/SolotechSuite/` | `VenueLibraryBuild.inc:64`, `VwemsHost.inc:45` | `Plug-ins/Data/vw-mcp/` |
| `using namespace SolotechSuite;` | `ExtSolotechSuite.cpp:23` | Not used by the native-ops code. Drop it. |

The native ops have no resource strings (`TXResStr`). The only user-visible string they produce is the undo name "MCP Native Ops", which is fine.

### 2.4 Safety gaps to close before a public release

- **The `call` path skips the safety table.** Python goes through the swept vs table and the in-engine guard (`VsSafety.generated.inc`). `call` only checks `IsBlockedIsdkCall`, which matches the `BuildResourceList*` prefix, `GetResourceFromList` and the `CreateWorksheet*` prefix (`ExtSolotechSuite.cpp:1411-1415`). The dispatch table still exposes about 27 modal, menu or document-level methods, including:
  - `AlertInform`, `AlertQuestion`, `AlertCritical*`
  - `DoMenuName`
  - `CloseDocument`, `SaveActiveFile`
  - `Show*Dialog`, `DisplayOrganizationDialog`, `EditClassWithUI`

  Those are the classes that crashed or hung through the Python path.
  - **Action:** ship an ISDK safety table built the same way as the vs table: classes `safe`, `interactive`, `document-level`, `crasher`, deny by default except `safe`. `allowDocumentLevel` and `allowUnclassified` should apply here too. Until that table exists, a name-pattern denylist (`Alert*`, `*Dialog*`, `DoMenu*`, `Close*`/`Open*`/`Save*`, `*Layout*`) is a stopgap.
- **Null handles reach the SDK.** `JHandle` returns `nullptr` for an unknown `$h`, `$name` or `$layer` (`IsdkDispatch.inc:9-21`), and the shim passes it straight to `gSDK->…`. Many ISDK methods dereference it. The `try/catch` only catches marshalling exceptions.
  - **Action:** the generator should emit a null check for every handle parameter and return `{"ok":false,"error":"handle arg N did not resolve"}`.
- **No per-op schema** on the relay side (`server.mjs:213`). For a public tool, give the curated ops a zod discriminated union so the client gets argument errors before the job runs.

## 3. The generated ISDK dispatch

**Size and shape**
- `Source/SolotechSuite/IsdkDispatch.inc`: **12,307 lines, 1,726 entries** in one `std::unordered_map<std::string, IsdkShim>` built from lambdas.
- Header comment: "AUTO-GENERATED from ISDK.h … Regenerate with scratchpad/gen_dispatch.py". That script is not in the repo or its history. The file arrived in the baseline commit `72fa9e5` and the generator was never committed.

**Dependencies**
It depends only on:
- `gSDK` (ISDK)
- `MCObjectHandle`, `TXString`, `WorldPt`, `WorldPt3`, `WorldRect` and the SDK scalar typedefs
- nlohmann::json, the copy bundled with the SDK
- `<unordered_map>`

It has no Solotech symbols. It can move as it is.

**Coverage against the SDK 2026 `ISDK.h`**
- 2026 declares 2,461 pure-virtual methods with 2,434 distinct names.
- The dispatch covers 1,726 names. It skips 708, which are methods whose parameters the generator could not marshal. The most common skipped types are `const ViewPt&` (103), `void*` (28), `MCObjectHandle&` out (27), `IFileIdentifier*` (24) and `GSHandle` (14), plus structs, STL containers and callbacks.
- The table is keyed by name, so 13 overloaded names (for example `CreateMesh`, `CoordToSIAString`) expose only one overload.

**Marshalling rules, read off the output (a new generator must reproduce them)**

| Parameter or return | JSON form |
|---|---|
| Integer, enum and `Boolean` parameters | JSON number or bool (`JInt`/`JBool`) |
| `double`, `WorldCoord` | JSON number (`JReal`) |
| `const TXString&` | JSON string |
| `MCObjectHandle` | `{"$h"}` / `{"$name"}` / `{"$layer"}` |
| `WorldPt` / `WorldPt3` / `WorldRect` | `[x,y]` / `[x,y,z]` / `[x1,y1,x2,y2]` |
| Non-const scalar, `TXString&` or point reference | Becomes `r["out"][<paramName>]` |
| `MCObjectHandle` return | Registered in `gHandleReg` under `as` (or an auto id), returned as `r["as"]`, with `ret` set to a bool |
| Other returns | `r["ret"]` |

**What VW 2027 changes (2026 vs 2027 `ISDK.h`)**
- **Removed in 2027 (8 methods):**
  - `DeleteAllComponents`, `GetCurtainWallCutPlane`, `SetCurtainWallCutPlane`, `GetLayerEnableCutPlane` and `SetLayerEnableCutPlane` are in the dispatch. They are the five entries wrapped by hand in `#if SDK_VERSION < 3200` (`IsdkDispatch.inc:4491, 9787, 9794, 10192, 10199`).
  - `GetPhase`, `GetWallCapAttributesType` and `SetWallCapAttributesType` were never in the dispatch.
  - VW 2026 is out of scope for vw-mcp (#1), so the guards and those five entries can simply go.
- **Signature changes on dispatched methods (7):** all of them still compile with the existing shims.
  - `EditPluginStyle`, `SetPhaseName` and `SetPhaseDescription` now return `bool`. The shim calls them as `void`, so the result is discarded.
  - `ClipSurface`, `CreateCustomObject` and `CreatePluginStyle` gained trailing defaulted parameters.
  - `ChoosePluginStyleForReplace` gained an overload.
  - A regeneration would expose the new returns and parameters.
- **New in 2027 (70 methods, declared with `VCOM_CALLTYPE`):**
  - **About 41 fit the existing marshalling rules:**
    - Wall and top-plan cut plane: `Get/SetWallCutPlane`, `Get/SetUseWallCutPlane[ByStyle]`, `Get/SetTopPlanViewCutPlane[ByStyle]`, `Get/SetWallAboveCutPlaneClass`, `Get/SetWallCutPlaneIsRelativeToWallBottom`, `Get/SetWallUseDesignLayerCutPlane`, `GetWallCalculatedCutPlane`, `Get/SetWallAddProfileLine`
    - Classes: `Get/SetClassIsNonPlot`
    - Snap points: `Get/SetMasterSnapPointName`
    - Data visualization: `ActivateDataVisualization`, `ActivateDVSetElement`, `IsDVSet`, `IsValidCriteria`
    - Other: `GetComponentID`, `GetTypeOfSolid`, `IsDocumentOpen`, `ResetCustomObject`, `CancelTempTool`
    - Dialog-only: `AddComboBoxMethod*`, `Get/SetComboBoxMethodValue`, `ClearComboBoxMenuMethodItems`, `SetSliderTickMarks`, `SetHighlightedTitleBarLabelInDialog`, `ObjPropsEditDlg`, `ShowCustomDimensionUnitsDialog`
    - The dialog-only ones should be refused, not exposed.
  - **About 29 need new marshalling:**
    - Phases: `AddPhase`, `GetPhaseByIndex`, `GetPhaseByRef`, `Get/SetObjPhaseData`, `GetStatusInPhase`, `IsPresentInPhase`, `SetDocumentActivePhase`, `SetViewportActivePhase` (`SPhaseData`, `SObjPhaseData`, `PhaseReference`)
    - Data visualization: `CreateDataVisualization`, `CreateDVSet`, `Add/Remove/UpdateDVSetElements`, `GetDVSetElements`, `GetActiveDVSetElements`, `GetActiveDataVisualizations` (parameter structs, `std::vector<TXString>`)
    - Low-detail flags: `GetDocumentLowDetailFlags`, `GetViewportLowDetailFlags` (`SLowDetailFlags`)
    - Saved settings: `GetSavedSettingN`, `DeleteSavedSettingN` (`ESavedSettingsFile`)
    - Meshes: `RepairMesh`, `GetSelectedFacetMeshesUnderMouse`
    - Other: `ShowAlert` (modal, refuse it), `SetText`, `SetControlTextColor`, `SetHotSpotStyle`, `CreateMaterialPreview`, `PreviewSetMatrix`
  - The phase methods are the most useful to add. Adding a `std::vector<TXString>` ⇄ JSON-array rule alone would unlock most of the data-visualization set.
- **Generator gotcha:** 2027 also adds `ImportImageFile(const TXString&, const WorldPt&)` and declares it **without** `VCOM_CALLTYPE` (`ISDK.h:4114` in 2027). A parser that requires `VCOM_CALLTYPE` will miss it. The new generator should accept both forms.

**How to regenerate for 2027**

Write `tools/gen_isdk_dispatch.py` from scratch and commit it:
1. Parse the `class DYNAMIC_ATTRIBUTE ISDK : public IVWSingletonUnknown` body in `SDK2027/SDKLib/Include/Interfaces/VectorWorks/ISDK.h`:
   - Strip comments.
   - Match `virtual <ret> [VCOM_CALLTYPE] <Name>(<params>) = 0;`.
   - Keep default arguments, so that trailing defaulted parameters can be optional in JSON.
2. Apply the marshalling rules above. Add the new rules:
   - a null check for every handle parameter
   - `std::vector<TXString>` as a JSON array
   - phase structs, optionally
3. Pick one overload per name deterministically, or name the extra overloads `Name#2`.
4. Emit only the shim table into `IsdkDispatch.generated.inc`. Keep the marshal helpers and the handle registry in a hand-written header, so the generated file contains only generated code.
5. Join the result with an ISDK safety table (§2.4) and generate the refusal list from it, not from hand-edited prefixes.
6. Record the SDK path, the SDK version (`SDK_VERSION 3200` from `VectorworksSDK.h:54`) and the method count in the generated header, so a mismatch is visible.

The SDK headers are licensed by Vectorworks. The repo should ship the generator and its output, not a copy of `ISDK.h`. The generator should take the SDK path as an argument.

## 4. Recommended layout in vw-mcp

The scaffold ticket (#5) is not done yet, so adapt the top-level names to it. What matters is how the pieces split, not the exact names.

```
plugin/
  src/
    bridge/
      Jobs.{h,cpp}            deferred job queue, poll, busy predicates (modal check + registered hooks)
      ScriptRunner.{h,cpp}    RunScriptNow / BuildGuardedPython / guard report (from ExtSolotechSuite.cpp)
      Guards.h                ScriptDialogGuard, UndoEventScope
      DataFolder.{h,cpp}      Plug-ins/Data/vw-mcp/ (SWEEP_MODE marker, vs-safety-override.json)
    nativeops/
      NativeOps.{h,cpp}       RunNativeOps: the curated ops + call + clearHandles, FinishCreatedObject
      HandleRegistry.h        gHandleReg, ResolveHandle, J*/M* marshal helpers (hand-written)
      IsdkSafety.generated.inc  refusal classes for ISDK names (replaces IsBlockedIsdkCall)
      IsdkDispatch.generated.inc  shim table only, generated from the 2027 ISDK.h
    safety/
      VsSafety.generated.inc  carried over unchanged
tools/
  gen_isdk_dispatch.py        new generator (takes --sdk <path>)
relay/
  server.mjs                  run_native_op with a zod discriminated union per curated op
docs/
  native-ops.md               op reference (fields, units, return shape, undo behaviour)
  research/native-ops-split.md
test/
  native-ops/*.json           op fixtures for a live smoke test on a throwaway document
```

Stays in SolotechSuite:
- `VenueLibraryBuild.inc`, `SheetGenerator.inc`, `SheetGenDialog.inc`, `VwemsHost.inc`
- its own copies of `ScriptDialogGuard`, `UndoEventScope` and the deferred-timer code (vwems needs them)
- the Build Venue Library and Generate Sheets menu commands

The `venueBuildRequest`, `venueBuildStatus` and `generateSheets` MCP entry points go away when SolotechSuite drops its bridge (#10). That is acceptable because the relay never advertised them, and both features have menu commands. If MCP access is still wanted later, vw-mcp can add an op-registration hook: another plug-in registers op kinds through a VCOM interface. That should not block v1.

## Follow-ups for other tickets

- **#6 (port the bridge core):**
  - Port the generic ops only.
  - Fix the `clearLayer` undo bug.
  - Add the null-handle check.
  - Decide the busy hook for the venue build.
- **#5 (scaffold):** reserve `tools/gen_isdk_dispatch.py` and the `nativeops/` split.
- **#10 (remove the bridge from SolotechSuite):** keep `ScriptDialogGuard`, `UndoEventScope` and the deferred timer for vwems. Delete `IsdkDispatch.inc` and `RunNativeOps`.
- **New ticket (suggested):** an ISDK safety table and sweep for the `call` path, the native counterpart of the vs sweep.
