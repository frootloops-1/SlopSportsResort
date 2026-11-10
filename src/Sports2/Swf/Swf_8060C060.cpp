// Swf_8060C060: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_8060C2E8(u8*);
extern u8 lbl_806EC128[];
extern void* lbl_806EC100[];

u8* fn_8060C1D8() { return lbl_806EC128; }

void* fn_8060C198(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8060C144(u8* p) {
    fn_8060C2E8(p);
    *(void***)(p + 0x0) = lbl_806EC100;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x5c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x68);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x74);
    return p;
}

}  // extern "C"
