# #pragma dont_inline on also blocks inlining inside fns defined under it

- status: works
- tags: inline,pragma
- scope: RPGol_802aaf88
- source: fn_802AB198

symptom: wanted inline helper emitted as call
cause: dont_inline affects the caller's region
fix: define static inline helper and its callers under dont_inline reset; keep only protected callees under on
