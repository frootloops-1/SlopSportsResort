# fn_802CBE54 (RPBox_802cb9cc): assign rec.mode before rec.kind=0 in both arms

- status: works
- tags: rpbox,register,arm-order
- source: tb-cb9cc-20261031

symptom: arm of if/else had wrong GPR colouring of li 0 / cntlzw / table temps (97.0)
cause: store order changes vreg creation order of the zero constant vs the table-index temps
fix: rec.mode = tbl[...]; rec.kind = 0; in both arms -> 98.3. Open: cmpwi-before-stw 0x78 schedule and BoxToScreen temp slot swap (0x8/0x10)
