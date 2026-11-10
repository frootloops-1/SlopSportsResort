# fn_801A2EFC u8 counter lead closed: 25 forms

- status: fails
- tags: fn-801a2efc,RPSysSystemWinMgr,loop,u8
- source: claude 2026-10-26

symptom: target index clrlwi r0,r29,24 at top and raw latch addi/cmplwi; need u8 truncation in latch at RA time without emitting it
cause: u8 do-while ++i / n=i+1 / (u8)(++i)<2 / u16 do-while: exact regs, 12 lines (4 extra clrlwi); i=i+1 / +=1 / (u8)(i+1) / &0xFF do-whiles: 24 lines (truncation moves from index to latch); for(;;i=i+1) rotates loop 194; s8 gives cmpwi; every raw-latch form (u8 for with casts/!=/swapped, u16 for, u32/u16 do-while with (u8) index, separate u32 test) is 486
fix: unsolved; kept reset();start() split (4 lines) remains best
