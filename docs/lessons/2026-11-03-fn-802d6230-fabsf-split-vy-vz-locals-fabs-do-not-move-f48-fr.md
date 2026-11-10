# fn_802D6230: __fabsf, split vy/vz locals, __fabs do not move |f48| from f12 to f9

- status: fails
- tags: fn_802D6230,RPBox_802cf93c,regalloc
- scope: RPBox_802cf93c

symptom: 102 lines: |f48| vreg f87 (asm BoxFAbs, front-end @) is coloured after the first Hermite body temps (f93-f102) and gets f12; target gets f9 (before dy/b0 f10/f11); also first V part's sign/herm f2/f3 swapped
cause: retail needs |f48| coloured between the Hermite temps, i.e. a vreg created after the dy/b temps while the fabs instruction is still scheduled early
fix: failed: __fabsf both (fabs no longer hoisted, 141), named vz-then-vy / vy-then-vz locals (141/147), __fabs (153). Also first diff line is lis/addi against ...bss.0 vs lbl_804A95F0 (reloc symbol, not code)
