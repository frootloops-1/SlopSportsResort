// Swf_80604CE0: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_8032349C(u8*);
void fn_8033E94C(u8*);
extern char lbl_806F3910[8];
extern char lbl_806F3918[8];
extern u8 lbl_806EBE50[];
extern u8 lbl_806EBE60[];
extern void* lbl_806EBE14[];

u8* fn_80607E78() { return lbl_806EBE50; }

char* fn_80607E70() { return lbl_806F3910; }

u8* fn_80607E64() { return lbl_806EBE60; }

char* fn_80607E5C() { return lbl_806F3918; }

void* fn_80607E1C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80607DDC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80607D9C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80607D5C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
void fn_806054A8(u8* p) { *(s32*)(p + 0x1a4) = 0; }


extern void* lbl_806EBE28[];
void fn_806079D4(u8*);

u8* fn_80607980(u8* p, s32 a, s32 b) {
    fn_8032349C(p);
    *(void***)p = lbl_806EBE28;
    fn_806079D4(p + 0x8);
    *(s32*)(p + 0x30) = a;
    *(s32*)(p + 0x34) = b;
    return p;
}

}  // extern "C"
