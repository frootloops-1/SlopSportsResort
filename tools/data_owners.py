#!/usr/bin/env python3
"""Who owns the symbols of a lumped data range? Evidence per object, for re-splitting a .data/.sdata/.sbss/.sdata2/.rodata range.

  python3 tools/data_owners.py <section> <start> <end> [--lines N]
  e.g. python3 tools/data_owners.py .data 0x803CA6B0 0x803CA738
       python3 tools/data_owners.py .sbss 0x804BF998 0x804BFA10

For every symbol of config/RZTE01_01/symbols.txt in [start,end) of the section it prints one row:
  addr size name | split-owner | refs | slots | src | suggest
  refs    asm units that mention the symbol (build/RZTE01_01/asm/<unit>.s, only units listed in splits.txt; stale auto_*.s and
          main.s are skipped), count per unit; a trailing 'w' marks stores (st*), 'd' marks data words (.4byte/.rel) referring to it
  slots   for tables/vtables: the units that own the functions in the object's own .4byte/.rel slots (vtable slot functions
          are defined by the class' TU: see docs/lessons/2026-11-01-rpbow-0x803ca940-*.md)
  src     D=defined / X=extern'd / u=used in src/ and include/ files (unit basename, or inc:<header>)
  suggest owner by evidence: the single defining src unit, else the slot-function majority, else the storing unit, else the
          first referencing unit in link order (= splits.txt order); in brackets, why
Header lines list the splits.txt owner ranges that overlap the range. Needs build/RZTE01_01/asm (run ninja once). Output capped.
"""
import collections
import os
import re
import sys
from pathlib import Path

CFG = Path("config/RZTE01_01")
ASM = Path("build/RZTE01_01/asm")
TOK = re.compile(r"@?[A-Za-z0-9_$]+")


def parse_splits():
    """unit -> {section: [(start,end)]}, in link order."""
    units = collections.OrderedDict()
    cur = None
    for line in (CFG / "splits.txt").read_text().splitlines():
        m = re.match(r"^(\S.*):\s*$", line)
        if m and not line.startswith("Sections"):
            cur = m.group(1)
            units[cur] = collections.defaultdict(list)
            continue
        m = re.match(r"^\s+(\.\w+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)", line)
        if m and cur:
            units[cur][m.group(1)].append((int(m.group(2), 16), int(m.group(3), 16)))
    return units


def parse_symbols():
    syms = []  # (addr, size, name, section)
    for line in (CFG / "symbols.txt").read_text().splitlines():
        m = re.match(r"(\S+) = (\.\w+):0x([0-9A-Fa-f]+);(.*)", line)
        if m:
            sz = re.search(r"size:0x([0-9A-Fa-f]+)", m.group(4))
            syms.append((int(m.group(3), 16), int(sz.group(1), 16) if sz else 0, m.group(1), m.group(2)))
    return syms


def short(unit):
    return os.path.basename(unit).rsplit(".", 1)[0] if not unit.startswith("inc:") else unit


def owner_of(units, sec, addr):
    for u, secs in units.items():
        for a, b in secs.get(sec, ()):
            if a <= addr < b:
                return u
    return None


def fmt_counts(c, flags, limit=4):
    items = sorted(c.items(), key=lambda kv: -kv[1])
    out = []
    for u, n in items[:limit]:
        f = flags.get(u, "")
        out.append(f"{short(u)}:{n}{f}")
    if len(items) > limit:
        out.append(f"+{len(items) - limit}")
    return " ".join(out) or "-"


def main():
    args = [a for a in sys.argv[1:]]
    cap = 60
    if "--lines" in args:
        i = args.index("--lines")
        cap = int(args[i + 1])
        del args[i:i + 2]
    if len(args) != 3:
        sys.exit(__doc__)
    sec, start, end = args[0], int(args[1], 16), int(args[2], 16)
    if not sec.startswith("."):
        sec = "." + sec
    units = parse_splits()
    order = {u: i for i, u in enumerate(units)}
    allsyms = parse_symbols()
    targets = [s for s in allsyms if s[3] == sec and start <= s[0] < end]
    if not targets:
        sys.exit(f"no symbols in {sec} {start:#x}..{end:#x}")
    names = {t[2] for t in targets}
    addr_of = {s[2]: s for s in allsyms}

    # (c) splits owners overlapping the range
    rows_hdr = []
    for u, secs in units.items():
        for a, b in secs.get(sec, ()):
            if a < end and b > start:
                rows_hdr.append(f"  split {a:#x}-{b:#x} {u}")

    # (a) asm references
    refs = {n: collections.Counter() for n in names}
    flags = {n: collections.defaultdict(str) for n in names}
    body = {}  # name -> list of slot symbols (from the asm that defines it)
    skipped = 0
    for u in units:
        p = ASM / (re.sub(r"\.(cpp|c)$", "", u) + ".s")
        if not p.is_file():
            skipped += 1
            continue
        text = p.read_text(errors="replace")
        hit = names & set(TOK.findall(text))
        if not hit:
            continue
        cur = None
        for line in text.splitlines():
            if line.startswith(".obj "):
                cur = line[5:].split(",")[0].strip().strip('"')
                continue
            if line.startswith(".endobj"):
                cur = None
                continue
            toks = set(TOK.findall(line)) & hit
            if cur in names and line.lstrip().startswith((".4byte", ".rel")):
                body.setdefault(cur, []).extend(t for t in TOK.findall(line) if t in addr_of and t != cur)
            for t in toks:
                if t == cur:
                    continue
                refs[t][u] += 1
                if line.lstrip().startswith((".4byte", ".rel")):
                    flags[t][u] += "d" if "d" not in flags[t][u] else ""
                else:
                    mn = re.search(r"\*/\s*(\w+)", line)
                    if mn and mn.group(1).startswith("st") and "w" not in flags[t][u]:
                        flags[t][u] += "w"

    # (b) source definitions / externs
    alias = {}
    for n in names:
        m = re.match(r"^([A-Za-z_]\w*?)__\d", n)
        alias[n] = m.group(1) if m and not n.startswith("__") else n
    want = {}
    for n, a in alias.items():
        want.setdefault(a, []).append(n)
    srcs = {n: {} for n in names}
    for root in ("src", "include"):
        for dp, _, fs in os.walk(root):
            for f in fs:
                if not f.endswith((".c", ".cpp", ".h", ".hpp", ".inc")):
                    continue
                fp = os.path.join(dp, f)
                text = Path(fp).read_text(errors="replace")
                hit = set(want) & set(TOK.findall(text))
                if not hit:
                    continue
                label = os.path.relpath(fp, "src").rsplit(".", 1)[0] if root == "src" else "inc:" + f
                for line in text.splitlines():
                    lt = set(TOK.findall(line)) & hit
                    for a in lt:
                        code = line.split("//")[0].replace('extern "C"', "").strip()
                        mpos = re.search(r"\b" + re.escape(a) + r"\b", code)
                        if not mpos:
                            continue
                        before, after = code[: mpos.start()], code[mpos.end():]
                        if "(" in before or "=" in before:
                            kind = "u"
                        elif before.lstrip().startswith("extern") or "extern " in before:
                            kind = "X"
                        elif re.match(r"\s*(\[[^\]]*\]\s*)*(=|;|\{)", after) and before.strip():
                            kind = "D"
                        else:
                            kind = "u"
                        for n in want[a]:
                            cur = srcs[n].get(label, "")
                            rank = {"D": 3, "X": 2, "u": 1, "": 0}
                            if rank[kind] > rank.get(cur, 0):
                                srcs[n][label] = kind

    def text_owner(sym):
        s = addr_of.get(sym)
        return owner_of(units, s[3], s[0]) if s else None

    print(f"{sec} {start:#x}-{end:#x}: {len(targets)} symbols; asm units without file/skipped: {skipped}")
    out = list(rows_hdr)
    out.append("addr size name | split-owner | refs | slots | src | suggest")
    for addr, size, name, _ in targets:
        own = owner_of(units, sec, addr)
        slotc = collections.Counter()
        for fn in body.get(name, []):
            o = text_owner(fn)
            if o:
                slotc[o] += 1
        defs = [u for u, k in srcs[name].items() if k == "D" and u in units or (k == "D" and re.sub(r"\.(cpp|c)$", "", u) in {re.sub(r"\.(cpp|c)$", "", x) for x in units})]
        xs = [u for u, k in srcs[name].items() if k == "X"]
        us = [u for u, k in srcs[name].items() if k == "u"]
        srcs_s = " ".join([f"D:{short(u)}" for u in defs] + [f"X:{short(u)}" for u in xs[:3]] + [f"u:{short(u)}" for u in us[:2]]) or "-"
        sug, why = None, ""
        full = {re.sub(r"\.(cpp|c)$", "", u): u for u in units}
        dunits = [full[u] for u in defs if u in full]
        stores = [u for u in refs[name] if "w" in flags[name][u]]
        by_link = sorted(refs[name], key=lambda u: order[u])
        if len(dunits) == 1:
            sug, why = dunits[0], "src-def"
        elif slotc:
            sug, why = slotc.most_common(1)[0][0], f"slot-fns {slotc.most_common(1)[0][1]}/{sum(slotc.values())}"
        elif stores:
            sug, why = sorted(stores, key=lambda u: order[u])[0], "stores"
        elif by_link:
            sug, why = by_link[0], "first ref"
        evidence = set(dunits) | set(slotc) | set(stores)
        if sug and (sug == own or own in evidence):
            sug_s = "= owner" + (f" [{why}]" if sug == own else f" (evidence also: {short(sug)} {why})")
        else:
            sug_s = f"{short(sug)} [{why}]" if sug else "?"
        out.append(f"{addr:#x} {size:#x} {name} | {short(own) if own else '-'} | {fmt_counts(refs[name], flags[name])} | "
                   f"{fmt_counts(slotc, {}, 2) if slotc else '-'} | {srcs_s} | {sug_s}")
    if len(out) > cap:
        print("\n".join(out[: cap - 1]))
        print(f"... {len(out) - cap + 1} more lines (use --lines N or narrow the range)")
    else:
        print("\n".join(out))


if __name__ == "__main__":
    main()
