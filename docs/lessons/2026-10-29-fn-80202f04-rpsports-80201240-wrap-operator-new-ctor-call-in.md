# fn_80202F04 (RPSports_80201240): wrap operator new + ctor call in a static inline so the result gets a high vreg and is coloured before loop temps

- status: works
- tags: RPSports_80201240,regalloc,mwcc_dbg,inline
- scope: RPSports

symptom: 99.78%: a is r28, target r29
cause: As a named local a was vreg r40, coloured after loop temps r45/r47 which already held r28, so it took the lowest used free reg r28. As the result of an inline new+ctor helper it becomes vreg r48, coloured earlier, gets r29.
fix: static inline SpAnmLytSelf* NewSpAnmLyt(const SpAnmLytInit*){ p=(T*)::operator new(0x44); if(p!=NULL) p=fn_801F17D4(p,init); return p;} used for both a and b. Invented helper, plausibly the real new-expression; worker added no marker -> orchestrator should decide on MATCH-PENDING/ledger. Commit e54128775 on claude/s2f04-1029.
