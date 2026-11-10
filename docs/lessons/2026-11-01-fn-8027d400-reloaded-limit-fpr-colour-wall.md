# fn_8027D400: reloaded limit FPR colour wall

- status: fails
- tags: fn_8027D400,fpr,colouring,IRO_SplitLifetimes,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8027d3ec
- source: batch 2026-11-01

symptom: 99.3%, 34 lines after bl fn_801BF32C: reloaded limit lbl_804BE568[0] is f0 in the original, f2 in ours; pos/timer temps f2/f1 vs f1/f0; schedule identical
cause: second lim becomes IRO temp @2610 (vreg f34) via IRO_SplitLifetimes, below the back-end pos/timer temps f52-f63, so it colours last; to get f0 it needs the highest vreg in the block while its load stays before the pos stores (Scheduler: global loads depend on earlier pointer stores, const does not change it)
fix: none. Dead: version sweep (6 builds 99.84), named timer local (substituted away), struct-return scale call (load moves after stores or adds copies, 96-178 lines), scalarised pos copy, identical/mixed-arm ternary, 8-min regsearch 608 evals. Idea if retried: a construct creating the limit vreg late while its load stays early (unconfirmed pre-RA peephole)
