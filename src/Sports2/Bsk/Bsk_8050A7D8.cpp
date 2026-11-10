// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

// Placeholder for an object called through its vtable (slot = byte offset in the vtable).
struct UnkVObj {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6C();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
};

extern "C" {

void fn_8050AAD8(void* p, s32 id);
void fn_8050AB54(void* p, void* a);
void fn_805193C8(void* p);
void fn_8050BCB8(u8* p);
void fn_8050B414(u8* p);
extern s32 lbl_806F2648;
extern s32 lbl_806F264C;
void fn_8050AD5C();
void fn_8050B07C();
void fn_8050B1B4();
void fn_80519260();
void fn_8051DA80();

f32 fn_8050C1F8() { return 1.0f; }

f32 fn_8050C1F0() { return 1.0f; }

int fn_8050C1E8() { return 0; }

f32 fn_8050C1E0() { return 1.0f; }

f32 fn_8050C1D8() { return 1.0f; }

void fn_8050C1D4() {}

f32 fn_8050C1CC() { return 0.0f; }

f32 fn_8050C1C4() { return 1.0f; }

f32 fn_8050C1BC() { return 1.0f; }

// Deleting destructor of a class without a base destructor.
void* fn_8050BE20(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8050BE1C() {}

void fn_8050BCB8(u8* p) {
    for (int i = 0; i < 3; i++) {
        ((f32*)(p + 0x94))[i] = 0.0f;
    }
}

void fn_8050BCA4(u8* p) {
    *(f32*)(p + 0xC4) = 0.0f;
    *(u32*)(p + 0xC8) = 0;
}

void fn_8050BBE0(u8* p) { (*(UnkVObj**)(p + 0x10))->vf14(); }

void fn_8050BBCC(u8* p) { (*(UnkVObj**)(p + 0x10))->vf18(); }

void fn_8050BBA8(u8* p) {
    if (*(s32*)(p + 4) == 0) {
        (*(UnkVObj**)(p + 0x10))->vf1C();
    }
}

void fn_8050BBA4() {}

int fn_8050BB9C() { return 0; }

void fn_8050BB7C(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 8) = 1;
    } else {
        *(u32*)(p + 8) = 0;
    }
}

BOOL fn_8050BB68(u8* p) { return *(s32*)(p + 0x8) == 1; }

void fn_8050BB58(u8* p) {
    p[0x8C] = 0;
    p[0x8D] = 0;
    fn_8050BCB8(p);
}

void fn_8050BB54(void* p) { ((void (*)(void*))fn_8050B1B4)(p); }

void fn_8050BB20(u8* p) {
    fn_8050BCB8(p);
    p[0x8F] = 0;
}

void fn_8050BB1C(void* p) { ((void (*)(void*))fn_8050B07C)(p); }

void fn_8050BAD0(u8* p, void* a) {
    fn_8050BCB8(p);
    fn_8050AB54(p, a);
    p[0x8A] = 1;
    fn_805193C8(*(void**)(p + 0x14));
}

void fn_8050BA50(void* p, u8* q) { ((void (*)(void*,void*))fn_80519260)(p, *(void**)(q + 0x14)); }

void fn_8050BA4C(u8* p) { fn_8050BCB8(p); }

void fn_8050BA48(void* p) { ((void (*)(void*))fn_8050AD5C)(p); }

u8 fn_8050B930(u8* p) { return p[0x88]; }

u8 fn_8050B928(u8* p) { return p[0x8b]; }

u8 fn_8050B920(u8* p) { return p[0x8c]; }

u8 fn_8050B918(u8* p) { return p[0x8d]; }

u8 fn_8050B910(u8* p) { return p[0x8e]; }

void* fn_8050B908(u8* p) { return *(void**)(p + 0xa0); }

u8 fn_8050B900(u8* p) { return p[0x89]; }

u8 fn_8050B8F8(u8* p) { return p[0x8f]; }

f32 fn_8050B7AC() { return 32.0f; }

void fn_8050B7A8(void* p) { ((void (*)(void*))fn_8051DA80)(p); }

void fn_8050B4C0(void* p) { fn_8050AAD8(p, 1); }

void fn_8050B4B8(void* p) { fn_8050AAD8(p, -2); }

int fn_8050B484() { return 4; }

void fn_8050B438(u8* p) {
    fn_8050B414(p);
    for (int i = 0; i < 5; i++) {
        p[0xFC + i] = 0;
    }
}

void fn_8050B414(u8* p) {
    *(u32*)(p + 0xE4) = 0;
    *(s32*)(p + 0xE8) = -999;
    *(u32*)(p + 0xEC) = 0;
    *(u32*)(p + 0xF0) = 0;
    *(u32*)(p + 0xF4) = 0;
    *(u32*)(p + 0xF8) = 0;
}

u8 fn_8050B320(u8* p) { return p[0xff]; }

void fn_8050B2E0(u8* p, f32 f, s32 n) {
    if (f >= 10.0f && n >= 20) {
        p[0xFE] = 1;
        if (f >= 15.0f && n >= 30) {
            p[0x100] = 1;
        }
    }
}

void fn_8050AC34(u8* p, BOOL b) {
    *(f32*)(p + 0xB4) = 0.0f;
    *(f32*)(p + 0xB8) = 0.0f;
    *(f32*)(p + 0xBC) = 0.0f;
    *(u32*)(p + 0xC0) = 0;
    if (!b) {
        fn_8050AAD8(p, lbl_806F264C);
    } else {
        fn_8050AAD8(p, lbl_806F2648);
    }
}

} // extern "C"
