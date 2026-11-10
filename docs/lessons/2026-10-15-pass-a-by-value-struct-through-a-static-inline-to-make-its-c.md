# Pass a by-value struct through a static inline to make its copy temp take the lowest slot

- status: works
- tags: stack,temporary,by-value,inline,slot-order,ResAnmScn,RPGraphics
- scope: MWCC stack-slot ordering
- source: RPGrpProjectionObject

symptom: Two calls take the same struct by value. The target puts the first call's copy temp at the lowest slot (0x8) and the second at 0xc, but plain calls give the reverse
cause: Inlined-function parameters/temps are allocated after the caller's temps, so they get the lowest address
fix: Use 'static inline void H(Cam& c, const ResAnmScn scn, const u8& v, const f32& f){c.Load(scn,v,f);}'. The const& params stop the mViewNo lbz / fmr frame from being hoisted above the copy store (by-value u8/f32 params scheduled them early and gave 91%). Re-ordering declarations, blocks, a named copy, a reference binding, or an assignment-in-arg had no effect. Matched LoadScnCamera__21RPGrpProjectionObjectFUsPCcf
