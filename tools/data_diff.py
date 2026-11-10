#!/usr/bin/env python3
"""Explain why a unit's data sections do not match the original.

Reads the target and built ELF objects directly (no objdiff, no build), cuts
each data section into atoms (one per symbol; pooled strings are split per
string), and compares the two sides. Each inexact section gets one category:

  ORDER    same atoms, different order     -> function/definition/emit order
  EXTRA    ours has atoms the target lacks -> extra constant/string/static
  MISSING  target has atoms ours lacks     -> a constant/string the code never
                                              produces (dead code, inline, ...)
  MIXED    both extra and missing          -> usually a wrong constant value
  PAD      same atoms and order, bytes or size differ (alignment/padding)
  TAIL     same atoms, but the target has trailing zero bytes ours lacks
           (alignment padding the split includes and the linker adds); benign
  STRAY    ours has extra atoms that the final link would drop: nothing in the
           code references them, or they are function-local statics of inlines
           (@LOCAL@..., weak). The original splits come from the linked DOL, so
           the target has no copy; it is not a source bug. Verified example:
           nw4r policyTable is `scope:weak` with one surviving copy in
           symbols.txt, and cm2hw survives in 2 of ~150 including units.
  BSS      .bss/.sbss size differs

For EXTRA/MISSING atoms the referencing functions are listed, which ties the
data problem back to specific code.

  python3 tools/data_diff.py                        # summary of all units
  python3 tools/data_diff.py --unit RPSndAudioMgr   # per-atom detail
  python3 tools/data_diff.py --list MISSING         # units/sections in a category
  python3 tools/data_diff.py --section .sdata2      # restrict to one section

Advisory: atoms are cut at symbol boundaries, so a wrong split in
config/*/splits.txt or symbols.txt can look like EXTRA/MISSING. Reads only;
run from the repo root or pass --root.
"""
import argparse
import json
import os
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

DATA_SECTIONS = {".data", ".rodata", ".sdata", ".sdata2", ".ctors", ".dtors", ".init", ".extab", ".extabindex"}
BSS_SECTIONS = {".bss", ".sbss", ".sbss2"}
PRINTABLE = set(range(0x20, 0x7F)) | {0x09, 0x0A, 0x0D}


class Elf:
    """Minimal ELF32 big-endian relocatable reader."""

    def __init__(self, path: str):
        b = Path(path).read_bytes()
        self.b = b
        shoff, = struct.unpack_from(">I", b, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from(">HHH", b, 0x2E)
        raw = [struct.unpack_from(">10I", b, shoff + i * shentsize) for i in range(shnum)]
        names = raw[shstrndx]
        self.sections = []
        for name, typ, flags, addr, off, size, link, info, align, entsize in raw:
            self.sections.append({"name": self._str(names[4], name), "type": typ, "off": off,
                                  "size": size, "link": link, "info": info, "align": align})
        self.symbols = []
        for s in self.sections:
            if s["type"] == 2:  # SHT_SYMTAB
                strtab = self.sections[s["link"]]["off"]
                for i in range(s["size"] // 16):
                    n, val, size, info, other, shndx = struct.unpack_from(">IIIBBH", b, s["off"] + i * 16)
                    self.symbols.append({"name": self._str(strtab, n), "value": val, "size": size,
                                         "type": info & 0xF, "weak": (info >> 4) == 2, "shndx": shndx})
                break

    def _str(self, base: int, off: int) -> str:
        end = self.b.index(b"\0", base + off)
        return self.b[base + off:end].decode("latin1")

    def data(self, idx: int) -> bytes:
        s = self.sections[idx]
        return b"" if s["type"] == 8 else self.b[s["off"]:s["off"] + s["size"]]  # 8 = NOBITS

    def relocs(self, target_idx: int):
        """Yield (offset, sym_index, type, addend) for relocations applying to a section."""
        for s in self.sections:
            if s["type"] == 4 and s["info"] == target_idx:
                for i in range(s["size"] // 12):
                    off, info, add = struct.unpack_from(">IIi", self.b, s["off"] + i * 12)
                    yield off, info >> 8, info & 0xFF, add


def is_unnamed(name: str) -> bool:
    return name.startswith("@") or name.startswith("lbl_") or name.startswith("$")


def split_strings(chunk: bytes):
    """Split a chunk that is NUL-separated printable text into strings; else None."""
    body = chunk.rstrip(b"\0")
    if len(body) < 2 or not all(c in PRINTABLE or c == 0 for c in body) or body[0] == 0:
        return None
    return [p for p in body.split(b"\0") if p]


def atoms_for(elf: Elf, idx: int, sec_name: str):
    """List of (offset, key, label) atoms for one section, in address order."""
    data = elf.data(idx)
    syms = sorted((s for s in elf.symbols if s["shndx"] == idx and s["type"] in (0, 1, 2) and s["name"]),
                  key=lambda s: s["value"])
    # reloc map for pointer-bearing data: offset -> (type, target, addend)
    rel = {off: (typ, elf.symbols[si]["name"] if si < len(elf.symbols) else "?", add)
           for off, si, typ, add in elf.relocs(idx)}
    cuts, seen = [], set()
    for s in syms:
        if s["value"] not in seen and s["value"] < len(data):
            seen.add(s["value"])
            cuts.append((s["value"], s["name"], s["size"]))
    if not cuts or cuts[0][0] != 0:
        cuts.insert(0, (0, "<start>", 0))
    out = []
    for n, (start, name, size) in enumerate(cuts):
        end = cuts[n + 1][0] if n + 1 < len(cuts) else len(data)
        if size and start + size < end:
            end = start + size
        chunk = data[start:end]
        if not chunk.strip(b"\0") and not any(start <= o < end for o in rel):
            continue  # pure padding
        parts = split_strings(chunk) if sec_name in (".data", ".rodata", ".sdata") else None
        if parts and len(parts) >= 1:
            for p in parts:
                out.append((start, ("s", p), name))
            continue
        pointers = tuple(sorted((o - start, t, "U" if is_unnamed(tn) else tn, a if not is_unnamed(tn) else 0)
                                for o, (t, tn, a) in rel.items() if start <= o < end))
        payload = chunk.rstrip(b"\0") if sec_name in (".data", ".rodata") else chunk
        out.append((start, ("b", len(chunk), payload, pointers), name))
    return out


def decode(key, sec_name: str) -> str:
    if key[0] == "s":
        return repr(key[1].decode("latin1"))[:60]
    _, n, payload, ptrs = key
    if sec_name == ".sdata2" and n in (4, 8):
        try:
            return f"{struct.unpack('>f' if n == 4 else '>d', payload.ljust(n, b'\0'))[0]!r}{'f' if n == 4 else ''}"
        except struct.error:
            pass
    txt = payload[:16].hex() + ("…" if len(payload) > 16 else "")
    return f"{n}B {txt}" + (f" +{len(ptrs)}ptr" if ptrs else "")


def referrers(elf: Elf, data_idx: int, atoms):
    """Map atom offset -> set of function names that relocate into it."""
    funcs = sorted((s["value"], s["size"], s["name"], s["shndx"]) for s in elf.symbols if s["type"] == 2)
    starts = [a[0] for a in atoms]
    out = defaultdict(set)
    for ti, t in enumerate(elf.sections):
        if not t["name"].startswith(".text"):
            continue
        fl = [f for f in funcs if f[3] == ti]
        for off, si, typ, add in elf.relocs(ti):
            if si >= len(elf.symbols):
                continue
            sym = elf.symbols[si]
            if sym["shndx"] != data_idx:
                continue
            target = sym["value"] + (add if sym["type"] == 3 else 0)
            owner = max((s for s in starts if s <= target), default=None)
            fn = next((f[2] for f in fl if f[0] <= off < f[0] + max(f[1], 1)), None)
            if owner is not None and fn:
                out[owner].add(fn)
    return out


def present_in(key, blob: bytes) -> bool:
    """True if an atom's bytes occur in the other side's section (moved, not absent)."""
    if key[0] == "s":
        return key[1] + b"\0" in blob
    _, n, payload, ptrs = key
    return not ptrs and len(payload) >= 4 and payload in blob


def residual(atoms, cnt: Counter, other: bytes):
    """Atoms still unexplained: in cnt (multiset surplus) and not found in the other side."""
    left, out = Counter(cnt), []
    for off, key, sym in atoms:
        if left.get(key, 0) > 0:
            left[key] -= 1
            if not present_in(key, other):
                out.append((off, key, sym))
    return out


def split_stray(ours: Elf, oi: int, all_atoms, extra_atoms):
    """(stray, real) partition of extra atoms: unreferenced or weak local statics are link-time artifacts."""
    refs = referrers(ours, oi, all_atoms) if extra_atoms else {}
    weak = {s["name"] for s in ours.symbols if s["weak"]}
    stray, real = [], []
    for atom in extra_atoms:
        off, key, sym = atom
        users = refs.get(off)
        # weak data and data used only by weak (inline/template) functions: the linker keeps one copy
        deduped = sym in weak or sym.startswith("@LOCAL@") or (users and all(f in weak for f in users))
        (stray if deduped or not users else real).append(atom)
    return stray, real


def compare_section(name, tgt: Elf, ti, ours: Elf, oi):
    """Return None if exact, else dict(category, extra, missing, sizes)."""
    td, od = tgt.data(ti), ours.data(oi)
    if td == od and not _reloc_names_differ(tgt, ti, ours, oi):
        return None
    ta, oa = atoms_for(tgt, ti, name), atoms_for(ours, oi, name)
    tc, oc = Counter(a[1] for a in ta), Counter(a[1] for a in oa)
    extra_atoms = residual(oa, oc - tc, td)
    missing_atoms = residual(ta, tc - oc, od)
    stray_atoms, extra_atoms = split_stray(ours, oi, oa, extra_atoms)
    extra, missing = Counter(k for _, k, _ in extra_atoms), Counter(k for _, k, _ in missing_atoms)
    moved = (sum((oc - tc).values()) + sum((tc - oc).values())
             - sum(extra.values()) - sum(missing.values()) - len(stray_atoms))
    if extra and missing:
        cat = "MIXED"
    elif extra:
        cat = "EXTRA"
    elif missing:
        cat = "MISSING"
    elif stray_atoms and not moved and [a[1] for a in ta] == [a[1] for a in oa if a not in stray_atoms]:
        cat = "STRAY"
    elif moved or [a[1] for a in ta] != [a[1] for a in oa if a not in stray_atoms]:
        cat = "ORDER"
    elif len(td) > len(od) and td.startswith(od) and not td[len(od):].strip(b"\0"):
        cat = "TAIL"
    else:
        cat = "PAD"
    return {"stray_atoms": stray_atoms, "cat": cat, "tsize": len(td), "osize": len(od), "extra": extra, "missing": missing,
            "tatoms": ta, "oatoms": oa, "extra_atoms": extra_atoms, "missing_atoms": missing_atoms, "moved": moved}


def _reloc_names_differ(tgt, ti, ours, oi) -> bool:
    return False  # byte equality is the data-level criterion; naming is near_miss.py's DATA-REF


def unit_sections(elf: Elf):
    return {s["name"]: i for i, s in enumerate(elf.sections) if s["name"] in DATA_SECTIONS | BSS_SECTIONS}


def analyze_unit(unit, only_sec):
    tgt, ours = Elf(unit["target_path"]), Elf(unit["base_path"])
    ts, os_ = unit_sections(tgt), unit_sections(ours)
    rows = []
    for name in sorted(set(ts) | set(os_)):
        if only_sec and name != only_sec:
            continue
        if name in BSS_SECTIONS:
            a = tgt.sections[ts[name]]["size"] if name in ts else 0
            b = ours.sections[os_[name]]["size"] if name in os_ else 0
            if a != b:
                # the split rounds the section up to its alignment; ours is the raw sum of objects
                align = max(tgt.sections[ts[name]]["align"], 4) if name in ts else 4
                tail = 0 < b < a < b + align and a % align == 0
                rows.append({"sec": name, "cat": "TAIL" if tail else "BSS", "tsize": a, "osize": b,
                             "extra": Counter(), "missing": Counter()})
            continue
        if name not in ts or name not in os_:
            side = ours if name in os_ else tgt
            idx = (os_ if name in os_ else ts)[name]
            all_atoms = atoms_for(side, idx, name)
            stray_atoms, real_atoms = split_stray(ours, idx, all_atoms, all_atoms) if name in os_ else ([], [])
            has_real = bool(real_atoms) or name not in os_
            rows.append({"sec": name, "cat": "STRAY" if (name in os_ and not has_real) else ("EXTRA" if name in os_ else "MISSING"),
                         "stray_atoms": stray_atoms,
                         "extra_atoms": real_atoms if name in os_ else [], "missing_atoms": [] if name in os_ else all_atoms,
                         "tatoms": [] if name in os_ else all_atoms, "oatoms": all_atoms if name in os_ else [],
                         "tsize": tgt.sections[ts[name]]["size"] if name in ts else 0,
                         "osize": ours.sections[os_[name]]["size"] if name in os_ else 0,
                         "extra": Counter(k for _, k, _ in real_atoms), "missing": Counter(k for _, k, _ in all_atoms) if name in ts else Counter()})
            continue
        r = compare_section(name, tgt, ts[name], ours, os_[name])
        if r:
            r["sec"] = name
            rows.append(r)
    return tgt, ours, ts, os_, rows


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=".")
    ap.add_argument("--unit", action="append", default=[], help="units whose name contains this; with one match, print atom detail")
    ap.add_argument("--section", help="restrict to one section, e.g. .sdata2")
    ap.add_argument("--list", metavar="CATEGORY", help="list unit/sections in ORDER|EXTRA|MISSING|MIXED|PAD|TAIL|STRAY|BSS")
    ap.add_argument("--limit", type=int, default=25)
    ap.add_argument("--group-depth", type=int, default=2)
    ap.add_argument("--side", choices=["extra", "missing", "stray"], help="show only recurring atoms of this kind (up to --limit)")
    ap.add_argument("--json", metavar="PATH")
    a = ap.parse_args()
    os.chdir(a.root)

    units = [u for u in json.loads(Path("objdiff.json").read_text())["units"]
             if u.get("base_path") and Path(u["base_path"]).exists() and Path(u["target_path"]).exists()
             and (not a.unit or any(q in u["name"] for q in a.unit))]
    results = []
    for u in units:
        name = u["name"].removeprefix("main/")
        try:
            tgt, ours, ts, os_, rows = analyze_unit(u, a.section)
        except (ValueError, struct.error, IndexError) as e:
            print(f"skip {name}: {e}", file=sys.stderr)
            continue
        results.append((name, tgt, ours, ts, os_, rows))

    flat = [(n, r) for n, *_, rows in results for r in rows]
    if a.json:
        Path(a.json).parent.mkdir(parents=True, exist_ok=True)
        Path(a.json).write_text(json.dumps([{"unit": n, "sec": r["sec"], "cat": r["cat"], "tsize": r["tsize"],
                                             "osize": r["osize"], "extra": sum(r["extra"].values()),
                                             "missing": sum(r["missing"].values())} for n, r in flat], indent=1))

    if len(a.unit) >= 1 and len(results) == 1:
        n, tgt, ours, ts, os_, rows = results[0]
        print(f"{n}: {len(rows)} inexact section(s)")
        for r in rows:
            print(f"\n{r['sec']}  {r['cat']}  target {r['tsize']}B  ours {r['osize']}B  ({r['osize'] - r['tsize']:+d})")
            if r.get("moved"):
                print(f"  {r['moved']} atom(s) present on both sides but in different positions")
            if r.get("stray_atoms"):
                print(f"  stray (link would drop; not a source bug): {len(r['stray_atoms'])} atom(s)")
                for off, key, sym in r["stray_atoms"][:a.limit]:
                    print(f"    +0x{off:x} {decode(key, r['sec'])}  [{sym[:48]}]")
            for label, res, elf, idx, allatoms in (("missing (target only)", r.get("missing_atoms", []), tgt, ts.get(r["sec"]), r.get("tatoms", [])),
                                                    ("extra (ours only)", r.get("extra_atoms", []), ours, os_.get(r["sec"]), r.get("oatoms", []))):
                if not res:
                    continue
                refs = referrers(elf, idx, allatoms) if idx is not None and allatoms else {}
                print(f"  {label}: {len(res)} atom(s)")
                for off, key, sym in res[:a.limit]:
                    fns = sorted(refs.get(off, ()))
                    print(f"    +0x{off:x} {decode(key, r['sec'])}  [{sym[:34]}]  <- " + (", ".join(f[:40] for f in fns[:3]) or "no code ref"))
        return

    by_cat = Counter(r["cat"] for _, r in flat)
    units_bad = len({n for n, _ in flat})
    real_units = len({n for n, r in flat if r["cat"] not in ("STRAY", "TAIL")})
    print(f"{len(results)} units scanned, {units_bad} with inexact data/bss sections "
          f"({real_units} once link-time strays and tail padding are set aside), {len(flat)} sections")
    secs = sorted({r["sec"] for _, r in flat})
    cats = ["ORDER", "EXTRA", "MISSING", "MIXED", "PAD", "TAIL", "STRAY", "BSS"]
    print(f"\n{'section':<11}" + "".join(f"{c:>9}" for c in cats) + f"{'total':>8}")
    for s in secs:
        c = Counter(r["cat"] for _, r in flat if r["sec"] == s)
        print(f"{s:<11}" + "".join(f"{c.get(k, 0):>9}" for k in cats) + f"{sum(c.values()):>8}")
    print(f"{'all':<11}" + "".join(f"{by_cat.get(k, 0):>9}" for k in cats) + f"{len(flat):>8}")

    if a.list:
        cat = a.list.upper()
        rows = sorted(((n, r) for n, r in flat if r["cat"] == cat),
                      key=lambda x: (sum(x[1]["extra"].values()) + sum(x[1]["missing"].values()), x[0]))
        print(f"\n{cat}: {len(rows)} section(s), fewest differing atoms first")
        for n, r in rows[:a.limit]:
            print(f"  {n}  {r['sec']:<8} {r['tsize']}B -> {r['osize']}B  -{sum(r['missing'].values())}/+{sum(r['extra'].values())} atoms")
        return

    clusters = defaultdict(set)
    for n, r in flat:
        for side, atoms in (("extra", r.get("extra_atoms", [])), ("missing", r.get("missing_atoms", [])), ("stray", r.get("stray_atoms", []))):
            for _, key, sym in atoms:
                label = sym if not is_unnamed(sym) else decode(key, r["sec"])
                clusters[(side, r["sec"], re.sub(r"@\d+$", "", label)[:70])].add(n)
    print(f"\natoms that recur across units (a shared header/inline is the likely cause)")
    shown = 0
    for (side, sec, label), us in sorted(clusters.items(), key=lambda kv: -len(kv[1])):
        if len(us) > 1 and (not a.side or side == a.side) and shown < (a.limit if a.side else min(a.limit, 10)):
            shown += 1
            print(f"  {len(us):>3} units  {side:<7} {sec:<8} {label}")

    groups = defaultdict(Counter)
    for n, r in flat:
        groups["/".join(n.split("/")[:a.group_depth])][r["cat"]] += 1
    print(f"\ncategory mix by group (top {min(a.limit, 12)})")
    for g, c in sorted(groups.items(), key=lambda kv: -sum(kv[1].values()))[:min(a.limit, 12)]:
        print(f"  {g:<28}{sum(c.values()):>4}  " + ", ".join(f"{k} {v}" for k, v in c.most_common(4)))


if __name__ == "__main__":
    main()
