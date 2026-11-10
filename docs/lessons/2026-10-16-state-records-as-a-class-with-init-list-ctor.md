# state records as a class with init-list ctor

- status: works
- tags: ctor,ptmf,state,rpbsb
- source: RPBsb_8027039c 2026-10-16

symptom: state default-init phase (vptr, obj, 2 null PMFs) not reproduced
cause: states are real C++ objects
fix: State() : vtbl(lbl_803C6570), obj(0), a(0), b(0) {} gives lwzu __ptmf_null copies; separate members st0..st5 (array -> __construct_array 24%). fn_80272D70 0 -> 70.6; port to fn_8026FF28/fn_80281424/fn_80285398
