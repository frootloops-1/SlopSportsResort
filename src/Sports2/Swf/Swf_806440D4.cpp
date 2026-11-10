// Swf_806440D4: Resort Swordplay unit 0x806440D4-0x806443F0 (Resort-only, no Wii Sports twin).
// Showdown fixed camera on path (組み手パス上固定カメラ).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8060C2E8(u8*);
extern u8 lbl_806EE920[];
extern void* lbl_806EE8F8[];

u8* fn_806443E4() {
    return lbl_806EE920;
}

// Deleting destructor of a class without a base destructor.
void* fn_806443A4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80644368(u8* p) {
    fn_8060C2E8(p);
    *(void**)p = lbl_806EE8F8;
    return p;
}

void fn_80644364() {}

void fn_80644358(u8* p) {
    *(f32*)(p + 0x3c) = 50.0f;
}

}  // extern "C"
