# RPGol 7CD8 pool: deferred-inline / param-order levers do not change pool order

- status: fails
- tags: sdata2,pool-order,inline-deferred,RPGol_802a7a40
- scope: Pack/RPSports/RPGolScene/RPGol_802a7a40
- source: claude/gol-7a40-1104

symptom: pow base literal pooled after the inline InvLerp divisor
cause: inline expansion order, not definition position or call arg order
fix: FAILED (no pool change): GolInvLerp defined after the caller with forward decl, non-inline static InvLerp (auto-inlined), pow wrapper with swapped params GolPowR(e,k), extern const global (lbl_804C4390) as divisor. Note @N names are not pool-position order (names can lag), only positions matter.
