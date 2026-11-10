// Swf_805F181C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EB8D8[];

u8* fn_805F1B00() { return lbl_806EB8D8; }

void* fn_805F1AC0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
void fn_80322FD4(u8*, u8*);

void fn_805F181C(u8* p, s32 i) { fn_80322FD4(p, *(u8**)(p + 0xb8 + i * 4)); }

}  // extern "C"
