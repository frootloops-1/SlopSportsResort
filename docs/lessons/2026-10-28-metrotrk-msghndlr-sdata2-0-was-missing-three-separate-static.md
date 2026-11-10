# MetroTRK msghndlr: -sdata2 0 was missing; three separate static const char[] under pool_data give addi r3,r31,0

- status: works
- tags: MetroTRK,msghndlr,pool_data,sdata2,strings,forecast
- scope: MetroTRK/debugger/Portable/msghndlr
- source: session 2026-10-28

symptom: TRKDoSetOption 99.94%: target addi r3,r31,0 for the first string where our struct-of-strings emitted mr r3,r31; plain literals gave per-string lis/addi and a packed pool (0x1f offset) unlike the 0x20/0x28 target layout
cause: cflags_trk lacked -sdata2 0 (doldecomp/forecast has it). Without it the 8-byte 'Enable\n' array went to .sdata2, so the arrays could not share one pooled .rodata base. With -sdata2 0 and three file-level static const char[] (4-aligned, 0x20/0x28 offsets) pool_data uses base+offset for all, including offset 0 as addi
fix: cflags_trk += -sdata2 0; static const char sOption[], sEnable[], sDisable[]; function under #pragma pool_data on (the pragma around the declarations is not needed). 16/16 exact, DOL 0, unit Matching. Permuter 'score 100' candidates used an uninitialised variable: not honest. Check the reference decomp's configure.py flags (not only its source) before reshaping source
