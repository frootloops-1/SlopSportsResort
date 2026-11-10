# f() == 0 as an argument: store to int first for mr/cntlzw shape

- status: works
- tags: cntlzw,bool,arg
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig mr r0,r3; cntlzw r0,r0; ours cntlzw r3
cause: direct expression
fix: int r = f(); g(r == 0)
