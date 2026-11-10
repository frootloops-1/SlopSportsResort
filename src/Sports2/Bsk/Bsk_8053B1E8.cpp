// Resort Basketball (bsk) file 0x8053B1E8-0x8053CD88: layout 60540_bsk_resultScore, vtable 0x806E29B0.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_Vec3 {
    f32 x, y, z;
};


void fn_8053C774(u8* p, const Unk_Vec3* a1) { *(Unk_Vec3*)((u8*)p + 0x2c) = *a1; }

}  // extern "C"
