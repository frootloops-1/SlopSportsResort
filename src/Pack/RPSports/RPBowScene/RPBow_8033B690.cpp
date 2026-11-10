// Resort (RZTE01_01) port of Wii Sports RPBow_8033B690.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_8033B690: Bowling::LaneContext virtuals (vtable lbl_803CA5F0, slots
// 0x20..0x40): pin/ball contact, ball vs lane collision and lane updates.
// Class and field names are unknown; the functions keep their fn_ names and
// take the object as an explicit pointer. Field names are inferred from use.
//
// Functions are written in ASCENDING address order with `#pragma
// defer_codegen off` (the unit is built with -inline deferred).
//
// Matching notes:
// - ogws_fn_8033B88C is the base-lane version of RPBow_80340C34's ogws_fn_80341CD8
//   (same code without the obstacle cells); the effect-position ball pointer
//   is the same `ball` local reloaded each time.
// - the ball radius gBowlingPhysicsData.f110 is read through an inline
//   accessor (BowBallR): with direct accesses fn_804DFFA0's callee-saved FPR
//   coloring (and fn_804DEC54's load order) comes out wrong.
// - pin sample radii are read into a named local before the point expression
//   (f32 r = pin->mpRadii[m]); in the mirrored point the radius is passed
//   after -fwd (BowScaleRev(r = ..., -fwd)) so its reload follows the -fwd
//   temp stores like the original.
// - fn_804E1A18: the per-pin pose matrices are built and thrown away
//   (BowGetMtx(...) as an expression statement, i before j) and the
//   inverses copied; the k loop reads the sphere position through
//   pi->sph[k] and the radius through ri.p[k] (two induction pointers).
// - local VEC3s that are assigned (not initialised) keep the member-wise
//   copy from a temporary; arguments passed to fn_804EB664 by reference
//   become function-level temporaries, inline-helper temporaries are
//   stacked bottom-up (BowResetAxes).

#pragma defer_codegen off

#include <Pack/RPUtility/RPUtlRandom.h>

extern "C" {
f32 PSVECMag(const void*);
void PSVECNormalize(const void*, void*);
void PSVECCrossProduct(const void*, const void*, void*);
void PSMTXMultVec(const void*, const void*, void*);
}

// MSL_C fabs/fabsf as defined in MSL_SS/cmath (header not included, same as RPBow_803381DC). The
// (float)fabs((double)x) inline boundary is what matches for the contact speeds vi/vj in fn_804E1A18
// (plain __fabs, and the real <cmath>, colour them differently).
inline double fabs(double f) {
    return __fabs(f);
}

inline float fabsf(float f) {
    return (float)fabs((double)f);
}

namespace nw4r {
namespace math {
struct _VEC3 {
    f32 x, y, z;
};

struct VEC3;
static inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB);
static inline VEC3* VEC3Sub(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB);
static inline VEC3* VEC3Scale(register VEC3* pOut, register const VEC3* pIn, register f32 scale);

struct VEC3 : _VEC3 {
    VEC3() {}
    VEC3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    VEC3 operator-() const {
        return VEC3(-x, -y, -z);
    }
    VEC3 operator+(const VEC3& rRhs) const {
        VEC3 out;
        VEC3Add(&out, this, &rRhs);
        return out;
    }
    VEC3 operator-(const VEC3& rRhs) const {
        VEC3 out;
        VEC3Sub(&out, this, &rRhs);
        return out;
    }
    VEC3 operator*(f32 f) const {
        VEC3 out;
        VEC3Scale(&out, this, f);
        return out;
    }
    VEC3& operator*=(f32 f) {
        VEC3Scale(this, this, f);
        return *this;
    }
    VEC3& operator+=(const VEC3& rRhs) {
        VEC3Add(this, this, &rRhs);
        return *this;
    }
    VEC3& operator-=(const VEC3& rRhs) {
        VEC3Sub(this, this, &rRhs);
        return *this;
    }
};

static inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB) {
    register f32 work0, work1, work2;
    asm {
        psq_l  work0, 0(pA), 0, 0
        psq_l  work1, 0(pB), 0, 0
        ps_add work2, work0, work1
        psq_st work2, 0(pOut), 0, 0
        psq_l  work0, 8(pA), 1, 0
        psq_l  work1, 8(pB), 1, 0
        ps_add work2, work0, work1
        psq_st work2, 8(pOut), 1, 0
    }
    return pOut;
}

static inline VEC3* VEC3Sub(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB) {
    register f32 work0, work1, work2;
    asm {
        psq_l  work0, 0(pA), 0, 0
        psq_l  work1, 0(pB), 0, 0
        ps_sub work2, work0, work1
        psq_st work2, 0(pOut), 0, 0
        psq_l  work0, 8(pA), 1, 0
        psq_l  work1, 8(pB), 1, 0
        ps_sub work2, work0, work1
        psq_st work2, 8(pOut), 1, 0
    }
    return pOut;
}

static inline VEC3* VEC3Scale(register VEC3* pOut, register const VEC3* pIn, register f32 scale) {
    register f32 work0, work1;
    asm {
        psq_l    work0, 0(pIn), 0, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, 0(pOut), 0, 0
        psq_l    work0, 8(pIn), 1, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, 8(pOut), 1, 0
    }
    return pOut;
}
static inline f32 VEC3Dot(register const VEC3* pA, register const VEC3* pB) {
    register f32 dot;
    register f32 work0, work1, work2, work3;
    asm {
        psq_l   work0, 4(pA), 0, 0
        psq_l   work1, 4(pB), 0, 0
        ps_mul  work0, work0, work1
        psq_l   work3, 0(pA), 1, 0
        psq_l   work2, 0(pB), 1, 0
        ps_madd work1, work3, work2, work0
        ps_sum0 dot, work1, work0, work0
    }
    return dot;
}

static inline f32 VEC3SquareMag(register const VEC3* pVec) {
    register f32 yz, x, t, ret;
    asm {
        psq_l   yz, 4(pVec), 0, 0
        psq_l   x, 0(pVec), 1, 0
        ps_mul  yz, yz, yz
        ps_madd t, x, x, yz
        ps_sum0 ret, t, yz, yz
    }
    return ret;
}

struct MTX34 {
    f32 m[3][4];
};

VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pMtx, const VEC3* pVec);
}  // namespace math
}  // namespace nw4r

namespace EGG {
struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(const nw4r::math::VEC3& rVec) : VEC3(rVec.x, rVec.y, rVec.z) {}
    Vector3f(f32 fx, f32 fy, f32 fz) : VEC3(fx, fy, fz) {}
    ~Vector3f() {}

    Vector3f& operator=(const Vector3f& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }

    Vector3f operator+(const Vector3f& rRhs) const;
    Vector3f operator*(f32 f) const;
};
}  // namespace EGG

class RPSysEffect {
public:
    RPSysEffect(const char* pName, u32 drawGroup, u32 drawScene);
    virtual ~RPSysEffect();
    virtual bool create();
    virtual void setScale(const nw4r::math::VEC3& rScale);
    virtual void setPos(const nw4r::math::VEC3& rPosition);
    virtual void update();

private:
    u8 mData[0x7C];
};

// Copy of Bowling::gBowlingPhysicsData (layout from the member-wise copy in
// fn_804F1F3C; only the fields used here are known).
struct BowPhysData {
    u8 b000;
    u8 b001;
    u8 b002;
    u8 b003;
    u8 b004;
    u8 b005;
    u8 b006;
    f32 f008;
    f32 f00C;
    f32 f010;
    f32 f014;
    f32 f018;
    f32 f01C;
    f32 f020;
    f32 f024;
    f32 f028;
    f32 f02C;
    f32 f030;
    f32 f034;
    f32 f038;
    f32 f03C;
    f32 f040;
    f32 f044;
    f32 f048;
    f32 f04C;
    f32 f050;
    f32 f054;
    f32 f058;
    f32 f05C;
    f32 f060;
    f32 f064;
    f32 f068;
    f32 f06C;
    f32 f070;
    f32 f074;
    f32 f078;
    f32 f07C;
    f32 f080;
    f32 f084;
    f32 f088;
    f32 f08C;
    f32 fResort090;  // Resort: inserted word (guess position)
    f32 f090;
    f32 f094;
    f32 f098;
    f32 f09C;
    f32 f0A0;
    f32 f0A4;
    f32 f0A8;
    f32 f0AC;
    f32 f0B0;
    f32 f0B4;
    f32 f0B8;
    f32 f0BC;
    f32 f0C0;
    f32 f0C4;
    f32 f0C8;
    f32 f0CC;
    f32 f0D0;
    f32 f0D4;
    f32 f0D8;
    f32 f0DC;
    f32 f0E0;
    f32 f0E4;
    f32 f0E8;
    f32 f0EC;
    f32 f0F0;
    f32 f0F4;
    f32 f0F8;
    f32 f0FC;
    f32 f100;
    f32 fResort100;  // Resort: second inserted word (guess position)
    f32 f104;
    f32 f108;
    f32 f10C;
    f32 f110;
    f32 f114;
    f32 f118;
    f32 f11C;
    f32 f120;
    f32 f124;
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    s32 i138;
    f32 f13C;
    f32 f140;
    f32 f144;
    f32 f148;
    f32 f14C;
    f32 f150;
    f32 f154;
    f32 a158[11];
    f32 a184[8];
    f32 a1A4[8];
    f32 a1C4[16];
    f32 f204;
    f32 f208;
    f32 f20C;
    f32 f210;
    f32 f214;
    f32 f218;
    f32 f21C;
    f32 f220;
    f32 f224;
    f32 f228;
    f32 f22C;
    f32 f230;
    f32 f234;
    f32 f238;
    f32 f23C;
    s32 i240;
    u8 b244;
    u8 b245;
    u8 b246;
    u8 b247;
    f32 f248;
    f32 f24C;
    f32 f250;
    f32 f254;
    f32 f258;
    f32 f25C;
    f32 f260;
    f32 f264;
    f32 f268;
    f32 a26C[10];
    f32 a294[10];
    f32 f2BC;
    f32 f2C0;
    f32 f2C4;
    f32 f2C8;
    f32 f2CC;
};

// Bowling::gBowlingPhysicsData (Resort symbol gBowlingPhysicsData__7Bowling, size 0x2F8)
extern "C" BowPhysData gBowlingPhysicsData__7Bowling;

// Ball rigid body (RPUtl Body; virtual accessors at 0x34..0x40).
struct BowBall {
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual EGG::Vector3f* GetPos();       // 0x30 (Resort)
    virtual void SetPos(EGG::Vector3f);    // 0x38
    virtual EGG::Vector3f* GetVel();       // 0x3C
    virtual void SetVel(EGG::Vector3f);    // 0x40

    u8 pad004[0x6C - 0x4];
    f32 mRadius;                 // 0x6C
    u8 pad070[0xE0 - 0x70];
    EGG::Vector3f mAngVel;       // 0xE0
};

// VEC3 with a member-wise assignment (the rigid-body state vectors).
struct BowVec3 : nw4r::math::VEC3 {
    BowVec3() {}
    BowVec3(f32 fx, f32 fy, f32 fz) : VEC3(fx, fy, fz) {}
    BowVec3(const nw4r::math::VEC3& rVec) : VEC3(rVec) {}

    BowVec3& operator=(const BowVec3& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};

// Rigid-body state (see RPBow_80327F0C).
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
    BowVec3 spin[3];     // 0x80
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

struct BowMtx {
    f32 m[3][4];
    BowMtx() {}
    BowMtx(f32 m00, f32 m01, f32 m02, f32 m03, f32 m10, f32 m11, f32 m12, f32 m13, f32 m20,
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

struct BowPinSphere {
    nw4r::math::VEC3 pos;  // 0x00
    nw4r::math::VEC3 vel;  // 0x0C
    f32 r;                 // 0x18
};

// Pin rigid body (RPBow_80329658 body; only the members used here).
struct BowPin {
    void* vtbl;                  // 0x000
    BowBodyState s;              // 0x004
    u8 unkF8;                    // 0x0F8
    u8 padF9[0xFC - 0xF9];
    BowVec3 base;                // 0x0FC
    BowMtx mtx;                  // 0x108 (pose)
    BowMtx invMtx;               // 0x138 (inverse pose)
    f32 f168;                    // 0x168
    f32 f16C;                    // 0x16C
    BowPinSphere sph[8];         // 0x170
    u8 b250;                     // 0x250
    u8 b251;                     // 0x251
    u8 pad252[0x254 - 0x252];
    f32* mpRadii;                // 0x254
    u8 pad258[0x264 - 0x258];
    s32 i264;                    // 0x264
    u8 pad268;
    u8 b269;                     // 0x269
    u8 b26A;                     // 0x26A
    u8 pad26B;
    u32 mHitBits[8];             // 0x26C
    s32 i28C;                    // 0x28C
    u8 b290;                     // 0x290
    u8 pad291[0x298 - 0x291];
    void* mpSnd;                 // 0x298
    u8 b29C;                     // 0x29C
    u8 pad29D[0x2AC - 0x29D];
    s32 i2AC;                    // 0x2AC
    u8 pad2B0[0x2D0 - 0x2B0];
    s32 i2D0;                    // 0x2D0 (sphere count)
};

// EGG::Vector3f storage without constructors (see RPBow_803381DC).
struct BowVecPod {
    f32 x, y, z;

    BowVecPod& operator=(const BowVecPod& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
    BowVecPod& operator=(const nw4r::math::VEC3& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};

// Contact record handed to the ball solver fn_80377790 (0x20 bytes).
struct BowContact {
    union {
        f32 restitution;  // 0x00
        u32 restitutionBits;
    };
    f32 friction;         // 0x04
    f32 slidingFriction;  // 0x08
    BowVecPod normal;     // 0x0C
    f32 displacement;     // 0x18
    f32 angularLimit;     // 0x1C
};

// Solver output (POD storage so the struct has no destructor).
struct BowCorrection {
    nw4r::math::_VEC3 displacement;     // 0x00
    nw4r::math::_VEC3 velocity;         // 0x0C
    nw4r::math::_VEC3 angularVelocity;  // 0x18
};

// Compacted lane BVH hit (0x20 bytes, see RPBow_80329350).
struct BowBvhHit {
    f32 n[4];  // 0x00 normal + depth
    s32 type;  // 0x10
    f32 p[3];  // 0x14
};

// Throw state passed to the collision virtuals (Bowling::ThrowContext).
struct BowThrow {
    s32 state;              // 0x00
    u8 pad004[0x14 - 0x4];
    f32 f14;                // 0x14
    u8 pad018[0x34 - 0x18];
    nw4r::math::VEC3 v34;   // 0x34
    u8 pad040[0x60 - 0x40];
    BowContact contact;     // 0x60
    u8 pad080[0xA0 - 0x80];
    u8 bA0;                 // 0xA0
    u8 pad0A1[0xA9 - 0xA1];
    u8 bA9;                 // 0xA9
    u8 bAA;                 // 0xAA
    u8 bAB;                 // 0xAB
    u8 pad0AC[0xB4 - 0xAC];
    u8 bB4;                 // 0xB4
    u8 pad0B5[0xCC - 0xB5];
    s32 iCC;                // 0xCC
    u8 pad0D0[0xF0 - 0xD0];
    f32 fF0;                // 0xF0
    u8 pad0F4[0xF9 - 0xF4];
    u8 bF9;                 // 0xF9
    u8 bFA;                 // 0xFA
    u8 pad0FB[0x100 - 0xFB];
    u8 b100;                // 0x100
};

struct BowBvhSub {
    u8 pad00[0x10];
    f32 f10;  // 0x10
};

struct BowBvh {
    u8 pad00[0x18];
    BowBvhSub** x18;  // 0x18
};

struct BowLane {
    void* vtbl;           // 0x0
    BowPin** mpPins;      // 0x4
    BowBvh* p8;           // 0x8
    u8 pad00C[0x10 - 0xC];
    void* x10;            // 0x10
    s32 i14;              // 0x14
    s32 i18;              // 0x18 (pinCount)
    BowBall* mpBall;      // 0x1C
    void* mpSnd;          // 0x20 (guess)
    u8 pad0024[0x2BFC - 0x24];
    f32 f2BFC;            // 0x2BFC (Wii Sports 0x1F08)
    u8 pad2C00[0x2C0C - 0x2C00];
    f32 f2C0C;            // 0x2C0C (0x1F18)
    u8 pad2C10[0x2C1C - 0x2C10];
    f32 f2C1C;            // 0x2C1C (0x1F28)
    u8 pad2C20[0x2CC8 - 0x2C20];
    f32 f2CC8;            // 0x2CC8 (0x1FD4)
    u8 pad2CCC[0x2CF4 - 0x2CCC];
    u32 i2CF4;            // 0x2CF4 (0x2000)
    u8 pad2CF8[0x2D2C - 0x2CF8];
    f32 f2D2C;            // 0x2D2C (0x2014)
    u8 pad2D30b[0x2D34 - 0x2D30];
    f32 f2D34;            // (0x201C: placeholder)
    f32 f2D38;            // (0x2020)
    u8 pad2D3C[0x2D40 - 0x2D3C];
    s32 i2D40;            // (0x2028)
    u8 pad2D44[0x2D89 - 0x2D44];
    u8 b2D89;             // (0x2071)
    u8 pad2D8A[0x2D90 - 0x2D8A];
    u8 b2D90;             // (0x2078)
};

extern "C" {

void fn_804E4B58(BowPin*, int, nw4r::math::VEC3*, f32*, nw4r::math::VEC3*);
void fn_804EAEC0(BowPin*, const nw4r::math::VEC3&, const nw4r::math::VEC3&, int, int, f32);
void fn_804EB5E8(BowPin*, const BowVec3*);
void fn_804EB664(BowPin*, const nw4r::math::VEC3&);
void ogws_fn_80316070(void*, int, f32);
void ogws_fn_8031617C(void*, int, f32, f32);
void ogws_fn_8031630C(void*, int, f32, f32);
void fn_804DAAE8(BowLane*);
void fn_804DD174(BowLane*, const nw4r::math::VEC3*);
void fn_804DDDC4(void*, const nw4r::math::VEC3&, const nw4r::math::VEC3&, const nw4r::math::VEC3&);
EGG::Vector3f ogws_fn_801C4B7C(const BowBall*, const EGG::Vector3f&);
void ogws_fn_801C4C38(BowBall*, EGG::Vector3f*, EGG::Vector3f*, const EGG::Vector3f&, const EGG::Vector3f&,
                 f32, f32, f32);
double sqrt(double);
extern f32 lbl_804BF9C0;
struct BowTriHit {
    nw4r::math::VEC3 pos;     // 0x00
    nw4r::math::VEC3 normal;  // 0x0C
    f32 depth;                // 0x18
    f32 unk1C[2];             // 0x1C
};

// Lane collision triangle (same layout as the RPBow_803381DC wall triangles).
struct BowLaneTri {
    nw4r::math::VEC3 v[3];  // 0x00
    nw4r::math::VEC3 n;     // 0x24
    nw4r::math::VEC3 e[3];  // 0x30
    f32 d;                  // 0x54
};

struct BowPinCfg {
    u8 pad000[0xF4];
    f32 fF4;  // 0xF4
};

extern BowLaneTri lbl_804AA0B8[4];
extern f32 lbl_804BF9C4;
int fn_80379380(BowTriHit*, const nw4r::math::VEC3*, const BowLaneTri*, const nw4r::math::VEC3*,
                const nw4r::math::VEC3*, const nw4r::math::VEC3*, const nw4r::math::VEC3*, f32,
                f32);
int fn_804E3C0C(BowBvh*, BowBvhHit*, int, const EGG::Vector3f*, int, bool, f32);
void ogws_fn_80315A88(void*, u32, int, f32);
void ogws_fn_80315F14(void*, f32, int);
void ogws_fn_80315998(void*, u32, int, f32);
void ogws_fn_80315C58(void*, u32, int, f32);
void fn_804D9A3C(BowLane*, BowPhysData*, f32*, f32*, f32);
int ogws_fn_80323734(BowLane*, const EGG::Vector3f*, BowPhysData*);
void fn_804DDCF4(void*, BowContact*, int);
void fn_80377790(BowBall*, s32, const BowContact*, BowCorrection*, void*, bool);
int CheckBallLaneIntersection__7BowlingFPff(const EGG::Vector3f*, f32);
void ogws_fn_80315380(void*, s32);
void* ogws_fn_803394BC(void* p);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void __destroy_arr(void*, void*, unsigned long, unsigned long);

static inline void BowCalcFriction(BowLane* self, BowPhysData* data, f32* a, f32* b, f32 z) {
    fn_804D9A3C(self, data, a, b, z);
}

// Lane ball-matrix translation.
static inline nw4r::math::VEC3 BowLanePos(const BowLane* self) {
    return nw4r::math::VEC3(self->f2BFC, self->f2C0C, self->f2C1C);
}

static inline f32 BowBallR() {
    return gBowlingPhysicsData__7Bowling.f110;
}

static inline void BowAddImpulse(BowPin* pin, const BowVec3& rVec) {
    fn_804EB664(pin, rVec);
}

static inline void BowResetAxes(BowBodyState* s) {
    s->axis[0] = BowVec3(1.0f, 0.0f, 0.0f);
    s->axis[1] = BowVec3(0.0f, 1.0f, 0.0f);
    s->axis[2] = BowVec3(0.0f, 0.0f, 1.0f);
}

static inline BowMtx BowGetMtx(const BowBodyState* st) {
    return BowMtx(st->axis[0].x, st->axis[1].x, st->axis[2].x, st->pos.x, st->axis[0].y,
                  st->axis[1].y, st->axis[2].y, st->pos.y, st->axis[0].z, st->axis[1].z,
                  st->axis[2].z, st->pos.z);
}

static inline void BowSetHit(BowBvhHit* pHit, const BowTriHit& rOut, u32 type) {
    pHit->n[0] = rOut.normal.x;
    pHit->n[1] = rOut.normal.y;
    pHit->n[2] = rOut.normal.z;
    pHit->n[3] = rOut.depth;
    pHit->p[0] = rOut.pos.x;
    pHit->p[1] = rOut.pos.y;
    pHit->p[2] = rOut.pos.z;
    pHit->type = type;
}

static inline bool BowPinRecent(const BowPin* pin) {
    if (pin->i2AC == 0) {
        return false;
    }
    return pin->i2AC < 20;
}

static inline void BowAccum(nw4r::math::VEC3* pMin, nw4r::math::VEC3* pMax,
                            const nw4r::math::VEC3& rVec) {
    if (pMin->x > rVec.x) {
        pMin->x = rVec.x;
    }
    if (pMin->y > rVec.y) {
        pMin->y = rVec.y;
    }
    if (pMin->z > rVec.z) {
        pMin->z = rVec.z;
    }
    if (pMax->x < rVec.x) {
        pMax->x = rVec.x;
    }
    if (pMax->y < rVec.y) {
        pMax->y = rVec.y;
    }
    if (pMax->z < rVec.z) {
        pMax->z = rVec.z;
    }
}

static inline nw4r::math::VEC3 BowScaleRev(f32 s, const nw4r::math::VEC3& rVec) {
    nw4r::math::VEC3 out;
    nw4r::math::VEC3Scale(&out, &rVec, s);
    return out;
}

static inline bool BowGt(f32 a, f32 b) {
    return a > b;
}

void fn_804DEC54(BowLane* self, BowPin* pin, BowPhysData* data) {
    int i = 0;
    if (pin->i2D0 > 0) {
        for (; i < pin->i2D0; i++) {
            nw4r::math::VEC3 pos;
            nw4r::math::VEC3 dir;
            f32 r;
            fn_804E4B58(pin, i, &pos, &r, &dir);
            nw4r::math::VEC3 d = pos - *self->mpBall->GetPos();
            f32 mag = PSVECMag(&d);
            if (mag < r + BowBallR()) {
                f32 depth = r + BowBallR() - mag;
                nw4r::math::VEC3 n = d * (1.0f / mag);
                fn_804EAEC0(pin, pos - n * r, n * depth * data->f104, 1, 1, -1.0f);
            }
        }
    }
}

bool fn_804DEDE4(BowLane* self, BowPin* pin, BowPhysData* data, const BowThrow* thr) {
    nw4r::math::VEC3 d = pin->s.pos - pin->base;
    d.y = 0.0f;
    if (thr->f14 < 0.5f || (f32)__fabs(pin->s.pos.x - self->f2D2C) > 0.5f * data->f014) {
        return true;
    }
    return pin->s.pos.y - (data->f090 + pin->base.y) < -0.5f;
}

void ogws_fn_8033B88C(BowLane* self, BowPhysData* data, BowThrow* thr, int flag) {
    BowBvhHit hits[64];
    BowContact contacts[65];
    BowCorrection corr;
    f32 a;
    f32 b;

    (*self->p8->x18)->f10 = data->f03C;
    BowBall* ball = self->mpBall;
    int n = fn_804E3C0C(self->p8, hits, 64, ball->GetPos(), flag, !self->b2D90, ball->mRadius);

    __construct_array(contacts, (void*)ogws_fn_803394BC, (void*)ogws_fn_80315380, sizeof(BowContact), 65);

    int sideHit = 0;
    int lowHit = 0;
    if (thr->bB4) {
        BowCalcFriction(self, data, &a, &b, -150.0f);
    } else {
        BowCalcFriction(self, data, &a, &b, self->mpBall->GetPos()->z);
    }

    for (int i = 0; i < n; i++) {
        contacts[i] = thr->contact;
        contacts[i].normal.x = hits[i].n[0];
        contacts[i].normal.y = hits[i].n[1];
        contacts[i].normal.z = hits[i].n[2];
        contacts[i].displacement = hits[i].n[3];
        contacts[i].friction = a;
        contacts[i].slidingFriction = b;
        if (hits[i].type == 1) {
            sideHit = 1;
        }
        if (hits[i].type == 0 && hits[i].p[1] < 0.01f) {
            lowHit = 1;
        }
        if (!thr->bA9 && hits[i].type == 3) {
            f32 r = (-self->mpBall->GetVel()->z - data->f234) / (data->f238 - data->f234);
            if (r > 0.0f) {
                ogws_fn_80315F14(self->mpSnd, r > 1.0f ? 1.0f : r, self->b2D90);
                thr->bA9 = 1;
            }
        }
        if (self->mpBall->GetPos()->x - self->f2D2C < -4.25f ||
            self->mpBall->GetPos()->x - self->f2D2C > 4.25f) {
            contacts[i].restitution = 0.0f;
        }
        if (self->mpBall->GetPos()->z < data->f010) {
            contacts[i].friction = 0.05f;
            contacts[i].slidingFriction = 0.05f;
            if (hits[i].type == 3) {
                contacts[i].restitution = data->f120;
                thr->b100 = 1;
            } else {
                contacts[i].restitution = 0.0f;
            }
            contacts[i].angularLimit = 2.0f;
        }
    }

    if (thr->bB4) {
        f32 lim = 30.0f;
        if (self->f2CC8 < 2.4f) {
            lim = 35.0f;
        }
        if (self->f2CC8 < 3.0f) {
            lim = 34.0f;
        }
        if (!BowGt(self->f2CC8, 1.7f) || BowLanePos(self).z > lim) {
            nw4r::math::VEC3 vel = *self->mpBall->GetVel();
            vel.x *= 0.98f;
            vel.z *= 0.98f;
            self->mpBall->SetVel(vel);
        }
    }

    if (self->f2D34 > 0.0f) {
        self->mpBall->SetPos(*self->mpBall->GetPos() + nw4r::math::VEC3(0.0f, 0.0f, -0.03f));
    }

    if (thr->b100) {
        f32 z = -self->mpBall->GetPos()->z;
        f32 foul = -data->f05C;
        f32 d = foul + self->mpBall->mRadius - z;
        if (d > 0.0f) {
            contacts[n] = thr->contact;
            contacts[n].normal = nw4r::math::VEC3(0.0f, 0.0f, -1.0f);
            contacts[n].displacement = d;
            contacts[n].friction = 0.0f;
            contacts[n].slidingFriction = 0.0f;
            contacts[n].restitution = 0.0f;
            n++;
        }
    }

    if (n != 0) {
        if (self->mpBall->GetPos()->z < data->f010) {
            self->mpBall->mAngVel = self->mpBall->mAngVel * 0.95f;
        }
        fn_804DDCF4(self->x10, contacts, n);
        fn_80377790(self->mpBall, n, contacts, &corr, 0, true);
        f32 vy = self->mpBall->GetVel()->y;
        self->mpBall->SetPos(*self->mpBall->GetPos() + *(EGG::Vector3f*)&corr.displacement);
        self->mpBall->SetVel(*self->mpBall->GetVel() + *(EGG::Vector3f*)&corr.velocity);
        self->mpBall->mAngVel = self->mpBall->mAngVel + *(EGG::Vector3f*)&corr.angularVelocity;
        if (ogws_fn_80323734(self, self->mpBall->GetPos(), data) && !thr->bB4 &&
            self->mpBall->GetVel()->z < 0.0f) {
            f32 mag = PSVECMag(self->mpBall->GetVel());
            if (0.0f == mag) {
                self->mpBall->SetVel(nw4r::math::VEC3(0.0f, 0.0f, -data->f124));
            } else if (mag < data->f124) {
                nw4r::math::VEC3 dir;
                PSVECNormalize(self->mpBall->GetVel(), &dir);
                self->mpBall->SetVel(dir * data->f124);
            }
        }
        if (self->mpBall->GetPos()->z > data->f010) {
            f32 r = (-vy - data->f214) / (data->f218 - data->f214);
            if (r > 0.0f) {
                ball = self->mpBall;
                if (ball->GetPos()->y > 0.1f + ball->mRadius) {
                    if (!thr->bAB) {
                        ogws_fn_80315A88(self->mpSnd, 0x28, self->b2D90, r);
                        thr->bAB = 1;
                    }
                } else {
                    bool play = true;
                    if (sideHit) {
                        if (thr->bFA) {
                            play = false;
                        }
                        thr->bFA = 1;
                    }
                    if (play) {
                        if (!self->b2D90) {
                            ogws_fn_80315998(self->mpSnd, 1, thr->iCC / 4, r);
                        }
                        ogws_fn_80315A88(self->mpSnd, 2, self->b2D90, r);
                    }
                    if (self->b2D89 && r > 0.1f) {
                        ball = self->mpBall;
                        if ((CheckBallLaneIntersection__7BowlingFPff(
                                 ball->GetPos(), 0.5f * data->f014 + 0.8f * ball->mRadius) ||
                             self->mpBall->GetPos()->z > 0.0f) &&
                            lowHit) {
                            RPSysEffect eff2("Bow_lane01", 0, 0);
                            eff2.create();
                            f32 z = self->mpBall->GetPos()->z;
                            ball = self->mpBall;
                            eff2.setPos(nw4r::math::VEC3(self->mpBall->GetPos()->x,
                                                         ball->GetPos()->y - ball->mRadius, z));
                            eff2.update();
                        }
                    }
                }
            } else {
                f32 k = PSVECMag(self->mpBall->GetVel()) / data->f23C;
                if (self->mpBall->GetPos()->y < 0.7f) {
                    if (!thr->bAA) {
                        ogws_fn_80315A88(self->mpSnd, 0x22, self->b2D90, k);
                        thr->bAA = 1;
                    }
                    ogws_fn_80315C58(self->mpSnd, 0x13, self->b2D90, k);
                } else {
                    ogws_fn_80315C58(self->mpSnd, 0x11, self->b2D90, k);
                }
            }
        }
    }

    __destroy_arr(contacts, (void*)ogws_fn_80315380, sizeof(BowContact), 65);
}

void fn_804DFFA0(BowLane* self, BowPin* pin, BowPhysData* data, BowThrow* thr,
                 const nw4r::math::MTX34* mtx, const nw4r::math::MTX34* prevMtx,
                 const nw4r::math::MTX34* invMtx, f32 f) {
    nw4r::math::VEC3 pts[8];
    nw4r::math::VEC3 surf;
    nw4r::math::VEC3 near;
    nw4r::math::VEC3 d0 = pin->s.pos - BowLanePos(self);
    f32 lim = data->f08C - data->f090 + BowBallR();
    if (nw4r::math::VEC3SquareMag(&d0) > lim * lim) {
        return;
    }
    nw4r::math::VEC3 velMin(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 velMax(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 posMin(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 posMax(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 angMin(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 angMax(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 dir = pin->s.pos - BowLanePos(self);
    PSVECNormalize(&dir, &dir);
    nw4r::math::VEC3 wn;
    nw4r::math::VEC3TransformNormal(&wn, invMtx, &dir);
    nw4r::math::VEC3 fwd;
    nw4r::math::VEC3 side;
    nw4r::math::VEC3 up(0.0f, 1.0f, 0.0f);
    PSVECCrossProduct(&up, &wn, &side);
    PSVECNormalize(&side, &side);
    PSVECCrossProduct(&up, &side, &fwd);
    PSVECNormalize(&fwd, &fwd);

    bool hit = false;
    for (int m = 0; m < 10; m++) {
        pts[0] = nw4r::math::VEC3(0.0f, pin->f168 / 10.0f * m - pin->f16C, 0.0f) +
                 fwd * pin->mpRadii[m];
        f32 r1 = pin->mpRadii[m + 1];
        pts[1] = nw4r::math::VEC3(0.0f, pin->f168 / 10.0f * (m + 1) - pin->f16C, 0.0f) + fwd * r1;
        nw4r::math::VEC3 e = pts[1] - pts[0];
        PSVECNormalize(&e, &e);
        nw4r::math::VEC3 c;
        PSVECCrossProduct(&e, &side, &c);
        pts[2] = (pts[0] + pts[1]) * 0.5f;
        pts[3] = pts[2] + c;
        nw4r::math::VEC3 c2;
        PSVECCrossProduct(&e, &c, &c2);
        pts[4] = pts[2];
        pts[5] = pts[4] + c2;
        PSMTXMultVec(mtx, &pts[4], &pts[4]);
        PSMTXMultVec(mtx, &pts[5], &pts[5]);
        PSMTXMultVec(mtx, &pts[0], &pts[0]);
        PSMTXMultVec(mtx, &pts[1], &pts[1]);
        PSMTXMultVec(mtx, &pts[2], &pts[2]);
        PSMTXMultVec(mtx, &pts[3], &pts[3]);
        c = pts[3] - pts[2];
        c2 = pts[5] - pts[4];
        nw4r::math::VEC3 dd = BowLanePos(self) - pts[0];
        f32 h = nw4r::math::VEC3Dot(&dd, &c);
        if (h < BowBallR() && h > 0.0f) {
            nw4r::math::VEC3 ball = BowLanePos(self);
            nw4r::math::VEC3 B = BowLanePos(self) - c * BowBallR();
            nw4r::math::VEC3 a = pts[0];
            nw4r::math::VEC3 b = pts[1];
            nw4r::math::VEC3 v1 = a - ball;
            nw4r::math::VEC3 v2 = b - ball;
            nw4r::math::VEC3 v3 = B - ball;
            nw4r::math::VEC3 n1;
            PSVECCrossProduct(&v1, &v3, &n1);
            nw4r::math::VEC3 n2;
            PSVECCrossProduct(&v2, &v3, &n2);
            if (nw4r::math::VEC3Dot(&c2, &n1) * nw4r::math::VEC3Dot(&c2, &n2) <= 0.0f) {
                nw4r::math::VEC3 w1 = ball - a;
                nw4r::math::VEC3 w2 = B - a;
                nw4r::math::VEC3 w3 = b - a;
                nw4r::math::VEC3 m1;
                PSVECCrossProduct(&w1, &w3, &m1);
                nw4r::math::VEC3 m2;
                PSVECCrossProduct(&w2, &w3, &m2);
                if (nw4r::math::VEC3Dot(&c2, &m1) * nw4r::math::VEC3Dot(&c2, &m2) <= 0.0f) {
                    if (thr->state != 2) {
                        fn_804DAAE8(self);
                    }
                    thr->bF9 = 1;
                    pts[6] = BowLanePos(self) - c * h;
                    pts[7] = pts[6] + -c * (BowBallR() - h);
                    hit = true;
                    fn_804EB664(pin, -c * (BowBallR() - h) * data->f154 * 0.5f);
                    nw4r::math::VEC3 imp = c * (BowBallR() - h) * data->f154 * 0.5f;
                    BowAccum(&posMin, &posMax, imp);
                    nw4r::math::VEC3 lp;
                    PSMTXMultVec(invMtx, &pts[6], &lp);
                    nw4r::math::VEC3 wp;
                    PSMTXMultVec(prevMtx, &lp, &wp);
                    nw4r::math::VEC3 bv = ogws_fn_801C4B7C(self->mpBall, pts[6]);
                    nw4r::math::VEC3 pv = pts[6] - wp;
                    nw4r::math::VEC3 tv = thr->v34;
                    nw4r::math::VEC3 rel = tv - pv;
                    f32 vn = -nw4r::math::VEC3Dot(&rel, &c);
                    f32 kRest = self->mpBall->GetPos()->z < data->f010 ? data->f0B0 : data->f0A8;
                    f32 kFric = self->mpBall->GetPos()->z < data->f010 ? data->f0B4 : data->f0AC;
                    f32 s = vn * kRest;
                    c = -c;
                    if (s < 0.0f) {
                        s = 0.0f;
                    }
                    fn_804EAEC0(pin, pts[6], c * s, 1, 1, thr->fF0);
                    if (vn > 0.0f) {
                        EGG::Vector3f dv;
                        EGG::Vector3f dw;
                        ogws_fn_801C4C38(self->mpBall, &dv, &dw, pts[6], c * (vn * kFric), 1.0f, data->f084,
                                    0.0f);
                        BowAccum(&velMin, &velMax, dv);
                        BowAccum(&angMin, &angMax, dw);
                    }
                    thr->bA0 = 1;
                    nw4r::math::VEC3 t = bv * f;
                    f32 dt = nw4r::math::VEC3Dot(&c, &t);
                    if (dt + s > 0.0f) {
                        fn_804EAEC0(pin, pts[6], t, 1, 1, -1.0f);
                    }
                    if (!pin->b269 && data->b244) {
                        f32 v = (vn - data->f21C) / (data->f220 - data->f21C);
                        if (v > 0.0f) {
                            if (v > 1.0f) {
                                v = 1.0f;
                            }
                            ogws_fn_8031630C(self->mpSnd, self->b2D90, v, v);
                            pin->b269 = 1;
                        }
                        if (vn > data->f268 && self->b2D89 && BowLanePos(self).z > data->f010) {
                            fn_804DD174(self, &pts[6]);
                        }
                    }
                }
            }
        }
    }

    if (!hit) {
        f32 minDist = 100000000.0f;
        nw4r::math::VEC3 best;
        nw4r::math::VEC3 bestN;
        for (int m = 0; m < 11; m++) {
            f32 r = pin->mpRadii[m];
            nw4r::math::VEC3 q = nw4r::math::VEC3(0.0f, pin->f168 / 10.0f * m - pin->f16C, 0.0f) +
                                 fwd * r;
            PSMTXMultVec(mtx, &q, &q);
            nw4r::math::VEC3 d = q - BowLanePos(self);
            f32 dist = PSVECMag(&d);
            if (dist < BowBallR() && dist < minDist) {
                minDist = dist;
                d *= 1.0f / dist;
                best = q;
                bestN = d;
                near = BowLanePos(self) + d * dist;
                surf = near + d * (BowBallR() - dist);
            }
        }
        if (minDist < 1000.0f) {
            fn_804EB664(pin, (surf - near) * data->f154 * 0.5f);
            nw4r::math::VEC3 imp = -(surf - near) * data->f154 * 0.5f;
            BowAccum(&posMin, &posMax, imp);
            if (thr->state != 2) {
                fn_804DAAE8(self);
            }
            thr->bF9 = 1;
            nw4r::math::VEC3 lp;
            PSMTXMultVec(invMtx, &best, &lp);
            nw4r::math::VEC3 wp;
            PSMTXMultVec(prevMtx, &lp, &wp);
            nw4r::math::VEC3 bv = ogws_fn_801C4B7C(self->mpBall, best);
            nw4r::math::VEC3 pv = best - wp;
            nw4r::math::VEC3 tv = thr->v34;
            nw4r::math::VEC3 rel = tv - pv;
            f32 vn = nw4r::math::VEC3Dot(&rel, &bestN);
            f32 kRest = self->mpBall->GetPos()->z < data->f010 ? data->f0B0 : data->f0A8;
            f32 kFric = self->mpBall->GetPos()->z < data->f010 ? data->f0B4 : data->f0AC;
            f32 s = vn * kRest;
            if (s < 0.0f) {
                s = 0.0f;
            }
            fn_804EAEC0(pin, best, bestN * s, 1, 1, thr->fF0);
            if (vn > 0.0f) {
                EGG::Vector3f dv;
                EGG::Vector3f dw;
                ogws_fn_801C4C38(self->mpBall, &dv, &dw, best, -bestN * (vn * kFric), 1.0f, data->f084,
                            0.0f);
                BowAccum(&velMin, &velMax, dv);
                BowAccum(&angMin, &angMax, dw);
            }
            thr->bA0 = 1;
            nw4r::math::VEC3 t = bv * f;
            if (s + nw4r::math::VEC3Dot(&bestN, &t) > 0.0f) {
                fn_804EAEC0(pin, best, t, 1, 1, -1.0f);
            }
            if (!pin->b269 && data->b244) {
                f32 v = (vn - data->f21C) / (data->f220 - data->f21C);
                if (v > 0.0f) {
                    if (v > 1.0f) {
                        v = 1.0f;
                    }
                    ogws_fn_8031630C(self->mpSnd, self->b2D90, v, v);
                    pin->b269 = 1;
                }
                if (vn > data->f268 && self->b2D89 && BowLanePos(self).z > data->f010) {
                    fn_804DD174(self, &best);
                }
            }
        }
    }

    self->mpBall->SetPos(*self->mpBall->GetPos() + posMin + posMax);
    self->mpBall->SetVel(*self->mpBall->GetVel() + velMin + velMax);
    self->mpBall->mAngVel = self->mpBall->mAngVel + angMin + angMax;
    fn_804DDDC4(self->x10, posMin + posMax, velMin + velMax, angMin + angMax);
}

// MATCH-PENDING (R17): one-field holder for the per-pin sphere base pointer.
// IRO_ScalarizeClassDataMembers turns ri.p/rj.p into early IRO @temps, so the
// two base pointers are coloured among the loop temporaries (sj r29, si r23)
// as in the original; named BowPinSphere* locals rank below every IRO temp
// (r20/r19). The real source probably reaches the spheres through some
// struct/accessor that is not modelled here.
struct BowSphRef {
    BowPinSphere* p;
};

void fn_804E1A18(BowLane* self, BowPhysData* data) {
    for (int i = 0; i < self->i14 - 1; i++) {
        if (!self->mpPins[i]->b251) {
            continue;
        }
        for (int j = i + 1; j < self->i14; j++) {
            if (!self->mpPins[j]->b251) {
                continue;
            }
            BowPin* pi = self->mpPins[i];
            BowPin* pj = self->mpPins[j];
            f32 dx = pi->s.pos.x - pj->s.pos.x;
            if (dx < -5.0f || dx > 5.0f) {
                continue;
            }
            f32 dz = pi->s.pos.z - pj->s.pos.z;
            if (dz < -5.0f || dz > 5.0f) {
                continue;
            }
            if (dx * dx + dz * dz > 25.0f) {
                continue;
            }

            BowSphRef ri = {pi->sph};
            BowSphRef rj = {pj->sph};
            bool nearI[16];
            bool nearJ[16];
            nw4r::math::VEC3 diff;
            for (int k = 0; k < 8; k++) {
                diff = pi->sph[k].pos - self->mpPins[j]->s.pos;
                f32 r = 2.5f + ri.p[k].r;
                if (nw4r::math::VEC3SquareMag(&diff) < r * r) {
                    nearI[k] = true;
                } else {
                    nearI[k] = false;
                }
                diff = pj->sph[k].pos - self->mpPins[i]->s.pos;
                r = 2.5f + rj.p[k].r;
                if (nw4r::math::VEC3SquareMag(&diff) < r * r) {
                    nearJ[k] = true;
                } else {
                    nearJ[k] = false;
                }
            }

            for (int a = 0; a < 8; a++) {
                if (!nearI[a]) {
                    continue;
                }
                nw4r::math::VEC3 posI = ri.p[a].pos;
                nw4r::math::VEC3 velI = ri.p[a].vel;
                f32 rI = ri.p[a].r;
                for (int b = 0; b < 8; b++) {
                    if (!nearJ[b]) {
                        continue;
                    }
                    nw4r::math::VEC3 posJ = rj.p[b].pos;
                    nw4r::math::VEC3 velJ = rj.p[b].vel;
                    f32 rJ = rj.p[b].r;
                    nw4r::math::VEC3 d = posI - posJ;
                    f32 rsum = rI + rJ;
                    f32 len2 = nw4r::math::VEC3SquareMag(&d);
                    if (len2 < rsum * rsum) {
                        f32 dist = sqrt(len2);
                        nw4r::math::VEC3 n = d * (1.0f / dist);
                        f32 pen = 0.5f * (rI + rJ - dist);
                        BowGetMtx(&self->mpPins[i]->s);
                        BowGetMtx(&self->mpPins[j]->s);
                        BowMtx invI = self->mpPins[i]->invMtx;
                        BowMtx invJ = self->mpPins[j]->invMtx;
                        nw4r::math::VEC3 cpI;
                        nw4r::math::VEC3 cpJ;
                        nw4r::math::VEC3 lI;
                        nw4r::math::VEC3 lJ;
                        cpI = posI - n * rI;
                        cpJ = posJ + n * rJ;
                        PSMTXMultVec(&invI, &cpI, &lI);
                        PSMTXMultVec(&invJ, &cpJ, &lJ);
                        nw4r::math::VEC3 oI;
                        nw4r::math::VEC3 oJ;
                        PSMTXMultVec(&self->mpPins[i]->mtx, &lI, &oI);
                        PSMTXMultVec(&self->mpPins[j]->mtx, &lJ, &oJ);
                        velI = cpI - oI;
                        velJ = cpJ - oJ;
                        nw4r::math::VEC3 rel = velJ - velI;
                        f32 vr = 0.5f * nw4r::math::VEC3Dot(&n, &rel);
                        f32 vi = fabsf(nw4r::math::VEC3Dot(&n, &velI));
                        f32 vj = fabsf(nw4r::math::VEC3Dot(&n, &velJ));
                        if (vi < lbl_804BF9C0) {
                            vi = lbl_804BF9C0;
                        }
                        if (vj < lbl_804BF9C0) {
                            vj = lbl_804BF9C0;
                        }
                        f32 imp = pen * data->f068 + vr * data->f06C;
                        nw4r::math::VEC3 impI = n * imp * (vj / (vi + vj));
                        nw4r::math::VEC3 impJ = -n * imp * (vi / (vi + vj));
                        if (vr > 0.0f) {
                            impI += n * data->f0C0 * vr;
                            impJ += -n * data->f0C0 * vr;
                        }
                        fn_804EAEC0(self->mpPins[i], posI - n * rI, impI, 1, 1, data->f0C4);
                        fn_804EAEC0(self->mpPins[j], posJ + n * rJ, impJ, 1, 1, data->f0C4);
                        if (!(self->mpPins[i]->mHitBits[j / 30] & (1 << (j % 30))) && data->b245) {
                            f32 v = (vr - data->f224) / (data->f228 - data->f224);
                            if (v > 0.0f) {
                                if (v > 1.0f) {
                                    v = 1.0f;
                                }
                                ogws_fn_8031617C(self->mpPins[i]->mpSnd, self->b2D90, v, v);
                                self->mpPins[i]->mHitBits[j / 30] |= 1 << (j % 30);
                                self->mpPins[j]->mHitBits[i / 30] |= 1 << (i % 30);
                            }
                        }
                    }
                }
            }
        }
    }
}

void fn_804E2574(BowLane* self, BowPin* pin, BowThrow* thr) {
    if (self->f2D34 > 0.0f) {
        f32 lim = self->f2D38 - self->f2D34;
        if (pin->i28C == 0) {
            for (int i = 0; i < 8; i++) {
                nw4r::math::VEC3 pos;
                nw4r::math::VEC3 dir;
                f32 r;
                fn_804E4B58(pin, i, &pos, &r, &dir);
                f32 front = pos.z + r;
                if (front > lim) {
                    f32 depth = front - lim;
                    f32 push = 0.1f * depth + 0.3f * dir.z;
                    fn_804EAEC0(pin, pos + nw4r::math::VEC3(0.0f, 0.0f, r),
                                nw4r::math::VEC3(0.0f, 0.0f, -push), 1, 1, -1.0f);
                    if (thr->f14 > 0.98f && RPUtlRandom::getU32() % 500 == 0) {
                        fn_804EAEC0(pin, pin->s.pos + nw4r::math::VEC3(0.0f, 1.0f, 0.0f),
                                    nw4r::math::VEC3(0.0f, 0.0f, -0.6f), 1, 1, -1.0f);
                    }
                }
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        nw4r::math::VEC3 pos;
        nw4r::math::VEC3 dir;
        f32 r;
        fn_804E4B58(pin, i, &pos, &r, &dir);
        if (pos.z + r > self->f2D38) {
            f32 depth = pos.z + r - self->f2D38;
            f32 push = 0.1f * depth + 0.3f * dir.z;
            fn_804EAEC0(pin, pos + nw4r::math::VEC3(0.0f, 0.0f, r),
                        nw4r::math::VEC3(0.0f, 0.0f, -push), 1, 1, -1.0f);
        }
    }
}

void fn_804E2870(BowLane* self, BowPin* pin, BowPhysData* data) {
    f32 g;
    if ((self->b2D90 && self->i2D40 == 0) || pin->b250) {
        g = -0.004f;
    } else if ((self->i2CF4 & 0x3FF) == 0x240) {
        g = -0.004f;
    } else {
        g = data->f070;
    }
    switch (pin->i28C) {
    case 0: {
        BowVec3 v(0.0f, g, 0.0f);
        fn_804EB5E8(pin, &v);
        break;
    }
    case 1: {
        BowVec3 v(0.0f, 0.05f, 0.0f);
        fn_804EB664(pin, v);
        if (pin->s.pos.y > 8.0f) {
            pin->s.pos = nw4r::math::VEC3(pin->base.x, 8.0f, pin->base.z);
            BowResetAxes(&pin->s);
        }
        break;
    }
    case 2:
        break;
    case 3: {
        f32 v = data->f090 - pin->s.pos.y;
        if (v < -0.05f) {
            v = -0.05f;
        }
        BowAddImpulse(pin, BowVec3(0.0f, v, 0.0f));
        break;
    }
    }
}

void fn_804E2A24(BowLane* self, BowPin* pin, BowPhysData* data, BowThrow* thr,
                 const nw4r::math::MTX34* mtx, const nw4r::math::MTX34* prevMtx,
                 const nw4r::math::MTX34* rotMtx) {
    if (pin->i264 != 0) {
        return;
    }
    if (pin->i28C == 1) {
        return;
    }
    nw4r::math::VEC3 nrm(0.0f, 1.0f, 0.0f);
    nw4r::math::VEC3 pt(0.0f, 0.0f, 0.0f);
    nw4r::math::VEC3 wn;
    nw4r::math::VEC3TransformNormal(&wn, rotMtx, &nrm);
    nw4r::math::VEC3 fwd;
    nw4r::math::VEC3 side;
    nw4r::math::VEC3 up(0.0f, 1.0f, 0.0f);
    if (nw4r::math::VEC3Dot(&up, &wn) >= 0.999999f) {
        side = nw4r::math::VEC3(1.0f, 0.0f, 0.0f);
    } else {
        PSVECCrossProduct(&up, &wn, &side);
        PSVECNormalize(&side, &side);
    }
    PSVECCrossProduct(&up, &side, &fwd);
    PSVECNormalize(&fwd, &fwd);

    for (int m = 0; m < 11; m++) {
        if (thr->state != 2 && m != 0) {
            break;
        }
        for (int q = 0; q < 2; q++) {
            if (q != 0 && m != 0) {
                continue;
            }
            nw4r::math::VEC3 base(0.0f, pin->f168 / 10.0f * m - pin->f16C, 0.0f);
            f32 r = pin->mpRadii[m];
            nw4r::math::VEC3 p = base + fwd * r;
            if (q != 0) {
                p = base + BowScaleRev(r = pin->mpRadii[m], -fwd);
            }
            nw4r::math::VEC3 wp;
            PSMTXMultVec(mtx, &p, &wp);
            nw4r::math::VEC3 wp2;
            PSMTXMultVec(prevMtx, &p, &wp2);
            if (wp.x - self->f2D2C > 0.5f * data->f014) {
                continue;
            }
            if (wp.x - self->f2D2C < 0.5f * -data->f014) {
                continue;
            }
            nw4r::math::VEC3 dd = wp - pt;
            f32 depth = -nw4r::math::VEC3Dot(&dd, &nrm);
            if (depth > 0.0f) {
                nw4r::math::VEC3 vel = wp - wp2;
                f32 vn = -nw4r::math::VEC3Dot(&vel, &nrm);
                fn_804EB664(pin, nrm * depth * data->f154);
                if (vn < 0.0f) {
                    continue;
                }
                if (vn < depth) {
                    vn = depth;
                }
                fn_804EAEC0(pin, wp, nrm * (vn * data->f09C + data->f098), 1, 1, data->f0F8);
                if (!pin->b26A && data->b246 && m != 0) {
                    f32 v = (vn - data->f22C) / (data->f230 - data->f22C);
                    if (v > 0.0f) {
                        if (v > 1.0f) {
                            v = 1.0f;
                        }
                        ogws_fn_80316070(pin->mpSnd, self->b2D90, v);
                        pin->b26A = 1;
                    }
                }
                nw4r::math::VEC3 h = vel;
                h.y = 0.0f;
                if (0.0f != h.x * h.x + h.z * h.z) {
                    nw4r::math::VEC3 fr = -h;
                    PSVECNormalize(&fr, &fr);
                    fr *= data->f0A0 * vn;
                    if (nw4r::math::VEC3SquareMag(&fr) > nw4r::math::VEC3SquareMag(&h)) {
                        fn_804EAEC0(pin, wp, -h, 1, 1, data->f0A4);
                    } else {
                        fn_804EAEC0(pin, wp, fr, 1, 1, data->f0A4);
                    }
                }
            }
        }
    }
}

void fn_804E3044(BowLane* self, BowPin* pin, BowPhysData* data, BowPinCfg* cfg, BowThrow* thr,
                 const nw4r::math::MTX34* prevMtx, const nw4r::math::MTX34* invMtx, int flag) {
    bool side = self->b2D90 && self->i2D40 != 2;
    if (pin->i28C != 0) {
        return;
    }
    if (pin->i264 == 0) {
        nw4r::math::VEC3 d = pin->base - pin->s.pos;
        int stand = 0;
        if (nw4r::math::VEC3SquareMag(&d) < lbl_804BF9C4 * lbl_804BF9C4 && thr->f14 > 0.9f) {
            stand = 1;
        }
        for (int i = 0; i < 8; i++) {
            nw4r::math::VEC3 pos;
            nw4r::math::VEC3 dir;
            f32 r;
            fn_804E4B58(pin, i, &pos, &r, &dir);
            if (!stand) {
                f32 k = i == 0 ? 1.0f : 1.3f;
                if (pos.z < data->f010 + r - k) {
                    pin->i264 = 1;
                    pin->i2AC = 1;
                }
                if ((f32)__fabs(pos.x - self->f2D2C) > 0.5f * data->f014) {
                    pin->i264 = 1;
                    pin->i2AC = 1;
                }
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        BowBvhHit hits[64];
        BowTriHit out;
        nw4r::math::VEC3 pos;
        nw4r::math::VEC3 dir;
        f32 r;
        fn_804E4B58(pin, i, &pos, &r, &dir);
        if (i == 7) {
            r = 0.494f;
        }
        (*self->p8->x18)->f10 = data->f038;
        int n = fn_804E3C0C(self->p8, hits, 64, (const EGG::Vector3f*)&pos, flag, false, r);
        if (!self->b2D90 || self->i2D40 == 2) {
            for (int t = 0; t < 4; t++) {
                const BowLaneTri* tri = &lbl_804AA0B8[t];
                if (fn_80379380(&out, &pos, tri, &tri->n, &tri->e[0], &tri->e[1], &tri->e[2], r,
                                tri->d) &&
                    n < 64) {
                    BowSetHit(&hits[n], out, 6);
                    n++;
                }
            }
        }
        for (int k = 0; k < n; k++) {
            nw4r::math::VEC3 hn = *(nw4r::math::VEC3*)hits[k].n;
            nw4r::math::VEC3 lp;
            nw4r::math::VEC3 wp2;
            f32 depth = hits[k].n[3];
            nw4r::math::VEC3 p = pos + -hn * r;
            PSMTXMultVec(invMtx, &p, &lp);
            PSMTXMultVec(prevMtx, &lp, &wp2);
            dir = p - wp2;
            f32 vn = -nw4r::math::VEC3Dot(&dir, &hn);
            if (pin->i264 == 0 && hits[k].type == 0) {
                continue;
            }
            pin->i264 = 1;
            f32 s = depth * data->f060 + vn * data->f064;
            nw4r::math::VEC3 imp = hn * s;
            if (pin->mpSnd && !pin->b26A && data->b246 &&
                (hits[k].type != 0 || !BowPinRecent(pin))) {
                f32 v = (vn - data->f22C) / (data->f230 - data->f22C);
                if (v > 0.0f) {
                    if (v > 1.0f) {
                        v = 1.0f;
                    }
                    if (flag == 0) {
                        v = 0.5f * RPUtlRandom::getF32() + 0.3f;
                    }
                    ogws_fn_80316070(pin->mpSnd, self->b2D90, v);
                    pin->b26A = 1;
                }
            }
            if (hits[k].type == 2) {
                if (vn > 0.0f) {
                    imp += hn * vn * data->f0E8;
                }
            } else if (hits[k].type == 3) {
                if (vn > 0.0f) {
                    imp += hn * vn * data->f0EC;
                }
            } else if (hits[k].type == 6) {
                if (vn > 0.0f) {
                    if (cfg) {
                        imp += hn * vn * cfg->fF4;
                    } else {
                        imp += hn * vn * data->f140;
                    }
                }
                pin->b29C = 1;
            } else if (hits[k].type == 0 || hits[k].type == 1) {
                if (vn > 0.0f) {
                    imp += hn * vn * data->f0DC;
                }
            } else if (hits[k].type == 5) {
                if (vn > 0.0f) {
                    imp += hn * vn * data->f0F0;
                }
            }
            if (hits[k].type == 0) {
                fn_804EAEC0(pin, p, imp, 1, 1, data->f0FC * data->a1C4[i + 8]);
            } else if (hits[k].type == 2) {
                fn_804EAEC0(pin, p, imp, 1, 1, data->f100);
            } else if (hits[k].type == 6) {
                fn_804EAEC0(pin, p, imp, 1, 1, data->f0E4);
            } else {
                fn_804EAEC0(pin, p, imp, 1, 1, -1.0f);
            }
            if (hits[k].type == 5 && self->f2D34 > 0.0f) {
                fn_804EB664(pin, nw4r::math::VEC3(0.0f, 0.0f, -0.03f));
            }
            if (hits[k].type == 5 && vn > 0.0f && p.z < -195.0f) {
                nw4r::math::VEC3 h = dir;
                h.y = 0.0f;
                if (0.0f != h.x * h.x + h.z * h.z) {
                    nw4r::math::VEC3 fr = -h;
                    PSVECNormalize(&fr, &fr);
                    fr *= data->f0D0;
                    f32 mag = PSVECMag(&h);
                    if (PSVECMag(&fr) > mag) {
                        fn_804EAEC0(pin, p, -h, 1, 1, -1.0f);
                    } else {
                        fn_804EAEC0(pin, p, fr, 1, 1, -1.0f);
                    }
                }
                pin->b290 = 1;
            }
            if (hits[k].type != 5 && vn > 0.0f) {
                nw4r::math::VEC3 t = dir;
                t -= hn * nw4r::math::VEC3Dot(&hn, &t);
                if (0.0f != nw4r::math::VEC3SquareMag(&t)) {
                    nw4r::math::VEC3 fr = -t;
                    PSVECNormalize(&fr, &fr);
                    fr *= data->f0D4 * vn;
                    f32 mag = PSVECMag(&t);
                    if (PSVECMag(&fr) > mag) {
                        fn_804EAEC0(pin, p, -t, 1, 1, data->f0D8);
                    } else {
                        fn_804EAEC0(pin, p, fr, 1, 1, data->f0D8);
                    }
                }
            }
        }
    }

    if (side) {
        f32 w = data->f048;
        for (int i = 0; i < 8; i++) {
            nw4r::math::VEC3 pos;
            nw4r::math::VEC3 dir;
            f32 r;
            fn_804E4B58(pin, i, &pos, &r, &dir);
            f32 x = pos.x - self->f2D2C;
            f32 lo = -w + r;
            if (x < lo) {
                fn_804EB664(pin, nw4r::math::VEC3(lo - x, 0.0f, 0.0f));
            }
            f32 hi = w - r;
            if (x > hi) {
                fn_804EB664(pin, nw4r::math::VEC3(-(x - hi), 0.0f, 0.0f));
            }
        }
    }
}

}
