# fn_802C5C78 FPR numbering residue (99.4)

- status: open
- tags: regalloc,fpr,camera
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: dot(m+3) in f30 vs orig f31; VEC3Lerp work regs off; remap const regs
cause: unknown
fix: failed: 120 decl perms of x/y/sq/ax/ay, sq placement, abs forms, VecDot arg swap, neg helper, lerp return out ptr, remap local variants; try permuter
