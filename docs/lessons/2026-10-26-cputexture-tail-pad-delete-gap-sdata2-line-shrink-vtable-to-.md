# CpuTexture tail pad: delete gap_ sdata2 line + shrink vtable to 0x18 -> .sdata2 100, vtable exact

- status: works
- tags: egg,eggCpuTexture,gap,sdata2,vtable,symbols
- scope: egg/gfxe/eggCpuTexture

symptom: .sdata2 78.26% and __vt__ size 0x20 vs compiled 0x18
cause: trailing zero pad was a gap_ symbol / vtable symbol included alignment pad
fix: delete gap_12_804C05B4_sdata2, set __vt__Q23EGG10CpuTexture size 0x18; DOL 0 diff, 4 known sym collisions. .data % stays low only because weak @STRING@/__dt objects are owned by other TUs
