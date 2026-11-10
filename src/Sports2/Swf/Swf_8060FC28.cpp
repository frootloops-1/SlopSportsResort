// Swf_8060FC28: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_8032349C(u8*);
extern u8 lbl_806EC7F0[];
extern void* lbl_806EC7DC[];

u8* fn_806104A4() { return lbl_806EC7F0; }

void* fn_80610464(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80610428(u8* p) {
    fn_8032349C(p);
    *(void***)(p + 0x0) = lbl_806EC7DC;
    return p;
}

}  // extern "C"
