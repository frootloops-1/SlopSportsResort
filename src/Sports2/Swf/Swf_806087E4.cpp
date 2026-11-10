// Swf_806087E4: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern char lbl_806F3920[8];
extern u8 lbl_806EBF68[];
extern u8 lbl_806EBF74[];

u8* fn_8060A11C() { return lbl_806EBF68; }

u8* fn_8060A110() { return lbl_806EBF74; }

char* fn_8060A108() { return lbl_806F3920; }

void* fn_8060A0C8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8060A088(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8060A048(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80608F68(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
void fn_8023E75C(u8*, s32);

void fn_8060935C(u8* p, s32 v) {
    if (v == *(s32*)(p + 0xc)) {
        fn_8023E75C(*(u8**)(p + 0x8), 0);
    } else {
        fn_8023E75C(*(u8**)(p + 0x8), 1);
    }
}
}  // extern "C"

extern "C" void fn_80608E8C(u8* p) {
    (*(RPSysEffect**)(p + 0x8))->forceKill();
    (*(RPSysEffect**)(p + 0x8))->create();
    *(s32*)(p + 0x14) = 1;
    *(s32*)(p + 0x18) = 0;
}

extern "C" {


extern void* lbl_806EBF40[];
extern void* lbl_806EBF54[];
extern char lbl_8068A750[];
void fn_8032349C(u8*);
u8* fn_80602F30(const char*);

u8* fn_80609380(u8* p, s32 a) {
    fn_8032349C(p);
    *(void***)p = lbl_806EBF54;
    *(s32*)(p + 0xc) = a;
    *(s32*)(p + 0x8) = 0;
    return p;
}

u8* fn_8060930C(u8* p, s32 a) {
    fn_80609380(p, a);
    *(void***)p = lbl_806EBF40;
    *(u8**)(p + 0x8) = fn_80602F30(lbl_8068A750 + 0x20);
    return p;
}


extern void* lbl_806EBF2C[];
extern u8* lbl_806F5FF0;
extern u8 lbl_807D0318[];
int fn_806044FC(u8*);
void fn_8023E498(u8*, u8*);
void fn_8023E28C(u8*);

u8* fn_80608EEC(u8* p, s32 a) {
    fn_80609380(p, a);
    *(void***)p = lbl_806EBF2C;
    u8* e = fn_80602F30(fn_806044FC(*(u8**)(lbl_806F5FF0 + 0x174)) ? lbl_8068A750 + 0xc : lbl_8068A750 + 0x16);
    *(u8**)(p + 0x8) = e;
    fn_8023E498(e, lbl_807D0318);
    fn_8023E28C(*(u8**)(p + 0x8));
    return p;
}

}  // extern "C"
