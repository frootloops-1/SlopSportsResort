#!/usr/bin/env python3
"""Recommend a model tier for each unmatched function / object.

Reads the objdiff report (scores, sizes, ownership) and the original split
assembly (build/RZTE01_01/asm/...) to measure each function's difficulty,
then maps it to a tier and a model. Attempts recorded with `record` escalate
a function up the ladder when the cheaper model fails to make progress.

Read-only except for the attempt log. Examples (run from repo root):

  python3 tools/route_functions.py summary                 # project overview
  python3 tools/route_functions.py unit Pack/RPUtility/RPUtlMapData
  python3 tools/route_functions.py next --limit 20          # cheapest useful work
  python3 tools/route_functions.py next --tier A --limit 50 # batch for Haiku
  python3 tools/route_functions.py record fn_801BF6C4 sonnet nogain
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPORT = Path("build/RZTE01_01/report.json")
ASM_ROOT = Path("build/RZTE01_01/asm")
LOG = Path("build/evidence/routing-log.jsonl")
# Optional: `python3 tools/near_miss.py --json build/evidence/near_miss.json` adds shape hints.
# A near-miss with a control-flow/declaration hint goes to a sonnet hand-fix before the
# permuter: on 2026-10-16 those closed 18 fns, while permuter/opus closed none of the
# register-only ones (lessons 2026-10-16-label-only-diffs-*, -branch-shape-*).
SHAPE = Path("build/evidence/near_miss.json")

# Escalation ladder. "permuter" = run decomp-permuter (no model usage);
# "park" = stop, record in handoff, revisit after surrounding types improve.
# Opus is the ceiling: the user's plan has no Fable access (2026-10-08).
LADDER = ["haiku", "sonnet", "opus", "park"]
# Tier C no longer starts at the permuter (user decision 2026-10-26: structural levers first;
# the permuter is a last resort for a diagnosed register residue, run by hand and recorded as "permuter").
TIER_START = {"A": "haiku", "B": "sonnet", "C": "sonnet", "D": "opus"}
NOGAIN_LIMIT = 2  # consecutive no-gain attempts at one model before escalating

TIER_DESC = {
    "A": "trivial: batch many per session",
    "B": "normal",
    "C": "near-miss (>=97%): sonnet with the playbook structural checklist (+ shape hints), then opus, then park",
    "D": "hard: large/loops/float-heavy/unknown types",
}

INSN = re.compile(r"^/\* [0-9A-F]{8} [0-9A-F]{8}  (?:[0-9A-F]{2} ){4}\*/\t(\S+)\s*(.*)$")
FN = re.compile(r"^\.fn (\S+),")
ENDFN = re.compile(r"^\.endfn ")


def parse_asm(path: Path) -> dict[str, dict]:
    """Per-function features from a DTK asm listing."""
    feats: dict[str, dict] = {}
    if not path.exists():
        return feats
    cur = None
    for line in path.read_text(errors="replace").splitlines():
        m = FN.match(line)
        if m:
            cur = feats.setdefault(m.group(1), Counter())
            continue
        if ENDFN.match(line):
            cur = None
            continue
        if cur is None:
            continue
        m = INSN.match(line)
        if not m:
            continue
        op, args = m.group(1), m.group(2)
        cur["insns"] += 1
        if op in ("bl",):
            cur["calls"] += 1
        elif op in ("bctrl", "bctr"):
            cur["indirect"] += 1
        elif op.startswith("b") and op not in ("blr", "b") and ".L_" in args:
            cur["cond"] += 1
        if op.startswith("b") and ".L_" in args:
            # backward branch => loop
            addr = int(line[3:11], 16)
            tgt = re.search(r"\.L_([0-9A-F]{8})", args)
            if tgt and int(tgt.group(1), 16) <= addr:
                cur["loops"] += 1
        if op.startswith("ps_") or op.startswith("psq_"):
            cur["paired"] += 1
        elif op.startswith("f") or op in ("lfs", "lfd", "stfs", "stfd"):
            cur["float"] += 1
        if op in ("mtctr",) and cur["indirect"] == 0:
            pass
        if op == "stwu" and "r1" in args:
            m2 = re.search(r"-0x([0-9A-F]+)\(r1\)", args, re.I)
            if m2:
                cur["frame"] = int(m2.group(1), 16)
    return feats


def classify(size: int, fuzzy: float | None, f: dict, named: bool) -> tuple[str, list[str]]:
    why = []
    if fuzzy is not None and fuzzy >= 97.0:
        return "C", [f"{fuzzy:.1f}% already"]
    insns = f.get("insns", size // 4)
    loops, cond, calls = f.get("loops", 0), f.get("cond", 0), f.get("calls", 0)
    fl, ps, ind = f.get("float", 0), f.get("paired", 0), f.get("indirect", 0)

    score = 0
    if insns > 400: score += 3; why.append(f"{insns} insns")
    elif insns > 150: score += 2; why.append(f"{insns} insns")
    elif insns > 40: score += 1
    if loops >= 3: score += 2; why.append(f"{loops} loops")
    elif loops: score += 1
    if cond > 25: score += 2; why.append(f"{cond} branches")
    elif cond > 8: score += 1
    if ps: score += 2; why.append("paired-single")
    if fl > 40: score += 1; why.append("float-heavy")
    if ind > 3: score += 1; why.append(f"{ind} virtual calls")
    if not named and insns > 60: score += 1; why.append("unnamed/unknown types")

    if insns <= 16 and loops == 0 and cond <= 1 and calls <= 1 and not ps:
        return "A", why or ["tiny"]
    if score >= 4:
        return "D", why
    return "B", why or ["moderate"]


def load_log() -> dict[str, list[dict]]:
    out: dict[str, list[dict]] = defaultdict(list)
    if LOG.exists():
        for line in LOG.read_text().splitlines():
            if line.strip():
                e = json.loads(line)
                out[e["function"]].append(e)
    return out


def load_shape() -> dict[str, list[str]]:
    """symbol -> near_miss.py shape hints, if a near_miss JSON report was saved."""
    if not SHAPE.exists():
        return {}
    try:
        return {f["sym"]: f["hints"] for f in json.loads(SHAPE.read_text()) if f.get("hints")}
    except (ValueError, KeyError):
        return {}


def recommend(tier: str, attempts: list[dict], shape: bool = False) -> str:
    """Start model for tier, escalated by recorded consecutive no-gain attempts."""
    if shape and not any(a["model"] == "sonnet" for a in attempts):
        return "sonnet"
    model = TIER_START[tier]
    if model == "permuter":
        if not any(a["model"] == "permuter" for a in attempts):
            return "permuter"
        model = "opus"
    streak: Counter = Counter()
    for a in attempts:
        if a["result"] in ("gain", "match"):
            streak.clear()
        else:
            streak[a["model"]] += 1
    while model != "park" and streak[model] >= NOGAIN_LIMIT:
        model = LADDER[LADDER.index(model) + 1]
    return model


def collect(unit_filter: str | None = None):
    rep = json.loads(REPORT.read_text())
    log = load_log()
    shape = load_shape()
    rows = []
    for u in rep["units"]:
        uname = u["name"].removeprefix("main/")
        if unit_filter and unit_filter not in uname:
            continue
        fns = u.get("functions") or []
        if not fns:
            continue
        has_src = bool(u.get("metadata", {}).get("source_path"))
        asm = parse_asm(ASM_ROOT / f"{uname}.s")
        for fn in fns:
            fz = fn.get("fuzzy_match_percent")
            if fz == 100.0:
                continue
            name = fn["name"]
            size = int(fn.get("size", 0))
            named = not re.match(r"(fn|func|lbl)_[0-9A-Fa-f]{8}", name)
            tier, why = classify(size, fz, asm.get(name, {}), named)
            hints = shape.get(name) if fz is not None and fz >= 80.0 else None
            if hints:
                why = why + ["shape: " + ",".join(hints)]
            atts = log.get(name, [])
            rows.append({
                "unit": uname, "function": name, "size": size,
                "fuzzy": fz, "tier": tier, "model": recommend(tier, atts, bool(hints)),
                "why": ", ".join(why), "attempts": len(atts), "has_source": has_src,
                "demangled": fn.get("metadata", {}).get("demangled_name", ""),
            })
    return rows


def cmd_summary(a):
    rows = collect(a.filter)
    by_unit: dict[str, list] = defaultdict(list)
    for r in rows:
        by_unit[r["unit"]].append(r)
    tiers = Counter(r["tier"] for r in rows)
    tbytes = Counter()
    for r in rows:
        tbytes[r["tier"]] += r["size"]
    print(f"{len(rows)} unmatched functions")
    for t in "ABCD":
        print(f"  tier {t} ({TIER_DESC[t]}): {tiers[t]} fns, {tbytes[t]/1024:.0f} KB -> start {TIER_START[t]}")
    print("\nObjects closest to completion (few, cheap functions left):")
    def cost(rs):
        w = {"A": 1, "B": 3, "C": 2, "D": 8}
        return sum(w[r["tier"]] for r in rs)
    for unit, rs in sorted(by_unit.items(), key=lambda kv: cost(kv[1]))[: a.limit]:
        t = Counter(r["tier"] for r in rs)
        lead = max(rs, key=lambda r: "ABCD".index(r["tier"]) if r["tier"] != "C" else 1)
        print(f"  {unit:55s} {len(rs):3d} left  A{t['A']} B{t['B']} C{t['C']} D{t['D']}  lead model: {lead['model']}")


def cmd_unit(a):
    rows = collect(a.unit)
    if a.json:
        json.dump(rows, sys.stdout, indent=1); return
    for r in sorted(rows, key=lambda r: (r["unit"], "ACBD".index(r["tier"]))):
        fz = "  -  " if r["fuzzy"] is None else f"{r['fuzzy']:5.1f}"
        print(f"{r['tier']} {r['model']:8s} {fz}% {r['size']:5d}B  {r['function']:40s} {r['why']}")


def cmd_next(a):
    rows = [r for r in collect(a.filter) if r["model"] != "park"]
    if a.tier:
        rows = [r for r in rows if r["tier"] == a.tier]
    if a.model:
        rows = [r for r in rows if r["model"] == a.model]
    # Prefer objects nearest completion, then cheap tiers.
    left = Counter(r["unit"] for r in rows)
    rows.sort(key=lambda r: (left[r["unit"]], "ACBD".index(r["tier"]), r["size"]))
    for r in rows[: a.limit]:
        fz = "  -  " if r["fuzzy"] is None else f"{r['fuzzy']:5.1f}"
        print(f"{r['tier']} {r['model']:8s} {fz}% {r['size']:5d}B {r['unit']}  {r['function']}")


def cmd_record(a):
    LOG.parent.mkdir(parents=True, exist_ok=True)
    with LOG.open("a") as fh:
        fh.write(json.dumps({"function": a.function, "model": a.model,
                             "result": a.result, "note": a.note or ""}) + "\n")
    rows = [r for r in collect() if r["function"] == a.function]
    nxt = rows[0]["model"] if rows else "(matched / not in report)"
    print(f"recorded; next recommendation for {a.function}: {nxt}")


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("summary"); s.add_argument("--filter"); s.add_argument("--limit", type=int, default=25)
    s.set_defaults(func=cmd_summary)
    s = sub.add_parser("unit"); s.add_argument("unit"); s.add_argument("--json", action="store_true")
    s.set_defaults(func=cmd_unit)
    s = sub.add_parser("next"); s.add_argument("--filter"); s.add_argument("--tier", choices=list("ABCD"))
    s.add_argument("--model"); s.add_argument("--limit", type=int, default=20); s.set_defaults(func=cmd_next)
    s = sub.add_parser("record"); s.add_argument("function"); s.add_argument("model", choices=LADDER[:-1] + ["permuter"])
    s.add_argument("result", choices=["gain", "nogain", "match", "fail"]); s.add_argument("--note")
    s.set_defaults(func=cmd_record)
    a = p.parse_args()
    for path in (REPORT,):
        if not path.exists():
            sys.exit(f"missing {path}; run `ninja progress` first")
    a.func(a)


if __name__ == "__main__":
    main()
