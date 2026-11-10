# Real ctor of a class whose base/member has a non-trivial dtor gives offset IVs; hand vtable arrays can keep __vt__ names

- status: works
- tags: 801f1d4c,ctor,vtable,induction,class-model,decomp-hard
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: ctor-20261031

symptom: ctor-shaped free fns (fn_801F2430/2FB4/3D5C/44C4) used pointer IVs (mr rX,self; addi +0x140) where target uses offset IVs (add r0,i*K,j*K; add rN,r0,this); volatile hack for the base vtable store
cause: MWCC uses offset IVs in a ctor only when a base or member subobject has a non-trivial dtor (scratch tests: virtual ~Base(){} or member with virtual dtor -> offset; plain/virtual-only/own dtor -> pointer)
fix: Model SpStateLink{virtual ~} member at 0x20, SpStateBase (vptr at 0x28 after members), SpMdlSetBase/SpMdlScrBase mids; virtuals declared, never defined, so no compiler vtable is emitted; keep hand arrays renamed void* __vt__11SpStateBase[]={...} and rename the lbl_/fn_ symbols to __vt__/__ct__ names in symbols.txt. 2430 95.1->99.9, 3D5C 92.3->98.4, 44C4 92.9->96.3, 63CC 99.8->100
