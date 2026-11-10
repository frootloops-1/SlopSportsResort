// Resort Basketball (bsk) file 0x80542EA8-0x805433C0: layout 65407_bsk_NewRecord, vtable 0x806E2EF8.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_803715C0(u8*, s32, s32);
extern u8 lbl_806E2EF8[];

u8* fn_805432E0(u8* p) {
    fn_803715C0(p, 5, 0);
    *(u8**)(p + 0x30) = lbl_806E2EF8;
    *(u8**)(p + 0x18) = lbl_806E2EF8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E2EF8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E2EF8 + 0x88;
    *(u32*)(p + 0x114) = 0;
    *(u32*)(p + 0x110) = 0;
    return p;
}

}  // extern "C"
