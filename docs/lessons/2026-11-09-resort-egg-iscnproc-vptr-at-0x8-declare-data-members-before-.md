# resort: EGG IScnProc vptr at 0x8: declare data members before the virtuals; ScnRenderer : ScnRootEx, IScnProc

- status: works
- tags: resort,EGG,layout,vtable,ScnRenderer
- source: rp-drawpathmanager-2 worker 2026-11-09

symptom: RPGrpDrawPathManager ctor 34.6%
cause: Resort's IScnProc stores mpDataSet@0, mNumScnProc@4, vtable@8; ScnRenderer builds IScnProc at 0xD4 (fn_801BB370)
fix: members above the virtual decls in eggIScnProc.h; ScnRenderer multiple inheritance, ScnRootEx padded to 0xD0 (see headers)
