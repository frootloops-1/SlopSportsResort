# 801f1d4c dead ends: RPGrpModel virtual-call view, member CreateData, 2D table, i at top

- status: fails
- tags: 801f1d4c,regalloc,decomp-hard
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: ctor-20261031

symptom: residual colour diffs in the new ctors (mgr r21/r24 vs r27/r25; 44C4 i r23 vs r31)
cause: unknown; register priority
fix: failed: SpGrpModelV virtual ReplaceTexture (vptr at 0x44) for 3D5C 98.4->97.0; RPGrpModelResManager::spCurrent->CreateData() loads spCurrent after GetFile (98.4->96.7); unnamed mgr in 2430 (99.9->97.9); 44C4: int i at top 95.8, lbl_803C29B0[i+6] 88.7, [3][3] table 89.2; 4A98 calling fn_801F4C88 is not auto-inlined, an inline SpStateCalc copy drops 4C88 to 98.8
