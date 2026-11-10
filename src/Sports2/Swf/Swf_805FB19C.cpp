// Swf_805FB19C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EBC14[];

u8* fn_805FD568() { return lbl_806EBC14; }

void* fn_805FD528(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805FCFB0() {}

void fn_805FC05C() {}


// ---- hand-written (first pass) ----
extern char sCurrent__13RPGrpRenderer[];
void fn_8025A0F8(u8*, s32);
void GXCallDisplayList(void*, u32);
void fn_805F295C(u8*);
void fn_805FC4F8(u8*, s32);

void fn_805FD410(s32* p) {
    s32 v = p[0];
    p[2] = v;
    p[3] = v;
    p[4] = v;
}

void fn_805FC590(u8* p) {
    switch ((u8)sCurrent__13RPGrpRenderer[0]) {
    case 2:
        fn_805FC4F8(p, 0);
        break;
    case 3:
        fn_805FC4F8(p, 1);
        break;
    }
}

u8* fn_805FC0E4(u8* p, s32 i) {
    u8** e = (u8**)(p + 0x20 + i * 4);
    fn_805F295C(*e);
    return *e;
}

void fn_805FB430(u8* p) {
    fn_8025A0F8(*(u8**)(p + 0x54), 0);
    GXCallDisplayList(*(void**)(p + 0x5c), *(u32*)(p + 0x58));
}

void fn_805FB2C8(u8* p, s32 i) { *(s32*)(p + 0x28) = *(s32*)(p + 0x34 + i * 4); }

}  // extern "C"
