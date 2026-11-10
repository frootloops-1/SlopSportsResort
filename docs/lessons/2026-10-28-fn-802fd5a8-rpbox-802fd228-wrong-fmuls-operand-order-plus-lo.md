# fn_802FD5A8 (RPBox_802fd228): wrong fmuls operand order plus low-register constants means a hand-expanded lerp; use the unit's existing BoxLerp

- status: works
- tags: regalloc,fpr,inline
- scope: RPBox_802fd228 fn_802FD5A8
- source: FPR batch 2 2026-10-28

symptom: 94.89 -> 97.1 (partial)
cause: commutative operand order follows vreg class, so a flipped operand order is a sign of a missing inline helper; the inline also colours the shared 1.0/0.4/0.0 constants as the target does
fix: case 2 uses BoxLerp(unkE4, unkE8*f[3], unk70) and BoxLerp(0.4f,1.0f,unk28); BoxLerp body moved above its forward declaration so it inlines. No marker. Remaining: Hermite eval inline temp colouring
