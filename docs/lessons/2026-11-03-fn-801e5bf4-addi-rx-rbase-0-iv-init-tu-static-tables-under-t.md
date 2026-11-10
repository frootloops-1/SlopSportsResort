# fn_801E5BF4: addi rX,rBase,0 IV init = TU-static tables under the ...data.0 anchor (98.5 -> DOL match)

- status: works
- tags: data,anchor,static,pool_data,iv-init,801E51B4
- scope: Pack/RPSports/RPSportsCommon/RPSports_801E51B4
- source: decomp-hard 2026-11-03 sp801e5-1103

symptom: loop pointer init 'addi r29,r31,0x0' (retail) vs 'mr r29,r31'; one base reg r31 serves offsets 0/0xA0/0x11C, where 0x11C lies inside a different dtk symbol (lbl_803C2598+0x14)
cause: MWCC ...data.0 anchor addressing: >=3 TU-static .data objects referenced in one function are addressed as anchor+offset in the backend, so offset 0 is a real addi that IRO never sees. A base offset landing inside another dtk symbol is the tell
fix: split the tables into separate file-static arrays defined before the function (rows[40], pairs[6], 2598[5], panels[7]) and index them directly; no holder needed. Extern globals or 2 statics do not pool. objdiff residue is the reloc name (...data.0 vs lbl_) until symbols.txt is split; DOL 0, FLIP-OK. 40+ IV-init spellings (holder, casts, opaque zeros) were the wrong family
