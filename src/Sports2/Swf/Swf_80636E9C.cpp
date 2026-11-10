// Swf_80636E9C: Resort Swordplay unit 0x80636E9C-0x80638D40 (Resort-only, no Wii Sports twin).
// Showdown CPU (組み手CPU).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8063A91C(u8*);
extern u8 lbl_806EE43C[];
void fn_80638348(u8*, s32);
void fn_805FF02C(u8*);
void fn_805F2888(u8*, s32);
void fn_80634668(u8*);
extern u8* lbl_806F5FF0;
u8* fn_80652FDC(u8*, u8*);

u8* fn_80638D34() {
    return lbl_806EE43C;
}

// Deleting destructor of a class without a base destructor.
void* fn_80638CF4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80638CB4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80638C1C(u8* p) {
    u8* o = (u8*)operator new(0x3c);
    if (o != NULL) {
        o = fn_80652FDC(o, *(u8**)(p + 0x8));
    }
    *(u8**)(p + 0x174) = o;
}

void fn_806384DC(u8* p, u32 a) {
    switch (a) {
    case 0:
        fn_80638348(p, 4);
        break;
    case 1:
        fn_80638348(p, 5);
        break;
    case 5:
        fn_80638348(p, 7);
        break;
    case 3:
        fn_80638348(p, 6);
        break;
    case 7:
        fn_80638348(p, 8);
        break;
    case 8:
        fn_80638348(p, 9);
        break;
    case 10:
        fn_80638348(p, 3);
        break;
    case 12:
        fn_80638348(p, 10);
        break;
    case 2:
    case 6:
    case 9:
    case 11:
        fn_80638348(p, 4);
        break;
    case 4:
        if (*(s32*)(*(u8**)(p + 0x8) + 0x88) != 0) {
            fn_80638348(p, 4);
        } else {
            fn_80638348(p, 0);
        }
        break;
    }
}

void fn_806384D8(u8* p) {
    fn_805FF02C(p);
}

void fn_806384BC(u8* p) {
    if (*(s32*)(*(u8**)(p + 0x8) + 0x88) == 0) {
        fn_80638348(p, 2);
    }
}

void fn_806383EC(u8* p) {
    fn_8063A91C(p);
    fn_805F2888(*(u8**)(p + 0x8), 0);
    fn_80634668(*(u8**)(lbl_806F5FF0 + 0x184));
}

BOOL fn_806383D8(u8* p) {
    return *(s32*)(p + 0x138) == 4;
}

BOOL fn_806383C4(u8* p) {
    return *(s32*)(p + 0x138) == 6;
}

BOOL fn_806383A4(u8* p) {
    s32 v = *(s32*)(p + 0x138);
    return v == 8 || v == 9;
}

}  // extern "C"
