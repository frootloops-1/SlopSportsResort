#!/usr/bin/env python3
"""report_cmp.py BEFORE.json AFTER.json : list every function whose fuzzy% went down, units whose
complete_code dropped, and summary. Exit 1 if anything went down. Functions are keyed by (unit, name);
a function that vanished from a unit counts as down unless it reappears under the same name in another unit
or under a new name at the same address (a rename)."""
import json, sys
def load(p):
    r = json.load(open(p)); fns = {}; units = {}; byname = {}; byaddr = {}
    for u in r['units']:
        m = u.get('measures', {})
        units[u['name']] = (float(m.get('fuzzy_match_percent', 0) or 0), int(m.get('complete_code', 0) or 0))
        for f in u.get('functions', []):
            v = float(f.get('fuzzy_match_percent', 0) or 0)
            fns[(u['name'], f['name'])] = v; byname[f['name']] = max(v, byname.get(f['name'], 0))
            a = (f.get('metadata') or {}).get('virtual_address')
            if a: byaddr[a] = max(v, byaddr.get(a, 0)); addr_of[(u['name'], f['name'])] = a
    return r, fns, units, byname, byaddr
addr_of = {}
_, bf, bu, bn, ba = load(sys.argv[1]); ar, af, au, an, aa = load(sys.argv[2])
down = []
for k, v in bf.items():
    if k in af: nv = af[k]
    else: nv = an.get(k[1], aa.get(addr_of.get(k), None))  # moved unit, or renamed (same address)
    if nv is None: down.append((k, v, 'MISSING'))
    elif nv + 1e-6 < v: down.append((k, v, nv))
up = sum(1 for k, v in af.items() if v > bf.get(k, bn.get(k[1], 0)) + 1e-6)
ex_b = sum(1 for v in bf.values() if v == 100); ex_a = sum(1 for v in af.values() if v == 100)
cdown = [(u, bu[u][1], au.get(u, (0, 0))[1]) for u in bu if au.get(u, (0, 0))[1] < bu[u][1]]
for k, v, nv in down[:60]: print(f"DOWN {k[0]} {k[1]}: {v:.2f} -> {nv}")
for u, a, b in cdown: print(f"COMPLETE DOWN {u}: {a} -> {b}")
m = ar.get('measures', {})
print(f"functions down: {len(down)}, up: {up}, exact {ex_b} -> {ex_a}; complete_code {m.get('complete_code')} ({m.get('complete_code_percent')}%)")
sys.exit(1 if down or cdown else 0)
