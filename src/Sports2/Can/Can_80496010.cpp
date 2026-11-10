// Canoeing (Resort-only), .text 0x80496010-0x80497B80: paddle (WS2_can_paddle, .sdata "Paddle"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Vec3Copy { u32 x, y, z; }; // 12-byte block, copied word by word
const char* fn_80497B2C() {
    static char sName[] = "Paddle";
    return sName;
}

Vec3Copy fn_80497B10(const u8* p) { return *(Vec3Copy*)(p + 0xe4); }

// Deleting destructor of a class without a base destructor.
void* fn_80497AD0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804976AC(u8* p) {
    *(f32*)(p + 0x2c) = 0.0f;
    *(f32*)(p + 0x30) = 1.0f;
}

}  // extern "C"
