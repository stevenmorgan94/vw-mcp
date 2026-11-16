# vw-mcp hardening spec (Vectorworks 2027)

The goal: **no MCP call can crash Vectorworks or lose work.** This spec is the destination of the hardening map *Harden the VW MCP server against crashes* (settled 2026-11-13). That map and its tickets were tracked in the bridge's original, private repository before vw-mcp was split out, so the ticket titles below are not links. Terms are defined in [`GLOSSARY.md`](GLOSSARY.md).

The safety layer and the sweep harness stay **free of coupling to any one plug-in or product**.

**Status in this repo:** the safety layer (`safety/`), the sweep (`sweep/`) and the relay (`relay/`) were carried over unchanged apart from names and paths. The bridge itself (job runner, ctx engine, native ops) is being ported into the headless plug-in in [#6](https://github.com/stevenmorgan94/vw-mcp/issues/6); where this spec says "the bridge", it describes the behaviour that port must keep.

## 1. Execution model

From the ticket *Does any context make the known crashers safe?*

- Run Python with **`IPythonScriptEngine::ScriptContext_Begin(script, logger)` + `ScriptContext_RunEx(logger)`**, never `ExecuteScript`.
  - `ExecuteScript` is the cause of crashes C1–C8.
  - Under the ctx engine, `vs.Rect`, `vs.CreateWS`, `vs.BuildResourceList`, `vs.Layer` and 50× symbol `ResetObject` + `ReDrawAll` all ran cleanly, from the deferred timer and inline.
- Under the ctx engine a wrong-arity `vs.*` call returns an error (no modal), and the script carries on.
- No VW-dispatched context helps on its own:
  - Menu `DoInterface` via an in-process NSMenu: no help.
  - The idle-loop notification: no help.
  - `DoMenuName`: can't reach `AddSpecialMenuItem` items.
- Outside sweep mode, the bridge **always runs jobs deferred**.
- `lang: vectorscript` is **removed**: the safety layer can't see inside VectorScript.

## 2. Safety classification

From the ticket *What is the safety classification scheme?*

- Every `vs.*` function gets **one safety class**: the worst outcome with valid arguments, under the ctx engine.
- It also gets an independent **`argCheck` flag**: behaviour gets worse with bad arguments.
- Classes, worst first: **crasher > hang > interactive > document-level > safe**.
- A function with no entry is **unclassified**, and is refused unless the request sets `allowUnclassified: true`.
- Context (inline vs deferred) becomes part of an entry only if the sweep finds it changes the outcome.
- **Class table:**
  - A JSON file with no product branding, shipped with the plug-in, stamped with the VW build it was swept on.
  - Only the sweep's derive step writes it.
  - A local override file may be merged on top; overridden entries are marked in results.
- **After a VW update:** classes carry forward, bridge status warns about the build mismatch, and the regression suite runs the sweep again.
- **Enforcement:**
  - The **in-engine `vs` wrapper** is the authority. It catches aliases and `getattr`, and replaces `FindBlockedCall` and the hand-written stubs.
  - The relay may pre-check the script text for clearer errors.
- **Native ops are outside the table.** They are our own code and are tested individually.

## 3. Mitigation per class

From the ticket *What is the mitigation for each safety class?*

| Class | Bridge behaviour |
|---|---|
| crasher | Auto-**reroute** to the native op when there's an exact native match whose op passed its own tests; the result notes it. Otherwise **refuse**, naming any alternative. |
| hang | Refuse. |
| interactive | Always refuse. The bridge can't know whether a user is present. |
| document-level | Requires `allowDocumentLevel: true`. If the front doc is dirty, the bridge first makes a **native backup copy** to a backups folder. It never saves the user's file. |
| safe | Run. **Each job is one undo step** ("MCP: …"). |
| `argCheck` | Generic check before the call: arity, Python types against the signature, no `None`/`0` handles. On failure it raises a catchable `TypeError`. A per-function value rule is added only where the sweep shows an edge value is the problem case. |

**Cross-cutting**
- **Time budget:**
  - 30 s by default; the client may raise it up to 300 s.
  - When it runs out, a watchdog thread interrupts the Python (`PyThreadState_SetAsyncExc`).
  - If VW is stuck in C, the relay reports *"Vectorworks is unresponsive"*. VW is **never killed outside sweep mode**.
- **Refusals:**
  - A refused name visible in the script text refuses the **whole script before it runs**.
  - A refusal at runtime raises partway through; the undo step reverts the partial changes, and the refusal advises an undo.
- **Modal already open:** the job waits up to 10 s, then is refused with *"Vectorworks is busy (a dialog is open)"*.

## 4. Tool surface

From the ticket *What tool surface does the MCP expose?*

| Tool | Contract |
|---|---|
| `execute_script` | Python only, enforced by the class table. Per-call params: `allowDocumentLevel`, `allowUnclassified`, `timeoutSec` (30, max 300). No session-wide unsafe mode and no `defer` option. |
| `run_native_op` | Native SDK ops with a schema per op. `execute_script` with `lang: "ops"` stays as a deprecated alias for one release. |
| `vw_lookup_function` | Read-only. For a `vs.*` name: class, `argCheck`, signature, native alternative. |
| `vw_bridge_status` | Adds: engine, class-table build with mismatch warning, modal up, sweep mode, last refusal or unresponsive event. |

- **Refusal body:** `isError: true` with `{refused: true, function, class, reason, alternative, partialChanges, advice}`.
- **Branding:** no product branding in tools or messages. The MCP server id is `vw-mcp`.

## 5. Sweep harness

From the ticket *How should the sweep harness work?*

- **Where it lives:** Node, in `sweep/`, driving the **MCP endpoint**. The relaunch script (`vw-relaunch.sh`, from the ticket *Can VW relaunch after a crash with no human?*, about 3 min per crash) lives with it.
- **Scope:**
  - All 3,098 `vs.py` functions (inventory: the ticket *What is the full VW 2027 scripting surface?*; the result is `safety/functions.csv`), none skipped.
  - Risk tiers, in order: reads → mutating → resource/geometry creators → `opens_ui` / `file_io` / event-only → known crashers.
- **Jobs:**
  - One argument case per job.
  - Valid cases run inline **and** deferred; bad cases run deferred only.
  - The fixture doc is reset after any job that changed it, and otherwise every 50 jobs.
- **Argument cases (typed generators):**
  - Valid: REAL 1.0, INTEGER 1, BOOLEAN True, STRING "x", VECTOR (1,0,0), HANDLE via a category→fixture map (default: a rectangle).
  - Bad: arity ±1, wrong type for the first parameter, a `None` handle, and edge values (0, negative, huge, empty string).
- **Outcome detection:**

  | Outcome | Signal |
  |---|---|
  | crash | Process gone or palette disconnected; a new `.ips` report, symbolicated with `vs_symbolicate.py` |
  | hang | No result within 10 s; the harness kills VW and relaunches |
  | interactive | `IsModalWindowUp` plus the System Events window title; the harness presses Cancel/Esc |
  | document-level | Front doc changed, a doc opened or closed, files written to the sandbox, or prefs changed |
  | corruption | The fixed read-back check (object/layer/resource counts, then Save As to the sandbox) fails or crashes |

- **Sweep log and derive step:**
  - An append-only JSONL log: `started` before submit, `outcome` after. A `started` with no `outcome` blames that case.
  - A separate derive step builds the class table, assigning classes from observed outcomes only, never from heuristic flags.
  - Crashes and hangs are retried once at the end of the run; those that don't reproduce are marked `flaky`.
- **Sweep mode:**
  - Skips the wrapper's refusals but keeps the ctx engine.
  - Enabled only by a marker file in the plug-in data folder, never by a request.
  - A one-off setup job builds `fixture.vwx`: rect, symbol def + instance, worksheet, layer, class, sheet viewport, text.
  - A sweep-mode-only **native** op resets the doc by closing it without saving and reopening a copy.
- **Protecting the user's setup:**
  - Snapshot `~/Library/Application Support/Vectorworks/2027` (everything but plug-ins) before the run; restore it after the run and after every relaunch.
  - All file output goes to a sandbox folder.
- **Stop rules:**
  - 3 relaunch failures in a row
  - more than 5 crashes in a row
  - less than 10 GB free disk

  The run is wrapped in `caffeinate -dims`.

## 6. Handoff order

1. **Switch to the ctx engine** in `RunScriptNow`. Done and deployed on 2026-11-13 (in the original repo).
   - Verified live with a doc open: inline read ok; deferred `vs.Rect` ok, which crashed every time under `ExecuteScript`.
   - **Undo verified:** one ⌘Z removed the whole deferred job (object count 239 → 238, `LNewObj` empty). Multi-call jobs are still to check in the pilot.
   - Keep the old blocklist and stubs until the pilot confirms the switch.
   - **New finding — the no-document context:** an inline `vs.GetFName()` + `vs.Count("ALL")` sent while only the Home Screen was up crashed VW (`EXC_BAD_ACCESS` 0x1c7 inside a `vs.*` call under `RunScriptNow`; `Vectorworks-2026-11-13-152548.ips`). It is not yet known whether `ExecuteScript` crashes the same way.
   - Proposed mitigation: the bridge refuses scripting jobs while no document is open, with a native check before the engine runs. The harness always runs with the fixture doc open, and a later sweep tier can probe the no-document context deliberately.
2. Add sweep mode, the fixture builder and the native reset op.
3. Build the harness in `sweep/`.
4. Run a **daytime pilot** with the user nearby: tier 1 (about 300 functions). Also verify:
   - undo grouping of ctx-engine jobs;
   - ctx engine under a modal;
   - the watchdog interrupt;
   - the plug-in object (regen) context.
5. Run the first overnight sweep, then derive the class table.
6. Build the enforcement layer (in-engine wrapper, mitigations, tool surface) on the derived table. Then remove `FindBlockedCall` and the stubs.
   **Done and deployed on 2026-11-14.** The class table is `docs/sweep/class-table-v1.json`.
   - `safety/build_table.py` turns it into `safety/vs-safety-table.json` and generates `plugin/src/safety/VsSafety.generated.inc`.
   - **Guard:** `safety/vwguard.py` runs in the engine. It gives the job a guarded `vs` (also for `from vs import` and `getattr`) and refuses names in the script text before it runs.
   - **Checks:** class refusals; `argCheck` covers arity, Python type, null handle, and the handle's **object type** (plus the plug-in name for plug-in objects); Begin*/End* pairing (a stray End is refused, an open Begin is auto-closed); the `UprString` → `str.upper()` reroute; and the `timeoutSec` watchdog.
   - **Native, in the bridge:** the no-document refusal, VectorScript refused, every job deferred outside sweep mode (marker file `Plug-ins/Data/vw-mcp/SWEEP_MODE`), a 10 s busy wait, and a local override at `vs-safety-override.json`.
   - **Relay:** `execute_script` with `allowDocumentLevel` / `allowUnclassified` / `timeoutSec`, `run_native_op`, `vw_lookup_function`, the status fields, and the refusal body.
   - `FindBlockedCall` and the stubs are removed. The ISDK check on native ops stays.
   - **Build-mismatch warning: done (2026-11-16).** The bridge answers a read-only `execute_script({info: true})` with the running build (`CFBundleShortVersionString`, e.g. `32.0.0 (882075)`), engine, guard version, sweep mode, document open and dialog-busy. `vw_bridge_status` shows these and sets `warning` when the build differs from the table's `vwBuild`.
   - **Backup copy for document-level jobs: deferred.** Only `Space_CreateSpace` and `ProgressDlgYield` are in that class, and both just open a window. The calls that really replace a document (`NewDoc`, `OpenDoc`, `Close`, `Save*`) are never run by the sweep and stay unclassified. The SDK's only save call, `SaveActiveDocumentPath`, is a Save As: it would retarget the user's document, which §3 forbids. Revisit if a document-replacing function ever lands in the class, with a save-a-copy route that leaves the active document untouched.
   - **Gap (closed by sweep v2, 2026-11-16):** v2 ran the 266 functions v0/v1 had skipped that are safe to run (core geometry, Begin/End point builders, `GetPref`/`SetPref`, the old tier-5 list); all core ones are `safe`. 549 dialog-builder and plug-in-event functions are classified by category (`interactive` / `event-only`, `basis: category`) without running. **271 stay unclassified on purpose:** file I/O, Excel, ODBC, XML, import/export, PDF, printing and workspaces, which act outside the document. See [sweep/README.md](sweep/README.md).
   - The sweep's inline context is gone: the relay always defers. v0 never found a context difference.

Follow-on work, not blocking: dispatch the 70 ISDK methods new in 2027 and the 137 cheap native additions. Each new native op widens what crashers can be rerouted to.

## Out of scope

- Vectorworks 2026 and older.
