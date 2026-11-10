#!/usr/bin/env python3
"""Move old checkpoint sections of docs/tasks/*.md under a trailing '## Archive'.

A '## ' section is archived only if its heading looks historical: it contains
a date, or the words checkpoint, continuation, historical, previous or
session. Undated working sections (Verified results, Experiments, Remaining,
Next, ...) stay in place. Moved text is unchanged apart from heading depth
(+1); a note's existing Archive content keeps its place first. Run from the
repo root.

  python3 tools/archive_notes.py              # dry run: table of savings
  python3 tools/archive_notes.py --apply      # rewrite files
  python3 tools/archive_notes.py --min 3000 --apply
  python3 tools/archive_notes.py --split --apply   # move each note's '## Archive' tail out to
                                                   # docs/archive/tasks/<note>.md (notes keep a pointer)

Skipped: queue-history.md. Run only when no agent is mid-task on a note (the
queue file that used to mark active notes was removed 2026-10-16). Every rewrite is
checked to preserve all lines (heading depth aside) before it is written.
"""
import argparse
import re
from pathlib import Path

TASKS = Path("docs/tasks")
ARCHIVE = Path("docs/archive/tasks")
OLD = re.compile(r"checkpoint|continuation|historical|previous|session|\d{4}-\d{2}-\d{2}|\b2026\d{4}", re.I)
SKIP = {"queue-history"}


def split_sections(text: str):
    """-> (preamble_lines, [(heading_line, [body_lines])]); respects code fences."""
    pre, secs, fence = [], [], False
    for line in text.splitlines():
        if line.lstrip().startswith("```"):
            fence = not fence
        if not fence and re.match(r"## \S", line):
            secs.append((line, []))
        elif secs:
            secs[-1][1].append(line)
        else:
            pre.append(line)
    return pre, secs


def demote(lines, fence=False):
    out = []
    for line in lines:
        if line.lstrip().startswith("```"):
            fence = not fence
        out.append("#" + line if not fence and re.match(r"#{1,5} \S", line) else line)
    return out


def norm(lines):
    return sorted(l.lstrip("#").strip() for l in lines if l.strip())


def rebuild(text: str):
    pre, secs = split_sections(text)
    arch_existing = [s for s in secs if s[0][3:].strip().lower() == "archive"]
    moved = [s for s in secs if s not in arch_existing and OLD.search(s[0])]
    if not moved:
        return None
    live = [s for s in secs if s not in arch_existing and s not in moved]
    out = list(pre)
    for h, b in live:
        out += [h] + b
    out += ["## Archive"]
    for h, b in arch_existing:
        out += b
    for h, b in moved:
        out += [""] + demote([h] + b)
    new = "\n".join(out).rstrip("\n") + "\n"
    old_lines = [l for l in text.splitlines()]
    if norm(old_lines) != norm(new.splitlines() if arch_existing else
                               [l for l in new.splitlines() if l != "## Archive"]):
        raise SystemExit("line-preservation check failed; refusing to write")
    return new, sum(len("\n".join(b)) + len(h) for h, b in moved)


def split_archive(text: str, stem: str):
    """-> (live_text, archive_text) or None; splits at the first '## Archive' outside a code fence."""
    lines, fence = text.splitlines(), False
    for i, line in enumerate(lines):
        if line.lstrip().startswith("```"):
            fence = not fence
        if not fence and line.strip().lower() == "## archive":
            live = "\n".join(lines[:i]).rstrip("\n")
            tail = "\n".join(lines[i + 1:]).strip("\n")
            if not tail:
                return None
            ptr = f"\n\n## Archive\n\nHistory moved to `docs/archive/tasks/{stem}.md` (read only if needed).\n"
            return live + ptr, f"# {stem}: archived history\n\n{tail}\n"
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--min", type=int, default=2000, help="min bytes to archive per note")
    ap.add_argument("--split", action="store_true", help="move Archive tails to docs/archive/tasks/")
    a = ap.parse_args()

    if a.split:
        total = n = 0
        for p in sorted(TASKS.glob("*.md")):
            res = split_archive(p.read_text(), p.stem)
            if res is None or len(res[1]) < a.min:
                continue
            n, total = n + 1, total + len(res[1])
            print(f"{p.stem:42} {len(res[1]):>7} B")
            if a.apply:
                ARCHIVE.mkdir(parents=True, exist_ok=True)
                (ARCHIVE / p.name).write_text(res[1])
                p.write_text(res[0])
        print(f"total {'moved' if a.apply else 'movable'}: {total} B across {n} notes")
        return

    active = ""  # no queue file; run only when no agent is mid-task on a note
    rows, total = [], 0
    for p in sorted(TASKS.glob("*.md")):
        if p.stem in SKIP:
            continue
        if re.search(rf"(?<![\w]){re.escape(p.stem)}(?![\w])", active):
            rows.append((p.stem, "skipped (active claim)", 0))
            continue
        res = rebuild(p.read_text())
        if res is None or res[1] < a.min:
            continue
        new, moved = res
        rows.append((p.stem, "archived" if a.apply else "would archive", moved))
        total += moved
        if a.apply:
            p.write_text(new)
    for stem, what, n in rows:
        print(f"{stem:42} {what:24} {n:>7} B")
    print(f"total {'moved' if a.apply else 'movable'}: {total} B across {sum(1 for r in rows if r[2])} notes")


if __name__ == "__main__":
    main()
