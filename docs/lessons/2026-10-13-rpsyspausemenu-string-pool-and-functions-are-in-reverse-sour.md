# RPSysPauseMenu: string pool and functions are in reverse source order; loop with mEntries[i].field directly

- status: works
- tags: pausemenu,string-pool,reverse-order,regalloc
- scope: Pack/RPKernel/RPSysPauseMenu

symptom: string pool offset extra addi; Entry* e keeps extra register
cause: -str pool order follows reverse source order; pointer/ref locals keep base reg
fix: string offsets only match once higher-address fns exist; write mEntries[i].x; static inline PlayFromEnd(p){p->play(p->getFrameMax()-1.0f);} fixed regswap
