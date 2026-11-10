# Actor-ctor tail 'li r4,N' vs 'li r0,N' with addi hoisted above stw 0x44 (4 functions)

- status: fails
- tags: dead-end,ctor,regalloc
- scope: RPTns,RPBow,RPBsb
- source: claude

symptom: fn_80214B64, fn_8032F2B8, fn_80323228, fn_802597F4: orig li r0,N and addi after second stw; ours li r4,N and addi above
cause: unknown register-coloring order for the shared constant
fix: tried 24 store permutations, chain assign, vt local, struct view, real class model, new BowSnd6C, manual inline. Unsolved; reproduces in a standalone mwcc harness
