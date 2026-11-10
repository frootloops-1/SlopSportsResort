// Swf_8064CC58: Resort Swordplay unit 0x8064CC58-0x8064CF28 (Resort-only, no Wii Sports twin).
// layout 65023_swf_kumite_achieve.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_803715C0(u8*, s32, s32);
void fn_8064CEB0(u8*, int);
extern u8 lbl_806EEE68[];

void fn_8064CF20(u8* p, int a) {
    fn_8064CEB0(p - 0x94, a);
}

void fn_8064CF18(u8* p, int a) {
    fn_8064CEB0(p - 0x18, a);
}

u8* fn_8064CE4C(u8* p) {
    fn_803715C0(p, 2, 0);
    *(u8**)(p + 0x30) = lbl_806EEE68;
    *(u8**)(p + 0x18) = lbl_806EEE68 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EEE68 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EEE68 + 0x88;
    *(s32*)(p + 0x110) = 25;
    return p;
}

}  // extern "C"
