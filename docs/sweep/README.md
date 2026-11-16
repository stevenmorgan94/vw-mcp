# Sweep results (VW 2027 32.0.0 b882075, ctx engine)

**Current table: `class-table-v2.json`** (v0 + v1 retest + v2). Lists: `sweep-v2-lists.txt`.

## v2 (2026-11-16): the functions v0/v1 never ran

`TAG=v2 zsh sweep/run-overnight.sh <backup> --v2`, 1,337 jobs (266 functions, valid + bad cases, guard off via SWEEP_MODE), about 1.5 h with 22 relaunches. Then `derive.py run-v2.jsonl class-table-v2.json --base class-table-v1.json` and `safety/build_table.py`.

**Harness changes:**
- **Python-driven arguments:** Python folds `pX, pY(, pZ)` into one point tuple, `colorR, G, B` into one color tuple and `x1, y1, …` into point varargs. v0 matched VectorScript params one-to-one, so 120 functions (`Arc`, `Oval`, `AddPoint`, `Wall`, `Symbol`, `FillBack`…) had no valid case. Successive points differ, so no zero-size shapes.
- **More typed fixtures:** a second wall, a polygon, a line and a 3D polygon (`JoinWalls`, `SetPolylineVertex`, `SetSegPt1/2`, `AddVertex3D`…); roof for `AppendRoofEdge`/`SetRoofEdge`, light for `SetLightLocation`.
- **Paired cases** run alongside the unpaired call: `BeginSym`, `BeginRoof…EndGroup`, `AddPoint`/`ArcTo`/`CurveTo`/`CurveThrough`/`Add2DVertex` inside `BeginPoly…EndPoly`, `Add3DPt` inside `BeginPoly3D…EndPoly3D`.
- **Not run on purpose:** dialogs, user input, plug-in object/tool events, workspaces, file I/O, Excel, ODBC, XML, import/export, PDF, QuickTime, printing, URLs, Python path changes.

**Results (266 functions):** safe 244 (argCheck 21), interactive 16, crasher 4, hang 1, document-level 1.
- **Every core function is safe:** `Rect`, `Layer`, `BeginSym`, `Arc`, `Oval`, `Poly`, `Wall`, `Symbol`, `AddPoint`/`ArcTo` (paired and unpaired), `NameObject`, `CreateWS`, `BuildResourceList*` (incl. `BuildResourceListN2`, which the old blocklist refused), `GetPref*`/`SetPref*`. The old C1–C8 crashes were the ExecuteScript entry point, not these functions.
- **New crashers:** `AddVectorFillLayer`, and three dialog openers that crash instead of showing: `DisplayContextHelpOfCurrentPlugin`, `DisplayLayerScaleDialog`, `DisplayOrganizationDialog`.
- **Hang:** `RetrieveOpenGLPrefs`.
- **Interactive (16):** mostly `Edit*`/`Run*`/`Show*` dialogs. Also `SetRoofEdge`: the test's edge values produced "Roof pitch is not valid" alerts. It's probably safe with valid geometry, but an alert blocks the bridge, so it stays refused.
- **Document-level:** `ProgressDlgYield` (opened a progress window that wouldn't close).
- **Bad arguments that crash:** `DelSavedSettings` (arity −1), `EditProperties` (arity −1), `EditOpenGLPrefs`/`EditRenderWorksPrefs`/`RunNewColorPalette` (arity +1), `LDevice_SetAccPos2D/3D` (wrong type), `EditCriteriaWithUI` (empty string), `ShowGradientEditorDialog` (None handle).

**Classified by category, not run (`basis: category`):** 409 dialog-builder / user-input functions → `interactive`; 140 plug-in object/tool event functions → `event-only` (new class: only valid inside an event handler).

**Still unclassified (271):** file I/O 43, Excel 32, workspaces 28, ODBC 26, XML 31, import/export 19, PDF 17, QuickTime 12, IFC 10, and a few more. Refused unless `allowUnclassified`.

**Table now:** 2,827 entries: safe 2,247, interactive 425, event-only 140, crasher 11, hang 2, document-level 2; 71 with arg specs.

## v1 retest (2026-11-14): typed fixtures

`node sweep/sweep.mjs --retest`, 149 jobs, then `derive.py <v0 log> <out> <retest log>`.

| Class | v0 | v1 |
|---|---|---|
| safe | 1,972 (argCheck 35) | 2,003 (argCheck 66) |
| crasher | 38 | 7 |
| interactive / hang / document-level / refused | 15 / 1 / 1 / 1 | unchanged |

**What it ran:**
- **Typed:** each v0 crasher and each handle-taking argCheck function, called with a handle of the right object type. The fixtures are:
  - a gradient;
  - a Lighting Device, a light and a Circuit;
  - a roof and a wall;
  - a Title Block Border;
  - a viewport on a sheet layer, and the sheet layer itself.
- **In-out args:** v0 dropped `VAR` parameters that Python also takes as input (`segmentIndex`, `str`, …), so 16 functions were only ever called with too few arguments. The harness is fixed, and the 13 that had only raised a TypeError were re-run.
- **Paired:** `BeginPoly…EndPoly` and `BeginSym…EndSym` used properly.
- **Repro:** 10 v0 crash cases re-run with v0's exact code.

**Findings:**
- **The wrong object type is the dominant crash cause.** These 31 functions are safe with the right object and crash with a rectangle: the gradient, `LDevice_*`, light, roof, viewport-override and wall families, plus `ApplyLightInfoRecord` and `OLDGetHangingPos`. They are now `safe` + `argCheck`, with bad case `wrong-object-type:crash`. **The argument check must compare each handle's object type** (GetTypeN, plus the plug-in name for PIOs) against what the function expects. A null-handle check is not enough.
- **Crashes are deterministic.** All 10 repro cases crashed again, the same way.
- **`BeginPoly` / `EndSym` are safe when paired** and crash when unpaired. Mitigation: a whole-script pairing check (Begin*/End* balanced), not a per-call check.
- **Remaining crashers (7):**
  - `UprString`: crashes with a string (v1) and with an int (v0). Python strings are immutable, so the in-out `str` parameter is probably the cause. Reroute it to Python's `str.upper()`.
  - `TBB_AttachRecords()`: takes no input; crashed in v0 and again in v1.
  - `CC_GetCircuitSource` / `CC_GetCircuitDest`: crash even on a real (unconnected) Circuit. Retesting needs a circuit connected to devices.
  - `Plant_ReplacePlantParam`, `SetConstraintValue`, `SetTexSpaceEndCap`: not retested. Plant isn't installed, and there is no simple way to create a constraint or texture-space fixture.
- **The 13 in-out functions are all safe** with the right arity, apart from `UprString`.

**Caveats:**
- The retest's inline jobs were all refused by the old text blocklist, because the new fixture prelude uses creator calls. The results above are deferred only. v0 never found a context difference.
- The `wrong-object-type` bad case uses a rectangle. Other wrong types weren't tried.

---

## v0 (2026-11-13/14)

The first overnight run of `sweep/sweep.mjs`. See [the hardening spec](../MCP_HARDENING_SPEC.md) §5.

**Scope:**
- 2,028 functions in tiers 1–3: reads, mutating calls, and resource/geometry creators.
- Valid case run deferred, plus inline for reads; bad-argument cases deferred only.
- 11,016 jobs.
- **Not covered:** tier 4 (dialogs, file I/O, events, workspaces: 940 functions), tier 5 (known crashers: 11), and 119 functions with no valid-case generator.
- The old blocklist and stubs were **on**: the `refused` result is the blocklist.

| Class | Functions |
|---|---|
| safe | 1,972 (35 of them crash only on bad arguments, so they need `argCheck`) |
| crasher | 38 |
| interactive | 15 |
| hang | 1 (`RefreshResManager`) |
| document-level | 1 (`Space_CreateSpace`, which opens a window) |
| refused | 1 (`BuildResourceListN2`) |

The full lists are in `sweep-v0-lists.txt`; the per-function table is in `class-table-v0.json`.

## Findings

- **Context never mattered.** No function behaved differently inline and deferred under the ctx engine. That supports "context only if it matters".
- **Most crashers get a handle of the wrong object type.** The harness passes a rectangle wherever a function wants a handle:
  - the gradient family (`Get/Set/Insert/RemoveGradient*`);
  - `LDevice_*` (lighting device);
  - `SetLightDirection` / `SetSpreadAngle` (light);
  - `SetRoofAttributes`, `CC_*` (ConnectCAD), `TBB_AttachRecords`, `ApplyLightInfoRecord`.

  These are probably safe with the right object. That points to an **object-type check on handle arguments** as the main mitigation, not refusing the functions outright. Testing this needs more fixtures (a gradient, a lighting device, a light, a roof, a circuit) in a later run.
- **Some crashers are state-machine calls:** `BeginPoly` and `EndSym` (an `EndSym` with no `BeginSym`). These need sequence rules, not an argument check.
- **Wrong-arity calls can still crash under the ctx engine.** `Ord`, `TrueTypeToPoly`, `CallToolByName` and `HasConstraint` crashed with one argument too few; `UprString` with one too many. This corrects the probe's "wrong arity just errors" finding: the generic arity check in the spec is **required**, not optional.
- **Interactive** calls open alerts even with valid arguments, for example `GetProduct` ("obsolete as of Vectorworks 10") and `RunImageComp` (an image-size alert). The harness clicked the dialog's only button or Cancel.

## Caveats

- **No flaky re-run yet.** The spec's end-of-run retry of every crash and hang wasn't done, so some crashes may be state left over from the previous job. `EndSym`, `BeginPoly` and `WallPeak` are the likeliest.
- **`dialogAfter` entries** (the dialog was noticed by the *next* job) are attributed to the previous function. `WallPeak` and `Record` may be wrong attributions.
- **The harness needed four fixes during the night:** reconnecting after a crash, untitled dialogs, single-button alerts, and skipping the extra cases of known crashers. Passes 1–4 are in the same log; the derived table uses each job's final outcome.
