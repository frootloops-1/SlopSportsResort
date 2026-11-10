# fn_802BB608 sound-mgr r29/r30 and fn_802BC904 work-ptr r28/r30 swaps

- status: open
- tags: golf,regalloc
- scope: RPGol_802bb608
- source: opus-worker

symptom: 99.0 / 99.8 register-only diffs
cause: unknown
fix: failed: early return vs if/else, decl orders, self-loading inline, add/dist locals; block-scoped loop vars, apply/reset inlines. Try permuter
