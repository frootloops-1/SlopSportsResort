# MWCC folds 1.0f * x for a direct literal but not through an inline parameter

- status: works
- tags: sdata2,pool,fold,inline
- scope: Pack/RPUtility/RPUtlLytBase/fn_801C3574
- source: claude-opus

symptom: retail keeps fmuls by 1.0 (pool entry); source with 1.0f literal loses the multiply and the pool entry shifts
cause: parse-time folding of literal 1.0f * x; post-inline constant propagation does not simplify
fix: pass 1.0f through a small inline (MATCH-PENDING marker if invented); extern named const also keeps it but pools before all function literals
