#!/usr/bin/env python3
"""Set up and run decomp-permuter on one function of one unit.

    python3 tools/permute.py setup  <unit> <function>   # build/permuter/<function>/
    python3 tools/permute.py run    <function> [--minutes N] [-j N]
    python3 tools/permute.py best   <function>          # show best candidate diff

<unit> is the objdiff unit path without the version prefix, e.g.
revolution/SI/SIBios. The permuter checkout defaults to ../decomp-permuter
(override with PERMUTER_DIR). See docs/permuter.md.

decomp-permuter parses C only. C units usually work as generated; C++ units
need base.c hand-edited (PERM_IGNORE/PERM_PRETEND) before `run`.
"""
from __future__ import annotations

import argparse
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VERSION = "RZTE01_01"
BUILD = ROOT / "build" / VERSION
OUT = ROOT / "build" / "permuter"
PERMUTER = Path(os.environ.get("PERMUTER_DIR", ROOT.parent / "decomp-permuter"))
BINUTILS = ROOT / "build" / "binutils"


def workdir(function: str) -> Path:
    """build/permuter/<function>; long mangled names are shortened (file name limit)."""
    if len(function) <= 80:
        return OUT / function
    import hashlib
    return OUT / f"{function[:60]}_{hashlib.sha1(function.encode()).hexdigest()[:8]}"


def ninja_build_vars(unit: str) -> dict[str, str]:
    """Rule, source and variables of the ninja stanza that compiles <unit>."""
    target = f"build/{VERSION}/src/{unit}.o"
    text = (ROOT / "build.ninja").read_text().replace("$\n", "")
    m = re.search(rf"^build {re.escape(target)}:\s+(\S+)\s+(\S+).*\n((?:  .*\n)*)", text, re.M)
    if not m:
        sys.exit(f"no ninja build stanza for {target}")
    v = {"rule": m.group(1), "source": m.group(2)}
    for line in m.group(3).splitlines():
        k, _, val = line.strip().partition(" = ")
        v[k] = re.sub(r"\s+", " ", val)
    return v


def extract_asm(unit: str, fn: str) -> str:
    """The .fn block for <fn>, plus any local data labels it needs are omitted:
    the scorer compares instructions and relocation targets only."""
    src = (BUILD / "asm" / f"{unit}.s").read_text()
    m = re.search(rf"^\.fn {re.escape(fn)},.*?^\.endfn {re.escape(fn)}\n", src, re.M | re.S)
    if not m:
        sys.exit(f"{fn} not found in asm/{unit}.s")
    return f'.include "macros.inc"\n.text\n.balign 4\n{m.group(0)}'


SENTINEL = "void __permuter_unit_begin(void);"

FN_HEAD = re.compile(r"^[^\n;#{}]*?\b(\w+)\s*\([^;{}]*\)\s*(?:const\s*)?\{", re.M)


def prototype(head: str, name: str) -> str:
    """Declaration for a function head; drops a constructor initializer list."""
    m = re.search(rf"\b{re.escape(name)}\s*\(", head)
    depth, i = 0, m.end() - 1
    while True:
        depth += {"(": 1, ")": -1}.get(head[i], 0)
        if depth == 0:
            break
        i += 1
    tail = " const" if re.match(r"\s*const\b", head[i + 1:]) else ""
    return head[:i + 1] + tail + ";"


def strip_other_fns(source: str, keep: str, keep_static: bool = False, keep_all: bool = False) -> str:
    """Replace bodies of other functions with prototypes. Inline (non-asm)
    functions keep their bodies, since they can change the target's codegen;
    so do static ones with keep_static (`-ipa file` inlines them even when
    they are defined after the target)."""
    out, pos = [], 0
    while (m := FN_HEAD.search(source, pos)):
        depth, i = 0, m.end() - 1
        while True:
            depth += {"{": 1, "}": -1}.get(source[i], 0)
            if depth == 0:
                break
            i += 1
        head = source[m.start():m.end() - 1]
        body = source[m.end() - 1:i + 1]
        out.append(source[pos:m.start()])
        if m.group(1) in ("if", "for", "while", "switch"):
            out.append(source[m.start():i + 1])
        elif m.group(1) == keep or (("inline" in head or keep_all or (keep_static and re.match(r"\s*static\b", head)))
                                    and not re.search(r"\b(?:asm|ASM)\s*[({]", body) and not re.search(r"\basm\b", head)):
            out.append(head + body)
        else:
            out.append(prototype(head, m.group(1)))
        pos = i + 1
    out.append(source[pos:])
    return "".join(out)


def clean_for_pycparser(src: str) -> str:
    src = re.sub(r"__declspec\s*\([^()]*(?:\([^()]*\)[^()]*)*\)", "", src)
    src = re.sub(r"^#line.*$", "", src, flags=re.M)
    # The precompiled prefix header is still applied by compile.sh's -prefix.
    src = re.sub(r'^#include "\w+\.mch".*$', "", src, flags=re.M)
    src = re.sub(r"\n{3,}", "\n\n", src)
    return src


def setup_cxx(a, d: Path, own: str, raw: str) -> None:
    """C++ unit: C-parseable stand-in in base.c, C++ prefix and original head
    kept aside (see tools/permute_cxx.py)."""
    import json
    sys.path.insert(0, str(ROOT / "tools"))
    import permute_cxx as cx

    quals = [a.name] if a.name else cx.demangle_mw(a.function)
    if not quals:
        sys.exit(f"cannot demangle {a.function}; pass --name Class::method (or a free function name)")
    for qual in quals:
        try:
            hs, bo, bc = cx.find_function(own, qual, a.index)
            break
        except LookupError as e:
            err = e
    else:
        sys.exit(str(err))
    fn_head = own[hs:bo].strip()
    c_head, c_body, scope_map, _cls = cx.cify(a.function, fn_head, own[bo:bc + 1], a.static)
    # Compile context: the real source text around the target (includes, earlier
    # functions that -inline auto may inline into it, later code). Pragmas that
    # `mwcc -E` drops stay intact this way.
    try:
        rs, _rbo, rbc = cx.find_function(raw, qual, a.index)
    except LookupError:
        sys.exit("target found in preprocessed code but not in the raw source")
    pragmas = re.findall(r"^[ \t]*#pragma[^\n]*", raw[_rbo:rbc], re.M)
    (d / "prefix.cpp").write_text(raw[:rs])
    (d / "suffix.cpp").write_text(raw[rbc + 1:])

    sys.path.insert(0, str(PERMUTER))
    from src import ast_util  # the permuter's vendored C parser
    base, stubs = cx.build_base(c_head, c_body, ast_util.parse_c)
    if a.type_context:
        context = Path(a.type_context).read_text()
        base = cx.add_type_context(base, context, ast_util.parse_c)
        (d / "type-context.h").write_text(context)
    (d / "base.c").write_text(base)
    (d / "cxx.json").write_text(json.dumps({
        "sym": a.function, "head": fn_head, "pragmas": [x.strip() for x in pragmas], "scope_map": scope_map, "stubs": stubs, "dir": str(d),
    }, indent=1))


def _setup(a, quiet: bool = False) -> int | None:
    v = ninja_build_vars(a.unit)
    if not v["rule"].startswith("mwcc"):
        sys.exit(f"rule {v['rule']} is not an mwcc rule")
    d = workdir(a.function)
    if d.exists():
        shutil.rmtree(d)
    d.mkdir(parents=True)

    mwcc = ROOT / "build" / "compilers" / v["mw_version"] / "mwcceppc.exe"
    wibo = ROOT / "build" / "tools" / "wibo"
    cflags = v["cflags"]
    # Preprocess a copy of the source with the exact project flags. A sentinel
    # after the last #include separates header code (kept whole, so inline
    # functions and class bodies survive) from the unit's own code (stripped).
    src = ROOT / v["source"]
    lines = src.read_text(errors="replace").splitlines()
    last_inc = max((i for i, l in enumerate(lines) if l.lstrip().startswith("#include")), default=-1)
    lines.insert(last_inc + 1, SENTINEL)
    copy = d / f"_source{src.suffix}"
    copy.write_text("\n".join(lines) + "\n")
    pre = subprocess.run(
        f"{shlex.quote(str(wibo))} {shlex.quote(str(mwcc))} {cflags} -i {shlex.quote(str(src.parent))} "
        f"-E {shlex.quote(str(copy))}",
        shell=True, cwd=ROOT, capture_output=True, text=True, errors="replace",
    )
    copy.unlink()
    if pre.returncode:
        sys.exit("preprocess failed:\n" + pre.stderr[-2000:])
    head, _, own = pre.stdout.partition(SENTINEL)
    cxx = src.suffix in (".cpp", ".cc", ".cxx") or "-lang=c++" in cflags
    if a.type_context and not cxx:
        sys.exit("--type-context is supported only for C++ stand-ins")
    if cxx:
        setup_cxx(a, d, own, src.read_text(errors='replace'))
        # The temp file keeps the real source's basename: anonymous-namespace
        # symbols (@unnamed@<file>@) embed it.
        compile_body = (
            'T=$(mktemp -d)\n'
            f'F="$T/{src.name}"\n'
            f'{shlex.quote(sys.executable)} {shlex.quote(str(ROOT / "tools" / "permute_cxx.py"))} '
            f'restore {shlex.quote(str(d))} "$1" "$F" || {{ rm -rf "$T"; exit 1; }}\n'
            f'{shlex.quote(str(wibo))} {shlex.quote(str(mwcc))} {cflags} -i {shlex.quote(str(src.parent))} '
            '-c "$F" -o "$3" >"${PERM_LOG:-/dev/null}"\n'
            'rc=$?; rm -rf "$T"; exit $rc\n'
        )
    else:
        ipa = "-ipa file" in cflags
        # Header code keeps its bodies except asm ones (pycparser cannot read them).
        base = clean_for_pycparser(strip_other_fns(head, a.function, keep_static=True)
                                   + strip_other_fns(own, a.function, keep_static=ipa, keep_all=a.keep_bodies))
        # The permuter reads any "PERM_" text as one of its macros (NWC24 has NAND_PERM_RUSR).
        base = base.replace("PERM_", "PRMX_")
        (d / "base.c").write_text(base)
        compile_body = f'set -e\n{shlex.quote(str(wibo))} {shlex.quote(str(mwcc))} {cflags} -c "$1" -o "$3" >"${{PERM_LOG:-/dev/null}}"\n'

    # compile.sh: permuter calls `compile.sh in.c -o out.o`.
    (d / "compile.sh").write_text(
        "#!/bin/bash\n"
        f"cd {shlex.quote(str(ROOT))}\n"
        + compile_body
    )
    (d / "compile.sh").chmod(0o755)
    settings = f'func_name = "{a.function}"\ncompiler_type = "mwcc"\n'
    if cxx or "-ipa file" in cflags or a.keep_bodies:  # candidates also contain other functions (inlining); score only the target
        dump = f"{BINUTILS / 'powerpc-eabi-objdump'} -dr -EB -mpowerpc -M broadway --disassemble={a.function}"
        settings += f'objdump_command = "{dump}"\n'
    (d / "settings.toml").write_text(settings)
    if a.keep_bodies:
        (d / "keep_bodies").write_text("run with PERMUTER_KEEP_BODIES=1\n")
    else:
        (d / "keep_bodies").unlink(missing_ok=True)

    (d / "target.s").write_text(extract_asm(a.unit, a.function))
    subprocess.run(
        [str(BINUTILS / "powerpc-eabi-as"), "-mgekko", "-I", str(BUILD / "include"),
         "-o", str(d / "target.o"), str(d / "target.s")],
        check=True,
    )

    # Sanity check: base.c must compile; report the starting score.
    compile_log = d / "baseline-compile.log"
    r = subprocess.run(["bash", str(d / "compile.sh"), str(d / "base.c"), "-o", str(d / "base.o")],
                       capture_output=True, text=True, env={**os.environ, "PERM_LOG": str(compile_log)})
    if r.returncode:
        if not quiet:
            details = compile_log.read_text(errors="replace") if compile_log.exists() else ""
            print(f"{d}/base.c does not compile as generated; edit it, then `run`.\n{r.stdout[-1500:]}{r.stderr[-500:]}{details[-1500:]}")
        return None
    mm = mismatch(d, a.function)
    if not quiet:
        print(f"set up {d}\nstarting mismatch: {mm} instruction lines" + (" (exact)" if mm == 0 else ""))
    return mm


def mismatch(d: Path, fn: str) -> int:
    """Instruction lines that differ between target.o and base.o for <fn>."""
    import difflib

    def lines(o: str) -> list[str]:
        out = subprocess.run(
            [str(BINUTILS / "powerpc-eabi-objdump"), "-dr", "-EB", "-mpowerpc", "-M", "broadway", f"--disassemble={fn}", str(d / o)],
            capture_output=True, text=True).stdout
        norm = []
        for l in out.splitlines():
            if "\t" not in l:
                continue
            l = re.sub(r"^\s*[0-9a-f]+:\s*(?:[0-9a-f]{2} ){4}?\s*", "", l)
            l = re.sub(r"\b[0-9a-f]+ <[^>]*>", "<>", l)  # branch targets
            l = re.sub(r"@\d+", "@N", l)  # anonymous constants are numbered per translation unit
            norm.append(re.sub(r"^[0-9a-f]+: (R_PPC)", r"\1", l.strip()))
        return norm

    a, b = lines("target.o"), lines("base.o")
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")


def cx_Ambiguous():
    sys.path.insert(0, str(ROOT / "tools"))
    import permute_cxx
    return permute_cxx.Ambiguous


def cmd_setup(a) -> None:
    if a.index >= 0:
        _setup(a)
        return
    try:
        _setup(a)
    except cx_Ambiguous() as e:  # overloaded name: take the definition whose code matches best
        best = None
        for i in range(e.n):
            a.index = i
            mm = _setup(a, quiet=True)
            if mm is not None and (best is None or mm < best[0]):
                best = (mm, i)
        if best is None:
            sys.exit(f"{e.n} definitions of the name and none set up; pass --name/--index")
        a.index = best[1]
        print(f"{e.n} overloads; using --index {best[1]}")
        _setup(a)


def env(d: Path | None = None) -> dict[str, str]:
    e = dict(os.environ)
    e["PATH"] = f"{BINUTILS}:{e['PATH']}"
    if d is not None and (d / "keep_bodies").exists():
        e["PERMUTER_KEEP_BODIES"] = "1"  # patched extract_fn keeps helper bodies and `static`
    return e


def cmd_run(a) -> None:
    d = workdir(a.function)
    if not (d / "base.c").exists():
        sys.exit(f"run `setup` first for {a.function}")
    py = PERMUTER / ".venv" / "bin" / "python"
    cmd = [str(py if py.exists() else sys.executable), str(PERMUTER / "permuter.py"), str(d), "-j", str(a.jobs), "--best-only"]
    if a.stop_on_zero:
        cmd.append("--stop-on-zero")
    # Own process group + log file: permuter workers outlive a plain kill and
    # would keep a caller's pipe open. Progress goes to run.log, not context.
    with open(d / "run.log", "w") as log:
        proc = subprocess.Popen(cmd, env=env(d), stdout=log, stderr=subprocess.STDOUT,
                                start_new_session=True)
        try:
            proc.wait(timeout=a.minutes * 60)
        except subprocess.TimeoutExpired:
            os.killpg(proc.pid, signal.SIGINT)
            try:
                proc.wait(timeout=10)
            except subprocess.TimeoutExpired:
                os.killpg(proc.pid, signal.SIGKILL)
            print(f"stopped after {a.minutes} min")
    scores = re.findall(r"(?:base score|new best score)\D*(\d+)", (d / "run.log").read_text())
    if scores:
        print(f"score: base {scores[0]} -> best {min(map(int, scores))} (0 = match)")
    else:
        print(f"no score reported; see {d}/run.log")
    cmd_best(a)


def cmd_best(a) -> None:
    d = workdir(a.function)
    log = d / "run.log"
    base = re.search(r"base score\D*(\d+)", log.read_text()) if log.exists() else None
    outs = sorted((int(p.name.split("-")[1]), p) for p in d.glob("output-*"))
    better = [(s, p) for s, p in outs if base is None or s < int(base.group(1))]
    if not better:
        print("no candidate beat the base score")
        return
    s, p = better[0]
    print(f"best: score {s} (0 = match): diff -u {d}/base.c {p}/source.c")


def main() -> None:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("setup"); s.add_argument("unit"); s.add_argument("function")
    s.add_argument("--name", help="C++ units: source name, e.g. Class::method (default: demangled from <function>)")
    s.add_argument("--index", type=int, default=-1, help="C++ units: which definition when the name is overloaded")
    s.add_argument("--static", action="store_true", help="C++ units: static member / free function (no `this`)")
    s.add_argument("--keep-bodies", action="store_true", help="C units: keep every non-asm function body (static helpers the unit inlines); scores only the target")
    s.add_argument("--type-context", help="C++ stand-in: C typedefs supplying search-only field types")
    s.set_defaults(f=cmd_setup)
    s = sub.add_parser("run"); s.add_argument("function")
    s.add_argument("--minutes", type=float, default=10); s.add_argument("-j", "--jobs", type=int, default=os.cpu_count() or 4)
    s.add_argument("--stop-on-zero", action="store_true", default=True); s.set_defaults(f=cmd_run)
    s = sub.add_parser("best"); s.add_argument("function"); s.set_defaults(f=cmd_best)
    a = p.parse_args()
    a.f(a)


if __name__ == "__main__":
    main()
