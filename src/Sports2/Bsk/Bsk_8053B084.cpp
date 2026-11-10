// Resort Basketball (bsk) file 0x8053B084-0x8053B1E8: layout 65405_bsk_perfect, vtable 0x806E2878.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
extern u8 lbl_806848B8[];
extern u8 lbl_806E2878[];

u8* fn_8053B0FC(u8* p) {
    fn_80371668(p, 2, lbl_806848B8 + 0xb, lbl_806848B8 + 0x18, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806E2878;
    *(u8**)(p + 0x18) = lbl_806E2878 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E2878 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E2878 + 0x88;
    return p;
}

}  // extern "C"
