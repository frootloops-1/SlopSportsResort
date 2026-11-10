// Swf_8064E7B4: Resort Swordplay unit 0x8064E7B4-0x8064F064 (Resort-only, no Wii Sports twin).
// vanish animation (消滅アニメ): WS2_swf_ava_dead_scale.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

extern u8 lbl_806EF42C[];

u8* fn_8064F058() {
    return lbl_806EF42C;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064F018(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8064ECB0() {}

}  // extern "C"
