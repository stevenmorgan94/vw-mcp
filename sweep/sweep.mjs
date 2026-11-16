// Sweep harness v0 — classify vs.* functions by calling each one through the MCP endpoint.
// See docs/MCP_HARDENING_SPEC.md §5. v0 limits: tiers 1-3 only, valid argument case only,
// no sweep mode (the bridge's blocklist/stubs still refuse known crashers).
//
//   node sweep/sweep.mjs [--limit N] [--dry] [--tiers 1,2,3] [--log path]
//
// Log: append-only JSONL. {"ev":"started",key,...} is written BEFORE a job is sent and
// {"ev":"outcome",key,...} after. A started with no outcome = that job killed VW or hung it.
import fs from 'node:fs';
import path from 'node:path';
import { execFileSync, spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { Client } from '../relay/node_modules/@modelcontextprotocol/sdk/dist/esm/client/index.js';
import { StreamableHTTPClientTransport } from '../relay/node_modules/@modelcontextprotocol/sdk/dist/esm/client/streamableHttp.js';

const HERE = path.dirname(fileURLToPath(import.meta.url));
const args = process.argv.slice(2);
const opt = (k, d) => { const i = args.indexOf(k); return i < 0 ? d : args[i + 1]; };
const LIMIT = Number(opt('--limit', 1e9));
const DRY = args.includes('--dry');
const V2 = args.includes('--v2');
const TIERS = opt('--tiers', '1,2,3').split(',').map(Number);
const LOG = opt('--log', path.join(HERE, 'results', 'run-v0.jsonl'));
const RELAUNCH = path.join(HERE, 'vw-relaunch.sh');
const MCP_URL = 'http://127.0.0.1:9101/mcp';
const MODAL_CHECK_MS = 10000;   // no result after this -> look for a modal
const HANG_MS = 40000;          // no result after this (incl. modal handling) -> hang
const RECYCLE_EVERY = 1000;     // fresh VW + doc every N jobs
const MIN_FREE_GB = 10;

const log = (...a) => console.log(new Date().toTimeString().slice(0, 8), ...a);

// ---------- inventory ----------
function parseCSV(text) {
  const rows = []; let row = [], f = '', q = false;
  for (let i = 0; i < text.length; i++) {
    const c = text[i];
    if (q) { if (c === '"') { if (text[i + 1] === '"') { f += '"'; i++; } else q = false; } else f += c; }
    else if (c === '"') q = true;
    else if (c === ',') { row.push(f); f = ''; }
    else if (c === '\n') { row.push(f); rows.push(row); row = []; f = ''; }
    else if (c !== '\r') f += c;
  }
  if (f || row.length) { row.push(f); rows.push(row); }
  const [h, ...rest] = rows;
  return rest.filter((r) => r.length === h.length).map((r) => Object.fromEntries(h.map((k, i) => [k, r[i]])));
}

const SKIP_CATEGORY = /^(Dialogs|User Interactive|Workspaces|File I\/O|Excel|ODBC|XML|ImportExport|PDF|Object Events|Tool Events)/;
const SKIP_NAME = /Quit|Close|NewDoc|OpenDoc|Open[A-Z]|Save|Revert|Import|Export|Print|Delete.*File|Pref|DoMenu|DoProgram|RunScript|PythonExecute|Execute|Dialog|Dlog|Alert|Ask|Wait|Sleep|Beep|Message|Launch|Browser|URL|Prompt|Interactive|Get(Pt|Line|Rect|Key|Mouse)|TrackObject|Callback/;

// v2: never run these (side effects outside the throwaway document, or need a dialog / event / user input).
const V2_SKIP_CATEGORY = /^(Dialogs|User Interactive|Workspaces|Object Events|Tool Events|File I\/O|Excel|ODBC|XML|ImportExport|PDF|Special - QuickTime)/;
const V2_SKIP_NAME = /Print|OpenURL|Launch|DoProgram|Python(Execute|SetSearchPath|GetSearchPath)|InstallScriptAddPath|Quit|VSave|SaveSheet|Export|Import|PDFDocument|DoMenuText|^IFC_|SetCheckoutsComment|Revert|NewDoc|OpenDoc|^Close$|^ws|PickObject$|RunTempTool/;
const v2Runnable = (f) => f.file_io !== '1' && !f.event_context && !V2_SKIP_CATEGORY.test(f.category) && !V2_SKIP_NAME.test(f.name);

function tierOf(f) {
  if (f.in_vs_py !== '1' || f.kind === 'CONSTANT') return 0;
  if (f.opens_ui === '1' || f.file_io === '1' || f.event_context) return 4;
  if (/crash|blocked/.test(f.bridge_history)) return 5;
  if (SKIP_CATEGORY.test(f.category) || SKIP_NAME.test(f.name)) return 4;
  if (f.creates_geometry === '1' || f.creates_resource === '1') return 3;
  if (f.mutates_doc === '1') return 2;
  return 1;
}

// VS param list "a:REAL; VAR b:HANDLE; c,d:INTEGER" -> [{name,type,isVar}]
function vsParams(sig) {
  const m = sig.match(/\((.*)\)/); if (!m) return [];
  const out = [];
  for (const grp of m[1].split(';')) {
    const [names, type] = grp.split(':'); if (!type) continue;
    const isVar = /^\s*VAR\s/i.test(names);
    for (const n of names.replace(/^\s*VAR\s+/i, '').split(',')) out.push({ name: n.trim(), type: type.trim().toUpperCase(), isVar });
  }
  return out;
}
function pyArgNames(sig) {
  const m = sig.match(/vs\.\w+\((.*)\)\s*$/); if (!m) return null;
  return m[1].trim() ? m[1].split(',').map((s) => s.trim()) : [];
}

// --retest: typed fixtures. fn-name regex -> expression per HANDLE param (in order). See docs/sweep/README.md.
const TYPED = [
  [/Gradient/, ['_fx_grad()']],
  [/^LDevice_AddAccessory$/, ['_fx_ldev()', "vs.GetObject('FX_SYM')"]],
  [/^(LDevice_|OLDGetHangingPos$)/, ['_fx_ldev()']],
  [/^ApplyLightInfoRecord$/, ["vs.GetObject('FX_SYM')", '_fx_ldev()']],
  [/^CC_GetCircuit/, ['_fx_circuit()']],
  [/^(SetLightDirection|SetSpreadAngle)$/, ['_fx_light()']],
  [/(RoofAttributes|^AppendRoofEdge|^SetRoofEdge)$/, ['_fx_roof()']],
  [/^SetLightLocation$/, ['_fx_light()']],
  [/^JoinWalls$/, ['_fx_wall()', '_fx_wall2()']],
  [/^(SetPolylineVertex|PtInPoly|Split2DObjectByLine|Create2DObjShadow)$/, ['_fx_poly()']],
  [/^(SetSegPt1|SetSegPt2)$/, ['_fx_line()']],
  [/^(AddVertex3D|SetPolyPt3D)$/, ['_fx_poly3d()']],
  [/^TBB_AttachRecords$/, ['_fx_tbb()']],
  [/^(GetWallThickness|GetComponents|GetDisplayWith2DComp|SetDisplayWith2DComp)$/, ['_fx_wall()']],
  [/VPLrOvrd/, ['_fx_vp()', '_layer()']],
  [/SheetLayerUserOrigin$/, ['_fx_sheet()']],
];
const typedFor = (fn) => TYPED.find(([re]) => re.test(fn))?.[1] ?? null;
function handleExpr(pname, category) {
  const n = pname.toLowerCase();
  if (/layer/.test(n) || category === 'Layers') return '_layer()';
  if (/class/.test(n)) return "vs.GetObject('FX_CLASS')";
  if (/symdef|symboldef|def/.test(n)) return "vs.GetObject('FX_SYM')";
  if (/sym/.test(n) || category === 'Objects - Symbols') return "vs.GetObject('FX_SYMINST')";
  if (/text/.test(n) || category === 'Objects - Text') return "vs.GetObject('FX_TEXT')";
  return "vs.GetObject('FX_RECT')";
}
function validArg(p, category) {
  const t = p.type;
  // v2: Python arguments that stand for several VectorScript params (see pyParams)
  if (t === 'POINT2') { ptN++; return `(${ptN * 100}.0, ${ptN * 50}.0)`; }   // distinct points: no zero-size shapes
  if (t === 'POINT3') return '(1.0, 1.0, 0.0)';
  if (t === 'COLOR') return '(0, 0, 0)';
  if (t === 'POLYPTS') return '(0.0, 0.0), (100.0, 0.0), (100.0, 100.0)';
  if (t === 'STRLIST') return "'a', 'b'";
  if (/TEXTSTYLE/.test(t)) return '0';
  if (/^ARRAY/.test(t)) return "['x']";
  if (/HANDLE/.test(t)) return handleExpr(p.name, category);
  if (/BOOL/.test(t)) return 'True';
  if (/REAL|DISTANCE/.test(t)) return '1.0';
  if (/INT|LONG|LNG/.test(t)) return '1';
  if (/STRING|STR|CHAR/.test(t)) return "'x'";
  if (/VECTOR/.test(t)) return '(1.0, 0.0, 0.0)';
  if (/CRITERIA/.test(t)) return "\"((N='FX_RECT'))\"";
  if (/PROCEDURE/.test(t)) return '(lambda *a: None)';
  if (/GLOBPT/.test(t)) return '(0.0, 0.0)';
  return null;   // ARRAY / ANY / unknown: can't build a valid case
}

// Fixtures: created on demand at the top of every job, so a job that deleted one doesn't poison the next.
const PRELUDE = `import vs
def _ensure():
    if not vs.GetObject('FX_RECT'):
        vs.Rect(0, 0, 100, 50); vs.SetName(vs.LNewObj(), 'FX_RECT')
    if not vs.GetObject('FX_TEXT'):
        vs.TextOrigin(0, 200); vs.CreateText('fx'); vs.SetName(vs.LNewObj(), 'FX_TEXT')
    if not vs.GetObject('FX_SYM'):
        vs.BeginSym('FX_SYM'); vs.Rect(0, 0, 10, 10); vs.EndSym()
    if not vs.GetObject('FX_SYMINST'):
        vs.Symbol('FX_SYM', (300, 0), 0); vs.SetName(vs.LNewObj(), 'FX_SYMINST')
    if not vs.GetObject('FX_CLASS'):
        _c = vs.ActiveClass(); vs.NameClass('FX_CLASS'); vs.NameClass(_c)
def _layer():
    return vs.ActLayer()
def _named(name, make):
    h = vs.GetObject(name)
    if not h:
        h = make()
        if h: vs.SetName(h, name)
    return h
def _fx_wall2():
    def mk():
        vs.Wall((500, -5000), (500, -5500)); return vs.LNewObj()
    return _named('FX_WALL2', mk)
def _fx_poly():
    def mk():
        vs.Poly((0, -9000), (100, -9000), (100, -8900)); return vs.LNewObj()
    return _named('FX_POLY', mk)
def _fx_line():
    def mk():
        vs.MoveTo(0, -9500); vs.LineTo(100, -9500); return vs.LNewObj()
    return _named('FX_LINE', mk)
def _fx_poly3d():
    def mk():
        vs.Poly3D((0, -9800, 0), (100, -9800, 0), (100, -9700, 10)); return vs.LNewObj()
    return _named('FX_POLY3D', mk)
def _fx_grad():
    return vs.GetObject('FX_GRAD') or vs.CreateGradient('FX_GRAD')
def _fx_light():
    return _named('FX_LIGHT', lambda: vs.CreateLight(0, -1000, 100, 2, True, False))
def _fx_pio(name, kind, y):
    return _named(name, lambda: vs.CreateCustomObjectN(kind, (0, y), 0, False))
def _fx_ldev():
    return _fx_pio('FX_LDEV', 'Lighting Device', -2000)
def _fx_circuit():
    return _fx_pio('FX_CIRCUIT', 'Circuit', -3000)
def _fx_tbb():
    return _fx_pio('FX_TBB', 'Title Block Border', -4000)
def _fx_wall():
    def mk():
        vs.Wall((0, -5000), (500, -5000)); return vs.LNewObj()
    return _named('FX_WALL', mk)
def _fx_roof():
    def mk():
        r = vs.CreateRoof(True, 0, 10, 1, 5)
        for p in [(0, -7000), (500, -7000), (500, -6500), (0, -6500)]: vs.AppendRoofEdge(r, p, 30, 0, 0)
        vs.ResetObject(r); return r
    return _named('FX_ROOF', mk)
def _fx_sheet():
    return vs.GetObject('FX_SHEET') or vs.CreateLayer('FX_SHEET', 2)
def _fx_vp():
    def mk():
        _a = vs.GetLName(vs.ActLayer()); v = vs.CreateVP(_fx_sheet()); vs.Layer(_a); return v
    return _named('FX_VP', mk)
`;

// v2: map each Python argument to the VectorScript param(s) it stands for. Python folds pX,pY(,pZ) into one
// point tuple, colorR,G,B into one color tuple, and x1,y1,...,xn,yn into point varargs.
function pyParams(f, py) {
  const vp = vsParams(f.vectorscript_signature); const by = Object.fromEntries(vp.map((p) => [p.name, p]));
  const used = new Set(); const out = [];
  for (const a of py) {
    if (by[a] && !used.has(a)) { used.add(a); out.push(by[a]); continue; }
    if (by[a + 'X'] || by[a + 'DX']) { out.push({ name: a, type: by[a + 'Z'] || by[a + 'DZ'] ? 'POINT3' : 'POINT2' }); continue; }
    if (by[a + 'R']) { out.push({ name: a, type: 'COLOR' }); continue; }
    if (/^(x1|p)$/.test(a) && /x1\s*,\s*y1/.test(f.vectorscript_signature)) { out.push({ name: a, type: 'POLYPTS' }); continue; }
    if (/str1\s*,/.test(f.vectorscript_signature)) { out.push({ name: a, type: 'STRLIST' }); continue; }
    return null;
  }
  return out;
}

let ptN = 0;
function buildCase(f, typed = null) {
  ptN = 0;
  const py = pyArgNames(f.python_signature);
  // VAR params are outputs, except in-out ones that Python also takes as arguments (e.g. SetGradientData's segmentIndex).
  let params = vsParams(f.vectorscript_signature).filter((p) => !p.isVar || (py && py.includes(p.name)));
  if (py && py.length !== params.length && V2) params = pyParams(f, py) ?? params;
  if (py && py.length < params.length) return { skip: `arity mismatch py ${py.length} vs ${params.length}` };
  const exprs = []; let hn = 0;
  for (const p of params) {
    let e = validArg(p, f.category);
    if (typed && /HANDLE/.test(p.type) && typed[hn] !== undefined) e = typed[hn++];
    if (e == null) return { skip: `no valid arg for ${p.type}` }; exprs.push(e);
  }
  const mk = (ex) => PRELUDE + (ex.some((e) => /FX_|_fx_/.test(e)) ? '_ensure()\n' : '') +
    `_r = vs.${f.name}(${ex.join(', ')})\nprint('RESULT', repr(_r)[:200])\n`;
  // Bad argument cases (spec §5): arity -1/+1, wrong type for the first param, None handle, edge values.
  const bad = {};
  if (exprs.length) bad['arity-1'] = exprs.slice(0, -1);
  bad['arity+1'] = [...exprs, '1'];
  if (exprs.length) {
    const t = params[0].type;
    bad['wrong-type'] = [/STR|CHAR/.test(t) ? '1' : "'x'", ...exprs.slice(1)];
    if (/REAL|INT|LONG|LNG|DISTANCE/.test(t)) { bad['edge-zero'] = ['0', ...exprs.slice(1)]; bad['edge-neg'] = ['-1', ...exprs.slice(1)]; bad['edge-huge'] = ['1e12', ...exprs.slice(1)]; }
    if (/STR|CHAR/.test(t)) bad['edge-empty'] = ["''", ...exprs.slice(1)];
  }
  const hi = params.findIndex((p) => /HANDLE/.test(p.type));
  if (hi >= 0) { const ex = [...exprs]; ex[hi] = 'None'; bad['none-handle'] = ex; }
  return { code: mk(exprs), bad: Object.fromEntries(Object.entries(bad).map(([k, ex]) => [k, mk(ex)])) };
}

// ---------- environment ----------
function extraWindows(wins, base) {
  const left = [...base]; const extra = [];
  for (const w of wins) { const i = left.indexOf(w); if (i >= 0) left.splice(i, 1); else extra.push(w || '(untitled window)'); }
  return extra;
}
function vwAlive() { return spawnSync('pgrep', ['-x', 'Vectorworks']).status === 0; }
function vwWindows() {
  try {
    const out = execFileSync('osascript', ['-e',
      'tell application "System Events" to if exists process "Vectorworks" then tell process "Vectorworks" to get name of every window'],
      { timeout: 8000 }).toString().trim();
    return out ? out.split(', ') : [];
  } catch { return null; }
}
function dismissModal() {
  // Cancel if there is one. A dialog with exactly ONE button is an alert: click it (acknowledging is safe).
  // Never click OK on a multi-button dialog. Otherwise Escape. Returns what it did plus the dialog text.
  const script = `tell application "System Events" to tell process "Vectorworks"
    set acted to ""
    repeat with w in windows
      try
        if subrole of w is "AXDialog" then
          set txt to ""
          try
            set AppleScript's text item delimiters to " / "
            set txt to (value of every static text of w) as text
          end try
          set bs to every button of w
          if exists button "Cancel" of w then
            click button "Cancel" of w
            set acted to acted & "cancel[" & txt & "] "
          else if (count of bs) is 1 then
            set bn to name of item 1 of bs
            click item 1 of bs
            set acted to acted & "only-button:" & bn & "[" & txt & "] "
          end if
        end if
      end try
    end repeat
    if acted is "" then
      key code 53
      set acted to "escape"
    end if
    return acted
  end tell`;
  try { return execFileSync('osascript', ['-e', script], { timeout: 8000 }).toString().trim().slice(0, 500); } catch (e) { return 'dismiss-failed'; }
}
function newestIps(sinceMs) {
  const dir = path.join(process.env.HOME, 'Library/Logs/DiagnosticReports');
  try {
    return fs.readdirSync(dir).filter((f) => f.startsWith('Vectorworks') && f.endsWith('.ips'))
      .map((f) => ({ f, t: fs.statSync(path.join(dir, f)).mtimeMs })).filter((x) => x.t >= sinceMs - 2000)
      .sort((a, b) => b.t - a.t)[0]?.f ?? null;
  } catch { return null; }
}
function freeGB() {
  const out = execFileSync('df', ['-k', process.env.HOME]).toString().trim().split('\n').pop().split(/\s+/);
  return Number(out[3]) / 1024 / 1024;
}
function relaunch() {
  log('relaunching VW');
  const r = spawnSync('zsh', [RELAUNCH], { timeout: 480000, encoding: 'utf8' });
  log((r.stdout || '').trim().split('\n').slice(-2).join(' | '));
  return r.status === 0;
}

// ---------- MCP ----------
let client = null;
async function mcp() {
  if (client) return client;
  const c = new Client({ name: 'vw-sweep', version: '0.0.1' });
  await c.connect(new StreamableHTTPClientTransport(new URL(MCP_URL)));
  client = c;
  return client;
}
async function waitBridge(ms = 90000) {
  const end = Date.now() + ms;
  while (Date.now() < end) {
    const h = await fetch('http://127.0.0.1:9101/health').then((r) => r.json()).catch(() => ({}));
    if (h.paletteConnected) { try { await mcp(); return true; } catch { await dropClient(); } }
    await new Promise((r) => setTimeout(r, 2000));
  }
  return false;
}
const BRIDGE_DOWN = /Not connected|fetch failed|ECONNREFUSED|not connected|socket/i;
async function dropClient() { try { await client?.close(); } catch {} client = null; }
async function callScript(code, defer) {
  const c = await mcp();
  const r = await c.callTool({ name: 'execute_script', arguments: { code, defer } }, undefined, { timeout: HANG_MS + 30000 });
  const text = r.content?.map((x) => x.text).join('\n') ?? '';
  let j = null; try { j = JSON.parse(text); } catch {}
  return { isError: !!r.isError, text, j };
}

// ---------- main ----------
const fns = parseCSV(fs.readFileSync(path.join(HERE, '../safety/functions.csv'), 'utf8'));
const jobs = []; const badJobs = [];
const skipped = { 0: 0, 4: 0, 5: 0, nocase: 0 };
if (args.includes('--retest')) {
  // Sweep v0 follow-up: typed fixtures for the crashers, paired state-machine calls, and repro of v0 crashes.
  const byName = Object.fromEntries(fns.map((f) => [f.name, f]));
  const TYPED_FNS = fns.filter((f) => typedFor(f.name) && tierOf(f) >= 1 && tierOf(f) <= 3);
  for (const f of TYPED_FNS) {
    const c = buildCase(f, typedFor(f.name)); if (c.skip) { log(`retest skip ${f.name}: ${c.skip}`); continue; }
    for (const ctx of ['deferred', 'inline']) jobs.push({ key: `${f.name}|typed|${ctx}`, fn: f.name, tier: tierOf(f), ctx, case: 'typed', code: c.code });
  }
  // v0 dropped in-out VAR params, so these were only ever called with too few args. Re-run them with the right arity.
  for (const f of fns) {
    const py = pyArgNames(f.python_signature); const t = tierOf(f);
    if (!py || t < 1 || t > 3 || typedFor(f.name)) continue;
    if (!vsParams(f.vectorscript_signature).some((p) => p.isVar && py.includes(p.name))) continue;
    const c = buildCase(f); if (c.skip) { log(`retest skip ${f.name}: ${c.skip}`); continue; }
    jobs.push({ key: `${f.name}|inout-fixed|deferred`, fn: f.name, tier: t, ctx: 'deferred', case: 'inout-fixed', code: c.code });
  }
  const paired = {
    BeginPoly: "vs.BeginPoly(); vs.AddPoint(0, 0); vs.AddPoint(100, 0); vs.AddPoint(100, 100); vs.EndPoly()\nprint('RESULT', vs.GetTypeN(vs.LNewObj()))\n",
    EndSym: "vs.BeginSym('FX_PAIRSYM'); vs.Rect(0, 0, 10, 10); vs.EndSym()\nprint('RESULT', bool(vs.GetObject('FX_PAIRSYM')))\n",
  };
  for (const [fn, body] of Object.entries(paired)) for (const ctx of ['deferred', 'inline']) jobs.push({ key: `${fn}|paired|${ctx}`, fn, tier: 3, ctx, case: 'paired', code: PRELUDE + body });
  // Repro: v0 crash cases run again (deferred), to tell deterministic crashes from flaky ones.
  const REPRO = [['GetNumGradientSegments', 'valid'], ['LDevice_GetCellCount', 'valid'], ['SetLightDirection', 'valid'], ['CC_GetCircuitSource', 'valid'],
    ['SetRoofAttributes', 'valid'], ['TBB_AttachRecords', 'valid'], ['BeginPoly', 'valid'], ['EndSym', 'valid'], ['Ord', 'arity-1'], ['UprString', 'arity+1']];
  for (const [fn, k] of REPRO) {
    // Exact v0 code (v0 dropped in-out VAR params, so v0's "UprString arity+1" was really vs.UprString(1)).
    const V0 = { 'UprString|arity+1': PRELUDE + "_r = vs.UprString(1)\nprint('RESULT', repr(_r)[:200])\n" };
    const c = buildCase(byName[fn]); const code = V0[`${fn}|${k}`] ?? (k === 'valid' ? c.code : c.bad[k]);
    jobs.push({ key: `${fn}|repro-${k}|deferred`, fn, tier: tierOf(byName[fn]), ctx: 'deferred', case: `repro-${k}`, code });
  }
} else if (V2) {
  // Sweep v2: the functions v0/v1 never ran (unclassified in the safety table), minus the ones a sweep must
  // not run (dialogs, events, file I/O, printing, workspaces) - build_table.py classifies those by category.
  const table = JSON.parse(fs.readFileSync(path.join(HERE, '../safety/vs-safety-table.json'), 'utf8')).functions;
  const PAIRED = {
    BeginSym: "vs.BeginSym('FX_PAIRSYM2'); vs.Rect(0, 0, 10, 10); vs.EndSym()\nprint('RESULT', bool(vs.GetObject('FX_PAIRSYM2')))\n",
    BeginRoof: "vs.BeginRoof((0, 0), (100, 0), (0, 1), 1, 1, 1, 0); vs.AddPoint(0, 0); vs.AddPoint(100, 0); vs.AddPoint(100, 100); vs.AddPoint(0, 100); vs.EndGroup()\nprint('RESULT', vs.GetTypeN(vs.LNewObj()))\n",
    Add3DPt: "vs.BeginPoly3D(); vs.Add3DPt((0, 0, 0)); vs.Add3DPt((100, 0, 0)); vs.Add3DPt((100, 100, 0)); vs.EndPoly3D()\nprint('RESULT', vs.GetTypeN(vs.LNewObj()))\n",
  };
  for (const [fn, call] of [['AddPoint', 'vs.AddPoint(50, 50)'], ['ArcTo', 'vs.ArcTo(50, 50, 10)'], ['CurveTo', 'vs.CurveTo(50, 50)'],
    ['CurveThrough', 'vs.CurveThrough(50, 50)'], ['Add2DVertex', 'vs.Add2DVertex((50, 50), 1, 0)']])
    PAIRED[fn] = `vs.BeginPoly(); vs.AddPoint(0, 0); ${call}; vs.AddPoint(100, 100); vs.EndPoly()\nprint('RESULT', vs.GetTypeN(vs.LNewObj()))\n`;
  for (const f of fns) {
    if (f.in_vs_py !== '1' || f.kind === 'CONSTANT' || table[f.name] || !v2Runnable(f)) continue;
    const t = tierOf(f); const c = buildCase(f, typedFor(f.name));
    if (PAIRED[f.name]) jobs.push({ key: `${f.name}|paired|deferred`, fn: f.name, tier: t, ctx: 'deferred', case: 'paired', code: PRELUDE + PAIRED[f.name] });
    if (c.skip) { skipped.nocase++; log(`v2 no case ${f.name}: ${c.skip}`); continue; }
    jobs.push({ key: `${f.name}|valid|deferred`, fn: f.name, tier: t, ctx: 'deferred', code: c.code });
    if (!args.includes('--valid-only')) for (const [k, code] of Object.entries(c.bad)) badJobs.push({ key: `${f.name}|${k}|deferred`, fn: f.name, tier: t, ctx: 'deferred', case: k, code });
  }
} else for (const t of TIERS) for (const f of fns) {
  if (tierOf(f) !== t) continue;
  const c = buildCase(f);
  if (c.skip) { skipped.nocase++; continue; }
  for (const ctx of t === 1 ? ['deferred', 'inline'] : ['deferred']) jobs.push({ key: `${f.name}|valid|${ctx}`, fn: f.name, tier: t, ctx, code: c.code });
  if (!args.includes('--valid-only')) for (const [k, code] of Object.entries(c.bad)) badJobs.push({ key: `${f.name}|${k}|deferred`, fn: f.name, tier: t, ctx: 'deferred', case: k, code });
}
jobs.push(...badJobs);   // every valid case first, then the bad ones
for (const f of fns) { const t = tierOf(f); if (t in skipped && t !== 'nocase') skipped[t]++; }
log(`jobs ${jobs.length}; skipped: not-in-vs.py/const ${skipped[0]}, tier4 ${skipped[4]}, tier5 ${skipped[5]}, no-valid-case ${skipped.nocase}`);
if (DRY) { for (const j of jobs.slice(0, Number(opt('--show', 5)))) console.log(`--- ${j.key} (tier ${j.tier})\n${j.code.split('\n').slice(-3).join('\n')}`); process.exit(0); }

fs.mkdirSync(path.dirname(LOG), { recursive: true });
const done = new Set(); const startedOnly = new Map();
if (fs.existsSync(LOG)) for (const line of fs.readFileSync(LOG, 'utf8').split('\n')) {
  if (!line) continue; const e = JSON.parse(line);
  if (e.ev === 'started') startedOnly.set(e.key, e);
  else if (e.ev === 'outcome') {
    startedOnly.delete(e.key);
    const retry = args.includes('--retry') && (e.outcome === 'bridge-error' || e.outcome === 'busy' || (e.outcome === 'error' && e.ms >= 25000));
    if (retry) done.delete(e.key); else done.add(e.key);
  }
}
const write = (e) => fs.appendFileSync(LOG, JSON.stringify({ t: new Date().toISOString(), ...e }) + '\n');
const crashedFns = new Set();
for (const l of fs.existsSync(LOG) ? fs.readFileSync(LOG, 'utf8').split('\n') : []) { if (l.includes('"outcome":"crash"')) crashedFns.add(JSON.parse(l).fn); }
for (const [key, e] of startedOnly) { write({ ev: 'outcome', key, fn: e.fn, tier: e.tier, ctx: e.ctx, outcome: 'crash', note: 'blamed on resume: started with no outcome' }); done.add(key); }

let prevJob = null;
let consecCrashes = 0, consecRelaunchFails = 0, sinceRecycle = 0, ran = 0;
async function recover(why) {
  await dropClient();
  for (;;) {
    if (relaunch()) { consecRelaunchFails = 0; sinceRecycle = 0; return true; }
    if (++consecRelaunchFails >= 3) { log(`STOP: relaunch failed 3 times (${why})`); return false; }
  }
}

if (!(await fetch('http://127.0.0.1:9101/health').then((r) => r.json()).catch(() => ({}))).paletteConnected || !vwWindows()?.some((w) => /Untitled/.test(w))) {
  if (!(await recover('initial'))) process.exit(2);
}
let baseline = vwWindows() ?? [];

for (const job of jobs) {
  if (done.has(job.key)) continue;
  if ((job.case || job.ctx === 'inline') && crashedFns.has(job.fn)) { write({ ev: 'outcome', key: job.key, fn: job.fn, tier: job.tier, ctx: job.ctx, case: job.case, outcome: 'skipped', note: 'function already crashes with valid arguments' }); continue; }
  if (ran >= LIMIT) break;
  if (ran % 100 === 0 && freeGB() < MIN_FREE_GB) { log('STOP: disk below 10 GB'); break; }
  if (sinceRecycle >= RECYCLE_EVERY) { if (!(await recover('recycle'))) break; baseline = vwWindows() ?? []; }
  if (!(await waitBridge())) { log('bridge not reachable; relaunching'); if (!(await recover('bridge down'))) break; baseline = vwWindows() ?? []; if (!(await waitBridge())) { log('STOP: bridge down after relaunch'); break; } }
  ran++; sinceRecycle++;
  const t0 = Date.now();
  write({ ev: 'started', key: job.key, fn: job.fn, tier: job.tier, ctx: job.ctx });

  let outcome = null, detail = {}; let docLost = false;
  const p = callScript(job.code, job.ctx === 'deferred').then((r) => ({ r }), (e) => ({ e }));
  let res = await Promise.race([p, new Promise((r) => setTimeout(() => r(null), MODAL_CHECK_MS))]);
  if (!res) {
    const wins = vwWindows() ?? [];
    const extra = extraWindows(wins, baseline);
    if (vwAlive() && extra.length) { detail.modal = extra; detail.dismiss = dismissModal(); outcome = 'interactive'; }
    res = await Promise.race([p, new Promise((r) => setTimeout(() => r(null), HANG_MS - MODAL_CHECK_MS))]);
  }
  if (res?.r) {
    const { j, text, isError } = res.r;
    if (!outcome) {
      if (j && !j.ok && /busy|modal/i.test(j.error || '')) outcome = 'busy';
      else if (j?.ok) outcome = 'ok';
      else if (/block|refus|stub/i.test(text)) outcome = 'refused';
      else if (j && !j.ok) outcome = 'error';
      else if (/palette|not connected|Timed out/i.test(text) && !vwAlive()) outcome = 'crash';
      else outcome = isError ? 'bridge-error' : 'error';
    }
    detail.error = j?.error; detail.stdout = j?.stdout?.slice(0, 300); detail.stderr = j?.stderr?.slice(-400); if (!j) detail.text = text.slice(0, 400);
  } else if (res?.e) {
    detail.err = String(res.e.message || res.e).slice(0, 300);
    outcome = !vwAlive() ? 'crash' : BRIDGE_DOWN.test(detail.err) ? 'bridge-error' : 'bridge-error';
    if (BRIDGE_DOWN.test(detail.err)) await dropClient();
  } else if (!outcome) outcome = vwAlive() ? 'hang' : 'crash';
  else if (outcome === 'interactive') detail.afterDismiss = 'no result';

  // Post-checks: process alive, document still there, stray windows.
  const alive = vwAlive();
  if (!alive && outcome !== 'crash') { detail.was = outcome; outcome = 'crash'; }
  if (alive && outcome !== 'hang') {
    const wins = vwWindows() ?? [];
    if (!wins.some((w) => /Untitled/.test(w))) { docLost = true; detail.windows = wins; if (outcome === 'ok') outcome = 'document-level'; }
    const extra = extraWindows(wins, baseline);
    if (extra.length) {
      detail.newWindows = extra; if (outcome === 'ok') outcome = 'window'; detail.dismissAfter = dismissModal();
      await new Promise((r) => setTimeout(r, 1000));
      if ((vwWindows() ?? []).length > baseline.length) { detail.stuck = true; docLost = true; }   // won't close: relaunch
    }
  }
  if (outcome === 'busy') {
    const wins = vwWindows() ?? [];
    detail.windows = wins; detail.dismiss = dismissModal();
    if (prevJob) write({ ev: 'note', key: prevJob.key, fn: prevJob.fn, note: 'a dialog was up after this job (found by the next job)', windows: wins });
    log(`busy: dialog up after ${prevJob?.key}; ${detail.dismiss}`);
    if (!job.requeued) { job.requeued = true; jobs.push(job); }   // it never really ran: try again later
    if ((vwWindows() ?? []).length > baseline.length) { spawnSync('pkill', ['-9', '-x', 'Vectorworks']); docLost = true; }
  }
  prevJob = job;
  write({ ev: 'outcome', key: job.key, fn: job.fn, tier: job.tier, ctx: job.ctx, case: job.case ?? 'valid', outcome, ms: Date.now() - t0, ...detail });
  if (outcome !== 'ok' && outcome !== 'error') log(`${job.key} -> ${outcome}`);
  if (ran % 50 === 0) log(`progress: ${ran} run this session`);

  if (outcome === 'crash') {
    crashedFns.add(job.fn);
    if (++consecCrashes > 12) { log('STOP: more than 12 crashes in a row'); break; }
    if (!(await recover('crash'))) break; baseline = vwWindows() ?? [];
    write({ ev: 'note', key: job.key, fn: job.fn, ips: newestIps(t0) });
  } else {
    consecCrashes = 0;
    if (outcome === 'hang' || docLost) { spawnSync('pkill', ['-9', '-x', 'Vectorworks']); if (!(await recover(outcome))) break; baseline = vwWindows() ?? []; }
  }
}
await dropClient();
log(`done: ${ran} jobs this session; log ${LOG}`);
process.exit(0);
