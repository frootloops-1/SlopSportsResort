// Swf_805F0C58: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EB890[];

u8* fn_805F17B0() { return lbl_806EB890; }

void* fn_805F1770(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805F1730(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805F16CC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
int fn_805F170C(u8*, u8* q) {
    return ((1 << (*(u16*)(*(u8**)(q + 0x4) + 0xe) & 0x1f)) & 0x80) == 0;
}

}  // extern "C"
