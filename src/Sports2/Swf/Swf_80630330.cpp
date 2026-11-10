// Swf_80630330: Resort Swordplay unit 0x80630330-0x8063269C (Resort-only, no Wii Sports twin).
// Duel sequence (対戦シーケンス), state functions in pointer-to-member tables.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EDDD4[];
extern void* lbl_806EDD60[];

u8* fn_80632690() {
    return lbl_806EDDD4;
}

// Deleting destructor of a class without a base destructor.
void* fn_80632650(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80632614(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EDD60;
    return p;
}

void fn_80632600(u8* p) {
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0xc) = 0;
    *(u32*)(p + 0x8) = 0;
}

void fn_806325FC() {}

}  // extern "C"
