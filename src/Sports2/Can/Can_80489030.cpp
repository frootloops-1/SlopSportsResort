// Canoeing (Resort-only), .text 0x80489030-0x80489D84. First pass; not a full match.

#include <types.h>

extern "C" {

void fn_8035D6C8(u8* p); // base ctor
void fn_80489960(u8* p, f32 a, f32 b, f32 c, f32 d);
extern void* lbl_806DBD10[];
// Deleting destructor of a class without a base destructor.
void* fn_80489D18(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80489CC4(u8* p) {
    fn_8035D6C8(p);
    *(void***)p = lbl_806DBD10;
    fn_80489960(p, 0.0f, 0.0f, 0.0f, 0.0f);
    return p;
}

f32 fn_804897B8() { return 1.5707963705062866f; }

// Degrees to radians.
f32 fn_80489704(f32 deg) { return deg * 0.017453292f; }

void fn_8048931C(u8* p) {
    if (p[0x10] != 0) {
        if (*(f32*)(p + 0x8) < *(f32*)(p + 0x68)) {
            p[0x10] = 0;
            *(f32*)(p + 0x64) = 0.05f + *(f32*)(p + 0x8);
        }
    } else {
        if (*(f32*)(p + 0x8) > *(f32*)(p + 0x64)) {
            p[0x10] = 1;
            *(f32*)(p + 0x68) = *(f32*)(p + 0x8) - 0.05f;
        }
    }
}

}  // extern "C"
