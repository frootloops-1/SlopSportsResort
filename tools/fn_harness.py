#!/usr/bin/env python3
"""One-function variant harness (docs/llm_matching_tricks.md section 4).

Compiles a unit with one function definition replaced by a variant, using the
unit's exact compiler and cflags from build.ninja, and scores the WHOLE function
against the target object (instruction-level diff count, relocations resolved to
symbol names, branch targets normalised). 0 differences = exact instructions.

Usage:
  python3 tools/fn_harness.py <unit> <fn> [variant.cpp ...] [--perm] [--max N] [--show]

  <unit>       e.g. Pack/RPSports/RPSportsCommon/RPSports_8020b340
  variant.cpp  file holding a full replacement definition of <fn> (from the
               signature line to the closing brace). Without variants, the
               current source is scored (sanity check: should equal verify.py).
  --perm       lines between `//PERM{` and `//PERM}` in a variant are permuted
               (every order, capped by --max); several blocks are permuted jointly.
  --show       print the normalised diff of the best variant (capped at 60 lines).

The real source file is never modified: the variant is written to a temporary
copy next to it (so relative includes still work) and deleted afterwards.
Prints one line per variant plus the best; exits 0.
"""
import argparse
import difflib
import itertools
import os
import re
import shlex
import signal
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDUMP = os.path.join(ROOT, "build/binutils/powerpc-eabi-objdump")


def ninja_block(unit):
    text = open(os.path.join(ROOT, "build.ninja")).read().replace("$\n", "")
    want = f"build build/RZTE01_01/src/{unit}.o:"
    for block in text.split("\n\n"):
        lines = block.split("\n")
        for i, line in enumerate(lines):
            if line.startswith(want):
                vars_ = {}
                for l in lines[i + 1:]:
                    m = re.match(r"\s+(\w+)\s*=\s*(.*)", l)
                    if m:
                        vars_[m.group(1)] = m.group(2)
                src = re.search(r"mwcc\w*\s+(\S+)", line).group(1)
                return src, vars_
    sys.exit(f"unit {unit} not found in build.ninja")


def find_def(src_text, fn):
    """Return (start, end) span of the definition of fn (column-0 signature, brace-matched)."""
    for m in re.finditer(r"^[A-Za-z][^\n;(]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(fn), src_text, re.M):
        i = m.end() - 1
        depth = 0
        for j in range(i, len(src_text)):
            c = src_text[j]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    return m.start(), j + 1
    sys.exit(f"definition of {fn} not found")


def disasm(obj, fn):
    out = subprocess.run([OBJDUMP, "-dr", "-EB", "-mpowerpc", "-M", "broadway",
                          f"--disassemble={fn}", obj], capture_output=True, text=True).stdout
    ins = []
    for line in out.split("\n"):
        m = re.match(r"\s+[0-9a-f]+:\s+(?:[0-9a-f]{2} ){4}\s*(.*)", line)
        if m:
            ins.append(m.group(1).split("#")[0].strip())
            continue
        m = re.match(r"\s+[0-9a-f]+:\s+(R_PPC_\w+)\s+(\S+)", line)
        if m and ins:
            # keep call targets; data symbols are named differently in our object
            # (`...data.0`, `@1234`) so only the relocation type is compared
            sym = re.sub(r"\+0x0$", "", m.group(2))
            ins[-1] += f" <{sym}>" if ins[-1].startswith("b") else f" <{m.group(1)}>"
    norm = []
    for s in ins:
        s = re.sub(r"\s+", " ", s)
        s = re.sub(r"^(b\w*[+-]?) (?:cr\d,)?[0-9a-f]+ <[^>]*>", r"\1 X", s)
        s = re.sub(r"^(b\w*[+-]?) (cr\d,)?[0-9a-f]+(?: <[^>]*>)?$", r"\1 \2X", s)
        norm.append(s)
    return norm


def score(a, b):
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    d = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            d += max(i2 - i1, j2 - j1)
    return d


def expand_perm(text, cap):
    blocks = list(re.finditer(r"//PERM\{\n(.*?)//PERM\}\n", text, re.S))
    if not blocks:
        yield "", text
        return
    lines = [b.group(1).splitlines(True) for b in blocks]
    prods = itertools.product(*[itertools.permutations(l) for l in lines])
    for n, combo in enumerate(prods):
        if n >= cap:
            return
        out, last = [], 0
        for b, perm in zip(blocks, combo):
            out.append(text[last:b.start()])
            out.append("".join(perm))
            last = b.end()
        out.append(text[last:])
        tag = " | ".join(" ".join(x.strip() for x in p) for p in combo)
        yield tag, "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("unit")
    ap.add_argument("fn")
    ap.add_argument("variants", nargs="*")
    ap.add_argument("--perm", action="store_true")
    ap.add_argument("--max", type=int, default=5040)
    ap.add_argument("--show", action="store_true")
    a = ap.parse_args()

    src, v = ninja_block(a.unit)
    src_path = os.path.join(ROOT, src)
    text = open(src_path).read()
    s0, e0 = find_def(text, a.fn)
    target = disasm(os.path.join(ROOT, f"build/RZTE01_01/obj/{a.unit}.o"), a.fn)
    if not target:
        sys.exit("target function not found in target object")
    cc = [os.path.join(ROOT, "build/tools/wibo"), os.path.join(ROOT, "build/tools/sjiswrap.exe"),
          os.path.join(ROOT, "build/compilers", v["mw_version"], "mwcceppc.exe")] + shlex.split(v["cflags"])

    cands = []
    if not a.variants:
        cands.append(("current", text[s0:e0]))
    for vf in a.variants:
        body = open(vf).read()
        if a.perm:
            for tag, t in expand_perm(body, a.max):
                cands.append((f"{os.path.basename(vf)} {tag}", t))
        else:
            cands.append((os.path.basename(vf), body))

    tmpdir = tempfile.mkdtemp(prefix="fnh_")
    tmp_src = os.path.join(os.path.dirname(src_path), f"_fnh_{os.getpid()}.cpp")
    best = None
    # make SIGTERM run the cleanup below (the temp source sits next to the real one)
    signal.signal(signal.SIGTERM, lambda *_: sys.exit(1))
    try:
        for tag, body in cands:
            open(tmp_src, "w").write(text[:s0] + body + text[e0:])
            obj = os.path.join(tmpdir, "out.o")
            if os.path.exists(obj):
                os.remove(obj)
            r = subprocess.run(cc + ["-c", os.path.relpath(tmp_src, ROOT), "-o", obj],
                               cwd=ROOT, capture_output=True, text=True)
            if r.returncode != 0 or not os.path.exists(obj):
                err = [l for l in (r.stdout + r.stderr).split("\n") if "rror" in l or "#    " in l]
                print(f"FAIL  {tag[:150]}  {' '.join(err[:3])[:200]}")
                continue
            ours = disasm(obj, a.fn)
            d = score(ours, target)
            print(f"{d:4d}  n={len(ours)}/{len(target)}  {tag[:150]}", flush=True)
            if best is None or d < best[0]:
                best = (d, tag, ours)
    finally:
        if os.path.exists(tmp_src):
            os.remove(tmp_src)
    if best:
        print(f"BEST {best[0]} diffs: {best[1][:200]}")
        if a.show:
            diff = list(difflib.unified_diff(target, best[2], "target", "ours", n=0, lineterm=""))
            print("\n".join(diff[:60]))


if __name__ == "__main__":
    main()
