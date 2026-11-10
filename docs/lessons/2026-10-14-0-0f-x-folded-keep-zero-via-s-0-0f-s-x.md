# 0.0f + x folded: keep zero via s = 0.0f; s += x

- status: works
- tags: float,fold,fadds
- scope: RPTns_80224cf8
- source: sonnet worker 2026-10-14

symptom: orig has lfs zero + fadds; 0.0f + x is folded away
cause: MWCC folds literal 0 addition
fix: f32 s = 0.0f; s += x; (fn_80224E7C)
