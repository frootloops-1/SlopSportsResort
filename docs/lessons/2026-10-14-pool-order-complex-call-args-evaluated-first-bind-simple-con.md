# Pool order: complex call args evaluated first; bind simple const arg to a local

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802a7a40
- source: fn_802A7CD8

symptom: const pooled after arg expression consts
cause: arg evaluation order
fix: float bs = 0.05f; before the call
