# TU sdata2 with shared consts used only by other TUs: define all as named globals

- status: works
- tags: sdata2,pool-order
- scope: RPGol_802b08a0
- source: RPGol_802b08a0

symptom: shared consts land after pool literals
cause: MWCC emits defined globals before pool literals
fix: define every constant as extern const float lbl_X = v; in address order (8-byte slot = float[2])
