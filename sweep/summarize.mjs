// Summarise a sweep log: outcome counts per case kind, then every non-ok/non-error job.
import fs from 'node:fs';
const last = new Map();
for (const l of fs.readFileSync(process.argv[2], 'utf8').split('\n')) { if (!l) continue; const e = JSON.parse(l); if (e.ev === 'outcome') last.set(e.key, e); }
const byCase = {}; const notable = [];
for (const e of last.values()) {
  const k = e.case === 'valid' || !e.case ? `valid/${e.ctx}` : 'bad'; (byCase[k] ??= {})[e.outcome] = (byCase[k][e.outcome] ?? 0) + 1;
  if (!['ok', 'error'].includes(e.outcome)) notable.push(e);
}
console.log(`# Sweep v0 summary\n\n${last.size} jobs with an outcome.\n\n| cases | outcomes |\n|---|---|`);
for (const [k, v] of Object.entries(byCase)) console.log(`| ${k} | ${Object.entries(v).map(([o, n]) => `${o} ${n}`).join(', ')} |`);
console.log(`\n## Notable outcomes (${notable.length})\n`);
for (const o of ['crash', 'hang', 'interactive', 'document-level', 'window', 'refused', 'bridge-error'])
  for (const e of notable.filter((x) => x.outcome === o))
    console.log(`- **${o}** \`${e.key}\`${e.ips ? ` (${e.ips})` : ''}${e.modal ? ` modal ${JSON.stringify(e.modal)}` : ''}${e.newWindows ? ` windows ${JSON.stringify(e.newWindows)}` : ''}${e.note ? ` — ${e.note}` : ''}`);
