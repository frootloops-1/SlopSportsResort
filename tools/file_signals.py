#!/usr/bin/env python3
"""Name-free evidence for source-file boundaries inside a .text region.

  same-file:      two functions referencing one data symbol of a section in SAME_SECS
                  (pooled constants, string pools, file-static tables)
  different-file: two copies of one weak inline function (identical code and identical
                  call/data targets, >= MIN_COPY bytes): a file emits each inline once

evaluate():  score both on a project with true splits (ogws), per section / per size.
Usage: file_signals.py DOL SYMBOLS SPLITS [--lo ADDR --hi ADDR]
"""
import bisect, collections, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, masked
from apply_ogws import parse_splits
import pool_bounds


def functions(symp, lo, hi):
    return sorted([f for f in symbols(symp) if f['func'] and f['sec'] == '.text' and f['size'] >= 4
                   and lo <= f['addr'] < hi], key=lambda f: f['addr'])


def data_symbols(symp):
    S = sorted((s['addr'], s['addr'] + max(s['size'], 1), s['sec']) for s in symbols(symp)
               if not s['func'] and s['sec'] not in ('.text', '.init', 'extab', 'extabindex'))
    return S


def fn_key(d, ds, f, refs):
    """identity of a function body: masked code + absolute branch targets + data targets"""
    code = read(d, ds, f['addr'], f['size']) or b''
    tg = []
    for i in range(0, len(code) - 3, 4):
        w = struct.unpack('>I', code[i:i + 4])[0]
        if w >> 26 == 18 and not w & 2:
            off = w & 0x03FFFFFC
            if off & 0x02000000: off -= 0x04000000
            tg.append((f['addr'] + i + off) & 0xFFFFFFFF)
    return (masked(code), tuple(tg), tuple(sorted(x for _, x in refs.get(f['addr'], ()))))


def referenced(d, ds, symp):
    """function addresses that are a branch target anywhere in .text or a word anywhere in data"""
    S = symbols(symp)
    fa = {s['addr'] for s in S if s['func']}
    out = set()
    for a, sz, off in ds:
        blob = read(d, ds, a, sz) or b''
        code = a < 0x80004000 + 0x700000 and any(s['sec'] in ('.text', '.init') and a <= s['addr'] < a + sz for s in S[:1])
        for i in range(0, len(blob) - 3, 4):
            w = struct.unpack('>I', blob[i:i + 4])[0]
            if w in fa: out.add(w)
            if w >> 26 == 18:
                off2 = w & 0x03FFFFFC
                if off2 & 0x02000000: off2 -= 0x04000000
                t = (off2 if w & 2 else a + i + off2) & 0xFFFFFFFF
                if t in fa: out.add(t)
    # lis/addi pairs forming a function address (function pointers in code)
    return out


def owner_of(symp_data):
    st = [s[0] for s in symp_data]
    def own(x):
        i = bisect.bisect_right(st, x) - 1
        return i if i >= 0 and x < symp_data[i][1] else None
    return own


def evaluate(dolp, symp, splp, lo, hi):
    d, ds = dol_sections(dolp)
    F = functions(symp, lo, hi)
    sp = parse_splits(splp)
    T = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.text')
    ts = [t[0] for t in T]
    def unit(a):
        i = bisect.bisect_right(ts, a) - 1
        return T[i][2] if i >= 0 and a < T[i][1] else None
    refs = pool_bounds.all_refs(dolp, symp)
    D = data_symbols(symp); own = owner_of(D)
    # same-file: per section, users of a data symbol
    users = collections.defaultdict(set)
    for f in F:
        for _, x in refs.get(f['addr'], ()):
            j = own(x)
            if j is not None: users[j].add(f['addr'])
    stat = collections.defaultdict(lambda: [0, 0])          # sec -> [same unit, crosses]
    for j, us in users.items():
        if len(us) < 2: continue
        sec = D[j][2]
        same = len({unit(a) for a in us}) == 1
        stat[sec][0 if same else 1] += 1
    print('same-file evidence (data symbols used by >= 2 functions in the region):')
    for sec, (a, b) in sorted(stat.items()):
        print(f'  {sec:8} {a:5} within one unit, {b:5} across units  ({a / max(a + b, 1):.1%} precise)')
    # different-file: identical function copies
    by = collections.defaultdict(list)
    for f in F:
        by[fn_key(d, ds, f, refs)].append(f)
    for mn in (0x10, 0x20, 0x40, 0x80):
        same = diff = 0
        for k, fs in by.items():
            if len(fs) < 2 or fs[0]['size'] < mn: continue
            for a, b in zip(fs, fs[1:]):
                if unit(a['addr']) == unit(b['addr']): same += 1
                else: diff += 1
        print(f'different-file evidence, copies >= 0x{mn:X} bytes: {diff} pairs across units, '
              f'{same} inside one unit ({diff / max(same + diff, 1):.1%} precise)')
    # weak copies: identical bodies where all but at most one copy are never referenced
    rc = referenced(d, ds, symp)
    for mn in (0x8, 0x10, 0x20):
        same = diff = 0
        for k, fs in by.items():
            if len(fs) < 2 or fs[0]['size'] < mn: continue
            dead = [f for f in fs if f['addr'] not in rc]
            if len(dead) < len(fs) - 1: continue
            for a, b in zip(fs, fs[1:]):
                if unit(a['addr']) == unit(b['addr']): same += 1
                else: diff += 1
        print(f'unreferenced weak copies >= 0x{mn:X}: {diff} pairs across units, {same} inside one unit '
              f'({diff / max(same + diff, 1):.1%} precise)')
    # how many true boundaries in the region
    nb = sum(1 for s, e, u in T if lo < s < hi)
    print(f'{len(F)} functions, {nb} true unit starts in region')


if __name__ == '__main__':
    a = sys.argv[1:]
    lo = int(a[a.index('--lo') + 1], 16) if '--lo' in a else 0
    hi = int(a[a.index('--hi') + 1], 16) if '--hi' in a else 0xFFFFFFFF
    evaluate(a[0], a[1], a[2], lo, hi)
