// Resort (RZTE01_01) port of Wii Sports RPBow_80329658.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_80329658: a bowling body that extends the RPBow_80327F0C rigid body
// (BowBody: vtable + BowBodyState at 0x04) with a base position, a cached
// 3x4 pose matrix, eight sample points with radii, a sound object and an
// effect. Its real class name is unknown (vtable lbl_803CA650), so the
// functions keep their fn_ names and take the object as an explicit pointer.
// Field names are inferred from use only.
// Functions are written in DESCENDING address order: the unit is built with
// -inline deferred, so MWCC emits them (and their .sdata2 pool entries) in
// reverse source order.
// Matching notes:
// - fn_804E4B9C's 18 out-of-line nw4r::math::VEC3 ctor/__as__ zeroings live in
//   an inline (BowBaseReset): inline-block temporaries are stacked bottom-up,
//   function-level ones top-down, so the identity-axis temps written directly
//   in the function land above them as in the original.
// - the debug spheres go through DrawGX::DrawDLWorld (inline), which puts their
//   GXColor argument copies below the DrawLine ones; GXColor is set at the top
//   of the innermost loop body (MWCC hoists the stores one level only) and
//   after the line points are computed.
// - j / 16.0f (not j * 0.0625f) keeps the fmuls operand order; sin/cos go
//   through f32 inline wrappers, which fixes the callee-saved FPR coloring.
// - fn_804E4FAC: the sound object's new+ctor is a static inline returning the
//   pointer (BowNewSnd), with `u8* b` declared before `s32 i` in the ctor
//   inline; a C++ class ctor swaps the self/new-object callee-saved regs.

struct BowVec3Base {
    f32 x, y, z;
};

static inline BowVec3Base* BowPsScale(register BowVec3Base* pOut, register const BowVec3Base* pIn,
                              register f32 scale);
static inline BowVec3Base* BowPsAdd(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB);
static inline BowVec3Base* BowPsSub(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB);

struct BowVec3 : BowVec3Base {
    BowVec3() {}
    BowVec3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    BowVec3& operator=(const BowVec3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    BowVec3 operator-() const {
        return BowVec3(-x, -y, -z);
    }
    BowVec3 operator+(const BowVec3& rhs) const {
        BowVec3 out;
        BowPsAdd(&out, this, &rhs);
        return out;
    }
    BowVec3 operator-(const BowVec3& rhs) const {
        BowVec3 out;
        BowPsSub(&out, this, &rhs);
        return out;
    }
    BowVec3 operator*(f32 s) const {
        BowVec3 out;
        BowPsScale(&out, this, s);
        return out;
    }
    BowVec3& operator*=(f32 s) {
        BowPsScale(this, this, s);
        return *this;
    }
};

static inline BowVec3Base* BowPsScale(register BowVec3Base* pOut, register const BowVec3Base* pIn,
                              register f32 scale) {
    register f32 w0, w1;
    asm {
        psq_l    w0, 0(pIn), 0, 0
        ps_muls0 w1, w0, scale
        psq_st   w1, 0(pOut), 0, 0
        psq_l    w0, 8(pIn), 1, 0
        ps_muls0 w1, w0, scale
        psq_st   w1, 8(pOut), 1, 0
    }
    return pOut;
}

static inline BowVec3Base* BowPsAdd(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB) {
    register f32 w0, w1, w2;
    asm {
        psq_l  w0, 0(pA), 0, 0
        psq_l  w1, 0(pB), 0, 0
        ps_add w2, w0, w1
        psq_st w2, 0(pOut), 0, 0
        psq_l  w0, 8(pA), 1, 0
        psq_l  w1, 8(pB), 1, 0
        ps_add w2, w0, w1
        psq_st w2, 8(pOut), 1, 0
    }
    return pOut;
}

static inline BowVec3Base* BowPsSub(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB) {
    register f32 w0, w1, w2;
    asm {
        psq_l  w0, 0(pA), 0, 0
        psq_l  w1, 0(pB), 0, 0
        ps_sub w2, w0, w1
        psq_st w2, 0(pOut), 0, 0
        psq_l  w0, 8(pA), 1, 0
        psq_l  w1, 8(pB), 1, 0
        ps_sub w2, w0, w1
        psq_st w2, 8(pOut), 1, 0
    }
    return pOut;
}

namespace nw4r {
namespace math {
struct VEC3 {
    f32 x, y, z;
    VEC3();
    VEC3(f32, f32, f32);
    VEC3& operator=(const VEC3&);
};
struct MTX34 {
    f32 m[3][4];
    MTX34() {}
    MTX34(f32 m00, f32 m01, f32 m02, f32 m03, f32 m10, f32 m11, f32 m12, f32 m13, f32 m20,
           f32 m21, f32 m22, f32 m23) {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
    }
};
}  // namespace math
}  // namespace nw4r

struct _GXColor {
    u8 r, g, b, a;
};
typedef _GXColor GXColor;

namespace EGG {
class DrawGX {
public:
    enum ColorChannel {
        COLORCHAN_LIGHT,
        COLORCHAN_COLOR,
    };
    enum DL {
        DL_LINE_AXIS,
        DL_CUBE,
        DL_CUBE_WIRE,
        DL_SPHERE_4X8,
        DL_SPHERE_8X16,
    };
    enum ZMode {
        ZMODE_ALWAYS,
        ZMODE_OPA,
    };
    static void BeginDrawSphere();
    static void BeginDrawLine(ColorChannel chan, ZMode zMode);
    static void DrawLine(const nw4r::math::VEC3* pPoints, u16 num, GXColor color, u8 width);
    static void DrawDL(DL dl, const nw4r::math::MTX34& rMtx, GXColor color);
    static void DrawDLWorld(DL dl, const nw4r::math::MTX34& rMtx, GXColor color);
    static nw4r::math::MTX34 s_cameraMtx;
};

template <int N>
class AudioSoundActorBaseWithCamera {
public:
    static void* smCommon3DManager[N];
};
}  // namespace EGG

class RPSysEffect {
public:
    RPSysEffect(const char* pName, u32 drawGroup);
    virtual ~RPSysEffect();
    u8 pad[0x114];
};

typedef nw4r::math::MTX34 BowMtx;

struct BowBodyState {
    BowVec3 pos;         // 0x04
    BowVec3 vel;         // 0x10
    BowVec3 prevPos;     // 0x1C
    BowVec3 impulseMin;  // 0x28
    BowVec3 impulseMax;  // 0x34
    BowVec3 forceMin;    // 0x40
    BowVec3 forceMax;    // 0x4C
    f32 velDamp;         // 0x58
    BowVec3 axis[3];     // 0x5C
    BowVec3 spin[3];     // 0x80 (only x/y used)
    BowVec3 spinMin0;    // 0xA4
    BowVec3 spinMax0;    // 0xB0
    BowVec3 spinMin1;    // 0xBC
    BowVec3 spinMax1;    // 0xC8
    BowVec3 spinMin2;    // 0xD4
    BowVec3 spinMax2;    // 0xE0
    f32 spinDamp;        // 0xEC
    f32 unkF0;           // 0xF0
    f32 radius;          // 0xF4
};

struct BowPt {
    BowVec3 p;  // 0x00
    BowVec3 d;  // 0x0C
    f32 r;      // 0x18
};

struct BowSndPad78 {
    u8 pad[0x78];
};

struct BowSndObj : BowSndPad78 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16(const BowVec3* pos);
};

struct BowNpcBody {
    void* vtable;        // 0x000
    BowBodyState s;      // 0x004
    u8 unkF8;            // 0x0F8
    u8 unkF9;            // 0x0F9
    BowVec3 base;        // 0x0FC
    BowMtx mtx;          // 0x108
    u8 pad138[0x30];     // 0x138
    f32 ptScale;         // 0x168
    f32 height;          // 0x16C
    BowPt pts[9];        // 0x170
    u8 b250;             // 0x250
    f32* a254;           // 0x254
    f32* a258;           // 0x258
    f32* a25c;           // 0x25C
    f32* a260;           // 0x260
    s32 i264;            // 0x264
    u8 b268;             // 0x268
    u8 b269;             // 0x269
    u8 b26a;             // 0x26A
    s32 i26c;            // 0x26C
    s32 i270;            // 0x270
    s32 i274;            // 0x274
    s32 i278;            // 0x278
    f32 f27c;            // 0x27C
    f32 f280;            // 0x280
    f32 f284;            // 0x284
    f32 f288;            // 0x288
    s32 i28c;            // 0x28C
    u8 b290;             // 0x290
    f32 maxSpin;         // 0x294
    BowSndObj* snd;      // 0x298
    u8 b29c;             // 0x29C
    RPSysEffect* effect; // 0x2A0
    s32 i2a4;            // 0x2A4
    u8 b2a8;             // 0x2A8
    s32 i2ac;            // 0x2AC
    s32 i2b0;            // 0x2B0
    s32 i2b4;            // 0x2B4 (Resort: shifted)
};

// Retail weak template vtables (kept once, in RPTns_8021ba24 .data). Empty local views so the
// hand-built constructor code can name the compiler's vtable symbols: the static member __vt of
// TRPSndAudioHandles<8> mangles to __vt__21TRPSndAudioHandles<8> (likewise for <4,4>).
template <int N> class TRPSndAudioHandles;
template <> class TRPSndAudioHandles<8> {
public:
    static u8 __vt[];
};
template <int N1, int N2> class TRPSndAudioActorBaseWithHandles;
template <> class TRPSndAudioActorBaseWithHandles<4, 4> {
public:
    static u8 __vt[];
};
extern "C" {
namespace EGG {
struct Heap {
    static void* sCurrentHeap;
};
}
extern "C" void* fn_802BA8D8(void* pObj, void* pHeap, int align);
void fn_802BA4DC(BowSndObj* snd, const BowVec3* pos);
double sin(double);
double cos(double);
void* memset(void*, int, unsigned long);
void PSMTXIdentity(void*);
u32 PSMTXInverse(const void*, void*);
void PSMTXConcat(const void*, const void*, void*);
void PSMTXScaleApply(const void*, void*, f32, f32, f32);
void PSMTXTransApply(const void*, void*, f32, f32, f32);
f32 PSVECMag(const void*);
void PSVECNormalize(const void*, void*);

void* __nw__FUl(unsigned long);
void* __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(
    void*, void*, void*);
void __ct__Q23EGG8DisposerFv(void*);
void __ct__17RPSndMoveValueF32Fv(void*);
void List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void __ct__Q34nw4r3snd11SoundHandleFv();
void __dt__Q34nw4r3snd11SoundHandleFv();
void system_halt(const char*, int, const char*, ...);
extern u8 __vt__19RPSndAudioActorBase[];
extern u8 sActorList__19RPSndAudioActorBase[];
extern u8 __vt__Q27Bowling17RPBowNpcSndObject[];
extern char lbl_803C4098[];
extern char lbl_803C4080[];
struct BowGlobal {
    u8 pad[0x18];
    s32 f18;
};
extern BowGlobal* lbl_806F5950;
extern f32 lbl_804BF9A0;
extern u8 lbl_804BF9A4;
struct BowSndMgr {
    u8 pad[0x69C];
    void* player;
};
extern BowSndMgr* spInstance__13RPSndAudioMgr;

void fn_804EBB64(BowNpcBody* self);
void fn_804EF1B8(BowNpcBody* self);
}

namespace nw4r {
namespace math {
inline MTX34* MTX34Mult(MTX34* pOut, const MTX34* pA, const MTX34* pB) {
    PSMTXConcat(pA, pB, pOut);
    return pOut;
}
}  // namespace math
}  // namespace nw4r

inline void EGG::DrawGX::DrawDLWorld(DL dl, const nw4r::math::MTX34& rMtx, GXColor color) {
    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Mult(&mtx, &s_cameraMtx, &rMtx);
    DrawDL(dl, mtx, color);
}

static inline f32 BowSinF(f32 x) {
    return sin(x);
}
static inline f32 BowCosF(f32 x) {
    return cos(x);
}

static inline BowMtx BowGetMtx(const BowNpcBody* self) {
    return BowMtx(self->s.axis[0].x, self->s.axis[1].x, self->s.axis[2].x, self->s.pos.x,
                  self->s.axis[0].y, self->s.axis[1].y, self->s.axis[2].y, self->s.pos.y,
                  self->s.axis[0].z, self->s.axis[1].z, self->s.axis[2].z, self->s.pos.z);
}

static inline void BowBaseReset(BowNpcBody* self) {
    *(nw4r::math::VEC3*)&self->s.pos = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.vel = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.axis[0] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.axis[1] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.axis[2] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spin[0] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spin[1] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spin[2] = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.impulseMin = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.impulseMax = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.forceMin = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.forceMax = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMin0 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMax0 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMin1 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMax1 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMin2 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.spinMax2 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    *(nw4r::math::VEC3*)&self->s.prevPos = *(nw4r::math::VEC3*)&self->s.pos;
    self->unkF9 = 0;
}

static inline void* BowSndCt(u8* a, void* player) {
    u8* b;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (!EGG::AudioSoundActorBaseWithCamera<4>::smCommon3DManager[i])
            system_halt(lbl_803C4098, 375, lbl_803C4080);
        void* s3 = __nw__FUl(0xC4);
        if (s3)
            s3 = __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(
                s3, player, EGG::AudioSoundActorBaseWithCamera<4>::smCommon3DManager[i]);
        ((void**)a)[i] = s3;
    }
    b = a + 0x10;
    __ct__Q23EGG8DisposerFv(b);
    *(void**)b = __vt__19RPSndAudioActorBase;
    __ct__17RPSndMoveValueF32Fv(b + 0x20);
    b[0x10] = 0;
    *(s32*)(b + 0x14) = 0;
    List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(sActorList__19RPSndAudioActorBase, b);
    *(void**)(b + 0x3C) = TRPSndAudioHandles<8>::__vt;
    __construct_array(b + 0x48, (void*)__ct__Q34nw4r3snd11SoundHandleFv,
                      (void*)__dt__Q34nw4r3snd11SoundHandleFv, 4, 8);
    *(s32*)(b + 0x40) = 8;
    *(s32*)(b + 0x44) = 8;
    *(void**)b = TRPSndAudioActorBaseWithHandles<4, 4>::__vt;
    *(void**)(b + 0x3C) = TRPSndAudioActorBaseWithHandles<4, 4>::__vt + 0x24;
    a[0x7C] = 0;
    *(s32*)(a + 0x80) = 0xF;
    *(void**)(a + 0x78) = __vt__Q27Bowling17RPBowNpcSndObject;
    *(void**)(a + 0x10) = __vt__Q27Bowling17RPBowNpcSndObject + 8;
    *(void**)(a + 0x4C) = __vt__Q27Bowling17RPBowNpcSndObject + 0x2C;
    *(s32*)(a + 0x84) = 0;
    *(s32*)(a + 0x88) = 0;
    *(s32*)(a + 0x8C) = 0;
    lbl_804BF9A0 = 0.0f;
    lbl_804BF9A4 = 0;
    return a;
}

static inline BowSndObj* BowNewSnd() {
    u8* a = (u8*)__nw__FUl(0x90);
    if (a) a = (u8*)BowSndCt(a, spInstance__13RPSndAudioMgr->player);
    return (BowSndObj*)a;
}

extern "C" {

struct BowNpcCtBody {
    void* vtable;
    u8 pad[0x2B4 - 4];
    s32 i2b4;
    s32 i2b8;
    s32 i2bc;
};

extern u8 lbl_806DEE20[];
extern u8 lbl_806DED98[];
void __ct__Q34nw4r4math4VEC3Fv(void*);

// MATCH-PENDING (R17): constructor written as a free function that calls the mangled nw4r VEC3 ctor once per
// member; the real source is a class ctor with VEC3 members (placement new / self->T::T() both failed). Ledger #30.
BowNpcCtBody* fn_804E5018(BowNpcCtBody* self) {
    self->vtable = lbl_806DEE20;
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x4);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x10);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x1C);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x28);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x34);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x40);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x4C);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x5C);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x68);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x74);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x80);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x8C);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0x98);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xA4);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xB0);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xBC);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xC8);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xD4);
    __ct__Q34nw4r4math4VEC3Fv((u8*)self + 0xE0);
    self->vtable = lbl_806DED98;
    self->i2b4 = 0;
    self->i2bc = 0;
    return self;
}

void fn_804E4FAC(BowNpcBody* self) {
    void* pSnd = __nw__FUl(0xD4);
    if (pSnd) {
        pSnd = fn_802BA8D8(pSnd, EGG::Heap::sCurrentHeap, 8);
    }
    self->snd = (BowSndObj*)pSnd;
    self->effect = new RPSysEffect("WS2_bwl_pinltail", 0);
}

void fn_804E4F74(BowNpcBody* self, const BowVec3* base, f32 ptScale, f32 height, f32* a258,
                 f32* a260, f32* a254, f32* a25c, f32 maxSpin) {
    self->base = *base;
    self->ptScale = ptScale;
    self->height = height;
    self->a254 = a254;
    self->a258 = a258;
    self->a260 = a260;
    self->maxSpin = maxSpin;
    self->a25c = a25c;
}

void fn_804E4B9C(BowNpcBody* self) {
    BowBaseReset(self);
    memset(self->pts, 0, sizeof(self->pts));
    self->s.pos.x = self->base.x;
    self->s.pos.z = self->base.z;
    self->s.pos.y = self->base.y + self->height;
    self->s.axis[0] = BowVec3(1.0f, 0.0f, 0.0f);
    self->s.axis[1] = BowVec3(0.0f, 1.0f, 0.0f);
    self->s.axis[2] = BowVec3(0.0f, 0.0f, 1.0f);
    self->mtx = BowGetMtx(self);
    self->b250 = 0;
    self->i264 = 0;
    self->b268 = 0;
    self->b269 = 0;
    self->i26c = 0;
    self->i270 = 0;
    self->i274 = 0;
    self->i278 = 0;
    self->b26a = 0;
    self->f27c = 0.0f;
    self->f280 = 0.0f;
    self->b290 = 0;
    self->i28c = 0;
    self->b29c = 0;
    self->i2a4 = 0;
    self->b2a8 = 0;
    self->i2ac = 0;
    self->i2b0 = 0;
    if (lbl_806F5950->f18 == 0) {
        self->i2b4 = 9;
    } else {
        self->i2b4 = 8;
    }
}

void fn_804E4B58(BowNpcBody* self, int i, BowVec3* p, f32* r, BowVec3* d) {
    *p = self->pts[i].p;
    *d = self->pts[i].d;
    *r = self->pts[i].r;
}

void fn_804E488C(BowNpcBody* self, f32 t) {
    self->mtx = BowGetMtx(self);
    fn_804EBB64(self);
    f32 y = -self->height + self->a258[0];
    if (self->i2b4 > 0) {
        for (int i = 0; i < self->i2b4; i++) {
            BowVec3 old = self->pts[i].p;
            self->pts[i].p = self->s.pos + self->s.axis[1] * y;
            self->pts[i].r = t * (self->a25c[i] - self->a258[i]) + self->a258[i];
            self->pts[i].d = self->pts[i].p - old;
            y += self->a260[i];
        }
    }
    if (self->i2b0) {
        fn_804EF1B8(self);
    }
    f32 maxSq = self->maxSpin * self->maxSpin;
    if (self->s.spin[0].x * self->s.spin[0].x + self->s.spin[0].y * self->s.spin[0].y > maxSq) {
        PSVECNormalize(&self->s.spin[0], &self->s.spin[0]);
        self->s.spin[0] *= self->maxSpin;
    }
    if (self->s.spin[1].x * self->s.spin[1].x + self->s.spin[1].y * self->s.spin[1].y > maxSq) {
        PSVECNormalize(&self->s.spin[1], &self->s.spin[1]);
        self->s.spin[1] *= self->maxSpin;
    }
    if (self->s.spin[2].x * self->s.spin[2].x + self->s.spin[2].y * self->s.spin[2].y > maxSq) {
        PSVECNormalize(&self->s.spin[2], &self->s.spin[2]);
        self->s.spin[2] *= self->maxSpin;
    }
    if (self->i2ac) {
        self->i2ac++;
    }
}

void fn_804E487C(BowNpcBody* self) {
    fn_802BA4DC(self->snd, &self->s.pos);
}

void fn_804E46EC(BowNpcBody* self) {
    if (self->s.pos.y < -0.2f && self->s.pos.z < -193.1f) {
        self->b2a8 = 1;
        return;
    }
    f32 k = 1.0f;
    if (self->s.axis[1].y < 0.5f) {
        k = 2.0f;
    }
    f32 maxMove;
    f32 maxRot;
    if (self->b250) {
        maxMove = 0.7f * (self->f27c * k);
        maxRot = 0.7f * (self->f280 * k);
    } else {
        maxRot = 0.15f * self->f288;
        maxMove = 0.5f * self->f284;
    }
    maxRot /= 10.0f;
    BowVec3 d = self->s.pos - self->s.prevPos;
    if (PSVECMag(&d) > maxMove) {
        self->i2a4 = 0;
        self->b2a8 = 0;
        return;
    }
    if (PSVECMag(&self->s.spin[0]) > maxRot || PSVECMag(&self->s.spin[1]) > maxRot ||
        PSVECMag(&self->s.spin[2]) > maxRot) {
        self->i2a4 = 0;
        self->b2a8 = 0;
        return;
    }
    self->i2a4++;
    if (self->i2a4 > 20 || self->b250) {
        self->b2a8 = 1;
    } else {
        self->b2a8 = 0;
    }
}

void fn_804E45FC(BowNpcBody* self) {
    self->s.axis[0] = BowVec3(1.0f, 0.0f, 0.0f);
    self->s.axis[1] = BowVec3(0.0f, 1.0f, 0.0f);
    self->s.axis[2] = BowVec3(0.0f, 0.0f, 1.0f);
    self->s.pos.y = self->base.y + self->height;
    self->mtx = BowGetMtx(self);
}

void fn_804E3E74(BowNpcBody* self, int drawPts, int drawRings, int drawBody) {
    nw4r::math::MTX34 tmp;
    BowMtx m = BowGetMtx(self);
    nw4r::math::MTX34 inv;
    GXColor color;
    PSMTXInverse(&m, &inv);
    if (drawBody) {
        EGG::DrawGX::BeginDrawSphere();
        if (self->i264) {
            color.r = 0xFF;
            color.g = 0xFF;
            color.b = 0;
            color.a = 0x60;
            PSMTXIdentity(&tmp);
            BowVec3 sc(0.5f, 0.5f, 0.5f);
            PSMTXScaleApply(&tmp, &tmp, sc.x, sc.y, sc.z);
            BowVec3 tr = self->s.pos + self->s.axis[1] * (0.5f + (self->ptScale - self->height)) +
                         self->s.axis[0] * -0.5f;
            PSMTXTransApply(&tmp, &tmp, tr.x, tr.y, tr.z);
            EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_SPHERE_8X16, tmp, color);
        }
        if (self->b2a8) {
            color.r = 0;
            color.g = 0;
            color.b = 0xFF;
            color.a = 0x60;
            PSMTXIdentity(&tmp);
            BowVec3 sc(0.5f, 0.5f, 0.5f);
            PSMTXScaleApply(&tmp, &tmp, sc.x, sc.y, sc.z);
            BowVec3 tr = self->s.pos + self->s.axis[1] * (0.5f + (self->ptScale - self->height)) +
                         self->s.axis[0] * 0.5f;
            PSMTXTransApply(&tmp, &tmp, tr.x, tr.y, tr.z);
            EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_SPHERE_8X16, tmp, color);
        }
    }
    if (drawPts) {
        EGG::DrawGX::BeginDrawSphere();
        for (int i = 0; i < 8; i++) {
            color.r = 0;
            color.g = 0;
            color.b = 0xFF;
            color.a = 0xA0;
            BowVec3 p;
            f32 r;
            BowVec3 d;
            fn_804E4B58(self, i, &p, &r, &d);
            PSMTXIdentity(&tmp);
            BowVec3 sc(r, r, r);
            PSMTXScaleApply(&tmp, &tmp, sc.x, sc.y, sc.z);
            BowVec3 tr(p.x, p.y, p.z);
            PSMTXTransApply(&tmp, &tmp, tr.x, tr.y, tr.z);
            EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_SPHERE_8X16, tmp, color);
        }
    }
    if (drawRings) {
        EGG::DrawGX::BeginDrawSphere();
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 16; j++) {
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0;
                color.a = 0xFF;
                f32 a = 2.0f * (3.14159f * (j / 16.0f));
                PSMTXIdentity(&tmp);
                BowVec3 sc(0.05f, 0.05f, 0.05f);
                PSMTXScaleApply(&tmp, &tmp, sc.x, sc.y, sc.z);
                BowVec3 tr(self->a254[i] * BowCosF(a), (self->ptScale / 10.0f) * i - self->height,
                           self->a254[i] * BowSinF(a));
                PSMTXTransApply(&tmp, &tmp, tr.x, tr.y, tr.z);
                PSMTXConcat(&m, &tmp, &tmp);
                EGG::DrawGX::DrawDLWorld(EGG::DrawGX::DL_SPHERE_4X8, tmp, color);
            }
        }
    }
    if (drawPts || drawRings) {
        BowVec3 line[2];
        line[0] = -self->s.axis[0] * 1.6f + self->s.pos;
        line[1] = self->s.axis[0] * 1.6f + self->s.pos;
        color.r = 0xFF;
        color.g = 0;
        color.b = 0;
        color.a = 0xFF;
        EGG::DrawGX::BeginDrawLine(EGG::DrawGX::COLORCHAN_COLOR, EGG::DrawGX::ZMODE_OPA);
        EGG::DrawGX::DrawLine((const nw4r::math::VEC3*)line, 2, color, 8);
        line[0] = -self->s.axis[2] * 1.6f + self->s.pos;
        line[1] = self->s.axis[2] * 1.6f + self->s.pos;
        color.r = 0;
        color.g = 0xFF;
        color.b = 0;
        color.a = 0xFF;
        EGG::DrawGX::BeginDrawLine(EGG::DrawGX::COLORCHAN_COLOR, EGG::DrawGX::ZMODE_OPA);
        EGG::DrawGX::DrawLine((const nw4r::math::VEC3*)line, 2, color, 8);
    }
}

}  // extern "C"
