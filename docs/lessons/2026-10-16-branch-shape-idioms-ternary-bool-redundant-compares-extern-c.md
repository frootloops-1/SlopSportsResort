# branch-shape idioms: ternary bool, redundant compares, extern C, s32 return decl

- status: works
- tags: branch,label,BRANCH-SHAPE,clrlwi,extern-C
- source: claude/nm-3 2026-10-16 sonnet worker

symptom: label/branch-shape near-misses in RPSportsCommon
cause: decomp simplified redundant conditions or wrong decl types
fix: 'bne Lx; li 0; b J' = 'return !c ? false : e'; redundant 2nd bge = 'n>=5 || (n<5 && A) || B' literally; doubled cmp blocks = '(a>=K&&d>=K)||(a<K&&d>=K)'; shared tail after an if with flag-true block ending in return; clrlwi. on callee result = callee declared u8 but really s32; mangled-vs-plain symbol = missing extern C; ctor-like fn ending 'mr r3,self' returns self. Failed: fn_801FE230 div CSE order; fn_801F9E48 lwzux table addressing
