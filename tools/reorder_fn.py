#!/usr/bin/env python3
"""Move function definitions inside a C/C++ source file (for emission-order fixes).

MWCC with -inline deferred orders .text by source order (reversed or not, depending on the unit), so a
unit that scores 100% in objdiff can still differ in the DOL. After moving, run
`python3 tools/order_check.py <unit>` and verify.py.

  python3 tools/reorder_fn.py FILE --list
  python3 tools/reorder_fn.py FILE MOVE... [--dry-run]
      MOVE is  NAME before|after OTHER   (repeatable, applied in order)

Function extents are found by brace matching (strings, chars and comments skipped), so multi-line
signatures, labels at column 0 and nested braces are handled. Leading `//` comment lines move with the
function. Prototypes (declarations ending in `;`) are never moved. The tool prints any #pragma lines
between the old and new position so you can check that no push/pop, dont_inline or auto_inline region
changes meaning, and refuses ambiguous names.
"""
import re
import sys


def scan(text):
    """Return list of (name, start_line, end_line) for top-level-ish function definitions."""
    lines = text.split("\n")
    # mask comments/strings so braces inside them are ignored; keep newlines
    out = []
    i, n = 0, len(text)
    st = "code"
    while i < n:
        c = text[i]
        two = text[i:i + 2]
        if st == "code":
            if two == "//":
                st = "line"; out.append("  "); i += 2; continue
            if two == "/*":
                st = "block"; out.append("  "); i += 2; continue
            if c == '"':
                st = "str"; out.append(" "); i += 1; continue
            if c == "'":
                st = "chr"; out.append(" "); i += 1; continue
            out.append(c)
        elif st == "line":
            out.append("\n" if c == "\n" else " ")
            if c == "\n":
                st = "code"
        elif st == "block":
            if two == "*/":
                st = "code"; out.append("  "); i += 2; continue
            out.append("\n" if c == "\n" else " ")
        elif st in ("str", "chr"):
            q = '"' if st == "str" else "'"
            if c == "\\":
                out.append("  "); i += 2; continue
            if c == q:
                st = "code"
            out.append("\n" if c == "\n" else " ")
        i += 1
    masked = "".join(out)
    mlines = masked.split("\n")
    funcs = []
    hdr = re.compile(r"^[A-Za-z_][^;{}=]*?\b([A-Za-z_~][\w:~]*)\s*\(")
    li = 0
    while li < len(mlines):
        m = hdr.match(mlines[li])
        if m and not mlines[li].lstrip().startswith("#"):
            # find '{' before any ';' within the next 6 lines
            blk = None
            for k in range(li, min(li + 6, len(mlines))):
                s = mlines[k]
                j_b = s.find("{")
                j_s = s.find(";")
                if j_b >= 0 and (j_s < 0 or j_b < j_s):
                    blk = (k, j_b); break
                if j_s >= 0:
                    break
            if blk:
                depth, k, j = 0, blk[0], blk[1]
                end = None
                while k < len(mlines) and end is None:
                    s = mlines[k]
                    while j < len(s):
                        if s[j] == "{":
                            depth += 1
                        elif s[j] == "}":
                            depth -= 1
                            if depth == 0:
                                end = k; break
                        j += 1
                    j = 0
                    k += 1
                if end is not None:
                    start = li
                    while start > 0 and lines[start - 1].startswith("//"):
                        start -= 1
                    funcs.append((m.group(1), start, end))
                    li = end + 1
                    continue
        li += 1
    return lines, funcs


def find(funcs, name):
    c = [f for f in funcs if f[0] == name or f[0].endswith("::" + name)]
    if len(c) != 1:
        sys.exit(f"error: {name!r} matches {len(c)} definitions: {[(f[0], f[1] + 1) for f in c]}")
    return c[0]


def main():
    args = [a for a in sys.argv[1:] if a != "--dry-run"]
    dry = "--dry-run" in sys.argv
    if not args:
        sys.exit(__doc__)
    path = args[0]
    text = open(path).read()
    lines, funcs = scan(text)
    if args[1:] == ["--list"]:
        for name, s, e in funcs:
            print(f"{s + 1:6d}-{e + 1:<6d} {name}")
        return
    moves = args[1:]
    if len(moves) % 3:
        sys.exit("moves are triples: NAME before|after OTHER")
    for a in range(0, len(moves), 3):
        name, where, other = moves[a:a + 3]
        if where not in ("before", "after"):
            sys.exit("where must be before|after")
        lines, funcs = scan("\n".join(lines))
        fn = find(funcs, name)
        ot = find(funcs, other)
        if fn is ot:
            sys.exit("cannot move a function relative to itself")
        blk = lines[fn[1]:fn[2] + 1]
        dest = ot[1] if where == "before" else ot[2] + 1
        lo, hi = sorted((fn[1], dest))
        prag = [(i + 1, lines[i]) for i in range(lo, hi) if lines[i].startswith("#pragma") and not (fn[1] <= i <= fn[2])]
        if prag:
            print(f"warning: moving {name} across pragma lines (check scope!):")
            for ln, t in prag:
                print(f"  {ln}: {t}")
        rest = lines[:fn[1]] + lines[fn[2] + 1:]
        if fn[2] + 1 < len(lines) and lines[fn[2] + 1] == "" and rest[fn[1]:fn[1] + 1] == [""]:
            del rest[fn[1]]
        # recompute destination in `rest`
        if dest > fn[2]:
            dest -= (fn[2] - fn[1] + 1) + (1 if len(rest) < len(lines) - (fn[2] - fn[1] + 1) else 0)
        # simpler and exact: re-scan rest and place relative to `other`
        rl, rf = scan("\n".join(rest))
        o2 = find(rf, other)
        d = o2[1] if where == "before" else o2[2] + 1
        ins = blk + [""] if where == "before" else [""] + blk
        lines = rl[:d] + ins + rl[d:]
        print(f"moved {name} {where} {other}")
    if not dry:
        open(path, "w").write("\n".join(lines))
    else:
        print("(dry run, file not written)")


if __name__ == "__main__":
    main()
