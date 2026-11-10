#!/bin/bash
# Create a ready-to-build worktree for one parallel worker (see docs/matching-playbook.md).
#   tools/setup_worktree.sh <new-worktree-dir> <new-branch> [base-ref]
# Run from a fully built worktree (it clones that worktree's build/ and orig/ sys data).
# Agent files (AGENTS.md, CLAUDE.md, .claude/, docs/, tools/lessons.py, tools/route_functions.py) are tracked,
# so they come with the checkout; commit them on main first if they have uncommitted edits.
set -euo pipefail
DIR=$1
BR=$2
BASE=${3:-HEAD}
SRC=$(git rev-parse --show-toplevel)

git worktree add -b "$BR" "$DIR" "$BASE" >/dev/null
mkdir -p "$DIR/orig/RZTE01_01"
cp -Rc "$SRC/orig/RZTE01_01/sys" "$DIR/orig/RZTE01_01/" 2>/dev/null || cp -R "$SRC/orig/RZTE01_01/sys" "$DIR/orig/RZTE01_01/"
# Only what a build needs (skips build/evidence and the ghidra-* dirs, ~2 GB); -c clones on APFS.
mkdir -p "$DIR/build"
for d in tools compilers binutils RZTE01_01; do
  [ -d "$SRC/build/$d" ] && { cp -Rcp "$SRC/build/$d" "$DIR/build/$d" 2>/dev/null || cp -Rp "$SRC/build/$d" "$DIR/build/$d"; }
done
# ninja's log/deps let it trust the copied tools instead of re-downloading them
for f in .ninja_log .ninja_deps; do [ -f "$SRC/$f" ] && cp "$SRC/$f" "$DIR/$f"; done
(cd "$DIR" && python3 configure.py >/dev/null 2>&1 || true)
# Touch the copied tools after configure so ninja does not try to re-download them.
find "$DIR/build/tools" "$DIR/build/compilers" "$DIR/build/binutils" -exec touch {} + 2>/dev/null || true
(cd "$DIR" && ninja -t restat >/dev/null 2>&1 || true)
(cd "$DIR" && ninja >/dev/null 2>&1 || true)
echo "ready: $DIR ($BR)"
