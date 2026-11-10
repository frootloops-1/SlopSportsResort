// Swf_8062B23C: Resort Swordplay unit 0x8062B23C-0x8062BB8C (Resort-only, no Wii Sports twin).
// class with vtable 0x806EDAC0 (base ctor fn_805FF170), short name 0x806F3AD4 ("対戦").
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>


#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))

extern "C" {

void fn_805FD884(u8*);
void fn_805FF170(u8*);
f32 fn_80328080(f32);
extern char lbl_806F3AD4[5];
extern f32 lbl_806F3AB8;
extern u8 lbl_806EDAC0[];

char* fn_8062BB84() { return lbl_806F3AD4; }

void* fn_8062BB44(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8062BB08(u8* p) {
    fn_805FF170(p);
    *(u8**)p = lbl_806EDAC0;
    return p;
}

void fn_8062B6E0(u8* p, s32 n) {
    switch (n) {
    case 4:
        fn_805FD884(p);
        break;
    case 0:
        S32(p, 0x9c) = 1;
        break;
    }
    S32(p, 0xa4) = n;
}

s32 fn_8062B6D8() { return 0; }

BOOL fn_8062B490(u8* p) { return S32(p, 0xa4) == 2; }

BOOL fn_8062B470(u8* p) {
    switch (S32(p, 0xa4)) {
    case 3:
    case 4:
        return TRUE;
    }
    return FALSE;
}

BOOL fn_8062B418(u8* p) {
    f32 d = fn_80328080(F32(p, 0xc) * F32(p, 0xc) + F32(p, 0x14) * F32(p, 0x14));
    return d >= F32(p, 0xa8) - lbl_806F3AB8;
}

void fn_8062B3BC(u8* p, u32 n) {
    switch (n) {
    case 0:
        return fn_8062B6E0(p, 0);
    case 1:
        return fn_8062B6E0(p, 1);
    case 5:
        return fn_8062B6E0(p, 5);
    case 3:
        return fn_8062B6E0(p, 2);
    case 7:
        return fn_8062B6E0(p, 3);
    case 8:
        return fn_8062B6E0(p, 4);
    case 2:
    case 4:
    case 6:
    case 9:
        return fn_8062B6E0(p, 0);
    }
}

BOOL fn_8062B398(u8* p) {
    if (S32(p, 0xa4) == 0) {
        return S32(p, 0x9c) == 0;
    }
    return FALSE;
}

}  // extern "C"
