# sdata2 constant order: 1.0f before int-to-float double

- status: open
- tags: sdata2,constants,order
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene

symptom: orig .sdata2 = u16[2], 1.0f, double 0x4330.., 100000f, 0f; ours u16, pad, double, 1.0f, 100000f; costs one reloc each in 3A5C and Configure
cause: unknown: 1.0f is pooled before Calculate's conversion double; trailing 0f is also missing from RPSysBootScene built with real headers, so likely an original RPGrpScreen/Frustum header inline
fix: failed: file-scope static const f32 (propagated, not emitted); shared inline with literal skip flag (dead branch not pooled); MWCC does not fill alignment holes
