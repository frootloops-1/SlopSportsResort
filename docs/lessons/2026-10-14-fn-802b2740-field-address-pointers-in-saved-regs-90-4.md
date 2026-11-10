# fn_802B2740 field-address pointers in saved regs (90.4)

- status: open
- tags: regalloc
- scope: RPGol_802b1a0c
- source: fn_802B2740

symptom: orig holds self+0xB0..BC in r31..r28; ours d-form
cause: MWCC folds pointer locals to d-form
fix: dead ends: reference/pointer locals, FLD macro, [0] indexing, inline float& params; try permuter or volatile-free array-of-pointers
