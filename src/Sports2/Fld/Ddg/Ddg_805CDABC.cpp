// Ddg_805CDABC: Resort Frisbee Dog unit 0x805CDABC-0x805CDF14 (Resort-only, no Wii Sports twin).
// layout 65201_diskSetBtn.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_801F5C64(u8*);
void fn_80270194(u8*, s32, s32);
void fn_802701C0(u8*, s32, u8*, s32, s32, s32, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
extern u8 lbl_80689530[];
void fn_802B73BC(s32);

void fn_805CDE78() {}

void fn_805CDDEC(u8* p, u32 a1) {
    *(u32*)(p + 0x100) = a1;
    fn_801F5C64(p);
}

void fn_805CDD0C(u8* p) {
    fn_802703A8(p + 0x94, lbl_80689530 + 0x9, lbl_80689530 + 0x16, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_80689530 + 0x27, lbl_80689530 + 0x2a, 0);
    fn_8027035C(p + 0x94, 1, lbl_80689530 + 0x35, lbl_80689530 + 0x3b, 0);
    fn_8027035C(p + 0x94, 2, lbl_80689530 + 0x44, lbl_80689530 + 0x3b, 0);
    fn_8027035C(p + 0x94, 3, lbl_80689530 + 0x4b, lbl_80689530 + 0x2a, 0);
    fn_802701C0(p + 0x94, 0, lbl_80689530, 1, 2, 0, 0, 1);
    fn_80270194(p + 0x94, 0, 3);
}

void fn_805CDD08() {}

void fn_805CDD00() { fn_802B73BC(95); }

}  // extern "C"
