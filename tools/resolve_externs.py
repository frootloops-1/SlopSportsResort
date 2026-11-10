#!/usr/bin/env python3
"""Give Resort symbols the names ported objects expect.

For every relocation in a ported object's .text against an undefined symbol, decode the target
address from Resort's instructions at the same place (REL24 calls, HA/LO pairs, SDA21). When every
use agrees on one address and Resort has a generic symbol starting exactly there, rename it.
Usage: resolve_externs.py RESORT_DIR PORTED_JSON [--apply]"""
import collections, json, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import dol_sections, read, symbols, GENERIC
from fuzzy_match import sda_bases
import complete_split as cs

def main(rs, pj, *flags):
    cfg = f'{rs}/config/RZTE01_01'; dolp = f'{rs}/orig/RZTE01_01/sys/main.dol'
    dol, ds = dol_sections(dolp); S = symbols(f'{cfg}/symbols.txt')
    fa = {s['name']: s['addr'] for s in S if s['func']}
    at = {s['addr']: s for s in S}; names = {s['name'] for s in S}
    r13, r2 = sda_bases(dol, ds, fa['__init_registers'])
    W = lambda a: struct.unpack('>I', read(dol, ds, a, 4))[0]
    votes = collections.defaultdict(collections.Counter)
    for p in json.load(open(pj)):
        obj = f"{rs}/build/RZTE01_01/src/{re.sub(r'.(c|cpp)$', '', p['name'])}.o"
        if not os.path.exists(obj): continue
        secs, syms, rel = cs.elf_full(obj)
        ti = next(i for i, s in enumerate(secs) if s['name'] == '.text')
        fns = sorted((x['value'], x['size'], x['name']) for x in syms if x['type'] == 2 and x['shndx'] == ti)
        def da(off):
            for v, sz, n in fns:
                if v <= off < v + sz and n in fa: return fa[n] + off - v
        ha = {}
        for off, typ, si, add in sorted(rel[ti]):
            sym = syms[si]
            a = da(off & ~3)
            if a is None: continue
            ins = W(a)
            if sym['shndx'] != 0 or sym['name'] in names:
                if typ == 6: ha.pop((ins >> 21) & 31, None)
                continue
            if typ == 10:
                d = ins & 0x03FFFFFC; d -= 0x04000000 if d & 0x02000000 else 0
                votes[sym['name']][(a + d - add) & 0xFFFFFFFF] += 1
            elif typ == 6: ha[(ins >> 21) & 31] = (ins & 0xFFFF) << 16
            elif typ == 4:
                ra = (ins >> 16) & 31; lo = ins & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0
                if ra in ha: votes[sym['name']][(ha[ra] + lo - add) & 0xFFFFFFFF] += 1
            elif typ == 109:
                ra = (ins >> 16) & 31; lo = ins & 0xFFFF; lo -= 0x10000 if lo & 0x8000 else 0
                base = r13 if ra == 13 else r2 if ra == 2 else 0
                votes[sym['name']][(base + lo - add) & 0xFFFFFFFF] += 1
    ren, bad = {}, []
    for n, c in votes.items():
        if len(c) != 1: bad.append((n, 'disagree')); continue
        a = next(iter(c))
        if a in at and GENERIC.match(at[a]['name']): ren[a] = n
        else: bad.append((n, hex(a), at.get(a, {}).get('name')))
    print(f'{len(votes)} undefined names, {len(ren)} resolvable, {len(bad)} not: {bad[:8]}')
    if '--apply' in flags:
        L = open(f'{cfg}/symbols.txt').read().split('\n')
        for i, l in enumerate(L):
            m = re.match(r'^(\S+) = (\.?\w+):0x([0-9A-Fa-f]+);', l)
            if m and int(m.group(3), 16) in ren and GENERIC.match(m.group(1)):
                L[i] = ren[int(m.group(3), 16)] + l[len(m.group(1)):]
        open(f'{cfg}/symbols.txt', 'w').write('\n'.join(L))

if __name__ == '__main__': main(*sys.argv[1:])
