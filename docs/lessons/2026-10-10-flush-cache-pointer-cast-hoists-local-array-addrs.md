# flush_cache pointer cast hoists local array addrs

- status: works
- tags: metrotrk,targimpl
- scope: MetroTRK/debugger/Processor/targimpl.c
- source: subagent decomp-standard, verified

symptom: no hoist of addi rX,r1,off; wrong regs in AccessFP/AccessExtended2
cause: mwcc folds local array address into each use
fix: TRK_flush_cache((void*)(u32)access_func, n)
