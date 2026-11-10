# fn_801EA90C: string literals instead of an lbl_ string pool, LoadResData-style helper, u16 CreateData

- status: works
- tags: literals,helper,types,fn_801EA90C,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ea458
- source: wave3 2026-11-01

symptom: 92.9%: colouring and clrlwi r5/addi r6 order swap before GetPtr
cause: extern lbl_80387438 holding path+name strings is the TU's own string pool; the file's private RPGrpModelResManager copy had CreateData returning u32 where the real RPGrpHandle is u16
fix: literals 'G3D/logo_model.brres' / 'logo_model'; static inline SpLoadResData(pResMgr,type,handle,name) copied from matching RPSportsMenuBgModel.cpp; CreateData returns u16; lbl_803C2650 vtable defined, size 0x10->0xC; gap_12_804C1F6C_sdata2 deleted. No marker. Check copy-pasted local class decls in RPSportsCommon units against include/Pack/RPGraphics headers
