// Swf_806447D8: Resort Swordplay unit 0x806447D8-0x806451C0 (Resort-only, no Wii Sports twin).
// tail effect manager (テイルエフェクト管理): Setting/blur.dat, WS2_swf_sword_blur.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

extern u8 lbl_806EE978[];

u8* fn_806451B4() {
    return lbl_806EE978;
}

// Deleting destructor of a class without a base destructor.
void* fn_80645174(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80645170() {}

void fn_80645090(u8* p) {
    u32 v = *(u32*)(p + 0x10);
    *(u32*)(p + 0x1c) = v;
    *(u32*)(p + 0x20) = v;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0xc) = 0;
    *(f32*)(p + 0x2c) = 1.0f;
}

}  // extern "C"
