# fn_8020CB74: const c plus colour computed after position copies

- status: works
- tags: constness,fn_8020CB74,fpr,statement-order,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b294
- source: constsweep 2026-11-01

symptom: 80.1% / 46 lines; u32->float magic temps and divisor one FPR higher (f5/f1/f2 vs f4/f0/f1)
cause: statement order sets vreg numbering and so FPR colouring
fix: const _GXColor* c, move mkScaledColor(...) below the six TriView r/p/q copies (no marker)
