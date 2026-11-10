// Swf_8060B71C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_8060C2E8(u8*);
extern u8 lbl_806EC0E8[];
extern void* lbl_806EC0C0[];

u8* fn_8060C054() { return lbl_806EC0E8; }

void* fn_8060C014(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8060BFD8(u8* p) {
    fn_8060C2E8(p);
    *(void***)(p + 0x0) = lbl_806EC0C0;
    return p;
}


// ---- hand-written (first pass) ----
void __ct__Q34nw4r4math4VEC3Fv(u8*);

u8* fn_8060B71C(u8* p) {
    __ct__Q34nw4r4math4VEC3Fv(p + 0xc);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    return p;
}

}  // extern "C"
