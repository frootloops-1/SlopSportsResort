# fn_801E7EB4: build pos from the pane translation then divide in place

- status: works
- tags: scheduler,fpr,fn_801E7EB4,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_801E7EB4
- source: step2 2026-11-01

symptom: 99.3%: quotient f2 / hh lfd f0 swapped
cause: pre-RA list scheduler hoisted the hh conversion lfd above the fdivs for x (source shape, not vreg numbering)
fix: EGG::Vector2f pos(mtx._03, mtx._13); pos.x /= (u16)(w/2); pos.y /= (u16)(h/2); plain source. Dead: all operands inline in the ctor (98.1), struct half(w/2,h/2) (93.3), member-wise pos.x = mtx/(u16)(w/2) (31.2). Tip: NonMatching units link the original obj/, so dol_diff 0 proves nothing; pre-check by swapping the src object into the build.ninja link line
