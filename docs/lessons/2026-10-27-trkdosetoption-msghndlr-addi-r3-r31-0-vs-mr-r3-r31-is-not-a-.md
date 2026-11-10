# TRKDoSetOption (msghndlr): 'addi r3,r31,0' vs 'mr r3,r31' is not a -str flag or pointer-expression issue

- status: fails
- tags: msghndlr,TRKDoSetOption,MetroTRK,addi,mr,str,F9
- scope: MetroTRK/debugger/Portable/msghndlr
- source: orchestrator-1027

symptom: 98.8%, 1 wrong line at 0x800C218C: target addi r3,r31,0x0 before first usr_puts_serial, ours mr r3,r31; same call set, control flow, registers
cause: offset-0 address of the hoisted section-relative base is emitted as a copy (mr) by ours; original emits addi rX,r31,0 (OS.c ReportOSInfo hoists lis r31,@N@ha bases for unpooled literals, so the original TRK probably had unpooled 4-aligned literals)
fix: failed: (const char*)&sSetOptionStrings first arg, local const char* p, strs declared after enable, global directly (80.4, no hoist), three static const char[] under pool_data (84.2), plain literals + #pragma pool_strings off (84.2), non-const struct ptr (build fail); per-object cflags -str reuse,readonly / readonly / noreuse: identical 98.8. Not a -str problem. Untried: different compiler build for this unit (lib uses GC/2.7), or sdata/sdata2 placement of the strings.
