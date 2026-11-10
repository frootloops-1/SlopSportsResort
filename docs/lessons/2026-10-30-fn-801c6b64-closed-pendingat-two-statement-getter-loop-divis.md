# fn_801C6B64 closed: pendingAt two-statement getter + loop divisor (end - start + 1)

- status: works
- tags: RPUtility,801C67B8,fn_801C6B64,regalloc,inline-getter,CSE
- source: claude/u67-1030

symptom: start r7 vs r4 swapped with CSE'd samples ptr (90 lines); then r11/r12 mulli vs addi length+1 swap (8 lines)
cause: samples @N temp coloured before named start; loop divisor (f32)(length+1) CSE'd with b.x created a late high-numbered addi temp coloured before the wrap mulli
fix: start = self->pendingAt(axis) with s32 pendingAt(a){s32 p=pending[a];return p;} (R17); divisor static_cast<f32>(end - start + 1) -> 100, DOL 0. Dead ends: named Sample* samples local (98.5-98.7), no named start (94.4), b.y before b.x (96.2), named count (94.5-98.9), / b.x (94.0), at()/axis() helper reshapes (no change)
