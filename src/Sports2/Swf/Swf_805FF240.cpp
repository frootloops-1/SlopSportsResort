// Swf_805FF240: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


extern u8 lbl_806EBCAC[];

u8* fn_80600B04() { return lbl_806EBCAC; }

void* fn_80600AC4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}


// ---- hand-written (first pass) ----
extern void* lbl_806EBC98[];
void fn_8032349C(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);

u8* fn_80600A08(u8* p, u8* a) {
    fn_8032349C(p);
    *(void***)p = lbl_806EBC98;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x30);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x3c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x48);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x54);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x6c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x78);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x84);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x9c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xa8);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xb4);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xcc);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xd8);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xe4);
    *(u8**)(p + 0x8) = a;
    return p;
}

}  // extern "C"
