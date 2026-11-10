# Table row: index the base BEFORE the field offset to colour the table base first

- status: works
- tags: regalloc,table,row-address,association,RPBow_80319C98
- source: RPBow_80319C98 round 3

symptom: tbl->arr[i] lerp: table base and [i] row GPRs swapped (retail tbl r3 row r4); holders, named row/ofs locals, refs, nested-inline params all flat (named row/ofs get copy-propagated into temps)
cause: MWCC associates tbl->arr[i] as (tbl+off)+i*sz; retail formed (tbl+i*sz) and folded off into the load displacement, which changes temp creation/colour order
fix: R17 helper: static inline T* Row(int k){ return (T*)((Elem*)lbl->p4 + k); } read Row(i)->arr[0], no named tbl local. fn_8031B3F4 99.7->100 (ledger 263); fn_8031A0E0 f32 tables same (ledger 264, vc moved before the B stores)
