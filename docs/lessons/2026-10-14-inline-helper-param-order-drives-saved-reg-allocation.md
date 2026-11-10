# Inline helper param order drives saved-reg allocation

- status: works
- tags: regalloc,inline
- scope: RPGol_802b08a0
- source: fn_802B0DD0

symptom: r30/r31 swap between two live objects
cause: evaluation/param order
fix: golSet3(u16 base, Obj* o, float f) called as golSet3(golBase(), o, f)
