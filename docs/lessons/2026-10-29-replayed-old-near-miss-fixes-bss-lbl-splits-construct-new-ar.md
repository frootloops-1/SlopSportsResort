# Replayed old near-miss fixes: bss lbl_ splits + __construct_new_array; case-4 replaces default

- status: works
- tags: bss-split,array-new,switch
- scope: RPBsb_8025a3e8

symptom: RPBsb_8025a3e8 fn_8025A80C/8025B2C0/8025DC58/8025DF10 99.6-99.9: one big bss lbl_ hides per-global symbols; fn_8025A428 new Vec3[500] names EGG ctor/dtor
cause: symbols.txt had 0x6C/0x12C lumped bss lbl_; array-new of unit-local ctor needs explicit __construct_new_array(__nwa__FUl, fn_8025A4D0, VEC3 dtor)
fix: split bss lbl_804A6F24/6F9C into 0xC globals (symbols.txt) and call __construct_new_array directly; fn_802FE090 closes by replacing default: with case 4: break; fn_80231C54 with '== 4 || < 4' return
