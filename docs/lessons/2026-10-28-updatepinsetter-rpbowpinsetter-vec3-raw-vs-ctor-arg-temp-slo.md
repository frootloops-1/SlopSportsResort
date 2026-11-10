# UpdatePinSetter (RPBowPinSetter): VEC3 raw vs ctor arg-temp slot order (retail raw ABOVE arg temps) not reachable by 13 source shapes

- status: fails
- tags: RPBowPinSetter,UpdatePinSetter,stack-layout,VEC3,temp-slots,inline-helper
- scope: RPBowPinSetter
- source: claude/pin-1028 sonnet

symptom: 28 diff lines, all stack offsets: retail basis 0x8-0x28, ctor arg temps 0x2c/0x30/0x34, raw 0x38/0x3c/0x40; ours raw 0x2c, arg temps 0x38
cause: named locals sit at the bottom in reverse declaration order, by-value arg temps above them (later temps lower), so a ctor-created VEC3 local lands BELOW its own arg temps; retail raw looks like a temp allocated before the ctor args
fix: failed: VEC3 pos = VEC3(x,8,z) / position=raw (94.6, memory round-trip folded away), const VEC3& raw = VEC3(...) (identical layout), raw = VEC3() assignment, raw outside loop (frame +0x10, 98.2), raw declared after basis (99.9, wrong layout), static inline SetPos/SetPose (99.9: right relative order but block lands below basis at 0x8-0x1c), SetBasis-only (worse), MakeVec returning VEC3 (94.6 or identical). Unbound VEC3 temporaries are scalar-replaced and lose the lwz/stw round trip: keep a named raw bound by the copy-ctor. Parked
