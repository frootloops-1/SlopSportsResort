#!/usr/bin/env python3
"""Assign data to units by exclusive references, respecting link order.

For every data symbol, find which .text units reference it (lis/addi pairs, r13/r2 SDA). A symbol
referenced by exactly one unit is that unit's. Per section, units' data must appear in the same
order as their code, so exclusive (unit, address) pairs that break the order are dropped (longest
non-decreasing subsequence). A unit's range is [first owned symbol, end of last owned symbol]
(conservative; unowned symbols in between stay with it, after it stay unassigned).
Usage: data_assign.py DOL SYMBOLS SPLITS [--eval TRUE_SPLITS] [--apply] [--units-prefix unk/]"""
import bisect, collections, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections
from apply_ogws import parse_splits
import pool_bounds

DATA = ('.data', '.rodata', '.sdata', '.sdata2', '.bss', '.sbss', '.sbss2')

def lnds(seq):
    """indices of a longest non-decreasing subsequence of seq (patience sorting)"""
    tails, tidx, prev = [], [], [-1] * len(seq)
    for i, x in enumerate(seq):
        j = bisect.bisect_right(tails, x)
        if j == len(tails): tails.append(x); tidx.append(i)
        else: tails[j] = x; tidx[j] = i
        prev[i] = tidx[j - 1] if j else -1
    out, k = [], tidx[-1] if tidx else -1
    while k >= 0: out.append(k); k = prev[k]
    return out[::-1]

def assign(dolp, symp, splp, prefix=None):
    S = symbols(symp); sp = parse_splits(splp)
    units = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.text')
    ustart = [s for s, e, u in units]
    def unit_of(a):
        i = bisect.bisect_right(ustart, a) - 1
        return i if i >= 0 and a < units[i][1] else None
    R = pool_bounds.all_refs(dolp, symp)
    dsyms = sorted((s['addr'], s['addr'] + max(s['size'], 1), s['sec'], s['name']) for s in S if s['sec'] in DATA)
    dstart = [x[0] for x in dsyms]
    users = collections.defaultdict(set)
    for fa, rs in R.items():
        ui = unit_of(fa)
        if ui is None: continue
        for _, x in rs:
            j = bisect.bisect_right(dstart, x) - 1
            if j >= 0 and x < dsyms[j][1]: users[j].add(ui)
    own = collections.defaultdict(list)            # section -> [(addr, end, unit_index)]
    for j, us in users.items():
        if len(us) == 1: own[dsyms[j][2]].append((dsyms[j][0], dsyms[j][1], next(iter(us))))
    ranges = collections.defaultdict(dict)         # unit -> section -> (start, end)
    dropped = 0
    for sec, lst in own.items():
        lst.sort(); keep = lnds([u for a, e, u in lst]); dropped += len(lst) - len(keep)
        for k in keep:
            a, e, ui = lst[k]; u = units[ui][2]
            nx = bisect.bisect_left(dstart, e)                     # absorb padding up to the next symbol
            if nx < len(dsyms) and dsyms[nx][2] == sec and dsyms[nx][0] - e < 0x20: e = dsyms[nx][0]
            if prefix and not u.startswith(prefix): continue
            s0, e0 = ranges[u].get(sec, (a, e)); ranges[u][sec] = (min(s0, a), max(e0, e))
    return ranges, dropped, sp

def main():
    a = sys.argv[1:]
    prefix = a[a.index('--units-prefix') + 1] if '--units-prefix' in a else None
    ranges, dropped, sp = assign(a[0], a[1], a[2], prefix)
    n = sum(len(v) for v in ranges.values())
    print(f'{len(ranges)} units get data ranges ({n} section ranges); {dropped} exclusive refs dropped as out of order')
    if '--eval' in a:
        true = parse_splits(a[a.index('--eval') + 1]); ok = bad = 0
        for u, secs in ranges.items():
            for sec, (s, e) in secs.items():
                t = [(ts, te) for (ts_sec, ts, te) in true.get(u, []) if ts_sec == sec for ts, te in [(ts, te)]]
                if any(ts <= s and e <= te for ts, te in t): ok += 1
                else: bad += 1
        print(f'  vs true splits: {ok} ranges inside the unit\'s real range, {bad} not ({ok / max(ok + bad, 1):.1%})')
    return ranges

if __name__ == '__main__': main()

def apply(dolp, symp, splp, skip_units=()):
    global SYMS
    SYMS = sorted((x['addr'], x['addr'] + max(x['size'], 1), x['sec'], x['name']) for x in symbols(symp) if x['sec'] in DATA)
    ranges, dropped, sp = assign(dolp, symp, splp)
    taken = [(sec, s, e) for v in sp.values() for (sec, s, e) in v]
    lines = open(splp).read().split('\n'); added = 0; skipped = 0
    import re
    for u, secs in ranges.items():
        if u in skip_units: continue
        have = {sec for sec, _, _ in sp[u]}
        new = []
        for sec, (s, e) in sorted(secs.items(), key=lambda kv: DATA.index(kv[0])):
            if s % 4: skipped += 1; continue                         # unit contributions start aligned
            while e % 4:                                              # string pools: run to an aligned symbol start
                nx = next((a0 for a0, e1, sc, nm in SYMS if sc == sec and a0 >= e), None)
                if nx is None or nx == e:
                    nx2 = next((e1 for a0, e1, sc, nm in SYMS if sc == sec and a0 == e), None)
                    if nx2 is None: break
                    e = nx2
                else: e = nx
            if e % 4 or sec in have or any(ts == sec and not (e <= s0 or s >= e0) for ts, s0, e0 in taken): skipped += 1; continue
            new.append(f'\t{sec:<11} start:0x{s:08X} end:0x{e:08X}'); taken.append((sec, s, e)); added += 1
        if not new: continue
        i = lines.index(f'{u}:')
        j = i + 1
        while j < len(lines) and lines[j].startswith('\t'): j += 1
        lines[j:j] = new
    open(splp, 'w').write('\n'.join(lines))
    print(f'added {added} data ranges, skipped {skipped} (section present or overlap)')
