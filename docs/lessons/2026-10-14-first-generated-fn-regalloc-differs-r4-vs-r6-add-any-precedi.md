# First-generated fn regalloc differs (r4 vs r6): add any preceding static fn

- status: works
- tags: regalloc
- scope: RPGol_802b8568
- source: fn_802B8568

symptom: global ptr in wrong reg in TU's lowest fn
cause: a dead-stripped fn preceded it
fix: an unreferenced static fn placed last in source fixes it
