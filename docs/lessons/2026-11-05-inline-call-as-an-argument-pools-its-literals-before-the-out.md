# Inline call as an argument pools its literals before the outer call's literal args

- status: works
- tags: sdata2,pool-order,inline,RPGol_802a7a40
- scope: Pack/RPSports/RPGolScene/RPGol_802a7a40
- source: claude/gol-7a40-1104

symptom: pow(0.05f, InvLerp(d,0,0.2f)) pooled 0.2 before 0.05 (retail: base first, divisor loaded first); bind-to-local fixed pool but hoisted the load
cause: an inline function call inside an argument list is expanded (hoisted) ahead of the enclosing call, so its literals pool first; plain expressions pool left-to-right. Tiny-file test: P(0.05f,(d-z)/0.2f) pools 0.05,0.2; with inline IL pools 0.2,0.05
fix: write the division inline with a zero local: float zero = 0.0f; fn(0.05f, (d - zero) / 0.2f). Copy-prop keeps the fsubs by 0.0 (literal - 0.0f folds it). Code unchanged, FLIP-OK. Test pool order in a tiny file with the unit's flags first (scratch tc.sh).
