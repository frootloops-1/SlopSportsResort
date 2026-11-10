// Swf_8062BB8C: Resort Swordplay unit 0x8062BB8C-0x8062C234 (Resort-only, no Wii Sports twin).
// class with vtable 0x806EDB20 (base ctor fn_805FF170), short name 0x806F3AE4 ("仕掛け"?).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))

extern "C" {

void fn_805FF170(u8*);
void fn_8062BC08(u8*);
extern char lbl_806F3AE4[5];
extern f32 lbl_807D0318[3];
extern u8 lbl_806EDB20[];

char* fn_8062C22C() { return lbl_806F3AE4; }

void* fn_8062C1EC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8062C190(u8* p) {
    fn_805FF170(p);
    *(u8**)p = lbl_806EDB20;
    F32(p, 0xa4) = lbl_807D0318[0];
    F32(p, 0xa8) = lbl_807D0318[1];
    F32(p, 0xac) = lbl_807D0318[2];
    return p;
}

void fn_8062BBC0(u8* p, s32 n);

void fn_8062C130(u8* p) {
    S32(p, 0xb4) = 0;
    fn_8062BC08(p);
    F32(p, 0x54) = F32(p, 0x48);
    F32(p, 0x58) = F32(p, 0x4c);
    F32(p, 0x5c) = F32(p, 0x50);
    F32(p, 0x60) = 0.0f;
    fn_8062BBC0(p, 0);
}

void fn_8062BE00(u8* p) { fn_8062BC08(p); }

void fn_8062BDF8(u8* p, s32 v) {
    S32(p, 0xb4) = v;
    fn_8062BC08(p);
}

// MATCH-PENDING (R17) #19: dont_inline region keeps this callee out of line
#pragma push
#pragma dont_inline on
void fn_8062BBC0(u8* p, s32 n) {
    switch (n) {
    case 1:
        F32(p, 0x84) = 0.0f;
        break;
    case 2:
        F32(p, 0x60) = 0.0f;
        F32(p, 0x54) = F32(p, 0xc);
        F32(p, 0x58) = F32(p, 0x10);
        F32(p, 0x5c) = F32(p, 0x14);
        break;
    }
    S32(p, 0xb0) = n;
}
#pragma pop

void fn_8062BB8C(u8* p) {
    F32(p, 0x54) = F32(p, 0xa4) - 8.0f * F32(p, 0x30);
    F32(p, 0x58) = F32(p, 0x10);
    F32(p, 0x5c) = F32(p, 0xac) - 8.0f * F32(p, 0x38);
    fn_8062BBC0(p, 1);
}

}  // extern "C"
