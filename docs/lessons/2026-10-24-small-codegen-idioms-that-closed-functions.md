# Small codegen idioms that closed functions

- status: works
- tags: idiom,cntlzw,pre-increment,volatile
- scope: project
- source: claude

symptom: assorted 1-5 insn diffs
cause: see fix
fix: (1) bool computed then passed to an inline gets folded after the call: 'u32 is4 = (u32)__cntlzw(x-4) >> 5;' (2) 2D fill loop with stwu: 's32* p = m->score[i]-1; ... *++p = v' (3) real struct members instead of a hand-offset List struct (+0.9) (4) check GX enum immediates in TEV calls (li 0xc = GX_CC_ONE) (5) 'for(..;j++,i++)' vs 'i++,j++' changes tail order (6) 'f32 m = ...' declared at first assignment changes FPR colouring (7) cond ? clamp(..) : b as if/else changes FPR numbering (8) header inline whose pointer the target reloads: file-local static inline copy with volatile read of the pointer, never edit the shared header (ef_drawfreestrategy 99.66 -> 99.97) (9) '*(volatile s32*)&e->a == ids[k]' restores per-compare reload in an unrolled loop
