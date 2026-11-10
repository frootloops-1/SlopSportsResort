// Ddg_805EA20C: Resort Frisbee Dog unit 0x805EA20C-0x805EB33C (Resort-only, no Wii Sports twin).
// layout 60520_fldScore (ScoreLyt).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_8027CB94(u8*);
void fn_805EA2FC(u8*);

void fn_805EAC90() {}

void fn_805EA2F8(u8* p) { fn_805EA2FC(p); }

void fn_805EA268(u8* p, s32 i, s32 j, u32 a, u32 b) {
    u8* q = p + i * 0x54 + j * 4;
    *(u32*)(q + 0x110) = a;
    *(u32*)(q + 0x138) = b;
}

void fn_805EA258(u8* p, s32 a1, u32 a2) { *(u32*)(p + a1 * 8 + 0x264) = a2; }

}  // extern "C"
