# ternary cmd byte vs local u8

- status: works
- tags: metrotrk,support
- scope: MetroTRK/debugger/Portable/support.c
- source: subagent decomp-standard, verified by orchestrator

symptom: read ? 0xD1 : 0xD0 compiles to neg/or trick
cause: ternary constant select
fix: u8 cmd = 0xD0; if (read) cmd = 0xD1; reply.cmd = cmd;
