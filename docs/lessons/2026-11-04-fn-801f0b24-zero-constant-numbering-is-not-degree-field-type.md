# fn_801F0B24: zero-constant numbering is not degree; field types / helpers do not move it

- status: open
- tags: regalloc,color_sim,constants,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: retail IV r31/i r30/self r29/one r28/zero r27; ours zero r31
cause: color_sim: removing up to 4 edges of the zero never reaches retail; only renumbering does (zero between init's lis 0x4330 and li 1, or 0x4330 before zero before one). MWCC keeps the FIRST li 0's vreg when it merges constants, and the first is the p+0x30 store
fix: FAILED: pointer/u32/BOOL types for the zero stores, the stores in an inline helper, the whole loop body in a helper, zero as inline param. Needs a source shape where the early stores do not create a zero constant before init()
