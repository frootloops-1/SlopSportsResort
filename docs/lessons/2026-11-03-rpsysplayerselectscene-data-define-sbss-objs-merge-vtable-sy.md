# RPSysPlayerSelectScene data: define sbss objs, merge vtable symbol, descending fn order, gpu guard

- status: works
- tags: sbss,data,vtable,emission-order,RPSysPlayerSelectScene,symbols
- scope: Pack/RPSports

symptom: .data 75%, .sbss 0% (all extern), .sdata2 80%; flip_gate dol_diff 7970 bytes with 20 fns shifted
cause: sbss lbl_804BF6F0/6F8/700 were extern though the split owns them; vtable 0x60 was split in symbols.txt as 0x28+lbl_803C2000 0x38; cm2hw leaked from g3d_gpu.h; function source order was not fully descending (helpers block and UserDraw/Calculate order, dtor at end) so emission order differed
fix: define s32 lbl[2]/Unk700* lbl[2] at file scope (8-byte sbss objs, use [0]); symbols.txt vtable size 0x60 and delete lbl_803C2000; #define NW4R_G3D_PLATFORM_GPU_H before includes; order source strictly by descending address (dtor right after fn_801D57A0). Leftover weak header .data strings/RPGrpScreen vtable and weak .sdata policyTable are deduped at link (guarding g3d_anmobj breaks g3d headers). Result: sections 100%, DOL diff 18 bytes (Calculate only)
