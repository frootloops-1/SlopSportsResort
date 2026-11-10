# resort: EGG::Screen is 0x88; RPGrpView 0x1C is an owned RPGrpScreen*; RPGrpModelScene vtable has only the dtor

- status: works
- tags: resort,RPGrpView,EGG,Screen,layout
- scope: resort
- source: RP batch 4 (2026-11-09)

symptom: RPGrpView ctor allocates 0x88, Render3D calls ModelScene Draw/PreConditionForRenderingGX directly
cause: newer EGG + Resort RP rewrite
fix: eggScreen.h 0x88, eggDrawGX SetCameraMtx = PSMTXCopy, RPGrpModelScene non-virtual members, GetModelScene out of line; RPGrpViewRender3D 9/9; RPGrpView real file 0x80255050-0x8025611C (ScreenEffect::Draw parked 52%)
