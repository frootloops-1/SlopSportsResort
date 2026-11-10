// Ddg_805EC01C: Resort Frisbee Dog unit 0x805EC01C-0x805EC330 (Resort-only, no Wii Sports twin).
// layout 65210_fld_explain (ExplainLyt).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
void strncpy(u8*, u8*, s32, u8*, u8*);
extern u8 lbl_80689E70[];
extern u8 lbl_806EB2D8[];
void fn_802B73BC(s32);

void fn_805EC2AC() {}

u8* fn_805EC228(u8* p) {
    fn_80371668(p, 8, lbl_80689E70 + 0x72, lbl_80689E70 + 0x7f, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806EB2D8;
    *(u8**)(p + 0x18) = lbl_806EB2D8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EB2D8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EB2D8 + 0x88;
    strncpy(p + 0x34, lbl_80689E70 + 0x91, 32, lbl_806EB2D8 + 0x78, lbl_806EB2D8);
    return p;
}

void fn_805EC01C() { fn_802B73BC(123); }

}  // extern "C"
