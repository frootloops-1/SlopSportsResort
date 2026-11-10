// Resort Basketball (bsk) file 0x80547010-0x805479BC: class vtable 0x806E3058 and layout 65408_bsk_startAdvice, vtable 0x806E3078.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80270194(u8*, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
void fn_803715C0(u8*, s32, s32);
void fn_805121DC(u8*);
void fn_80547010(u8*);
extern u8 lbl_80684C38[];
extern u8 lbl_806E3058[];
extern u8 lbl_806E3078[];

u8* fn_805478D8(u8* p) {
    fn_803715C0(p, 3, 0);
    *(u8**)(p + 0x30) = lbl_806E3078;
    *(u8**)(p + 0x18) = lbl_806E3078 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E3078 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E3078 + 0x88;
    *(u8*)(p + 0x110) = 0;
    *(u8*)(p + 0x112) = 0;
    *(u8*)(p + 0x111) = 0;
    return p;
}

void fn_80547834(u8* p) {
    fn_802703A8(p + 0x94, lbl_80684C38, lbl_80684C38 + 0xd, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_80684C38 + 0x23, lbl_80684C38 + 0x26, 0);
    fn_8027035C(p + 0x94, 1, lbl_80684C38 + 0x31, lbl_80684C38 + 0x26, 0);
    fn_8027035C(p + 0x94, 2, lbl_80684C38 + 0x35, lbl_80684C38 + 0x26, 0);
    fn_80270194(p + 0x94, 0, 1);
}

u8* fn_80547610(u8* p) {
    fn_805121DC(p);
    *(u8**)(p) = lbl_806E3058;
    *(u32*)(p + 0x44) = 0;
    return p;
}

void fn_80547438(u8* p) { fn_80547010(p); }

}  // extern "C"
