#!/usr/bin/env python3
"""Register-allocation colouring-order diagnoser for same-instruction, different-register near misses.

  python3 tools/regalloc_diag.py <unit> <function> [--ours OBJ] [--target OBJ] [--json]

Applies the vreg/colouring model in docs/forecast-regalloc-notes.md to one function: compares the
non-volatile register assignment (r14-r31, f14-f31) of the original against ours, names each
non-volatile value by its first definition, reports which values the target colours first, which
pairs ours inverts, and lists the cheapest levers from the notes for that pair of roles.

It is a diagnosis, not a proof (docs/matching-playbook.md): objdiff's register diff is judged by
instruction index, so it only means something when the two opcode sequences are identical
(wall-identifier: register/schedule class). When they are not, it says so and stops.
"""
import argparse, collections, json, pathlib, re, subprocess, sys

ROOT = pathlib.Path("build/RZTE01_01")

STORE = re.compile(r"^(st[bhw]u?x?|stfsu?x?|stfdu?x?|stfiwx|psq_stu?x?|sthbrx|stwbrx|stswi|stmw|stwcx\.)$")
CMP = re.compile(r"^(cmp|cmpl|cmpw|cmplw|cmpwi|cmplwi|cmpi|cmpli|fcmpu|fcmpo|ps_cmp\w+)$")
USEONLY = {"mtlr", "mtctr", "mtspr", "mtcrf", "mtmsr", "mtfsf", "twi", "tw", "dcbf", "dcbi", "dcbst", "icbi",
           "dcbz", "dcbt", "dcbtst", "sync", "isync", "eieio"}
UPDATE = re.compile(r"^(l[bhwf][a-z]*u|lfsu|lfdu|st[bhw]u|stfsu|stfdu|psq_lu|psq_stu)$")
BRANCH = re.compile(r"^(b|bl|blr|bctr|bctrl|blrl|b[lgen][te]|bdnz|bdz|bt|bf|beq|bne|bgt|blt|bge|ble|bso|bns)[+-]?l?r?$")
REG = re.compile(r"\b([rf])(\d+)\b")
MEM = re.compile(r"\(([rf]\d+)\)")


def disasm(obj: pathlib.Path, scratch: pathlib.Path) -> dict:
    out = scratch / (obj.parent.name + "_" + obj.stem + "_" + obj.parent.parent.name + ".diag.s")
    subprocess.run(["build/tools/dtk", "elf", "disasm", str(obj), str(out)], check=True, capture_output=True)
    funcs, cur = {}, None
    for line in out.read_text().splitlines():
        m = re.match(r"\.fn (\S+),", line)
        if m:
            cur = m.group(1); funcs[cur] = []; continue
        if line.startswith(".endfn"):
            cur = None; continue
        if cur is None:
            continue
        if re.match(r"\.L_[0-9A-Fa-f]+:", line):
            continue
        if line.startswith("/*"):
            ins = re.sub(r"^/\*.*?\*/\s*", "", line).strip()
            mn, _, ops = ins.partition(" ")
            funcs[cur].append((mn, ops.strip()))
    return funcs


def regs_of(ops: str):
    """Ordered (kind,num,is_base) for every GPR/FPR token."""
    base = {m.group(1) for m in MEM.finditer(ops)}
    out = []
    for m in REG.finditer(ops):
        tok = m.group(0)
        out.append((m.group(1), int(m.group(2)), tok in base and f"({tok})" in ops))
    return out


def defs_uses(mn, ops):
    """(defs, uses) as sets of (kind,num). Conservative PPC model; r0 as a base is literal zero."""
    rg = regs_of(ops)
    if not rg or BRANCH.match(mn) and mn not in ("bctr",):
        return set(), set()
    if STORE.match(mn) or CMP.match(mn) or mn in USEONLY:
        uses = {(k, n) for k, n, b in rg if not (b and n == 0 and k == "r")}
        defs = set()
        if UPDATE.match(mn):
            for k, n, b in rg:
                if b: defs.add((k, n))
        return defs, uses
    first = rg[0]
    defs = {(first[0], first[1])}
    uses = {(k, n) for k, n, b in rg[1:] if not (b and n == 0 and k == "r")}
    if mn.startswith("rlwimi") or mn == "insrwi":
        uses.add((first[0], first[1]))
    if UPDATE.match(mn):
        for k, n, b in rg[1:]:
            if b: defs.add((k, n))
    return defs, uses


def nonvol(k, n):
    return 14 <= n <= 31


def analyse(ins):
    """Per non-volatile register: first def, last use, counts, calls in span, role of first def."""
    info = {}
    calls = [i for i, (mn, _) in enumerate(ins) if mn in ("bl", "bctrl", "blrl")]
    for i, (mn, ops) in enumerate(ins):
        d, u = defs_uses(mn, ops)
        for r in d | u:
            if not nonvol(*r):
                continue
            v = info.setdefault(r, {"first": i, "last": i, "defs": 0, "uses": 0, "role": None})
            v["last"] = i
            if r in d:
                v["defs"] += 1
                if v["role"] is None:
                    v["role"] = (i, mn, ops)
            if r in u:
                v["uses"] += 1
    # prologue saves (stw rN, off(r1) / stfd fN) and epilogue restores are not values
    for r, v in list(info.items()):
        v["calls"] = sum(1 for c in calls if v["first"] < c < v["last"])
    return info


def role_class(r, v, ins, info):
    """Name the first definition. Returns (class, text). Classes drive the lever table."""
    if v["role"] is None:
        return "param", "never defined (incoming)"
    i, mn, ops = v["role"]
    rg = regs_of(ops)
    pre_call = not any(m in ("bl", "bctrl") for m, _ in ins[:i])
    if mn in ("mr", "fmr") and len(rg) == 2:
        s = rg[1]
        if s[0] == "r" and 3 <= s[1] <= 10 and pre_call:
            return "param", f"copy of incoming arg r{s[1]} (param {s[1]-3})"
        if s[0] == "r" and s[1] == 3:
            return "callres", "copy of call result"
        if s[0] == "f" and s[1] == 1:
            return "callres", "copy of float call result"
        return "copy", f"copy of {s[0]}{s[1]}"
    if mn in ("addi", "addic") and len(rg) >= 2 and rg[1][1] == 1:
        return "stackaddr", "address of a stack local"
    if mn == "addi":
        return "derived", f"derived pointer from {rg[1][0]}{rg[1][1]}" if len(rg) > 1 else "derived pointer"
    if mn in ("li", "lis"):
        return "const", "constant"
    if re.match(r"^l(bz|hz|ha|wz|fs|fd|bzx|wzx|hzx|fsx|fdx|ha)", mn):
        return "load", f"load {ops.split(',', 1)[-1].strip()}"
    if mn.startswith("f") or mn.startswith("ps_"):
        return "fres", f"float result ({mn})"
    return "temp", f"result of {mn}"


# lever numbers refer to docs/forecast-regalloc-notes.md "Levers to try"
LEVERS = {
    ("param", "param"): [(4, "walk a copy of a parameter / keep parameter order"), (1, "declare locals up front")],
    ("param", "load"): [(4, "walk a copy of the parameter"), (2, "declared type of the load result")],
    ("load", "load"): [(1, "declare locals up front in colouring order"), (2, "declared type of each load result")],
    ("load", "derived"): [(7, "reuse the carried variable"), (3, "put loop pointer/index in one inline expansion")],
    ("derived", "derived"): [(7, "reuse the carried variable"), (3, "loop pointer/index in one inline")],
    ("load", "stackaddr"): [(5, "non-POD lvalue / hoisted stack-copy address"), (1, "declare up front")],
    ("fres", "fres"): [(8, "float result as a named variable, assign in target order"), (9, "named local for a hoisted constant")],
    ("fres", "load"): [(8, "named float result"), (2, "type of the loaded local")],
    ("const", "load"): [(9, "named local for hoisted constant")],
    ("callres", "load"): [(1, "declare locals up front"), (2, "type of the call-result local")],
}


def levers_for(a, b):
    key = (a, b) if (a, b) in LEVERS else (b, a)
    return LEVERS.get(key, [(1, "declare locals up front, uninitialised, in the order that gives the needed colouring")])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("function")
    ap.add_argument("--ours", type=pathlib.Path)
    ap.add_argument("--target", type=pathlib.Path)
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    tgt = a.target or ROOT / "obj" / f"{a.unit}.o"
    our = a.ours or ROOT / "src" / f"{a.unit}.o"
    scratch = pathlib.Path("build/evidence/regalloc_diag"); scratch.mkdir(parents=True, exist_ok=True)
    ft, fo = disasm(tgt, scratch), disasm(our, scratch)
    t, o = ft.get(a.function), fo.get(a.function)
    if t is None or o is None:
        sys.exit(f"{a.function}: missing in {'target' if t is None else 'ours'}")
    res = {"function": a.function, "len_target": len(t), "len_ours": len(o)}
    mism = [i for i in range(min(len(t), len(o))) if t[i][0] != o[i][0]]
    if len(t) != len(o) or mism:
        res["verdict"] = "NOT-REGALLOC"
        res["detail"] = f"opcode sequences differ (len {len(t)} vs {len(o)}, first mismatch at {mism[:1]}); not an allocator-order problem"
        print(json.dumps(res) if a.json else f"{a.function}: {res['verdict']}: {res['detail']}")
        return 2
    # register mapping ours -> target by operand position
    mp = collections.defaultdict(collections.Counter)
    sites = collections.defaultdict(list)
    ndiff = 0
    for i in range(len(t)):
        rt, ro = regs_of(t[i][1]), regs_of(o[i][1])
        if len(rt) != len(ro):
            continue
        for (kt, nt, _), (ko, no, _) in zip(rt, ro):
            if nt != no:
                ndiff += 1
                sites[(f"{ko}{no}", f"{kt}{nt}")].append(i)
            mp[(ko, no)][nt] += 1
    res["diff_operands"] = ndiff
    if ndiff == 0:
        res["verdict"] = "IDENTICAL"
        print(json.dumps(res) if a.json else f"{a.function}: registers identical")
        return 0
    it, io = analyse(t), analyse(o)
    # variables keyed by OUR register; the target register is the dominant image
    var = []
    split = []
    minority = []
    for (k, n), cnt in sorted(mp.items()):
        if not nonvol(k, n):
            continue
        tr, c = cnt.most_common(1)[0]
        if len(cnt) > 1:
            split.append((f"{k}{n}", {f"{k}{x}": y for x, y in cnt.items()}))
            share = 1 - cnt.most_common(1)[0][1] / sum(cnt.values())
            minority.append((f"{k}{n}", share))
        v = io.get((k, n))
        if v is None:
            continue
        cls, txt = role_class((k, n), v, o, io)
        var.append({"ours": f"{k}{n}", "target": f"{k}{tr}", "class": cls, "role": txt,
                    "first": v["first"], "last": v["last"], "uses": v["uses"], "calls": v["calls"]})
    # colouring order: callee-saved nodes take r31, r30, ... in colouring order => higher reg = coloured earlier
    key = lambda x: -int(x[1:])
    tord = sorted(var, key=lambda x: key(x["target"]))
    oord = sorted(var, key=lambda x: key(x["ours"]))
    tpos = {v["ours"]: i for i, v in enumerate(tord)}
    opos = {v["ours"]: i for i, v in enumerate(oord)}
    moved = [x for x in var if x["ours"] != x["target"]]
    inv = []
    for x in moved:
        for y in moved:
            if x["ours"] < y["ours"] and (tpos[x["ours"]] - tpos[y["ours"]]) * (opos[x["ours"]] - opos[y["ours"]]) < 0:
                first, second = (x, y) if tpos[x["ours"]] < tpos[y["ours"]] else (y, x)
                inv.append((first, second))
    # model consistency: params (lowest vregs) must be coloured after every non-param value
    RANK = {"param": 0}
    viol = []
    for i, x in enumerate(tord):
        for y in tord[i + 1:]:
            if x["class"] == "param" and y["class"] != "param" and (x in moved or y in moved):
                viol.append((x["ours"], y["ours"]))
    res["model_violations"] = viol
    res.update(variables=var, inversions=[(f["ours"], s["ours"]) for f, s in inv], split=split)
    volonly = all(not nonvol(k, n) for (k, n) in mp if any(c != n for c in mp[(k, n)]))
    small = all(sh < 0.2 or sum(len(v) for (ro, _), v in sites.items() if ro == nm) <= 4 for nm, sh in minority)
    if split and small:
        res["verdict"] = "VALUE-PLACEMENT"
    elif split:
        res["verdict"] = "SPLIT-MERGED-RANGES"
    elif volonly:
        res["verdict"] = "VOLATILE-ONLY"
    elif inv and viol and any(v[0] in {m["ours"] for m in moved} for v in viol):
        res["verdict"] = "COLOURING-ORDER-MODEL-VIOLATION"
    elif inv:
        res["verdict"] = "COLOURING-ORDER"
    else:
        res["verdict"] = "NONVOL-COUNT-OR-OTHER"
    sugg = []
    for f, s in inv:
        sugg.append({"target_colours_first": f["ours"], "role": f["class"],
                     "target_colours_second": s["ours"], "role2": s["class"],
                     "levers": levers_for(f["class"], s["class"])})
    res["suggestions"] = sugg
    if a.json:
        print(json.dumps(res)); return 1
    print(f"{a.function}: {res['verdict']}  ({ndiff} differing operands, {len(var)} non-volatile values)")
    print("  non-volatile values (ours reg -> target reg; coloured-first in target order):")
    for v in tord:
        mark = "" if v["ours"] == v["target"] else "  <-- moved"
        print(f"    {v['ours']:>4} -> {v['target']:<4} {v['class']:9s} {v['role'][:46]:46s} span {v['first']}-{v['last']} uses {v['uses']} calls {v['calls']}{mark}")
    if res["verdict"] == "VOLATILE-ONLY":
        mv = sorted({(f"{k}{n}", f"{k}{x}") for (k, n), c in mp.items() for x in c if x != n})
        print("  volatile renames (ours -> target): " + ", ".join(f"{a}->{b}" for a, b in mv[:12]))
        sw = [(ro, rt) for (ro, rt) in sites if (rt, ro) in sites and ro < rt]
        for ro, rt in sw[:2]:
            ia, ib = sites[(ro, rt)][0], sites[(rt, ro)][0]
            lo, hi = (ia, ib) if int(rt[1:]) < int(ro[1:]) else (ib, ia)
            e, l = sorted((ia, ib))
            low_reg = min(ro, rt, key=lambda x: int(x[1:]))
            who = "earlier" if (sites[(ro, rt)][0] if int(rt[1:]) < int(ro[1:]) else sites[(rt, ro)][0]) == e else "later"
            print(f"  swap {ro}<->{rt}: target gives the lower volatile ({low_reg}) to the {who} value (insn {sorted((ia, ib))}); "
                  f"the model says the higher vreg takes the lower volatile, so that value must be the newer one "
                  f"(declare it later / make it the later expression temp); levers #1, #2")
    if res["model_violations"]:
        first = res["model_violations"][0]
        print(f"  MODEL VIOLATION: target colours param-copy {first[0]} before non-param {first[1]}; the model says params are coloured last, "
              "so that value is not a plain parameter (inline-expansion arg temp / split live range / param folded into a temp)")
    for name, m in split:
        print(f"  SPLIT {name} maps to several target registers {m}"
              + (": a short value sits in a different register than the long-lived value it shares with (placement of one value, same lever family as order)"
                 if res["verdict"] == "VALUE-PLACEMENT" else ": live ranges are structured differently (not an order problem)"))
    for (ro, rt), idxs in sorted(sites.items(), key=lambda kv: -len(kv[1]))[:4]:
        i = idxs[0]
        print(f"  site {ro}(ours)/{rt}(target) x{len(idxs)} first at insn {i}: target `{t[i][0]} {t[i][1]}`  ours `{o[i][0]} {o[i][1]}`")
        d = t[i]
        if d[0] == "addi" and "r1," in d[1]:
            hint = [(5, "stack-copy address of a non-POD lvalue"), (1, "declare up front")]
        elif d[0] == "addi":
            hint = [(7, "reuse the carried variable as the induction pointer"), (3, "loop pointer/index in one inline expansion")]
        elif d[0].startswith("l") and d[0][1] in "bhwf":
            hint = [(3, "FIRST check whether the value comes through an inline getter/accessor (lessons: fn_801E8ED0 closed this way after #1/#2 were flat)"),
                    (1, "declare the local up front, uninitialised"), (2, "declared type of the load result")]
            if d[0].startswith("lf"):
                hint.append((8, "named float result"))
        elif d[0] in ("li", "lis"):
            hint = [(9, "named local for a hoisted constant")]
        else:
            hint = [(1, "declare locals up front in colouring order")]
        if res["verdict"] != "VOLATILE-ONLY":
            print("    value kind -> levers: " + "; ".join(f"#{n} {x}" for n, x in hint))
    for s in sugg:
        print(f"  target colours {s['target_colours_first']} ({s['role']}) before {s['target_colours_second']} ({s['role2']}); levers: " +
              "; ".join(f"#{n} {d}" for n, d in s["levers"]))
    return 1


sys.exit(main())
