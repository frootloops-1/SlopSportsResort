# fn_802CF94C: volatile read into a function-level idx local (declared before p) fixes owner/w3D4/p colour order

- status: works
- tags: fn_802CF94C,RPBox_802cf93c,volatile,regalloc,colour-order
- scope: mwcc GC/3.0a5.2
- source: docs/marker-ledger.md row 142

symptom: case 8 target: owner r5, w3D4 r6, p(&pl+0xe8) r7; ours owner r6, w3D4 r5 (w3D4 is a codegen temp r107 coloured before the owner IRO temp r51)
cause: colouring is descending vreg number; codegen temps colour before IRO temps and named locals. A single-use named local is forward-substituted so it stays a codegen temp
fix: s32 idx declared at function level BEFORE BoxObj** p; idx = *(volatile s32*)&self->owner->w3D4; p += idx;. Volatile makes idx a real named-local vreg (low number) so owner colours first. Declaring idx after p gives idx r7/p r6 (8 lines); non-volatile named idx (even assigned twice) is forwarded and changes nothing
