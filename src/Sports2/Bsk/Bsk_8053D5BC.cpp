// Resort Basketball (bsk) file 0x8053D5BC-0x8053D760: layout 65406_bsk_foulText, vtable 0x806E2AF0.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
extern u8 lbl_80684B50[];
extern u8 lbl_806E2AF0[];

u8* fn_8053D668(u8* p) {
    fn_80371668(p, 2, lbl_80684B50 + 0x17, lbl_80684B50 + 0x24, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806E2AF0;
    *(u8**)(p + 0x18) = lbl_806E2AF0 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E2AF0 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E2AF0 + 0x88;
    *(u32*)(p + 0x114) = 0;
    *(u32*)(p + 0x110) = 0;
    return p;
}

}  // extern "C"
