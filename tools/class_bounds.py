#!/usr/bin/env python3
"""Source-file boundaries inside unk units from vtable classes (name-free).

Class of a function: the one vtable that lists it (a slot no other vtable shares), or the one
vtable whose address it forms (constructors/destructors store it). Vtables are found
structurally: data symbols whose words are mostly function starts.
Boundary rule (tested on ogws game code, see evaluate): between two neighbouring classed functions
of different classes, when no class has functions on both sides of the gap inside the container.
Placement: functions in between are pulled to the side they share a .sdata2 constant with
(pooled constants are file-local); if a .sdata2 constant is shared across every cut position, the
candidate is dropped. Remaining ambiguity: the cut goes right before the right-hand class's first
function (--place right) or right after the left-hand class's last one (--place left).

  class_bounds.py eval DOL SYMBOLS TRUE_SPLITS LO HI          # score on a project with true splits
  class_bounds.py run  DOL SYMBOLS SPLITS [--apply]           # cut Resort unk units
"""
import bisect, collections, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read
from apply_ogws import parse_splits
import pool_bounds


def vtables(d, ds, S):
    fa = {s['addr'] for s in S if s['func']}
    out = {}
    for s in S:
        if s['func'] or s['sec'] not in ('.data', '.rodata') or s['size'] < 12: continue
        blob = read(d, ds, s['addr'], s['size']) or b''
        w = [struct.unpack('>I', blob[i:i + 4])[0] for i in range(0, len(blob) - 3, 4)]
        f = [x for x in w if x in fa]
        if len(f) >= 2 and len(f) >= 0.6 * len(w):
            out[s['addr']] = (s['addr'] + s['size'], f)
    return out


def classes(d, ds, S, refs):
    vt = vtables(d, ds, S)
    cnt = collections.Counter(f for _, fs in vt.values() for f in set(fs))
    cls = {}
    for v, (_, fs) in vt.items():
        for f in set(fs):
            if cnt[f] == 1: cls[f] = v
    vs = sorted(vt); ve = {v: vt[v][0] for v in vs}
    for f, rs in refs.items():
        hit = set()
        for _, x in rs:
            i = bisect.bisect_right(vs, x) - 1
            if i >= 0 and x < ve[vs[i]]: hit.add(vs[i])
        if len(hit) == 1:
            v = hit.pop()
            if cls.get(f, v) == v: cls[f] = v
            else: cls.pop(f, None)
    return cls


def sdata2_groups(S, refs):
    """function addr -> set of .sdata2 symbol ids it uses"""
    D = sorted((s['addr'], s['addr'] + max(s['size'], 1)) for s in S if s['sec'] == '.sdata2')
    st = [x[0] for x in D]
    out = collections.defaultdict(set)
    for f, rs in refs.items():
        for _, x in rs:
            i = bisect.bisect_right(st, x) - 1
            if i >= 0 and x < D[i][1]: out[f].add(i)
    return out


def cuts(F, cls, g2, place='right', refs=None, users=None):
    """F: functions of one container in address order. Returns cut indices k (cut before F[k])."""
    C = [(i, cls[f['addr']]) for i, f in enumerate(F) if f['addr'] in cls]
    first, last = {}, {}
    for j, (i, c) in enumerate(C):
        first.setdefault(c, i); last[c] = i
    # .sdata2 spans: a cut at k is impossible when a constant is used by F[<k] and F[>=k]
    span = collections.defaultdict(lambda: [None, None])
    for i, f in enumerate(F):
        for g in g2.get(f['addr'], ()):
            sp = span[g]
            sp[0] = i if sp[0] is None else sp[0]; sp[1] = i
    blocked = [0] * (len(F) + 1)
    for lo, hi in span.values():
        if hi > lo:
            blocked[lo + 1] += 1; blocked[hi + 1] -= 1
    acc, blk = 0, []
    for k in range(len(F) + 1):
        acc += blocked[k]; blk.append(acc > 0)
    out = []
    for (i, c), (j, e) in zip(C, C[1:]):
        if c == e: continue
        if any(first[x] <= i and last[x] >= j for x in first): continue    # a class straddles the gap
        ok = [k for k in range(i + 1, j + 1) if not blk[k]]
        if not ok: continue
        if place == 'gap': out.append((i, j)); continue
        if place == 'data' and len(ok) > 1:
            out.append(data_place(F, i, j, c, e, cls, ok, refs, users)); continue
        out.append(ok[-1] if place == 'right' else ok[0])
    return out


def local_refs(F, refs, users):
    """per function: data addresses it uses that only functions of this container use"""
    fs = {f['addr'] for f in F}
    return {f['addr']: [(sec, x) for sec, x in refs.get(f['addr'], ()) if users.get(x, set()) <= fs]
            for f in F}


def data_place(F, i, j, c, e, cls, ok, refs, users):
    lr = local_refs(F, refs, users)
    L, R = {}, {}
    for f in F:
        k = cls.get(f['addr'])
        for sec, x in lr[f['addr']]:
            if k == c: L[sec] = max(L.get(sec, 0), x)
            if k == e: R[sec] = min(R.get(sec, 1 << 32), x)
    vote = {}
    for k in range(i + 1, j):
        l = sum(1 for sec, x in lr[F[k]['addr']] if sec in L and x <= L[sec])
        r = sum(1 for sec, x in lr[F[k]['addr']] if sec in R and x >= R[sec])
        if l != r: vote[k] = 'L' if l > r else 'R'
    best = min(ok, key=lambda p: (sum(1 for k, v in vote.items() if (v == 'L') == (k >= p)), p))
    return best


def evaluate(dolp, symp, splp, lo, hi):
    d, ds = dol_sections(dolp); S = symbols(symp)
    refs = pool_bounds.all_refs(dolp, symp)
    cls = classes(d, ds, S, refs); g2 = sdata2_groups(S, refs)
    F = sorted([s for s in S if s['func'] and s['sec'] == '.text' and lo <= s['addr'] < hi], key=lambda s: s['addr'])
    sp = parse_splits(splp)
    T = sorted((s, e, u) for u, v in sp.items() for (sec, s, e) in v if sec == '.text')
    starts = {s for s, e, u in T}
    ts = [t[0] for t in T]
    def unit(a):
        i = bisect.bisect_right(ts, a) - 1
        return T[i][2] if i >= 0 and a < T[i][1] else None
    nb = sum(1 for f in F[1:] if f['addr'] in starts)
    print(f'{len(F)} functions, {sum(1 for f in F if f["addr"] in cls)} classed, {nb} true unit starts')
    # containers like Resort's unk/sinit units: runs ending at a __sinit function
    conts, cur = [], []
    for f in F:
        cur.append(f)
        if f['name'].startswith('__sinit'): conts.append(cur); cur = []
    if cur: conts.append(cur)
    print(f'  {len(conts)} __sinit-delimited containers')
    det = n = 0
    for c in conts:
        for i, j in cuts(c, cls, g2, 'gap'):
            n += 1; det += any(c[k]['addr'] in starts for k in range(i + 1, j + 1))
    print(f'  detection: {det}/{n} candidate gaps hold a true unit start ({det / max(n, 1):.1%})')
    users = collections.defaultdict(set)
    for f, rs in refs.items():
        for sec, x in rs: users[x].add(f)
    for place in ('right', 'left', 'data'):
        ks = []
        for c in conts:
            base = F.index(c[0])
            ks += [base + k for k in cuts(c, cls, g2, place, refs, users)]
        exact = sum(1 for k in ks if F[k]['addr'] in starts)
        between = sum(1 for k in ks if unit(F[k - 1]['addr']) != unit(F[k]['addr']))
        # a detected boundary: some true start between the two classed neighbours (approximate: same as exact or near)
        print(f'  place={place}: {len(ks)} cuts, {exact} exactly at a unit start ({exact / max(len(ks), 1):.1%}), '
              f'recall {exact / max(nb, 1):.1%}')


def main(a):
    if a[0] == 'eval':
        evaluate(a[1], a[2], a[3], int(a[4], 16), int(a[5], 16))


if __name__ == '__main__': main(sys.argv[1:])
