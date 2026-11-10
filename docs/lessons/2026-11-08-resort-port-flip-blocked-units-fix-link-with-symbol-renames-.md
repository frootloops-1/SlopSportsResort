# resort: port_flip blocked units - fix link with symbol renames and padded split ends

- status: works
- tags: resort,porting,splits,link,dtk
- scope: library porting
- source: lib-flip-batch2 2026-11-09

symptom: Scanned-exact ogws library unit fails after port_flip: 'undefined: lbl_X' at link, or dtk 'split ends within symbol' / 'Invalid alignment for split'
cause: Resort's generic symbols disagree with the object: other TUs reference the unit's globals/tables by lbl_ names; dtk split one object into two labels (sdata2 halfwords, sdp_cb+0xC44 from a false data pointer); split start missed the first function (EUARTInit); port_flip writes unpadded section ends
fix: Rename lbl_ to the object's global name (objdump -t); merge split labels to the object size; block_relocations for false pointers in config.yml; extend .text start to the missing named function; pad section ends to the next symbol. Gate each unit alone (dol_diff + sym_addr_check). Got mem_list, euart, bte_main, hidh_conn, sdp_main, bta_dm_act
