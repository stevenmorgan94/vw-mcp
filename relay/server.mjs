#!/usr/bin/env node
//
// vw-mcp: MCP server for Vectorworks (relay)
// =============================================================================
// TODO(#6): this is the transport carried over unchanged from the original
// palette bridge. Ticket #6 replaces it: the headless plug-in serves
// POST /jobs, GET /jobs/{id}?wait=N and GET /status on 127.0.0.1 (bearer token,
// discovery file), and this relay becomes an HTTP client of it (stdio MCP by
// default for `npx -y vw-mcp`). Until then nothing in this repo dials :9100.
//
// Persistent relay. Owns two ports:
//   - WebSocket :9100  — the Vectorworks bridge palette dials in to this (palette side)
//   - HTTP      :9101  — MCP clients connect here  (/mcp, Streamable HTTP)
//
//   AI client (MCP)  --HTTP /mcp-->  THIS PROCESS  --WS :9100-->  palette (in VW)
//                                                                    |
//                                                    <palette JS bridge>.execute_script
//                                                                    |
//                                                        C++ bridge -> VW main thread
//
// Because this process is standalone (not spawned per client session over stdio),
// the palette always has something to connect to, there are no port clashes between
// sessions, and multiple MCP client sessions can share it.
//
// Pass `--stdio` to run as a classic stdio MCP server instead of HTTP (used by the
// headless test; stdout is then reserved for the MCP protocol). All logs go to stderr.
// -----------------------------------------------------------------------------

import { McpServer } from '@modelcontextprotocol/sdk/server/mcp.js';
import { StdioServerTransport } from '@modelcontextprotocol/sdk/server/stdio.js';
import { StreamableHTTPServerTransport } from '@modelcontextprotocol/sdk/server/streamableHttp.js';
import { isInitializeRequest } from '@modelcontextprotocol/sdk/types.js';
import { WebSocketServer } from 'ws';
import { randomUUID } from 'node:crypto';
import express from 'express';
import { z } from 'zod';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const WS_PORT         = Number(process.env.VW_MCP_WS_PORT || 9100);
const HTTP_PORT       = Number(process.env.VW_MCP_HTTP_PORT || 9101);
const CALL_TIMEOUT_MS = Number(process.env.VW_MCP_CALL_TIMEOUT_MS || 60000);
const USE_STDIO       = process.argv.includes('--stdio');

// Deferred-execution (crash-safe writes): poll cadence + overall wait for a job to finish.
const DEFER_POLL_INTERVAL_MS = Number(process.env.VW_MCP_DEFER_POLL_MS || 150);
const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

const log = (...a) => console.error('[vw-mcp]', ...a);

// The vs safety table the bridge enforces (built by safety/build_table.py), for vw_lookup_function.
// It lives in the repo's safety/ folder; VW_MCP_SAFETY_DIR overrides that (e.g. for a packaged relay).
const HERE = path.dirname(fileURLToPath(import.meta.url));
const SAFETY_DIR = process.env.VW_MCP_SAFETY_DIR || path.join(HERE, '..', 'safety');
let safetyTable = null, signatures = null;
function loadSafety() {
  if (safetyTable) return;
  try { safetyTable = JSON.parse(fs.readFileSync(path.join(SAFETY_DIR, 'vs-safety-table.json'), 'utf8')); }
  catch (e) { safetyTable = { functions: {}, error: String(e.message || e) }; }
  signatures = {};
  try {
    const rows = parseCSV(fs.readFileSync(path.join(SAFETY_DIR, 'functions.csv'), 'utf8'));
    for (const r of rows) signatures[r.name] = { python: r.python_signature, vectorscript: r.vectorscript_signature };
  } catch { /* signatures are optional */ }
}
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
let lastEvent = null;   // last refusal / timeout / unresponsive, for vw_bridge_status

// -----------------------------------------------------------------------------
// WebSocket relay — the palette connects out to us.
// -----------------------------------------------------------------------------
let palette = null;                 // currently connected palette socket (last wins)
let nextId  = 1;
const pending = new Map();          // id -> { resolve, reject, timer }

const wss = new WebSocketServer({ host: '127.0.0.1', port: WS_PORT });

wss.on('listening', () => log(`WebSocket relay listening on ws://127.0.0.1:${WS_PORT}`));
wss.on('error', (err) => log('WebSocket server error:', err.message));

wss.on('connection', (sock) => {
  if (palette && palette !== sock && palette.readyState === palette.OPEN) {
    log('A new palette connected — replacing the previous one.');
  }
  palette = sock;
  log('Palette connected.');

  sock.on('message', (raw) => {
    let msg;
    try { msg = JSON.parse(raw.toString()); }
    catch { log('Ignoring non-JSON message from palette:', raw.toString().slice(0, 200)); return; }
    const entry = msg && msg.id != null ? pending.get(msg.id) : null;
    if (!entry) return;
    pending.delete(msg.id);
    clearTimeout(entry.timer);
    if (msg.error) entry.reject(new Error(String(msg.error)));
    else entry.resolve(msg.result);
  });

  sock.on('close', () => { if (palette === sock) palette = null; log('Palette disconnected.'); });
  sock.on('error', (err) => log('Palette socket error:', err.message));
});

// Send a command to the palette and await its reply, keyed by a fresh id.
function callPalette(method, params) {
  return new Promise((resolve, reject) => {
    if (!palette || palette.readyState !== palette.OPEN) {
      reject(new Error(
        'No Vectorworks palette connected. Open Vectorworks, show the bridge palette, ' +
        'and make sure its MCP Bridge tab is connected to this relay.'));
      return;
    }
    const id = nextId++;
    const timer = setTimeout(() => {
      pending.delete(id);
      reject(new Error(`Timed out after ${CALL_TIMEOUT_MS}ms waiting for the palette to run ${method}.`));
    }, CALL_TIMEOUT_MS);
    pending.set(id, { resolve, reject, timer });
    palette.send(JSON.stringify({ id, method, params }));
  });
}

// -----------------------------------------------------------------------------
// MCP server factory — the tools an AI client can call. A fresh instance is created per
// HTTP session (stateful Streamable HTTP), but they all share the relay state above.
// -----------------------------------------------------------------------------
const asText = (value) => ({
  content: [{ type: 'text', text: typeof value === 'string' ? value : JSON.stringify(value, null, 2) }],
});
const asError = (message) => ({ content: [{ type: 'text', text: message }], isError: true });

function buildMcpServer() {
  const mcp = new McpServer({ name: 'vw-mcp', version: '0.0.0' });

  // Submit a job to the bridge (always deferred: it runs on a clean main-loop pass) and poll for its result.
  async function runJob(params, timeoutSec) {
    const submit = await callPalette('execute_script', { ...params, defer: true });
    if (!submit || submit.deferred !== true || submit.jobId == null) return submit;   // refused up front, or an old bridge
    const jobId = submit.jobId;
    const deadline = Date.now() + (timeoutSec + 25) * 1000;   // script budget + busy wait + slack
    for (;;) {
      await sleep(DEFER_POLL_INTERVAL_MS);
      const r = await callPalette('execute_script', { poll: jobId });
      if (!r || r.pending !== true) return r;
      if (Date.now() > deadline) {
        lastEvent = { at: new Date().toISOString(), kind: 'unresponsive', jobId };
        return { ok: false, unresponsive: true, jobId,
          error: `Vectorworks is unresponsive: job ${jobId} did not finish within ${timeoutSec + 25} s. ` +
            'It may be stuck inside a Vectorworks call or have crashed. It is never force-quit by this server.' };
      }
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
    'vw_lookup_function to check a function first.',
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
    },
    async ({ code, lang, allowDocumentLevel, allowUnclassified, timeoutSec }) => {
      const t = Math.min(Math.max(timeoutSec ?? 30, 1), 300);
      try {
        return toResult(await runJob({ code, lang: lang || 'python', allowDocumentLevel: !!allowDocumentLevel,
          allowUnclassified: !!allowUnclassified, timeoutSec: t }, t));
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
    '{"op":"clearHandles"} resets the handle registry. One undo step per call.',
    { ops: z.union([z.string(), z.array(z.any())]).describe('JSON array of operations (or its JSON text).') },
    async ({ ops }) => {
      try {
        const code = typeof ops === 'string' ? ops : JSON.stringify(ops);
        return toResult(await runJob({ code, lang: 'ops' }, 30));
      } catch (e) { return asError(e.message || String(e)); }
    },
  );

  mcp.tool(
    'vw_lookup_function',
    'Look up a vs.* function in the safety table: its class (safe, crasher, hang, interactive, ' +
    'event-only, document-level or unclassified), the argument checks applied, its signature and any alternative. Read-only.',
    { name: z.string().describe('Function name, with or without "vs." (case-insensitive).') },
    async ({ name }) => {
      loadSafety();
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
        signature: signatures[key] ?? null,
        allowedByDefault: !!e && (e.class === 'safe' || !!e.reroute),
        needs: !e ? 'allowUnclassified: true' : e.class === 'document-level' ? 'allowDocumentLevel: true' : null,
        table: { vwBuild: safetyTable.vwBuild, source: safetyTable.source },
      });
    },
  );

  mcp.tool(
    'vw_bridge_status',
    'Check whether the Vectorworks bridge palette is connected to this MCP relay: the running Vectorworks build, whether ' +
    'a document is open or a dialog is blocking jobs, the safety table in use (with a warning when it was swept on a ' +
    'different build), and the last refusal or timeout.',
    {},
    async () => {
      loadSafety();
      const connected = !!(palette && palette.readyState === palette.OPEN);
      // Live bridge state. An older plug-in without the info request answers with an error: report it as unknown.
      let info = null;
      if (connected) info = await callPalette('execute_script', { info: true }).catch(() => null);
      if (info && !info.vwBuild) info = null;
      const mismatch = info && safetyTable.vwBuild && info.vwBuild !== safetyTable.vwBuild;
      return asText({
        paletteConnected: connected,
        vwBuild: info?.vwBuild ?? null,
        engine: info?.engine ?? null,
        documentOpen: info?.documentOpen ?? null,
        busy: info?.busy ?? null,
        sweepMode: info?.sweepMode ?? null,
        guardVersion: info?.guardVersion ?? null,
        safetyTable: { vwBuild: safetyTable.vwBuild, source: safetyTable.source,
          functions: Object.keys(safetyTable.functions).length, error: safetyTable.error },
        warning: mismatch ? `Vectorworks is ${info.vwBuild} but the safety table was swept on ${safetyTable.vwBuild}. ` +
          'Classes carry forward, but a function that changed in this build may behave differently; re-run the sweep.' : null,
        lastEvent,
        wsPort: WS_PORT,
        httpPort: HTTP_PORT,
        pendingCalls: pending.size,
      });
    },
  );

  return mcp;
}

// -----------------------------------------------------------------------------
// Boot — HTTP (default) or stdio (--stdio)
// -----------------------------------------------------------------------------
if (USE_STDIO) {
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
  app.get('/health', (req, res) => res.json({
    ok: true,
    paletteConnected: !!(palette && palette.readyState === palette.OPEN),
  }));

  app.listen(HTTP_PORT, '127.0.0.1', () => {
    log(`MCP server (Streamable HTTP) on http://127.0.0.1:${HTTP_PORT}/mcp`);
  });
}

const shutdown = () => { try { wss.close(); } catch {} process.exit(0); };
process.on('SIGINT', shutdown);
process.on('SIGTERM', shutdown);
