// Swf_8065277C: Resort Swordplay unit 0x8065277C-0x806530E4 (Resort-only, no Wii Sports twin).
// Showdown search control and manager (組み手サーチ制御, 組み手サーチ制御管理).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EFDE8[];
extern u8 lbl_806EFE00[];
extern void* lbl_806EFDC0[];
extern void* lbl_806EFDD4[];
void fn_80653038(u8*);

u8* fn_806530D8() {
    return lbl_806EFDE8;
}

u8* fn_806530CC() {
    return lbl_806EFE00;
}

// Deleting destructor of a class without a base destructor.
void* fn_8065308C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8065304C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80653038(u8* p) {
    *(u32*)p = 0;
    *(f32*)(p + 0x4) = 3.4028235e38f;
}

void fn_80653020(u8* p, u32 a, f32 x) {
    if (x < *(f32*)(p + 0x4)) {
        *(u32*)p = a;
        *(f32*)(p + 0x4) = x;
    }
}

u8* fn_80652FDC(u8* p, u32 a) {
    fn_8032349C(p);
    *(void**)p = lbl_806EFDD4;
    *(u32*)(p + 0x8) = a;
    return p;
}

void fn_80652A90(u8* p) {
    for (s32 i = 0; i < 3; i++) {
        fn_80653038(p + i * 8 + 0xc);
    }
}

u8* fn_80652988(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EFDC0;
    return p;
}

}  // extern "C"
