# fn_80235CD0 other-colouring: colour_sim replay, wall needs vreg 44-46

- status: fails
- tags: fn_80235CD0,RPTns_80235cd0,regalloc,color_sim
- scope: RPTns_80235cd0

symptom: target colours side r31, st r30, e r29, other r28; ours other r30, st r29 (99.2)
cause: named other (vreg 36) has deg 29 so is pushed in sweep 2 and coloured 2nd; inline-expansion temps number descending in source order (st>other>e2..), so an inline 'other' (TnsOpp) is coloured before the loop-2 e (r29 vs r28, 99.3)
fix: no fix: other needs a vreg number 44-46 (after loop IVs, before loop-2 e). Tried inline x3 (62.6), decl order (99.0), plain st expr (99.0), TnsOpp inline (99.3, not kept)
