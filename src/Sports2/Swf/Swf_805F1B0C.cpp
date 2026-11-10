// Swf_805F1B0C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EB920[];

u8* fn_805F1F80() { return lbl_806EB920; }

void* fn_805F1F40(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
extern char sCurrent__13RPGrpRenderer[];
extern s32 lbl_806F0BF8;
extern u8 lbl_8068A148[];
void fn_805F1C2C(u8*);
s32 fn_805F1D08(u8*, s32);
void fn_8037E974(u8*, u8*);

void fn_805F1E5C(u8* p) { fn_8037E974(p, lbl_8068A148 + fn_805F1D08(p, 0) * 0x20); }

void fn_805F1C90(u8* p) {
    if (sCurrent__13RPGrpRenderer[0] == 6 && lbl_806F0BF8 == 2) {
        fn_805F1C2C(p);
    }
}

}  // extern "C"
