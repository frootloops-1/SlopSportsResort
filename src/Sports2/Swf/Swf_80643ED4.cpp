// Swf_80643ED4: Resort Swordplay unit 0x80643ED4-0x806440D4 (Resort-only, no Wii Sports twin).
// Showdown intro camera (組み手イントロカメラ); __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8060C2E8(u8*);
extern u8 lbl_806EE8E0[];
extern void* lbl_806EE8B8[];

u8* fn_806440A8() {
    return lbl_806EE8E0;
}

// Deleting destructor of a class without a base destructor.
void* fn_80644068(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8064402C(u8* p) {
    fn_8060C2E8(p);
    *(void**)p = lbl_806EE8B8;
    return p;
}

void fn_80644018(u8* p) {
    *(u32*)(p + 0x50) = 0;
    *(f32*)(p + 0x54) = 30.0f;
}

}  // extern "C"
