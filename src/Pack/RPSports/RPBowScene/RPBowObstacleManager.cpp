// RPBowObstacleManager: Resort Bowling unit (Resort rewrite of ogws RPBowObstacleManager).
// Evidence: fn_804F9D20 is the ogws fn_80340308 box builder (same 2.329/0.408 extents,
// 12-triangle unit-cube table, now in .rodata), with a different manager layout.
// First pass: fn_ names are Resort addresses, struct offsets are raw. NonMatching.

#include <types.h>

struct BowObsVec {
    f32 x, y, z;
};

extern "C" {

void PSVECNormalize(const BowObsVec* in, BowObsVec* out);

void fn_804F9CE4() {
    BowObsVec v;
    v.x = -1.0f;
    v.y = 1.0f;
    v.z = -1.0f;
    PSVECNormalize(&v, &v);
}

}  // extern "C"
