# Handle/ring helpers as struct members, not static inlines

- status: works
- tags: regalloc,inline
- scope: RPTnsScene
- source: claude/rptns-3

symptom: fn_8021F8C4 93, BD48 73, C04C 96
cause: static inline vs member inline changes allocation
fix: write findSame/findFree/findLow and ring front()/next() as members
