// Canoeing (Resort-only), .text 0x804B171C-0x804B6D58: ducks (WS2_can_duck*, .sdata "Duck"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Vec3f { f32 x, y, z; };
struct Vec3Copy { u32 x, y, z; }; // 12-byte block, copied word by word
void fn_804B346C(u8*);
void fn_804B37E0(u8*);
extern u8* lbl_806F5838;

// Deleting destructor of a class without a base destructor.
void* fn_804B6C98(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

const char* fn_804B6C90() {
    static char sName[] = "Duck";
    return sName;
}

u32 fn_804B6954(u8* p) { return *(u32*)(p); }

u8* fn_804B6938(const u8* p, s32 off) {
    u8* base = *(u8**)p;
    if (off != 0) {
        return base + off;
    }
    return NULL;
}

void fn_804B3BE8(u8* p) {
    fn_804B37E0(p);
    fn_804B346C(p);
}

Vec3Copy fn_804B2860(const u8* p) { return **(Vec3Copy**)(*(u8**)(p + 0xc) + 0x4c); }

u8* fn_804B275C(u8* p) { return *(u8**)(p + 0xc) + 0x8; }

u8* fn_804B2750(u8* p) { return *(u8**)(p + 0xc) + 0x50; }

f32 fn_804B2744(u8* p) { return *(f32*)(*(u8**)(p + 0x10) + 0x8); }

u8* fn_804B2308() { return *(u8**)(lbl_806F5838 + 0x44) + 0x1; }

s32 fn_804B2300() { return 11; }

f32 fn_804B22EC(const u8* p) { return *(f32*)(*(u8**)(p + 0x48) + 0xac) + 3.0f; }

void fn_804B1C30(u8* p, u32 a1) { *(u32*)(p + 0x190) = a1; }

// Keeps the nearest hit: distance at 0x1AC (0 = none), position at 0x1A0.
void fn_804B1B40(u8* p, f32 dist, const Vec3f* pos) {
    if (0.0f == *(f32*)(p + 0x1ac) || dist < *(f32*)(p + 0x1ac)) {
        *(f32*)(p + 0x1ac) = dist;
        *(Vec3f*)(p + 0x1a0) = *pos;
    }
}

}  // extern "C"
