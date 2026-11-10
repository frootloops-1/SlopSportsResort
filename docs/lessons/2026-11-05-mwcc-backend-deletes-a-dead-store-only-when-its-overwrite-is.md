# MWCC backend deletes a dead store only when its overwrite is adjacent

- status: fails
- tags: block-split,pcode,dead-store,rpgol,aa614
- scope: RPGol_802aa614 fn_802AA714
- source: gol-aa614-1105

symptom: need 2-5 vanishing initial pcode lines between two statements to move a block split
cause: dead store then overwrite separated by other stores (stack temp init or other globals) survives to final code; only an immediately-following overwrite (vt; vt) is removed
fix: dead byte store before c0 (81.7, li/stb stay) and duplicate name[0] store (73.3, first stw stays) both give the right split but leave code; use adjacent pairs only
