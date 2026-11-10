// Swf_80633C38: Resort Swordplay unit 0x80633C38-0x80635720 (Resort-only, no Wii Sports twin).
// Showdown rules (組み手ルール): Cpu/Sp2SwfKumiteData.exbin; __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

struct Unk_Swf320 {
    u8 pad[0x290];
    struct {
        s32 a;
        u32 b;
    } m290[18];
};
#include "Pack/RPKernel/RPSysEffectBase.h"

extern "C" {

extern u8 lbl_806EE278[];
extern u8* lbl_806F5FF0;
void fn_802C038C(u8*, s32);
void fn_80633D7C(u8*, s32);
void fn_80643B0C(u8*);
extern void* lbl_806EE228[];
void fn_80633E7C(u8*);

u8* fn_806356B0() {
    return lbl_806EE278;
}

// Deleting destructor of a class without a base destructor.
void* fn_80635670(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80635624(u8* p) {
    fn_80643B0C(p);
    *(void**)p = lbl_806EE228;
    *(u32*)(p + 0x50) = 0;
    *(u32*)(p + 0x34) = 0;
    *(u32*)(p + 0x68) = 0;
    return p;
}

void fn_80635484(u8* p) {
    *(u32*)(p + 0x1c) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
    *(u32*)(p + 0x2c) = 0;
    *(u32*)(p + 0x30) = 0;
    *(u32*)(p + 0x38) = 0;
    *(u32*)(p + 0x4c) = 0;
    *(u32*)(p + 0x50) = 0;
    *(u32*)(p + 0x54) = 0;
    *(u32*)(p + 0x58) = 0;
    *(u32*)(p + 0x48) = 0;
    fn_80633E7C(p);
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x18) = 0;
}

void fn_80635480() {}

void fn_80634C20(u8* p, u8* q) {
    if (*(s32*)(p + 0x14) == 1 && *(s32*)(q + 0xc) == 0) {
        *(s32*)(p + 0x48) = 0;
    }
}

void fn_80634C08(u8* p, u32 a) {
    if (*(u32*)(p + 0x24) == a) {
        *(u32*)(p + 0x24) = 0;
    }
}

void fn_80634BE4(u8* p) {
    s32 n = *(s32*)(p + 0x48) + 1;
    *(s32*)(p + 0x48) = n;
    if (n > *(s32*)(p + 0x4c)) {
        *(s32*)(p + 0x4c) = n;
    }
    fn_80633D7C(p, *(s32*)(p + 0x48));
}

void fn_80634B50() {}

void fn_806349AC() {}

void fn_806349A8() {}

void fn_80634668(u8* p) {
    s32 n = *(s32*)(p + 0x2c) + 1;
    *(s32*)(p + 0x2c) = n;
    fn_802C038C(*(u8**)(p + 0x68), *(s32*)(p + 0x20) - n);
}

u32 fn_80634660(u8* p) {
    return *(u32*)(p + 0x20);
}

u8* fn_806341D4(u8* p, s32 i) {
    u8* base = *(u8**)(p + 0x10);
    Unk_Swf320* e = (Unk_Swf320*)base + *(s32*)(p + 0x3c);
    s32 idx = e->m290[i].a;
    return base + idx * 0x18 + 0xb0;
}

u32 fn_806341B4(u8* p, s32 i) {
    Unk_Swf320* e = (Unk_Swf320*)*(u8**)(p + 0x10) + *(s32*)(p + 0x3c);
    return e->m290[i].b;
}

void fn_80633E7C(u8* p) {
    (*(RPSysEffect**)(p + 0x5c))->forceKill();
    (*(RPSysEffect**)(p + 0x60))->forceKill();
    (*(RPSysEffect**)(p + 0x64))->forceKill();
}

int fn_80633D74() {
    return 20;
}

u32 fn_80633D5C() {
    return *(u32*)(*(u8**)(*(u8**)(*(u8**)(lbl_806F5FF0 + 0x170) + 0x20) + 0x110) + 0x104);
}

s32 fn_80633C38(u8* p) {
    s32 a = *(s32*)(p + 0x2c);
    s32 b = *(s32*)(p + 0x20);
    if (b - a == 1) {
        return 99;
    }
    return a * 100 / b;
}

}  // extern "C"
