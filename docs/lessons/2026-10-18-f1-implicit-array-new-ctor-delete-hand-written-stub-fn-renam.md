# F1 implicit array-new ctor: delete hand-written stub fn, rename target symbol to mangled __ct__

- status: works
- tags: F1,ctor
- scope: RPUtl_801C0D90
- source: claude/nm-data

symptom: 4-byte blr fn between caller and next fn, ours calls mangled __ct__ of unnamed-namespace struct
cause: compiler-generated Record ctor from new Record[count]
fix: remove stub, rename target to __ct__Q228@unnamed@RPUtl_801C0D90_cpp@6RecordFv
