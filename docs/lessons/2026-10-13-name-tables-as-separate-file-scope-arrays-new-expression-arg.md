# Name tables as separate file-scope arrays; new-expression arg order; resetEntries inline fixes loop reg swap

- status: works
- tags: pausemenu,data-table,new-expression,regalloc,restart
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: base+0xc pointer for table; loop counter vs base reg swap; new evaluates operator new before arg
cause: 2D array vs separate arrays; MWCC order
fix: separate arrays (unused first); store Func() result in local before placement new; move loop into inline member helper; RPSysLytAnmObj::restart() = reset+start
