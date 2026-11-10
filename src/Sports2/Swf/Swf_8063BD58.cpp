// Swf_8063BD58: Resort Swordplay unit 0x8063BD58-0x8063F630 (Resort-only, no Wii Sports twin).
// path manager (パス管理).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EE6BC[];
extern void* lbl_806EE680[];
extern char lbl_806F3C00[8];
extern char lbl_806F3C08[8];
void fn_8063C064(u8*, u32, s32, f32, f32);
extern f32 lbl_806F3BF8;
extern s32 lbl_806F3BFC;
void fn_8063E0C8(u8*, f32);
void fn_8063D058(u8*, f32);
void fn_8063CF50(u8*, f32);
void fn_8063E1AC(u8*);
void fn_8063E2B8(u8*, u8*);
extern void* lbl_806EE6A8[];

u8* fn_8063F624() {
    return lbl_806EE6BC;
}

char* fn_8063F61C() {
    return lbl_806F3C00;
}

char* fn_8063F614() {
    return lbl_806F3C08;
}

// Deleting destructor of a class without a base destructor.
void* fn_8063F5D4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8063F594(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8063F540(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EE6A8;
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x18) = 0;
    *(u32*)(p + 0x24) = 0;
    *(f32*)(p + 0x1c) = 0.0f;
    return p;
}

void fn_8063EC60() {}

void fn_8063E16C(u8* p, u8* q) {
    fn_8063E1AC(q);
    fn_8063E2B8(p, q);
}

u32 fn_8063DF0C(u8* p, s32 i) {
    return (*(u32**)(*(u8**)(p + 0x8) + 0x14))[*(s32*)(*(u8**)(p + 0x10) + i * 16)];
}

u8* fn_8063DA80(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EE680;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8063DA40(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8063DA34(u8* p) {
    *(u32*)(p + 0x0) = 0;
}

void fn_8063D294() {}

void fn_8063D280(u8* p) {
    u32 v = *(u32*)p;
    *(u32*)(p + 0x8) = v;
    *(u32*)(p + 0xc) = v;
    *(u32*)(p + 0x10) = v;
}

void fn_8063D150(u8* p, f32 x) {
    if (x >= 0.0f) {
        fn_8063D058(p, x);
    } else {
        fn_8063CF50(p, -x);
    }
}

void fn_8063CA70(u8* p) {
    f32 t;
    if (*(s32*)(p + 0x8) != 0) {
        t = *(f32*)(*(u8**)(p + 0x4) + 0x1c) - *(f32*)(p + 0xc);
    } else {
        t = *(f32*)(p + 0xc);
    }
    fn_8063E0C8(*(u8**)(p + 0x4), t);
}

BOOL fn_8063C968(u8* p) {
    return *(u32*)(p + 0x8) == *(u32*)(p + 0xc);
}

void fn_8063C2B8(u8* p, u32 a) {
    fn_8063C064(p, a, lbl_806F3BFC, lbl_806F3BF8, lbl_806F3BF8);
}

BOOL fn_8063C038(u8** p) {
    u8* a = p[3] + 0x74;
    if (a > p[1]) {
        a = p[0];
    }
    return a == p[2];
}

u8* fn_8063BF6C(u8** p, u8* a) {
    a += 0x74;
    if (a > p[1]) {
        a = p[0];
    }
    return a;
}

}  // extern "C"
