// Swf_805EFD7C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EB824[];

u8* fn_805F0C30() { return lbl_806EB824; }

void* fn_805F0BF0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805F0B08() {}

void fn_805F09CC() {}


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;
void fn_805F09D0(u8*);
void fn_8037BA68(u8*);

void fn_805F01F8(u8* p) {
    fn_8037BA68(*(u8**)(*(u8**)(lbl_806F5FF0 + 0x154) + *(s32*)(p + 0x8) * 4 + 0x8));
}

void fn_805F01BC(u8* p, s32 b) {
    u8* e = *(u8**)(*(u8**)(lbl_806F5FF0 + 0x154) + *(s32*)(p + 0x8) * 4 + 0x8);
    s32 r = 0;
    if (b != 0 && *(s32*)(p + 0x50) == 0) {
        r = 1;
    }
    *(s32*)(e + 0x10) = r;
}

void fn_805EFD7C(u8* p, s32 v) {
    *(s32*)(p + 0x50) = v;
    if (v != 0) {
        fn_805F09D0(p);
    }
}

}  // extern "C"
