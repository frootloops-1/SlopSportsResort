# fn_80322B68 (RPBow_80320EFC): a const f32 local with a literal init is propagated as a late literal temp; drop const to keep an old named vreg

- status: works
- tags: regalloc,fpr,const
- scope: RPBow_80320EFC fn_80322B68
- source: FPR batch 2 2026-10-28

symptom: 99.90
cause: const local with literal init is propagated into a late (newest) literal temp -> f2; non-const named local is an old vreg -> f4; moving it to the block top regresses (98.2, live across sin/cos)
fix: `const f32 distance = 20.0f;` -> `f32 distance = 20.0f;` same position; 100%, no marker. General: const named local != named local for colouring
