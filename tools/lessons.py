#!/usr/bin/env python3
"""Shared log of compiler/matching lessons (what worked, what failed).

One small file per lesson in docs/lessons/, so worktrees never conflict on a
shared file. Search before an experiment; add after a verified win or a
dead end. Run from the repo root.

  python3 tools/lessons.py search regalloc inline      # all terms must match; best 8, compact
  python3 tools/lessons.py search inline --limit 20    # more hits
  python3 tools/lessons.py search inline --status fails  # only dead ends (works|fails|open)
  python3 tools/lessons.py search inline --full        # whole entries (use sparingly)
  python3 tools/lessons.py search                      # no terms: count + most common tags
  python3 tools/lessons.py add --title "..." --status works|fails|open \\
      --tags a,b --symptom "..." --cause "..." --fix "..." \\
      [--scope unit/fn] [--source "commit or note"]
"""
import argparse
import re
import sys
from datetime import date
from pathlib import Path



DIR = Path("docs/lessons")  # tracked: each worktree has the log; lessons merge with the branch
FIELDS = ("symptom", "cause", "fix")


def load():
    for p in sorted(DIR.glob("*.md")):
        text = p.read_text()
        meta = dict(re.findall(r"^- (\w+): (.*)$", text, re.M))
        body = dict(re.findall(r"^(symptom|cause|fix): (.*)$", text, re.M))
        title = (re.match(r"# (.*)", text) or [None, p.stem])[1]
        yield p, title, meta, body, text


def rank(terms, p, title, meta, text):
    """Title/tag hits outrank body hits; newer lessons win ties."""
    head = (title + " " + meta.get("tags", "")).lower()
    return (-sum(t in head for t in terms), p.stem[:10].replace("-", ""))


def cmd_search(a):
    terms = [t.lower() for t in a.terms]
    entries = list(load())
    if not terms:
        tags = {}
        for _, _, meta, _, _ in entries:
            for t in meta.get("tags", "").split(","):
                if t.strip():
                    tags[t.strip()] = tags.get(t.strip(), 0) + 1
        top = sorted(tags.items(), key=lambda kv: -kv[1])[:25]
        print(f"{len(entries)} lessons. Give search terms. Common tags:")
        print(", ".join(f"{t}({n})" for t, n in top))
        return
    hits = [e for e in entries
            if all(t in e[4].lower() for t in terms)
            and (not a.status or e[2].get("status") == a.status)]
    # newest first, then stable sort so title/tag hits outrank body hits
    hits.sort(key=lambda e: e[0].stem[:10], reverse=True)
    hits.sort(key=lambda e: rank(terms, *e[:3], e[4])[0])
    shown = hits if a.full and a.limit is None else hits[: a.limit or 8]
    for p, title, meta, body, text in shown:
        print(f"{p.stem[:10]} {p.stem[11:60]} [{meta.get('status', '?')}] {title[:110]}")
        if a.full:
            print(text)
        elif body.get("fix"):
            print(f"    fix: {body['fix'][:160]}")
    if not hits:
        print("no lessons match")
    elif len(hits) > len(shown):
        print(f"+{len(hits) - len(shown)} more (add terms, --status, or --limit N)")


def cmd_add(a):
    slug = re.sub(r"[^a-z0-9]+", "-", a.title.lower()).strip("-")[:60]
    path = DIR / f"{date.today():%Y-%m-%d}-{slug}.md"
    if path.exists():
        sys.exit(f"lessons: {path} already exists")
    DIR.mkdir(parents=True, exist_ok=True)
    lines = [f"# {a.title}", "", f"- status: {a.status}", f"- tags: {a.tags}"]
    if a.scope:
        lines.append(f"- scope: {a.scope}")
    if a.source:
        lines.append(f"- source: {a.source}")
    lines.append("")
    lines += [f"{f}: {getattr(a, f)}" for f in FIELDS]
    path.write_text("\n".join(lines) + "\n")
    print(path)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("search")
    s.add_argument("terms", nargs="*")
    s.add_argument("--full", action="store_true", help="print whole entries")
    s.add_argument("--limit", type=int, help="max hits shown (default 8)")
    s.add_argument("--status", choices=["works", "fails", "open"])
    s.set_defaults(fn=cmd_search)
    d = sub.add_parser("add")
    d.add_argument("--title", required=True)
    d.add_argument("--status", required=True, choices=["works", "fails", "open"])
    d.add_argument("--tags", required=True)
    for f in FIELDS:
        d.add_argument(f"--{f}", required=True)
    d.add_argument("--scope")
    d.add_argument("--source")
    d.set_defaults(fn=cmd_add)
    a = ap.parse_args()
    a.fn(a)


if __name__ == "__main__":
    main()
