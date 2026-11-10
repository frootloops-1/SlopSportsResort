# fn_8033DB38 (RPBow_8033B690) hard tier: two independent register walls (si/sj among loop temps; velI-first FPR order), 13 more hypotheses no gain

- status: fails
- tags: RPBow_8033B690,fn_8033DB38,register,colouring,FPR,decomp-hard,wall
- scope: Pack/RPSports/RPBowScene/RPBow_8033B690
- source: orchestrator-1028

symptom: 96.0%. Orig int order from top: impI addr, impJ addr, sj, i-off, j-off, bit_i, word_i, nearI-it, si, word_j, bit_j, nearJ-it, sj-it, a, b, data, self, one; ours: impI, impJ, i-off, ..., sj-it, sj, si, a, b, data, self, one (si/sj always with ordinary user vars). Velocity block: orig computes velI = cpI - oI first
cause: two separate walls: (1) si/sj allocated among compiler loop temporaries in the original; (2) FPR allocation changes when velI/velJ source order is swapped (n.yz ps_mr lands f4 vs f6, 94.2)
fix: failed: no sj var / pj->sph[k] direct (95.0, keeps pj and folds 0x170), si++ pointer loop + sb=sj (95.9), static inline accessor BowSph(pj) (identical), b-loop via pj->sph[b] (95.7), si/sj after k-loop (94.6), sibling fn_803395E4 style sphJ/sphI (95.9), BowPinSphere* const sj (96.0 but swaps si and sj with each other; only thing that moved anything), const both (95.9), int i,j at function scope (identical), si/sj from self->mpPins[x]->sph (identical), both at function scope (identical), velI before velJ + vi before vj (93.1), a/b loops in a static inline helper (40.8). Park.
