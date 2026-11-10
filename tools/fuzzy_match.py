#!/usr/bin/env python3
"""Fuzzy function matching between two linked DOLs, spreading out from known pairs.

Anchors: functions with the same non-generic name in both symbol files, plus unique exact
relocation-masked byte matches. From each matched pair, the unmatched callees/callers of both
sides and functions sharing a unique string literal become candidates. A candidate pair is scored
on register-agnostic opcode similarity, size ratio and how many already-matched callees agree;
a pair is accepted when it is the mutual best, scores >= --min and beats the runner-up by --margin.
Repeats until nothing new is accepted.

Usage: fuzzy_match.py SRC_DOL SRC_SYMBOLS DST_DOL DST_SYMBOLS OUT_JSON [--holdout 0.2] [--min 0.85]
"""
import argparse, collections, difflib, hashlib, json, random, re, struct, sys, os
sys.path.insert(0, os.path.dirname(__file__))
from sig_match import symbols, dol_sections, read, masked, GENERIC

XO_OPS = {4, 19, 31, 59, 63}
def tokens(code):
    out = []
    for i in range(0, len(code) - 3, 4):
        w = struct.unpack('>I', code[i:i + 4])[0]; op = w >> 26
        if op in XO_OPS: out.append(op << 11 | (w >> 1) & 0x3FF)
        elif op == 30: out.append(op << 11 | (w >> 2) & 7)
        elif op == 16: out.append(op << 11 | (w >> 21) & 0x1F)     # bc: keep BO (cond kind)
        else: out.append(op << 11)
    return out

def sda_bases(dol, secs, init_regs):
    code = read(dol, secs, init_regs, 0x90) or b''
    regs = {}
    for i in range(0, len(code) - 3, 4):
        w = struct.unpack('>I', code[i:i + 4])[0]; op, rd, ra, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        if op == 15 and ra == 0: regs[rd] = imm << 16
        elif op == 24 and rd == ra and rd in regs: regs[rd] |= imm
        elif op == 14 and rd == ra and rd in regs: regs[rd] += imm - (0x10000 if imm & 0x8000 else 0)
    return regs.get(13), regs.get(2)

def cstring(dol, secs, addr):
    b = read(dol, secs, addr, 1)
    if b is None: return None
    s = bytearray()
    while len(s) < 200:
        c = read(dol, secs, addr + len(s), 1)
        if not c or c == b'\0': break
        s += c
    if len(s) >= 4 and all(32 <= c < 127 for c in s): return bytes(s).decode()
    return None

class Side:
    def __init__(self, dol_path, sym_path):
        self.dol, self.secs = dol_sections(dol_path)
        self.syms = symbols(sym_path)
        self.fns = sorted([s for s in self.syms if s['func'] and s['size'] >= 4], key=lambda s: s['addr'])
        self.at = {f['addr']: f for f in self.fns}
        ir = next((s['addr'] for s in self.syms if s['name'] == '__init_registers'), None)
        self.r13, self.r2 = sda_bases(self.dol, self.secs, ir) if ir else (None, None)
        self.tok, self.calls, self.strs, self.mhash = {}, {}, {}, {}
        for f in self.fns:
            code = read(self.dol, self.secs, f['addr'], f['size']) or b''
            self.tok[f['addr']] = tokens(code)
            self.mhash[f['addr']] = hashlib.sha1(masked(code)).digest()
            calls, strs, hi = [], set(), {}
            for i in range(0, len(code) - 3, 4):
                w = struct.unpack('>I', code[i:i + 4])[0]; op = w >> 26
                if op == 18 and w & 1:
                    d = w & 0x03FFFFFC
                    if d & 0x02000000: d -= 0x04000000
                    t = f['addr'] + i + d
                    if t in self.at and t not in calls: calls.append(t)
                rd, ra, imm = (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
                simm = imm - 0x10000 if imm & 0x8000 else imm
                if op == 15 and ra == 0: hi[rd] = imm << 16
                elif op == 14 and ra in hi:
                    s = cstring(self.dol, self.secs, (hi[ra] + simm) & 0xFFFFFFFF)
                    if s: strs.add(s)
                elif op == 14 and ra == 13 and self.r13:
                    s = cstring(self.dol, self.secs, (self.r13 + simm) & 0xFFFFFFFF)
                    if s: strs.add(s)
            self.calls[f['addr']], self.strs[f['addr']] = calls, strs
        self.callers = collections.defaultdict(list)
        for a, cs in self.calls.items():
            for c in cs: self.callers[c].append(a)
        self.strfn = collections.defaultdict(set)
        for a, ss in self.strs.items():
            for s in ss: self.strfn[s].add(a)

def opsim(a, b):
    if not a or not b: return 0.0
    sm = difflib.SequenceMatcher(None, a[:800], b[:800], autojunk=False)
    if sm.real_quick_ratio() < 0.7 or sm.quick_ratio() < 0.7: return 0.0
    return sm.ratio()

def run(S, D, anchors, min_score, margin, log=print):
    o2w = dict(anchors); w2o = {w: o for o, w in o2w.items()}
    cache = {}
    def score(o, w):
        k = (o, w)
        if k in cache: return cache[k]
        so, sw = S.at[o]['size'], D.at[w]['size']
        if min(so, sw) / max(so, sw) < 0.6: cache[k] = 0.0; return 0.0
        s = opsim(S.tok[o], D.tok[w])
        if s:
            co = [o2w.get(c) for c in S.calls[o] if c in o2w]; cw = set(D.calls[w])
            if co: s = 0.75 * s + 0.25 * (sum(1 for c in co if c in cw) / len(co))
            if S.strs[o] and D.strs[w]:
                j = len(S.strs[o] & D.strs[w]) / len(S.strs[o] | D.strs[w]); s = 0.85 * s + 0.15 * j
        cache[k] = s; return s
    # string seeds: a literal used by exactly one function on each side
    seeds = set()
    for s, fo in S.strfn.items():
        fw = D.strfn.get(s)
        if fw and len(fo) == 1 and len(fw) == 1: seeds.add((next(iter(fo)), next(iter(fw))))
    rnd = 0
    while True:
        rnd += 1
        cands = collections.defaultdict(dict)
        def add(os_, ws_):
            os_ = [o for o in os_ if o not in o2w]; ws_ = [w for w in ws_ if w not in w2o]
            if len(os_) * len(ws_) > 900: return
            for o in os_:
                for w in ws_:
                    cands[w][o] = score(o, w)
        for o, w in list(o2w.items()):
            add(S.calls[o], D.calls[w]); add(S.callers[o], D.callers[w])
            io, iw = S.fns.index(S.at[o]) if False else None, None
        for o, w in seeds:
            if o not in o2w and w not in w2o: cands[w][o] = score(o, w)
        # address neighbours between consecutive anchors
        by_o = sorted(o2w.items())
        oi = {f['addr']: i for i, f in enumerate(S.fns)}; wi = {f['addr']: i for i, f in enumerate(D.fns)}
        for (o1, w1), (o2, w2) in zip(by_o, by_o[1:]):
            if o1 not in oi or w1 not in wi or o2 not in oi or w2 not in wi: continue
            a, b, c, d = oi[o1], oi[o2], wi[w1], wi[w2]
            if 1 < b - a <= 12 and 1 < d - c <= 12:
                add([f['addr'] for f in S.fns[a + 1:b]], [f['addr'] for f in D.fns[c + 1:d]])
        best_o = collections.defaultdict(lambda: (0.0, None))
        for w, os_ in cands.items():
            for o, s in os_.items():
                if s > best_o[o][0]: best_o[o] = (s, w)
        new = 0
        for w, os_ in cands.items():
            r = sorted(os_.items(), key=lambda kv: -kv[1])
            if not r or r[0][1] < min_score: continue
            o, s = r[0]
            if len(r) > 1 and s - r[1][1] < margin: continue
            if best_o[o][1] != w or o in o2w or w in w2o: continue
            o2w[o] = w; w2o[w] = o; new += 1
        log(f'round {rnd}: +{new} (total {len(o2w)})')
        if not new: break
    return o2w

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('sdol'); ap.add_argument('ssym'); ap.add_argument('ddol'); ap.add_argument('dsym'); ap.add_argument('out')
    ap.add_argument('--holdout', type=float, default=0); ap.add_argument('--min', type=float, default=0.85)
    ap.add_argument('--margin', type=float, default=0.05)
    a = ap.parse_args()
    S, D = Side(a.sdol, a.ssym), Side(a.ddol, a.dsym)
    print(f'src fns {len(S.fns)} dst fns {len(D.fns)} sda dst r13={D.r13 and hex(D.r13)} r2={D.r2 and hex(D.r2)}')
    dn = {f['name']: f['addr'] for f in D.fns if not GENERIC.match(f['name'])}
    anchors = {f['addr']: dn[f['name']] for f in S.fns if not GENERIC.match(f['name']) and f['name'] in dn}
    hs = collections.defaultdict(list); hd = collections.defaultdict(list)
    for f in S.fns: hs[(f['size'], S.mhash[f['addr']])].append(f['addr'])
    for f in D.fns: hd[(f['size'], D.mhash[f['addr']])].append(f['addr'])
    used_w = set(anchors.values())
    for k, v in hs.items():
        if len(v) == 1 and len(hd.get(k, [])) == 1 and v[0] not in anchors and hd[k][0] not in used_w and k[0] >= 0x20:
            anchors[v[0]] = hd[k][0]; used_w.add(hd[k][0])
    print(f'anchors {len(anchors)}')
    held = {}
    if a.holdout:
        named = [o for o in anchors if not GENERIC.match(S.at[o]['name'])]
        random.seed(7); held = {o: anchors.pop(o) for o in random.sample(named, int(len(named) * a.holdout))}
    o2w = run(S, D, anchors, a.min, a.margin)
    if held:
        got = {o: o2w[o] for o in held if o in o2w}
        right = sum(1 for o, w in got.items() if held[o] == w)
        print(f'HOLDOUT {len(held)}: recovered {len(got)}, correct {right}, wrong {len(got) - right}')
    res = [dict(src=S.at[o]['name'], src_addr=hex(o), dst=D.at[w]['name'], dst_addr=hex(w), size=hex(D.at[w]['size']))
           for o, w in o2w.items() if o not in anchors]
    json.dump(sorted(res, key=lambda r: int(r['dst_addr'], 16)), open(a.out, 'w'), indent=0)
    print(f'{len(res)} new pairs -> {a.out}')

if __name__ == '__main__': main()
