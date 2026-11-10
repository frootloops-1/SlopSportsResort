# AccessExtended2 loop var and ioResult types

- status: works
- tags: metrotrk,targimpl
- scope: MetroTRK/debugger/Processor/targimpl.c
- source: subagent decomp-standard, verified

symptom: wrong param register order; cmplwi instead of cmpwi
cause: param used as counter; unsigned ioResult
fix: separate u32 i = firstRegister; int ioResult cast (u32*) at call; pass (u8)GPR[5]
