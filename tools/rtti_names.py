#!/usr/bin/env python3
"""Name RTTI type-info objects and their vtables from class-name strings.

A type-info object's first word points at its class-name string; a vtable's first word points at
its type-info object. Generic labels at those addresses become __RTTI__<mangled> and
__vt__<mangled> (MWCC mangling, ogws template spelling). Usage: rtti_names.py DOL SYMBOLS [--apply]"""
import collections, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, GENERIC

TPL = {'wchar_t': 'w', 'char': 'c'}
def mangle(q):
    parts = q.split('::'); out = []
    for p in parts:
        m = re.fullmatch(r'(\w+)<(\w+)>', p)
        p = f'{m.group(1)}<{TPL.get(m.group(2), m.group(2))}>' if m else p
        out.append(f'{len(p)}{p}' if not m else f'{len(m.group(1))}{p}')
    return ''.join(out) if len(parts) == 1 else f'Q{len(parts)}' + ''.join(out)

def main(dolp, symp, *flags):
    dol, secs = dol_sections(dolp)
    syms = symbols(symp); lab = {s['addr']: s for s in syms if not s['func'] and s['sec'] != '.text'}
    words = collections.defaultdict(list)
    for a, sz, o in secs:
        if a < 0x80653FA0 or not o: continue
        b = dol[o:o + sz]
        for i in range(0, sz - 3, 4): words[struct.unpack('>I', b[i:i + 4])[0]].append(a + i)
        for m in re.finditer(rb'[A-Za-z]\w*(?:::\w+(?:<\w+>)?)+\0', b):
            pass
    def word(x):
        for a, sz, o in secs:
            if a <= x < a + sz - 3 and o: return struct.unpack('>I', dol[o + x - a:o + x - a + 4])[0]
    ren = {}
    for a, sz, o in secs:
        if a < 0x80653FA0 or not o: continue
        b = dol[o:o + sz]
        for m in re.finditer(rb'[A-Za-z]\w*(?:::\w+(?:<\w+>)?)+\0', b):
            q = m.group()[:-1].decode(); sa = a + m.start(); mg = mangle(q)
            for ti in words.get(sa, []):
                if ti in lab and GENERIC.match(lab[ti]['name']): ren[ti] = f'__RTTI__{mg}'
                for vt in words.get(ti, []):
                    # vtable = {&typeinfo, this-offset 0, fn, ...}; base-class lists also point at type-info
                    w1, w2 = word(vt + 4), word(vt + 8)
                    if w1 != 0 or not (0x80004000 <= (w2 or 0) < 0x80653FA0): continue
                    if vt in lab and GENERIC.match(lab[vt]['name']) and vt != ti: ren[vt] = f'__vt__{mg}'
    taken = {s['name'] for s in syms}
    ren = {a: n for a, n in ren.items() if n not in taken}
    if len(set(ren.values())) != len(ren):
        dup = [n for n, c in collections.Counter(ren.values()).items() if c > 1]
        ren = {a: n for a, n in ren.items() if n not in dup}
    print(f'{sum(n.startswith("__RTTI__") for n in ren.values())} type-info, {sum(n.startswith("__vt__") for n in ren.values())} vtables')
    for a, n in sorted(ren.items())[:6]: print(hex(a), n)
    if '--apply' in flags:
        L = open(symp).read().split('\n')
        for i, l in enumerate(L):
            m = re.match(r'^(\S+) = (\.\w+):0x([0-9A-Fa-f]+);', l)
            if m and m.group(2) != '.text' and int(m.group(3), 16) in ren and GENERIC.match(m.group(1)):
                L[i] = ren[int(m.group(3), 16)] + l[len(m.group(1)):]
        open(symp, 'w').write('\n'.join(L))

if __name__ == '__main__': main(*sys.argv[1:])
