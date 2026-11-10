# Dead pool strings in an unused static const char* const array; string pool order follows deferred codegen (reverse source)

- status: works
- tags: rodata,string,pool,rpbsb,emission-order
- scope: RPBsb_8025a3e8

symptom: Hidden addend mismatch in fns using lbl_X+0xNN of a string pool; MWCC drops (void)"str", unused locals and Nop("str") calls so leading unreferenced strings cannot be pooled; unused static fn does pool but emits code
cause: Unreferenced strings at the pool head; also literals pool in codegen order which is reverse source order in this unit, so ascending source gives F468,E93C,B2C0 string order
fix: merge lbl_ strings to one @stringBase0 data:string_table size 0xB4; replace lbl+off with literals; file-scope 'static const char* const X[2]={...}' (dropped, no .data) pools leading strings (MATCH-PENDING R17); order functions descending in source (reorder_fn.py) so literals pool ascending. RPBsb_8025a3e8 rodata 100, fn_8025F468/E93C 100
