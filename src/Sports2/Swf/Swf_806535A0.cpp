// Swf_806535A0: Resort Swordplay unit 0x806535A0-0x80653FA0 (Resort-only, no Wii Sports twin).
// custom effects (カスタム): monitor_lightning, candle_flame/smoke.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

struct Unk_VtAt0_30 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void vf();
};
#include "Pack/RPKernel/RPSysEffectBase.h"

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806F0024[];
extern void* lbl_806EFFF0[];
u8* fn_80653E5C(u8*, u32);
u32 fn_80602F30(const char*);
extern void* lbl_806EFFBC[];
extern void* lbl_806EFF54[];

u8* fn_80653F60() {
    return lbl_806F0024;
}

// Deleting destructor of a class without a base destructor.
void* fn_80653F20(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80653EE0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80653EA0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80653E5C(u8* p, u32 a) {
    fn_8032349C(p);
    *(void**)p = lbl_806EFFF0;
    *(u32*)(p + 0x8) = a;
    return p;
}


void fn_80653DAC(u8* p) {
    (*(RPSysEffect**)(p + 0xc))->forceKill();
    (*(RPSysEffect**)(p + 0x10))->forceKill();
    *(s32*)(p + 0x18) = 0;
    *(s32*)(p + 0x14) = 0;
}

void fn_80653D6C(u8* p) {
    (*(RPSysEffect**)(p + 0xc))->create();
    (*(RPSysEffect**)(p + 0x10))->forceKill();
    *(s32*)(p + 0x14) = 1;
}

void fn_80653D34(u8* p) {
    (*(RPSysEffect**)(p + 0xc))->forceKill();
    (*(RPSysEffect**)(p + 0x10))->forceKill();
}


void fn_806537F0(u8* p) {
    *(s32*)(p + 0xc) = 599;
    *(s32*)(p + 0x10) = 0;
    (*(RPSysEffect**)(p + 0x14))->forceKill();
    *(s32*)(p + 0x18) = 0;
}

void fn_806537E0(Unk_VtAt0_30* p) {
    p->vf();
}

void fn_806537D8(u8* p) {
    (*(RPSysEffect**)(p + 0x14))->forceKill();
}

void fn_806535A0(u8* p, u8* q) {
    *(u32*)(p + 0xc) = *(u32*)(q + 0xc);
    *(u32*)(p + 0x10) = *(u32*)(q + 0x10);
    *(u32*)(p + 0x18) = 0;
}

}  // extern "C"
