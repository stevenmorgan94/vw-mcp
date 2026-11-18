import json
P = __TAG__
made = []
for i in range(2):
    vs.CreateCustomObjectN('Stage Deck', (i * 1500, 6000 + 3000 * len(P)), 0, False)
    h = vs.LNewObj()
    vs.SetName(h, P + '-%d' % i)
    vs.SetFPat(h, 1); vs.SetFillFore(h, 65535, 0, 0); vs.SetFillBack(h, 65535, 0, 0)
    vs.ResetObject(h)
    made.append(vs.GetName(h))
print(json.dumps(made))
