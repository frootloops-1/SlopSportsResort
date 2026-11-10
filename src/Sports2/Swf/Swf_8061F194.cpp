// Swf_8061F194: Resort Swordplay unit 0x8061F194-0x80621738 (Resort-only, no Wii Sports twin).
// Speed Slice cut object (WS2_swf_hit_stab effect); state switches use jump tables 0x806ED590-0x806ED658.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

extern "C" {

f32 fn_8061EA64(void*);
void fn_8061E53C(void*);
void fn_80621BA8(void*, void*);
BOOL fn_8061E5A0(void*);
void fn_8061E87C(void*);
void fn_806209C0(u8*, u8*);
void fn_8061E910(void*, void*);
void fn_8061E6FC(void*);
void fn_8061E79C(void*);
void fn_8033E500(u8*);
void fn_8061E45C(void*, u8*);
void fn_8061E390(void*, u8*);
void* fn_8061ECCC(void*, void*, s32);

void fn_806216EC(u8* p) {
    void* q = operator new(0x6c);
    if (q != NULL) {
        q = fn_8061ECCC(q, PTR(PTR(p, 0x14c), 0x1c), 7);
    }
    PTR(p, 0x150) = q;
}

void fn_80621280() {}

void fn_80620DC0(u8* p) {
    if (S32(p, 0x104) != 0 && S32(p, 0x128) != 0) {
        fn_8033E500(p);
    }
    fn_8061E45C(PTR(p, 0x150), p + 0x8);
    fn_8061E390(PTR(p, 0x150), p + 0x20);
}

void fn_80620DBC() {}

void fn_806207FC(u8* p) { fn_8061E79C(PTR(p, 0x150)); }

void fn_806207F4(u8* p) { fn_8061E6FC(PTR(p, 0x150)); }

void fn_80620444() {}

void fn_80620440() {}

void fn_8061FFC8(u8* p, u8* q) {
    fn_806209C0(p, q);
    fn_8061E910(PTR(p, 0x150), PTR(q, 0x150));
}

void fn_8061FFC0(u8* p) { fn_8061E87C(PTR(p, 0x150)); }

BOOL fn_8061FBA8(u8* p) { return fn_8061E5A0(PTR(p, 0x150)); }

void fn_8061FB3C(u8* p) {
    fn_8061E53C(PTR(p, 0x150));
    S32(p, 0xfc) = 0;
    for (s32 i = 0; i < 7; i++) {
        if (PTR(p + i * 4, 0x12c) != NULL) {
            fn_80621BA8(PTR(p, 0x14c), PTR(p + i * 4, 0x12c));
            PTR(p + i * 4, 0x12c) = NULL;
        }
    }
}

void fn_8061FB38() {}

BOOL fn_8061FA50(u8* p) { return S32(p, 0x10c) > 3; }

void fn_8061FA20(u8* p, s32 n) {
    if (n < 0) {
        n = 120;
    }
    if (n > 0) {
        S32(p, 0x110) = n;
        S32(p, 0x100) = 1;
    } else {
        S32(p, 0x100) = 2;
    }
}

f32 fn_8061FA18(u8* p) { return fn_8061EA64(PTR(p, 0x150)); }

u8* fn_8061FA0C(u8* p) { return (u8*)PTR(p, 0x150) + 0x54; }

void fn_8061F96C(u8* p, f32 f) { F32(PTR(p, 0x150), 0x3c) = f; }

f32 fn_8061F960(u8* p) { return F32(PTR(p, 0x150), 0x3c); }

s32 fn_8061F958() { return 4; }

}  // extern "C"
