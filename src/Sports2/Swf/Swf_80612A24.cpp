// Swf_80612A24: Resort Swordplay unit 0x80612A24-0x80614864 (Resort-only, no Wii Sports twin).
// CPU motion: a state machine with a 8-entry pointer-to-member table (0x806ED368) and the
// "CPUモーション管理" (CPU motion manager) class (vtable 0x806ED3C8, name 0x806ED3DC).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_PtmfHost {};
typedef void (Unk_PtmfHost::*Unk_StateFn)();

extern "C" {

void fn_8060FF30(void*, u8*, f32, f32);
void fn_8060FDC8(void*, u8*, f32, f32);
void fn_80613E10(u8*, f32, s32, s32);
f32 fn_80326720(u8*, u8*);
void fn_8032349C(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_80369F18(u8*, s32);
void* fn_80610428(void*);
extern f32 lbl_806FB390;
extern u8* lbl_806F5FF0;
extern f32 lbl_806F39A8[2];
extern Unk_StateFn lbl_806ED368[];
extern u8 lbl_806ED3C8[];
extern char lbl_806ED3DC[];

static inline void setState(u8* p, s32 s) {
    S32(p, 0x10) = s;
    F32(p, 0x14) = 0.0f;
}

char* fn_80614858() { return lbl_806ED3DC; }

void* fn_80614818(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80614708(u8* p, void* a) {
    fn_8032349C(p);
    *(u8**)p = lbl_806ED3C8;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x30);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x3c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x48);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x54);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x60);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x6c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x78);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xa4);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xb0);
    __ct__Q34nw4r4math4VEC3Fv(p + 0xbc);
    fn_80369F18(p + 0xd0, 3);
    fn_80369F18(p + 0xf0, 3);
    fn_80369F18(p + 0x134, 3);
    fn_80369F18(p + 0x154, 3);
    void* q = operator new(8);
    if (q != NULL) {
        q = fn_80610428(q);
    }
    PTR(p, 0x8) = q;
    PTR(p, 0xc) = a;
    F32(p, 0xe8) = 0.5f;
    F32(p, 0x108) = 0.5f;
    F32(p, 0x14c) = 0.5f;
    F32(p, 0x16c) = 0.5f;
    return p;
}

struct Unk_S24 {
    u32 w[9];
};

void fn_806144C4(u8* p, Unk_S24* src) {
    Unk_S24* q = (Unk_S24*)(p + 0x9e0);
    do {
        q->w[0] = src->w[0];
        q->w[1] = src->w[1];
        q->w[2] = src->w[2];
        q->w[3] = src->w[3];
        q->w[4] = src->w[4];
        q->w[5] = src->w[5];
        q->w[6] = src->w[6];
        q->w[7] = src->w[7];
        q->w[8] = src->w[8];
        q--;
    } while (q >= (Unk_S24*)(p + 0x194));
    *(Unk_S24**)(p + 0xa04) = (Unk_S24*)(p + 0x194);
}

void fn_80614478(u8* p) {
    F32(p, 0x14) += F32(lbl_806F5FF0, 0x1bc);
    (((Unk_PtmfHost*)p)->*lbl_806ED368[S32(p, 0x10)])();
}

void fn_8061398C(u8* p) { fn_80613E10(p, F32(p, 0xc8), 1, 1); }

static inline f32 normAngle(f32 a) {
    while (a > 180.0f) {
        a -= 360.0f;
    }
    while (a < -180.0f) {
        a += 360.0f;
    }
    return a;
}

void fn_806138EC(u8* p) {
    F32(p, 0x8c) = normAngle(5.0f * F32(p, 0x190) * F32(lbl_806F5FF0, 0x1bc) + F32(p, 0x8c));
    fn_8060FF30(PTR(p, 0x8), p + 0x3c, F32(p, 0x8c), F32(p, 0x90));
    fn_80613E10(p, F32(p, 0xc8), 0, 0);
}

void fn_80613838(u8* p) {
    F32(p, 0x90) = F32(p, 0x90) - F32(p, 0x98) * F32(lbl_806F5FF0, 0x1bc);
    if (F32(p, 0x90) < F32(p, 0x94)) {
        F32(p, 0x90) = F32(p, 0x94);
    }
    fn_8060FF30(PTR(p, 0x8), p + 0x3c, F32(p, 0x8c), F32(p, 0x90));
    fn_80613E10(p, 1.0f, 1, 1);
    if (F32(p, 0x90) == F32(p, 0x94) && fn_80326720(p + 0x54, p + 0x30) * lbl_806FB390 <= 45.0f) {
        S32(p, 0x17c) = 1;
    }
}

void fn_80613600(u8* p) {
    if (F32(p, 0x14) >= 10.0f) {
        setState(p, 0);
    }
    fn_80613E10(p, 1.0f, 0, 0);
}

void fn_80613004(u8* p) {
    fn_80613E10(p, 1.0f, 0, 0);
    f32 a = fn_80326720(p + 0x6c, p + 0x48) * lbl_806FB390;
    f32 b = fn_80326720(p + 0x78, p + 0x54) * lbl_806FB390;
    a = (a >= b) ? a : b;
    if (a <= 90.0f) {
        S32(p, 0x174) = 1;
    }
}

void fn_80612F5C(u8* p) {
    f32 v = F32(p, 0x90);
    if (v >= 0.0f) {
        F32(p, 0x90) = v - lbl_806F39A8[0];
        if (F32(p, 0x90) < 0.0f) {
            F32(p, 0x90) = 0.0f;
            S32(p, 0x178) = 1;
        }
    } else {
        F32(p, 0x90) = v + lbl_806F39A8[0];
        if (F32(p, 0x90) > 0.0f) {
            F32(p, 0x90) = 0.0f;
            S32(p, 0x178) = 1;
        }
    }
    fn_8060FF30(PTR(p, 0x8), p + 0x3c, F32(p, 0x8c), F32(p, 0x90));
    fn_80613E10(p, 0.0f, 0, 0);
}

void fn_80612F48(u8* p) { setState(p, 0); }

void fn_80612F2C(u8* p, f32 a, f32 b, f32 c) {
    F32(p, 0xc8) = c;
    F32(p, 0x8c) = 180.0f * a;
    fn_8060FDC8(PTR(p, 0x8), p + 0x3c, a, b);
}

void fn_80612ED0(u8* p, f32 a) {
    F32(p, 0x8c) = normAngle(a);
    fn_8060FF30(PTR(p, 0x8), p + 0x3c, F32(p, 0x8c), F32(p, 0x90));
}

void fn_80612F20(u8* p, f32 a) { fn_80612ED0(p, F32(p, 0x8c) + a); }

void fn_80612EB0(u8* p, f32 a, f32 b) {
    F32(p, 0xc8) = b;
    F32(p, 0x90) = 0.0f;
    F32(p, 0x190) = a;
    setState(p, 1);
}

void fn_80612E44(u8* p, f32 a, f32 b) {
    F32(p, 0x98) = a * 9.0f + 1.0f;
    F32(p, 0x94) = F32(p, 0x90) - (b * 90.0f + 30.0f);
    if (F32(p, 0x8c) > 135.0f) {
        F32(p, 0x8c) = 135.0f;
    } else if (F32(p, 0x8c) < -135.0f) {
        F32(p, 0x8c) = -135.0f;
    }
    S32(p, 0x17c) = 0;
    setState(p, 2);
}

void fn_80612CC0(u8* p) {
    if (S32(p, 0x10) != 5) {
        if (F32(p, 0x8c) >= 0.0f) {
            F32(p, 0x110) = F32(p, 0x8c) - 90.0f;
        } else {
            F32(p, 0x110) = 90.0f + F32(p, 0x8c);
        }
        if (F32(p, 0x8c) <= 0.0f) {
            S32(p, 0x114) = 1;
        } else {
            S32(p, 0x114) = 0;
        }
        F32(p, 0x11c) = 0.0f;
        F32(p, 0x118) = 0.0f;
        S32(p, 0x130) = 0;
        setState(p, 5);
        F32(p, 0x120) = 0.0f;
    }
}

void fn_80612A40(u8* p) {
    if (S32(p, 0x114) != 0) {
        F32(p, 0x8c) = F32(p, 0x110) - 90.0f;
    } else {
        F32(p, 0x8c) = 90.0f + F32(p, 0x110);
    }
    while (F32(p, 0x8c) > 180.0f) {
        F32(p, 0x8c) -= 360.0f;
    }
    while (F32(p, 0x8c) < -180.0f) {
        F32(p, 0x8c) += 360.0f;
    }
    fn_8060FF30(PTR(p, 0x8), p + 0x3c, F32(p, 0x8c), 0.0f);
    S32(p, 0x174) = 0;
    setState(p, 6);
}

void fn_80612A24(u8* p) {
    S32(p, 0x178) = 0;
    setState(p, 7);
}

}  // extern "C"
