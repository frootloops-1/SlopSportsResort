#pragma defer_codegen off
// RPBow_80323790: Bowling lane physics (Resort counterpart of ogws RPBow_80323790):
// lane-triangle setup, physics parameter init, pin/ball helpers.
//
// Written in ASCENDING address order with `#pragma defer_codegen off`: callees
// defined after their callers stay out of line, as in the original. Raw
// offsets are kept; the owning Bowling object types are not reconstructed.

#include <types.h>

namespace nw4r { namespace math {
struct VEC3 {
    f32 x, y, z;
    VEC3();
    VEC3(f32, f32, f32);
    VEC3& operator=(const VEC3&);
    VEC3 operator+(const VEC3&) const;
    VEC3 operator-(const VEC3&) const;
};
struct MTX34 {
    f32 m[12];
    MTX34(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
};
void MTX34Identity(MTX34*);
VEC3* VEC3Cross(VEC3*, const VEC3*, const VEC3*);
f32 VEC3Dot(const VEC3*, const VEC3*);
}}  // namespace nw4r::math
using nw4r::math::VEC3;
using nw4r::math::MTX34;

namespace EGG {
struct Vector3f;
}
namespace EGG {
struct Vector3f {
    f32 x, y, z;
    // __ct__Q23EGG8Vector3fFfff (0x801C052C): out-of-line copy of Vector3f(f32, f32, f32) in another unit.
    Vector3f(f32 x, f32 y, f32 z);
    Vector3f(const VEC3& v);
    ~Vector3f();
};
}  // namespace EGG

struct Words8 { s32 a; f32 f0, f1, f2, f3, f4, f5, f6; };
static inline void CopyW8(Words8* d, const Words8* s) { *d = *s; }
struct Words5 { s32 a, b, c, d, e; };
struct Words61 { s32 w[61]; };
static inline void CopyW61(Words61* d, const Words61* s) { *d = *s; }
struct Words2 { s32 w[2]; };
struct Words3 { s32 w[3]; };
struct Words12 { s32 w[12]; };
struct Words63 { s32 w[63]; };
static inline void CopyW2(Words2* d, const Words2* s) { *d = *s; }
static inline void CopyW3(Words3* d, const Words3* s) { *d = *s; }
static inline void CopyW12(Words12* d, const Words12* s) { *d = *s; }
static inline void CopyW63(Words63* d, const Words63* s) { *d = *s; }
struct WordsN8 { s32 w[8]; };
static inline void CopyWN8(WordsN8* d, const WordsN8* s) { *d = *s; }
static inline void CopyW5(Words5* d, const Words5* s) { *d = *s; }
struct V3 { s32 x; f32 y, z; };
static inline void CopyV3(V3* d, const V3* s) { *d = *s; }

struct LaneHead {
    void* vtbl;
    u8** pins;
    u8 pad8[0x10];
    s32 numPins;
};
#define PINS(ctx) (((LaneHead*)(ctx))->pins)
#define NPINS(ctx) (((LaneHead*)(ctx))->numPins)
#define F32AT(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32AT(p, o) (*(s32*)((u8*)(p) + (o)))

namespace Bowling {
struct LaneContext;
void fn_804E5100(LaneContext*);
int UpdatePinSetter(LaneContext*);
void ResetPinSetterState(LaneContext*, u8);
}
namespace EGG {
class Heap {
public:
    static Heap* sCurrentHeap;
};
}

class RPSysEffect {
public:
    RPSysEffect(const char*, u32);
    void forceKill();
    void create();
    void update();
    void setPos(const VEC3&);

private:
    u8 mData[0x118];
};

struct VObj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
};

struct BallObj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual const VEC3* GetPos();               // 0x30
    virtual void SetPos(const EGG::Vector3f&);  // 0x34
    virtual const VEC3* GetVel();               // 0x38
    virtual void SetVel(const EGG::Vector3f&);  // 0x3C
    virtual void f14();
    virtual void f15();
    virtual const VEC3* GetAxisX();             // 0x48
    virtual void SetAxisX(const EGG::Vector3f&);
    virtual const VEC3* GetAxisY();             // 0x50
    virtual void SetAxisY(const EGG::Vector3f&);
    virtual const VEC3* GetAxisZ();             // 0x58
    virtual void SetAxisZ(const EGG::Vector3f&);
};

// No function in this unit is inlined into another (non-`inline` helpers stay out of line);
// `dont_inline off` regions below only admit the struct-copy operators and marked helpers.
#pragma dont_inline on

extern "C" {

extern u8 gBowlingPhysicsData__7Bowling[0x2F8];  // ogws gBowlingPhysicsData__7Bowling

void __ct__Q34nw4r4math4VEC3Ffff(void*, f32, f32, f32);
void* memset(void*, int, unsigned long);
void fn_802F280C(VEC3* dst, const VEC3* src);
void fn_8021D094(VEC3* dst, const VEC3* src, f32 s);
void fn_80373570(u32 color, s32, s32, s32, s32);
void fn_8037332C();
void fn_8037334C(f32 x, f32 y, f32 z);
void fn_804C457C(void* p);
f32 fn_80204FEC(const VEC3* v);
VEC3 fn_80204168(const VEC3* v);

int fn_804D952C(u8* p);
f32* fn_804D9524(u8* p);

VEC3 fn_804D93EC(u8* ctx) {
    f32 maxZ = -9999.0f;
    f32 minX = 9999.0f;
    f32 maxX = maxZ;
    for (s32 i = 0; i < NPINS(ctx); i++) {
        if (fn_804D952C(PINS(ctx)[i])) {
            if (maxX < fn_804D9524(PINS(ctx)[i])[0]) maxX = fn_804D9524(PINS(ctx)[i])[0];
            if (minX > fn_804D9524(PINS(ctx)[i])[0]) minX = fn_804D9524(PINS(ctx)[i])[0];
            if (maxZ < fn_804D9524(PINS(ctx)[i])[2]) maxZ = fn_804D9524(PINS(ctx)[i])[2];
        }
    }
    return VEC3(0.5f * (minX + maxX), 0.0f, maxZ);
}

f32* fn_804D9524(u8* p) { return (f32*)(p + 4); }
int fn_804D952C(u8* p) { return p[0x26D]; }

int fn_804D9534(void*, const VEC3* p, const u8* g) {
    if (p->z < F32AT(g, 0x10)) return 0;
    if (p->x > F32AT(g, 0x50) && p->x < F32AT(g, 0x54) && p->z > F32AT(g, 0x58) && p->z < F32AT(g, 0x5C)) return 0;
    return 1;
}

struct LaneTri {
    VEC3 v[3];
    VEC3 n;
    VEC3 e[3];
    f32 d;
};
LaneTri lbl_807D3EF0[4];

void fn_804D9590() {
    const u8* g = gBowlingPhysicsData__7Bowling;
    const f32 s = 10.0f * F32AT(g, 0x14);
#define A F32AT(g, 0x2E4)
#define B F32AT(g, 0x2DC)
#define C F32AT(g, 0x2D8)
#define D F32AT(g, 0x2E8)
#define E F32AT(g, 0x2E0)
    f32 pts[4][9] = {
        {-s, A, B, s, 10.0f, C, -s, 10.0f, C},
        {s, 10.0f, C, -s, A, B, s, A, B},
        {-s, D, E, s, A, B, -s, A, B},
        {s, A, B, -s, D, E, s, D, E},
    };
#undef A
#undef B
#undef C
#undef D
#undef E
    s32 i;
    for (i = 0; i < 4; i++) {
        LaneTri* t = &lbl_807D3EF0[i];
        t->v[0] = VEC3(pts[i][0], pts[i][1], pts[i][2]);
        t->v[1] = VEC3(pts[i][3], pts[i][4], pts[i][5]);
        t->v[2] = VEC3(pts[i][6], pts[i][7], pts[i][8]);
        VEC3 a = t->v[1] - t->v[0];
        VEC3 b = t->v[2] - t->v[0];
        VEC3 c = t->v[2] - t->v[1];
        VEC3 d = t->v[0] - t->v[2];
        nw4r::math::VEC3Cross(&t->n, &a, &b);
        fn_802F280C(&t->n, &t->n);
        nw4r::math::VEC3Cross(&t->e[0], &a, &t->n);
        nw4r::math::VEC3Cross(&t->e[1], &c, &t->n);
        nw4r::math::VEC3Cross(&t->e[2], &d, &t->n);
        fn_802F280C(&t->e[0], &t->e[0]);
        fn_802F280C(&t->e[1], &t->e[1]);
        fn_802F280C(&t->e[2], &t->e[2]);
        VEC3 w = t->v[0] - t->v[1];
        t->d = -nw4r::math::VEC3Dot(&w, &t->e[1]);
    }
}

struct CurveTbl {
    u8 pad0[3];
    u8 enabled;
    u8 pad4[0xC];
    f32 len;
    u8 pad[0x284 - 0x14];
    f32 a[10];
    f32 b[10];
    f32 scale;
};
void fn_804D9A34();
void fn_804D9A38(f32 x, f32 y, f32 z);
void fn_804D9A3C(void*, f32 t, CurveTbl* p, f32* a, f32* b);

void fn_804D9804(void* self, CurveTbl* p) {
    if (p->enabled) {
        f32 m = 0.0f;
        s32 i;
        for (i = 0; i < 10; i++) {
            if (p->a[i] > m) m = p->a[i];
            if (p->b[i] > m) m = p->b[i];
        }
        f32 scale = 250.0f / m;
        for (i = 0; i < 32; i++) {
            f32 va, vb;
            f32 z0 = (f32)i / 32.0f * p->len;
            f32 z1 = (f32)(i + 1) / 32.0f * p->len;
            fn_804D9A3C(self, z0, p, &va, &vb);
            s32 ca = (s32)(va * scale);
            s32 cb = (s32)(vb * scale);
            fn_80373570((ca << 16) | 0xFF000000, 4, 1, 1, 0);
            fn_804D9A38(-3.0f, 0.1f, z0);
            fn_804D9A38(-3.0f, 0.1f, z1);
            fn_804D9A38(-1.0f, 0.1f, z0);
            fn_804D9A38(-1.0f, 0.1f, z1);
            fn_804D9A34();
            fn_80373570((cb << 8) | 0xFF000000, 4, 1, 1, 0);
            fn_804D9A38(1.0f, 0.1f, z0);
            fn_804D9A38(1.0f, 0.1f, z1);
            fn_804D9A38(3.0f, 0.1f, z0);
            fn_804D9A38(3.0f, 0.1f, z1);
            fn_804D9A34();
        }
    }
}

void fn_804D9A34() { fn_8037332C(); }
void fn_804D9A38(f32 x, f32 y, f32 z) { fn_8037334C(x, y, z); }

void fn_804D9A3C(void*, f32 t, CurveTbl* p, f32* a, f32* b) {
    f32 lim = -192.0f;
    if (t > 0.0f) {
        *a = p->a[0];
        *b = p->b[0];
    }
    if (t > 0.0f || t < lim) {
        *a = 0.0f;
        *b = 0.0f;
    } else {
        f32 x = 9.0f * (t / lim);
        s32 i = (s32)x;
        f32 fr = x - (f32)i;
        s32 j = i + 1;
        *a = p->a[i] + fr * (p->a[j] - p->a[i]);
        *b = p->b[i] + fr * (p->b[j] - p->b[i]);
        *a *= p->scale;
        *b *= p->scale;
    }
}

void fn_804D9C04(u8* p, const void* q);
void fn_804D9C50(u8* p, f32 v);
void fn_804D9C58(u8* p, f32 v);
void fn_804D9C60(u8* p, f32 v);
void fn_804D9C68(u8* p, f32 v);

void fn_804D9B20(u8* p) {
    const u8* g = gBowlingPhysicsData__7Bowling;
    s32 i;
    F32AT(p, 0x2C70) = F32AT(g, 0x110);
    F32AT(p, 0x2C74) = F32AT(g, 0x114);
    F32AT(p, 0x2C78) = F32AT(g, 0x118);
    F32AT(p, 0x2C80) = F32AT(g, 0x11C);
    F32AT(p, 0x2C84) = F32AT(g, 0x120);
    F32AT(p, 0x2C4C) = F32AT(g, 0x124);
    F32AT(p, 0x2C68) = F32AT(g, 0x130);
    for (i = 0; i < NPINS(p); i++) {
        fn_804D9C68(PINS(p)[i], F32AT(g, 0x78));
        fn_804D9C60(PINS(p)[i], F32AT(g, 0x7C));
        fn_804D9C58(PINS(p)[i], F32AT(g, 0x80));
        fn_804D9C50(PINS(p)[i], F32AT(g, 0x84));
    }
    if (*(u8**)(p + 0x1C)) fn_804D9C04(*(u8**)(p + 0x1C), p + 0x2C6C);
}

void fn_804D9C0C(void* dd, const void* ss);
void fn_804D9C04(u8* p, const void* q) { fn_804D9C0C(p + 0x60, q); }
#pragma dont_inline off
void fn_804D9C0C(void* dd, const void* ss) { *(Words8*)dd = *(const Words8*)ss; }
#pragma dont_inline reset

void fn_804D9C50(u8* p, f32 v) { F32AT(p, 0xF0) = v; }
void fn_804D9C58(u8* p, f32 v) { F32AT(p, 0xF4) = v; }
void fn_804D9C60(u8* p, f32 v) { F32AT(p, 0xEC) = v; }
void fn_804D9C68(u8* p, f32 v) { F32AT(p, 0x58) = v; }


struct PhysAll { f32 f[0x2F8 / 4]; };
#define G(o) (g->f[(o) / 4])
#define GB(o) (((u8*)g)[o])
extern f32 lbl_806F5998;  // split: belongs to this unit's .sbss (starts 0x806F599C now)
f32 lbl_806F599C;
f32 lbl_806F59A0;
f32 lbl_806F59A4;

void fn_804D9C70(u8* ctx) {
    PhysAll* g = (PhysAll*)gBowlingPhysicsData__7Bowling;
    memset(g, 0, 0x2F4);
    G(0x110) = 4.0f;
    G(0x114) = 0.004f;
    G(0x11C) = 0.0001f;
    G(0x120) = 0.0f;
    G(0x124) = 0.3f;
    G(0x12C) = 0.1f;
    G(0x130) = 0.0f;
    G(0x134) = 0.8f;
    G(0x128) = 0.1f;
    G(0x74) = -0.0055f;
    G(0x64) = 0.1f;
    G(0x68) = 0.6f;
    G(0x6C) = 0.05f;
    G(0x70) = 0.5f;
    G(0x78) = 0.995f;
    G(0x7C) = 0.99f;
    G(0x84) = 0.2f;
    G(0x88) = 1.5f;
    G(0x8C) = 0.0f;
    G(0x98) = 0.15f;
    G(0x118) = 1.075f;
    G(0x90) = 3.9f;
    G(0x94) = 1.53f;
    G(0x80) = 3.0f;
    G(0x8) = 3.05f;
    G(0xC) = 2.642f;
    G(0x10) = -192.0f;
    G(0x60) = -193.0f;
    G(0x14) = 10.66f;
    G(0x18) = 182.88f;
    G(0x1C) = 20.0f;
    G(0x20) = 1.2f;
    G(0x24) = 1.0f;
    G(0x28) = -208.6f;
    G(0x2C) = -200.0f;
    G(0x30) = -120.0f;
    G(0x34) = 0.1f;
    G(0x38) = 0.3f;
    G(0x3C) = 0.6f;
    G(0x40) = -210.0f;
    G(0x44) = 8.5f;
    G(0x48) = 19.0f;
    G(0x4C) = 7.6f;
    G(0x50) = 6.0f;
    G(0x54) = 11.0f;
    G(0x58) = -1.0f;
    G(0x5C) = 3.5f;
    G(0x160) = 0.3f;
    G(0x164) = 0.45f;
    G(0x168) = 0.55f;
    G(0x16C) = 0.62f;
    G(0x170) = 0.53f;
    G(0x174) = 0.5f;
    G(0x178) = 0.3f;
    G(0x17C) = 0.32f;
    G(0x180) = 0.35f;
    G(0x184) = 0.3f;
    G(0x188) = 0.0f;
    G(0x18C) = 0.35f;
    G(0x190) = 0.62f;
    G(0x194) = 0.65f;
    G(0x198) = 0.55f;
    G(0x19C) = 0.35f;
    G(0x1A0) = 0.33f;
    G(0x1A4) = 0.37f;
    G(0x1A8) = 0.4f;
    G(0x1D4) = 0.4f;
    G(0x1D8) = 0.42f;
    G(0x1DC) = 0.45f;
    G(0x1E0) = 0.45f;
    G(0x1E4) = 0.42f;
    G(0x1E8) = 0.42f;
    G(0x1EC) = 0.4f;
    G(0x1AC) = 0.66f;
    G(0x1F0) = -2.3f;
    G(0x100) = 0.3f;
    G(0x9C) = 0.002f;
    G(0xA0) = 1.2f;
    G(0xA4) = 0.1f;
    G(0xA8) = 1.2f;
    G(0xF0) = 0.8f;
    G(0xF4) = 0.0f;
    G(0xE8) = 0.5f;
    G(0xF8) = 0.3f;
    G(0xE4) = 1.0f;
    G(0xD8) = 0.4f;
    G(0xDC) = 0.4f;
    G(0xE0) = 1.0f;
    G(0x104) = 0.3f;
    G(0x108) = 0.3f;
    G(0xEC) = 0.1f;
    G(0xC4) = 0.35f;
    G(0xB0) = 1.9f;
    G(0xB4) = 1.1f;
    G(0xC0) = 0.00015f;
    G(0x10C) = 0.01f;
    G(0xB8) = 0.8f;
    G(0xBC) = 0.8f;
    G(0xC8) = 1.3f;
    G(0xCC) = 0.5f;
    G(0xD0) = 0.5f;
    G(0xFC) = 0.5f;
    G(0xD4) = 0.6f;
    G(0x15C) = 1.0f;
    G(0x21C) = 0.001f;
    G(0x224) = G(0x21C) / 120.0f;
    G(0x220) = 0.07f;
    G(0x228) = G(0x220) / 120.0f;
    G(0x22C) = 0.014722f;
    G(0x230) = 0.27f;
    G(0x234) = 0.01f;
    G(0x238) = 0.3f;
    G(0x23C) = 0.01f;
    G(0x240) = 0.1f;
    G(0x244) = 0.01f;
    G(0x248) = 0.1f;
    G(0x24C) = 0.01f;
    G(0x250) = 0.3f;
    G(0x254) = 0.6f;
    GB(0x25C) = 1;
    GB(0x25D) = 1;
    GB(0x25E) = 1;
    GB(0x25F) = 1;
    *(s32*)&G(0x258) = 60;
    G(0x284) = 0.007f;
    G(0x2AC) = 0.007f;
    G(0x288) = 0.007f;
    G(0x2B0) = 0.007f;
    G(0x28C) = 0.007f;
    G(0x2B4) = 0.007f;
    G(0x290) = 0.009f;
    G(0x2B8) = 0.009f;
    G(0x294) = 0.013f;
    G(0x2BC) = 0.013f;
    G(0x298) = 0.02f;
    G(0x2C0) = 0.02f;
    G(0x29C) = 0.03f;
    G(0x2C4) = 0.03f;
    G(0x2A0) = 0.03f;
    G(0x2C8) = 0.03f;
    G(0x2A4) = 0.01f;
    G(0x2CC) = 0.01f;
    G(0x2A8) = 0.01f;
    G(0x2D0) = 0.01f;
    G(0x2D4) = 1.0f;
    G(0x1A8) = 0.39999998f;
    G(0x138) = 0.9978f;
    G(0x13C) = 0.9995f;
    *(s32*)&G(0x140) = 24;
    for (s32 i = 0; i < 9; i++) {
        (&G(0x1B0))[i] = (&G(0x18C))[i];
        (&G(0x1F8))[i] = 1.0f;
    }
    G(0x210) = 1.4f;
    G(0x214) = 1.5f;
    G(0x1B0) = 0.55f;
    G(0x1CC) = 0.8f;
    G(0x14C) = 0.9982f;
    G(0x150) = 0.9995f;
    G(0x144) = 0.6f;
    G(0x154) = 0.9982f;
    G(0x158) = 0.9995f;
    G(0x148) = 1.15f;
    lbl_806F59A0 = 0.5f;
    lbl_806F5998 = 0.05f;
    lbl_806F599C = 0.1f;
    lbl_806F59A4 = 0.0f;
    G(0x2D8) = -197.0f;
    G(0x2DC) = -197.0f;
    G(0x2E0) = -200.0f;
    G(0x2E4) = 1.7f;
    G(0x2E8) = 0.8f;
    G(0x260) = 191.0f;
    G(0x264) = 192.0f;
    G(0x268) = 1.0f;
    G(0x26C) = 0.0f;
    G(0x270) = 191.0f;
    G(0x274) = 192.0f;
    G(0x278) = 1.0f;
    G(0x27C) = 0.0f;
    G(0x280) = 0.005f;
    GB(0x6) = 1;
    G(0x2EC) = G(0xDC);
    if (S32AT(ctx, 0x2D40) != 1) {
        G(0xA4) = 0.1f;
        G(0xDC) = 0.04f;
        G(0x2EC) = 0.07f;
        G(0x1B0) = 0.5f;
        G(0x1CC) = 0.7f;
        G(0xB0) = 1.6f;
        G(0x84) = 0.3f;
        G(0xF0) = 0.3f;
        G(0x100) = 0.47f;
        G(0xE4) = 0.89f;
    }
    G(0x2F0) = 0.1f;
    G(0xAC) = 0.12f;
    ((VObj*)ctx)->f5();
}
#undef G
#undef GB

#pragma fp_contract off
int fn_804DA328(void*, const f32* a, const f32* b, const VEC3& c, f32 t) {
    f32 prod = (c.z - a[2]) * (b[0] / b[2]);
    f32 x = prod + a[0];
    return x < c.x + t;
}
#pragma fp_contract on

VEC3 fn_804DA64C(const VEC3& v, f32 s);
VEC3* fn_804DA6A0(u8* p);

int fn_804DA364(u8* ctx, const f32* a, const f32* b, f32 t) {
    VEC3 pos;
    f32 maxZ = -9999.0f;
    s32 i;
    for (i = 0; i < NPINS(ctx); i++) {
        if (fn_804D952C(PINS(ctx)[i]) && maxZ < fn_804DA6A0(PINS(ctx)[i])->z) maxZ = fn_804DA6A0(PINS(ctx)[i])->z;
    }
    for (i = 0; i < NPINS(ctx); i++) {
        if (fn_804D952C(PINS(ctx)[i]) && maxZ == fn_804DA6A0(PINS(ctx)[i])->z) {
            s32 cnt;
            s32 j, k;
            s32 other = -1;
            for (j = i + 1; j < NPINS(ctx); j++) {
                if (fn_804D952C(PINS(ctx)[j]) && maxZ == fn_804DA6A0(PINS(ctx)[j])->z) {
                    other = j;
                    break;
                }
            }
            cnt = 0;
            for (k = i + 1; k < NPINS(ctx); k++) {
                if (fn_804D952C(PINS(ctx)[k]) && maxZ == fn_804DA6A0(PINS(ctx)[k])->z) cnt++;
            }
            bool pair = cnt == 1 && other == i + 1;
            if (pair) {
                pos = fn_804DA64C(*fn_804DA6A0(PINS(ctx)[i]) + *fn_804DA6A0(PINS(ctx)[other]), 0.5f);
                break;
            }
            if (other == -1) {
                pos = *fn_804DA6A0(PINS(ctx)[i]);
                break;
            }
            if (fn_804DA328(ctx, a, b, fn_804DA64C(*fn_804DA6A0(PINS(ctx)[i]) + *fn_804DA6A0(PINS(ctx)[other]), 0.5f), -t)) {
                pos = *fn_804DA6A0(PINS(ctx)[i]);
                break;
            }
        }
    }
    return fn_804DA328(ctx, a, b, pos, t);
}

// MATCH-PENDING (R17): ledger #10; see fn_804DC924 (stw-pair saves of a header-like inline).
#pragma use_lmw_stmw off
VEC3 fn_804DA64C(const VEC3& v, f32 s) {
    VEC3 r;
    fn_8021D094(&r, &v, s);
    return r;
}
#pragma use_lmw_stmw reset

VEC3* fn_804DA6A0(u8* p) { return (VEC3*)(p + 0xFC); }

int fn_804DA724(u8* p);

s32 fn_804DA6A8(u8* ctx) {
    s32 n = 0;
    for (s32 i = 0; i < NPINS(ctx); i++) {
        if (fn_804D952C(PINS(ctx)[i]) && fn_804DA724(PINS(ctx)[i])) n++;
    }
    return n;
}

int fn_804DA724(u8* p) { return p[0x26C]; }

void fn_804DA7D4(u32* p, s32 i);
void fn_804DA800(s32* p, s32 v);
void fn_804DA808(s32* p);

struct LaneMode {
    LaneHead head;
    u8 pad[0x2CF0 - sizeof(LaneHead)];
    s32 mode;
};

void fn_804DA72C(s32* p, LaneMode* lc) {
    fn_804C457C(p);
    fn_804DA808(p);
    fn_804DA800(p, lc->head.numPins);
    switch (lc->mode) {
    case 0:
        for (s32 i = 0; i < lc->head.numPins; i++) {
            if (fn_804D952C(lc->head.pins[i]) && !fn_804DA724(lc->head.pins[i])) fn_804DA7D4((u32*)p, i);
        }
        break;
    }
}

void fn_804DA7D4(u32* p, s32 i) { p[i / 30] |= 1 << (i % 30); }

void fn_804DA800(s32* p, s32 v) { p[4] = v; }

void fn_804DA808(s32* p) {
    p[3] = 0;
    p[2] = 0;
    p[1] = 0;
    p[0] = 0;
}

u8 fn_804DA820(u8* p) { return p[0x2C44]; }

void fn_804DA828(u8* p) { S32AT(p, 0x23D8) = S32AT(p, 0x2CB8); }

struct LaneTrail {
    u8 pad0[0x23EC];
    VEC3 pos[0x80];
    s32 time[0x80];
    u8 pad2BEC[0x2CB8 - 0x2BEC];
    s32 frame;
};

void fn_804DA834(LaneTrail* ctx, const VEC3& v) {
    for (s32 i = 0; i < 0x80; i++) {
        if (ctx->time[i] == -1) {
            ctx->pos[i] = v;
            ctx->time[i] = ctx->frame;
            break;
        }
    }
}

#pragma dont_inline off
struct PhysF { u8 pad[0x12C]; f32 radius; };
void fn_804DA8A4(u8* ctx, const PhysF* g, const s32* mode) {
    f32 len = fn_80204FEC((*(BallObj**)(ctx + 0x1C))->GetVel());
    if (0.0f == len || (*(BallObj**)(ctx + 0x1C))->GetVel()->z >= -0.001f) {
        (*(BallObj**)(ctx + 0x1C))->SetVel(EGG::Vector3f(0.0f, 0.0f, -g->radius));
    } else if (len < g->radius) {
        if (*mode == 2) {
            VEC3 v = fn_80204168((*(BallObj**)(ctx + 0x1C))->GetVel());
            v.z -= g->radius - len;
            (*(BallObj**)(ctx + 0x1C))->SetVel(EGG::Vector3f(v));
        } else {
            VEC3 n;
            fn_802F280C(&n, (*(BallObj**)(ctx + 0x1C))->GetVel());
            (*(BallObj**)(ctx + 0x1C))->SetVel(EGG::Vector3f(fn_804DA64C(n, g->radius)));
        }
    }
}
#pragma dont_inline reset


// 0x804DAA64: out-of-line weak copy (no inlining happens in this unit).
EGG::Vector3f::Vector3f(const VEC3& v) { __ct__Q34nw4r4math4VEC3Ffff(this, v.x, v.y, v.z); }

void fn_804DAAA0(u8* p, const VEC3& a, const VEC3& b) {
    *(VEC3*)(p + 0x23BC) = a;
    *(VEC3*)(p + 0x23C8) = b;
    S32AT(p, 0x23D4) = S32AT(p, 0x2CB8);
}

struct BallRates {
    f32 r0, pad, r2, r1, o0, o1;
};

void fn_804DAAE8(u8* ctx) {
    const u8* g = gBowlingPhysicsData__7Bowling;
    if (S32AT(ctx, 0x2BEC) == 2) return;
    S32AT(ctx, 0x2BEC) = 2;
    *(VEC3*)(ctx + 0x2C38) = *(*(BallObj**)(ctx + 0x1C))->GetVel();
    VEC3 a(F32AT(ctx, 0x2CC0), 0.0f, F32AT(ctx, 0x2CC8));
    VEC3 b(F32AT(ctx, 0x2C38), 0.0f, F32AT(ctx, 0x2C40));
    fn_802F280C(&a, &a);
    fn_802F280C(&b, &b);
    f32 dot = nw4r::math::VEC3Dot(&a, &b);
    if (ctx[0x2D0C]) dot = 1.0f;
    f32 r0 = 1.0f - (dot - F32AT(g, 0x138)) / (F32AT(g, 0x13C) - F32AT(g, 0x138));
    if (r0 > 1.0f) r0 = 1.0f;
    if (r0 < 0.0f) r0 = 0.0f;
    f32 r1 = 1.0f - (dot - F32AT(g, 0x14C)) / (F32AT(g, 0x150) - F32AT(g, 0x14C));
    if (r1 > 1.0f) r1 = 1.0f;
    if (r1 < 0.0f) r1 = 0.0f;
    f32 r2 = 1.0f - (dot - F32AT(g, 0x154)) / (F32AT(g, 0x158) - F32AT(g, 0x154));
    if (r2 > 1.0f) r2 = 1.0f;
    if (r2 < 0.0f) r2 = 0.0f;
    bool all = true;
    s32 i;
    for (i = 0; i < NPINS(ctx); i++) {
        if (!fn_804D952C(PINS(ctx)[i])) {
            all = false;
            break;
        }
    }
    BallRates* br = (BallRates*)(ctx + 0x2CCC);
    if (g[6]) {
        br->r0 = r0;
        br->r2 = all ? r2 : 1.0f;
        br->r1 = r1;
    } else {
        br->r0 = 0.0f;
        br->r2 = 0.0f;
        br->r1 = 0.0f;
    }
    br->o0 = F32AT(g, 0xC4) + br->r1 * (F32AT(g, 0x144) - F32AT(g, 0xC4));
    br->o1 = F32AT(g, 0xE8) + br->r2 * (F32AT(g, 0x148) - F32AT(g, 0xE8));
}

void fn_804DDF3C(void*);
void fn_804DDC88(void*, s32, const VEC3*, const VEC3*);
void fn_803787EC(void*);
void fn_80377364(void*, f32, const EGG::Vector3f&, const EGG::Vector3f&, f32, f32);
void fn_80243A94(void*, const EGG::Vector3f&);
VEC3 fn_804DB010(const VEC3& v);
void fn_804DB02C(u8* p, const EGG::Vector3f& v);
VEC3 fn_804DB034(const u8* o);
VEC3 fn_804DB044(const u8* o);
VEC3 fn_804DB054(const u8* o);
VEC3 fn_804DB064(const u8* o);
void fn_804DB220(u8* ctx);

static inline const VEC3* AddrOf(const VEC3& v) { return &v; }
#define BALL(ctx) (*(BallObj**)((u8*)(ctx) + 0x1C))

#pragma dont_inline off
void fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(u8* ctx, const VEC3* pos, u8 flag) {
    fn_804DDF3C(*(void**)(ctx + 0x10));
    BALL(ctx)->SetPos(EGG::Vector3f(fn_804DB064(ctx)));
    BALL(ctx)->SetAxisZ(EGG::Vector3f(fn_804DB054(ctx)));
    BALL(ctx)->SetAxisY(EGG::Vector3f(fn_804DB044(ctx)));
    BALL(ctx)->SetAxisX(EGG::Vector3f(fn_804DB034(ctx)));
    BALL(ctx)->SetVel(EGG::Vector3f(VEC3(0.0f, 0.0f, 0.0f)));
    fn_804DB02C(*(u8**)(ctx + 0x1C), EGG::Vector3f(VEC3(0.0f, 0.0f, 0.0f)));
    fn_803787EC(*(void**)(ctx + 0x1C));
    VEC3 start = fn_804DB064(ctx) + fn_804DA64C(fn_804DA64C(fn_804DB010(*pos), F32AT(gBowlingPhysicsData__7Bowling, 0x118)), 0.25f);
    fn_80377364(*(void**)(ctx + 0x1C), 1.0f, EGG::Vector3f(start), EGG::Vector3f(fn_804DA64C(*pos, 0.25f)), 0.0f, 0.0f);
    fn_804DDC88(*(void**)(ctx + 0x10), 0, &start, AddrOf(fn_804DA64C(*pos, 0.25f)));
    S32AT(ctx, 0x2BEC) = 1;
    ctx[0x2CA0] = flag;
    S32AT(ctx, 0x23D4) = -1;
    S32AT(ctx, 0x23D8) = -1;
    S32AT(ctx, 0x23E8) = -1;
    for (s32 i = 0; i < 0x80; i++) {
        ((s32*)(ctx + 0x29EC))[i] = -1;
    }
    *(VEC3*)(ctx + 0x2CC0) = *pos;
    fn_804DB220(ctx);
    S32AT(ctx, 0x23B4) = 0;
    S32AT(ctx, 0x23B8) = 0;
}
#pragma dont_inline reset

VEC3 fn_804DB010(const VEC3& v) { return VEC3(-v.x, -v.y, -v.z); }
void fn_804DB02C(u8* p, const EGG::Vector3f& v) { fn_80243A94(p + 0xE0, v); }
VEC3 fn_804DB034(const u8* o) { return VEC3(F32AT(o, 0x2BF8), F32AT(o, 0x2C08), F32AT(o, 0x2C18)); }
VEC3 fn_804DB044(const u8* o) { return VEC3(F32AT(o, 0x2BF4), F32AT(o, 0x2C04), F32AT(o, 0x2C14)); }
VEC3 fn_804DB054(const u8* o) { return VEC3(F32AT(o, 0x2BF0), F32AT(o, 0x2C00), F32AT(o, 0x2C10)); }
VEC3 fn_804DB064(const u8* o) { return VEC3(F32AT(o, 0x2BFC), F32AT(o, 0x2C0C), F32AT(o, 0x2C1C)); }

void fn_804E3C08(void*);
void fn_804E3E74(void*, bool, bool, bool);
void fn_804F9CE4(void*);

struct PhysData { u8 flags[0x14]; f32 laneW; f32 laneLen; u8 pad[0x2D8 - 0x1C]; f32 z0, z1, z2, y1, y2; };

void fn_804DB074__7BowlingFPQ27Bowling11LaneContext(u8* ctx) {
    const PhysData* g = (const PhysData*)gBowlingPhysicsData__7Bowling;
    s32 i;
    fn_804E3C08(*(void**)(ctx + 8));
    for (i = 0; i < NPINS(ctx); i++) {
        if (fn_804D952C(PINS(ctx)[i])) {
            fn_804E3E74(PINS(ctx)[i], g->flags[0] != 0, g->flags[1] != 0, g->flags[2] != 0);
        }
    }
    Bowling::fn_804E5100((Bowling::LaneContext*)ctx);
    fn_804D9804(ctx, (CurveTbl*)g);
    if (g->flags[4]) {
        f32 w = 10.0f * g->laneW;
        fn_80373570(0xFF50FF50, 4, 1, 1, 0);
        fn_804D9A38(-w, 10.0f, g->z0);
        fn_804D9A38(w, 10.0f, g->z0);
        fn_804D9A38(-w, g->y1, g->z1);
        fn_804D9A38(w, g->y1, g->z1);
        fn_804D9A34();
        fn_80373570(0xFF50C050, 4, 1, 1, 0);
        fn_804D9A38(-w, g->y1, g->z1);
        fn_804D9A38(w, g->y1, g->z1);
        fn_804D9A38(-w, g->y2, g->z2);
        fn_804D9A38(w, g->y2, g->z2);
        fn_804D9A34();
    }
    if (*(void**)(ctx + 0x14)) fn_804F9CE4(*(void**)(ctx + 0x14));
}

void fn_801EA79C(void*, const MTX34&);
// MATCH-PENDING (R17): ledger #11. BowMul keeps `sp * k` operand order (a plain `sp * 1000.0f` emits
// fmuls with the constant first); SpeedMag supplies the frsp after the call (the original
// probably calls a double-returning magnitude helper). Names inferred.
static inline f32 BowMul(f32 a, f32 b) { return a * b; }
static inline f64 SpeedMag(const VEC3* v) { return fn_80204FEC(v); }
const VEC3* fn_804DB504(u8* p);

#pragma dont_inline off
void fn_804DB220(u8* ctx) {
    const u8* g = gBowlingPhysicsData__7Bowling;
    *(VEC3*)(ctx + 0x2C20) = *BALL(ctx)->GetVel();
    *(VEC3*)(ctx + 0x2C2C) = *fn_804DB504(*(u8**)(ctx + 0x1C));
    fn_801EA79C(ctx + 0x2BF0,
                MTX34(BALL(ctx)->GetAxisZ()->x, BALL(ctx)->GetAxisY()->x, BALL(ctx)->GetAxisX()->x, BALL(ctx)->GetPos()->x,
                      BALL(ctx)->GetAxisZ()->y, BALL(ctx)->GetAxisY()->y, BALL(ctx)->GetAxisX()->y, BALL(ctx)->GetPos()->y,
                      BALL(ctx)->GetAxisZ()->z, BALL(ctx)->GetAxisY()->z, BALL(ctx)->GetAxisX()->z, BALL(ctx)->GetPos()->z));
    if (ctx[0x2C94] == 0) {
        if (BALL(ctx)->GetPos()->z < F32AT(g, 0x30)) {
            ctx[0x2C94] = 1;
            f32 sp = SpeedMag((const VEC3*)(ctx + 0x2C20));
            sp = sp / 4.16665f;
            sp = BowMul(sp, 1000.0f);
            sp = BowMul(sp, 3600.0f) / 10000.0f;
            F32AT(ctx, 0x2C90) = sp;
        }
    }
}
#pragma dont_inline reset

const VEC3* fn_804DB504(u8* p) { return (const VEC3*)(p + 0xE0); }

// --- 0x804DB50C: fn_804DB50C (lane physics step) not yet written ---
void fn_804DB50C(u8* ctx, const u8* g);

void* fn_804DC8D8(u8* p) { return *(void**)(p + 0x2BC); }
s32 fn_804DC8E0(void*) { return 0; }
int fn_804DC8E8(u8* p) { return p[0x2C4]; }

void fn_804DC8F0(u8* p, f32 a, f32 b, f32 c, f32 d) {
    F32AT(p, 0x298) = a;
    F32AT(p, 0x29C) = b;
    F32AT(p, 0x2A0) = c;
    F32AT(p, 0x2A4) = d;
}

int fn_804DC904(u8* p) { return p[0x2B8]; }
int fn_804DC90C(u8* p) { return p[0x2AC]; }
void fn_804DC914(u8* p, u8 v) { p[0x26D] = v; }
void fn_804DC91C(u8* p, const MTX34& m) { fn_801EA79C(p + 0x138, m); }

void* fn_8029F988(void*);
void* fn_8012FAB0(const void*);
void PSMTXInverse(const void*, void*);

// MATCH-PENDING (R17): ledger #10. These save GPRs with stw pairs where the unit's own functions use
// stmw: they look like header inlines / copy operators emitted out of line under
// different settings (struct copies still use the size-mode word loops).
#pragma use_lmw_stmw off
void fn_804DC924(void* a, const void* b) { PSMTXInverse(fn_8012FAB0(b), fn_8029F988(a)); }
#pragma use_lmw_stmw reset

void* fn_804DC96C(u8* p) { return p + 0x108; }
void fn_804DC974(u8* p, u8 v) { p[0x26C] = v; }
void fn_804DC97C() {}

void fn_804DC980(u8* p) {
    S32AT(p, 0x40) = 0;
    S32AT(p, 0x3C) = 0;
    F32AT(p, 0x48) = 0.0f;
}

void fn_80243A30(void* d, const void* s);

#pragma use_lmw_stmw off
void fn_804DC998(u8* p, const u8* q) {
    fn_804D9C0C(p + 0x60, q);
    fn_80243A30(p + 0x80, q + 0x20);
    fn_80243A30(p + 0xB0, q + 0x50);
    fn_80243A94(p + 0xE0, *(const EGG::Vector3f*)(q + 0x80));
    F32AT(p, 0xEC) = F32AT(q, 0x8C);
    fn_80243A94(p + 0xF0, *(const EGG::Vector3f*)(q + 0x90));
    fn_80243A94(p + 0x10, *(const EGG::Vector3f*)(q + 0x9C));
    fn_80243A94(p + 0x1C, *(const EGG::Vector3f*)(q + 0xA8));
    fn_80243A94(p + 0x28, *(const EGG::Vector3f*)(q + 0xB4));
    fn_80243A94(p + 0x34, *(const EGG::Vector3f*)(q + 0xC0));
    fn_80243A94(p + 0x40, *(const EGG::Vector3f*)(q + 0xCC));
    fn_80243A94(p + 0x4C, *(const EGG::Vector3f*)(q + 0xD8));
    F32AT(p, 0x58) = F32AT(q, 0xE4);
}
#pragma use_lmw_stmw reset

void fn_804DCA5C() {}


struct PhysBodyRaw {
    void* vtbl;
    Words61 body;
    u8 flagF8;
    u8 flagF9;
};
PhysBodyRaw* fn_804DCC20(PhysBodyRaw* d, const PhysBodyRaw* s);

struct PinBodyRaw {
    PhysBodyRaw base;
    Words3 vFC;
    Words12 m108;
    Words12 m138;
    f32 f168;
    f32 f16C;
    Words63 sub170;
    u8 b26C;
    u8 b26D;
    s32 w270, w274, w278, w27C, w280;
    u8 b284, b285, b286;
    Words2 w288;
    Words2 w290;
    f32 f298, f29C, f2A0, f2A4;
    s32 w2A8;
    u8 b2AC;
    f32 f2B0;
    s32 w2B4;
    u8 b2B8;
    s32 w2BC;
    s32 w2C0;
    u8 b2C4;
    s32 w2C8, w2CC, w2D0;
};

#pragma use_lmw_stmw off
#pragma dont_inline off
PinBodyRaw* fn_804DCA60(PinBodyRaw* d, const PinBodyRaw* s) {
    fn_804DCC20(&d->base, &s->base);
    d->vFC = s->vFC;
    d->m108 = s->m108;
    d->m138 = s->m138;
    d->f168 = s->f168;
    d->f16C = s->f16C;
    d->sub170 = s->sub170;
    d->b26C = s->b26C;
    d->b26D = s->b26D;
    d->w270 = s->w270;
    d->w274 = s->w274;
    d->w278 = s->w278;
    d->w27C = s->w27C;
    d->w280 = s->w280;
    d->b284 = s->b284;
    d->b285 = s->b285;
    d->b286 = s->b286;
    d->w288 = s->w288;
    d->w290 = s->w290;
    d->f298 = s->f298;
    d->f29C = s->f29C;
    d->f2A0 = s->f2A0;
    d->f2A4 = s->f2A4;
    d->w2A8 = s->w2A8;
    d->b2AC = s->b2AC;
    d->f2B0 = s->f2B0;
    d->w2B4 = s->w2B4;
    d->b2B8 = s->b2B8;
    d->w2BC = s->w2BC;
    d->w2C0 = s->w2C0;
    d->b2C4 = s->b2C4;
    d->w2C8 = s->w2C8;
    d->w2CC = s->w2CC;
    d->w2D0 = s->w2D0;
    return d;
}
#pragma dont_inline reset
#pragma use_lmw_stmw reset


#pragma dont_inline off
PhysBodyRaw* fn_804DCC20(PhysBodyRaw* d, const PhysBodyRaw* s) {
    d->body = s->body;
    d->flagF8 = s->flagF8;
    d->flagF9 = s->flagF9;
    return d;
}
#pragma dont_inline reset


struct Blk20 { s32 a; f32 b, c; EGG::Vector3f v; f32 d, e; };
Blk20* fn_804DCEAC(Blk20* d, const Blk20* s);

struct Blk12C {
    s32 w0;
    Words12 m4;
    Words3 v34;
    Words3 v40;
    Words3 v4C;
    u8 b58;
    s32 w5C;
    Blk20 s60;
    WordsN8 s80;
    u8 bA0;
    f32 fA4;
    u8 bA8, bA9, bAA, bAB, bAC;
    s32 wB0;
    u8 bB4;
    s32 wB8, wBC, wC0, wC4;
    u8 bC8;
    s32 wCC;
    u8 bD0, bD1;
    Words2 wD4;
    s32 wDC;
    f32 fE0;
    s32 wE4;
    f32 fE8, fEC, fF0, fF4;
    u8 bF8, bF9, bFA, bFB;
    s32 wFC;
    u8 b100;
    s32 w104;
    u8 b108, b109;
    s32 w10C, w110, w114;
    u8 b118, b119;
    f32 f11C;
    u8 b120;
    s32 w124, w128;
};

#pragma use_lmw_stmw off
#pragma dont_inline off
Blk12C* fn_804DCC60(Blk12C* d, const Blk12C* s) {
    d->w0 = s->w0;
    d->m4 = s->m4;
    d->v34 = s->v34;
    d->v40 = s->v40;
    d->v4C = s->v4C;
    d->b58 = s->b58;
    d->w5C = s->w5C;
    fn_804DCEAC(&d->s60, &s->s60);
    d->s80 = s->s80;
    d->bA0 = s->bA0;
    d->fA4 = s->fA4;
    d->bA8 = s->bA8;
    d->bA9 = s->bA9;
    d->bAA = s->bAA;
    d->bAB = s->bAB;
    d->bAC = s->bAC;
    d->wB0 = s->wB0;
    d->bB4 = s->bB4;
    d->wB8 = s->wB8;
    d->wBC = s->wBC;
    d->wC0 = s->wC0;
    d->wC4 = s->wC4;
    d->bC8 = s->bC8;
    d->wCC = s->wCC;
    d->bD0 = s->bD0;
    d->bD1 = s->bD1;
    d->wD4 = s->wD4;
    d->wDC = s->wDC;
    d->fE0 = s->fE0;
    d->wE4 = s->wE4;
    d->fE8 = s->fE8;
    d->fEC = s->fEC;
    d->fF0 = s->fF0;
    d->fF4 = s->fF4;
    d->bF8 = s->bF8;
    d->bF9 = s->bF9;
    d->bFA = s->bFA;
    d->bFB = s->bFB;
    d->wFC = s->wFC;
    d->b100 = s->b100;
    d->w104 = s->w104;
    d->b108 = s->b108;
    d->b109 = s->b109;
    d->w10C = s->w10C;
    d->w110 = s->w110;
    d->w114 = s->w114;
    d->b118 = s->b118;
    d->b119 = s->b119;
    d->f11C = s->f11C;
    d->b120 = s->b120;
    d->w124 = s->w124;
    d->w128 = s->w128;
    return d;
}
#pragma dont_inline reset
#pragma use_lmw_stmw reset

#pragma use_lmw_stmw off
#pragma dont_inline off
Blk20* fn_804DCEAC(Blk20* d, const Blk20* s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    fn_80243A94(&d->v, s->v);
    d->d = s->d;
    d->e = s->e;
    return d;
}
#pragma dont_inline reset

void fn_804DCF18(u8* p, u8* q) {
    fn_804D9C0C(q, p + 0x60);
    fn_80243A30(q + 0x20, p + 0x80);
    fn_80243A30(q + 0x50, p + 0xB0);
    fn_80243A94(q + 0x80, *(const EGG::Vector3f*)(p + 0xE0));
    F32AT(q, 0x8C) = F32AT(p, 0xEC);
    fn_80243A94(q + 0x90, *(const EGG::Vector3f*)(p + 0xF0));
    fn_80243A94(q + 0x9C, *(const EGG::Vector3f*)(p + 0x10));
    fn_80243A94(q + 0xA8, *(const EGG::Vector3f*)(p + 0x1C));
    fn_80243A94(q + 0xB4, *(const EGG::Vector3f*)(p + 0x28));
    fn_80243A94(q + 0xC0, *(const EGG::Vector3f*)(p + 0x34));
    fn_80243A94(q + 0xCC, *(const EGG::Vector3f*)(p + 0x40));
    fn_80243A94(q + 0xD8, *(const EGG::Vector3f*)(p + 0x4C));
    F32AT(q, 0xE4) = F32AT(p, 0x58);
}
#pragma use_lmw_stmw reset

void fn_804DCFE0(void* a, s32 b, const VEC3* c) {
    VEC3 zero(0.0f, 0.0f, 0.0f);
    fn_804DDC88(a, b, c, &zero);
}

EGG::Vector3f fn_804DD090(const f32* m, const VEC3& v);

#pragma use_lmw_stmw off
void fn_804DD040(u8* p, const VEC3& v) {
    fn_80243A94(p + 0xE0, fn_804DD090((const f32*)(p + 0xB0), v));
}
#pragma use_lmw_stmw reset

EGG::Vector3f fn_804DD090(const f32* m, const VEC3& v) {
    return EGG::Vector3f(m[0] * v.x + m[1] * v.y + m[2] * v.z, m[4] * v.x + m[5] * v.y + m[6] * v.z,
                         m[8] * v.x + m[9] * v.y + m[10] * v.z);
}

EGG::Vector3f fn_804DD0E8(const u8* q) { return fn_804DD090((const f32*)(q + 0x80), *(const VEC3*)(q + 0xE0)); }

EGG::Vector3f fn_804DD0F8(const VEC3& a, const VEC3& b) { return EGG::Vector3f(a.x + b.x, a.y + b.y, a.z + b.z); }

void* fn_804DD120(u8* p) { return p + 0x60; }
s32 fn_804DD128(u8* p) { return S32AT(p, 0x2CC); }

void fn_804DD130(u8* ctx) {
    if (Bowling::UpdatePinSetter((Bowling::LaneContext*)ctx)) fn_804DB50C(ctx, gBowlingPhysicsData__7Bowling);
}


#define EFFECTS(ctx) ((RPSysEffect**)((ctx) + 0x2D48))

void fn_804DD174(u8* ctx, const VEC3* pos) {
    EFFECTS(ctx)[S32AT(ctx, 0x2CE8)]->forceKill();
    EFFECTS(ctx)[S32AT(ctx, 0x2CE8)]->create();
    EFFECTS(ctx)[S32AT(ctx, 0x2CE8)]->setPos(*pos);
    EFFECTS(ctx)[S32AT(ctx, 0x2CE8)]->update();
    if (++S32AT(ctx, 0x2CE8) >= 16) S32AT(ctx, 0x2CE8) = 0;
}

int fn_804D395C(const u32* st, s32 i);
void fn_804DD374(void* d, const void* s);

struct PD21C { u8 pad[0x21C]; f32 a, b; };

void fn_804DD210__7BowlingFPQ27Bowling11LaneContextPQ27Bowling9PinStatus(LaneHead* lc, u32* st) {
    u8* ctx = (u8*)lc;
    const PD21C* g = (const PD21C*)gBowlingPhysicsData__7Bowling;
    ((VObj*)lc)->f6();
    for (s32 i = 0; i < lc->numPins; i++) {
        if (fn_804D395C(st, i)) {
            fn_804DC914(lc->pins[i], 1);
        } else {
            fn_804DC914(lc->pins[i], 0);
        }
        ((VObj*)lc->pins[i])->f1();
        fn_804DC8F0(lc->pins[i], g->a, g->b, g->a, g->b);
    }
    memset(ctx + 0x2BEC, 0, 0x12C);
    nw4r::math::MTX34Identity((MTX34*)(ctx + 0x2BF0));
    fn_804DD374(ctx + 0x2D18, st);
    if (ctx[0x2D88]) {
        for (s32 i = 0; i < lc->numPins; i++) {
            ((RPSysEffect*)fn_804DC8D8(lc->pins[i]))->forceKill();
        }
        ctx[0x2D88] = 0;
    }
    for (s32 i = 0; i < 16; i++) {
        EFFECTS(ctx)[i]->forceKill();
    }
}

#pragma dont_inline off
void fn_804DD374(void* d, const void* s) { *(Words5*)d = *(const Words5*)s; }
#pragma dont_inline reset

void fn_804E4F74(void* pin, const VEC3* pos, f32, f32, f32, const void*, const void*, const void*, const void*);
void fn_804DD5E0(f32* p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f);

void fn_804DD3A0(u8* ctx) {
    const u8* g = gBowlingPhysicsData__7Bowling;
    s32 i;
    for (i = 0; i < NPINS(ctx); i++) {
        f32 z = -F32AT(g, 0x18);
        VEC3 pos;
        f32 sp = F32AT(g, 0x8);
        f32 row = -F32AT(g, 0xC);
        f32 half = 0.5f * -sp;
        if (i == 0) {
            pos = VEC3(F32AT(ctx, 0x2D2C), 0.0f, z);
        } else if (i <= 2) {
            pos = VEC3(F32AT(ctx, 0x2D2C) + (sp * (f32)(i - 1) + half), 0.0f, z + row);
        } else if (i <= 5) {
            pos = VEC3(F32AT(ctx, 0x2D2C) + (2.0f * half + sp * (f32)(i - 3)), 0.0f, 2.0f * row + z);
        } else if (i <= 9) {
            pos = VEC3(F32AT(ctx, 0x2D2C) + (3.0f * half + sp * (f32)(i - 6)), 0.0f, 3.0f * row + z);
        }
        fn_804E4F74(PINS(ctx)[i], &pos, F32AT(g, 0x90), F32AT(g, 0x94), F32AT(g, 0x98), g + 0x18C, g + 0x1D4, g + 0x160, g + 0x1B0);
    }
    fn_804DD5E0(*(f32**)(ctx + 8), F32AT(g, 0x10), F32AT(g, 0x20), F32AT(g, 0x24), F32AT(g, 0x28), F32AT(g, 0x2C), F32AT(g, 0x34));
}

void fn_804DD5E0(f32* p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    p[4] = e;
    p[5] = f;
}

void fn_804DD684(u8* p);

void fn_804DD5FC__7BowlingFPQ27Bowling11LaneContext(u8* p) {
    S32AT(p, 0x23D4) = -1;
    S32AT(p, 0x23D8) = -1;
    S32AT(p, 0x23E8) = -1;
    for (s32 i = 0; i < 0x80; i++) {
        ((s32*)(p + 0x29EC))[i] = -1;
    }
    memset(p + 0x2BEC, 0, 0x12C);
    S32AT(p, 0x23B4) = 1;
    S32AT(p, 0x23B8) = 0;
    Bowling::ResetPinSetterState((Bowling::LaneContext*)p, 0);
    fn_804DD684(p);
}

void fn_804DD684(u8* p) {
    s32 st[5];
    fn_804C457C(st);
    fn_804DD210__7BowlingFPQ27Bowling11LaneContextPQ27Bowling9PinStatus((LaneHead*)p, (u32*)st);
}

void fn_804D9C70(u8* ctx);
void* __nw__FUl(unsigned long);
void* __nwa__FUl(unsigned long);
void* __construct_new_array(void*, void*, void*, unsigned long, unsigned long);
void* fn_804E5018(void*);
void fn_804E4FAC(void*);
void fn_804EBE5C(void*, f32, f32, f32, f32);
void* fn_804DD9D4(void*);
void fn_804DDF54(void*, s32);
void* fn_803790BC(void*, void*);
void* fn_802BA8D8(void*, EGG::Heap*, s32);
EGG::Heap* fn_804DD9CC();
f32 fn_804DDBA0(f32 x);
void fn_804D1BC0(void*, f32, f32);

void fn_804DD6C0(u8* ctx, f32 x, s32 mode, s32 n, void* p) {
    F32AT(ctx, 0x2D2C) = x;
    S32AT(ctx, 0x2D40) = mode;
    S32AT(ctx, 0x14) = 0;
    ctx[0x2D89] = 0;
    if (mode == 0 && fn_804DDBA0(x) < 0.01f) ctx[0x2D89] = 1;
    if (mode == 2) ctx[0x2D89] = 1;
    u8* bs = ctx + 0x2BEC;
    ctx[0x2D88] = 0;
    const PhysData* g = (const PhysData*)gBowlingPhysicsData__7Bowling;
    memset(bs, 0, 0x12C);
    S32AT(ctx, 0x1C) = 0;
    S32AT(ctx, 0x8) = 0;
    S32AT(ctx, 0x18) = 0;
    fn_804D9C70(ctx);
    S32AT(ctx, 0x18) = n;
    PINS(ctx) = (u8**)__nwa__FUl(n * 4);
    for (s32 i = 0; i < NPINS(ctx); i++) {
        void* pin = __nw__FUl(0x2D4);
        if (pin) pin = fn_804E5018(pin);
        PINS(ctx)[i] = (u8*)pin;
        fn_804E4FAC(PINS(ctx)[i]);
        fn_804EBE5C(PINS(ctx)[i], 10.0f, 0.5f, 1.0f, 0.0f);
    }
    for (s32 j = 0; j < 16; j++) {
        EFFECTS(ctx)[j] = new RPSysEffect("WS2_bwl_pin_hit", 0);
    }
    if (!(*(bool*)(ctx + 0x2D90) = !(fn_804DDBA0(x) < 0.01f))) {
        for (s32 j = 0; j < NPINS(ctx); j++) {
            ((void**)(ctx + 0x2164))[j] = __construct_new_array(__nwa__FUl(0x2D50), (void*)fn_804E5018, 0, 0x2D4, 16);
        }
        for (s32 j = 0; j < 48; j++) {
            ((void**)(ctx + 0x22F4))[j] = __construct_new_array(__nwa__FUl(0x54D0), (void*)fn_804DD9D4, 0, 0x54C, 16);
        }
    }
    *(void**)(ctx + 0x10) = __nw__FUl(0x2C);
    fn_804DDF54(*(void**)(ctx + 0x10), 0);
    *(void**)(ctx + 0x8) = __nw__FUl(0x20);
    ((VObj*)ctx)->f6();
    void* b = __nw__FUl(0x108);
    if (b) b = fn_803790BC(b, bs + 0x80);
    *(void**)(ctx + 0x1C) = b;
    fn_804DD684(ctx);
    b = __nw__FUl(0xD4);
    if (b) b = fn_802BA8D8(b, fn_804DD9CC(), 8);
    *(void**)(ctx + 0x20) = b;
    F32AT(ctx, 0x2D9C) = 0.0f;
    S32AT(ctx, 0x23B4) = 1;
    *(void**)(ctx + 0xC) = p;
    fn_804D1BC0(p, x, -g->laneLen);
    fn_804D9590();
    S32AT(ctx, 0x2D44) = 0;
    F32AT(ctx, 0x2D8C) = -9999.0f;
    S32AT(ctx, 0x2D94) = 0;
    S32AT(ctx, 0x2DA0) = 0;
    S32AT(ctx, 0x2DA4) = 0;
    ctx[0x2DA8] = 0;
    S32AT(ctx, 0x2DAC) = 0;
    S32AT(ctx, 0x2DB0) = 0;
    ctx[0x2DB4] = 0;
}

EGG::Heap* fn_804DD9CC() { return EGG::Heap::sCurrentHeap; }

f32 fn_8001705C(f32);
f32 fn_804DDBA0(f32 x) { return fn_8001705C(x); }
f32 fn_804DDBA4() { return F32AT(gBowlingPhysicsData__7Bowling, 0x94); }
s32 fn_804DDBB4() { return 0; }
void fn_804DDBBC() {}

}  // extern "C"
