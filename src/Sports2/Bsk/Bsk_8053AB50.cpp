// Resort Basketball (bsk) file 0x8053AB50-0x8053B084: layout 65430_bsk_explain, vtable 0x806E2758.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
extern u8 lbl_80684718[];
extern u8 lbl_806E2758[];

u8* fn_8053AF88(u8* p) {
    fn_80371668(p, 10, lbl_80684718 + 0x17e, lbl_80684718 + 0x18b, 1, 0, 0);
    *(u8**)(p + 0x18) = lbl_806E2758 + 0x8;
    *(u8**)(p + 0x30) = lbl_806E2758;
    *(u8**)(p + 0x94) = lbl_806E2758 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E2758 + 0x88;
    *(u32*)(p + 0x110) = 6;
    *(u32*)(p + 0x114) = 1;
    return p;
}

void fn_8053AB64(u8* p, u32 a1) { *(u32*)(p + 0x110) = a1; }

}  // extern "C"
