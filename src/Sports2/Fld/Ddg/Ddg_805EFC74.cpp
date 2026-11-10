// Ddg_805EFC74: Resort Frisbee Dog unit 0x805EFC74-0x805EFD7C (Resort-only, no Wii Sports twin).
// layout 65212_fld_BtnAdvicet (BbtnAdviceLyt).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
void strncpy(u8*, u8*, s32, u8*, u8*);
extern u8 lbl_8068A090[];
extern u8 lbl_806EB6E8[];

u8* fn_805EFC78(u8* p) {
    fn_80371668(p, 0, lbl_8068A090, lbl_8068A090 + 0xd, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806EB6E8;
    *(u8**)(p + 0x18) = lbl_806EB6E8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EB6E8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EB6E8 + 0x88;
    strncpy(p + 0x34, lbl_8068A090 + 0x22, 32, lbl_806EB6E8 + 0x78, lbl_806EB6E8);
    return p;
}

void fn_805EFC74() {}

}  // extern "C"
