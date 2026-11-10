# SDK pad_ bss units: missing ALIGN(32) and unreferenced globals (check forecast)

- status: works
- tags: bss,pad,align,sdk,forecast
- scope: revolution/BTE/main/bte_main,revolution/DVD/dvd_broadway,revolution/NAND/NANDCore
- source: session-2026-11-07

symptom: auto pad_09_* bss units of 8/16/0x40 B between SDK units
cause: NANDCore: natural 32-align (split lacked align:32); bte_main: s_btu_stack ALIGN(32) missing; dvd_broadway: unreferenced globals coverStatus/coverRegister (globals survive, statics are dropped)
fix: splits align:32 on next unit .bss; s_btu_stack ALIGN(32) per forecast; add DVDLowRegBuffer coverRegister/coverStatus ALIGN(32) uninit globals, declared in reverse (MWCC lays uninit globals out in reverse decl order). Supersedes 2026-10-26 SIBios gap lessons
