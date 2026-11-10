#!/bin/bash
# Dump the real GC/3.0a5.2 compiler's PCode and register-allocator state for ONE function of ANY unit (C or C++).
#   tools/mwcc_dbg.sh <unit-path-under-src-without-ext> <function> <outdir>
# e.g. tools/mwcc_dbg.sh egg/gfxe/eggCpuTexture setColor /tmp/dump
# Run from a built worktree root. ~2 min. Needs $OGWS_TOOLS (default ~/Downloads/ogws-tools) with mwcc-debugger/ (gc30/NOTES.md) and retrowin32/.
# C++ functions are matched by their UNQUALIFIED name (setColor, Draw), not the mangled one; overloads: first match wins.
# The dump is of OUR source; the target is read from its disassembly. See docs/mwcc-debugger.md.
# CONCURRENCY: both mwcc_debugger.py (gdb "target remote localhost:9001") and retrowin32 (cli/src/debugger.rs) hard-code
# TCP port 9001, so two runs at once make one gdb attach to the OTHER run's compiler (and dump the wrong worktree).
# The port is not configurable, so runs are serialised with a global lock (/tmp/mwccdbg.lock, mkdir-based, pid-checked so a
# crashed run does not wedge anyone; MWCC_DBG_LOCK_TIMEOUT seconds, default 3600) and we also wait for port 9001 to be free
# (covers runs started by an old copy of this wrapper). After the run the debugger log must show this worktree's source.
set -euo pipefail
UNIT=$1; FN=$2; OUT=$3
ROOT=$(git rev-parse --show-toplevel); cd "$ROOT"
OBJ=build/RZTE01_01/src/$UNIT.o
SRC=$(ls src/$UNIT.cpp src/$UNIT.c 2>/dev/null | head -1 || true)
CMD=$(ninja -t commands "$OBJ" | tail -1 | sed -e 's/ *&&.*$//' -e 's/^.*mwcceppc.exe/build\/compilers\/GC\/3.0a5.2\/mwcceppc.exe/' -e 's/ -enc SJIS//' -e 's/ -MMD//' -e 's/ -o [^ ]*$//')
CMD="$CMD -o /private/tmp/mwccdbg_obj_$$"
mkdir -p /private/tmp/mwccdbg_obj_$$ "$OUT"

LOCK=/tmp/mwccdbg.lock
TIMEOUT=${MWCC_DBG_LOCK_TIMEOUT:-3600}
HAVE_LOCK=0
cleanup() {
  rm -rf "/private/tmp/mwccdbg_obj_$$"
  if [ "$HAVE_LOCK" = 1 ]; then rm -rf "$LOCK"; fi
}
trap cleanup EXIT
trap 'exit 130' INT TERM HUP
port_busy() { python3 -c 'import socket,sys; s=socket.socket(); s.settimeout(1); sys.exit(0 if s.connect_ex(("127.0.0.1",9001))==0 else 1)'; }
waited=0; announced=0
while :; do
  if mkdir "$LOCK" 2>/dev/null; then
    echo $$ >"$LOCK/pid"; echo "$ROOT" >"$LOCK/root"; HAVE_LOCK=1
    if port_busy; then   # someone not using the lock (old wrapper / manual run) holds 9001
      rm -rf "$LOCK"; HAVE_LOCK=0
    else
      break
    fi
  else
    holder=$(cat "$LOCK/pid" 2>/dev/null || true)
    if [ -n "$holder" ] && ! kill -0 "$holder" 2>/dev/null; then
      echo "mwcc_dbg: removing stale lock (pid $holder is gone)" >&2
      mv "$LOCK" "$LOCK.stale.$$" 2>/dev/null && rm -rf "$LOCK.stale.$$"
      continue
    fi
    if [ -z "$holder" ] && [ -d "$LOCK" ] && [ -n "$(find "$LOCK" -maxdepth 0 -mmin +1 2>/dev/null)" ]; then
      mv "$LOCK" "$LOCK.stale.$$" 2>/dev/null && rm -rf "$LOCK.stale.$$"; continue   # pid file never written
    fi
  fi
  if [ "$announced" = 0 ]; then
    echo "mwcc_dbg: waiting for another dump to finish (port 9001 is single-user; holder: pid ${holder:-?} $(cat "$LOCK/root" 2>/dev/null))" >&2
    announced=1
  fi
  if [ "$waited" -ge "$TIMEOUT" ]; then echo "mwcc_dbg: gave up after ${TIMEOUT}s waiting for the debugger lock" >&2; exit 2; fi
  sleep 5; waited=$((waited+5))
done
[ "$announced" = 1 ] && echo "mwcc_dbg: lock acquired after ${waited}s" >&2

python3 -I "${MWCC_DEBUGGER:-${OGWS_TOOLS:-$HOME/Downloads/ogws-tools}/mwcc-debugger/mwcc_debugger.py}" -e "${OGWS_TOOLS:-$HOME/Downloads/ogws-tools}/retrowin32/target/lto/retrowin32" -g x86_64-elf-gdb -a "$CMD" "$FN" "$OUT" >"$OUT/run.log" 2>&1 || { tail -5 "$OUT/run.log"; exit 1; }
# Guard: the log's 'Reading <path>' lines must come from THIS worktree (a stray run on port 9001 would show another one).
foreign=$(grep -ao 'Reading /private/tmp/[^/ ]*' "$OUT/run.log" 2>/dev/null | sort -u | grep -v -F "Reading $ROOT" || true)
if [ -n "$foreign" ]; then
  echo "mwcc_dbg: FAIL: dump is from another worktree ($foreign), expected $ROOT; discard $OUT and rerun" >&2; exit 3
fi
if ! grep -aq "Reading $ROOT" "$OUT/run.log"; then
  echo "mwcc_dbg: WARNING: no 'Reading $ROOT' line in $OUT/run.log; cannot confirm the dump is from this worktree" >&2
fi
echo "dump in $OUT (backend-*.txt, regalloc-gpr-pass-1-assigned.txt)"
