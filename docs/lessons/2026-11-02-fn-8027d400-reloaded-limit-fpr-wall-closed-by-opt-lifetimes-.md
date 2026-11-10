# fn_8027D400: reloaded-limit FPR wall closed by opt_lifetimes off + reused named scalars

- status: works
- tags: fn_8027D400,fpr,colouring,opt_lifetimes,SplitLifetimes,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8027d3ec
- source: bsb7d3ec Opus 2026-11-02

symptom: 99.3: reloaded global limit must be f0 (coloured first) while its load stays before pointer stores; pos/timer temps f2/f1
cause: Scheduler never hoists a DDATA load over pointer stores (Scheduler.c CheckSpillNode), so lim must be created early yet have the highest vreg in the block; backend temps always outrank IRO-level vars. Fix: make every block value an IRO-level named local below lim
fix: #pragma opt_lifetimes off on the function; locals declared lim, b, a (first declared = highest vreg); per component a = pos.x; b = d.x; b = a + b; pos.x = b; timer via b; if (b >= lim). Without the pragma SplitLifetimes makes 10 @temps that drop the callee-saved constants' degree below the limit in the first simplify pass and reorders f27-f31 (52 lines). MATCH-PENDING ledger row 82
