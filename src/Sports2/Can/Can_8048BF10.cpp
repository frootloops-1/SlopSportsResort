// Canoeing (Resort-only), .text 0x8048BF10-0x80494264: boat (WS2_can_canoe*, .sdata "Boat"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Vec3Copy { u32 x, y, z; }; // 12-byte block, copied word by word
void fn_8049AEBC(u8* p, u8* q);
void fn_8048FE60(u8* p, u32 v);
void fn_802A4C90(u8*);
void fn_8035D6C8(u8*);
void fn_80490874(u8*);
void fn_80490F3C(u8*);
extern u8 lbl_806DBD78[];

const char* fn_80494114() {
    static char sName[] = "Boat";
    return sName;
}

// Deleting destructor of a class without a base destructor.
void* fn_804940D4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u32 fn_804940B0(u8* p, s32 i) { return ((s32*)(p + 0x20))[i] < 4; }

u32 fn_804940A0(u8* p, s32 a1) { return *(u32*)(p + a1 * 4 + 0x20); }

void fn_8049409C() {}

void fn_80492818(u8* p) { fn_802A4C90(*(u8**)(p + 0x8)); }

u8* fn_804927DC(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DBD78;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8049279C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

f32 fn_80492000(f32 lo, f32 hi, f32 x) {
    f32 d = hi - lo;
    f32 r = 0.0f;
    if (0.0f != d) {
        r = (x - lo) / d;
    }
    return r;
}

void fn_80491FE4(f32* v, f32 s) {
    v[0] *= s;
    v[2] *= s;
}

void fn_804916B0(u8* p, u32* begin, u32* end) {
    u32* it = begin;
    while (it <= end) {
        fn_8048FE60(p, *it);
        it++;
    }
}

void fn_8049167C(u8* p) {
    fn_80490F3C(p);
    fn_80490874(p);
}

void fn_8048F900(u8* p) {
    fn_8049AEBC(*(u8**)(p + 0x198) + (*(s32*)(p + 0xc) - 1) * 0xf8, *(u8**)(p + 0x30) + 0x8);
}

f32 fn_8048E2F8(u8* p) { return *(f32*)(p + 0x4); }

Vec3Copy fn_8048C968(const u8* p) { return **(Vec3Copy**)(*(u8**)(p + 0x30) + 0x4c); }

u8* fn_8048C878(u8* p) { return *(u8**)(p + 0x30) + 0x8; }

u8* fn_8048C86C(u8* p) { return *(u8**)(p + 0x30) + 0x50; }

void fn_8048C83C(const u8* p, f32* out) {
    u8* q = *(u8**)(p + 0x30);
    out[0] = *(f32*)(q + 0x50);
    out[1] = *(f32*)(q + 0x54);
    out[2] = *(f32*)(q + 0x58);
    out[0] *= 0.9f;
    out[2] *= 0.9f;
}

u8* fn_8048C82C(u8* p, s32 i) { return *(u8**)(p + 0x194) + i * 0x30; }

f32 fn_8048C750(u8* p) { return *(f32*)(*(u8**)(p + 0x64) + 0x8); }

f32 fn_8048C720(f32 a, f32 b) {
    f32 r = (a * b) / 0.01f;
    if (r > 1.0f) {
        r = 1.0f;
    }
    if (r < 0.25f) {
        return 0.0f;
    }
    return r;
}

f32 fn_8048C718() { return 1.0f; }

void fn_8048C6C4(const u8* p, f32* out) {
    u8* e = *(u8**)(p + 0x198) + (*(s32*)(p + 0xc) - 1) * 0xf8;
    f32* d = *(f32**)(*(u8**)(p + 0x30) + 0x48);
    f32 s = *(f32*)(e + 0xac);
    out[0] = d[6] * s + *(f32*)(e + 0xa0);
    out[1] = d[7] * s + *(f32*)(e + 0xa4);
    out[2] = d[8] * s + *(f32*)(e + 0xa8);
}

void fn_8048C66C(const u8* p, f32* out) {
    u8* e = *(u8**)(p + 0x198) + (*(s32*)(p + 0xc) - 1) * 0xf8;
    f32* d = *(f32**)(*(u8**)(p + 0x30) + 0x48);
    f32 s = -*(f32*)(e + 0xac);
    out[0] = d[6] * s + *(f32*)(e + 0xa0);
    out[1] = d[7] * s + *(f32*)(e + 0xa4);
    out[2] = d[8] * s + *(f32*)(e + 0xa8);
}

f32 fn_8048C664(f32 x) { return x * x; }

}  // extern "C"
