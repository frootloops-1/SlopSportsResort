# pool_data off sends float literals to @floatBase0 at the end of .sdata2

- status: works
- tags: sdata2,pool,literal,inline-deferred
- scope: Pack/RPUtility/RPUtlLytBase
- source: claude-opus

symptom: float literals pooled as one @floatBase0 after all conversion doubles; retail interleaves them per function
cause: #pragma pool_data off groups float literals into a single @floatBase pool
fix: drop pool_data off; each literal then gets its own @N in function emission order (explicit const data still precedes all function pools)
