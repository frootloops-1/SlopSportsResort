// Canoeing (Resort-only), .text 0x804A6C88-0x804A7AD4. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_804A7478(u8* p, u8* q, f32 t);
void fn_804A7A08(u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0xc); i++) {
        *(u32*)((*(u8***)(p + 0x8))[i] + 0x78) = 0;
    }
    *(s32*)(p + 0xc) = 0;
}

void fn_804A79C4(u8* p, u8* obj) {
    if (*(u32*)(obj + 0x78) == 0) {
        s32 n = *(s32*)(p + 0xc);
        u8* e = *(u8**)(p + 0x4) + n * 0x60;
        *(s32*)(obj + 0x7c) = n;
        *(u8**)(obj + 0x78) = e;
        (*(u8***)(p + 0x8))[*(s32*)(p + 0xc)] = obj;
        (*(s32*)(p + 0xc))++;
    }
}

// Deleting destructor of a class without a base destructor.
void* fn_804A7984(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804A7380() {}

void fn_804A6FB8(const u8* p, const u8* idx, u8* out) {
    fn_804A7478(*(u8**)(p + 0x8) + *(s32*)idx * 0x68, out, *(f32*)(idx + 0x4));
}

// Moves a toward b along a looped course of length 0x10 (shortest way, half-length 0x14).
f32 fn_804A6F6C(const u8* p, f32 a, f32 b) {
    f32 d = b - a;
    while (d < 0.0f) {
        d += *(f32*)(p + 0x10);
    }
    while (d > *(f32*)(p + 0x10)) {
        d -= *(f32*)(p + 0x10);
    }
    if (d > *(f32*)(p + 0x14)) {
        d -= *(f32*)(p + 0x10);
    }
    return a + d;
}

f32 fn_804A6F44(const f32* a, const f32* b) {
    f32 dz = b[2] - a[2];
    f32 dx = b[0] - a[0];
    f32 zz = dz * dz;
    f32 xx = dx * dx;
    return xx + zz;
}

f32 fn_804A6F34(f32 a, f32 b) { return (a < b) ? a : b; }

}  // extern "C"
