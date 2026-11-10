// Swf_806394F8: Resort Swordplay unit 0x806394F8-0x8063A0C4 (Resort-only, no Wii Sports twin).
// Showdown player (組み手プレイヤー).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8063BC34(u8*);
extern u8 lbl_806EE5D8[];
extern void* lbl_806EE55C[];
void fn_8063965C(u8*);

int fn_8063A0BC() {
    return 0;
}

u8* fn_8063A0B0() {
    return lbl_806EE5D8;
}

// Deleting destructor of a class without a base destructor.
void* fn_8063A070(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8063A034(u8* p) {
    fn_8063BC34(p);
    *(void**)p = lbl_806EE55C;
    return p;
}

BOOL fn_80639944(u8*, s32, s32 c, s32 d) {
    if (d != 0) {
        return FALSE;
    }
    return c >= 2;
}

BOOL fn_80639898(u8* p) {
    return *(s32*)(p + 0x130) == 1;
}

BOOL fn_80639884(u8* p) {
    return *(s32*)(p + 0x130) == 3;
}

BOOL fn_80639864(u8* p) {
    s32 v = *(s32*)(p + 0x130);
    return v == 5 || v == 6;
}

void fn_80639860() {}

void fn_80639820(u8* p) {
    *(s32*)(p + 0x130) = 7;
    fn_8063965C(p);
    *(u32*)(p + 0xc8) &= ~1;
}

void fn_8063981C() {}

}  // extern "C"
