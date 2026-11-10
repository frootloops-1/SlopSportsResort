// Swf_80635720: Resort Swordplay unit 0x80635720-0x80636E9C (Resort-only, no Wii Sports twin).
// Showdown sequence (組み手シーケンス), pointer-to-member state tables.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EE2F0[];
extern void* lbl_806EE288[];

u8* fn_80636E90() {
    return lbl_806EE2F0;
}

// Deleting destructor of a class without a base destructor.
void* fn_80636E50(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80636E14(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EE288;
    return p;
}

void fn_80636DF8(u8* p) {
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0xc) = 0;
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x18) = 0;
}

void fn_80636DF4() {}

}  // extern "C"
