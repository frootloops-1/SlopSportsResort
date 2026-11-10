# Vtable .data order follows reverse class-declaration order; include the later class header first

- status: works
- tags: vtable,data,order,include,weak
- scope: Pack/RPGraphics/RPGrpModelManager
- source: claude/data-grp-1026

symptom: two vtables in one TU emitted in the wrong .data order (ours Misc,IBinary,Manager vs target Manager,pad,Misc)
cause: MWCC emits vtables in reverse of class declaration order; RPGraphics.h declares Manager before Misc
fix: #include <Pack/RPGraphics/RPGrpModelMisc.h> before <Pack/RPGraphics.h>; strong vtable gets 8-aligned so the 4-byte pad appears; DOL 0 diff
