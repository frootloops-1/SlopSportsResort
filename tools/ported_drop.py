#!/usr/bin/env python3
"""Remove units from ported_objects.json and restore their pre-flip split entries.
Usage: ported_drop.py CONFIG_DIR PRE_FLIP_SPLITS UNIT..."""
import json, re, sys
cfg, pre, units = sys.argv[1], sys.argv[2], set(sys.argv[3:])
pj = f'{cfg}/ported_objects.json'
d = json.load(open(pj)); keep = [x for x in d if x['name'] not in units]; json.dump(keep, open(pj, 'w'), indent=1)
old, cur = open(pre).read(), open(f'{cfg}/splits.txt').read()
for u in units:
    pat = rf'(?m)^{re.escape(u)}:\n(\t.*\n)+'
    a, b = re.search(pat, old), re.search(pat, cur)
    if a and b: cur = cur.replace(b.group(0), a.group(0))
open(f'{cfg}/splits.txt', 'w').write(cur)
print(f'dropped {len(d) - len(keep)}, {len(keep)} remain')
