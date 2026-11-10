# fn_80236358 r21/r22: hoisted li vreg 95 vs slwi temp vreg 47 sweep order

- status: fails
- tags: fn_80236358,RPTns_80235cd0,regalloc,color_sim
- scope: RPTns_80235cd0

symptom: li 1 gets r22 and slwi temp r21, target reversed (99.8)
cause: slwi temp r47 deg 28 <29 is pushed in sweep 1 before the later-numbered hoisted const r95, so r95 is coloured first; target needs r47 deg>=29 (one more GPR vreg live across lwzx..stwx)
fix: no source spelling found; see 2026-10-29 lesson for forms already tried
