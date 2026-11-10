// Swf_8060C1E4: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_80322E4C(u8*);
extern u8 lbl_806EC160[];
extern void* lbl_806EC138[];

u8* fn_8060C32C() { return lbl_806EC160; }

u8* fn_8060C2E8(u8* p) {
    fn_80322E4C(p);
    *(void***)(p + 0x0) = lbl_806EC138;
    *(s32*)(p + 0x4c) = 0x0;
    return p;
}

}  // extern "C"
