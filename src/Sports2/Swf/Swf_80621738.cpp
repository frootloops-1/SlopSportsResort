// Swf_80621738: Resort Swordplay unit 0x80621738-0x80624988 (Resort-only, no Wii Sports twin).
// Speed Slice objects: "分割オブジェ" (divided object, vtable 0x806ED698, name 0x806ED6AC) and
// "分割オブジェ管理" (divided object manager, vtable 0x806ED76C, name 0x806ED7DC); spark_cut_ring/wood/egg
// effects; object table 0x8068AF18 (0x6C-byte entries, strings 0x8068B714-0x8068BAF0).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_Words3 {
    u32 w0, w1, w2;
};

struct Unk_F4 {
    f32 v[4];
};

extern "C" {

void fn_8033EB04(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_8028FDE4(u8*, s32, s32);
void fn_80618908(void*, void*);
void fn_8061DB24(void*, u8*, s32);
void* fn_80621838(void*);
void fn_80623B8C(u8*);
void fn_806230FC(u8*, void*, void*, void*);
void fn_80615DB8(void*);
void fn_80653E5C(u8*, s32);
void fn_8061EAF8(void*, void**, s32);
void __destroy_arr(void*, void*, u32, u32);
void* fn_8061F100(void*, int);
extern u8 lbl_806ED698[];
extern char lbl_806ED6AC[];
extern void* lbl_806ED6C0[];
extern void* lbl_8068AE10[];
extern u8 lbl_8068AF18[];
extern Unk_F4 lbl_8068B6E0;
extern f32 lbl_806F3A18;
extern s32 lbl_806F0BF8;
extern u8 lbl_806EFF88[];

u8* fn_80624898(u8* p, int del) {
    if (p != NULL) {
        __destroy_arr(p + 0xa4, (void*)fn_8061F100, 0x98, 0x18);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80624860(u8* p) {
    PTR(p, 0x0) = operator new(4);
    return p;
}

void fn_80624820(u8* p) {
    u8* e = (u8*)PTR(p, 0x4);
    PTR(p, 0x10) = e;
    S32(p, 0x14) = 0;
    for (; e < (u8*)PTR(p, 0x8); e += 0xc) {
        PTR(e, 0x4) = e + 0xc;
    }
    PTR(e, 0x4) = NULL;
    PTR(p, 0x20) = PTR(p, 0x18);
}

void fn_80624400(u8* p, void* q, s32 k) {
    void* arr[7];
    u8* e = lbl_8068AF18 + k * 0x6c;
    s32 n;
    for (n = 0; n < 7; n++) {
        s32 idx = S32(e + n * 4, 0x14);
        if (idx == -1) {
            break;
        }
        arr[n] = p + idx * 0x98 + 0xa4;
    }
    fn_8061EAF8(q, arr, n);
}

void* fn_806243C0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80624380(u8* p) {
    fn_80653E5C(p, 1);
    *(u8**)p = lbl_806EFF88;
    return p;
}

void fn_80623F00() {}

void* fn_80623B3C(u8* p) {
    s32 idx = S32(p, 0xf38);
    void* obj = PTR(p + idx * 4, 0xef8);
    S32(p, 0xf38) = idx + 1;
    if (idx + 1 >= 16) {
        fn_80623B8C(p);
    }
    return fn_80621838(obj);
}

void fn_806235B0(u8* p) {
    if (lbl_806F0BF8 == 0) {
        fn_80615DB8(PTR(p, 0x18));
    }
}

void fn_806232A4() {}

void fn_806230B4(u8* p, void* a, void* b) { fn_806230FC(p, fn_80623B3C(p), a, b); }

void fn_80622ED4(void*, u8* q) {
    fn_8061DB24(PTR(q, 0x150), lbl_8068AF18 + S32(q, 0xf4) * 0x6c + 0x4c, 7);
}

void fn_80622120(void*, void* a, void* b) { fn_80618908(a, b); }

void fn_80622114(u8* p) { S32(p, 0xef0) = 0; }

f32 fn_80621EE8(s32 i) { return F32(lbl_8068AF18 + i * 0x6c, 0x4); }

f32 fn_80621E98(s32 i) {
    Unk_F4 t = lbl_8068B6E0;
    return t.v[S32(lbl_8068AF18 + i * 0x6c, 0x8)];
}

u32 fn_80621E80(s32 i) { return S32(lbl_8068AF18 + i * 0x6c, 0x10); }

u8 fn_80621E68(s32 i) { return U8(lbl_8068AF18 + i * 0x6c, 0x69); }

void fn_80621E64() {}

void fn_80621C84() {}

f32 fn_80621BA0() { return lbl_806F3A18; }

void* fn_80621824(s32 i) { return lbl_8068AE10[i]; }

void* fn_80621810(s32 i) { return lbl_806ED6C0[i]; }

Unk_Words3 fn_806217F4(const u8* src) { return *(const Unk_Words3*)(src + 0x8); }

char* fn_806217E8() { return lbl_806ED6AC; }

void* fn_806217A8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80621738(u8* p) {
    fn_8033EB04(p);
    *(u8**)p = lbl_806ED698;
    S32(p, 0x120) = 0;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x160);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x16c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x178);
    S32(p, 0x14c) = 0;
    fn_8028FDE4(p, 4, 0);
    return p;
}

}  // extern "C"
