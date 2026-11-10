# RPGolMapObjBall 97934: explicit GXColor ABI copy closes stack slots (R17)

- status: works
- tags: GXColor,ABI,stack,R17,RPGolMapObjBall
- scope: fn_80297934
- source: codex-golball-1105

symptom: All 51 instructions otherwise identical, but two implicit outgoing by-value color copies produce 0x50 frame; retail reuses one slot and has 0x40 frame.
cause: Native GXColor by-value calls allocate distinct parse-time temporary slots; exact original source boundary remains unknown.
fix: R17 row 215: declare existing mangled DrawCornY symbol using physical (Circle,const MTX34*,const GXColor*) ABI; explicitly copy color through u32 into one outgoing local before each call. 204/204 actual linked DOL bytes match at original 0x80297934, no regressions; configured DOL0, three known collisions. Reference, Color, wrappers, loop, const-param, lifetimes, memcpy and union probes failed. Original C++ pending, whole unit NonMatching.
