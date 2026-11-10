# 8x unrolled member-array build with signed trip count = real ctor

- status: works
- tags: ctor,loop
- scope: RPTnsScene
- source: claude/rptns-3

symptom: fn_8024668C 34% as hand loop
cause: compiler-built member array construction in a ctor
fix: write real ctor (do-while with new T(i)); rename fn_ to __ct__ in symbols.txt and update extern users
