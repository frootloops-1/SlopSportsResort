// Swf_8062CB80: Resort Swordplay unit 0x8062CB80-0x8062E938 (Resort-only, no Wii Sports twin).
// "薪割りトレーナー" (Speed Slice trainer): vtables 0x806EDC08 (state table) / 0x806EDC74, name 0x806EDCB0,
// arrow_icon.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_PtmfHost {};
typedef void (Unk_PtmfHost::*Unk_StateFn)();

extern "C" {

void fn_8064F9C8(void*);
void fn_8064FB10(void*);
void fn_8064FEE0(void*);
void fn_8064F2F0(void*, BOOL);
void fn_8064F338(void*);
void fn_8062C44C(void*, s32);
void fn_8062C47C(void*, s32, s32, s32);
void fn_8065078C(void*, s32);
void fn_80328488(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);
void* fn_80650308(void*);
void* fn_80602F30(const char*);
extern u8* lbl_806F5FF0;
extern Unk_StateFn lbl_806EDC08[];
extern u8 lbl_806EDC74[];
extern char lbl_806EDCB0[];
extern char lbl_8068BD50[];

char* fn_8062E8B8() { return lbl_806EDCB0; }

void* fn_8062E878(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8062E7E0(u8* p) {
    fn_80328488(p);
    *(u8**)p = lbl_806EDC74;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x20);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x2c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x38);
    void* q = operator new(0xf0);
    if (q != NULL) {
        q = fn_80650308(q);
    }
    PTR(p, 0x10) = q;
    for (s32 i = 0; i < 2; i++) {
        PTR(p + i * 4, 0x80) = fn_80602F30(lbl_8068BD50);
    }
    return p;
}

void fn_8062E7D8(u8* p) { fn_8064FEE0(PTR(p, 0x10)); }

void fn_8062E5C8(u8* p) {
    S32(p, 0x44) = S32(p, 0x44) + 1;
    (((Unk_PtmfHost*)p)->*lbl_806EDC08[S32(p, 0x48)])();
    if (S32(p, 0xb4) > 0) {
        if (--S32(p, 0xb4) == 0) {
            fn_8064F2F0(PTR(p, 0x10), S32(p, 0x74) == 0);
        }
    }
}

void fn_8062E5B8(u8* p) { S32(p, 0x70) = S32(p, 0x70) + 1; }

void fn_8062E1C8() {}

static inline f32 clampMax(f32 v, f32 m) {
    if (v > m) {
        v = m;
    }
    return v;
}

void fn_8062DF8C(u8* p) {
    F32(p, 0x90) = clampMax(0.07f + F32(p, 0x90), 1.0f);
    F32(PTR(p, 0x50), 0x108) = F32(p, 0x90);
    F32(PTR(p, 0x54), 0x108) = F32(p, 0x90);
    if (S32(p, 0x44) >= S32(p, 0xa4)) {
        fn_8064F338(PTR(p, 0x10));
        S32(p, 0x48) = 3;
        S32(p, 0x44) = 0;
    }
}

void fn_8062D5E4(u8* p) {
    if (S32(p, 0x44) >= S32(p, 0x9c)) {
        fn_8062C47C(PTR(lbl_806F5FF0, 0x180), S32(p, 0x74), S32(p, 0xb0), S32(p + S32(p, 0x74) * 0xc, 0x60));
        fn_8064F2F0(PTR(p, 0x10), S32(p, 0x74) == 0);
        fn_8065078C(PTR(lbl_806F5FF0, 0x19c), 0);
        fn_8065078C(PTR(lbl_806F5FF0, 0x19c), 1);
        S32(p, 0x48) = 8;
        S32(p, 0x44) = 0;
    }
}

void fn_8062D4E0(u8* p) { fn_8064FB10(PTR(p, 0x10)); }

void fn_8062D4D8(u8* p) { fn_8064F9C8(PTR(p, 0x10)); }

void fn_8062D1AC(u8* p) {
    S32(p, 0x4c) = 1;
    S32(p, 0x48) = 1;
    S32(p, 0x44) = 25;
}

void fn_8062D020(u8* p, s32 i, void* v) {
    if (v == PTR(p + i * 4, 0x50)) {
        S32(p + i * 0xc, 0x5c) = 2;
        fn_8062C44C(PTR(lbl_806F5FF0, 0x180), i);
        PTR(p + i * 4, 0x50) = NULL;
        S32(p + i * 4, 0x88) = 0;
    }
}

f32 fn_8062CD88(u8*, s32 n, f32 d) {
    switch (n) {
    case 0:
        return 45.0f;
    case 1:
        return 90.0f;
    case 2:
        return 135.0f;
    case 3:
        return 180.0f;
    case 4:
        return -135.0f;
    case 5:
        return -90.0f;
    case 6:
        return -45.0f;
    }
    return d;
}

void fn_8062CD7C(u8* p, s32 v) { S32(PTR(p, 0x10), 0xec) = v; }

s32 fn_8062CD70(u8* p) { return S32(PTR(p, 0x10), 0xec); }

}  // extern "C"
