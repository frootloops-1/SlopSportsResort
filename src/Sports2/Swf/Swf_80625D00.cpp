// Swf_80625D00: Resort Swordplay unit 0x80625D00-0x80627ED0 (Resort-only, no Wii Sports twin).
// "モーション" (motion): vtables 0x806ED948/0x806ED95C, name 0x806ED970; two motion tables at 0x806ED848.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_Words3 {
    u32 w0, w1, w2;
};

extern "C" {

void fn_8032349C(u8*);
void fn_80627A60(void*, void*, void*, f32);
extern u8 lbl_806ED848[];
extern u8 lbl_806ED95C[];
extern char lbl_806ED970[];
extern char lbl_806F3A44[4];
extern void* lbl_806F6028[2];
extern f32 lbl_807D0318[3];

Unk_Words3 fn_80627D04(const u8* src) { return *(const Unk_Words3*)(src + 0x18); }

char* fn_80627CFC() { return lbl_806F3A44; }

char* fn_80627CF0() { return lbl_806ED970; }

void* fn_80627CB0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80627C70(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// MATCH-PENDING (R17) #19: dont_inline region keeps this callee out of line
#pragma push
#pragma dont_inline on
void* fn_80627C34(void* q) {
    u8* p = (u8*)q;
    fn_8032349C(p);
    *(u8**)p = lbl_806ED95C;
    return p;
}
#pragma pop

void fn_80627BAC(u8* p, void* q, f32 f) {
    void* a;
    void* b;
    f32 t;
    if (f >= 90.0f) {
        t = (f - 90.0f) / 90.0f;
        a = PTR(p, 0xc);
        b = PTR(p, 0x8);
    } else if (f >= 0.0f) {
        t = f / 90.0f;
        a = PTR(p, 0x8);
        b = PTR(p, 0xc);
    } else if (f >= -90.0f) {
        t = (90.0f + f) / 90.0f;
        a = PTR(p, 0xc);
        b = PTR(p, 0x8);
    } else {
        t = (180.0f + f) / 90.0f;
        a = PTR(p, 0x8);
        b = PTR(p, 0xc);
    }
    fn_80627A60(q, a, b, t);
}

void fn_806279D8() {
    u8* t = lbl_806ED848;
    void* q = operator new(0x10);
    if (q != NULL) {
        q = fn_80627C34(q);
    }
    lbl_806F6028[0] = q;
    PTR(q, 0x8) = t;
    PTR(q, 0xc) = t + 0x40;
    q = operator new(0x10);
    if (q != NULL) {
        q = fn_80627C34(q);
    }
    lbl_806F6028[1] = q;
    PTR(q, 0x8) = t + 0x80;
    PTR(q, 0xc) = t + 0xc0;
}

void fn_80626458(u8* p) {
    PTR(PTR(p, 0x1e0), 0x7c) = NULL;
    PTR(PTR(p, 0x1e4), 0x7c) = NULL;
    F32(p, 0x178) = lbl_807D0318[0];
    F32(p, 0x17c) = lbl_807D0318[1];
    F32(p, 0x180) = lbl_807D0318[2];
    F32(p, 0x184) = lbl_807D0318[0];
    F32(p, 0x188) = lbl_807D0318[1];
    F32(p, 0x18c) = lbl_807D0318[2];
    F32(p, 0x190) = 0.0f;
    F32(p, 0x194) = 0.0f;
    S32(p, 0x168) = 1;
}

BOOL fn_80625D00(u8* p, f32 f);

BOOL fn_8062644C(u8* p) { return fn_80625D00((u8*)PTR(p, 0x1e0), -70.0f); }

BOOL fn_80626440(u8* p) { return fn_80625D00((u8*)PTR(p, 0x1e4), -70.0f); }

f32 fn_80626438(u8* p) { return F32(p, 0xe0); }

static inline f32 normAngle(f32 a) {
    while (a > 180.0f) {
        a -= 360.0f;
    }
    while (a < -180.0f) {
        a += 360.0f;
    }
    return a;
}

BOOL fn_80625D00(u8* p, f32 f) {
    f32 a = normAngle(f - F32(p, 0x44));
    if (a <= 0.0f) {
        a += 360.0f;
    }
    f32 b = normAngle(F32(p, 0x40) - f);
    if (b < 0.0f) {
        b += 360.0f;
    }
    return a + b < 180.0f;
}

}  // extern "C"
