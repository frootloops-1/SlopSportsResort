// Ddg_805CAE14: Resort Frisbee Dog unit 0x805CAE14-0x805CBDF0 (Resort-only, no Wii Sports twin).
// layout: P_FrameBase*, T_pts_*, balloon score icons, Mii faces (pool up to 65200_diskPointCount header).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_805CBD64() {}

void fn_805CB21C() {}

void fn_805CB030() {}

void fn_805CAFC4(u8* p, s32 i, u32 v) { *(u32*)(p + i * 0x58 + 0x184) += v; }

void fn_805CAFB4(u8* p, s32 i, u32 v) { *(u32*)(p + i * 0x58 + 0x184) = v; }

void fn_805CAE14(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 4 + 0x114) = a3;
    *(u32*)(p + a1 * 4 + 0x124) = a2;
}

}  // extern "C"
