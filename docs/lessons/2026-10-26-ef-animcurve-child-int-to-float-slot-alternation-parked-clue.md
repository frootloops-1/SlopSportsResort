# ef_animcurve Child: int-to-float slot alternation + parked clues

- status: open
- tags: ef_animcurve,int-to-float,stack-slots,regalloc
- scope: src/nw4r/ef/ef_animcurve.cpp

symptom: Child 97.9: 2nd inlined frame-calc copy has int->float stack slots 0x8/0x10 swapped; frame1 clrlwi not before loop branch; copy-1 FPR f0/f1
cause: MWCC alternates the two int->float slots per conversion created (dead ones count); 11 conversions per helper copy (odd) flips copy 2. Per-variable use counts identical to orig, so colouring wall is pre-allocation IR numbering
fix: dead (f32)life after TURN 'scaled' fixes slots (696->654 diff lines, still 97.9) - marker, not kept; helper arg/return shapes (u16& out, CalcFrameStep, s32 ret, tick+1 local) do not move clues a/c; parked
