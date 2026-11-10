# fn_802631C8/B0: extern const on .sdata floats (lbl_804BE118/11C) fixed fmuls/lfs hoist

- status: works
- tags: sdata,extern-const,scheduling,RPBsb_8025ff94
- scope: RPBsb_8025ff94

symptom: Tiny float-store fns: ours hoisted lfs/fmuls above the first stfs (fn_802631C8 41.4%), or loaded the .sdata2 zero before the .sdata float (fn_802631B0)
cause: Declared extern const f32 on a writable .sdata global; compiler treats it as immutable and schedules the load freely
fix: extern f32 lbl_804BE118/11C (non-const); both asm-identical. Blanket de-const of RPSports_801f9534/801fd3c8 sdata externs REGRESSED (19/23, 6/9): apply per symbol only where a diff shows load hoisting. fn_80260604 volatile locals vs BsbVecSub/plain/ordered locals: all worse (95-96.5 vs 97.7).
