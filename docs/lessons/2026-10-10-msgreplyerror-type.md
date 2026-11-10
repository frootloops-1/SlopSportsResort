# msgReplyError type

- status: works
- tags: metrotrk,support
- scope: MetroTRK/debugger/Portable/support.c
- source: subagent decomp-standard, verified by orchestrator

symptom: cmplwi instead of cmpwi
cause: variable declared u8
fix: declare it int
