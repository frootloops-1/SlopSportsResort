# Static member declared in header but never defined: define it in the .cpp

- status: works
- tags: static,member,bss,sbss,definition,symbols,naming
- scope: RPGrpModelImplement
- source: coordinator, verified 2026-10-12

symptom: .bss/.sbss 0% and ExecCallback fns 99.5%; our .o has U (undefined) for sJointWorldMtx
cause: Source never defined the static members, so no storage/section content in our object
fix: Add s8 RPGrpModelG3D::sJointWorldMtxInitialized; MTX34 RPGrpModelG3D::sJointWorldMtx; and rename lbl_/fn_ placeholders in symbols.txt to the mangled names (50/53 exact). Check nm for U symbols when a worker reports only 'symbol names differ'
