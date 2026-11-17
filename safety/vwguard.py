# vwguard - the in-engine safety layer for Python sent to Vectorworks over MCP.
# docs/MCP_HARDENING_SPEC.md §2-3. Installed by the bridge as sys.modules['_vwmcp_guard'] and used as:
#     _vwmcp_guard.load(table_json, override_json_or_None)
#     _vwmcp_guard.run(code, {'allowDocumentLevel': bool, 'allowUnclassified': bool, 'timeoutSec': float})
# The job sees a guarded view of `vs` (also through `import vs`, `from vs import X` and getattr), so
# every vs.* call is checked against the safety table before it reaches Vectorworks. The real vs
# module is never modified: the user's own Run Script commands keep the unguarded one.
# The result goes back as one stdout line starting with MARKER, holding JSON.
import ast
import ctypes
import json
import sys
import threading
import types

VERSION = 7
MARKER = '\x1eVWGUARD '
REFUSE_CLASSES = ('crasher', 'hang', 'interactive', 'event-only')
REASONS = {
    'crasher': 'crashes Vectorworks',
    'hang': 'hangs Vectorworks',
    'interactive': 'opens a dialog or waits for user input, which a remote client cannot answer',
    'document-level': 'opens, closes or replaces a document or window',
    'event-only': 'only works inside a plug-in object or tool event handler, which a remote script is not',
    'unclassified': 'has not been safety-tested',
}

_table = {}
_pairs = {}
_ends = {}
_meta = {}


def load(table_json, override_json=None):
    global _table, _pairs, _ends, _meta
    t = json.loads(table_json)
    fns = dict(t.get('functions', {}))
    if override_json:
        for name, e in json.loads(override_json).get('functions', {}).items():
            fns[name] = dict(e, overridden=True)
    _table = fns
    _pairs = dict(t.get('pairs', {}))
    _ends = {}
    for b, e in _pairs.items():
        _ends.setdefault(e, set()).add(b)
    _meta = {k: t.get(k) for k in ('vwBuild', 'engine', 'source', 'schema')}
    _meta['functions'] = len(fns)
    _meta['overrides'] = sum(1 for e in fns.values() if e.get('overridden'))


# ---- plug-in objects to rebuild after the job (#25) ----------------------------------
# A plug-in object (PIO) changed by a script keeps its old 2D/3D until vs.ResetObject, and a reset
# in the job that created it does nothing. The guard records every PIO a job creates or passes to a
# call that may change it; the bridge resets them once the script has finished.
PIO_TYPE = 86
MAX_TOUCHED = 2000      # ~15 ms each to rebuild: about 30 s at the cap
# Calls that only read: a PIO passed to or returned by these is not recorded.
READ_PREFIXES = ('Get', 'Is', 'Num', 'Count', 'Find', 'Has', 'Eval', 'Next', 'Prev', 'FIn', 'LIn',
                 'FS', 'LS', 'FAct', 'LAct', 'FLayer', 'LLayer', 'LNewObj', 'ActLayer', 'Obj', 'ForEach',
                 'Calc', 'Search', 'ResetObject')


def _is_reader(name):
    return name.startswith(READ_PREFIXES)


class Refused(Exception):
    """A vs.* call the safety table does not allow. Raised before the call reaches Vectorworks."""
    def __init__(self, info):
        Exception.__init__(self, info['reason'])
        self.info = info


class ScriptTimeout(Exception):
    pass


def classify(name):
    e = _table.get(name)
    return (e['class'], e) if e else ('unclassified', {})


def refusal_for(name, opts):
    """None if vs.<name> may run, else the refusal body (spec §4)."""
    cls, e = classify(name)
    if cls == 'safe' or e.get('reroute'):
        return None
    if cls == 'document-level' and opts.get('allowDocumentLevel'):
        return None
    if cls == 'unclassified' and opts.get('allowUnclassified'):
        return None
    info = {'refused': True, 'function': name, 'class': cls,
            'reason': 'vs.%s %s%s.' % (name, REASONS.get(cls, 'is not allowed'),
                                       ' (classified by its category; the sweep does not run these)' if e.get('basis') == 'category' else ''),
            'alternative': e.get('alternative')}
    if cls == 'document-level':
        info['advice'] = 'Set allowDocumentLevel: true to run it anyway.'
    elif cls == 'unclassified':
        info['advice'] = 'Set allowUnclassified: true to run it anyway (at your own risk).'
    if e.get('overridden'):
        info['overridden'] = True
    return info


# ---- argument checks (spec §3 argCheck) ----------------------------------------------
_HANDLE_TYPE = None


def _is_handle(v):
    return _HANDLE_TYPE is not None and isinstance(v, _HANDLE_TYPE)


def _num(v):
    return isinstance(v, (int, float))


def check_args(name, spec, args, kwargs, real):
    where = 'vs.%s(%s)' % (name, ', '.join(a[0] for a in spec))
    if kwargs:
        raise TypeError('%s takes positional arguments only' % where)
    if len(args) != len(spec):
        raise TypeError('%s takes %d argument%s, got %d' % (where, len(spec), '' if len(spec) == 1 else 's', len(args)))
    for i, (a, v) in enumerate(zip(spec, args)):
        arg, kind = a[0], a[1]
        bad = None
        if kind == 'h':
            if v is None or v == 0 or not _is_handle(v):
                bad = 'a valid handle' if v is None or v == 0 else 'a handle'
            elif len(a) > 2:
                rule = a[2]
                t = real.GetTypeN(v)
                if t not in rule['types']:
                    raise TypeError('%s: %s must be %s, got an object of type %d' % (where, arg, _rule_text(rule), t))
                if rule.get('pio') and t == 86:
                    pn = real.GetName(real.GetParametricRecord(v))
                    if pn != rule['pio']:
                        raise TypeError('%s: %s must be a %s object, got a %s object' % (where, arg, rule['pio'], pn or 'plug-in'))
        elif kind == 'r' and not _num(v):
            bad = 'a number'
        elif kind == 'i' and not (isinstance(v, int) or (isinstance(v, float) and v.is_integer())):
            bad = 'an integer'
        elif kind == 'b' and not isinstance(v, (bool, int)):
            bad = 'a bool'
        elif kind == 's' and not isinstance(v, str):
            bad = 'a string'
        elif kind == 'p' and not (isinstance(v, (tuple, list)) and len(v) in (2, 3) and all(_num(c) for c in v)):
            bad = 'a point tuple (x, y)'
        if bad:
            raise TypeError('%s: %s must be %s, got %r' % (where, arg, bad, v))


def _rule_text(rule):
    if rule.get('pio'):
        return 'a %s object' % rule['pio']
    return 'an object of type %s' % ' or '.join(str(t) for t in rule['types'])


# ---- one job ------------------------------------------------------------------------
class _Job:
    def __init__(self, real, opts):
        self.real = real
        self.opts = opts
        self.calls = 0
        self.refusals = []
        self.rerouted = []
        self.open = []          # stack of open Begin* names
        self.auto_closed = []
        self.cache = {}
        self.touched = {}       # uuid -> None, insertion-ordered: PIOs to reset after the job
        self.touched_over = 0   # PIOs past MAX_TOUCHED, not reset

    def touch(self, h):
        if not _is_handle(h):
            return
        try:
            if self.real.GetTypeN(h) == PIO_TYPE:
                u = self.real.GetObjectUuid(h)
                if u and u not in self.touched:
                    if len(self.touched) >= MAX_TOUCHED:
                        self.touched_over += 1
                    else:
                        self.touched[u] = None
        except Exception:
            pass

    def wrap(self, name, fn):
        w = self.cache.get(name)
        if w:
            return w
        job = self
        info = refusal_for(name, self.opts)
        cls, e = classify(name)
        spec = e.get('args')
        reroute = e.get('reroute')

        def guarded(*args, **kwargs):
            if info:
                body = dict(info, partialChanges=job.calls > 0)
                if job.calls > 0:
                    body['advice'] = (body.get('advice', '') + ' Earlier calls in this job already ran; '
                                      'Edit > Undo reverts the whole job in one step.').strip()
                job.refusals.append(body)
                raise Refused(body)
            if reroute == 'upper':
                job.rerouted.append({'function': name, 'to': "str.upper()"})
                if len(args) != 1 or kwargs or not isinstance(args[0], str):
                    raise TypeError('vs.%s(str) takes one string' % name)
                return args[0].upper()
            if spec is not None:
                check_args(name, spec, args, kwargs, job.real)
            if name in _ends:
                if not job.open or job.open[-1] not in _ends[name]:
                    body = {'refused': True, 'function': name, 'class': 'sequence',
                            'reason': 'vs.%s() with no matching %s open crashes Vectorworks.'
                                      % (name, ' / '.join(sorted(_ends[name]))),
                            'alternative': None, 'partialChanges': job.calls > 0,
                            'advice': 'Call %s() first.' % sorted(_ends[name])[0]
                                      + (' Earlier calls in this job already ran; Edit > Undo reverts the whole job in one step.'
                                         if job.calls > 0 else '')}
                    job.refusals.append(body)
                    raise Refused(body)
            job.calls += 1
            track = not _is_reader(name)
            if track:   # before the call: a handle may be gone after it (DelObject)
                for a in args:
                    job.touch(a)
            r = fn(*args, **kwargs)
            if track:
                job.touch(r)
            if name in _pairs:
                job.open.append(name)
            elif name in _ends:
                job.open.pop()
            return r

        guarded.__name__ = name
        guarded.__doc__ = getattr(fn, '__doc__', None)
        self.cache[name] = guarded
        return guarded

    def close_open(self):
        # A Begin* left open when the script ends crashes VW (BeginPoly): close it with its End*.
        while self.open:
            b = self.open.pop()
            end = _pairs[b]
            try:
                getattr(self.real, end)()
                self.auto_closed.append({'begin': b, 'closedWith': end})
            except Exception as ex:
                self.auto_closed.append({'begin': b, 'closedWith': end, 'error': repr(ex)})


def _make_proxy(job):
    real = job.real

    class GuardedVs(types.ModuleType):
        def __getattr__(self, name):
            v = getattr(real, name)
            if name.startswith('_') or not callable(v) or isinstance(v, type):
                return v
            return job.wrap(name, v)

        def __dir__(self):
            return dir(real)

    m = GuardedVs('vs')
    m.__doc__ = real.__doc__
    return m


def precheck(code, opts):
    """Refuse the whole script before it runs when a refused vs.* name is visible in its text."""
    try:
        tree = ast.parse(code)
    except SyntaxError:
        return None                       # let it run so the caller sees the normal SyntaxError
    aliases, names = set(), []
    for n in ast.walk(tree):
        if isinstance(n, ast.Import):
            for a in n.names:
                if a.name == 'vs':
                    aliases.add(a.asname or 'vs')
        elif isinstance(n, ast.ImportFrom) and n.module == 'vs':
            names += [a.name for a in n.names if a.name != '*']
    aliases.add('vs')
    for n in ast.walk(tree):
        if isinstance(n, ast.Attribute) and isinstance(n.value, ast.Name) and n.value.id in aliases:
            names.append(n.attr)
        elif (isinstance(n, ast.Call) and isinstance(n.func, ast.Name) and n.func.id == 'getattr' and len(n.args) >= 2
              and isinstance(n.args[0], ast.Name) and n.args[0].id in aliases
              and isinstance(n.args[1], ast.Constant) and isinstance(n.args[1].value, str)):
            names.append(n.args[1].value)
    import vs as real
    for name in names:
        if name.startswith('_') or not callable(getattr(real, name, None)):
            continue
        info = refusal_for(name, opts)
        if info:
            return dict(info, partialChanges=False, stage='precheck')
    return None


def _arm_timeout(seconds):
    if not seconds or seconds <= 0:
        return None
    tid = threading.get_ident()

    def fire():
        ctypes.pythonapi.PyThreadState_SetAsyncExc(ctypes.c_ulong(tid), ctypes.py_object(ScriptTimeout))
    t = threading.Timer(seconds, fire)
    t.daemon = True
    t.start()
    return t


def _emit(d):
    sys.stdout.write('\n' + MARKER + json.dumps(d) + '\n')


def run(code, opts):
    global _HANDLE_TYPE
    import vs as real
    if _HANDLE_TYPE is None:
        try:
            _HANDLE_TYPE = type(real.Handle(0)) if hasattr(real, 'Handle') else type(real.ActLayer())
        except Exception:
            _HANDLE_TYPE = type(real.ActLayer())
    report = {'guard': VERSION, 'table': _meta}
    pre = precheck(code, opts)
    if pre:
        report['refusal'] = pre
        _emit(report)
        return
    job = _Job(real, opts)
    proxy = _make_proxy(job)
    saved = sys.modules.get('vs')
    sys.modules['vs'] = proxy
    g = {'__name__': '__main__', '__builtins__': __builtins__, 'vs': proxy}
    timer = None
    try:
        timer = _arm_timeout(opts.get('timeoutSec'))
        exec(compile(code, '<mcp>', 'exec'), g)
    except Refused:
        pass                                  # reported below from job.refusals
    except ScriptTimeout:
        report['timeout'] = {'seconds': opts.get('timeoutSec'), 'partialChanges': job.calls > 0,
                             'advice': 'The script was stopped. Edit > Undo reverts the whole job in one step.'}
    finally:
        if timer:
            timer.cancel()
        sys.modules['vs'] = saved
        job.close_open()
        report['calls'] = job.calls
        if job.touched:
            report['touchedPio'] = list(job.touched)
        if job.touched_over:
            report['touchedPioSkipped'] = job.touched_over
        if job.refusals:
            report['refusal'] = job.refusals[0]
            if len(job.refusals) > 1:
                report['moreRefusals'] = len(job.refusals) - 1
        if job.rerouted:
            report['rerouted'] = job.rerouted
        if job.auto_closed:
            report['autoClosed'] = job.auto_closed
        _emit(report)
