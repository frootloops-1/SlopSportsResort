#!/usr/bin/env python3
"""Relink; for each undefined label that lives in a data section, remove the data ranges added since
BASE_SPLITS that sit immediately before/after its address in that section. Repeat.
Usage: link_fix.py BASE_SPLITS [rounds]"""
import re, subprocess, sys
sys.path.insert(0, 'tools')
from apply_ogws import parse_splits
from sig_match import symbols
base = parse_splits(sys.argv[1]); rounds = int(sys.argv[2]) if len(sys.argv) > 2 else 20
P = 'config/RZTE01_01/splits.txt'
LINK = 'build/tools/wibo build/compilers/Wii/1.0/mwldeppc.exe -fp hardware -nodefaults -lcf build/RZTE01_01/ldscript.lcf -o build/RZTE01_01/main.elf @build/RZTE01_01/main.elf.rsp'
for r in range(rounds):
    subprocess.run('ninja build/RZTE01_01/config.json >/dev/null 2>&1; ninja -k 0 build/RZTE01_01/main.elf >/dev/null 2>&1', shell=True)
    out = subprocess.run(LINK, shell=True, capture_output=True, text=True).stdout
    und = set(re.findall(r"undefined: '(\S+)'", out))
    if not und: print(f'round {r}: links'); break
    addr = {s['name']: (s['sec'], s['addr']) for s in symbols('config/RZTE01_01/symbols.txt')}
    sp = parse_splits(P)
    victims = set()
    for n in und:
        if n not in addr: continue
        sec, a = addr[n]
        before = max(((e, u, (sec, s0, e)) for u, v in sp.items() for (sc, s0, e) in v if sc == sec and e <= a), default=None)
        after = min(((s0, u, (sec, s0, e)) for u, v in sp.items() for (sc, s0, e) in v if sc == sec and s0 > a), default=None)
        for x in (before, after):
            if x and x[2] not in base.get(x[1], []): victims.add((x[1], x[2]))
    if not victims: print(f'round {r}: {len(und)} undefined, nothing droppable: {sorted(und)[:5]}'); break
    L = open(P).read().split('\n'); cur = None; keep = []
    for l in L:
        if l and not l.startswith('\t') and l.endswith(':'): cur = l[:-1]
        m = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)', l)
        if m and (cur, (m.group(1), int(m.group(2), 16), int(m.group(3), 16))) in victims: continue
        keep.append(l)
    open(P, 'w').write('\n'.join(keep)); print(f'round {r}: {len(und)} undefined, dropped {len(victims)} ranges')
