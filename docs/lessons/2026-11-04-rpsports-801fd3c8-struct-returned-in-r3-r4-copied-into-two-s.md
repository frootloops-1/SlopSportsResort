# RPSports_801fd3c8: struct returned in r3:r4 copied into two stack slots needs the VEC2 shape (POD base + empty ctor)

- status: works
- tags: struct-return,stack-slot,size-mismatch,inline,RPSports_801fd3c8
- scope: Pack/RPSports/RPSportsCommon/RPSports_801fd3c8
- source: claude/sp801fd-1104

symptom: fn_801FD3C8 4 insns short and frame 0x30 vs 0x40: retail stores fn_801D01F0's r3/r4 result twice (0x18 and 0x20) and passes &0x18; ours stored once
cause: retail pos type is nw4r::math::VEC2-like (derived from a POD base, user ctor): return temp + copy-construct into the named local; a plain POD struct is constructed in place, a POD with only a ctor copies via lfs/stfs
fix: struct CurPos : CurPosBase { CurPos() {} }; plus the 80205c74 shape: inline RPSndAudioMgr::startPointCursorSe(name, const CurPos&) called from static inline SpStartPaneCursorSe(name, button) with a 'CurPos pos = fn_801D01F0(...)' local
