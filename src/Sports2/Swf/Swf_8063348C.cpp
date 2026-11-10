// Swf_8063348C: Resort Swordplay unit 0x8063348C-0x80633C38 (Resort-only, no Wii Sports twin).
// Showdown field (組み手フィールド): WS2_swf_island map, collision, models; __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

extern u8 lbl_806EE1E0[];
extern s32 lbl_806F6040;

u8* fn_80633C08() {
    return lbl_806EE1E0;
}

// Deleting destructor of a class without a base destructor.
void* fn_80633BC8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80633638() {}

f32 fn_806335AC() {
    return 5e+01f;
}

void fn_8063358C() {
    s32 v = lbl_806F6040 + 1;
    lbl_806F6040 = v;
    if (v >= 3) {
        lbl_806F6040 = 0;
    }
}

}  // extern "C"
