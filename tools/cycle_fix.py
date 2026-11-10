#!/usr/bin/env python3
"""Run `dtk dol split` and, while it reports a link-order cycle, remove the data ranges that were
added since BASE_SPLITS from the units named in the cycle. Usage: cycle_fix.py BASE_SPLITS [rounds]"""
import re, subprocess, sys
sys.path.insert(0, 'tools')
from apply_ogws import parse_splits
base = parse_splits(sys.argv[1]); rounds = int(sys.argv[2]) if len(sys.argv) > 2 else 60
P = 'config/RZTE01_01/splits.txt'
for r in range(rounds):
    out = subprocess.run('build/tools/dtk dol split config/RZTE01_01/config.yml build/RZTE01_01 2>&1', shell=True, capture_output=True, text=True).stdout
    g = re.search(r'Unsplit data in (\S+) from (\S+) \d+:0x(\w+) to next split \d+:0x(\w+)', out)
    if g:
        sec, unit, a, b = g.group(1), g.group(2), int(g.group(3), 16), int(g.group(4), 16)
        txt = open(P).read()
        pat = re.compile(rf'(?m)^({re.escape(unit)}:\n(?:\t.*\n)*?\t{re.escape(sec)}\s+start:0x\w+ end:0x){a:08X}')
        if pat.search(txt):
            open(P, 'w').write(pat.sub(lambda mm: mm.group(1) + f'{b:08X}', txt, count=1)); print(f'round {r}: extended {unit} {sec} to {b:#x}'); continue
        print(f'round {r}: cannot extend {unit} {sec}'); break
    m = re.search(r'Cyclic dependency encountered while resolving link order: (.*)', out)
    if not m:
        err = re.search(r'Caused by:\s*\n\s*(.*)', out)
        print(f'round {r}: ' + ('split OK' if not err else 'other error: ' + err.group(1))); break
    names = [n.strip() for n in m.group(1).split('->') if not n.strip().startswith('auto_')]
    lines = open(P).read().split('\n'); cur = None; out_l = []; dropped = 0
    for l in lines:
        if l and not l.startswith('\t') and l.endswith(':'): cur = l[:-1]
        mm = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)', l)
        if mm and cur in names and mm.group(1) != '.text':
            t = (mm.group(1), int(mm.group(2), 16), int(mm.group(3), 16))
            if t not in base.get(cur, []): dropped += 1; continue
        out_l.append(l)
    open(P, 'w').write('\n'.join(out_l))
    print(f'round {r}: cycle over {len(names)} units, dropped {dropped} added ranges')
    if not dropped: print('nothing droppable; stopping'); break
