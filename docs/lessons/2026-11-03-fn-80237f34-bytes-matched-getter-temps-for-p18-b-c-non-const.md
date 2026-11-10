# fn_80237F34 bytes-matched: getter temps for p18/b/c, non-const root, function-level pp, j/n/i order

- status: works
- tags: colour order,regalloc,getter,strength reduction,RPTns,MATCH-PENDING
- scope: Pack/RPSports/RPTnsScene/RPTns_8023758c

symptom: p18/ent-pointer and i/pp register swaps (84 lines); all 13 big nodes in sweep 2 so colour order = descending vreg
cause: the strength-reduced loop pointer is an IRO @ temp (numbered above every named local), so named p18/b/c could never colour before it; inline-return temps are created earlier and number above it
fix: static inline getters TnsGetP18/B/C (MATCH-PENDING R17, ledger 117) -> 54; root non-const (global-copy @ temp, colours after the ent pointer) + function-level TnsPair* pp declared before int j,n,i (i last) -> 100. Getter for pp (inline temp) colours too early (48); TnsGetEnt inline, unsigned long x, j += 1 were unnecessary
