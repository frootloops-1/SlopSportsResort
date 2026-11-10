# Weak data/functions are emitted right after first user

- status: works
- tags: data,weak,strings,order
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene

symptom: @STRING@ assert strings of inlined header functions (changeNameToIdRP, Frustum::SetCanvasMode) in .data after the vtable came out in the wrong order
cause: weak @STRING@ objects come out in reverse order of the owning inline's parse position; a deduplicated weak vtable (__vt__11RPGrpScreen) leaves 0x14 zero bytes in the DOL
fix: define the Frustum/Screen local view (EGG_ASSERT under #line 'eggFrustum.h') before #include RPSndAudioMgr.h -> .data 99.8% (only the zeroed weak vtable differs)
