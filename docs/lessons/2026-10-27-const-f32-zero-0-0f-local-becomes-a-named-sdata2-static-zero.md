# const f32 zero = 0.0f local becomes a named sdata2 static (zero$N), shifting the pool

- status: works
- tags: mwcc,sdata2,pool,const-local,RPUtlCollisionChecker
- scope: Pack/RPUtility/RPUtlCollisionChecker

symptom: extra 4-byte sdata2 object zero$1512; objdiff still 100% but DOL relocation points elsewhere
cause: MWCC emits a const-qualified local float with constant initializer as a function-static object
fix: use the 0.0f literal (or a non-const local); RPUtlCollisionChecker fn_801BD230 stays 100% with literals
