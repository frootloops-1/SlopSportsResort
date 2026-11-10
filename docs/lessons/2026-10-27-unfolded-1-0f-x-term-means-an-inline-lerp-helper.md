# Unfolded 1.0f*x term means an inline lerp helper

- status: works
- tags: fpr,inline,helper
- scope: RPUtlDohGraphSun
- source: claude/rputl-doh-1027

symptom: retail keeps fmuls/fmadds by 1.0 that open-coded 1.0f*x folds away
cause: MWCC folds literal 1.0f*x at parse time but not after inlining
fix: inline f32 lerp(a,b,t){return a*(1.0f-t)+b*t;} at each blend site
