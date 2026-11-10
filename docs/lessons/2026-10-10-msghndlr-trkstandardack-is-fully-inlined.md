# msghndlr TRKStandardACK is fully inlined

- status: works
- tags: metrotrk,msghndlr
- scope: MetroTRK/debugger/Portable/msghndlr.c
- source: subagent decomp-standard, verified

symptom: no standalone TRKStandardACK in asm
cause: inlined at every call, double g_CurrentSequence++
fix: static inline with local 0x40-byte reply struct; switch case order 0x703,0x701,0x702,0x704 in Read/WriteRegisters; error vars int
