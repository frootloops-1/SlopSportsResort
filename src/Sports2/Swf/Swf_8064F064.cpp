// Swf_8064F064: Resort Swordplay unit 0x8064F064-0x8064F2B0 (Resort-only, no Wii Sports twin).
// Speed Slice camera (薪割りカメラ); __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8060C2E8(u8*);
extern u8 lbl_806EF478[];
extern void* lbl_806EF450[];

u8* fn_8064F26C() {
    return lbl_806EF478;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064F22C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8064F1F0(u8* p) {
    fn_8060C2E8(p);
    *(void**)p = lbl_806EF450;
    return p;
}

void fn_8064F1D4(u8* p) {
    *(s32*)(p + 0x50) = 1;
    *(f32*)(p + 0x54) = 0.0f;
    *(f32*)(p + 0x48) = 1.1666666f;
}

void fn_8064F1C0(u8* p) {
    *(s32*)(p + 0x50) = 1;
    *(f32*)(p + 0x54) = 0.0f;
}

}  // extern "C"
