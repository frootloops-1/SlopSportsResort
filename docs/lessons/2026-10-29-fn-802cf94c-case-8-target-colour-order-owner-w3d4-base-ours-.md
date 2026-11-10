# fn_802CF94C case 8: target colour order owner > w3D4 > base; ours w3D4 temp r107 > base @4031 r55 > owner @4076 r50

- status: fails
- tags: fn_802CF94C,RPBox_802cf93c,regalloc,mwcc_dbg
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: owner r7 vs r5, w3D4 r5 vs r6, base r6 vs r7 (28 lines incl. FPR lerp)
cause: all three are low-degree, so sweep-1 simplify colours by descending vreg (Coloring.c); owner must be the highest (a codegen temp) while w3D4 and base are variables with w3D4 > base
fix: failed: k computed before u (28), named BoxObj** pp += w3D4 (36), static inline BoxPlCurKind(o) wrapper (28)
