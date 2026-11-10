// Resort (RZTE01_01) port of Wii Sports RPBow_803381DC.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_803381DC: bowling lane object physics / debug-draw virtuals (the
// lane class extends Bowling::LaneContext past 0x2080; ogws_fn_8033B5D8 is its
// dtor). Real class and field names are unknown; the functions keep their
// fn_ names and take the object as an explicit pointer. Field names are
// inferred from use only.
//
// Functions are written in DESCENDING address order: the unit is built with
// -inline deferred, so MWCC emits them (and their .sdata2 pool entries) in
// reverse source order. The old RPBow_8033A558 split is part of this unit.
//
// Matching notes:
// - the physics-data copy in fn_804F1F3C is MWCC's member-wise struct copy;
//   its schedule depends on the exact member list (seven u8 scalars, f32
//   arrays of <= 16 words copied as blocks, no 20-word arrays, which become
//   copy loops) and on one extra (dead) store before it. x / 2.0f (not
//   0.5f * x) keeps the fmuls operand order.
// - arguments of an inlined call are evaluated right to left: the debug
//   vertices go through BowVtx(x, y, z) so z is loaded first, and the
//   friction curve call goes through BowCalcFriction.
// - stack slots: locals are sorted by size (largest highest), named locals
//   before temporaries; hence the 16-entry arrays in fn_804F0284 and the
//   0x24-byte BowTriHit.
// - VEC3 -> EGG::Vector3f conversion copies member-wise through the
//   (x, y, z) ctor (lfs/stfs, right-to-left), VEC3 copies are bitwise.
// - BowContact.restitution sits in a union so the implicit copy moves it
//   with lwz/stw like the original (the other members use lfs/stfs).

extern "C" {
void PSVECCrossProduct(const void*, const void*, void*);
void PSVECNormalize(const void*, void*);
f32 PSVECMag(const void*);
void PSMTXIdentity(void*);
void PSMTXConcat(const void*, const void*, void*);
void PSMTXScaleApply(const void*, void*, f32, f32, f32);
void PSMTXTransApply(const void*, void*, f32, f32, f32);
void PSMTXMultVec(const void*, const void*, void*);
double sqrt(double);
double __fabs(double);
}

// MSL_C fabs/fabsf as defined in MSL_SS/cmath (that header is not included here: including it drops
// fn_804F0284 to 90.5, cause not investigated). The (float)fabs((double)x) inline boundary is what matches for the
// contact speeds vi/vj (plain __fabs colours them differently).
inline double fabs(double f) {
    return __fabs(f);
}

inline float fabsf(float f) {
    return (float)fabs((double)f);
}

struct BowVec3;
static inline void BowPsSub(register BowVec3* pOut, register const BowVec3* pA,
                            register const BowVec3* pB);

struct BowVec3 {
    f32 x, y, z;

    BowVec3() {}
    BowVec3(f32 fx, f32 fy, f32 fz) : x(fx), y(fy), z(fz) {}

    BowVec3 operator-(const BowVec3& rhs) const {
        BowVec3 out;
        BowPsSub(&out, this, &rhs);
        return out;
    }
};

static inline void BowPsSub(register BowVec3* pOut, register const BowVec3* pA,
                            register const BowVec3* pB) {
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
}

static inline f32 BowPsDot(register const BowVec3* pA, register const BowVec3* pB) {
    register f32 dot;
    register f32 w0, w1, w2, w3;
    asm {
        psq_l   w0, 4(pA), 0, 0
        psq_l   w1, 4(pB), 0, 0
        ps_mul  w0, w0, w1
        psq_l   w3, 0(pA), 1, 0
        psq_l   w2, 0(pB), 1, 0
        ps_madd w1, w3, w2, w0
        ps_sum0 dot, w1, w0, w0
    }
    return dot;
}

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
    f32 rPad70;
    f32 f070;
    f32 f074;
    f32 f078;
    f32 f07C;
    f32 f080;
    f32 f084;
    f32 f088;
    f32 f08C;
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
    f32 rPadF0;
    f32 f0F0;
    f32 f0F4;
    f32 f0F8;
    f32 f0FC;
    f32 f100;
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

namespace Bowling {
extern BowPhysData gBowlingPhysicsData;
struct LaneContext;
void ogws_fn_803345F0(LaneContext*);
}

extern BowPhysData lbl_804BCE80;

struct BowWallPin {
    u8 pad000[0x168];
    f32 f168; // offset 0x168
    f32 f16C; // offset 0x16C
    u8 pad170[0x251 - 0x170];
    u8 b251;  // offset 0x251
    u8 pad252[0x2B0 - 0x252];
    s32 i2B0; // offset 0x2B0
};

struct BowWallObj8 {
    f32 f00, f04, f08, f0C, f10, f14;
};

struct BowWallTri {
    BowVec3 v[3]; // offset 0x0
    BowVec3 n;    // offset 0x24
    BowVec3 e[3]; // offset 0x30
    f32 d;        // offset 0x54
};


struct BowBall;

struct BowWallLane {
    void* vtbl;           // offset 0x0
    BowWallPin** mpPins;  // offset 0x4
    BowWallObj8* p8;      // offset 0x8
    u8 pad00C[0x14 - 0xC];
    s32 i14;              // offset 0x14
    s32 rPad18;
    BowBall* mpBall;      // offset 0x1C (Resort)
    void* mpSnd;          // offset 0x20 (guess)
    u8 pad024[0x1F08 - 0x24];
    f32 f1F08;            // offset 0x1F08 (throw ball matrix translation)
    u8 pad1F0C[0x1F18 - 0x1F0C];
    f32 f1F18;            // offset 0x1F18
    u8 pad1F1C[0x1F28 - 0x1F1C];
    f32 f1F28;            // offset 0x1F28
    u8 pad1F2C[0x2078 - 0x1F2C];
    u8 b2078;             // offset 0x2078
    u8 pad2079[0x2080 - 0x2079];
    f32 f2080;            // offset 0x2080
    f32 f2084;
    s32 i2088;
    f32 f208C;
    f32 f2090;
    f32 f2094;
    f32 f2098;
    f32 f209C;
    f32 f20A0;
    f32 f20A4;
    u8 b20A8;
    u8 pad20A9[3];
    f32 f20AC;
    f32 f20B0;
    f32 f20B4;
    f32 f20B8;
    f32 f20BC;
    f32 f20C0;
    f32 f20C4;
    f32 f20C8;
    f32 f20CC;
    f32 f20D0;
    f32 f20D4;
    f32 f20D8;
    s32 i20DC;
    s32 i20E0;
    f32 f20E4;
    f32 f20E8;
    f32 f20EC;
    f32 f20F0;
    u8 b20F4;
    u8 b20F5;
    u8 b20F6;
    u8 b20F7;
    BowWallTri tris[2][12]; // offset 0x20F8
    u32 mPinHitBits[5];     // offset 0x2938
    s32 i294C;              // offset 0x294C
    u8 b2950;               // offset 0x2950
    u8 b2951;               // offset 0x2951
    u8 pad2952[2];
    BowVec3 v2954[11];      // offset 0x2954
    u8 b29D8;               // offset 0x29D8
    // Resort layout (differs from ogws): fields seen by the Resort functions.
    u8 pad29D9[0x2DF8 - 0x29D9];
    s32 r2DF8;              // offset 0x2DF8
    s32 r2DFC;              // offset 0x2DFC
    u8 pad2E00[0x1EB28 - 0x2E00];
    u8 r1EB28;              // offset 0x1EB28
    u8 pad1EB29[3];
    s32 r1EB2C;             // offset 0x1EB2C
    u8 pad1EB30[0x1EB38 - 0x1EB30];
    u8 r1EB38;              // offset 0x1EB38
    u8 r1EB39;              // offset 0x1EB39
    u8 pad1EB3A[0x1EBC0 - 0x1EB3A];
    u8 r1EBC0;              // offset 0x1EBC0
};

static inline void BowSetObj8(BowWallObj8* p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f) {
    p->f00 = a;
    p->f04 = b;
    p->f08 = c;
    p->f0C = d;
    p->f10 = e;
    p->f14 = f;
}

namespace nw4r {
namespace math {
struct MTX34 {
    f32 m[3][4];
};

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
    VEC3(const _VEC3& rVec) {
        x = rVec.x;
        y = rVec.y;
        z = rVec.z;
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
    VEC3& operator+=(const VEC3& rRhs) {
        VEC3Add(this, this, &rRhs);
        return *this;
    }
    VEC3& operator*=(f32 f) {
        VEC3Scale(this, this, f);
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
    Vector3f operator-(const Vector3f& rRhs) const;
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
    virtual EGG::Vector3f* GetPos();       // 0x34
    virtual void SetPos(EGG::Vector3f);    // 0x38
    virtual EGG::Vector3f* GetVel();       // 0x3C
    virtual void SetVel(EGG::Vector3f);    // 0x40

    u8 pad004[0x6C - 0x4];
    f32 mRadius;                 // 0x6C
    u8 pad070[0xE0 - 0x70];
    EGG::Vector3f mAngVel;       // 0xE0
};

// EGG::Vector3f storage without constructors, so BowContact stays trivially
// constructible (its array is constructed through the explicit
// __construct_array call with the out-of-line ctor/dtor ogws_fn_803394BC/ogws_fn_80315380).
struct BowVecPod {
    f32 x, y, z;

    BowVecPod& operator=(const BowVecPod& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};

// Contact record handed to the ball solver fn_80377790 (0x20 bytes).
struct BowContact {
    union {
        f32 restitution;         // 0x00
        u32 restitutionBits;
    };
    f32 friction;                // 0x04
    f32 slidingFriction;         // 0x08
    BowVecPod normal;            // 0x0C
    f32 displacement;            // 0x18
    f32 angularLimit;            // 0x1C
};

struct BowCorrection {
    EGG::Vector3f displacement;  // 0x00
    EGG::Vector3f velocity;      // 0x0C
    EGG::Vector3f angularVelocity; // 0x18
};

// Compacted lane BVH hit (0x20 bytes, see RPBow_80329350).
struct BowBvhHit {
    f32 n[4];   // 0x00 normal + depth
    s32 type;   // 0x10
    f32 p[3];   // 0x14
};

struct BowTriHit {
    nw4r::math::VEC3 pos;    // 0x00
    nw4r::math::VEC3 normal; // 0x0C
    f32 depth;               // 0x18
    f32 unk1C[2];            // 0x1C
};

// Throw state passed to the collision virtuals (Bowling::ThrowContext, 0x108).
struct BowThrow {
    s32 state;              // 0x00
    u8 pad004[0x4C - 0x4];
    EGG::Vector3f v4C;      // 0x4C
    u8 b58;                 // 0x58
    u8 pad059[0x60 - 0x59];
    BowContact contact;     // 0x60
    u8 pad080[0xA9 - 0x80];
    u8 bA9;                 // 0xA9
    u8 pad0AA[0xB4 - 0xAA];
    u8 bB4;                 // 0xB4
    u8 pad0B5[0xCC - 0xB5];
    s32 iCC;                // 0xCC
    u8 pad0D0[0xFB - 0xD0];
    u8 bFB;                 // 0xFB
    u8 pad0FC[0x104 - 0xFC];
    s32 i104;               // 0x104
};

struct _GXColor {
    u8 r, g, b, a;
};

namespace EGG {
struct DrawGX {
    enum DL {
        DL_LINE_AXIS,
        DL_CUBE,
        DL_CUBE_WIRE,
        DL_SPHERE_4X8,
        DL_SPHERE_8X16
    };
    static void BeginDrawSphere();
    static void DrawDL(DL, const nw4r::math::MTX34&, _GXColor);
    static nw4r::math::MTX34 s_cameraMtx;
};
}  // namespace EGG

// Pin rigid body (Bowling::PinPhysicsBody; only the members used here).
struct BowPinSphere {
    nw4r::math::VEC3 pos;  // 0x00
    nw4r::math::VEC3 vel;  // 0x0C
    f32 r;                 // 0x18
};

struct BowPin {
    void* vtbl;                 // 0x000
    nw4r::math::VEC3 pos;       // 0x004
    u8 pad010[0x170 - 0x10];
    BowPinSphere sph[8];        // 0x170
    u8 pad250[0x254 - 0x250];
    f32* mpRadii;               // 0x254
    u8 pad258[0x26A - 0x258];
    u8 b26A;                    // 0x26A
    u8 pad26B;
    u32 mHitBits[11];           // 0x26C
    void* mpSnd;                // 0x298
    BowPinSphere* GetSpheres() { return sph; }
    BowPinSphere& GetSphere(int index) { return sph[index]; }
};

extern f32 lbl_804BF9C0;

namespace nw4r {
namespace snd {
class SoundArchive {
public:
    const char* GetSoundLabelString(unsigned long) const;
};
}  // namespace snd
}  // namespace nw4r

// RPSndAudioMgr view (only the members used by the inlined startSystemSe).
struct BowSnd {
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
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual int startSound(void* pHandle, u32 id); // 0xB8
    u8 p4[0xFC];
    nw4r::snd::SoundArchive* mpArchive;  // 0x100
    u8 p104[0x928 - 0x104];
    u8 mHandleSystemSe[4];               // 0x928
    u8 p92c[0x970 - 0x92C];
    u8 mIsDisableFanfare;                // 0x970
};

extern "C" BowSnd* spInstance__13RPSndAudioMgr;

static inline void BowStartSystemSe(BowSnd* pSnd, u32 id) {
    if (pSnd->mIsDisableFanfare) {
        const char* pName = pSnd->mpArchive->GetSoundLabelString(id);
        if (pName[7] == 'B' && pName[8] == 'G' && pName[9] == 'M') {
            return;
        }
    }
    pSnd->startSound(pSnd->mHandleSystemSe, id);
}


extern "C" {

void fn_804DB50C(void*, const void*);
void fn_804E4F74(BowWallPin*, const BowVec3*, f32, f32, f32, f32*, f32*, f32*, f32*);
void fn_804DD6C0(void*, int, int, f32, int);
void ogws_fn_803154C4(void*, s32);
void ogws_fn_80315520(void*, s32);
void __dt__18IRPSysHostIOSocketFv(void*, s32);
void __dl__FPv(void*);
void __destroy_arr(void*, void*, unsigned long, unsigned long);
void fn_804E3C08(BowWallObj8*);
void fn_804E3E74(BowWallPin*, int, int, int);
void fn_804D9804(BowWallLane*, BowPhysData*);
void fn_8037365C(u32, u32, int);
void fn_8037334C(f32, f32, f32);
void fn_8037332C();
void fn_804EB5E8(BowWallPin*, const BowVec3*);
int fn_804E3D48(BowWallObj8*, BowBvhHit*, int, const EGG::Vector3f*, f32, f32);
int fn_80379380(BowTriHit*, const EGG::Vector3f*, const BowWallTri*, const BowVec3*,
                const BowVec3*, const BowVec3*, const BowVec3*, f32, f32);
void fn_804D9A3C(BowWallLane*, BowPhysData*, f32*, f32*, f32);
void ogws_fn_80315A88(void*, u32, int, f32);
void ogws_fn_80315F14(void*, f32, int);
void ogws_fn_80315998(void*, u32, int, f32);
void ogws_fn_80315C58(void*, u32, int, f32);
void fn_80377790(BowBall*, s32, const BowContact*, BowCorrection*, void*, bool);
void ogws_fn_80315380(void*, s32);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void* ogws_fn_803394BC(void* p);
void ogws_fn_80329E04(BowPin*);
void fn_804EAEC0(BowPin*, const nw4r::math::VEC3&, const nw4r::math::VEC3&, int, int, f32);
void ogws_fn_8031617C(void*, int, f32, f32);
void fn_804EB664(BowPin*, const nw4r::math::VEC3&);
void ogws_fn_80316070(void*, int, f32);
void fn_804DFFA0(BowWallLane*, void*, BowPhysData*, void*, void*, void*, void*, f32);

extern "C" {
extern f32 lbl_807D4050[3];
extern f32 lbl_807D405C[3];
extern u8 lbl_807D4068[];
}

void fn_804F27F4() {
    lbl_807D4050[0] = 3.0f;
    lbl_807D4050[1] = 1.0f;
    lbl_807D4050[2] = 1.0f;
    lbl_807D405C[0] = 0.0f;
    lbl_807D405C[1] = 0.0f;
    lbl_807D405C[2] = -202.0f;
}

s32 fn_804F27CC(BowWallLane* self) {
    if (self->r1EBC0) {
        return self->r2DFC + 200;
    }
    return self->r2DF8 + 200;
}

void fn_804F27C8() {}

void fn_804F27C4() {}

void fn_804F27B0(BowWallLane* self) {
    self->r1EB39 = 0;
    self->r1EB38 = 0;
}

u8 fn_804F27A4(BowWallLane* self) {
    return self->r1EB38;
}

f32 fn_804F2794() {
    return *(f32*)(lbl_807D4068 + 0x94);
}

void* ogws_fn_8033B5D8(u8* p, s32 del) {
    if (p) {
        if (p) {
            __destroy_arr(p + 0xdb8, (void*)ogws_fn_803154C4, 0x108, 15);
            __destroy_arr(p + 0x20, (void*)ogws_fn_80315520, 0xe8, 15);
            __dt__18IRPSysHostIOSocketFv(p, 0);
        }
        if (del > 0) {
            __dl__FPv(p);
        }
    }
    return p;
}

void fn_804F1F3C(BowWallLane* self, int arg) {
    fn_804DD6C0(self, 1, 91, 0.0f, arg);
    self->i2088 = 0;
    self->i2088 = 0; // dead duplicate: needed for the copy's schedule
    self->b20A8 = 0;
    self->b20F5 = 0;
    self->f2080 = 3.05f;
    self->f2084 = 2.642f;
    self->f2090 = 10.0f;
    self->f208C = 2.0f;
    self->f2094 = 2.0f;
    self->f2098 = 0.2f;
    self->f209C = 60.0f;
    self->f20A4 = 1.0f;
    self->f20A0 = 3.44131f;
    self->f20AC = -0.4f;
    self->f20B0 = 1.4f;
    self->f20B4 = 0.001f;
    self->f20D0 = -326.0f;
    self->f20CC = 3.0f;
    self->f20D4 = 0.015f;
    self->f20D8 = 0.3f;
    self->i20DC = 0x118;
    self->i20E0 = 0x21C;
    self->f20E4 = 20.9f;
    self->f20E8 = 4.0f;
    self->f20EC = -340.0f;
    self->f20F0 = 0.3f;
    self->b20F4 = 0x96;
    self->b20F6 = 0;
    self->b20F7 = 0xFF;
    self->f20B8 = 0.01f;
    self->f20BC = 0.5f;
    self->f20C0 = 0.18f;
    self->f20C4 = 1.0f;
    self->f20C8 = -260.0f;

    lbl_804BCE80 = Bowling::gBowlingPhysicsData;
    lbl_804BCE80.i138 = 30;
    lbl_804BCE80.a158[0] = 0.0f;
    lbl_804BCE80.f010 = -330.0f;
    lbl_804BCE80.f040 = -400.0f;
    lbl_804BCE80.f0BC = 0.6f;
    lbl_804BCE80.f20C = 0.0f;
    lbl_804BCE80.f210 = 0.0f;
    lbl_804BCE80.f204 = lbl_804BCE80.f204 / 2.0f;
    lbl_804BCE80.f208 = lbl_804BCE80.f208 / 2.0f;
    lbl_804BCE80.f0B8 = 0.00005f;
    lbl_804BCE80.f070 = -0.004f;
    self->i294C = 0;
}

void ogws_fn_8033A564(BowWallLane* self) {
    BowPhysData* data = &lbl_804BCE80;
    int n = self->i294C + 1;
    int k = 0;
    if (self->i2088 >= 1) {
        n = self->i2088;
    }

    lbl_804BCE80.f014 = 2.0f * (0.5f * ((f32)(n - 1) * self->f2080) + self->f208C);
    if (lbl_804BCE80.f014 < self->f2090) {
        lbl_804BCE80.f014 = self->f2090;
    }

    f32 t = (f32)(self->i294C - 3) / 7.0f;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        t = 1.0f;
    }
    data->f0A8 = 1.9f + 0.6f * t;

    for (int i = 0; i < n; i++) {
        f32 z = -data->f018 + -(f32)i * self->f2084;
        f32 x = 0.5f * (-(f32)i * self->f2080);
        for (int j = 0; j <= i; j++) {
            BowVec3 pos(x, 0.0f, z);
            fn_804E4F74(self->mpPins[k++], &pos, data->f08C, data->f090,
                        data->f094, data->a184, data->a1C4, data->a158, data->a1A4);
            x += self->f2080;
        }
    }

    BowSetObj8(self->p8, data->f010, data->f020, data->f024, data->f028, data->f02C,
               data->f034);
    self->i14 = k;

    for (int b = 0; b < 2; b++) {
        f32 tbl[12][9] = {
            {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
            {-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f},
            {-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f},
            {-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f},
            {-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f},
            {-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f},
            {-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f},
            {1.0f, -1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f},
            {1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f},
            {-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f},
            {-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, -1.0f},
        };
        for (int t = 0; t < 12; t++) {
            BowWallTri* tri = &self->tris[b][t];
            f32 half = 0.5f;
            f32 depth = 500.0f;
            f32 w = self->f20A4;
            f32 off;
            f32 h = self->f20A0;
            if (b == 0) {
                off = -(half * lbl_804BCE80.f014 + w);
            } else {
                off = half * lbl_804BCE80.f014 + w;
            }
            tri->v[0] = BowVec3(w * tbl[t][0], h * tbl[t][1], depth * tbl[t][2]);
            tri->v[1] = BowVec3(w * tbl[t][3], h * tbl[t][4], depth * tbl[t][5]);
            tri->v[2] = BowVec3(w * tbl[t][6], h * tbl[t][7], depth * tbl[t][8]);
            if (b == 1) {
                for (int m = 0; m < 3; m++) {
                    if (tri->v[m].x > 0.0f) {
                        tri->v[m].x = 0.0f;
                    }
                }
            } else {
                for (int m = 0; m < 3; m++) {
                    if (tri->v[m].x < 0.0f) {
                        tri->v[m].x = 0.0f;
                    }
                }
            }

            tri->v[0].x += off;
            tri->v[1].x += off;
            tri->v[2].x += off;

            BowVec3 e0 = tri->v[1] - tri->v[0];
            BowVec3 e1 = tri->v[2] - tri->v[0];
            BowVec3 e2 = tri->v[2] - tri->v[1];
            BowVec3 e3 = tri->v[0] - tri->v[2];
            PSVECCrossProduct(&e0, &e1, &tri->n);
            PSVECNormalize(&tri->n, &tri->n);
            PSVECCrossProduct(&e0, &tri->n, &tri->e[0]);
            PSVECCrossProduct(&e2, &tri->n, &tri->e[1]);
            PSVECCrossProduct(&e3, &tri->n, &tri->e[2]);
            PSVECNormalize(&tri->e[0], &tri->e[0]);
            PSVECNormalize(&tri->e[1], &tri->e[1]);
            PSVECNormalize(&tri->e[2], &tri->e[2]);
            BowVec3 d = tri->v[0] - tri->v[1];
            tri->d = -BowPsDot(&d, &tri->e[1]);
        }
    }

    for (int i = 0; i < 11; i++) {
        BowWallPin* pin = self->mpPins[0];
        self->v2954[i] = BowVec3(0.0f, pin->f168 / 10.0f * i - pin->f16C,
                                 0.0f);
    }
}

void ogws_fn_8033A558(void* self) {
    fn_804DB50C(self, &lbl_804BCE80);
}

static inline const nw4r::math::VEC3& BowAsVec(const BowVec3& v) {
    return reinterpret_cast<const nw4r::math::VEC3&>(v);
}

static inline f32 BowDot(const nw4r::math::VEC3& a, const nw4r::math::VEC3& b) {
    return nw4r::math::VEC3Dot(&a, &b);
}

static inline void BowWallSeparate(BowPin* pin, const nw4r::math::VEC3& normal, f32 depth, const BowPhysData* data) {
    fn_804EB664(pin, normal * depth * data->f154);
}

static inline void BowWallBounce(BowPin* pin, const nw4r::math::VEC3& point, const nw4r::math::VEC3& normal, f32 speed, f32 restitution, const BowPhysData* data) {
    fn_804EAEC0(pin, point, normal * (speed * restitution + data->f098), 1, 1, data->f0F8);
}

static inline void BowWallFriction(BowPin* pin, const nw4r::math::VEC3& wp, const nw4r::math::VEC3& vel, f32 vn, const BowPhysData* data) {
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

static inline f32 BowWallRadius(const BowPin* pin, int index) {
    return pin->mpRadii[index];
}

// MATCH-PENDING (R17): invented helper (ledger 251). Inlining the contact-count expression through a helper
// return value keeps (m == 0) + 1 out of the IRO @var chain, so it colours as an early temp like retail (r30).
static inline int BowWallContactCount(int index) {
    int count = (index == 0) + 1;
    return count;
}

void fn_804EEE80(BowWallLane*);

void fn_804F1388(BowWallLane* self) {
    fn_804DB50C(self, lbl_807D4068);
    fn_804EEE80(self);
}

void fn_804F0C58(BowWallLane* self, BowPin* pin, BowPhysData* data, void*,
                 const nw4r::math::MTX34* mtx, const nw4r::math::MTX34* prevMtx,
                 const nw4r::math::MTX34* rotMtx) {
    nw4r::math::VEC3 normals[3] = {
        nw4r::math::VEC3(0.0f, 1.0f, 0.0f),
        nw4r::math::VEC3(1.0f, 0.0f, 0.0f),
        nw4r::math::VEC3(-1.0f, 0.0f, 0.0f),
    };
    nw4r::math::VEC3 points[3] = {
        nw4r::math::VEC3(0.0f, 0.0f, 0.0f),
        nw4r::math::VEC3(0.5f * -data->f014, 0.0f, 0.0f),
        nw4r::math::VEC3(0.5f * data->f014, 0.0f, 0.0f),
    };
    f32 restit[3] = {data->f09C, self->f2094, self->f2094};
    bool active[3] = {true, false, false};

    if (pin->pos.x < 0.5f * -data->f014 + (data->f08C - data->f090)) {
        active[1] = true;
    }
    if (pin->pos.x > 0.5f * data->f014 - (data->f08C - data->f090)) {
        active[2] = true;
    }

    nw4r::math::VEC3 d0 = *self->mpBall->GetPos() - EGG::Vector3f(pin->pos);
    if (PSVECMag(&d0) < 1.5f + (data->f110 + (data->f08C - data->f090))) {
        restit[1] = restit[2] = 1.0f;
    }

    for (int k = 0; k < 3; k++) {
        if (!active[k]) {
            continue;
        }
        nw4r::math::VEC3 nrm = normals[k];
        nw4r::math::VEC3 pt = points[k];
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

        for (int m = 0; m < 11; m += 2) {
            int count = BowWallContactCount(m);
            for (int q = 0; q < count; q++) {
                nw4r::math::VEC3 p;
                if (q != 0) {
                    const nw4r::math::VEC3& c = BowAsVec(self->v2954[m]);
                    f32 r = pin->mpRadii[m];
                    p = c + -fwd * r;
                } else {
                    const nw4r::math::VEC3& c = BowAsVec(self->v2954[m]);
                    f32 r = pin->mpRadii[m];
                    p = c + fwd * r;
                }
                nw4r::math::VEC3 wp;
                PSMTXMultVec(mtx, &p, &wp);
                nw4r::math::VEC3 dd = wp - pt;
                f32 depth = -nw4r::math::VEC3Dot(&dd, &nrm);
                if (depth > 0.0f) {
                    nw4r::math::VEC3 wp2;
                    PSMTXMultVec(prevMtx, &p, &wp2);
                    nw4r::math::VEC3 vel = wp - wp2;
                    f32 vn = -nw4r::math::VEC3Dot(&vel, &nrm);
                    fn_804EB664(pin, nrm * depth * data->f154);
                    if (vn < 0.0f) {
                        continue;
                    }
                    if (vn < depth) {
                        vn = depth;
                    }
                    fn_804EAEC0(pin, wp, nrm * (vn * restit[k] + data->f098), 1, 1, data->f0F8);
                    if (!pin->b26A && data->b246 && m != 0) {
                        f32 v = (vn - data->f22C) / (data->f230 - data->f22C);
                        if (v > 0.0f) {
                            if (v > 1.0f) {
                                v = 1.0f;
                            }
                            ogws_fn_80316070(pin->mpSnd, self->b2078, v);
                            pin->b26A = 1;
                        }
                    }
                    if (k == 0) {
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
    }
}

static inline f64 BowAbsoluteDot(const nw4r::math::VEC3& a, const nw4r::math::VEC3& b) {
    return __fabs(nw4r::math::VEC3Dot(&a, &b));
}

static inline void BowCollidePinSpheres(BowWallLane* self, BowPhysData* data, int i, int j,
                                       const f32* lim, BowPinSphere* sphI, BowPinSphere* sphJ) {
    bool nearI[16];
    bool nearJ[16];
    nw4r::math::VEC3 diff;
    for (int k = 0; k < 8; k++) {
        diff = sphI[k].pos - ((BowPin**)self->mpPins)[j]->pos;
        if (nw4r::math::VEC3SquareMag(&diff) < lim[k]) {
            nearI[k] = true;
        } else {
            nearI[k] = false;
        }
        diff = sphJ[k].pos - ((BowPin**)self->mpPins)[i]->pos;
        if (nw4r::math::VEC3SquareMag(&diff) < lim[k]) {
            nearJ[k] = true;
        } else {
            nearJ[k] = false;
        }
    }

    for (int a = 0; a < 8; a++) {
        if (!nearI[a]) {
            continue;
        }
        BowPinSphere* si = &sphI[a];
        for (int b = 0; b < 8; b++) {
            if (!nearJ[b]) {
                continue;
            }
            BowPinSphere* sj = &sphJ[b];
            f32 rsum = si->r + sj->r;
            nw4r::math::VEC3 d;
            d.x = si->pos.x - sj->pos.x;
            if (d.x < -rsum || d.x > rsum) {
                continue;
            }
            d.y = si->pos.y - sj->pos.y;
            if (d.y < -rsum || d.y > rsum) {
                continue;
            }
            d.z = si->pos.z - sj->pos.z;
            if (d.z < -rsum || d.z > rsum) {
                continue;
            }
            f32 len2 = nw4r::math::VEC3SquareMag(&d);
            if (len2 < rsum * rsum) {
                f32 dist = sqrt(len2);
                nw4r::math::VEC3 n = d * (1.0f / dist);
                nw4r::math::VEC3 rel = sj->vel - si->vel;
                f32 pen = 0.5f * (si->r + sj->r - dist);
                f32 vi = __fabs(nw4r::math::VEC3Dot(&n, &si->vel));
                f32 vj = __fabs(nw4r::math::VEC3Dot(&n, &sj->vel));
                f32 vr = 0.5f * nw4r::math::VEC3Dot(&n, &rel);
                if (vi < lbl_804BF9C0) {
                    vi = lbl_804BF9C0;
                }
                if (vj < lbl_804BF9C0) {
                    vj = lbl_804BF9C0;
                }
                f32 wi = vj / (vi + vj);
                f32 wj = vi / (vi + vj);
                f32 imp = pen * data->f068 + vr * data->f06C;
                nw4r::math::VEC3 impI = n * imp * wi;
                nw4r::math::VEC3 impJ = -n * imp * wj;
                if (vr > 0.0f) {
                    impI += n * data->f0C0 * vr;
                    impJ += -n * data->f0C0 * vr;
                }
                fn_804EAEC0(((BowPin**)self->mpPins)[i], si->pos - n * si->r, impI, 1, 1,
                            data->f0C4);
                fn_804EAEC0(((BowPin**)self->mpPins)[j], sj->pos + n * sj->r, impJ, 1, 1,
                            data->f0C4);
                if (!(((BowPin**)self->mpPins)[i]->mHitBits[j / 30] & (1 << (j % 30))) &&
                    data->b245) {
                    f32 v = (vr - data->f224) / (data->f228 - data->f224);
                    if (v > 0.0f) {
                        if (v > 1.0f) {
                            v = 1.0f;
                        }
                        ogws_fn_8031617C(((BowPin**)self->mpPins)[i]->mpSnd, self->b2078, v, v);
                        ((BowPin**)self->mpPins)[i]->mHitBits[j / 30] |= 1 << (j % 30);
                        ((BowPin**)self->mpPins)[j]->mHitBits[i / 30] |= 1 << (i % 30);
                    }
                }
            }
        }
    }
}

static inline void BowResolvePinContact(BowWallLane* self, BowPhysData* data, int i, int j,
                                       BowPinSphere* si, BowPinSphere* sj,
                                       const nw4r::math::VEC3& d, f32 len2) {
    f32 dist = sqrt(len2);
    nw4r::math::VEC3 n = d * (1.0f / dist);
    nw4r::math::VEC3 rel = sj->vel - si->vel;
    f32 pen = 0.5f * (si->r + sj->r - dist);
    f32 vj = __fabs(nw4r::math::VEC3Dot(&n, &sj->vel));
    f32 vi = __fabs(nw4r::math::VEC3Dot(&n, &si->vel));
    f32 vr = 0.5f * nw4r::math::VEC3Dot(&n, &rel);
    if (vi < lbl_804BF9C0) {
        vi = lbl_804BF9C0;
    }
    if (vj < lbl_804BF9C0) {
        vj = lbl_804BF9C0;
    }
    f32 wi = vj / (vi + vj);
    f32 wj = vi / (vi + vj);
    f32 imp = pen * data->f068 + vr * data->f06C;
    nw4r::math::VEC3 impI = n * imp * wi;
    nw4r::math::VEC3 impJ = -n * imp * wj;
    if (vr > 0.0f) {
        impI += n * data->f0C0 * vr;
        impJ += -n * data->f0C0 * vr;
    }
    fn_804EAEC0(((BowPin**)self->mpPins)[i], si->pos - n * si->r, impI, 1, 1,
                data->f0C4);
    fn_804EAEC0(((BowPin**)self->mpPins)[j], sj->pos + n * sj->r, impJ, 1, 1,
                data->f0C4);
    if (!(((BowPin**)self->mpPins)[i]->mHitBits[j / 30] & (1 << (j % 30))) &&
        data->b245) {
        f32 v = (vr - data->f224) / (data->f228 - data->f224);
        if (v > 0.0f) {
            if (v > 1.0f) {
                v = 1.0f;
            }
            ogws_fn_8031617C(((BowPin**)self->mpPins)[i]->mpSnd, self->b2078, v, v);
            ((BowPin**)self->mpPins)[i]->mHitBits[j / 30] |= 1 << (j % 30);
            ((BowPin**)self->mpPins)[j]->mHitBits[i / 30] |= 1 << (i % 30);
        }
    }
}

// MATCH-PENDING (R17): one-field holder for the per-pin sphere base pointer (ledger 252), as in
// RPBow_8033B690 fn_804E1A18. IRO_ScalarizeClassDataMembers turns sphI.p/sphJ.p into IRO @temps, so the
// two base pointers colour among the loop temporaries (sphJ r29, si r23) as in the original; named
// BowPinSphere* locals rank below every IRO temp (r20/r19).
struct BowSphRef {
    BowPinSphere* p;
};

void fn_804F0284(BowWallLane* self, BowPhysData* data, BowThrow* thr) {
    if (thr->bFB || thr->b58) {
        for (int i = 0; i < self->i14; i++) {
            if (self->mPinHitBits[i / 30] & (1 << (i % 30))) {
                ogws_fn_80329E04(((BowPin**)self->mpPins)[i]);
            }
        }
    }

    f32 lim[16];
    for (int k = 0; k < 8; k++) {
        f32 r = 2.4f + ((BowPin**)self->mpPins)[0]->sph[k].r;
        lim[k] = r * r;
    }

    for (int i = 0; i < self->i14 - 1; i++) {
        for (int j = i + 1; j < self->i14; j++) {
            BowPin* pj = ((BowPin**)self->mpPins)[j];
            BowPin* pi = ((BowPin**)self->mpPins)[i];
            f32 dx = pi->pos.x - pj->pos.x;
            if (dx < -4.7f || dx > 4.7f) {
                continue;
            }
            f32 dz = pi->pos.z - pj->pos.z;
            if (dz < -4.7f || dz > 4.7f) {
                continue;
            }
            if (dx * dx + dz * dz > 22.089998f) {
                continue;
            }

            bool nearI[16];
            bool nearJ[16];
            nw4r::math::VEC3 diff;
            BowSphRef sphJ;
            sphJ.p = pj->sph;
            BowSphRef sphI;
            sphI.p = pi->sph;
            for (int k = 0; k < 8; k++) {
                const f32& threshold = lim[k];
                diff = sphI.p[k].pos - ((BowPin**)self->mpPins)[j]->pos;
                if (nw4r::math::VEC3SquareMag(&diff) < threshold) {
                    nearI[k] = true;
                } else {
                    nearI[k] = false;
                }
                diff = sphJ.p[k].pos - ((BowPin**)self->mpPins)[i]->pos;
                if (nw4r::math::VEC3SquareMag(&diff) < threshold) {
                    nearJ[k] = true;
                } else {
                    nearJ[k] = false;
                }
            }

            for (int a = 0; a < 8; a++) {
                if (!nearI[a]) {
                    continue;
                }
                BowPinSphere* si = &sphI.p[a];
                for (int b = 0; b < 8; b++) {
                    if (!nearJ[b]) {
                        continue;
                    }
                    BowPinSphere* sj = &sphJ.p[b];
                    f32 rsum = si->r + sj->r;
                    nw4r::math::VEC3 d;
                    d.x = si->pos.x - sj->pos.x;
                    if (d.x < -rsum || d.x > rsum) {
                        continue;
                    }
                    d.y = si->pos.y - sj->pos.y;
                    if (d.y < -rsum || d.y > rsum) {
                        continue;
                    }
                    d.z = si->pos.z - sj->pos.z;
                    if (d.z < -rsum || d.z > rsum) {
                        continue;
                    }
                    f32 len2 = nw4r::math::VEC3SquareMag(&d);
                    if (len2 < rsum * rsum) {
                        f32 dist = sqrt(len2);
                        nw4r::math::VEC3 n = d * (1.0f / dist);
                        nw4r::math::VEC3 rel = sj->vel - si->vel;
                        f32 pen = 0.5f * (si->r + sj->r - dist);
                        f32 vr = 0.5f * nw4r::math::VEC3Dot(&n, &rel);
                        f32 vi = fabsf(nw4r::math::VEC3Dot(&n, &si->vel));
                        f32 vj = fabsf(nw4r::math::VEC3Dot(&n, &sj->vel));
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
                        fn_804EAEC0(((BowPin**)self->mpPins)[i], si->pos - n * si->r, impI, 1, 1,
                                    data->f0C4);
                        fn_804EAEC0(((BowPin**)self->mpPins)[j], sj->pos + n * sj->r, impJ, 1, 1,
                                    data->f0C4);
                        if (!(((BowPin**)self->mpPins)[i]->mHitBits[j / 30] & (1 << (j % 30))) &&
                            data->b245) {
                            f32 v = (vr - data->f224) / (data->f228 - data->f224);
                            if (v > 0.0f) {
                                if (v > 1.0f) {
                                    v = 1.0f;
                                }
                                ogws_fn_8031617C(((BowPin**)self->mpPins)[i]->mpSnd, self->b2078, v, v);
                                ((BowPin**)self->mpPins)[i]->mHitBits[j / 30] |= 1 << (j % 30);
                                ((BowPin**)self->mpPins)[j]->mHitBits[i / 30] |= 1 << (i % 30);
                            }
                        }
                    }
                }
            }
        }
    }
}

void fn_804F0160(BowWallLane* self, void* a1, BowPhysData* data, void* a3, void* a4, void* a5,
                 void* a6, f32 f) {
    f32 lim = 0.5f * data->f014 - (data->f08C - data->f090) - 1.8f - data->f110;
    if (self->mpBall->GetPos()->x < -lim || self->mpBall->GetPos()->x > lim) {
        fn_804DFFA0(self, a1, data, a3, a4, a5, a6, 0.0f);
    } else {
        fn_804DFFA0(self, a1, data, a3, a4, a5, a6, f);
    }
}

void* ogws_fn_803394BC(void* p) {
    return p;
}

static inline void BowCalcFriction(BowWallLane* self, BowPhysData* data, f32* a, f32* b, f32 z) {
    fn_804D9A3C(self, data, a, b, z);
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

// MATCH-PENDING (R17): name inferred. Builds the throw-matrix translation as an inline return value so its
// VEC3 ctor locals are @vars of a separate expansion (FPR colouring of the wall-hit effect position in fn_804EF354);
// the real source probably used a matrix/translation getter here.
static inline nw4r::math::VEC3 BowThrowTrans(const BowWallLane* self) {
    return nw4r::math::VEC3(self->f1F08, self->f1F18, self->f1F28);
}

void fn_804EF354(BowWallLane* self, BowPhysData* data, BowThrow* thr) {
    BowBvhHit hits[64];
    BowContact contacts[64];
    BowTriHit out;
    BowCorrection corr;
    f32 a;
    f32 b;
    int n = fn_804E3D48(self->p8, hits, 64, self->mpBall->GetPos(), self->mpBall->mRadius, self->f209C);
    int wallHit = 0;

    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 12; t++) {
            BowWallTri* tri = &self->tris[s][t];
            if (fn_80379380(&out, self->mpBall->GetPos(), tri, &tri->n, &tri->e[0], &tri->e[1], &tri->e[2],
                            self->mpBall->mRadius, tri->d)) {
                if (n < 64) {
                    BowSetHit(&hits[n], out, 2);
                    if (out.normal.y > 0.8f) {
                        wallHit = 1;
                    }
                    n++;
                }
                f32 speed = -nw4r::math::VEC3Dot(&out.normal, self->mpBall->GetVel());
                bool side = true;
                if (self->mpBall->GetPos()->x > 0.0f) {
                    if (out.normal.x > 0.5f) {
                        side = false;
                    }
                } else if (out.normal.x < -0.5f) {
                    side = false;
                }
                if (speed > 0.0f && out.normal.y < 0.5f &&
                    self->mpBall->GetPos()->z > self->f20C8 && side) {
                    f32 r = (speed - self->f20B8) / (self->f20C0 - self->f20B8);
                    if (r > 0.0f) {
                        if (r > 1.0f) {
                            r = 1.0f;
                        }
                        f32 scale = r * (self->f20C4 - self->f20BC) + self->f20BC;
                        f32 rad = Bowling::gBowlingPhysicsData.f110;
                        nw4r::math::VEC3 pos =
                            BowThrowTrans(self) + -out.normal * (rad - out.depth);
                        RPSysEffect eff("Bow_wall_hit02", 0, 0);
                        eff.create();
                        eff.setPos(pos);
                        eff.setScale(nw4r::math::VEC3(scale, scale, scale));
                        eff.update();
                    }
                }
                f32 v = (speed - self->f20D4) / (self->f20D8 - self->f20D4);
                if (v > 0.0f) {
                    if (v > 1.0f) {
                        v = 1.0f;
                    }
                    ogws_fn_80315A88(self->mpSnd, 0x2C, 0, v);
                }
            }
        }
    }

    __construct_array(contacts, (void*)ogws_fn_803394BC, (void*)ogws_fn_80315380, sizeof(BowContact), 64);

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
        if (self->mpBall->GetPos()->z < data->f010) {
            contacts[i].friction = 0.05f;
            contacts[i].slidingFriction = 0.05f;
            contacts[i].restitution = self->f2098;
            contacts[i].angularLimit = 2.0f;
            self->b2951 = 1;
        }
        if (!thr->bA9 && hits[i].type == 3) {
            f32 r = (-self->mpBall->GetVel()->z - data->f234) / (data->f238 - data->f234);
            if (r > 0.0f) {
                ogws_fn_80315F14(self->mpSnd, r > 1.0f ? 1.0f : r, self->b2078);
                thr->bA9 = 1;
            }
        }
    }

    if (thr->bB4 || thr->bFB || self->mpBall->GetPos()->z < data->f010) {
        nw4r::math::VEC3 vel = *self->mpBall->GetVel();
        vel.x *= 0.98f;
        vel.z *= 0.98f;
        self->mpBall->SetVel(vel);
    }

    if (n != 0) {
        if (self->mpBall->GetPos()->z < data->f010) {
            self->mpBall->mAngVel = self->mpBall->mAngVel * 0.95f;
        }
        fn_80377790(self->mpBall, n, contacts, &corr, 0, true);
        f32 vy = self->mpBall->GetVel()->y;
        self->mpBall->SetPos(*self->mpBall->GetPos() + corr.displacement);
        self->mpBall->SetVel(*self->mpBall->GetVel() + corr.velocity);
        self->mpBall->mAngVel = self->mpBall->mAngVel + corr.angularVelocity;
        if (self->mpBall->GetPos()->z > data->f010 && !thr->bB4 && !self->b2951 && !thr->bFB &&
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
                ogws_fn_80315998(self->mpSnd, 1, thr->iCC / 4, r);
                ogws_fn_80315A88(self->mpSnd, 2, self->b2078, r);
            } else {
                ogws_fn_80315C58(self->mpSnd, 0x11, self->b2078,
                            PSVECMag(self->mpBall->GetVel()) / data->f23C);
            }
        }
    }

    if (thr->state == 2) {
        f32 mag = PSVECMag(self->mpBall->GetVel());
        if (mag > PSVECMag(&thr->v4C)) {
            nw4r::math::VEC3 v = *self->mpBall->GetVel();
            PSVECNormalize(&v, &v);
            self->mpBall->SetVel(v * PSVECMag(&thr->v4C));
        }
        thr->v4C = *self->mpBall->GetVel();
    }

    f32 lim = 0.5f * lbl_804BCE80.f014 + 2.0f;
    if ((self->mpBall->GetPos()->x < -lim || self->mpBall->GetPos()->x > lim) && thr->i104 == 0) {
        thr->b58 = 1;
        self->b2950 = 1;
    }

    if (wallHit) {
        f32 px = self->mpBall->GetPos()->x;
        f32 hw = 0.5f * data->f014;
        nw4r::math::VEC3 push(0.0f, 0.0f, 0.0f);
        if (px > 0.0f) {
            if (px < hw + self->f20AC) {
                push.x = -self->f20B4;
            }
            if (px > hw + self->f20B0) {
                push.x = self->f20B4;
            }
        } else {
            if (px > -hw - self->f20AC) {
                push.x = self->f20B4;
            }
            if (px < -hw - self->f20B0) {
                push.x = -self->f20B4;
            }
        }
        self->mpBall->SetVel(*self->mpBall->GetVel() + push);
    }

    if (thr->i104 == 0) {
        if (self->mpBall->GetPos()->z < self->f20D0 && self->mpBall->GetPos()->y > self->f20CC &&
            self->i294C == 12) {
            thr->i104 = 1;
            BowStartSystemSe(spInstance__13RPSndAudioMgr, 0x2D);
        }
    } else {
        thr->i104++;
        if (thr->i104 == (self->b29D8 ? self->i20E0 : self->i20DC)) {
            for (int i = 0; i < self->i14; i++) {
                self->mpPins[i]->i2B0 = 40;
            }
        }
    }

    __destroy_arr(contacts, (void*)ogws_fn_80315380, sizeof(BowContact), 64);
}

void fn_804EF318(BowWallLane*, BowWallPin* pin, BowPhysData* data) {
    BowVec3 g(0.0f, data->f070, 0.0f);
    fn_804EB5E8(pin, &g);
}

void fn_804EF314() {}

void fn_804EF310() {}

void fn_804EEFE8(BowWallLane* self) {
    self->r1EB28 = 1;
    self->r1EB2C = 0;
}

void fn_804EEFD8(BowWallLane* self) {
    self->r1EB28 = 0;
}

static inline void BowVtx(f32 x, f32 y, f32 z) {
    fn_8037334C(x, y, z);
}

void fn_804EE70C(BowWallLane* self) {
    BowPhysData* data = &lbl_804BCE80;
    fn_804E3C08(self->p8);
    for (int i = 0; i < self->i14; i++) {
        BowWallPin* pin = self->mpPins[i];
        if (pin->b251) {
            fn_804E3E74(pin, data->b000 != 0, data->b001 != 0, data->b002 != 0);
        }
    }
    Bowling::ogws_fn_803345F0((Bowling::LaneContext*)self);
    fn_804D9804(self, data);

    if (self->b20A8) {
        f32 w = self->f209C;
        fn_8037365C(0x8080FF80, 4, 1);
        BowVtx(-w, 0.0f, 0.0f);
        BowVtx(-w, 0.0f, -300.0f);
        BowVtx(-w, 10.0f, 0.0f);
        BowVtx(-w, 10.0f, -300.0f);
        fn_8037332C();
        fn_8037365C(0x8080FF80, 4, 1);
        BowVtx(w, 0.0f, 0.0f);
        BowVtx(w, 10.0f, 0.0f);
        BowVtx(w, 0.0f, -300.0f);
        BowVtx(w, 10.0f, -300.0f);
        fn_8037332C();

        f32 hw = 50.0f;
        fn_8037365C(0x8080FF80, 4, 1);
        BowVtx(-hw, 0.0f, data->f040);
        BowVtx(-hw, 5.0f, data->f040);
        BowVtx(hw, 0.0f, data->f040);
        BowVtx(hw, 5.0f, data->f040);
        fn_8037332C();
        fn_8037365C(0x80FF8080, 4, 1);
        BowVtx(-hw, 0.0f, data->f010);
        BowVtx(-hw, 5.0f, data->f010);
        BowVtx(hw, 0.0f, data->f010);
        BowVtx(hw, 5.0f, data->f010);
        fn_8037332C();
        fn_8037365C(0x80FFFF80, 4, 1);
        BowVtx(-hw, 0.0f, self->f20C8);
        BowVtx(-hw, 5.0f, self->f20C8);
        BowVtx(hw, 0.0f, self->f20C8);
        BowVtx(hw, 5.0f, self->f20C8);
        fn_8037332C();

        BowVec3 light(-1.0f, 1.0f, -1.0f);
        PSVECNormalize(&light, &light);
        for (int b = 0; b < 2; b++) {
            for (int t = 0; t < 12; t++) {
                BowWallTri* tri = &self->tris[b][t];
                f32 d = BowPsDot(&tri->n, &light);
                if (d < 0.0f) {
                    d = 0.0f;
                }
                f32 shade = 0.3f + 0.7f * d;
                int c = 255.0f * shade;
                fn_8037365C(0x80000000 | c | (c << 8) | (c << 16), 3, 1);
                BowVtx(tri->v[0].x, tri->v[0].y, tri->v[0].z);
                BowVtx(tri->v[1].x, tri->v[1].y, tri->v[1].z);
                BowVtx(tri->v[2].x, tri->v[2].y, tri->v[2].z);
                fn_8037332C();
            }
        }

        f32 x = 0.5f * data->f014 + self->f20AC;
        fn_8037365C(0x80FFFF80, 4, 1);
        BowVtx(x, 0.0f, 0.0f);
        BowVtx(x, 0.0f, -300.0f);
        BowVtx(x, 10.0f, 0.0f);
        BowVtx(x, 10.0f, -300.0f);
        fn_8037332C();
        x = 0.5f * data->f014 + self->f20B0;
        fn_8037365C(0x80FFFF80, 4, 1);
        BowVtx(x, 0.0f, 0.0f);
        BowVtx(x, 0.0f, -300.0f);
        BowVtx(x, 10.0f, 0.0f);
        BowVtx(x, 10.0f, -300.0f);
        fn_8037332C();
    }

    EGG::DrawGX::BeginDrawSphere();
    for (int i = 0; i < 2; i++) {
        nw4r::math::MTX34 m;
        nw4r::math::MTX34 out;
        PSMTXIdentity(&m);
        f32 s = self->f20F0;
        BowVec3 scale(s, s, s);
        PSMTXScaleApply(&m, &m, scale.x, scale.y, scale.z);
        BowVec3 trans(i == 0 ? self->f20E4 : -self->f20E4, self->f20E8, self->f20EC);
        PSMTXTransApply(&m, &m, trans.x, trans.y, trans.z);
        _GXColor col = {self->b20F4, self->b20F5, self->b20F6, self->b20F7};
        PSMTXConcat(&EGG::DrawGX::s_cameraMtx, &m, &out);
        EGG::DrawGX::DrawDL(EGG::DrawGX::DL_SPHERE_8X16, out, col);
    }
}

// MATCH-PENDING (R17): the lumped .data split 0x803CA758-0x803CA858 (vtables of unmodelled classes owned by
// neighbouring TUs) is hand-defined here as arrays (ledger 237). 0x803CA858-0x803CA940 moved to its owners.
void EditJointLocalMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34PQ34nw4r4math4VEC3();
void EditJointWorldMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34();
void GenMessage__18IRPSysHostIOSocketFv();
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void ReferViewMtx__19IRPGrpModelCallbackFP10RPGrpModel();
void ogws_fn_80316418();
void fn_804C7D10();
void fn_804C7D14();
void fn_804D9B20();
void fn_804DC8E0();
void ogws_fn_80326954();
void fn_804DCA5C();
void fn_804DDBA4();
void ogws_fn_8033758C();
void ogws_fn_8033763C();
void ogws_fn_80337E90();
void ogws_fn_80337EA0();
void ogws_fn_80337EA4();
void fn_804DEC54();
void fn_804DEDE4();
void fn_804E1A18();
void fn_804E2870();
void fn_804E2A24();
void fn_804E3044();
void fn_804D0C38();
void fn_804D0CF4();
void fn_804D0CF8();
void fn_804D0D68();
void fn_804D0DE4();
void fn_804D0E24();
void fn_804D0E2C();
void ogws_fn_80341CD4();
void ogws_fn_80341CD8();
void ogws_fn_80342D0C();
void ogws_fn_80342D50();
void ogws_fn_80342D58();
void ogws_fn_80342E0C();

void* lbl_803CA758[6] = {
    0,
    0,
    (void*)ogws_fn_80337EA4,
    (void*)ogws_fn_8033763C,
    (void*)ogws_fn_8033758C,
    (void*)ogws_fn_80337EA0,
};

void* lbl_803CA770[20] = {
    0,
    0,
    (void*)ogws_fn_8033B5D8,
    (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
    (void*)ogws_fn_80337E90,
    (void*)fn_804D9B20,
    (void*)ogws_fn_8033A564,
    (void*)fn_804F0C58,
    (void*)fn_804EF310,
    (void*)fn_804F0160,
    (void*)fn_804F27C4,
    (void*)fn_804EF314,
    (void*)fn_804EF318,
    (void*)fn_804F0284,
    (void*)fn_804EF354,
    (void*)fn_804DEDE4,
    (void*)fn_804DCA5C,
    (void*)ogws_fn_80326954,
    (void*)fn_804F27CC,
};

void* lbl_803CA7C0[18] = {
    0,
    0,
    (void*)fn_804D0DE4,
    (void*)fn_804D0D68,
    (void*)fn_804D0CF8,
    (void*)fn_804D0CF4,
    (void*)ogws_fn_80316418,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
    0,
    (void*)fn_804D0E2C,
    (void*)EditJointLocalMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34PQ34nw4r4math4VEC3,
    (void*)EditJointWorldMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34,
    (void*)fn_804D0E24,
    (void*)ReferViewMtx__19IRPGrpModelCallbackFP10RPGrpModel,
    (void*)fn_804D0C38,
    0,
};

void* lbl_803CA808[20] = {
    0,
    0,
    (void*)ogws_fn_80342E0C,
    (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
    (void*)fn_804DDBA4,
    (void*)fn_804D9B20,
    (void*)ogws_fn_80342D0C,
    (void*)fn_804E2A24,
    (void*)fn_804E3044,
    (void*)fn_804DFFA0,
    (void*)fn_804DEC54,
    (void*)ogws_fn_80341CD4,
    (void*)fn_804E2870,
    (void*)fn_804E1A18,
    (void*)ogws_fn_80341CD8,
    (void*)fn_804DEDE4,
    (void*)ogws_fn_80342D58,
    (void*)ogws_fn_80342D50,
    (void*)fn_804DC8E0,
};

}
