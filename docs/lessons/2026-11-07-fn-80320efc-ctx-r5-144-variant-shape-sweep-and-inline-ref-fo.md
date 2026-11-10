# fn_80320EFC ctx r5: 144-variant shape sweep and inline/ref forms all leave ctx in r4

- status: fails
- tags: mwcc,regalloc,fn_80320EFC,RPBow,lowest-free
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: IRO CSE temp ctx gets r4 (neighbours only r0/r3); retail r5 with no r4 instruction in the block
cause: lowest-free colouring needs an r4 neighbour or a merge with the BowRatio reload node; IRO splits a reassigned named ctx (2nd def gets its own temp even for a const-typed named var)
fix: none. Dead: outer-if form x ctx type x sbuf pos x compare order x Set form x reload form (144), ctx as T* const& / T*& to member, inline helpers taking ctx&/self/dst&/limit, BowIsEarly/BowLastPos/BowGetCtx, ctor/copy-op struct assign, named BowVec2& last (real hoisted li vreg), dead return-ref Set
