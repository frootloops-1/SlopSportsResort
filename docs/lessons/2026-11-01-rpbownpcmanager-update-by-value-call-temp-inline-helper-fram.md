# RPBowNpcManager Update: by-value call temp, inline helper frame slot, namespace-mangled f32 externs

- status: works
- tags: frame-layout,by-value,namespace,reorder,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBowNpcManager
- source: batch 2026-11-01

symptom: 99.7%: pin pointer r3 vs r7 in BACK loops, frame order, reloc name lbl_X__7Bowling, .sdata2 order, stray cm2hw
cause: pin pointer should be a compiler temp from a by-value struct-returning call; inline-function locals are appended to the frame at deferred-inline time; extern const f32 inside namespace Bowling mangles; pool order follows emission order
fix: by-value extern C view of fn_80324994 (R17 row 55), SetFullRack inline (row 56), literals 9999.0f/-999.0f instead of namespaced externs, reorder_fn, NW4R_G3D_PLATFORM_GPU_H predefine. Dead: PinStatus x = f() / x = f() (temp + copy, frame 0x230->0x260). InitAudioActors (99.5) still blocked by the template-vtable cross-unit issue
