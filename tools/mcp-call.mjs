#!/usr/bin/env node
// Call one vw-mcp tool the way an AI client does: spawn the relay over stdio and print the result.
//   node tools/mcp-call.mjs <tool> '<json args>'      e.g.  node tools/mcp-call.mjs vw_bridge_status '{}'
//   node tools/mcp-call.mjs execute_script --file script.py [--opts '{"timeoutSec":5}']
// Needs `npm ci` in relay/ first.
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { Client } from '../relay/node_modules/@modelcontextprotocol/sdk/dist/esm/client/index.js';
import { StdioClientTransport } from '../relay/node_modules/@modelcontextprotocol/sdk/dist/esm/client/stdio.js';

const HERE = path.dirname(fileURLToPath(import.meta.url));
const [tool, ...rest] = process.argv.slice(2);
if (!tool) { console.error('usage: mcp-call.mjs <tool> <json> | execute_script --file f.py [--opts json]'); process.exit(2); }
let args;
if (rest[0] === '--file') {
  const oi = rest.indexOf('--opts');
  args = { code: fs.readFileSync(rest[1], 'utf8'), ...(oi > 0 ? JSON.parse(rest[oi + 1]) : {}) };
} else args = JSON.parse(rest[0] || '{}');

const client = new Client({ name: 'vw-mcp-test', version: '0.0.1' });
await client.connect(new StdioClientTransport({ command: process.execPath, args: [path.join(HERE, '../relay/server.mjs')], stderr: 'inherit' }));
const t0 = Date.now();
const r = await client.callTool({ name: tool, arguments: args }, undefined, { timeout: 400000 });
console.log(JSON.stringify({ ms: Date.now() - t0, isError: !!r.isError, text: r.content?.map((c) => c.text).join('\n') }));
await client.close();
