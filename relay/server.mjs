#!/usr/bin/env node
//
// vw-mcp: MCP server for Vectorworks (relay)
// =============================================================================
//   AI client --MCP (stdio, or Streamable HTTP with --http)--> THIS RELAY
//             --HTTP 127.0.0.1 + bearer token--> vw-mcp plug-in (headless, inside Vectorworks)
//
// The plug-in starts with Vectorworks and writes a discovery file per running instance:
//   ~/Library/Application Support/vw-mcp/instances/<pid>.json  { pid, port, token, vwBuild, ... }
// The relay reads it on every call, so restarting Vectorworks needs nothing here.
// VW_MCP_INSTANCE=<pid> picks one instance when several Vectorworks versions run at once.
//
//   npx -y vw-mcp              stdio MCP server (what AI clients launch)
//   npx -y vw-mcp --http       Streamable HTTP on 127.0.0.1:$VW_MCP_HTTP_PORT (default 47822), /mcp
//
// All logs go to stderr (stdout is the MCP protocol in stdio mode).
// -----------------------------------------------------------------------------

import { McpServer } from '@modelcontextprotocol/sdk/server/mcp.js';
import { StdioServerTransport } from '@modelcontextprotocol/sdk/server/stdio.js';
import { StreamableHTTPServerTransport } from '@modelcontextprotocol/sdk/server/streamableHttp.js';
import { isInitializeRequest } from '@modelcontextprotocol/sdk/types.js';
import { randomUUID } from 'node:crypto';
import express from 'express';
import { z } from 'zod';
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import { fileURLToPath } from 'node:url';

const HTTP_PORT  = Number(process.env.VW_MCP_HTTP_PORT || 47822);
const USE_HTTP   = process.argv.includes('--http');
const INSTANCE   = process.env.VW_MCP_INSTANCE ? Number(process.env.VW_MCP_INSTANCE) : null;
const INSTANCES_DIR = process.env.VW_MCP_INSTANCES_DIR ||
  (process.platform === 'win32'
    ? path.join(process.env.APPDATA || os.homedir(), 'vw-mcp', 'instances')
    : path.join(os.homedir(), 'Library', 'Application Support', 'vw-mcp', 'instances'));
const MAX_WAIT_SEC = 20;   // long-poll slice; the plug-in caps it at 25
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

const log = (...a) => console.error('[vw-mcp]', ...a);

// The safety table and vs.* signatures come from the running plug-in (GET /safety-table, /signatures),
// so vw_lookup_function always matches what that plug-in enforces (#17). Cached per plug-in instance.
const HERE = path.dirname(fileURLToPath(import.meta.url));
const RELAY_VERSION = JSON.parse(fs.readFileSync(path.join(HERE, 'package.json'), 'utf8')).version;
let safetyCache = { key: null, table: null, signatures: null };
async function loadSafety() {
  const inst = pickInstance();
  if (!inst) throw new Error(NOT_RUNNING);
  const key = `${inst.pid}:${inst.pluginVersion}`;
  if (safetyCache.key !== key) {
    const [table, signatures] = await Promise.all([
      plugin('GET', '/safety-table', null, 10000), plugin('GET', '/signatures', null, 10000)]);
    if (!table?.functions) throw new Error('The vw-mcp plug-in did not return its safety table (it may be older than this relay).');
    safetyCache = { key, table, signatures: signatures?.ok === false ? {} : (signatures || {}) };
  }
  return safetyCache;
}
// Plug-in and relay come from one release (#17): a difference beyond patch level is worth a warning.
function versionWarning(pluginVersion) {
  if (!pluginVersion) return null;
  const mm = (v) => String(v).split('.').slice(0, 2).join('.');
  return mm(pluginVersion) === mm(RELAY_VERSION) ? null
    : `The vw-mcp plug-in is ${pluginVersion} but this relay is ${RELAY_VERSION}. Install the matching versions ` +
      'from the same release (plug-in zip and relay).';
}
let lastEvent = null;   // last refusal / timeout / unresponsive, for vw_bridge_status

// -----------------------------------------------------------------------------
// Plug-in client: find the running Vectorworks instance and call its internal endpoints.
// -----------------------------------------------------------------------------
const NOT_RUNNING = 'Vectorworks with the vw-mcp plug-in is not running. Start Vectorworks ' +
  '(the plug-in starts with it), then retry. Check the vw-mcp status palette if it still fails.';

function pidAlive(pid) { try { process.kill(pid, 0); return true; } catch (e) { return e.code === 'EPERM'; } }

// Live instances, newest first. Stale files (VW crashed) are skipped and removed.
function findInstances() {
  let names = [];
  try { names = fs.readdirSync(INSTANCES_DIR).filter((f) => f.endsWith('.json')); } catch { return []; }
  const out = [];
  for (const f of names) {
    const file = path.join(INSTANCES_DIR, f);
    try {
      const d = JSON.parse(fs.readFileSync(file, 'utf8'));
      if (!pidAlive(d.pid)) { try { fs.unlinkSync(file); } catch {} continue; }
      out.push(d);
    } catch { /* half-written: skip */ }
  }
  return out.sort((a, b) => String(b.started).localeCompare(String(a.started)));
}
function pickInstance() {
  const all = findInstances();
  return (INSTANCE ? all.find((d) => d.pid === INSTANCE) : all[0]) ?? null;
}

let clientName = '';   // the MCP client's name (from initialize), shown in the status palette
async function plugin(method, route, body, timeoutMs = 30000) {
  const inst = pickInstance();
  if (!inst) throw new Error(NOT_RUNNING);
  const ctl = new AbortController();
  const timer = setTimeout(() => ctl.abort(), timeoutMs);
  try {
    const res = await fetch(`http://127.0.0.1:${inst.port}${route}`, {
      method,
      headers: { Authorization: `Bearer ${inst.token}`, 'Content-Type': 'application/json',
        ...(clientName ? { 'X-VW-MCP-Client': clientName } : {}) },
      body: body ? JSON.stringify(body) : undefined,
      signal: ctl.signal,
    });
    const j = await res.json().catch(() => ({ ok: false, error: `HTTP ${res.status}` }));
    return j;
  } catch (e) {
    if (e.name === 'AbortError') throw new Error(`Vectorworks did not answer within ${Math.round(timeoutMs / 1000)} s.`);
    throw new Error(NOT_RUNNING + ` (${e.cause?.code || e.message})`);
  } finally { clearTimeout(timer); }
}

// -----------------------------------------------------------------------------
// MCP server factory — the tools an AI client can call. A fresh instance is created per
// HTTP session (stateful Streamable HTTP), but they all share the relay state above.
// -----------------------------------------------------------------------------
const asText = (value) => ({
  content: [{ type: 'text', text: typeof value === 'string' ? value : JSON.stringify(value, null, 2) }],
});
const asError = (message) => ({ content: [{ type: 'text', text: message }], isError: true });

// Sent to the client at connect, so the AI gets the house rules without the user pasting them.
// Keep in step with PROMPT in plugin/palette/index.html and the README.
const INSTRUCTIONS = `You can control Vectorworks through the vw-mcp tools.
- Call vw_bridge_status first. If documentOpen is false, ask the user to open a drawing.
- Run Python with execute_script (the vs module is available). print() JSON to return data.
- Every vs.* call is safety-checked. A refusal comes back as an error with a reason and advice. Don't retry a refused call; use the alternative it names.
- Use vw_lookup_function before calling an unfamiliar vs.* function.
- Plug-in objects (Stage Deck, lighting devices, …) that a job creates or changes are rebuilt automatically when it finishes (autoReset in the result), so their 2D/3D shows the new attributes and parameters. A vs.ResetObject inside the creating script does nothing; check the result in a new call.
- Create plug-in objects with vs.CreateCustomObjectN(name, pt, rot, False): False skips the Object Preferences dialog.
- A solid fill (vs.SetFPat(h, 1)) paints with the background colour: set vs.SetFillBack as well as vs.SetFillFore.
- Only set allowUnclassified or allowDocumentLevel if the user asks.
- Each job is one undo step in Vectorworks.`;

function buildMcpServer() {
  const mcp = new McpServer({ name: 'vw-mcp', version: RELAY_VERSION }, { instructions: INSTRUCTIONS });

  // Submit a job to the plug-in (it runs on a clean main-loop pass) and long-poll for its result.
  async function runJob(params, timeoutSec) {
    clientName = mcp.server.getClientVersion()?.name || clientName;
    const submit = await plugin('POST', '/jobs', params);
    if (!submit || submit.jobId == null) return submit;   // refused up front
    const jobId = submit.jobId;
    const deadline = Date.now() + (timeoutSec + 25) * 1000;   // script budget + busy wait + slack
    for (;;) {
      const r = await plugin('GET', `/jobs/${jobId}?wait=${MAX_WAIT_SEC}`, null, (MAX_WAIT_SEC + 10) * 1000)
        .catch((e) => ({ pending: true, transient: e.message }));
      if (r && r.pending !== true) return r;
      if (Date.now() > deadline) {
        lastEvent = { at: new Date().toISOString(), kind: 'unresponsive', jobId };
        return { ok: false, unresponsive: true, jobId,
          error: `Vectorworks is unresponsive: job ${jobId} did not finish within ${timeoutSec + 25} s. ` +
            'It may be stuck inside a Vectorworks call or have crashed. It is never force-quit by this server.' };
      }
      if (r?.transient) await sleep(1000);
    }
  }
  // Refusals and timeouts come back as isError with the refusal body first (spec §4).
  function toResult(r) {
    if (r && r.refused) {
      lastEvent = { at: new Date().toISOString(), kind: 'refusal', function: r.function, class: r.class, reason: r.reason };
      const body = { refused: true, function: r.function ?? null, class: r.class, reason: r.reason,
        alternative: r.alternative ?? null, partialChanges: !!r.partialChanges, advice: r.advice ?? null };
      if (r.stdout) body.stdout = r.stdout;
      if (r.stderr) body.stderr = r.stderr;
      return { content: [{ type: 'text', text: JSON.stringify(body, null, 2) }], isError: true };
    }
    if (r && (r.unresponsive || r.guard?.timeout)) {
      if (r.guard?.timeout) lastEvent = { at: new Date().toISOString(), kind: 'timeout', seconds: r.guard.timeout.seconds };
      return { content: [{ type: 'text', text: JSON.stringify(r, null, 2) }], isError: true };
    }
    return asText(r);
  }

  mcp.tool(
    'execute_script',
    'Run Python inside the open Vectorworks document and return its output (the `vs` module is ' +
    'available). print() JSON and read it back from "stdout". Every vs.* call is checked against a ' +
    'safety table built by testing each function: calls that crash, hang or open dialogs are refused ' +
    'before they run, handle arguments are checked for the right object type, and Begin*/End* calls ' +
    'must pair up. A refusal returns isError with {refused, function, class, reason, alternative, ' +
    'partialChanges, advice}. Each job is one undo step and runs on a clean main-loop pass. Use ' +
    'vw_lookup_function to check a function first. Plug-in objects the job creates or changes are rebuilt ' +
    'automatically after it (vs.ResetObject inside the creating script does nothing); the result\'s autoReset counts them.',
    {
      code: z.string().describe('Python source. `import vs` is optional (vs is predefined).'),
      lang: z.enum(['python', 'ops']).optional()
        .describe('"python" (default). "ops" is deprecated: use run_native_op.'),
      allowDocumentLevel: z.boolean().optional()
        .describe('Allow functions that open, close or replace documents or windows.'),
      allowUnclassified: z.boolean().optional()
        .describe('Allow vs.* functions the safety table has no entry for (not yet tested). At your own risk.'),
      timeoutSec: z.number().optional()
        .describe('Script time budget in seconds (default 30, max 300). The script is interrupted when it runs out.'),
      autoReset: z.boolean().optional()
        .describe('Rebuild the plug-in objects this job creates or changes once it finishes (default true).'),
    },
    async ({ code, lang, allowDocumentLevel, allowUnclassified, timeoutSec, autoReset }) => {
      const t = Math.min(Math.max(timeoutSec ?? 30, 1), 300);
      try {
        return toResult(await runJob({ code, lang: lang || 'python', allowDocumentLevel: !!allowDocumentLevel,
          allowUnclassified: !!allowUnclassified, timeoutSec: t, autoReset: autoReset !== false }, t));
      } catch (e) { return asError(e.message || String(e)); }
    },
  );

  mcp.tool(
    'run_native_op',
    'Change the document through native SDK calls instead of Python. `ops` is a JSON array, e.g. ' +
    '[{"op":"rect","x1":0,"y1":0,"x2":1000,"y2":500}]. Curated ops: rect, oval, rrect, line, locus, text, ' +
    'polygon, layer, viewport, group, duplicate, move, rotate, delete, clearLayer. Generic call: ' +
    '{"op":"call","fn":"<ISDK method>","args":[...],"as":<int>}; args: numbers/bools/strings literal, ' +
    '[x,y]/[x,y,z] = point, [x1,y1,x2,y2] = rect, handles via {"$h":id} / {"$name":"X"} / {"$layer":"X"}. ' +
    '{"op":"clearHandles"} resets the handle registry. One undo step per call. "call" is safety-checked: each ISDK ' +
    'method takes the class of its tested vs.* twin (crashers, dialogs and event-only methods are refused; methods ' +
    'with no twin need allowUnclassified), and handle arguments that name a missing object are refused.',
    {
      ops: z.union([z.string(), z.array(z.any())]).describe('JSON array of operations (or its JSON text).'),
      allowUnclassified: z.boolean().optional()
        .describe('Allow "call" on ISDK methods with no safety class yet (no tested vs.* twin). At your own risk.'),
      allowDocumentLevel: z.boolean().optional()
        .describe('Allow "call" on methods that open, close or replace documents or windows.'),
      autoReset: z.boolean().optional()
        .describe('Rebuild the plug-in objects this job creates or changes once it finishes (default true).'),
    },
    async ({ ops, allowUnclassified, allowDocumentLevel, autoReset }) => {
      try {
        const code = typeof ops === 'string' ? ops : JSON.stringify(ops);
        return toResult(await runJob({ code, lang: 'ops', allowUnclassified: !!allowUnclassified,
          allowDocumentLevel: !!allowDocumentLevel, autoReset: autoReset !== false }, 30));
      } catch (e) { return asError(e.message || String(e)); }
    },
  );

  mcp.tool(
    'vw_lookup_function',
    'Look up a vs.* function in the safety table: its class (safe, crasher, hang, interactive, ' +
    'event-only, document-level or unclassified), the argument checks applied, its signature and any alternative. Read-only.',
    { name: z.string().describe('Function name, with or without "vs." (case-insensitive).') },
    async ({ name }) => {
      let safetyTable, signatures;
      try { ({ table: safetyTable, signatures } = await loadSafety()); }
      catch (e) { return asError(e.message || String(e)); }
      const n = name.replace(/^vs\./, '');
      const fns = safetyTable.functions;
      const key = fns[n] ? n : Object.keys(fns).find((k) => k.toLowerCase() === n.toLowerCase())
        ?? Object.keys(signatures).find((k) => k.toLowerCase() === n.toLowerCase()) ?? n;
      const e = fns[key];
      return asText({
        function: key,
        class: e ? e.class : 'unclassified',
        basis: e ? (e.basis === 'category' ? 'category (not run by the sweep)' : 'sweep') : null,
        argCheck: e?.args ? e.args.map(([arg, kind, rule]) => ({ arg, kind, ...(rule ? { objectType: rule } : {}) })) : null,
        rerouted: e?.reroute ? `runs as ${e.reroute === 'upper' ? 'str.upper()' : e.reroute}` : null,
        alternative: e?.alternative ?? null,
        signature: signatures[key] ? { python: signatures[key][0], vectorscript: signatures[key][1] } : null,
        allowedByDefault: !!e && (e.class === 'safe' || !!e.reroute),
        needs: !e ? 'allowUnclassified: true' : e.class === 'document-level' ? 'allowDocumentLevel: true' : null,
        nativeCall: (() => {   // run_native_op "call" with the ISDK method of the same name
          const k = Object.keys(safetyTable.isdk || {}).find((x) => x.toLowerCase() === n.toLowerCase());
          return k ? { method: k, class: safetyTable.isdk[k].class, via: 'vs.' + safetyTable.isdk[k].via } : null;
        })(),
        table: { vwBuild: safetyTable.vwBuild, source: safetyTable.source },
      });
    },
  );

  mcp.tool(
    'vw_bridge_status',
    'Check the connection to Vectorworks: whether the vw-mcp plug-in is running, the Vectorworks build, whether ' +
    'a document is open or a dialog is blocking jobs, the safety table in use (with a warning when it was swept on a ' +
    'different build), and the last refusal or timeout. Call this first.',
    {},
    async () => {
      clientName = mcp.server.getClientVersion()?.name || clientName;
      const inst = pickInstance();
      let info = null, error = null;
      if (inst) info = await plugin('GET', '/status', null, 5000).catch((e) => { error = e.message; return null; });
      else error = NOT_RUNNING;
      const tableBuild = info?.tableBuild ?? null;
      const mismatch = info && tableBuild && info.vwBuild !== tableBuild;
      return asText({
        connected: !!info?.ok,
        vwBuild: info?.vwBuild ?? inst?.vwBuild ?? null,
        engine: info?.engine ?? null,
        documentOpen: info?.documentOpen ?? null,
        busy: info?.busy ?? null,
        sweepMode: info?.sweepMode ?? null,
        guardVersion: info?.guardVersion ?? null,
        plugin: info ? { version: info.pluginVersion, port: info.port, pid: info.pid } : null,
        relayVersion: RELAY_VERSION,
        otherInstances: findInstances().filter((d) => d.pid !== inst?.pid).map((d) => ({ pid: d.pid, vwBuild: d.vwBuild })),
        safetyTable: info ? { vwBuild: tableBuild, functions: info.tableFunctions } : null,
        warning: [mismatch ? `Vectorworks is ${info.vwBuild} but the safety table was swept on ${tableBuild}. ` +
          'Classes carry forward, but a function that changed in this build may behave differently; re-run the sweep.' : null,
          versionWarning(info?.pluginVersion)].filter(Boolean).join(' ') || null,
        error,
        lastEvent,
      });
    },
  );

  return mcp;
}

// -----------------------------------------------------------------------------
// Boot — HTTP (default) or stdio (--stdio)
// -----------------------------------------------------------------------------
if (!USE_HTTP) {
  const transport = new StdioServerTransport();
  await buildMcpServer().connect(transport);
  log('MCP server ready on stdio.');
} else {
  const app = express();
  app.use(express.json({ limit: '10mb' }));

  // Stateful Streamable HTTP: one transport per MCP session, keyed by header.
  const transports = {}; // sessionId -> transport

  app.post('/mcp', async (req, res) => {
    const sessionId = req.headers['mcp-session-id'];
    let transport = sessionId ? transports[sessionId] : undefined;

    if (!transport && isInitializeRequest(req.body)) {
      transport = new StreamableHTTPServerTransport({
        sessionIdGenerator: () => randomUUID(),
        onsessioninitialized: (sid) => { transports[sid] = transport; },
      });
      transport.onclose = () => { if (transport.sessionId) delete transports[transport.sessionId]; };
      await buildMcpServer().connect(transport);
    } else if (!transport) {
      res.status(400).json({
        jsonrpc: '2.0',
        error: { code: -32000, message: 'Bad Request: no valid session ID (send initialize first)' },
        id: null,
      });
      return;
    }

    await transport.handleRequest(req, res, req.body);
  });

  // GET (server->client SSE stream) and DELETE (session teardown) reuse the session.
  const sessionRequest = async (req, res) => {
    const sessionId = req.headers['mcp-session-id'];
    const transport = sessionId ? transports[sessionId] : undefined;
    if (!transport) { res.status(400).send('Invalid or missing session ID'); return; }
    await transport.handleRequest(req, res);
  };
  app.get('/mcp', sessionRequest);
  app.delete('/mcp', sessionRequest);

  // Tiny health endpoint for humans / monitoring.
  app.get('/health', (req, res) => {
    const inst = pickInstance();
    res.json({ ok: true, vectorworks: inst ? { pid: inst.pid, port: inst.port, vwBuild: inst.vwBuild } : null });
  });

  app.listen(HTTP_PORT, '127.0.0.1', () => {
    log(`MCP server (Streamable HTTP) on http://127.0.0.1:${HTTP_PORT}/mcp`);
  });
}

const shutdown = () => process.exit(0);
process.on('SIGINT', shutdown);
process.on('SIGTERM', shutdown);
