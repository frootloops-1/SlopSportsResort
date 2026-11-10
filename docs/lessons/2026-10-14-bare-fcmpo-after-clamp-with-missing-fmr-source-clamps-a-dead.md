# Bare fcmpo after clamp with missing fmr: source clamps a dead variable

- status: works
- tags: float,clamp
- scope: RPGol_802b7670
- source: fn_802B7770

symptom: fcmpo without move
cause: original bug clamps wrong var
fix: compute p, clamp v, pass p
