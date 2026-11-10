# TRKDoSetOption string pool dead end

- status: fails
- tags: metrotrk,msghndlr
- scope: MetroTRK/debugger/Portable/msghndlr.c
- source: subagent decomp-standard

symptom: pool base not hoisted to r31, strings packed 0/0x1f/0x27 instead of 0/0x20/0x28
cause: unknown; -str pool strings unaligned
fix: ternary and three static const char[] did not help
