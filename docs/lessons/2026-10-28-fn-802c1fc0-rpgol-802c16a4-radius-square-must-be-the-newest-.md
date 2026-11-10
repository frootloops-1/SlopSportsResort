# fn_802C1FC0 (RPGol_802c16a4): radius-square must be the newest temp: write golLenSq(v) < lbl*lbl as an expression, bool inline at the if-site

- status: works
- tags: regalloc,fpr,inline,marker
- scope: RPGol_802c16a4 fn_802C1FC0
- source: FPR batch 2 2026-10-28

symptom: 99.33; r2 as first inline param is the oldest vreg (f4), target needs it newest
cause: expression temps are newest; as a second param r2 lands in the middle (f2); a plain expression at the if-site loses mfcr/extrwi (ble) so a bool-returning inline reading the global radius is kept there
fix: nearRef/nearPos = golLenSq(GolVec2(..)) < lbl*lbl; if-site via static inline bool golBeyond950(v) (name inferred, MATCH-PENDING R17 + ledger row); 100%
