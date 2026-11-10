# fn_80338760 FPR/stack wall: one-expression VEC3 sum via inline getter + named f32 for the global load

- status: works
- tags: fpr,colouring,vec3,inline-helper,named-local,RPBow_803381DC
- scope: Pack/RPSports/RPBowScene/RPBow_803381DC

symptom: stack temps of a VEC3 sum in wrong slots and f2-f7 rotated around fneg/lfs
cause: named offset/pos split changed temp creation order; VEC3(f..) ctor and the global load f110 numbered as temps above the operator- @vars
fix: pos = BowThrowTrans(self) + -out.normal * (rad - out.depth) with f32 rad = gBowlingPhysicsData.f110 declared just before: 72 -> 6 diff lines (R17 ledger 238)
