import json
out = {}
def kids(h):
    r = []; c = vs.FInGroup(h)
    while c:
        r.append([vs.GetTypeN(c), vs.GetFPat(c), vs.GetFillFore(c)]); c = vs.NextObj(c)
    return r
for n in __NAMES__:
    h = vs.GetObject(n)
    out[n] = kids(h) if h else None
print(json.dumps(out))
