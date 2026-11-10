# fn_802BB608 / fn_802BCA94 s7C tail: target loads 0 once, stores it to b78, copies with mr r0,r3 (m=7 in r0); every spelling flat or worse

- status: fails
- tags: regalloc,gpr,schedule
- scope: RPGol_802bb608 fn_802BB608
- source: Gol units 2026-10-28

symptom: 99.5 remaining 14 lines, opcode stream differs (li r0,0 / li r3,7 / li r3,0 vs shared li r3,0 + mr r0,r3)
cause: same wall as sibling fn_802BCA94's b80=0 store; constant ternaries become branchless, other shapes change the branch
fix: none: m as u8/u32/int/bool, false/(u8)0, res->b78 forward (lbz reload), nested flags inline, inline-return, all ternaries, if/else local or stores, m=0 to b78 then if(!on) m=7, double s7C store. park
