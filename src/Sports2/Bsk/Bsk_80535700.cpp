// Resort Basketball (bsk) file 0x80535700-0x80535D2C: layout 65404_bsk_Time, vtable 0x806E1E38.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_803715C0(u8*, s32, s32);
extern u8 lbl_806E1E38[];

u8* fn_80535C4C(u8* p) {
    fn_803715C0(p, 3, 0);
    *(u8**)(p + 0x30) = lbl_806E1E38;
    *(u8**)(p + 0x18) = lbl_806E1E38 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E1E38 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E1E38 + 0x88;
    *(u8*)(p + 0x120) = 0;
    *(u8*)(p + 0x121) = 0;
    return p;
}

void fn_80535958(u8* p) { *(u8*)(p + 0x110) = 1; }

void fn_8053594C(u8* p) { *(u8*)(p + 0x110) = 0; }

}  // extern "C"
