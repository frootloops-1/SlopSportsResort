#!/usr/bin/env python3
"""Merge plain C names from a Dolphin signature-DB symbol map into symbols.txt, conservatively.

Keeps an entry only if: it carries an SDK/C-runtime library tag, its name is a plain C identifier
that appears once in the map, it is >= MIN_SIZE bytes, and dtk has a generic-named function at the
same address with the same size. Usage: merge_dolphin_map.py MAP SYMBOLS [--apply]
"""
import re, sys, collections
sys.path.insert(0, __import__('os').path.dirname(__file__))
from sig_match import symbols, GENERIC

MIN_SIZE = 0x20
BAD_LIBS = {'TRK_Hollywood_Revolution.a', 'base.a', 'ipc.a'}   # >30% wrong against verified names

def load(path):
    out = {}
    for l in open(path):
        p = l.split()
        if len(p) >= 5 and re.fullmatch(r'[0-9a-f]{8}', p[0]) and not p[4].startswith('zz_'):
            m = re.match(r'^(.*?)(?: (\S+\.a) (\S+))?$', ' '.join(p[4:]))
            out[int(p[0], 16)] = (int(p[1], 16), m.group(1), m.group(2))
    return out

def candidates(dm):
    cnt = collections.Counter(n for _, n, _ in dm.values())
    for a, (sz, n, lib) in dm.items():
        if lib and lib not in BAD_LIBS and sz >= MIN_SIZE and cnt[n] == 1 and re.fullmatch(r'[A-Za-z_]\w*', n):
            yield a, sz, n

def main(mp, sym, *flags):
    dm = load(mp); syms = symbols(sym)
    fns = {s['addr']: s for s in syms if s['func']}; taken = {s['name'] for s in syms}
    ok = bad = 0; ren = {}
    for a, sz, n in candidates(dm):
        s = fns.get(a)
        if not s or s['size'] != sz: continue
        if not GENERIC.match(s['name']):
            ok, bad = (ok + 1, bad) if (s['name'] == n or s['name'].startswith(n + '__')) else (ok, bad + 1)
        elif n not in taken:
            ren[a] = n; taken.add(n)
    print(f'filter check vs already-named: {ok} agree, {bad} disagree; {len(ren)} new names')
    if '--apply' in flags:
        lines = open(sym).read().split('\n')
        for i, l in enumerate(lines):
            m = re.match(r'^(\S+) = \.text:0x([0-9A-Fa-f]+);', l)
            if m and int(m.group(2), 16) in ren:
                lines[i] = ren[int(m.group(2), 16)] + l[len(m.group(1)):]
        open(sym, 'w').write('\n'.join(lines))

if __name__ == '__main__': main(*sys.argv[1:])
