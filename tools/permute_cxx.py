#!/usr/bin/env python3
"""C++ adapter for decomp-permuter (used by tools/permute.py).

The permuter only parses C. For a C++ target function this module builds a
C-parseable stand-in and restores the C++ around every candidate:

  setup:  base.c      = `typedef struct X X;` stubs + the target function with
                        its name replaced by the mangled symbol, `this` as an
                        explicit `Cls* this` parameter, `::` mangled, casts
                        like static_cast<T>(e) turned into C casts.
          prefix.cpp  = preprocessed headers + prototypes of the unit's other
                        functions (compiled unchanged with every candidate).
          cxx.json    = original head, scope-name map, stub names.
  compile: `restore` takes a candidate's C text, keeps only the target
           function's body, undoes the mangling, puts the original C++ head
           back and prepends prefix.cpp. compile.sh then runs mwcc on it.

Unsupported (reported by `setup` when the C parse fails): templates, lambdas,
new/delete expressions, references declared in the body (reference
*parameters* are fine, the original head is restored verbatim).
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

DROP_SPECIFIERS = ("inline", "static", "virtual", "extern", "explicit", "friend")
CAST_RE = re.compile(r"\b(static_cast|reinterpret_cast|const_cast|dynamic_cast)\s*<")


def balanced(text: str, start: int, open_c: str, close_c: str) -> int:
    """Index of the bracket closing the one at text[start]."""
    depth = 0
    for i in range(start, len(text)):
        c = text[i]
        if c == open_c:
            depth += 1
        elif c == close_c:
            depth -= 1
            if depth == 0:
                return i
    raise ValueError(f"unbalanced {open_c}")


def hoist_for_decls(body: str) -> str:
    """The permuter's randomizer asserts on C99 `for (T i = 0; ...)` (ca.DeclList).
    Rewrite to `{ T i; for (i = 0; ...) stmt }`; the block keeps the scope, so the
    restored C++ compiles to the same code. Not undone in restore()."""
    out, pos = [], 0
    for m in re.finditer(r"\bfor\s*\(", body):
        if m.start() < pos:
            continue  # inside a loop already rewritten
        op = m.end() - 1
        cl = balanced(body, op, "(", ")")
        head = body[op + 1:cl]
        semi = head.find(";")
        d = re.match(r"^\s*((?:const\s+)?[A-Za-z_][\w:]*(?:\s*\*+)?)\s+(\w+)\s*=\s*(.*)$", head[:semi] if semi >= 0 else "", re.S)
        if not d or d.group(1).split()[0] in ("return", "else", "case", "goto"):
            continue
        j = cl + 1
        while body[j].isspace():
            j += 1
        if body[j] == "{":
            end = balanced(body, j, "{", "}") + 1
        else:
            end = body.index(";", j) + 1
        out.append(body[pos:m.start()])
        out.append(f"{{ {d.group(1)} {d.group(2)}; for ({d.group(2)} = {d.group(3)}{head[semi:]}) {body[j:end]} }}")
        pos = end
    out.append(body[pos:])
    return "".join(out)


def demangle_mw(sym: str) -> list[str]:
    """Metrowerks mangling `name__<scope>F...` -> candidate source names
    (`Class::name`, longest scope suffix first). Empty if not understood."""
    m = re.match(r"^(?P<n>.+?)__(?P<rest>(?:Q\d)?\d.*)$", sym)
    if not m:
        return []
    rest, name = m.group("rest"), m.group("n")
    scope: list[str] = []
    q = re.match(r"Q(\d)", rest)
    count = int(q.group(1)) if q else 1
    pos = 2 if q else 0
    for _ in range(count):
        d = re.match(r"\d+", rest[pos:])
        if not d:
            break
        n = int(d.group())
        scope.append(rest[pos + len(d.group()):pos + len(d.group()) + n])
        pos += len(d.group()) + n
    if not scope:
        return []
    cls = scope[-1]
    if name == "__ct":
        name = cls
    elif name == "__dt":
        name = "~" + cls
    return ["::".join(scope[k:] + [name]) for k in range(len(scope))] + [name]


class Ambiguous(Exception):
    def __init__(self, n: int):
        self.n = n


def count_definitions(own: str, qual: str) -> int:
    try:
        return len(_definitions(own, qual))
    except LookupError:
        return 0


def find_function(own: str, qual: str, index: int) -> tuple[int, int, int]:
    """(head_start, body_open, body_close) of the index'th definition named <qual>."""
    hits = _definitions(own, qual)
    if len(hits) > 1 and index < 0:
        raise Ambiguous(len(hits))
    return hits[max(index, 0)]


def _mask_comments(text: str) -> str:
    """Blank out comments (same length, newlines kept) so names inside them are not hits."""
    return re.sub(r"//[^\n]*|/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S)


def _definitions(own: str, qual: str) -> list[tuple[int, int, int]]:
    own = _mask_comments(own)
    pat = re.compile(r"(?<![\w:])" + r"\s*::\s*".join(map(re.escape, qual.split("::"))) + r"\s*\(")
    hits = []
    for m in pat.finditer(own):
        paren = own.index("(", m.start())
        try:
            close = balanced(own, paren, "(", ")")
        except ValueError:
            continue
        j = close + 1
        # skip `const`, ctor initializer lists, up to the body brace (or `;` = not a definition)
        depth = 0
        while j < len(own):
            c = own[j]
            if c == "(":
                depth += 1
            elif c == ")":
                depth -= 1
            elif depth == 0 and c == ";":
                j = -1
                break
            elif depth == 0 and c == "{":
                break
            j += 1
        if j < 0 or j >= len(own):
            continue
        # head starts after the previous statement / block / access label
        hs = max(own.rfind(c, 0, m.start()) for c in ";{}") + 1
        d = own.rfind("\n#", 0, m.start())
        if d >= 0:  # after the end of the last preprocessor line
            hs = max(hs, own.find("\n", d + 1) + 1)
        hits.append((hs, j, balanced(own, j, "{", "}")))
    if not hits:
        raise LookupError(f"definition of {qual} not found in the unit's own code")
    return hits


def split_params(head: str) -> tuple[str, str, str, str]:
    """head = `<ret> [Cls::]name(<params>)[ const][: inits]` -> (pre, name, params, post)."""
    paren = head.index("(")
    close = balanced(head, paren, "(", ")")
    pre_name = head[:paren]
    m = re.search(r"((?:[\w~]+\s*::\s*)*[\w~]+)\s*$", pre_name)
    return pre_name[:m.start()], m.group(1), head[paren + 1:close], head[close + 1:]


def convert_casts(text: str) -> str:
    """static_cast<T>(e) -> ((T)(e))."""
    while (m := CAST_RE.search(text)):
        lt = m.end() - 1
        depth, i = 0, lt
        while True:
            depth += {"<": 1, ">": -1}.get(text[i], 0)
            if depth == 0:
                break
            i += 1
        ty = text[lt + 1:i]
        j = i + 1
        while text[j].isspace():
            j += 1
        close = balanced(text, j, "(", ")")
        text = text[:m.start()] + f"(({ty})({text[j + 1:close]}))" + text[close + 1:]
    return text


def cify(sym: str, head: str, body: str, is_static: bool) -> tuple[str, str, list[list[str]], str]:
    """Return (c_head, c_body, scope_map, class_name)."""
    pre, name, params, post = split_params(head)
    cls = name.rsplit("::", 1)[0] if "::" in name else ""
    pre = re.sub(r'\bextern\s*"C"', "", pre)  # linkage spec; head is restored verbatim
    for s in DROP_SPECIFIERS:
        pre = re.sub(rf"\b{s}\b", "", pre)
    pre = pre.strip() or "void"  # constructors / destructors have no return type
    params = re.sub(r"=[^,]*", "", params)  # default args
    params = "" if params.strip() == "void" else params.strip()
    if cls and not is_static:
        cls_c = cls.replace("::", "__")
        params = f"{cls_c}* this" + (", " + params if params else "")
    scope_map: list[list[str]] = []

    def mangle(m: re.Match) -> str:
        orig = m.group(0)
        c = re.sub(r"\s*::\s*", "__", orig).replace("~", "__dtor_")
        if [c, orig] not in scope_map:
            scope_map.append([c, orig])
        return c

    scope_re = r"(?<![\w])(?:::\s*)?[\w~]+(?:\s*::\s*[\w~]+)+"
    body = convert_casts(body)
    body = hoist_for_decls(body)

    def keep(c: str, orig: str) -> str:
        if [c, orig] not in scope_map:
            scope_map.append([c, orig])
        return c

    # allocation functions/expressions: C has no `new`/`operator`. Hide them behind
    # identifiers that restore() maps back. `new T[n]` -> `__NEWa_T[n]` (indexing parses),
    # `new T(args)` -> `__NEWc_T(args)`, `operator new[](n)` -> `__OPNEWARR(n)`.
    for kw, c in (("new[]", "__OPNEWARR"), ("new", "__OPNEW"), ("delete[]", "__OPDELARR"), ("delete", "__OPDEL")):
        pat = r"(?:::\s*)?operator\s+" + re.escape(kw).replace(r"\[\]", r"\s*\[\s*\]")
        body = re.sub(pat, lambda m, c=c, kw=kw: keep(c, "operator " + kw), body)
    body = re.sub(
        r"\bnew\s+((?:const\s+)?[A-Za-z_][\w:]*)(\s*\[)?",
        lambda m: keep(("__NEWa_" if m.group(2) else "__NEWc_") + m.group(1).replace("::", "__").replace("const ", "const_"),
                       "new " + m.group(1)) + (m.group(2) or ""),
        body)

    def template(m: re.Match) -> str:
        c = f"__TPL{len(scope_map)}"
        scope_map.append([c, m.group(1)])
        return c + "("

    # explicit template calls `ns::F<T*>(x)` -> `__TPLn(x)` (restored verbatim)
    body = re.sub(r"((?:[\w:]+::)?\w+\s*<[^<>;(){}]*(?:<[^<>;(){}]*>[^<>;(){}]*)*>)\s*\(", template, body)
    # `T x(args);` direct-initialisation looks like a call in C: write `T x = __CTOR_x(args);`
    not_types = "return|else|goto|delete|case|sizeof|typedef|do|throw|new"
    body = re.sub(
        rf"(?m)((?:^|[;{{}}])\s*(?!(?:{not_types})\b)(?:const\s+)?[\w:]+(?:\s*\*+)?)\s+(\w+)\s*\(([^;]*)\)\s*;",
        r"\1 \2 = __CTOR_\2(\3);", body)
    # `T& x = ...;` declarations: C has no references. Declare `T__REF x`
    # (restored to `T&` afterwards); uses of x stay `x.field`.
    body = re.sub(r"(?m)((?:^|[;{}])\s*(?:const\s+)?[\w:]+)\s*&\s*(\w+)\s*=", r"\1__REF \2 =", body)
    params = re.sub(r"([\w:]+)\s*&", r"\1__REF", params)
    # explicit destructor calls: x->~T()
    for m in re.finditer(r"(->|\.)\s*~(\w+)", body):
        if [f"__dtor_{m.group(2)}", f"~{m.group(2)}"] not in scope_map:
            scope_map.append([f"__dtor_{m.group(2)}", f"~{m.group(2)}"])
    body = re.sub(r"(->|\.)\s*~(\w+)", r"\1__dtor_\2", body)
    body = re.sub(scope_re, mangle, body)
    pre = re.sub(scope_re, mangle, pre)
    params = re.sub(scope_re, mangle, params)
    return f"{pre} {sym}({params})", body, scope_map, cls


STUB_PRELUDE = "typedef int bool;\nenum { false, true };\n"


C_KEYWORDS = {
    "if", "else", "for", "while", "do", "return", "switch", "case", "default", "break", "continue",
    "goto", "sizeof", "struct", "union", "enum", "typedef", "const", "volatile", "static", "extern",
    "void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "register",
}


def error_pos(msg: str, nstubs: int) -> tuple[int, int] | None:
    """(line, column) of a parse error, line counted without the stub lines."""
    m = re.search(r"line (\d+), column (\d+)", msg)
    return (int(m.group(1)) - nstubs, int(m.group(2))) if m else None


def render(c_head: str, c_body: str, stubs: list[str]) -> str:
    if stubs:  # `T(x)` functional casts / constructor calls: T is a typedef here, so hide the call
        c_body = re.sub(r"\b(%s)\s*\((?!\s*\*)" % "|".join(map(re.escape, stubs)), r"__FC_\1(", c_body)
    return STUB_PRELUDE + "".join(f"typedef struct {s} {s};\n" for s in stubs) + f"\n{c_head}\n{c_body}\n"


def build_base(c_head: str, c_body: str, parse) -> tuple[str, list[str]]:
    """Add `typedef struct X X;` stubs until the C parser accepts the function.
    Unknown type names make the parser fail *after* the name (`T * x = ...`
    parses as an expression), so try each identifier on the failing line and
    keep the first stub that moves the error later."""
    stubs: list[str] = []

    def attempt(st: list[str]):
        text = render(c_head, c_body, st)
        try:
            parse(text)
            return text, None
        except Exception as e:  # pycparser ParseError
            return text, (error_pos(str(e), len(st)), str(e))

    text, err = attempt(stubs)
    for _ in range(200):
        if err is None:
            return text, stubs
        pos, msg = err
        if pos is None:
            raise SystemExit(f"C parse of the stand-in failed (unsupported C++?): {msg}")
        lines = text.split("\n")
        # the failing token's line first, then the lines just before it
        near = "\n".join(reversed(lines[max(0, pos[0] + len(stubs) - 4):pos[0] + len(stubs)]))
        idents = [x for x in dict.fromkeys(re.findall(r"[A-Za-z_]\w*", near)) if x not in C_KEYWORDS and x not in stubs]
        for ident in idents:
            t2, e2 = attempt(stubs + [ident])
            if e2 is None or (e2[0] is not None and e2[0] > pos):
                stubs.append(ident)
                text, err = t2, e2
                break
        else:
            # two unknown types can be needed at once (`T (*f)(U*)`): try pairs
            for i, a in enumerate(idents):
                for b in idents[i + 1:]:
                    t2, e2 = attempt(stubs + [a, b])
                    if e2 is None or (e2[0] is not None and e2[0] > pos):
                        stubs += [a, b]
                        text, err = t2, e2
                        break
                else:
                    continue
                break
            else:
                raise SystemExit(f"C parse of the stand-in failed (unsupported C++?): {msg}")
    raise SystemExit("too many type stubs needed")


def restore(c_text: str, cfg: dict) -> str:
    """Candidate C text -> full C++ translation unit."""
    sym = cfg["sym"]
    m = re.search(rf"(?<![\w]){re.escape(sym)}\s*\(", c_text)
    if not m:
        raise SystemExit("target function missing from candidate")
    open_b = c_text.index("{", m.end())
    body = c_text[open_b:balanced(c_text, open_b, "{", "}") + 1]
    body = re.sub(r"__FC_(\w+)\(", r"\1(", body)  # before scope_map: __FC_ glues onto mangled names
    for c, orig in sorted(cfg["scope_map"], key=lambda p: -len(p[0])):
        body = re.sub(rf"(?<!\w){re.escape(c)}(?!\w)", lambda _m, o=orig: o, body)
    body = re.sub(r"(\w)__REF\b", r"\1&", body)
    body = re.sub(r"__FC_(\w+)\(", r"\1(", body)
    body = re.sub(r"\b(\w+) = __CTOR_\1\(", r"\1(", body)
    if cfg.get("pragmas"):  # `mwcc -E` drops in-body pragmas (e.g. #pragma unused)
        body = "{\n" + "\n".join(cfg["pragmas"]) + "\n" + body[1:]
    prefix = Path(cfg["dir"], "prefix.cpp").read_text()
    suffix = Path(cfg["dir"], "suffix.cpp").read_text()
    return f"{prefix}\n{cfg['head']}\n{body}\n{suffix}\n"


def add_type_context(base: str, context: str, parse) -> str:
    """Replace opaque typedef stubs with explicit search-only C types.

    restore() uses only the function body, so these declarations never replace
    the compiler's real C++ headers. Reject executable declarations here.
    """
    context = _mask_comments(context)
    tree = parse(context)
    for node in tree.ext:
        if type(node).__name__ != "Typedef":
            raise ValueError("type context must contain only typedef declarations")
        base = re.sub(
            rf"(?m)^typedef struct {re.escape(node.name)} {re.escape(node.name)};\s*\n",
            "", base,
        )
    result = context.rstrip() + "\n" + base
    parse(result)
    return result


def main() -> None:
    if len(sys.argv) >= 4 and sys.argv[1] == "restore":
        cfg = json.loads(Path(sys.argv[2], "cxx.json").read_text())
        Path(sys.argv[4]).write_text(restore(Path(sys.argv[3]).read_text(), cfg))
    else:
        sys.exit("usage: permute_cxx.py restore <permuter-dir> <candidate.c> <out.cpp>")


if __name__ == "__main__":
    main()
