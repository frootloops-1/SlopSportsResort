// Swf_80604314: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_80328F20(u8*);
extern u8 lbl_806EBDF0[];
extern void* lbl_806EBDD0[];

u8* fn_80604CD4() { return lbl_806EBDF0; }

void* fn_80604C94(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;
void fn_806043AC(u8*);

void fn_80604530(u8* p, s32 v) {
    if (v == 1) {
        fn_806043AC(p);
    }
}

int fn_806044FC(u8*) {
    u8* s = *(u8**)(lbl_806F5FF0 + 0x170);
    u8* a = *(u8**)(s + 0x20);
    u8* b = *(u8**)(s + 0x24);
    int r = 0;
    if (*(s32*)(a + 0xd0) == 0 && *(s32*)(b + 0xd0) == 0) {
        r = 1;
    }
    return r;
}

}  // extern "C"
