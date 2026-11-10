# Header includes pull weak g3d policyTable into .sdata

- status: works
- tags: sdata,includes,g3d
- scope: mwcc
- source: RPTns_802390b0

symptom: unit gains .sdata @LOCAL@GetAnmPlayPolicy...policyTable not in target
cause: RPGrpModelManager.h / RPSysEffectBase.h / eggDrawGX.h pull g3d_anmobj.h
fix: declare mangled externs (GetLightManager__17RPGrpModelManagerCFUc, LoadTexture__Q23EGG6DrawGX...) and a local RPSysEffect view; include only nw4r/math.h, revolution/GX.h, OS.h, string.h
