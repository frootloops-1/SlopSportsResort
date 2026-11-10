// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVec3f { f32 x, y, z; };
struct UnkVec3w { u32 x, y, z; };
struct UnkVObj { virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); };
void fn_80503570(void* p, void* a, u32 b);
void fn_80515E2C(void* p, void* a);
void* fn_8053A6F8(void* p, int i);
extern u8 lbl_806F2588;
extern UnkVec3f lbl_807D44D8;
extern UnkVec3f lbl_807D44E4;
extern UnkVec3f lbl_807D443C[];
extern void* lbl_806E02B8[];
f32 lbl_806F2594 = 87.0f;
f32 lbl_806F2598 = 10.0f;
void* fn_80503558(s32* p) { return lbl_806E02B8[*p]; }

void* fn_80503548(u8* p, int i) { return ((void**)(p + 0x1c))[i]; }

u32* fn_80503198(s32* p, u32 x) {
    if (p[0] == 8 || p[0] == 13) {
        u32* q = *(u32**)(p + 3);
        if (*q == x) {
            return q;
        }
    }
    return NULL;
}

BOOL fn_80503158(u8* p, u32 x) {
    for (int i = 0; i < *(s32*)(p + 4); i++) {
        if (x == **(u32**)(p + 8 + i * 4)) {
            return TRUE;
        }
    }
    return FALSE;
}

void fn_80503138(u32* p) {
    for (int i = 0; i < 4; i++) {
        p[i] = 0;
    }
}

void* fn_8050312C(void** p, int i) { return p[i]; }

// Deleting destructor of a class without a base destructor.
void* fn_80502D44(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80502870(u8* p) {
    for (int i = 0; i < 5; i++) {
        void* o = operator new(0xB0);
        if (o != NULL) {
            o = fn_8053A6F8(o, i);
        }
        *(void**)(p + 0xB8 + i * 4) = o;
    }
}

void fn_805027A4(u8* p, int i) {
    switch (i) {
    case 0:
        *(f32*)(p + 0x80) = 1.75f;
        break;
    case 1:
        *(f32*)(p + 0x80) = 1.8f;
        break;
    }
}

void fn_8050220C(u8* p) {
    for (int i = 0; i < 2; i++) {
        (*(UnkVObj**)(p + 0x84 + i * 4))->vf24();
    }
}

void fn_80502094(u8* p, void* a) {
    for (int i = 0; i < 2; i++) {
        fn_80515E2C(*(void**)(p + 0x84 + i * 4), a);
    }
}

BOOL fn_80501ECC(void*, const UnkVec3f* v) {
    if (__fabs(v->x) > lbl_806F2594 && __fabs(v->z) < lbl_806F2598) {
        return FALSE;
    }
    return TRUE;
}

void* fn_80501EB8(u8* p) { return *(void**)(p + 0x84 + *(s32*)(p + 0x78) * 4); }

void* fn_80501E10(u8* p, int i) { return ((void**)(p + 0x8c))[i]; }

u8* fn_80501934(void*, u8* a, s32* b) {
    if (*(s32*)a == 1) {
        if (*b == 0) {
            return a + 0x3C;
        }
        if (*b == 2) {
            return a + 0x48;
        }
    }
    return a + 0x3C;
}

void fn_80501830(u8* p, void* a) {
    for (int i = 0; i < 8; i++) {
        fn_80503570(*(void**)(p + 0x8C + i * 4), a, *(u32*)(p + 0x78));
    }
}

void* fn_80501820(u8* p, int i) { return ((void**)(p + 0xac))[i]; }

void fn_805017C4(UnkVec3f* out, u8* a, int i) {
    f32 s;
    if (*(s32*)(a + 0x78) == 0) {
        s = 0.85f;
    } else {
        s = -0.85f;
    }
    *out = lbl_807D443C[i];
    out->x *= s;
    out->z *= s;
}

void fn_805015B8(void*, UnkVec3f* a, UnkVec3f* b, f32* c) {
    *a = lbl_807D44D8;
    *b = lbl_807D44E4;
    *c = 150.0f;
}

BOOL fn_805013E0(void*, int i, BOOL b) {
    if (lbl_806F2588) {
        return b;
    }
    return i < 2;
}

f32 fn_805013A0(void*, int i, BOOL b) {
    f32 f = 0.0f;
    if (!lbl_806F2588) {
        return f;
    }
    if (b) {
        if (i < 3) {
            return -20.0f;
        }
        return -0.0f;
    }
    if (i > 2) {
        f = 20.0f;
    }
    return f;
}

} // extern "C"
