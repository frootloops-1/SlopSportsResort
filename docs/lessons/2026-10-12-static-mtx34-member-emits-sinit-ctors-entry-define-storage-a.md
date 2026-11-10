# Static MTX34 member emits __sinit/.ctors entry: define storage as POD _MTX34 and static_cast at use

- status: works
- tags: sinit,ctors,MTX34,static,POD,DOL,RPGrpModelImplement
- scope: RPGrpModelImplement
- source: coordinator 2026-10-12

symptom: Flipping object grows .ctors by 4 and the DOL by 32 bytes (dtk: Invalid virtual data range)
cause: nw4r::math::MTX34 has a constructor so a static MTX34 gets a static initializer; original has none
fix: static nw4r::math::_MTX34 member + #define JOINT_MTX() static_cast<MTX34*>(&x) at each use (a local pointer variable regressed ExecCallbackB to 95.5%)
