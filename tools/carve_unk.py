#!/usr/bin/env python3
"""Carve named library/framework files out of end-anchored unk/sinit_* units.

An unk/sinit_<addr>.cpp unit runs from the previous known boundary to its __sinit, so library files
without a static initialiser that sit before it were swallowed. For each reference unit that
port_splits.candidates() finds wholly inside one unk unit U = [s, e):
  - the file gets [a, b) as its own unit (a/b = first/last matched function, as port_splits does);
  - code before it, [s, a), becomes a placeholder unk/text_<s>.cpp (it is a different file:
    files are contiguous), unless a == s;
  - U keeps [b, e). If [a, b) holds U's __sinit, the file takes [a, e) and U's .ctors entry,
    and U's name is dropped.
Data: U's data ranges are cut only when the exclusively-referenced symbols (data_assign.assign on
the new .text layout) keep the link order prefix < file < U inside that range; the cut points are
the first symbol owned by a later unit. Otherwise the range stays with U (an upper bound, as now).
Usage: carve_unk.py SYMBOLS SPLITS DOL REF_SYMBOLS:REF_SPLITS ... [--prefix nw4r/,egg/] [--apply]
"""
import bisect, collections, os, re, sys, tempfile
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections
from apply_ogws import parse_splits
from sig_match import GENERIC, read
from unit_paths import canonical
import data_assign

DATA = data_assign.DATA


def read_units(path):
    """ordered [(name, header_line, [section lines])]"""
    units, cur = [], None
    head = []
    for line in open(path).read().split('\n'):
        if line and not line[0].isspace():
            cur = [line.split(':')[0], line, []]; units.append(cur)
        elif cur is None:
            head.append(line)
        elif line.strip():
            cur[2].append(line)
    return head, units


def sec_ranges(lines):
    out = []
    for l in lines:
        m = re.match(r'\s+(\S+)\s+start:0x(\w+) end:0x(\w+)(.*)', l)
        out.append((m[1], int(m[2], 16), int(m[3], 16), m[4]) if m else (None, 0, 0, l))
    return out


def fmt(sec, s, e, rest=''):
    return f'\t{sec:<11} start:0x{s:08X} end:0x{e:08X}{rest}'


def cls(name):
    """mangled class qualifier of a member function name (e.g. Q34nw4r2ef6Effect), or None"""
    m = re.match(r'.+?__(?:[CF]|Q\d|\d)', name)
    if not m: return None
    q = name[name.index('__', 1) + 2:] if '__' in name[1:] else ''
    m = re.match(r'(Q(\d)(?:\d+[A-Za-z_<>,0-9]+?)+|\d+[A-Za-z_]\w*?)(?=F|C|$)', q)
    if not m: return None
    if q.startswith('Q'):
        n, k, out = int(q[1]), 2, 'Q' + q[1]
        for _ in range(n):
            d = re.match(r'\d+', q[k:])
            if not d: return None
            ln = int(d[0]); out += q[k:k + len(d[0]) + ln]; k += len(d[0]) + ln
        return out
    d = re.match(r'(\d+)', q); ln = int(d[1])
    return q[:len(d[1]) + ln]


def lis(seq):
    """indices of the longest strictly increasing subsequence"""
    tails, tidx, prev = [], [], [-1] * len(seq)
    for i, x in enumerate(seq):
        j = bisect.bisect_left(tails, x)
        if j == len(tails): tails.append(x); tidx.append(i)
        else: tails[j] = x; tidx[j] = i
        prev[i] = tidx[j - 1] if j else -1
    out, k = [], tidx[-1] if tidx else -1
    while k >= 0: out.append(k); k = prev[k]
    return out[::-1]


def carve_candidates(fns, idx, dol, secs, refs, holder):
    """Like port_splits.candidates, tolerant of a newer library version:
    names may occur twice (HBM's private copies), so hits are taken in the unit holding most of them,
    in reference order (longest increasing run, >= 80% kept); coverage of the reference is not
    required when >= 3 names hit; named functions in between may only be other methods of a class
    the reference file defines."""
    multi = collections.defaultdict(list)
    for f in fns: multi[f['name']].append(f)
    cands = []
    for ref in refs:
        rsym, rspl = ref.split(':')
        rf = sorted([s for s in symbols(rsym) if s['func']], key=lambda s: s['addr'])
        for unit, ss in parse_splits(rspl).items():
            unit = canonical(unit)
            t = [x for x in ss if x[0] == '.text']
            if len(t) != 1: continue
            _, s, e = t[0]
            named = [f['name'] for f in rf if s <= f['addr'] < e and not GENERIC.match(f['name'])]
            if not named: continue
            byu = collections.defaultdict(list)
            for k, n in enumerate(named):
                for f in multi.get(n, ()):
                    h = holder(f['addr'], f['addr'] + 1)
                    if h: byu[h[2]].append((k, f))
            if not byu: continue
            u, hs = max(byu.items(), key=lambda kv: len(kv[1]))
            total = sum(len(v) for v in byu.values())
            if len(hs) < 0.8 * total: continue
            keep = sorted(hs, key=lambda x: x[1]['addr'])   # newer versions reorder methods: no order check
            n_hit = len(keep)
            if n_hit < 2 or (n_hit < 3 and n_hit < 0.6 * len(named)): continue
            classes = {c for c in map(cls, named) if c}
            nset = set(named)
            i0, i1 = idx[keep[0][1]['addr']], idx[keep[-1][1]['addr']]
            bad = [f['name'] for f in fns[i0:i1 + 1]
                   if not GENERIC.match(f['name']) and f['name'] not in nset and cls(f['name']) not in classes]
            if bad: continue
            start, end = fns[i0]['addr'], fns[i1]['addr'] + fns[i1]['size']
            nxt = fns[i1 + 1]['addr'] if i1 + 1 < len(fns) else end
            pad = read(dol, secs, end, nxt - end) if nxt > end else b''
            if pad is not None and 0 < nxt - end < 0x20 and pad.strip(b'\0') == b'': end = nxt
            cands.append((n_hit / len(named), n_hit, unit, start, end, os.path.basename(rspl)))
    return cands


def main(argv):
    apply = '--apply' in argv
    prefixes = None
    if '--prefix' in argv:
        prefixes = tuple(argv[argv.index('--prefix') + 1].split(','))
        argv = argv[:argv.index('--prefix')] + argv[argv.index('--prefix') + 2:]
    only = None
    if '--only' in argv:
        only = set(argv[argv.index('--only') + 1].split(','))
        argv = argv[:argv.index('--only')] + argv[argv.index('--only') + 2:]
    gaps = '--gaps' in argv
    argv = [a for a in argv if a not in ('--apply', '--gaps')]
    dsym, dsplit, ddol, refs = argv[0], argv[1], argv[2], argv[3:]
    fns = sorted([s for s in symbols(dsym) if s['func']], key=lambda s: s['addr'])
    idx = {s['addr']: i for i, s in enumerate(fns)}; byname = {s['name']: s for s in fns}
    dol, secs = dol_sections(ddol)
    sp = parse_splits(dsplit)
    taken = {u.lower() for u in sp}                    # macOS: names differing in case collide
    text = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.text')
    starts = [t[0] for t in text]

    def holder(a, b):
        i = bisect.bisect_right(starts, a) - 1
        if i >= 0 and text[i][0] <= a and b <= text[i][1]: return text[i]
        if not gaps or (i >= 0 and a < text[i][1]): return None
        lo = text[i][1] if i >= 0 else fns[0]['addr']           # a gap between split units
        hi = text[i + 1][0] if i + 1 < len(text) else fns[-1]['addr'] + fns[-1]['size']
        return (lo, hi, f'gap/{lo:08X}') if b <= hi else None

    cands = carve_candidates(fns, idx, dol, secs, refs, holder)
    plan = collections.defaultdict(list)         # unk unit -> [(a, b, file)]
    names = set()
    for cov, n, unit, a, b, src in sorted(cands, key=lambda c: (-c[0], -c[1])):
        if prefixes and not unit.startswith(prefixes): continue
        if unit.lower() in taken or unit.lower() in names: continue
        h = holder(a, b)
        if not h or not h[2].startswith('gap/' if gaps else 'unk/') or (only and h[2] not in only): continue
        if any(not (b <= x or a >= y) for x, y, _ in plan[h[2]]): continue
        plan[h[2]].append((a, b, unit)); names.add(unit.lower())

    if gaps:
        new = sorted((a, b, f) for v in plan.values() for a, b, f in v)
        print(f'{len(cands)} candidates; {len(new)} files in {len(plan)} gaps')
        for a, b, f in new: print(f'  {f} [{a:08X},{b:08X})')
        if not apply: return
        with open(dsplit, 'a') as fh:
            for a, b, f in new: fh.write(f'\n{f}:\n\t.text       start:0x{a:08X} end:0x{b:08X}\n')
        data_assign.apply(ddol, dsym, dsplit, skip_units=set(sp))
        return

    # New .text layout: each unk unit becomes [P0, F1, P1, F2, ..., U]
    new_units = {}                               # unit -> (start, end)
    order = {}                                   # unk unit -> [names in order]
    for u, files in plan.items():
        s, e = next((x, y) for x, y, n in text if n == u)
        cur, seq = s, []
        for a, b, f in sorted(files):
            if a > cur:
                p = f'unk/text_{cur:08X}.cpp'; new_units[p] = (cur, a); seq.append(p)
            new_units[f] = (a, b); seq.append(f); cur = b
        if cur < e:                              # unk/text_* has no __sinit: the tail is a new placeholder
            tail = f'unk/text_{cur:08X}.cpp' if u.startswith('unk/text_') else u
            new_units[tail] = (cur, e); seq.append(tail)
        else:                                    # the last file holds U's __sinit
            f = seq[-1]; new_units[f] = (new_units[f][0], e)
        order[u] = seq

    print(f'{len(cands)} candidates; carving {sum(len(v) for v in plan.values())} files '
          f'out of {len(plan)} unk units')
    for u, seq in sorted(order.items()):
        print(f'  {u}: ' + ', '.join(f'{n} [{new_units[n][0]:08X},{new_units[n][1]:08X})' for n in seq))
    if not apply: return

    apply_layout(dsym, dsplit, ddol, order, new_units)


def apply_layout(dsym, dsplit, ddol, order, new_units):
    """order: unit -> [piece names in .text order]; new_units: piece -> (start, end). The last piece keeps
    the unit's .ctors/extab; data ranges are cut by exclusive references (see module doc)."""
    head, units = read_units(dsplit)
    secorder = [l.split()[0] for l in head if l.startswith(('\t', ' ')) and l.split()]
    out_units, orig_data = [], {}
    for name, header, lines in units:
        if name not in order:
            out_units.append((name, header, lines)); continue
        rs = sec_ranges(lines)
        orig_data[name] = [(sec, a, b, r) for sec, a, b, r in rs if sec in DATA]
        for n in order[name]:
            ls = [fmt('.text', *new_units[n])]
            if n == order[name][-1]:              # last piece keeps U's .ctors/extab
                ls += [fmt(sec, a, b, r) if sec else r for sec, a, b, r in rs
                       if sec != '.text' and sec not in DATA]
            out_units.append((n, f'{n}:', ls))
    write(dsplit, head, out_units)

    # Data: cut U's ranges by exclusive ownership under the new .text layout
    ALIGN = []
    for l in open(dsym):
        m = re.match(r'\S+ = (\S+):0x(\w+);', l)
        if m and m[1] in DATA:
            al = re.search(r'align:(\d+)', l)
            ALIGN.append((int(m[2], 16), m[1], int(al[1]) if al else 1))
    ALIGN.sort()
    def max_align(sec, x, y):
        return max([al for ad, sc, al in ALIGN if sc == sec and x <= ad < y] or [1])
    def next_sym(sec, x, y):
        return next((ad for ad, sc, al in ALIGN if sc == sec and x < ad), y)
    ranges, _, _ = data_assign.assign(ddol, dsym, dsplit)
    byn = {n: [n, h, list(l)] for n, h, l in out_units}
    moved = kept = 0
    for u, seq in order.items():
        last = seq[-1]
        for sec, a, b, r in orig_data[u]:
            pieces, ok, prev_end = [], True, a
            for k, n in enumerate(seq):
                rg = ranges.get(n, {}).get(sec)
                if rg is None: continue
                s0, e0 = rg
                if not (a <= s0 and e0 <= b) or s0 < prev_end: ok = False; break
                pieces.append((k, s0, e0)); prev_end = e0
            bounds = [a] + [p[1] for p in pieces[1:]] + [b]
            # A piece's section is aligned to its most-aligned symbol: round each cut up until the
            # piece starts on that alignment (the symbols skipped stay with the previous piece).
            for j in range(1, len(bounds) - 1):
                while bounds[j] < bounds[j + 1] and bounds[j] % max_align(sec, bounds[j], bounds[j + 1]):
                    bounds[j] = next_sym(sec, bounds[j], bounds[j + 1])
            if any(x >= y for x, y in zip(bounds, bounds[1:])):
                byn[last][2].append(fmt(sec, a, b, r)); kept += 1; continue
            if not ok or not pieces or (len(pieces) == 1 and pieces[0][0] == len(seq) - 1) \
                    or any(x % 4 for x in bounds):
                byn[last][2].append(fmt(sec, a, b, r)); kept += 1; continue
            for j, (k, _, _) in enumerate(pieces):
                byn[seq[k]][2].append(fmt(sec, bounds[j], bounds[j + 1], r if j == len(pieces) - 1 else ''))
            moved += 1
    def key(l):
        sec = l.split()[0]
        return secorder.index(sec) if sec in secorder else len(secorder)
    for n in byn:
        if any(n in seq for seq in order.values()):
            byn[n][2].sort(key=key)
    write(dsplit, head, [tuple(byn[n]) for n, _, _ in out_units])
    print(f'data: {moved} section ranges split between pieces, {kept} left whole with the unk unit')


def write(path, head, units):
    out = list(head)
    while out and not out[-1].strip(): out.pop()
    for n, h, ls in units:
        out += ['', h] + [l for l in ls if l.strip()]
    open(path, 'w').write('\n'.join(out) + '\n')


if __name__ == '__main__': main(sys.argv[1:])
