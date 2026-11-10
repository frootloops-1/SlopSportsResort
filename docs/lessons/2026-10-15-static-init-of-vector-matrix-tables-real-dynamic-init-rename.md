# Static init of vector/matrix tables: real dynamic init, rename to __sinit

- status: works
- tags: sinit,ctors
- scope: RPTnsScene
- source: claude/rptns-3

symptom: hand-written fn_ initialiser forwards floats through FPRs; 75% match
cause: compiler sinit copies temps via lwz/stw only for POD-base vectors
fix: struct V : Base{f32 x,y,z;} with ctor; brace aggregate init of arrays; rename fn_ to __sinit_\RPTns_xxx_cpp scope:local in symbols.txt (RPTns_802479cc, 8024dc50)
