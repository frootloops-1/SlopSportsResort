# fn_80200A88 closed: loop body as inline helper makes the row pointer a late vreg, so IV/counter colour before self

- status: works
- tags: regalloc,color_sim,inline,simplify,RPSports_801ffec0
- scope: Pack/RPSports
- source: claude/sp801ff-1103

symptom: self r31 / IV r30 / i r29 vs retail IV r31 / i r30 / self r29; typed param or local copy of self no change
cause: color_sim sweep model K=29: named p (r36, deg 18) pushed first in sweep 1, dropping i/IV to 28 so they were pushed in sweep 1 and self (deg 35) in sweep 2 = coloured first
fix: static inline SpRowResetVisible(void* p) holding the body, called with self->rows[i]: p numbered late, i/IV stay deg 29 until sweep 2 after self -> IV r31, i r30, self r29. 93.6 -> 100 (R17 ledger 158)
