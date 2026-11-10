// Ddg_805EF944: Resort Frisbee Dog unit 0x805EF944-0x805EFC74 (Resort-only, no Wii Sports twin).
// layout 65211_fld_release_attention (ReleaseAdviceLyt).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
void strncpy(u8*, u8*, s32, u8*, u8*);
extern u8 lbl_8068A010[];
extern u8 lbl_806EB5C0[];

void fn_805EFBF0() {}

u8* fn_805EFB6C(u8* p) {
    fn_80371668(p, 4, lbl_8068A010 + 0x41, lbl_8068A010 + 0x4e, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806EB5C0;
    *(u8**)(p + 0x18) = lbl_806EB5C0 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EB5C0 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EB5C0 + 0x88;
    strncpy(p + 0x34, lbl_8068A010 + 0x6a, 32, lbl_806EB5C0 + 0x78, lbl_806EB5C0);
    return p;
}

void fn_805EF944() {}

}  // extern "C"
