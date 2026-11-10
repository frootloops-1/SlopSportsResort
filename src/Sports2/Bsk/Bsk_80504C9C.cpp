// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVObj { virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); };
void fn_80357194(void* p, void* state);
BOOL fn_803571A8(void* p, void* state);
BOOL fn_80533B08(void* p);
u8* fn_80506B4C(u8* p);
u8* fn_80506B14(u8* p);
void fn_8051F954(void* p);
void fn_8051FA6C(void* p);
void fn_802B5A34(void* p);
void fn_802B5A40(void* p);
void fn_802B7228(int id);
void fn_805115BC(void* p);
void fn_804FC0E4(void* p, int a, int b);
void fn_804FC050(void* p, int a);
void fn_8051155C(void* p, int a, int b);
f32 fn_80529DE4(void* p);
void fn_805043E4(void* p, BOOL b);
void fn_80535DF8(void* p);
void fn_80535F38(void* p);
void fn_80535E00(void* p);
void fn_80535F40(void* p);
extern u8* lbl_806F59E4; // GraphManager instance
extern f32 lbl_806F0C38;
void fn_80504A08(void* p, int del); // base dtor
void fn_802B7208();
void fn_80504194();
void fn_80533A2C();
void fn_80535EFC();

void fn_80508B10() {}

void fn_80508B0C() {}

// Deleting destructor of a class without a base destructor.
void* fn_80507E50(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor: only the base destructor runs.
void* fn_80507E00(void* p, int del) {
    if (p != NULL) {
        fn_80504A08(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80507BC8(void* p) { ((void (*)(void*))fn_80504194)(p); }

void* fn_80507A5C(u8* p) { return *(void**)(p + 0x90); }

void fn_8050771C(u8* p, BOOL b) {
    fn_805043E4(p, b);
    if (b) {
        fn_80535DF8(*(void**)(p + 0x328));
        fn_80535F38(*(void**)(p + 0x328));
    } else {
        fn_80535E00(*(void**)(p + 0x328));
        fn_80535F40(*(void**)(p + 0x328));
    }
}

void fn_8050767C(u8* p) { (*(UnkVObj**)(**(u8***)(fn_80506B4C(p) + 0x118) + 0x158))->vf28(); }

void* fn_80507658(u8* p) { return *(void**)(fn_80506B4C(p) + 0x128); }

void fn_80507650(u8* p) { ((void (*)(void*))fn_80533A2C)(*(void**)(p + 0x100)); }

void fn_80507648(u8* p) { ((void (*)(void*))fn_80535EFC)(*(void**)(p + 0x328)); }

f32 fn_805075EC() { return -1.0f; }

void fn_805075E8() {}

u8* fn_80506B4C(u8* p) {
    for (int i = 0; i < 2; i++) {
        u8* o = *(u8**)(p + 0x320 + i * 4);
        if (*(s32*)(o + 0x134) == 0) {
            return o;
        }
    }
    return NULL;
}

u8* fn_80506B14(u8* p) {
    for (int i = 0; i < 2; i++) {
        u8* o = *(u8**)(p + 0x320 + i * 4);
        if (*(s32*)(o + 0x134) == 1) {
            return o;
        }
    }
    return NULL;
}

f32 fn_80506814() { return -1.0f; }

void fn_80506698(u8* p) {
    *(f32*)(lbl_806F59E4 + 0x54) = fn_80529DE4(*(void**)(p + 0xFC));
    lbl_806F0C38 = fn_80529DE4(*(void**)(p + 0xFC));
    fn_802B5A40(*(void**)(p + 0x104));
}

void fn_80506318() { fn_8051155C(*(void**)(lbl_806F59E4 + 0x34), 1, 0); }

void fn_805062D4(u8* p) {
    if (fn_803571A8(p, p + 0x168)) {
        fn_80357194(p, p + 0x168);
    }
}

void fn_80505FFC() {
    fn_805115BC(*(void**)(lbl_806F59E4 + 0x38));
    fn_804FC0E4(lbl_806F59E4, 1, 0);
    fn_804FC050(lbl_806F59E4, 1);
}

void fn_80505D74() { ((void (*)(void*))fn_802B7208)((void*)90); }

void fn_80505AE8(u8* p) {
    fn_80506B4C(p)[0x138] = 0;
    fn_80506B14(p)[0x138] = 0;
    fn_80506B4C(p)[0x139] = 0;
    fn_80506B14(p)[0x139] = 0;
}

void fn_8050541C(u8* p) {
    *(f32*)(lbl_806F59E4 + 0x54) = 1.0f;
    lbl_806F0C38 = 1.0f;
    fn_802B5A34(*(void**)(p + 0x104));
}

void fn_80505408(u8* p) {
    *(u32*)(p + 0x344) = 0;
    *(u32*)(p + 0x110) = 0;
    fn_802B7228(0x45);
}

void fn_8050529C(u8* p) {
    *(f32*)(lbl_806F59E4 + 0x54) = 1.0f;
    lbl_806F0C38 = 1.0f;
    fn_802B5A34(*(void**)(p + 0x104));
}

void fn_8050524C(u8* p) {
    fn_8051F954(fn_80506B4C(p));
    fn_8051FA6C(fn_80506B4C(p));
    fn_8051FA6C(fn_80506B14(p));
    *(u32*)(p + 0x10C) = 0;
}

void fn_8050522C(u8* p) {
    if (++*(s32*)(p + 0x10C) > 60) {
        fn_80357194(p, p + 0x2C8);
    }
}

void fn_805051DC(u8* p) {
    fn_8051F954(fn_80506B4C(p));
    fn_8051FA6C(fn_80506B4C(p));
    fn_8051FA6C(fn_80506B14(p));
    *(u32*)(p + 0x10C) = 0;
}

void fn_80505184(u8* p) {
    p[0x118] = 0;
    (*(s32*)(p + 0x10C))++;
    if (fn_80533B08(*(void**)(p + 0x100))) {
        fn_80357194(p, p + 0x2C8);
    }
}

void fn_80504FE8(u8* p) {
    *(u32*)(p + 0x110) = 0;
    *(u32*)(p + 0x10C) = 0;
}

} // extern "C"
