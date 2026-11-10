#!/usr/bin/env python3
"""Translation-unit boundaries from per-unit constant pools (.sdata2).

MWCC pools float/double literals per unit: a pooled constant is local, so every function that loads
it is in the same unit, and two units each get their own copy of a value. Hence:
  same-unit:  functions referencing the same .sdata2 address  -> the whole span between them is one unit
  separate:   functions referencing equal values at different addresses -> a boundary lies between
Spans are merged into blocks; a boundary is forced between consecutive blocks that hold a duplicate
value. Reports, for each forced gap, the candidate function starts in it.
Usage: pool_bounds.py DOL SYMBOLS [TRUE_SPLITS] [--out JSON]"""
import collections, json, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read
from fuzzy_match import sda_bases

def refs(dolp, symp):
    d, ds = dol_sections(dolp); S = symbols(symp)
    ir = next(s['addr'] for s in S if s['name'] == '__init_registers')
    r13, r2 = sda_bases(d, ds, ir)
    sd2 = next((a, a + sz) for a, sz, o in ds if a <= r2 - 0x8000 + 0x10 < a + sz) if r2 else None
    F = sorted([f for f in S if f['func'] and f['sec'] == '.text' and f['size'] >= 4], key=lambda f: f['addr'])
    out = []
    for f in F:
        code = read(d, ds, f['addr'], f['size']) or b''; rs = set()
        for i in range(0, len(code) - 3, 4):
            w = struct.unpack('>I', code[i:i + 4])[0]; op = w >> 26; ra = (w >> 16) & 31
            if op in (48, 50, 32, 34, 40, 14) and ra == 2:   # lfs lfd lwz lbz lhz addi off r2
                imm = w & 0xFFFF; imm -= 0x10000 if imm & 0x8000 else 0
                a = (r2 + imm) & 0xFFFFFFFF
                if sd2 and sd2[0] <= a < sd2[1]: rs.add(a)
        out.append((f, rs))
    val = lambda a: read(d, ds, a, 4)
    return out, val

MAX_SPAN = 0x6000
MIN_CONFLICTS = 2
def blocks(dolp, symp):
    fr, val = refs(dolp, symp)
    idx = {f['addr']: i for i, (f, _) in enumerate(fr)}
    users = collections.defaultdict(list)
    for i, (f, rs) in enumerate(fr):
        for a in rs: users[a].append(i)
    # constants used across a wide address span are shared globals, not unit-local literals
    spans = sorted((min(v), max(v)) for v in users.values()
                   if fr[max(v)][0]['addr'] - fr[min(v)][0]['addr'] <= MAX_SPAN)
    merged = []
    for s, e in spans:
        if merged and s <= merged[-1][1]: merged[-1][1] = max(merged[-1][1], e)
        else: merged.append([s, e])
    # values held by each block
    bval = []
    for s, e in merged:
        vs = collections.defaultdict(set)
        for i in range(s, e + 1):
            for a in fr[i][1]: vs[val(a)].add(a)
        bval.append(vs)
    forced = []
    for k in range(len(merged) - 1):
        A, B = bval[k], bval[k + 1]
        if sum(1 for v in A if v in B and not (A[v] & B[v])) >= MIN_CONFLICTS:
            lo, hi = merged[k][1], merged[k + 1][0]           # boundary is at a start in (lo, hi]
            forced.append([fr[j][0]['addr'] for j in range(lo + 1, hi + 1)])
    return forced, merged, fr

def main():
    global MAX_SPAN
    a = sys.argv[1:]
    if '--span' in a: MAX_SPAN = int(a[a.index('--span') + 1], 16)
    outp = a[a.index('--out') + 1] if '--out' in a else None
    forced, merged, fr = blocks(a[0], a[1])
    exact = [c[0] for c in forced if len(c) == 1]
    print(f'{len(merged)} same-unit blocks; {len(forced)} forced gaps, {len(exact)} with a single possible start')
    if len(a) > 2 and not a[2].startswith('--'):
        from apply_ogws import parse_splits
        true = {s for v in parse_splits(a[2]).values() for (sec, s, e) in v if sec == '.text'}
        print(f'  exact-position precision {sum(x in true for x in exact) / max(len(exact), 1):.1%} ({len(exact)}), '
              f'gaps containing a true start {sum(any(x in true for x in c) for c in forced) / max(len(forced), 1):.1%}')
    if outp: json.dump(dict(forced=forced), open(outp, 'w'))

if __name__ == '__main__': main()

# ---- placing the boundary inside a forced gap using all data references -------------------------
def all_refs(dolp, symp):
    """Per function: set of (section_start, addr) for every data address it forms (lis/addi|load,
    r13 and r2 relative)."""
    d, ds = dol_sections(dolp); S = symbols(symp)
    ir = next(s['addr'] for s in S if s['name'] == '__init_registers')
    r13, r2 = sda_bases(d, ds, ir)
    # data sections from the symbol table (covers .bss/.sbss, which have no file data in the DOL)
    ext = {}
    for x in S:
        if x['sec'] in ('.text', '.init') or not x['sec'].startswith('.') and x['sec'] not in ('extab', 'extabindex'): continue
        lo, hi = ext.get(x['sec'], (x['addr'], x['addr']))
        ext[x['sec']] = (min(lo, x['addr']), max(hi, x['addr'] + max(x['size'], 1)))
    dsecs = sorted(v for k, v in ext.items() if k not in ('.text', '.init'))
    def sec_of(x):
        for a, b in dsecs:
            if a <= x < b: return a
    res = {}
    F = sorted([f for f in S if f['func'] and f['sec'] == '.text' and f['size'] >= 4], key=lambda f: f['addr'])
    for f in F:
        code = read(d, ds, f['addr'], f['size']) or b''; rs = set(); hi = {}
        for i in range(0, len(code) - 3, 4):
            w = struct.unpack('>I', code[i:i + 4])[0]; op = w >> 26; rd = (w >> 21) & 31; ra = (w >> 16) & 31
            imm = w & 0xFFFF; simm = imm - 0x10000 if imm & 0x8000 else imm
            if op == 15 and ra == 0: hi[rd] = imm << 16; continue
            if op in (14, 32, 34, 36, 38, 40, 44, 48, 50, 52, 54) and ra:
                base = hi.get(ra) if ra not in (1, 2, 13) else (r13 if ra == 13 else r2 if ra == 2 else None)
                if base is not None:
                    x = (base + simm) & 0xFFFFFFFF; s = sec_of(x)
                    if s: rs.add((s, x))
        res[f['addr']] = rs
    return res

def place(dolp, symp, forced, merged, fr):
    R = all_refs(dolp, symp)
    addr_i = {f['addr']: i for i, (f, _) in enumerate(fr)}
    cuts = []
    for k, cands in enumerate(forced):
        if len(cands) == 1: cuts.append(cands[0]); continue
        i0 = addr_i[cands[0]]
        # block before = up to i0-1 back to its block start; block after = from last cand on
        blk = next(b for b in merged if b[1] == i0 - 1)
        nxt = next(b for b in merged if b[0] == addr_i[cands[-1]])
        prev_max, next_min = {}, {}
        for j in range(blk[0], blk[1] + 1):
            for s, x in R[fr[j][0]['addr']]: prev_max[s] = max(prev_max.get(s, 0), x)
        for j in range(nxt[0], nxt[1] + 1):
            for s, x in R[fr[j][0]['addr']]: next_min[s] = min(next_min.get(s, 1 << 32), x)
        side = []
        for c in cands[:-1]:   # the last candidate is the next block's first function itself
            v = 0
            for s, x in R[c]:
                if s in prev_max and x <= prev_max[s]: v -= 1
                if s in next_min and x >= next_min[s]: v += 1
            side.append(v)
        last_prev = max([n for n, v in enumerate(side) if v < 0], default=-1)
        first_next = min([n for n, v in enumerate(side) if v > 0], default=len(side))
        # the cut goes right after the last function voting 'previous unit', provided no function
        # before it voted 'next unit'; with no votes at all the position stays unknown
        # only when the votes pin the boundary to one position
        cuts.append(cands[last_prev + 1] if first_next == last_prev + 1 else None)
    return cuts

def evaluate_place(dolp, symp, true_splits):
    forced, merged, fr = blocks(dolp, symp)
    cuts = place(dolp, symp, forced, merged, fr)
    from apply_ogws import parse_splits
    true = {s for v in parse_splits(true_splits).values() for (sec, s, e) in v if sec == '.text'}
    got = [c for c in cuts if c]
    print(f'placed {len(got)}/{len(cuts)} cuts, precision {sum(c in true for c in got) / max(len(got), 1):.1%}')
    return cuts
