// Swf_8060C73C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_8032349C(u8*);
extern u8 lbl_806EC1BC[];
extern void* lbl_806B880C[];
extern void* lbl_806EC1A8[];

u8* fn_8060CB60() { return lbl_806EC1BC; }

void* fn_8060CB20(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8060C80C() {}


// ---- hand-written (first pass) ----
extern u8* lbl_806F4E90;
void fn_80370BD4(int, const char*);
void fn_80269C90(u8*);

s32 fn_8060C7D4(u8* p) {
    s32 n = 0;
    for (s32 i = 0; i < 2; i++) {
        if (*(s32*)(p + 0xc + i * 4) == 0) {
            n++;
        }
    }
    return n;
}

void fn_8060C798() {
    fn_80370BD4(lbl_806F4E90 != NULL, (const char*)lbl_806B880C);
    fn_80269C90(lbl_806F4E90);
}

}  // extern "C"
