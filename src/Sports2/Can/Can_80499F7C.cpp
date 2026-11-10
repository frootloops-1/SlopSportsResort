// Canoeing (Resort-only), .text 0x80499F7C-0x8049A1BC: BoatParam.dat loader. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <revolution/MTX.h>

extern "C" {

struct Vec3f { f32 x, y, z; };
void fn_8035D6C8(u8*);
extern u8 lbl_806DBF10[];

void fn_8049A158(const u8* p, Vec3f* a, Vec3f* b) {
    *a = *(Vec3f*)(*(u8**)(p + 0x8) + 0xc);
    *b = *(Vec3f*)(*(u8**)(p + 0xc) + 0xc);
    a->y -= *(f32*)(*(u8**)(p + 0x8) + 0x18);
    b->y -= *(f32*)(*(u8**)(p + 0xc) + 0x18);
}

// Deleting destructor of a class without a base destructor.
void* fn_8049A01C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80499FE0(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DBF10;
    return p;
}

void fn_80499F88(u8* p) {
    *(f32*)(p + 0x8) = 0.0f;
    *(f32*)(p + 0xc) = 0.0f;
    *(f32*)(p + 0x10) = 0.0f;
    *(f32*)(p + 0x14) = 0.0f;
    for (s32 i = 0; i < 10; i++) {
        p[0x90 + i] = 0;
    }
    for (s32 i = 0; i < 10; i++) {
        p[0x190 + i] = 0;
    }
}

// Horizontal length: drops y, then the vector magnitude.
f32 fn_80499F7C(Vec* v) {
    v->y = 0.0f;
    return PSVECMag(v);
}

}  // extern "C"
