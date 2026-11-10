# u8 stored into word field

- status: works
- tags: metrotrk,support
- scope: MetroTRK/debugger/Portable/support.c
- source: subagent decomp-standard, verified by orchestrator

symptom: clrlwi+stw instead of stb
cause: plain assignment to u32 field
fix: *(u8*)&reply.field = x
