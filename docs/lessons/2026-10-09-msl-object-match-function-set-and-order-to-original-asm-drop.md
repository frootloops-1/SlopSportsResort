# MSL object: match function set and order to original asm, drop extra ss functions

- status: works
- tags: msl,order
- scope: MSL_C ports
- source: claude/msl-text string.c 2026-10-09

symptom: ss-ported unit has functions at 0% (missing) and extra symbols
cause: ss copy has functions (strlen, strrchr) not in this object, and older-MSL idioms for strncat/strstr (pointer-walk with *++p, unsigned long temporaries)
fix: Check the .fn order in build/RSPE01_01/asm/MSL/<unit>.s; delete extras, add missing functions in order, write old-MSL pointer-walk style
