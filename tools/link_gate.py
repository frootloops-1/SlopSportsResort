#!/usr/bin/env python3
"""Link, attribute every linker error to a ported unit, drop those units, repeat until it links.
Attribution: multiply-defined X -> the ported unit whose object defines X; undefined L referenced
from an auto/asm unit -> the ported unit whose split range contains L; undefined referenced from a
ported object -> that unit. Usage: link_gate.py PRE_FLIP_SPLITS"""
import json, re, subprocess, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
from apply_ogws import parse_splits
CFG = 'config/RZTE01_01'; PJ = f'{CFG}/ported_objects.json'
LINK = 'build/tools/wibo build/compilers/Wii/1.0/mwldeppc.exe -fp hardware -nodefaults -lcf build/RZTE01_01/ldscript.lcf -o build/RZTE01_01/main.elf @build/RZTE01_01/main.elf.rsp'
pre = sys.argv[1]
for rnd in range(10):
    subprocess.run('python3 configure.py >/dev/null 2>&1; touch config/RZTE01_01/config.yml; ninja build/RZTE01_01/config.json >/dev/null 2>&1; ninja -k 0 build/RZTE01_01/main.elf >/dev/null 2>&1', shell=True)
    out = subprocess.run(LINK, shell=True, capture_output=True, text=True).stdout
    ported = {p['name'] for p in json.load(open(PJ))}
    base = {re.sub(r'\.(c|cpp)$', '', u).split('/')[-1] + '.o': u for u in ported}
    sp = parse_splits(f'{CFG}/splits.txt'); addr = {s['name']: (s['sec'], s['addr']) for s in symbols(f'{CFG}/symbols.txt')}
    drop = set(); lines = out.split('\n')
    for i, l in enumerate(lines):
        m = re.search(r"multiply-defined: '(\S+)' in (\S+)", l)
        if m:
            for o in (m.group(2),):
                if o in base: drop.add(base[o])
            ctx = ' '.join(lines[i:i + 3])
            for o, u in base.items():
                if o in ctx: drop.add(u)
        m = re.search(r"undefined: '(\S+)'", l)
        if m and i + 1 < len(lines):
            ref = re.search(r"in (\S+\.o)", lines[i + 1])
            if ref and ref.group(1) in base: drop.add(base[ref.group(1)])
            elif m.group(1) in addr:
                sec, a = addr[m.group(1)]
                for u in ported:
                    if any(s0 <= a < e0 for (sc, s0, e0) in sp.get(u, [])): drop.add(u)
    errs = out.count('Linker Error') - out.count('both need')
    print(f'round {rnd}: link errors ~{errs}, dropping {len(drop)}: {sorted(drop)[:6]}')
    if not drop: break
    subprocess.run(['python3', 'tools/ported_drop.py', CFG, pre, *drop])
