#!/bin/bash
# compiler_sweep.sh OGWS_DIR RESORT_DIR OUT_DIR UNIT... : compile ogws units with each compiler, score vs Resort
OG=$1; RS=$2; OUT=$3; shift 3
VERS="GC/3.0a3 GC/3.0a5 GC/3.0a5.2 Wii/0x4201_127 Wii/1.0RC1 Wii/1.0a Wii/1.0 Wii/1.1 Wii/1.3 Wii/1.5 Wii/1.7"
cd "$OG"; RUN=${RUN_DIR:-$OG}; EXTRA=${EXTRA_FLAGS:-}
for u in "$@"; do
  cmd=$(ninja -t commands build/RSPE01_01/src/$u.o 2>/dev/null | tail -1 | sed "s/ && .*//; s/SportsPack.mch/SportsPack.pch/")
  for v in $VERS; do
    o="$OUT/$(echo $u | tr / _)__$(echo $v | tr / _).o"
    c=$(echo "$cmd" | sed -E "s#build/compilers/[^ ]+/mwcceppc.exe#$RS/build/compilers/$v/mwcceppc.exe#; s# -MMD# $EXTRA#; s# -o [^ ]+# -o $o#")
    if (cd "$RUN" && eval "$c") >/dev/null 2>&1; then
      printf "%-34s %-16s %s\n" "$u" "$v" "$(python3 $RS/tools/obj_score.py $o $RS/orig/RZTE01_01/sys/main.dol $RS/config/RZTE01_01/symbols.txt)"
    else printf "%-34s %-16s compile failed\n" "$u" "$v"; fi
  done
done
