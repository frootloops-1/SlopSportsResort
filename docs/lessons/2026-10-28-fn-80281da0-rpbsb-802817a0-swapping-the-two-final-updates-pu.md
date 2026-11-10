# fn_80281DA0 (RPBsb_802817a0): swapping the two final updates puts diff on f3 but moves score and swaps the stores

- status: fails
- tags: regalloc,fpr
- scope: RPBsb_802817a0 fn_80281DA0
- source: FPR batch 2 2026-10-28

symptom: 99.71; target diff f3 / score cvt f2, ours f2/f1
cause: creation order of the int conversions drives it (as the model says) but the statement swap changes the stores too
fix: none: decl moves, f32 score=0.0f, ang2 local, += (identical), AddScore/Grade inline (flat; Grade broke fn_80282274 100->0), s32 idiff/iscore locals (99.2)
