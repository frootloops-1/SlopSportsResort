# RPSportsKokeshiLyt closed: inline lookup results and state frame parameter plus indexed IVs

- status: works
- tags: RPSportsKokeshiLyt,regalloc,inline,GPR,MATCH-PENDING
- scope: Pack/RPSports/RPSportsCommon/RPSportsKokeshiLyt

symptom: F808 99.3: text/shadow colour after IVs; EFCC 99.5: frame/count/replay/IV roles rotated.
cause: Named variables and inline/strength-reduced temporaries enter different allocator levels; late short values reuse the lowest already-used free saved register.
fix: F808 wrap both record findTextBox calls in an invented inline return helper. EFCC extract state machine with frame parameter and bool/row/i references to caller locals; inline count getter; declare scoreOffset before replay; use order[i] before row=base+i*0x38; named effectRow inside replay. 8/8 functions, all sections 100, Matching DOL 0 bytes; R17 ledger 126/127.
