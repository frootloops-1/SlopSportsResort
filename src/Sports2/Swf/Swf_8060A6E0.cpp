// Swf_8060A6E0: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_8060C2E8(u8*);
extern u8 lbl_806EC000[];
extern void* lbl_806EBFD8[];

u8* fn_8060AA44() { return lbl_806EC000; }

void* fn_8060AA04(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8060A9B0(u8* p) {
    fn_8060C2E8(p);
    *(void***)(p + 0x0) = lbl_806EBFD8;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x60);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x6c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x78);
    return p;
}

}  // extern "C"
