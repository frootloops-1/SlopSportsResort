# fn_801BB9B8 first-block FPR colouring wall (delta/e1/e2 callee choice)

- status: fails
- tags: fpr,regalloc,wall,RPUtlCollisionModel,permuter
- scope: Pack/RPUtility/RPUtlCollisionModel
- source: claude/rputl-cmod-1027

symptom: target e2 + e1.y callee-saved, d2=f13 d3=f9; ours e1 + delta.x callee; 128 lines pure FPR
cause: unknown colouring order; scheduling identical
fix: failed: dot operand order/pointer/x+y+z, delta member stores/scalars, cosine decl order, scalar distance locals, pointers up front, decl positions, const Triangle*, permuter 9 min (520 flat)
