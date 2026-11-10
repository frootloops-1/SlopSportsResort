// Swf_80600BA8: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EBCCC[];

u8* fn_80602B4C() { return lbl_806EBCCC; }

void* fn_80602B0C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806022C8(u8* p) { return p + 0x48; }

f32 fn_80600D48() { return 1e+01f; }


// ---- hand-written (first pass) ----
void fn_80602860(u8* p) {
    *(s32*)(p + 0xf8) += 1;
    *(s32*)(p + 0xf4) += 1;
}

}  // extern "C"
