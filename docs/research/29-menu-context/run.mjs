// #29: run each crasher/hang case in each context; classify ok / error / crash / hang. Log JSONL; resumable.
// node run.mjs <contexts comma list: timer,menu,menu-noscopes> [fn filter regex]
import fs from 'node:fs'; import path from 'node:path'; import os from 'node:os';
import { spawnSync } from 'node:child_process';
const HERE = path.dirname(new URL(import.meta.url).pathname); const SP = path.dirname(HERE);
const cases = JSON.parse(fs.readFileSync(path.join(HERE, 'cases.json'), 'utf8'));
const CTX = { timer: {}, menu: { context: 'menu' }, 'menu-noscopes': { context: 'menu', scopes: false } };
const ctxs = (process.argv[2] || 'timer,menu').split(','); const filt = new RegExp(process.argv[3] || '.');
const LOG = path.join(HERE, 'results.jsonl');
const done = new Set(fs.existsSync(LOG) ? fs.readFileSync(LOG, 'utf8').split('\n').filter(Boolean).map((l) => JSON.parse(l)).filter((e) => e.outcome).map((e) => e.key) : []);
const MARKER = path.join(os.homedir(), 'Library/Application Support/Vectorworks/2027/Plug-ins/Data/vw-mcp/SWEEP_MODE');
const log = (...a) => console.log(new Date().toTimeString().slice(0, 8), ...a);
const alive = () => spawnSync('pgrep', ['-x', 'Vectorworks']).status === 0;
const launch = () => { const r = spawnSync('zsh', [path.join(SP, 'launch.sh')], { encoding: 'utf8' }); log('launch:', r.stdout.trim().split('\n').pop()); return r.status === 0; };
const cancelModal = () => spawnSync('osascript', ['-e', `tell application "System Events" to tell process "Vectorworks"
  set out to ""
  repeat with w in windows
    try
      set out to out & (name of w) & ";"
      repeat with b in {"Cancel", "No", "OK", "Close"}
        if exists button (b as text) of w then
          click button (b as text) of w
          set out to out & "clicked " & (b as text) & ";"
          exit repeat
        end if
      end repeat
    end try
  end repeat
  return out
end tell`], { encoding: 'utf8' }).stdout.trim();

function inst() {
  const dir = path.join(os.homedir(), 'Library/Application Support/vw-mcp/instances');
  return fs.readdirSync(dir).map((f) => JSON.parse(fs.readFileSync(path.join(dir, f)))).sort((a, b) => b.started.localeCompare(a.started))[0];
}
async function run(code, opts) {
  const i = inst(); const base = `http://127.0.0.1:${i.port}`;
  const H = { Authorization: `Bearer ${i.token}`, 'Content-Type': 'application/json', 'X-VW-MCP-Client': 'research-29' };
  const t0 = Date.now(); let modal = null;
  let r = await (await fetch(base + '/jobs', { method: 'POST', headers: H, body: JSON.stringify({ code, ...opts }) })).json();
  if (r.jobId == null) return { outcome: 'not-queued', r };
  const id = r.jobId;
  for (;;) {
    try { r = await (await fetch(`${base}/jobs/${id}?wait=5`, { headers: H, signal: AbortSignal.timeout(9000) })).json(); }
    catch (e) { await new Promise((s) => setTimeout(s, 1500)); if (!alive()) return { outcome: 'crash', ms: Date.now() - t0, modal }; r = { pending: true }; }
    if (!r.pending) return { outcome: r.ok ? 'ok' : 'error', ms: Date.now() - t0, modal, r };
    if (!alive()) return { outcome: 'crash', ms: Date.now() - t0, modal };
    if (Date.now() - t0 > 10000 && !modal) { modal = cancelModal() || '-'; log('  modal check:', modal); }
    if (Date.now() - t0 > 45000) return { outcome: alive() ? 'hang' : 'crash', ms: Date.now() - t0, modal };
  }
}

fs.mkdirSync(path.dirname(MARKER), { recursive: true }); fs.writeFileSync(MARKER, '');
process.on('exit', () => { try { fs.unlinkSync(MARKER); } catch {} });
for (const sig of ['SIGINT', 'SIGTERM']) process.on(sig, () => process.exit(1));
for (const ctx of ctxs) for (const [fn, code] of Object.entries(cases)) {
  const key = `${fn}|${ctx}`; if (done.has(key) || !filt.test(fn)) continue;
  if (!alive() || !(await fetch(`http://127.0.0.1:${inst()?.port}/status`).then(() => true, () => false))) if (!launch()) { log('launch failed; stop'); process.exit(2); }
  log(`${key} ...`);
  let res; try { res = await run(code, CTX[ctx]); } catch (e) { res = { outcome: alive() ? 'bridge-error' : 'crash', err: String(e) }; }
  if (res.outcome === 'hang') { spawnSync('pkill', ['-9', '-x', 'Vectorworks']); await new Promise((s) => setTimeout(s, 3000)); }
  const r = res.r || {};
  const rec = { key, fn, ctx, outcome: res.outcome, ms: res.ms, modal: res.modal, stdout: r.stdout?.slice(0, 300), stderr: r.stderr?.slice(-300), error: r.error, refused: r.refused, guarded: r.guarded, doMenuName: r.doMenuName, menuContext: r.menuContext };
  fs.appendFileSync(LOG, JSON.stringify({ t: new Date().toISOString(), ...rec }) + '\n');
  log(`  -> ${res.outcome}${r.error ? ' ' + String(r.error).slice(0, 80) : ''}${r.doMenuName && !r.doMenuName.ran ? ' (menu did not run)' : ''}`);
}
log('done');
