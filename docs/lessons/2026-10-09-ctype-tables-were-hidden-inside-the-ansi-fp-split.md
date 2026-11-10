# ctype tables were hidden inside the ansi_fp split

- status: works
- tags: splits,msl,rodata
- scope: MSL_C
- source: claude/msl-data 2026-10-09

symptom: locale.c had only .data and its pointers referenced .rodata/.sdata2 labels inside ansi_fp.c ranges
cause: ansi_fp.c .rodata (0x8037B2F8..B8E0) and .sdata2 (..B20) swallowed ctype.c (0x8037B3D8..B7D8) and locale.c's strings
fix: Split ansi_fp .rodata to B3D8, add MSL/ctype.c (.rodata B3D8..B7D8), give locale.c .rodata B7D8..B8E0 + .sdata2 B08..B20, end ansi_fp .sdata2 at B08. When a data-only object's relocs point at labels in a neighbour's range, the neighbour's split is too big
