# Unreferenced static fn returning a literal last in source pins .sdata2 pool order

- status: works
- tags: sdata2,pool,deferred,RPSysPauseMgr
- scope: RPSysPauseMgr
- source: opus

symptom: .sdata2 50%: float pool order wrong (0.0f must precede later users)
cause: pool entries follow codegen order = reverse source order under -inline deferred
fix: append 'static f32 unusedZero(){return 0.0f;}' as last function; also: s32 ch = u8 getter gives clrlwi; two separate early returns not ||; __dt(p,1) is delete of non-virtual dtor; hand-write CreateInstance when no DestroyInstance
