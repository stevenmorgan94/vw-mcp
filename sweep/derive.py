"""Derive the class table from a sweep log (spec §2/§5): class = worst valid outcome, argCheck = any bad case worse than an error.

  python3 derive.py <v0 log> <out.json> [<retest log>]
  python3 derive.py <v2 log> <out.json> --base <class-table.json>   (v2: overlay the new functions onto a table)

A retest log (sweep.mjs --retest) overrides v0 where v0's "valid" case was not really valid:
  typed        - v0 passed a handle of the wrong object type -> v0's valid outcomes become bad case 'wrong-object-type'
  inout-fixed  - v0 dropped an in-out VAR arg                -> v0's valid outcomes become bad case 'missing-inout-arg'
  paired       - v0 called a state-machine call unpaired     -> v0's valid outcomes become bad case 'unpaired'
  repro-*      - v0 crash case run again: sets 'reproduced' when it crashed again
Retest jobs the old text blocklist refused (all inline ones) are ignored.
A 'paired' case in the main log (v2) does the same within that log: paired becomes valid, unpaired becomes bad."""
import json, collections, sys
argv = sys.argv[1:]; base = None
if '--base' in argv: i = argv.index('--base'); base = argv[i + 1]; del argv[i:i + 2]
log = argv[0]; out = argv[1]; retest = argv[2] if len(argv) > 2 else None
last = {}; notes = collections.defaultdict(list)
for l in open(log):
    e = json.loads(l)
    if e['ev'] == 'outcome': last[e['key']] = e
    elif e['ev'] == 'note': notes[e['fn']].append(e)
rank = {'crash': 5, 'hang': 4, 'interactive': 3, 'busy': 0, 'document-level': 2, 'window': 2, 'ok': 0, 'error': 0, 'refused': -1, 'skipped': -2, 'bridge-error': -3}
cls = {0: 'safe', 2: 'document-level', 3: 'interactive', 4: 'hang', 5: 'crasher', -1: 'refused', -2: 'untested', -3: 'untested'}
fn = collections.defaultdict(lambda: {'valid': [], 'bad': []})
for e in last.values():
    fn[e['fn']]['valid' if e.get('case', 'valid') == 'valid' else 'bad'].append(e)
RENAME = {'typed': 'wrong-object-type', 'inout-fixed': 'missing-inout-arg', 'paired': 'unpaired'}
reproduced = collections.defaultdict(list); retested = set()
if retest:
    rt = {}
    for l in open(retest):
        e = json.loads(l)
        if e['ev'] == 'outcome': rt[e['key']] = e
        elif e['ev'] == 'note': notes[e['fn']].append(e)
    by = collections.defaultdict(list)
    for e in rt.values():
        if e['outcome'] in ('refused', 'skipped'): continue
        if e['case'].startswith('repro-'): reproduced[e['fn']].append(f"{e['case'][6:]}:{e['outcome']}")
        else: by[e['fn']].append(e)
    for f, es in by.items():
        d = fn[f]
        for e in d['valid']: d['bad'].append({**e, 'case': RENAME[es[0]['case']]})
        d['valid'] = [{**e, 'case': 'valid'} for e in es]; retested.add(f)
for f, d in fn.items():          # paired cases in the main log (v2)
    p = [e for e in d['bad'] if e.get('case') == 'paired' and e['outcome'] not in ('refused', 'skipped')]
    if p:
        d['bad'] = [e for e in d['bad'] if e.get('case') != 'paired'] + [{**e, 'case': 'unpaired'} for e in d['valid']]
        d['valid'] = [{**e, 'case': 'valid'} for e in p]
res = {}
for f, d in fn.items():
    v = max((rank[e['outcome']] for e in d['valid']), default=-2)
    dialogAfter = any('dialog' in (n.get('note') or '') for n in notes[f])
    if dialogAfter and v < 3: v = 3
    bad = [e for e in d['bad'] if rank[e['outcome']] > 0]
    res[f] = {'class': cls[v], 'argCheck': bool(bad) and v < 5,
              'badCases': sorted({f"{e['case']}:{e['outcome']}" for e in bad}),
              'valid': {e['ctx']: e['outcome'] for e in d['valid']},
              'dialogAfter': dialogAfter or None,
              'retest': sorted({e.get('case') for e in fn[f]['bad'] if e.get('case') in RENAME.values()}) or None if f in retested else None,
              'reproduced': reproduced.get(f) or None,
              'dialogText': next((e.get('dismiss') or e.get('dismissAfter') for e in d['valid'] + d['bad'] if e.get('dismiss') or e.get('dismissAfter')), None)}
harness = 'v0 (tiers 1-3, blocklist on)' + (' + v1 retest (typed fixtures, in-out args, paired calls)' if retest else '')
if base:
    b = json.load(open(base))
    res = {**b['functions'], **{f: dict(r, sweep='v2') for f, r in res.items()}}
    harness = b['harness'] + ' + v2 (functions v0/v1 never ran, guard off)'
json.dump({'vwBuild': '32.0.0 (882075)', 'engine': 'ctx', 'harness': harness, 'functions': res}, open(out, 'w'), indent=1, sort_keys=True)
c = collections.Counter(r['class'] for r in res.values())
print(len(res), 'functions', dict(c), '| argCheck', sum(r['argCheck'] for r in res.values()))
diff = sorted(f for f, r in res.items() if len(set(r['valid'].values()) - {'skipped'}) > 1)
print('context differs:', diff)
for k in ['crasher', 'hang', 'interactive', 'document-level', 'refused']:
    L = sorted(f for f, r in res.items() if r['class'] == k); print(f'\n{k} ({len(L)}):', ', '.join(L))
A = sorted(f for f, r in res.items() if r['argCheck'] and r['class'] == 'safe')
print(f'\nsafe + argCheck ({len(A)}):', ', '.join(f"{f}[{'/'.join(sorted({c.split(':')[1] for c in res[f]['badCases']}))}]" for f in A))
