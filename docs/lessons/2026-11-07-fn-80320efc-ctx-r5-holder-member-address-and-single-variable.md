# fn_80320EFC ctx r5: holder, member-address and single-variable forms all flat (round 8)

- status: fails
- tags: regalloc,RPBow_80320EFC,webs,holder
- scope: Pack/RPSports/RPBowScene/RPBow_80320EFC

symptom: ctx (@719) r4 vs retail r5 in the final debug block; neighbours only r0/r3, block insn count identical to retail
cause: Named locals are split into webs before the backend (j has 4 vregs), and IRO gives a reassigned ctx a fresh vreg in initial code; &ctx->vA0 pointers/refs fold in the front end; post-RA VN and peephole are no-ops here. So the hidden r4 neighbour or the merge with the r5 BowRatio load cannot come from these spellings.
fix: Dead (harness 5, all identical): ctx at function/block scope reassigned before BowRatio, assignment-in-condition (7), f32 r ratio local; const BowVec2& p / BowVec2* p = &ctx->vA0 at block or inner scope; one-field holder struct {BowThrowCtx* p} (function/block scope, reassigned or not); BowVec2* p = &lbl (9). Parked.
