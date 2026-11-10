# UpdatePinSetter: inline helper reverses stack-slot order of copy-constructed locals

- status: works
- tags: stack-slot,inline,UpdatePinSetter,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBowPinSetter
- source: batch 2026-11-01

symptom: 99.9%: 28 lines of stack offsets, raw/pos swapped (retail raw 0x2c, pos 0x38)
cause: outer-function locals take slots in reverse declaration order; inlined-function locals in declaration order, below outer locals
fix: move the pose block into static inline SetPose(PinPhysicsBody*) with declarations basisX, basisY, basisZ, raw, pos (R17 row 54). Dead: const VEC3& pos = VEC3(raw), VEC3 pos; pos = raw (94.4)
