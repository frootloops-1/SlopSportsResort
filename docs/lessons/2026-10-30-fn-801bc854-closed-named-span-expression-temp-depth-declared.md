# fn_801BC854 closed: named span -> expression temp, depth declared first

- status: works
- tags: fn_801BC854,RPUtlCollisionChecker,fpr,colouring,mwcc_dbg,named-local,temp
- scope: Pack/RPUtility/RPUtlCollisionChecker
- source: claude/chk-1030 9bc5badb7

symptom: 99.4 FPR residue: endDistance f7 vs f9, zero f6 vs f7, span f9 vs f6, start.y/z swap
cause: mwcc_dbg FPR order: temps (s/e reloads, 0.0f const) coloured before named locals; target has span as an unnamed temp (coloured before zero) and depth coloured before endDistance
fix: replace f32 span with (endDistance - startDistance) everywhere (CSE temp); declare 'f32 depth;' before VEC3 start; write start x,y,z -> 100, no markers, unit flipped (DOL 0)
