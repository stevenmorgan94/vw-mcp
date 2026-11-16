"""Build the vs safety table the bridge enforces (docs/MCP_HARDENING_SPEC.md §2-3).

  python3 safety/build_table.py

Inputs:  docs/sweep/class-table-v2.json  (the sweep's derive step: class + argCheck per function; v1 if no v2)
         safety/functions.csv             (Python + VectorScript signatures)
Outputs: safety/vs-safety-table.json                   (the table; also read by the relay's vw_lookup_function)
         plugin/src/safety/VsSafety.generated.inc      (the table + vwguard.py as C++ string literals)

Nothing here is specific to any one plug-in: the guard and table were carried over unchanged from the original bridge.
"""
import csv, json, re, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
CLASS_TABLE = next(p for p in (ROOT / 'docs/sweep/class-table-v2.json', ROOT / 'docs/sweep/class-table-v1.json') if p.exists())
FUNCTIONS = HERE / 'functions.csv'
OUT_JSON = HERE / 'vs-safety-table.json'
OUT_INC = ROOT / 'plugin/src/safety/VsSafety.generated.inc'
ISDK_DISPATCH = ROOT / 'plugin/src/nativeops/IsdkDispatch.inc'
GUARD = HERE / 'vwguard.py'

# Node types (SDK MiniCadHookIntf.h). Each rule = allowed GetTypeN values, plus a plug-in object name for type 86.
WALLISH = [68, 89, 71, 83]                 # wall, round wall, slab, roof container: the objects with components
LDEV = {'types': [86], 'pio': 'Lighting Device'}
SYMDEF = {'types': [16]}
# fn-name regex -> rule per HANDLE argument, in order. From the v1 retest's typed fixtures (docs/sweep/README.md).
HANDLE_RULES = [
    (r'Gradient', [{'types': [120]}]),
    (r'^LDevice_AddAccessory$', [LDEV, SYMDEF]),
    (r'^(LDevice_|OLDGetHangingPos$)', [LDEV]),
    (r'^ApplyLightInfoRecord$', [SYMDEF, LDEV]),
    (r'^(SetLightDirection|SetSpreadAngle)$', [{'types': [81]}]),
    (r'RoofAttributes$', [{'types': [83]}]),
    (r'^GetWallThickness$', [{'types': [68, 89]}]),
    (r'^(GetComponents|GetDisplayWith2DComp|SetDisplayWith2DComp)$', [{'types': WALLISH}]),
    (r'VPLrOvrd', [{'types': [122]}, {'types': [31]}]),
    (r'SheetLayerUserOrigin$', [{'types': [31]}]),
]
# Begin*/End* state machines: an End with no open Begin crashes (EndSym), and so does a script that
# ends with a Begin still open (BeginPoly). The guard refuses the first and closes the second.
PAIRS = {
    'BeginContext': 'EndContext', 'BeginFolder': 'EndFolder', 'BeginFolderN': 'EndFolder',
    'BeginGroup': 'EndGroup', 'BeginGroupN': 'EndGroup', 'BeginMesh': 'EndMesh',
    'BeginMultipleDuplicate': 'EndMultipleDuplicate', 'BeginMXtrd': 'EndMXtrd', 'BeginPoly': 'EndPoly',
    'BeginPoly3D': 'EndPoly3D', 'BeginSweep': 'EndSweep', 'BeginSym': 'EndSym', 'BeginText': 'EndText',
    'BeginVectorFillN': 'EndVectorFill', 'BeginXtrd': 'EndXtrd',
}
# Crashers with an exact, tested replacement. Python-side reroutes only; native-op reroutes come with run_native_op.
REROUTES = {'UprString': 'upper'}
# Functions the sweep deliberately never runs, classified by category instead (basis 'category').
# Anything else the sweep didn't run (file I/O, Excel, XML, workspaces, printing) stays unclassified.
def category_class(f):
    if re.match(r'(Dialogs|User Interactive)', f['category']) or f['event_context'] == 'dialog-handler': return 'interactive'
    if f['event_context'] or re.match(r'(Object|Tool) Events', f['category']): return 'event-only'
    return None
ALTERNATIVES = {
    'UprString': "Python's str.upper()",
    'Ord': "Python's ord()",
}


def kind_of(t):
    t = t.upper()
    if 'HANDLE' in t: return 'h'
    if 'BOOL' in t: return 'b'
    if re.search(r'REAL|DISTANCE|COORD', t): return 'r'
    if re.search(r'INT|LONG|LNG', t): return 'i'
    if re.search(r'STR|CHAR', t): return 's'
    if re.search(r'VECTOR|POINT', t): return 'p'
    return 'x'


def vs_params(sig):
    m = re.search(r'\((.*)\)', sig)
    out = {}
    if not m: return out
    for grp in m.group(1).split(';'):
        if ':' not in grp: continue
        names, typ = grp.split(':', 1)
        for n in re.sub(r'^\s*VAR\s+', '', names, flags=re.I).split(','):
            out[n.strip()] = typ.strip()
    return out


def py_args(sig):
    m = re.search(r'vs\.\w+\((.*)\)\s*$', sig)
    if not m: return None
    return [s.strip() for s in m.group(1).split(',')] if m.group(1).strip() else []


def arg_spec(f, name):
    py = py_args(f['python_signature'])
    if py is None: return None
    vs = vs_params(f['vectorscript_signature'])
    rules = next((r for rx, r in HANDLE_RULES if re.search(rx, name)), [])
    spec, hi = [], 0
    for a in py:
        if a in vs: k = kind_of(vs[a])
        elif a + 'X' in vs: k = 'p'        # Python point p <- VectorScript pX, pY
        else: k = 'x'
        entry = [a, k]
        if k == 'h':
            if hi < len(rules): entry.append(rules[hi])
            hi += 1
        spec.append(entry)
    return spec


RANK = ['crasher', 'hang', 'interactive', 'event-only', 'document-level', 'safe']


def isdk_classes(out, fns):
    """run_native_op's `call` op (#11): each ISDK method in the dispatch takes the class of its vs.* twin
    (functions.csv native_dispatch; the worst class when several vs functions share one method).
    Methods with no classified twin are left out, so the plug-in treats them as unclassified."""
    names = set(re.findall(r'^\s*\{\s*"(\w+)",\s*\[\]', ISDK_DISPATCH.read_text(), re.M))
    twins = {}
    for f in fns.values():
        if f.get('native_dispatch') and f['name'] in out:
            twins.setdefault(f['native_dispatch'], []).append(f['name'])
    res = {}
    for n in sorted(names):
        vs = twins.get(n)
        if not vs: continue
        worst = min(vs, key=lambda v: RANK.index(out[v]['class']))
        res[n] = {'class': out[worst]['class'], 'via': worst}
    return res, len(names)


def main():
    ct = json.loads(CLASS_TABLE.read_text())
    fns = {r['name']: r for r in csv.DictReader(FUNCTIONS.open())}
    out = {}
    for name, r in sorted(ct['functions'].items()):
        cls = r['class']
        if cls not in ('safe', 'crasher', 'hang', 'interactive', 'document-level'):
            continue                                   # 'refused'/'untested': no evidence -> unclassified
        e = {'class': cls}
        if r['argCheck'] and cls == 'safe':
            spec = arg_spec(fns[name], name) if name in fns else None
            if spec is None:
                print(f'warning: {name} has argCheck but no Python signature', file=sys.stderr)
            else:
                e['args'] = spec
        if name in REROUTES: e['reroute'] = REROUTES[name]
        if name in ALTERNATIVES: e['alternative'] = ALTERNATIVES[name]
        out[name] = e
    for name, f in fns.items():
        if name in out or f['in_vs_py'] != '1' or f['kind'] == 'CONSTANT': continue
        c = category_class(f)
        if c: out[name] = {'class': c, 'basis': 'category'}
    isdk, isdk_total = isdk_classes(out, fns)
    table = {
        'schema': 1,
        'vwBuild': ct.get('vwBuild'),
        'engine': ct.get('engine'),
        'source': ct.get('harness'),
        'pairs': PAIRS,
        'isdk': isdk,
        'functions': out,
    }
    OUT_JSON.write_text(json.dumps(table, indent=0, sort_keys=True) + '\n')
    compact = json.dumps(table, separators=(',', ':'), sort_keys=True)
    guard = GUARD.read_text()
    delim = 'VWSAFETY'
    assert f'){delim}"' not in compact + guard
    OUT_INC.parent.mkdir(parents=True, exist_ok=True)
    OUT_INC.write_text(
        '// GENERATED by safety/build_table.py - do not edit.\n'
        '// The vs safety table (from the sweep) and the in-engine guard that enforces it.\n'
        f'static const char* kVsSafetyTable = R"{delim}({compact}){delim}";\n'
        f'static const char* kVsGuardSource = R"{delim}({guard}){delim}";\n')
    from collections import Counter
    c = Counter(e['class'] for e in out.values())
    ic = Counter(e['class'] for e in isdk.values())
    print(f'isdk call: {len(isdk)} of {isdk_total} dispatch methods classified via a vs twin {dict(ic)}')
    print(f'{len(out)} functions {dict(c)}; with arg specs {sum("args" in e for e in out.values())}; '
          f'{len(compact) // 1024} KB -> {OUT_JSON.relative_to(ROOT)}, {OUT_INC.relative_to(ROOT)}')


if __name__ == '__main__':
    main()
