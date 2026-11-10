# resort: RPGrpModel vtable 0xB8 and Resort Texture/Material/ResManager layouts

- status: works
- tags: resort,RPGrpModel,vtable,layout
- scope: resort
- source: RP batch 5 (2026-11-09)

symptom: kokeshi and model functions miss on vtable slot offsets and member offsets
cause: Resort: ReplaceTexture 0x28, SetCallback 0x2C, GetMaterialIndex 0x68, dtor 0x94; GetViewMtx/GetJointNum/... non-virtual; RPGrpTexture no vtable sizeof 0x34; RPGrpModelMaterial 0xB8 vptr 0xB4; ResManager::Resource s16 mParent 0xE, CreateData 4 args
fix: RPGrp model headers carry Resort layouts with evidence; RPSysKokeshiManager 19/21
