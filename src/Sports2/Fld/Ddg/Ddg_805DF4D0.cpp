// Ddg_805DF4D0: Resort Frisbee Dog unit 0x805DF4D0-0x805E48DC (Resort-only, no Wii Sports twin).
// dog AI state handlers (pointed to by the state table 0x806E8A98).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {



void fn_805E3840(u8* p) {
    *(u32*)(p + 0x2cc) = 0;
    *(u32*)(p + 0x188) = 2;
}

void fn_805E3680() {}

void fn_805E3520() {}

void fn_805E29CC() {}

u32 fn_805E1E60(u8* p) { return *(u32*)(p + 0x8); }

void fn_805E0D14() {}

void fn_805E0AE8(u8* p) {
    *(u8*)(p + 0x1a8) = 1;
    *(u32*)(p + 0x188) = 5;
}

u32 fn_805E084C(u8* p) { return *(u32*)(p + 0x4); }

u32 fn_805E0844(u8* p) { return *(u32*)(p + 0x8); }

f32 fn_805E0838(u8* p) { return *(f32*)(*(u8**)(p)); }

}  // extern "C"
