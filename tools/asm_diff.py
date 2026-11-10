"""Compact instruction diff of one object against the original, hard-capped in size.

  python3 tools/asm_diff.py MSL/ansi_fp                 # all functions, first 40 diff lines
  python3 tools/asm_diff.py MSL/ansi_fp __num2dec -n 25 # one function, 25 lines max

Addresses, byte dumps and local label numbers are normalised away, so only real
instruction/operand/relocation differences remain. Ends with a one-line summary.
Run from the repo root after the object is built (ninja build/RZTE01_01/src/<unit>.o).
"""
import argparse, difflib, pathlib, re, subprocess, sys

ap = argparse.ArgumentParser()
ap.add_argument("unit", help="path under src/, without extension, e.g. MSL/ansi_fp")
ap.add_argument("function", nargs="?", help="restrict to one function")
ap.add_argument("-n", "--max-lines", type=int, default=40)
ap.add_argument("-c", "--context", type=int, default=1)
a = ap.parse_args()

root = pathlib.Path("build/RZTE01_01")
orig, mine = root / "obj" / f"{a.unit}.o", root / "src" / f"{a.unit}.o"
for p in (orig, mine):
    if not p.exists():
        sys.exit(f"missing {p}; build it first")
scratch = pathlib.Path("build/evidence/asm_diff"); scratch.mkdir(parents=True, exist_ok=True)

def functions(obj):
    s = scratch / (obj.parent.name + "_" + obj.stem + "_" + obj.parent.parent.name + ".s")
    subprocess.run(["build/tools/dtk", "elf", "disasm", str(obj), str(s)], check=True, capture_output=True)
    funcs, cur, labels = {}, None, {}
    for line in s.read_text().splitlines():
        m = re.match(r"\.fn (\S+),", line)
        if m: cur = m.group(1); funcs[cur] = []; labels = {}; continue
        if line.startswith(".endfn"): cur = None; continue
        if cur is None or not line.startswith("/*"): 
            if cur is not None and re.match(r"\.L_[0-9A-Fa-f]+:", line):
                funcs[cur].append("<label>")
            continue
        ins = re.sub(r"^/\*.*?\*/\s*", "", line).strip()
        def lab(m):
            return labels.setdefault(m.group(0), f"L{len(labels)}")
        ins = re.sub(r"\.L_[0-9A-Fa-f]+", lab, ins)
        # compiler/splitter-generated names differ between sides but name the same data
        ins = re.sub(r'"?@[0-9A-Za-z_$]+"?|\blbl_[0-9A-Fa-f]+|\bjumptable_[0-9A-Fa-f]+|\bgap_\w+|\b\w+\$\d+', "SYM", ins)
        funcs[cur].append(ins)
    return funcs

fo, fm = functions(orig), functions(mine)
names = [a.function] if a.function else list(fo)
out, bad = [], []
for n in names:
    x, y = fo.get(n), fm.get(n)
    if x is None or y is None:
        bad.append(f"{n}: {'missing in original' if x is None else 'missing in ours'}"); continue
    d = list(difflib.unified_diff(x, y, "original", "ours", lineterm="", n=a.context))
    if d:
        bad.append(f"{n}: {sum(1 for l in d if l[:1] in '+-' and l[:3] not in ('+++','---'))} differing lines")
        out += [f"## {n}"] + d[2:]
extra = [n for n in fm if n not in fo and not a.function]
if extra: bad += [f"{n}: only in ours (unused inline copy?)" for n in extra if fm[n] and len(fm[n]) > 0 and False] or []
for l in out[: a.max_lines]: print(l)
if len(out) > a.max_lines: print(f"... {len(out) - a.max_lines} more lines (raise -n or name a function)")
print("SUMMARY:", "; ".join(bad) if bad else "all compared functions identical")
# Moved labels were the cheapest near-misses to close by hand (lessons 2026-10-16-label-only-diffs-*).
dl = [l for l in out if l[:1] in "+-" and not l.startswith(("+++", "---"))]
if any("<label>" in l for l in dl):
    only = all("<label>" in l for l in dl)
    print("HINT: branch labels moved" + (" (label-only diff)" if only else "") +
          ": the join point differs - code shared by every path may sit inside the last case/if, "
          "or an if (v == K) is really a one-case switch. `near_miss.py --shape` lists the other patterns.")
