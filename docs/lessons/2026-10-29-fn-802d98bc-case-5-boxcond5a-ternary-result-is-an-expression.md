# fn_802D98BC: case 5 BoxCond5a ternary result is an expression temp coloured before the @inline chain vars

- status: open
- tags: RPBox_802cf93c,regalloc,mwcc_dbg
- scope: RPBox

symptom: 58 lines: 5a result r27 vs target r23, rest of chain shifted; case 2/4 BOOL r27 vs r28; FPR f1/f2/f3 in the u32->float compare
cause: mwcc_dbg: 5a '(...)?TRUE:FALSE' gives temp r80 (no @var) while 5b..5h are @inline vars r49..r55; target colours 5a last
fix: failed: plain && in 5a (zeros CSEd into mr copies, 154 lines), if-form with named r (426 lines), BOOL r = ternary; return r (same 58). Untried: other 5a spellings that keep li 0/li 1 per var
