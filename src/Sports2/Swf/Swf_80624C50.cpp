// Swf_80624C50: Resort Swordplay unit 0x80624C50-0x80625D00 (Resort-only, no Wii Sports twin).
// "リプレイ用カメラ" (replay camera): vtable 0x806ED808, name 0x806ED830, Env/replay.pdof.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_8060C2E8(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);
extern u8 lbl_806ED808[];
extern char lbl_806ED830[];

char* fn_80625C8C() { return lbl_806ED830; }

void* fn_80625C4C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80625BF8(u8* p) {
    fn_8060C2E8(p);
    *(u8**)p = lbl_806ED808;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x58);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x64);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x70);
    return p;
}

}  // extern "C"
