# fn_80320EFC loop-1 15.0f vs m FPR swap insensitive

- status: fails
- tags: RPBow_80320EFC,regalloc,fpr,licm
- scope: fn_80320EFC

symptom: 15.0f const f18 vs retail f19, m f19 vs f18
cause: both high-degree; order by spill weight, not vreg
fix: none. Dead: decl perms loop1 and block1, direct cos/sin, m without local/at block scope/shared with ang (132), named 15.0f local (208+)
