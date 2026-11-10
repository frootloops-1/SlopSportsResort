// Resort Basketball (bsk) file 0x80531C40-0x80531ED8: class vtable 0x806E1908 (ctor 0x80531E90).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_Vec2 {
    f32 x, y;
};


void fn_80531E3C() {}

void fn_80531E28(u8* p, const Unk_Vec2* a1) { *(Unk_Vec2*)((u8*)p + 0x94) = *a1; }

}  // extern "C"
