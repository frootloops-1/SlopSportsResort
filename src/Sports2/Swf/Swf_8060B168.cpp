// Swf_8060B168: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_805FF170(u8*);
extern u8 lbl_806EC0B0[];
extern void* lbl_806EC050[];

u8* fn_8060B650() { return lbl_806EC0B0; }

void* fn_8060B610(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8060B24C(u8* p) {
    fn_805FF170(p);
    *(void***)(p + 0x0) = lbl_806EC050;
    return p;
}


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;

void fn_8060B240(u8* p) { *(s32*)(p + 0xa4) = 0; }

void fn_8060B220(u8* p) {
    if (*(s32*)(p + 0xa4) == 1) {
        *(f32*)(p + 0x10) = *(f32*)(*(u8**)(lbl_806F5FF0 + 0x164) + 0x98);
    }
}

}  // extern "C"
