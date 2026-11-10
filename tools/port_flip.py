#!/usr/bin/env python3
"""Turn fully exact scan results into Matching objects.

For each (unit, compiler) in PORT_FULL_JSON: take the scan's object, locate every allocated data
section in Resort via complete_split, extend the .text range to every object function present by
name, copy the ogws source file, and record {name, mw_version, cflags} in
config/RZTE01_01/ported_objects.json (read by configure.py). Units with an unlocatable or
overlapping section are skipped. Usage: port_flip.py OGWS RESORT SCAN_JSON PORT_FULL_JSON"""
import io, contextlib, json, os, re, shutil, subprocess, sys
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols
from apply_ogws import parse_splits
import complete_split as cs

SKIP = {'.text', '.comment', '.symtab', '.strtab', '.shstrtab', ''}
def main(og, rs, scanj, fullj):
    scan = {r['unit']: r for r in json.load(open(scanj))}
    full = json.load(open(fullj))
    cfg = f'{rs}/config/RZTE01_01'
    sp = parse_splits(f'{cfg}/splits.txt')
    used = [(s, e, u) for u, v in sp.items() for (sec, s, e) in v]
    allsyms = symbols(f'{cfg}/symbols.txt')
    fa = {s['name']: s for s in allsyms if s['func']}
    pj = f'{cfg}/ported_objects.json'
    ported = json.load(open(pj)) if os.path.exists(pj) else []
    done = {p['name'] for p in ported}
    text = open(f'{cfg}/splits.txt').read()
    added = skipped = 0
    for unit, ver in full:
        if unit in done or unit.startswith('Pack/'): continue
        obj = scan[unit]['results'][ver]['obj']
        secs, syms, rel = cs.elf_full(obj)
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf): cs.main(obj, f'{rs}/orig/RZTE01_01/sys/main.dol', f'{cfg}/symbols.txt', '0')
        found = {}
        for line in buf.getvalue().splitlines():
            m = re.match(r'\t(\S+)\s+start:0x(\w+) end:0x(\w+)\s+# \d+ refs(.*)', line)
            if m and not m.group(4): found[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))
        alloc = [s['name'] for s in secs if s['type'] in (1, 8) and s['size'] and s['name'] not in SKIP]
        if any(a not in found for a in alloc): skipped += 1; print('skip (section not located):', unit, [a for a in alloc if a not in found]); continue
        ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
        names = [x['name'] for x in syms if x['type'] == 2 and x['shndx'] == ti and x['name'] in fa]
        lo = min(fa[n]['addr'] for n in names); hi = max(fa[n]['addr'] + fa[n]['size'] for n in names)
        (_, ts, te) = next(x for x in sp[unit] if x[0] == '.text')
        ts, te = min(ts, lo), max(te, hi)
        rng = {'.text': (ts, te), **found}
        # never shrink a range the splits already give this unit
        for n, s0, e0 in sp[unit]:
            if n in rng: rng[n] = (min(rng[n][0], s0), max(rng[n][1], e0))
        # a section end inside a Resort symbol is alignment padding: end at that symbol's end
        for n, (s, e) in list(rng.items()):
            for y in allsyms:
                if y['addr'] < e < y['addr'] + y['size'] and y['addr'] >= s: rng[n] = (s, y['addr'] + y['size'])
        if any(not (e <= s0 or s >= e0) for name, (s, e) in rng.items() for (s0, e0, u) in used if u != unit):
            skipped += 1; print('skip (overlap):', unit); continue
        old = re.search(rf'(?m)^{re.escape(unit)}:\n(\t.*\n)+', text).group(0)
        new = f'{unit}:\n' + ''.join(f'\t{n:<11} start:0x{s:08X} end:0x{e:08X}\n' for n, (s, e) in rng.items())
        text = text.replace(old, new)
        used += [(s, e, unit) for s, e in rng.values()]
        cmd = subprocess.run(['ninja', '-t', 'commands', 'build/RSPE01_01/src/' + re.sub(r'\.(c|cpp|cp)$', '', unit) + '.o'], cwd=og, capture_output=True, text=True).stdout.strip().split('\n')[-1].split(' && ')[0]
        flags = re.search(r'mwcceppc\.exe (.*) -MMD', cmd).group(1)
        flags = re.sub(rf'-i build/RSPE01_01/include|-DBUILD_VERSION=\d+|-DVERSION_RSPE01_01', '', flags)
        # ogws headers branch on VERSION_RSPE01_01 (configure.py passes it to the base flags too)
        flags += ' -i build/RZTE01_01/include -DBUILD_VERSION=0 -DVERSION_RZTE01_01 -DVERSION_RSPE01_01'
        os.makedirs(os.path.dirname(f'{rs}/src/{unit}'), exist_ok=True)
        shutil.copy(f'{og}/src/{unit}', f'{rs}/src/{unit}')
        ported.append(dict(name=unit, mw_version=ver, cflags=flags.split(), category='game' if unit.startswith('Pack/') else 'sdk'))
        added += 1
    open(f'{cfg}/splits.txt', 'w').write(text)
    json.dump(ported, open(pj, 'w'), indent=1)
    print(f'added {added}, skipped {skipped}')

if __name__ == '__main__': main(*sys.argv[1:])
