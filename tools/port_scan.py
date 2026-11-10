#!/usr/bin/env python3
"""Scan Resort splits that have ogws source: compile each with ogws's own compiler and Wii/1.0,
score reloc-masked functions against Resort, and check the object covers every Resort function in
the split's .text range. Writes a JSON table. Compiles in a scratch copy of ogws (RUN_DIR), using
ogws's per-object command line. Usage: port_scan.py OGWS RESORT RUN_DIR OUT_DIR OUT_JSON"""
import json, os, re, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
from apply_ogws import parse_splits
from obj_score import elf, score
import io, contextlib

def main(og, rs, run, out, oj):
    sp = parse_splits(f'{rs}/config/RZTE01_01/splits.txt')
    fns = sorted([s for s in symbols(f'{rs}/config/RZTE01_01/symbols.txt') if s['func']], key=lambda s: s['addr'])
    res = []
    for unit, secs in sp.items():
        src = f'{og}/src/{unit}'
        t = [x for x in secs if x[0] == '.text']
        if not t or not os.path.exists(src) or unit.startswith('unk/'): continue
        base = re.sub(r'\.(c|cpp|cp)$', '', unit)
        cmd = subprocess.run(['ninja', '-t', 'commands', f'build/RSPE01_01/src/{base}.o'], cwd=og, capture_output=True, text=True).stdout.strip().split('\n')[-1]
        cmd = cmd.split(' && ')[0].replace('SportsPack.mch', 'SportsPack.pch')
        if 'mwcceppc' not in cmd: continue
        ogver = re.search(r'build/compilers/(\S+)/mwcceppc\.exe', cmd).group(1)
        need = [f['name'] for f in fns if t[0][1] <= f['addr'] < t[0][2]]
        row = dict(unit=unit, ogws_ver=ogver, n_resort=len(need), results={})
        for ver in dict.fromkeys([ogver, 'Wii/1.0']):
            o = f"{out}/{base.replace('/', '_')}__{ver.replace('/', '_')}.o"
            extra = ' -Dprivate=public -Dprotected=public' if ver.startswith('Wii') else ''
            c = re.sub(r'build/compilers/\S+/mwcceppc\.exe', f'{rs}/build/compilers/{ver}/mwcceppc.exe', cmd)
            c = re.sub(r' -o \S+', f' -o {o}', c.replace(' -MMD', extra))
            if subprocess.run(c, shell=True, cwd=run, capture_output=True).returncode: row['results'][ver] = 'compile failed'; continue
            with contextlib.redirect_stdout(io.StringIO()):
                ok, tot = score(o, f'{rs}/orig/RZTE01_01/sys/main.dol', f'{rs}/config/RZTE01_01/symbols.txt')
            b, osecs, osyms, _ = elf(o)
            have = {s['name'] for s in osyms if s['type'] == 2}
            missing = [n for n in need if n not in have]
            row['results'][ver] = dict(exact=ok, scored=tot, missing=len(missing), obj=o)
        res.append(row)
        best = max((v['exact'] for v in row['results'].values() if isinstance(v, dict)), default=0)
        print(f"{unit:<58} need {len(need):>3}  " + '  '.join(f"{k}={v if isinstance(v, str) else str(v['exact']) + '/' + str(v['scored']) + ' miss ' + str(v['missing'])}" for k, v in row['results'].items()), flush=True)
    json.dump(res, open(oj, 'w'), indent=1)

if __name__ == '__main__': main(*sys.argv[1:])
