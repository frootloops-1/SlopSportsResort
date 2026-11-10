// Swf_806419C4: Resort Swordplay unit 0x806419C4-0x80642EB8 (Resort-only, no Wii Sports twin).
// Mii manager (Miiマネージャ); __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
#include <revolution/GX.h>

extern "C" {

extern u8 lbl_806EE7CC[];

u8* fn_80642E30() {
    return lbl_806EE7CC;
}

// Deleting destructor of a class without a base destructor.
void* fn_80642DF0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80642B08(u8* p) {
    *(u32*)(p + 0x0) = 0;
    *(u32*)(p + 0x1c) = 0;
    *(u32*)(p + 0x20) = 0;
}

void fn_80641A54(u8* p) {
    GXSetArray(GX_VA_POS, *(void**)(p + 0x8), 0xc);
    GXSetArray(GX_VA_NRM, *(void**)(p + 0xc), 0xc);
}

}  // extern "C"
