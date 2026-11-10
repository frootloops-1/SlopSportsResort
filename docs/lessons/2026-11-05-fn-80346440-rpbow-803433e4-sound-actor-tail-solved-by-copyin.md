# fn_80346440 (RPBow_803433E4) sound-actor tail solved by copying RPBow_80335DB0 class block

- status: works
- tags: ctor,sound-actor,li-r0,RPBow_803433E4
- scope: RPBow_803433E4

symptom: inlined BowPinSndActor ctor: li r4,8 vs li r0,8, stw 0x44 after addi vt+0x24
cause: hand struct model (BowSnd6C) lacks the compiler-generated intermediate vptr stores
fix: copy the RPBow_80335DB0 local class block (EGG::Disposer..BowPinSndActor, out-of-line virtuals, hand __construct_array) and write new BowPinSndActor; 97.1->100, no weak syms
