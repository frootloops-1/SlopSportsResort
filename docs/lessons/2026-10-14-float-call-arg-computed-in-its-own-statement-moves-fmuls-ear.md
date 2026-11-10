# Float call arg computed in its own statement moves fmuls earlier in prologue

- status: works
- tags: scheduling
- scope: RPGol_802a7a40
- source: fn_802A7A64

symptom: fmr/stw vs fmuls prologue order
cause: arg evaluation position
fix: float rad = k*ang; before the call
