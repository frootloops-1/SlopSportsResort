# RPSysLytMenuFrame data layout: local name array + sdata globals + literals, whole-file descending source order

- status: works
- tags: rodata,sdata,sdata2,string-pool,order,vtable
- scope: Pack/RPSports/RPSportsCommon/RPSysLytMenuFrame

symptom: .rodata 64/.data 0/.sdata 5/.sdata2 58 with code 100%; order_check differed at #4 but nm showed ~15 ascending groups out of order (order_check only prints the first diff)
cause: string pool/name table/vtable/sdata pointers were externs; source was in mixed order under reverse emission
fix: sort all defs into DESCENDING address order (reorder_fn moves 'X after prev' fed via xargs; zsh doesn't word-split $args). Literals at use sites; file-scope non-const char* globals keep lbl_ names (.sdata, pooled first); 18-entry anim table as a local const char* names[18] array (@N after the ctor's @N arrays, strings pooled at parse before function-body strings); local paneNames[2] -> one 8-byte sdata2 @N; vtable as void* lbl_[8]. symbols: string pool -> @stringBase0 local, table/sdata2 -> our @N local, delete split 2nd half lbl_804C1DBC. reorder_fn.py BUG: a prototype line directly above a moved function (no blank line) was carried to file end; fn_801D8B60 lost DONT_INLINE and got inlined into the ctor -> restore the prototype by hand
