// Swf_806530E4: Resort Swordplay unit 0x806530E4-0x806535A0 (Resort-only, no Wii Sports twin).
// layout 65011_swf_ringOut_caution.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_803715C0(u8*, s32, s32);
void fn_80653528(u8*, int);
extern u8 lbl_806EFE28[];

void fn_80653598(u8* p, int a) {
    fn_80653528(p - 0x94, a);
}

void fn_80653590(u8* p, int a) {
    fn_80653528(p - 0x18, a);
}

u8* fn_806534CC(u8* p) {
    fn_803715C0(p, 6, 0);
    *(u8**)(p + 0x30) = lbl_806EFE28;
    *(u8**)(p + 0x18) = lbl_806EFE28 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EFE28 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EFE28 + 0x88;
    return p;
}

void fn_806530F4(u8* p, s32 i) {
    p[i + 0x110] = 1;
}

void fn_806530E4(u8* p, s32 i) {
    p[i + 0x110] = 3;
}

}  // extern "C"
