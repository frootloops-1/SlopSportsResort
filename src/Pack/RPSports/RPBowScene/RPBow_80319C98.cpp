// Resort (RZTE01_01) port of Wii Sports RPBow_80319C98.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_80319C98: bowling scene camera controller (an RPGrpCamera subclass
// driven by camera paths, scripted throw/aim follow cameras and fixed
// shots). Class and field names are inferred from use (invented); the
// functions keep their fn_ names and take the object as an explicit pointer.
//
// Functions are written in ASCENDING address order with `#pragma
// defer_codegen off`; .sdata2 is byte-exact (the table sizes are
// `const int x[1]` defined right before their first user, and an unreferenced
// placeholder supplies the stripped function's pool head).
//
// Matching notes:
// - SetFovy uses an nw4r-style SinCosDeg inline (0.5 before 256/360 in the
//   pool) and keeps the assert on one line (__LINE__ 391);
// - ogws_fn_8031B3F4: the path-output copy (BowCamApplyOutput), the fixed shot
//   (BowCamSetFixed) and the shake add (BowCamAddShake) are inlines at the
//   depths that reproduce the original stack-slot order; the mode select is
//   if/else with a default-then-override inner if;
// - fn_804CB0C0: dir is EGG::Vector3f (user dtor keeps it contiguous), Q is
//   a plain VEC3 assigned from v1BC (`VEC3 Q; Q = self->v1BC;`: the copy
//   values colour as ordinary temps), the
//   switch has an empty `case 3`, the 1.0 lerp weight reuses `height` (both
//   live in f31), 182.6/30 come from late locals (constant load order), the
//   two table lerps compute ft2/ft1, i2/fr2, i1/fr1 in that order (int->float
//   stack slots), and the tEF4 base is re-read from a cached BowRes* after
//   the flag branch.
// All functions match; fn_804CB0C0 relies on R17 markers (ledger 264-266,
// 288-290).

#pragma defer_codegen off

extern "C" {
void system_halt(const char*, int, const char*, ...);
void* memset(void*, int, unsigned long);
double sin(double);
double cos(double);
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

struct _MTX34 {
    f32 m[3][4];
};

struct MTX34 : _MTX34 {
    MTX34() {}
};

void SinCosFIdx(f32* pSin, f32* pCos, f32 fidx);
inline void SinCosDeg(f32* pSin, f32* pCos, f32 deg) {
    return SinCosFIdx(pSin, pCos, (deg) * (256.0f / 360.0f));
}
MTX34* MTX34RotXYZFIdx(MTX34* pMtx, f32 fx, f32 fy, f32 fz);
VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pMtx, const VEC3* pIn);
}  // namespace math
}  // namespace nw4r

using nw4r::math::VEC3;

namespace EGG {
struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(f32 fx, f32 fy, f32 fz) : VEC3(fx, fy, fz) {}
    Vector3f(const nw4r::math::VEC3& rVec) : VEC3(rVec.x, rVec.y, rVec.z) {}
    ~Vector3f() {}
};
}  // namespace EGG

extern "C" void PSVECNormalize(const VEC3* pSrc, VEC3* pDst);

const int lbl_804C5B80[1] = {30};

namespace EGG {
class Frustum {
public:
    f32 GetFovy() const {
        return mFovY;
    }
    void SetFovy(f32 fovy) {
        if (mFovY == fovy)
            return;

#line 391 "eggFrustum.h"
        if (!(0.f < fovy && fovy < 180.f)) system_halt(__FILE__, __LINE__, "0.f < fovy && fovy < 180.f");
#line 169 "RPBow_80319C98.cpp"
        mFovY = fovy;

        f32 sin, cos;
        nw4r::math::SinCosDeg(&sin, &cos, mFovY / 2.0f);
        mTanFovY = sin / cos;
    }
    void SetNearZ(f32 nearZ) {
        mNearZ = nearZ;
    }

    // Public in this view: fn_804CB0C0 reads mFovY directly (through
    // GetFovy() the saved fovy lands in the wrong callee-saved FPR).
    u8 unk00[0x10];
    f32 mFovY;     // at 0x10
    f32 mTanFovY;  // at 0x14
    f32 mNearZ;    // at 0x18
};
}  // namespace EGG

// Minimal view of RPGrpCamera (vtable at 0x174).
class RPGrpCamera {
public:
    void CalcMatrix();

    u8 pad_0x0[0xC0];
    VEC3 mPosition;  // at 0xC0
    VEC3 mTarget;    // at 0xCC
    u8 pad_0xD8[0xF4 - 0xD8];
    VEC3 mUp;  // at 0xF4
    u8 pad_0x100[0x10C - 0x100];
    s32 mCameraType;  // at 0x10C
    u8 pad_0x110[0x178 - 0x110];
};

// Inferred (name invented): camera output block written by the path player
struct BowCamOutput {
    VEC3 pos;      // offset 0x0
    VEC3 target;   // offset 0xC
    VEC3 up;       // offset 0x18
    f32 fovy;      // offset 0x24
    s32 camType;   // offset 0x28
};

// Inferred (name invented): camera path player (RPBow_80348158)
struct BowCamPath {
    u8 pad_0x0[0x4];
    BowCamOutput out;  // offset 0x4
    s32 index;         // offset 0x30
};

extern "C" {
void fn_804CD120(BowCamPath*, s32);
void fn_804CCE3C(BowCamPath*);
int fn_804CCFE4(BowCamPath*);
void fn_804CD180(BowCamPath*);
}

// Inferred (name invented): BowExcelGlobal.bin camera tables
struct BowCamTblVec {
    f32 x, y, z;
};
struct BowCamTbl4 {
    f32 a, b, c, d;
};
struct BowExcelGlobal {
    u8 pad_0x0[0x2C4];
    f32 t2C4[300];         // offset 0x2C4
    f32 t774[300];         // offset 0x774
    BowCamTblVec tC24[60];  // offset 0xC24
    BowCamTbl4 tEF4[30];    // offset 0xEF4
    BowCamTbl4 t10D4[60];   // offset 0x10D4
    f32 t1494[200];        // offset 0x1494
    u8 pad_0x17B4[0x1C6C - 0x17B4];
    f32 t1C6C[300];         // offset 0x1C6C
    BowCamTblVec t211C[30];  // offset 0x211C
    f32 t2284[300];         // offset 0x2284
    f32 t2734[300];         // offset 0x2734
};
struct BowRes {
    u8 pad_0x0[0x4];
    BowExcelGlobal* p4;
};
extern BowRes* lbl_804BF9A8;

// Inferred (name invented): camera tuning parameters (+0x258)
struct BowCamParams {
    f32 p00, p04, p08, p0C, p10, p14, p18, p1C;
    f32 p20, p24, p28, p2C, p30, p34, p38, p3C;
    f32 p40, p44, p48, p4C, p50;
    f32 fov[6];  // offset 0x54
    f32 p6C, p70, p74, p78, p7C, p80, p84, p88, p8C;
    f32 p90, p94, p98, p9C, pA0, pA4, pA8, pAC;
    f32 pB0, pB4, pB8;
    s32 iBC;
    f32 pC0, pC4, pC8, pCC;
};

// Inferred (name invented): bowling camera
struct BowCamera : RPGrpCamera {
    EGG::Frustum* mpFrustum;  // offset 0x178
    VEC3 v17C;                // offset 0x17C
    VEC3 v188;                // offset 0x188
    f32 f194;                 // offset 0x194
    f32 f198;                 // offset 0x198
    f32 f19C;                 // offset 0x19C
    s32 i1A0;                 // offset 0x1A0
    f32 f1A4;                 // offset 0x1A4
    u8 b1A8;                  // offset 0x1A8
    s32 i1AC;                 // offset 0x1AC
    s32 i1B0;                 // offset 0x1B0
    f32 f1B4;                 // offset 0x1B4
    s32 i1B8;                 // offset 0x1B8
    VEC3 v1BC;                // offset 0x1BC
    VEC3 v1C8;                // offset 0x1C8
    VEC3 v1D4;                // offset 0x1D4
    VEC3 v1E0;                // offset 0x1E0
    VEC3 v1EC;                // offset 0x1EC
    VEC3 v1F8;                // offset 0x1F8
    f32 f204;                 // offset 0x204
    f32 f208;                 // offset 0x208
    s32 i20C;                 // offset 0x20C
    s32 i210;                 // offset 0x210
    f32 f214;                 // offset 0x214
    VEC3 v218;                // offset 0x218
    VEC3 v224;                // offset 0x224
    f32 f230;                 // offset 0x230
    s32 i234;                 // offset 0x234
    u8 pad_0x238[0x23C - 0x238];
    f32 f23C;  // offset 0x23C
    u8 pad_0x240[0x250 - 0x240];
    f32 f250;            // offset 0x250
    bool b254;           // offset 0x254
    BowCamParams prm;    // offset 0x258
    s32 mState;          // offset 0x328
    s32 mFrame;          // offset 0x32C
    BowCamPath* mpPath;  // offset 0x330
    u8 b334;             // offset 0x334
    s32 i338;            // offset 0x338
    s32 i33C;            // offset 0x33C
    u8 b340;             // offset 0x340
    s32 i344;            // offset 0x344
    u8 b348;             // offset 0x348
};

// MATCH-PENDING (R17): invented row helper (name inferred). Advancing the table base by
// k rows BEFORE adding the +0x211C field offset makes the [i] row address (p4 + i*12) a
// value the allocator colours after the table base (target tbl r3, row r4); the real source
// probably just wrote lbl_804BF9A8->p4->t211C[i], which MWCC associates as (p4+0x211C)+i*12.
static inline BowExcelGlobal* BowCamShakeRow(int k) {
    return (BowExcelGlobal*)((BowCamTblVec*)lbl_804BF9A8->p4 + k);
}

static inline VEC3 BowCamShake(BowCamera* self) {
    VEC3 v(0.0f, 0.0f, 0.0f);
    if (self->i234 != 0) {
        f32 t = self->prm.pB4 * (f32)(self->i234 - self->prm.iBC);
        int i = (int)t;
        f32 fr = t - (f32)i;
        if (i >= 0 && i < lbl_804C5B80[0] - 1) {
            int j = i + 1;
            v.x = fr * (BowCamShakeRow(j)->t211C[0].x - BowCamShakeRow(i)->t211C[0].x) + BowCamShakeRow(i)->t211C[0].x;
            v.y = fr * (BowCamShakeRow(j)->t211C[0].y - BowCamShakeRow(i)->t211C[0].y) + BowCamShakeRow(i)->t211C[0].y;
            v.z = fr * (BowCamShakeRow(j)->t211C[0].z - BowCamShakeRow(i)->t211C[0].z) + BowCamShakeRow(i)->t211C[0].z;
            v *= self->prm.pB8;
        }
        self->i234++;
    }
    return v;
}

static inline void BowCamApplyOutput(BowCamera* self, BowCamPath* path) {
    self->mCameraType = path->out.camType;
    self->mPosition = path->out.pos + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mTarget = path->out.target + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mUp = path->out.up;
    self->mpFrustum->SetFovy(path->out.fovy);
}

static inline void BowCamApplyPath(BowCamera* self) {
    fn_804CCE3C(self->mpPath);
    BowCamPath* path = self->mpPath;
    BowCamApplyOutput(self, path);
    self->b334 = fn_804CCFE4(self->mpPath);
    self->b254 = !(path->out.target.z > path->out.pos.z);
}

static inline void BowCamAddShake(BowCamera* self) {
    self->mTarget = self->mTarget + BowCamShake(self) * self->prm.pC0;
}

static inline void BowCamSetFixed(BowCamera* self) {
    self->mPosition = VEC3(6.42504f, 4.29835f, -2.00618f);
    self->mTarget = VEC3(5.24153f, 4.25234f, 1.9646f);
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    self->mpFrustum->SetFovy(39.0f);
}


// Resort camera view (invented names): only the offsets the Resort-only
// functions below touch; the older ogws-derived BowCamera view above does not
// match the Resort layout.
struct BowCam2 : RPGrpCamera {
    EGG::Frustum* mpFrustum;  // 0x178
    u8 pad_0x17C[0x190 - 0x17C];
    f32 f190;                 // 0x190
    u8 pad_0x194[0x1A4 - 0x194];
    f32 f1A4;                 // 0x1A4
    u8 pad_0x1A8[0x1B0 - 0x1A8];
    f32 f1B0;                 // 0x1B0
    u8 pad_0x1B4[0x1B8 - 0x1B4];
    f32 f1B8;                 // 0x1B8
    u8 pad_0x1BC[0x214 - 0x1BC];
    f32 f214;                 // 0x214
    f32 f218;                 // 0x218
    u8 pad_0x21C[0x244 - 0x21C];
    s32 i244;                 // 0x244
    u8 pad_0x248[0x264 - 0x248];
    bool b264;                // 0x264
    u8 pad_0x265[0x270 - 0x265];
    f32 f270;                 // 0x270
    u8 pad_0x274[0x278 - 0x274];
    f32 f278;                 // 0x278
    f32 f27C;                 // 0x27C
    u8 pad_0x280[0x288 - 0x280];
    f32 f288;                 // 0x288
    s32 i28C;                 // 0x28C
    VEC3 v290;                // 0x290
    f32 f29C;                 // 0x29C
    f32 f2A0;                 // 0x2A0
    s32 i2A4;                 // 0x2A4
    u8 pad_0x2A8[0x384 - 0x2A8];
    f32 f384;                 // 0x384
    f32 f388;                 // 0x388
    s32 i38C;                 // 0x38C
    f32 f390;                 // 0x390
    u8 pad_0x394[0x3A8 - 0x394];
    s32 i3A8;                 // 0x3A8
    s32 i3AC;                 // 0x3AC
    BowCamPath* mpPath;       // 0x3B0
    u8 b3B4;                  // 0x3B4
    u8 pad_0x3B5[0x3C4 - 0x3B5];
    s32 i3C4;                 // 0x3C4
};
struct BowModeGlobal {
    u8 pad_0x0[0x18];
    s32 mode;
};
extern BowModeGlobal* lbl_806F5950;
extern "C" {
void fn_801BE894(EGG::Frustum*, f32);
void fn_804CC5B4(BowCam2*);
VEC3 fn_804CAF90(BowCam2*);
}

extern "C" {

void fn_804CA62C(void*) {}

void fn_804CA630(void*) {}

void fn_804CA634(BowCam2* self) {
    if (self->i3AC == 0) {
        self->f2A0 = self->f27C;
    }
    f32 side = (self->f2A0 > 0.0f) ? 1.0f : -1.0f;
    VEC3 pos(30.9f * side, 44.5f, -238.9f);
    self->mPosition = pos;
    VEC3 tgt(12.33f * side, 14.8f, -218.4f);
    self->mTarget = tgt;
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    fn_801BE894(self->mpFrustum, 30.0f);
}

namespace EGG {
struct Screen {
    static int sTVMode;
};
}  // namespace EGG

void fn_804CA6FC(BowCam2* self) {
    f32 a, b, c, d, e, f, g;
    if (self->i2A4 == 0) {
        a = 35.0f;
        b = 13.0f;
        c = 2.0f;
        d = 0.0f;
        e = 30.0f;
        f = 22.0f;
        g = 0.5f;
    } else {
        b = 30.0f;
        a = -46.0f;
        e = b;
        c = 4.0f;
        d = -5.0f;
        f = 28.0f;
        g = 1.0f;
    }
    if (EGG::Screen::sTVMode == 0) {
        e += 6.0f;
        f += 4.0f;
    }
    if (self->i3AC == 0) {
        self->i28C = 0;
        self->f29C = 0.6f;
        self->f2A0 = self->f270;
    }
    VEC3 pos(g * (self->f2A0 - self->f1B0) + self->f1B0, b, self->f1B8 + a);
    VEC3 tgt(self->f270, c, self->f278 + d);
    f32 t;
    if (self->i28C == 0) {
        t = (f32)self->i3AC / 90.0f;
        if (t > 1.0f) {
            t = 1.0f;
            if (self->f288 >= 0.98f) {
                self->i28C = self->i3AC;
            }
        }
    } else {
        t = 1.0f - (f32)(self->i3AC - self->i28C) / 90.0f;
        if (t < 0.0f) {
            t = 0.0f;
        }
    }
    if (self->i3AC == 0) {
        self->v290 = tgt;
    } else {
        self->v290 += (tgt - self->v290) * self->f29C;
        if (self->f288 >= 0.98f) {
            self->f29C -= 0.015f;
            if (self->f29C < 0.0f) {
                self->f29C = 0.0f;
            }
        }
    }
    self->mPosition = pos;
    self->mTarget = self->v290;
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    fn_801BE894(self->mpFrustum, t * (f - e) + e);
}

void fn_804CA994(BowCam2* self) {
    if (self->i3AC == 0) {
        self->f214 = self->f190;
        self->f218 = 0.0f;
    }
    if (self->f190 > 2.0f + self->f1B8) {
        self->f218 = self->f190 - self->f214;
    } else {
        self->f218 *= 0.92f;
    }
    f32 a = self->f214 + self->f218;
    f32 pz = 40.0f + a;
    f32 tz = 16.0f + a;
    f32 x = self->f1A4 + self->f1B0;
    self->f214 = a;
    VEC3 pos(x, 4.0f, pz);
    self->mPosition = pos;
    VEC3 tgt(x, 3.0f, tz);
    self->mTarget = tgt;
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    fn_801BE894(self->mpFrustum, 20.0f);
}

int fn_804CAA94(BowCam2* self) {
    s32 s = self->mpPath->index;
    if (s == 3) {
        return 1;
    }
    return s == 4;
}

void fn_804CAABC(BowCam2* self, int n) {
    if (self->i3AC == 0) {
        fn_804CD120(self->mpPath, n + 0x10);
        self->i244 = 0;
    }
    fn_804CC5B4(self);
    f32 k = self->f390;
    self->mTarget = self->mTarget + fn_804CAF90(self) * k;
}

// MATCH-PENDING (R17): ledger #7.
// Placeholder for a function absent from the DOL (inferred: dead-stripped by
// the linker; name and body are NOT known). A non-constant SetFovy and an
// s32->f32 conversion were compiled here: 0.0, 180.0, 0.5, 256/360 and the
// signed magic double sit at the head of .sdata2, ahead of fn_804CAB84's
// constants. Only its pool entries survive.
f32 BowCam_StrippedFovy(BowCamera* self, f32 fovy, int n) {
    self->mpFrustum->SetFovy(fovy);
    return n;
}

void fn_804CAB84(BowCamera* self, int type) {
    VEC3 pos;
    VEC3 tgt;
    if (type == 0) {
        tgt = VEC3(-2.27784f, 4.42f, -183.574f);
        pos = VEC3(-6.03312f, 7.19999f, -179.143f);
    }
    if (type == 1) {
        tgt = VEC3(0.0f, 4.42f, -191.9f);
        pos = VEC3(0.0f, 8.08f, -197.2f);
    }
    if (type == 2) {
        tgt = VEC3(0.0f, 1.47f, -178.1f);
        pos = VEC3(0.0f, 1.69f, -174.7f);
    }
    self->mPosition = pos + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mTarget = tgt + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    self->mpFrustum->SetFovy(45.0f);
}

const int lbl_804C5BDC[1] = {200};

void fn_804CADAC(BowCamera* self) {
    BowExcelGlobal* g;
    if (self->mFrame == 0) {
        self->f250 = 10.0f;
        self->f23C = self->v188.z + self->f250;
    }
    f32 len = 182.6f;
    VEC3 a(0.0f, self->prm.pA0, self->prm.pAC);
    VEC3 b(0.0f, self->prm.p94, self->v188.z);
    f32 t = -self->v188.z / len;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        t = 1.0f;
    }
    f32 ft = t * (f32)(lbl_804C5BDC[0] - 3);
    int i = (int)ft;
    f32 fr = ft - (f32)i;
    g = lbl_804BF9A8->p4;
    // MATCH-PENDING (R17): `gi` (g advanced by i floats, read at +0x1494) makes the
    // [i] row address a named variable coloured after g; the real source probably
    // just wrote g->t1494[i] and got that address as a CSE variable some other way.
    BowExcelGlobal* gi = (BowExcelGlobal*)((f32*)g + i);
    f32 v = fr * (g->t1494[i + 1] - gi->t1494[0]) + gi->t1494[0];
    self->mPosition = a + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mTarget = b + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    self->mpFrustum->SetFovy(v * (self->prm.pA8 - self->prm.p7C) + self->prm.p7C);
}

const int lbl_807005D0[1] = {30};

VEC3 fn_804CAF90(BowCam2* self) {
    VEC3 v(0.0f, 0.0f, 0.0f);
    if (self->i244 != 0) {
        f32 t = self->f384 * (f32)(self->i244 - self->i38C);
        int i = (int)t;
        f32 fr = t - (f32)i;
        if (i >= 0 && i < lbl_807005D0[0] - 1) {
            int j = i + 1;
            v.x = fr * (BowCamShakeRow(j)->t211C[0].x - BowCamShakeRow(i)->t211C[0].x) + BowCamShakeRow(i)->t211C[0].x;
            v.y = fr * (BowCamShakeRow(j)->t211C[0].y - BowCamShakeRow(i)->t211C[0].y) + BowCamShakeRow(i)->t211C[0].y;
            v.z = fr * (BowCamShakeRow(j)->t211C[0].z - BowCamShakeRow(i)->t211C[0].z) + BowCamShakeRow(i)->t211C[0].z;
            v *= self->f388;
        }
        self->i244++;
    }
    return v;
}

const int lbl_804C5BE8[1] = {60};
const int lbl_804C5BEC[1] = {300};
const int lbl_804C5BF0[1] = {300};
const int lbl_804C5BF4[1] = {60};
const int lbl_804C5BF8[1] = {300};
const int lbl_804C5BFC[1] = {300};
const int lbl_804C5C00[1] = {30};

// MATCH-PENDING (R17): invented row helper (name inferred), like BowCamShakeRow: the f32
// tables are read as (p4 + k*4)->tXXXX[0] so the row address is formed before the field
// offset (retail colours it after the table base); the real source probably wrote
// lbl_804BF9A8->p4->tXXXX[k].
static inline BowExcelGlobal* BowCamF32Row(int k) {
    return (BowExcelGlobal*)((f32*)lbl_804BF9A8->p4 + k);
}

// MATCH-PENDING (R17): invented row helper (name inferred) for the 16-byte tEF4 rows, read
// through the cached BowRes* (re-read after the flag branch as retail does); same
// row-before-offset association as BowCamShakeRow/BowCamF32Row. Real source probably wrote
// tbl->tEF4[j].b with tbl = res->p4.
static inline BowExcelGlobal* BowCamT4Row(BowRes* r, int k) {
    return (BowExcelGlobal*)((BowCamTbl4*)r->p4 + k);
}
// MATCH-PENDING (R17): invented one-field holder (name inferred) for the side flag: turns
// the named bool into an optimizer var coloured before j (retail flag r4, j r5). Real
// source probably had a plain `bool flag`.
struct BowCamFlagRef {
    bool b;
};
void fn_804CB0C0(BowCamera* self, int type) {
    BowCamParams* prm = &self->prm;
    VEC3 oldPos = self->mPosition;
    VEC3 oldTgt = self->mTarget;
    f32 oldFovy = self->mpFrustum->mFovY;
    f32 rate;
    f32 height;
    f32 angle;
    f32 fovy;
    f32 dist;
    nw4r::math::MTX34 m;
    VEC3 A;

    if (self->mFrame == 0) {
        self->i20C = 50;
        self->i210 = 50;
        self->b1A8 = 0;
        self->f214 = 1.0f;
        self->i234 = 0;
    }
    if (self->b1A8) {
        self->i210 = 0;
        self->i20C++;
    }
    if (!self->b1A8) {
        self->i20C = 0;
        self->i210++;
    }
    if (self->b1A8) {
        if (lbl_804BF9A8->p4->t10D4[self->i20C].d < -0.5f || self->i20C >= lbl_804C5BE8[0]) {
            self->i20C--;
        }
        rate = lbl_804BF9A8->p4->t10D4[self->i20C].d;
        self->f214 = lbl_804BF9A8->p4->t10D4[self->i20C].b;
    } else {
        if (lbl_804BF9A8->p4->t10D4[self->i210].c < -0.5f || self->i210 >= lbl_804C5BE8[0]) {
            self->i210--;
        }
        rate = lbl_804BF9A8->p4->t10D4[self->i210].c;
        self->f214 = lbl_804BF9A8->p4->t10D4[self->i210].a;
    }
    if (self->f214 > 1.0f) {
        self->f214 = 1.0f;
    }
    if (self->f214 < 0.0f) {
        self->f214 = 0.0f;
    }
    if (rate > 0.99f) {
        rate = 1.0f;
    }
    if (rate < 0.01f) {
        rate = 0.0f;
    }

    height = rate * (prm->p00 - prm->p14) + prm->p14;
    // MATCH-PENDING (R17): `baseDist` (name inferred) copied into dist gives the scheduler an
    // fmr after the dist lerp (coalesced away by the allocator); with height lerped first this
    // reproduces the retail load order and FPR colours (rate f6). Real source probably had two
    // distance variables (lerped base vs. per-mode distance) rather than this one-use copy.
    f32 baseDist = rate * (prm->p04 - prm->p1C) + prm->p1C;
    dist = baseDist;
    angle = rate * (prm->p08 - prm->p18) + prm->p18;
    fovy = rate * (prm->p0C - prm->p30) + prm->p30;

    switch (type) {
    case 0:
        self->i1AC = 0;
        self->i1B0 = 0;
        self->f194 = 0.0f;
        self->f1B4 = 0.0f;
        self->i1B8 = 0;
        self->v1E0 = VEC3(0.0f, 0.0f, 0.0f);
        self->f204 = 0.0f;
        self->f208 = 0.0f;
        self->i1A0 = -1;
        break;
    case 1: {
        f32 a = lbl_804BF9A8->p4->t2C4[self->i1AC];
        f32 b = lbl_804BF9A8->p4->t774[self->i1B0];
        if (a < 0.0f) {
            a = 0.0f;
        }
        if (b < 0.0f) {
            b = 0.0f;
        }
        if (a > 1.0f) {
            a = 1.0f;
        }
        if (b > 1.0f) {
            b = 1.0f;
        }
        dist = prm->p1C - a * prm->p28 - b * prm->p2C;
        if (self->i1AC < lbl_804C5BEC[0] - 1) {
            self->i1AC++;
        }
        if (self->i1B0 < lbl_804C5BF0[0] - 1 && self->f194) {
            self->i1B0++;
        }
        break;
    }
    case 2:
        if (self->i1B8 < lbl_804C5BF4[0] - 1) {
            self->i1B8++;
        }
        break;
    case 3:
        break;
    }

    A.x = self->f198 + prm->p24;
    A.y = dist * (f32)sin(angle) + prm->p20;
    A.z = dist * (f32)cos(angle) + prm->p10;
    VEC3 B(self->f198 + prm->p24, height, prm->p10);
    nw4r::math::MTX34RotXYZFIdx(&m, 0.0f, 40.743664f * -self->f19C, 0.0f);
    VEC3 e;
    VEC3 c(self->f198, 0.0f, 20.0f);
    c += (self->v17C - c) * prm->pCC;
    e = A - c;
    nw4r::math::VEC3TransformNormal(&e, &m, &e);
    A = c + e;
    e = B - c;
    nw4r::math::VEC3TransformNormal(&e, &m, &e);
    B = c + e;

    if (type != 3) {
        if (self->f194) {
            self->f1B4 += prm->p40;
            if (self->f1B4 > 1.0f) {
                self->f1B4 = 1.0f;
            }
            f32 neg = -self->v188.z;
            if (self->f204 < neg) {
                f32 dd = neg - self->f204;
                self->f204 = neg;
                self->f208 = dd;
            } else {
                self->f204 += self->f208;
                self->f208 *= prm->p50;
            }
            f32 len = 182.6f;
            f32 t = self->f204 / len;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            f32 ft2 = t * (f32)(lbl_804C5BF8[0] - 3);
            f32 ft1 = t * (f32)(lbl_804C5BFC[0] - 3);
            int i2 = (int)ft2;
            f32 fr2 = ft2 - (f32)i2;
            int i1 = (int)ft1;
            f32 fr1 = ft1 - (f32)i1;
            f32 va = fr1 * (BowCamF32Row(i1 + 1)->t2734[0] - BowCamF32Row(i1)->t2734[0]) + BowCamF32Row(i1)->t2734[0];
            f32 vb = fr1 * (BowCamF32Row(i1 + 1)->t1C6C[0] - BowCamF32Row(i1)->t1C6C[0]) + BowCamF32Row(i1)->t1C6C[0];
            f32 vc = fr2 * (BowCamF32Row(i2 + 1)->t2284[0] - BowCamF32Row(i2)->t2284[0]) + BowCamF32Row(i2)->t2284[0];
            B.x *= 1.0f - vb;
            B.y *= 1.0f - va;
            if (self->i1A0 >= 0) {
                self->mpFrustum->SetFovy(vc * (prm->fov[self->i1A0] - prm->p30) + fovy);
            } else {
                self->mpFrustum->SetFovy(vc * (prm->p34 - prm->p30) + fovy);
            }
        } else {
            self->mpFrustum->SetFovy(fovy);
        }
    }

    height = 1.0f;
    self->mpFrustum->SetNearZ(height);
    if (type == 2) {
        if (self->b348) {
            self->mpFrustum->SetNearZ(0.5f);
            f32 d = self->v188.z - self->v1D4.z;
            if (d < 0.03f && self->v188.z > 30.0f) {
                d = 0.03f;
            }
            self->v1D4.x = self->v188.x;
            self->v1D4.y = self->v188.y;
            self->v1D4.z += d;
            self->v1BC += (self->v188 - self->v1BC) * prm->pC4;
            self->v1C8 += (self->v1D4 - self->v1C8) * prm->pC4;
            f32 rot = self->f19C;
            f32 cs = -(f32)cos(rot);
            f32 sn = (f32)sin(self->f19C);
            EGG::Vector3f dir(sn, 0.0f, cs);
            f32 len2 = 30.0f;
            BowCamFlagRef flag;
            f32 slope = dir.x / dir.z;
            flag.b = slope * len2 + self->f198 > 0.0f;
            f32 u = 0.6f * self->v1BC.z;
            if (u < 0.0f) {
                u = 0.0f;
            }
            int n = lbl_804C5C00[0] - 1;
            if (u > (f32)n) {
                u = (f32)n - 0.001f;
            }
            int j = (int)u;
            f32 fj = u - (f32)j;
            f32 w = 0.6f * self->v1C8.z;
            if (w < 0.0f) {
                w = 0.0f;
            }
            if (w > (f32)n) {
                w = (f32)n - 0.001f;
            }
            int k = (int)w;
            f32 fk = w - (f32)k;
            BowRes* res = lbl_804BF9A8;
            VEC3 P;
            P.x = fj * (BowCamT4Row(res, j + 1)->tEF4[0].b - BowCamT4Row(res, j)->tEF4[0].b) + BowCamT4Row(res, j)->tEF4[0].b;
            if (flag.b) {
                P.x *= -1.0f;
            }
            P.x += self->v1BC.x;
            // MATCH-PENDING (R17): `rz` (name inferred) names the j+1 row before P.y so its
            // (j+1)*16 CSE temp is created before the base+k*16 one (IRO numbers CSE temps in
            // reverse creation order; retail colours (j+1)*16 first). Real source probably
            // indexed the row inline in P.z.
            BowExcelGlobal* rz = BowCamT4Row(res, j + 1);
            P.y = fk * (BowCamT4Row(res, k + 1)->tEF4[0].c - BowCamT4Row(res, k)->tEF4[0].c) + BowCamT4Row(res, k)->tEF4[0].c;
            P.z = fj * (rz->tEF4[0].d - BowCamT4Row(res, j)->tEF4[0].d) + BowCamT4Row(res, j)->tEF4[0].d;
            VEC3 Q;
            Q = self->v1BC;
            Q.y = fk * (BowCamT4Row(res, k + 1)->tEF4[0].a - BowCamT4Row(res, k)->tEF4[0].a) + BowCamT4Row(res, k)->tEF4[0].a;
            // MATCH-PENDING (R17): `h` (name inferred) reaches v1F8 as h[1] so &v1F8 stays a
            // CSE address register (retail addi r6,r29,0x1f8 + psq 0/8(r6)); a member access
            // folds into the displacement. Real source probably had a two-VEC3 eye/target
            // member or helper that this pointer stands in for.
            VEC3* h = &self->v1EC;
            A = h[0] + (P - h[0]) * height;
            B = h[1] + (Q - h[1]) * height;
            VEC3 D = B - A;
            PSVECNormalize(&D, &D);
            if (D.z > prm->pC8) {
                self->b254 = 0;
            } else {
                self->b254 = 1;
            }
        } else {
            A = self->v1EC;
            A.y += prm->p44 * lbl_804BF9A8->p4->tC24[self->i1B8].x;
            A.z += prm->p48 * lbl_804BF9A8->p4->tC24[self->i1B8].y;
            VEC3 F = B - A;
            VEC3 G = self->v188 - A;
            G.x -= self->f1A4;
            PSVECNormalize(&G, &G);
            if (G.z >= prm->p4C) {
                B = self->v1E0;
            } else {
                PSVECNormalize(&F, &F);
                B = F + (G - F) * lbl_804BF9A8->p4->tC24[self->i1B8].z;
                PSVECNormalize(&B, &B);
                B += A;
                self->v1E0 = B;
            }
            self->v1BC = A;
            self->b254 = 1;
        }
    } else {
        self->v1BC = self->v188;
        self->v1C8 = self->v188;
        self->v1BC.y = lbl_804BF9A8->p4->tEF4[0].a;
        self->v1EC = A;
        self->v1F8 = B;
        self->v1D4 = self->v188;
    }

    if (type == 3) {
        self->v218 *= prm->pB0;
        self->v224 *= prm->pB0;
        self->f230 *= prm->pB0;
        self->mPosition = self->mPosition + self->v218;
        self->mTarget = self->mTarget + self->v224;
        EGG::Frustum* frustum = self->mpFrustum;
        frustum->SetFovy(self->f230 + frustum->GetFovy());
    } else {
        self->mPosition = A + VEC3(self->f1A4, 0.0f, 0.0f);
        self->mTarget = B + VEC3(self->f1A4, 0.0f, 0.0f) + BowCamShake(self);
        self->mUp = VEC3(0.0f, 1.0f, 0.0f);
        self->v218 = self->mPosition - oldPos;
        self->v224 = self->mTarget - oldTgt;
        self->f230 = self->mpFrustum->GetFovy() - oldFovy;
    }
}

void fn_804CC40C(BowCam2* self) {
    self->mPosition = VEC3(6.42504f, 4.29835f, -2.00618f);
    self->mTarget = VEC3(5.24153f, 4.25234f, 1.9646f);
    self->mUp = VEC3(0.0f, 1.0f, 0.0f);
    fn_801BE894(self->mpFrustum, 39.0f);
}

void fn_804CC49C(BowCam2* self) {
    if (self->i3AC == 0) {
        fn_804CD120(self->mpPath, 9);
    }
    fn_804CC5B4(self);
}

void fn_804CC4E4(BowCam2* self) {
    if (self->i3AC == 0) {
        if (lbl_806F5950->mode == 0) {
            fn_804CD120(self->mpPath, 10);
        } else {
            fn_804CD120(self->mpPath, 13);
        }
    }
    fn_804CC5B4(self);
}

void fn_804CC54C(BowCam2* self) {
    if (self->i3AC == 0) {
        s32 t = self->i3C4;
        BowCamPath* p = self->mpPath;
        s32 idx;
        if (t == 0) {
            idx = 1;
        } else {
            idx = 3;
            if (t == 1) {
                idx = 2;
            }
        }
        fn_804CD120(p, idx);
    }
    fn_804CC5B4(self);
}

void fn_804CC5B4(BowCam2* self) {
    fn_804CCE3C(self->mpPath);
    BowCamPath* path = self->mpPath;
    self->mCameraType = path->out.camType;
    self->mPosition = path->out.pos + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mTarget = path->out.target + VEC3(self->f1A4, 0.0f, 0.0f);
    self->mUp = path->out.up;
    fn_801BE894(self->mpFrustum, path->out.fovy);
    self->b3B4 = fn_804CCFE4(self->mpPath);
    self->b264 = !(path->out.target.z > path->out.pos.z);
}

f32 fn_804CC6E8(BowCamera* self) {
    if (self->mState == 3 || self->mState == 4) {
        return self->f214 * ((1.0f - self->prm.p3C) * self->f1B4 + self->prm.p3C);
    }
    return 1.0f;
}

f32 fn_804CC720(BowCamera* self) {
    if (self->mState == 3 || self->mState == 4) {
        return self->f214 * (-self->prm.p38 * self->f1B4 + self->prm.p38);
    }
    return 1.0f;
}

void ogws_fn_8031B3F4(BowCamera* self) {
    if (self->mState < 0) {
        return;
    }
    if (self->mFrame < 0) {
        self->mFrame = 0;
    }
    switch (self->mState) {
    case 0:
        if (self->mFrame == 0) {
            BowCamPath* path = self->mpPath;
            int idx;
            if (self->i344 == 0) {
                idx = 1;
            } else {
                idx = 3;
                if (self->i344 == 1) {
                    idx = 2;
                }
            }
            fn_804CD120(path, idx);
        }
        BowCamApplyPath(self);
        break;
    case 1:
        if (self->mFrame == 0) {
            fn_804CD120(self->mpPath, 4);
        }
        BowCamApplyPath(self);
        break;
    case 2:
        BowCamSetFixed(self);
        break;
    case 3:
        fn_804CB0C0(self, 0);
        break;
    case 4:
        fn_804CB0C0(self, 1);
        break;
    case 5:
        fn_804CB0C0(self, 2);
        break;
    case 6:
        fn_804CB0C0(self, 3);
        break;
    case 7:
        if (self->mFrame == 0) {
            if (self->b340 == 0) {
                fn_804CD120(self->mpPath, (self->i33C != 0) + 5);
            } else {
                fn_804CD120(self->mpPath, (self->i33C != 0) + 7);
            }
        }
        BowCamApplyPath(self);
        break;
    case 8:
        if (self->mFrame == 0) {
            fn_804CD120(self->mpPath, self->i338 + 12);
        }
        BowCamApplyPath(self);
        break;
    case 9:
        if (self->mFrame == 0) {
            fn_804CD120(self->mpPath, 9);
        }
        BowCamApplyPath(self);
        break;
    case 10:
    case 11:
    case 12:
        fn_804CAB84(self, self->mState - 10);
        break;
    case 13:
    case 14:
    case 15: {
        int k = self->mState - 13;
        if (self->mFrame == 0) {
            if (k == 0) {
                fn_804CD120(self->mpPath, self->i338 + 42);
            } else if (k == 1) {
                fn_804CD120(self->mpPath, self->i338 + 22);
            } else {
                fn_804CD120(self->mpPath, self->i338 + 32);
            }
            self->i234 = 0;
        }
        BowCamApplyPath(self);
        BowCamAddShake(self);
        break;
    }
    case 16:
        fn_804CADAC(self);
        break;
    case 17:
        fn_804CAB84(self, 2);
        break;
    }
    self->mFrame++;
    self->CalcMatrix();
}

void fn_804CC8B8(BowCamera* self) {
    self->mpFrustum->SetNearZ(1.0f);
    fn_804CD180(self->mpPath);
    memset(&self->v17C, 0, 0xDC);
    self->mState = -1;
    self->b334 = 0;
}

void fn_804CC914(BowCamera* self, EGG::Frustum* frustum, BowCamPath* path) {
    self->mpFrustum = frustum;
    self->mpPath = path;
    self->prm.p00 = -1.0f;
    self->prm.p04 = 160.0f;
    self->prm.p08 = 0.01f;
    self->prm.p0C = 10.0f;
    self->prm.p10 = -150.0f;
    self->prm.p14 = -15.0f;
    self->prm.p18 = 0.035f;
    self->prm.p1C = 191.0f;
    self->prm.p20 = 2.0f;
    self->prm.p24 = 0.0f;
    self->prm.p28 = 20.0f;
    self->prm.p2C = 20.0f;
    self->prm.p30 = 35.0f;
    self->prm.p34 = 6.0f;
    self->prm.p38 = 0.3f;
    self->prm.p3C = 0.25f;
    self->prm.p40 = 0.02f;
    self->prm.p44 = 5.0f;
    self->prm.p48 = 5.0f;
    self->prm.p4C = 3.0f;
    self->prm.p50 = 0.98f;
    self->prm.fov[0] = 6.0f;
    self->prm.fov[1] = 6.0f;
    self->prm.fov[2] = 6.0f;
    self->prm.fov[3] = 6.0f;
    self->prm.fov[4] = 6.0f;
    self->prm.fov[5] = 6.0f;
    self->prm.p6C = 7.0f;
    self->prm.p70 = 8.0f;
    self->prm.p74 = 9.0f;
    self->prm.p78 = 10.0f;
    self->prm.p7C = 20.0f;
    self->prm.p88 = 0.5f;
    self->prm.p80 = -170.0f;
    self->prm.p8C = 1.5f;
    self->prm.p84 = -150.0f;
    self->prm.p90 = 0.95f;
    self->prm.p94 = 2.0f;
    self->prm.p98 = 0.02f;
    self->prm.p9C = 0.04f;
    self->prm.pA0 = 15.0f;
    self->prm.pA4 = 10.0f;
    self->prm.pAC = 40.0f;
    self->prm.pA8 = 4.0f;
    self->prm.pB0 = 0.96f;
    self->prm.pC8 = -0.6f;
    self->prm.pCC = 0.4f;
    self->prm.pC4 = 0.03f;
    self->prm.pB4 = 0.8f;
    self->prm.pB8 = 3.0f;
    self->prm.iBC = 20;
    self->prm.pC0 = 0.03f;
}

}  // extern "C"
