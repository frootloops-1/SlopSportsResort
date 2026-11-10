# Unhoisted global load in loop: hoist pointer locals, increment order matters

- status: works
- tags: mwcc,loop,regalloc
- scope: RPGol_802bb608
- source: sonnet-worker

symptom: fn_802BC904 loop global load/pointer bump order differed
cause: pointer IV order follows for-increment order
fix: GolSing* g = global; before loop; pointer locals; order of pa++/pb++ in the increment decides bump order
