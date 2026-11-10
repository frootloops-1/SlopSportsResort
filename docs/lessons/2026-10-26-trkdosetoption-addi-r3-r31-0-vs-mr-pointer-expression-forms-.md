# TRKDoSetOption addi r3,r31,0 vs mr: pointer-expression forms do not reach it

- status: fails
- tags: TRK,msghndlr,addi,mr,pool
- scope: MetroTRK/debugger/Portable/msghndlr

symptom: first usr_puts_serial arg is addi r3,r31,0x0 in target, we emit mr r3,r31 (98.8%)
cause: base+0 string-pool address; (const char*)strs+0, &strs->option[0], (char*)&strs->option, direct global sSetOptionStrings.option all fold to mr or regress; inline literals give lis/addi per string (80%)
fix: none found; parked. Likely original used separate pooled literals in a way not reproduced
