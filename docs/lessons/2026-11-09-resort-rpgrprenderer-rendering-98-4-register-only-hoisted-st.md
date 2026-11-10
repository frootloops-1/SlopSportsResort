# resort: RPGrpRenderer Rendering 98.4 register-only (hoisted state consts 1/2 take r30/r31)

- status: fails
- tags: resort,regalloc,RPGrpRenderer
- scope: resort
- source: rp9-renderer

symptom: every register shifted by two in Rendering
cause: hoisted constants 1/2 allocated r30/r31 instead of r22/r23
fix: failed: state as inline param vs direct store, capture outside loop, inline capture helper, if-block vs continue
