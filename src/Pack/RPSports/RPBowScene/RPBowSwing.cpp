// Resort (RZTE01_01) port of Wii Sports RPBowSwing.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBowSwing: bowling swing detector (Wii remote motion state machine).
// The object (allocated by RPBow_80313028, vtable lbl_803CA2D0) owns a motion
// sample ring buffer (RPUtl_801C67B8 SampleBuffer) and classifies the throw
// from the accelerometer history. Class and field names are inferred from use
// (invented); the functions keep their fn_ names and take the object as an
// explicit pointer.
//
// Functions are written in ASCENDING address order with
// `#pragma defer_codegen off`; .sdata2 is byte-exact (an unreferenced static
// placeholder supplies the 180/3.14159 pair that sits after ogws_fn_8031C388's 1.0).
//
// Matching notes (fn_804E842C):
// - EGG::Vector3f here has NO destructor: a local with a user dtor (sum)
//   stopped MWCC from CSE-ing the sample-buffer loads across the __fabs
//   compares, and also blocked inlining of the VEC3 operators;
// - sample access is BowSwing::Get(back) = local buffer pointer + a static
//   BowAt(buf, index) wrap (member/`this`-based forms change CSE, register
//   choice or argument order); the i+1 neighbour is Get2 (`-2 - back +
//   index`, the original's subfic/add);
// - PSVECMag goes through an inline VEC3Len and the excel block through an
//   inline BowExcel() reading word 1 of a cast pointer array, so the excel
//   pointer is re-read after each call like the original;
// - comparisons between two magnitude calls are split into nested ifs with
//   locals (left operand first); `target *= f6C` keeps fmuls/fsubs apart;
// - ogws_fn_801C67B8 is declared (buf, f32, f32, s32) for the argument load order.
// - pts is a NON-const EGG::Vector3f* (as the caller RPBow_80320EFC declares
//   it): with a const pointee the 3.0a5.2 alias analysis lets the unrolled
//   sum loop's lfs float above the previous copy's paired-single chain, which
//   recolours the work registers (f6/f5/f4 instead of f4/f2/f0);
// - the case-4 body reads the sample through GetC (const getters for index
//   and samples), so those two loads are re-read like the original while
//   capacity stays CSE'd.
// The sum loop uses an inline VEC3(x,y,z) temp (a BowAddSample helper moved the
// temp slot to the frame end); the m2/d fabs results go through a double local.

#pragma defer_codegen off

extern "C" {
void* memset(void*, int, unsigned long);
double atan2(double, double);
double sqrt(double);
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
    VEC3(const _VEC3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
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
}  // namespace math
}  // namespace nw4r

using nw4r::math::VEC3;

extern "C" f32 PSVECMag(const VEC3*);

static inline f32 VEC3Len(const VEC3* p) {
    return PSVECMag(p);
}

namespace EGG {
struct Vector3f : VEC3 {
    Vector3f() {}
    Vector3f(f32 fx, f32 fy, f32 fz) : VEC3(fx, fy, fz) {}

    Vector3f& operator=(const Vector3f& r) {
        x = r.x;
        y = r.y;
        z = r.z;
        return *this;
    }
};
}  // namespace EGG

using EGG::Vector3f;

static inline void BowAddSample(Vector3f& sum, const nw4r::math::_VEC3& sample) {
    sum += VEC3(sample.x, sample.y, sample.z);
}

// Inferred: RPUtl_801C67B8 motion sample (0x30 bytes).
struct BowSample {
    Vector3f raw;       // 0x00
    Vector3f filtered;  // 0x0C
    Vector3f delta;     // 0x18
    Vector3f velocity;  // 0x24
};

// Inferred: RPUtl_801C67B8 sample ring buffer (0x1B8 bytes).
struct BowSampleBuffer {
    Vector3f backup[32];   // 0x000
    s32 backupPending[3];  // 0x180
    s32 index;             // 0x18C
    s32 capacity;          // 0x190
    BowSample* samples;    // 0x194
    s32 pending[3];        // 0x198
    f32 startScale;        // 0x1A4
    f32 endScale;          // 0x1A8
    f32 startBias;         // 0x1AC
    f32 endBias;           // 0x1B0
    f32 threshold;         // 0x1B4

    void SetScale(f32 s, f32 e) {
        startScale = s;
        endScale = e;
    }
    void SetBias(f32 s, f32 e) {
        startBias = s;
        endBias = e;
    }
    s32 GetIndex() const {
        return index;
    }
    const BowSample* GetSamples() const {
        return samples;
    }
    void SetThreshold(f32 t) {
        threshold = t;
    }
    void Save() {
        for (int i = 0; i < 17; i++) {
            backup[i] = samples[i].filtered;
        }
        for (int i = 0; i < 3; i++) {
            backupPending[i] = pending[i];
        }
    }
    void Restore() {
        for (int i = 0; i < 17; i++) {
            samples[i].filtered = backup[i];
        }
        for (int i = 0; i < 3; i++) {
            pending[i] = backupPending[i];
        }
    }
};

extern "C" {
BowSampleBuffer* ogws_fn_801C71F4(void*, s32);
void ogws_fn_801C6B64(BowSampleBuffer*, const VEC3*);
void ogws_fn_801C67B8(BowSampleBuffer*, f32, f32, s32);
}

// Inferred: BowExcelGlobal swing tuning values.
struct BowSwingExcel {
    u8 pad_0x0[0x50];
    f32 f50, f54, f58, f5C;  // 0x50
    u8 pad_0x60[0x4];
    f32 f64, f68, f6C, f70;  // 0x64
    s32 x74;                 // 0x74
    u8 pad_0x78[0x98 - 0x78];
    s32 x98;   // 0x98
    f32 f9C;   // 0x9C
    f32 fA0;   // 0xA0
    f32 fA4;   // 0xA4
    f32 fA8;   // 0xA8
    u8 pad_0xAC[0x4];
    f32 fB0;  // 0xB0
    f32 fB4;  // 0xB4
    f32 fB8;  // 0xB8
    s32 xBC;  // 0xBC
    f32 fC0;  // 0xC0
    f32 fC4;  // 0xC4
    u8 pad_0xC8[0x4];
    s32 xCC;  // 0xCC
    f32 fD0;  // 0xD0
};
// lbl_804BF9A8: bowling resource object (inferred); its +4 word is the
// BowExcelGlobal block. Reading it as element 1 of a cast pointer array (not
// a struct field, not a natively typed X**) keeps lbl_804BF9A8 cached across
// blocks while the +4 word is re-read, like the original.
struct BowRes;
extern BowRes* lbl_804BF9A8;

static inline BowSwingExcel* BowExcel() {
    return ((BowSwingExcel**)lbl_804BF9A8)[1];
}

static inline BowSample& BowAt(BowSampleBuffer* b, int i) {
    while (i < 0) i += b->capacity;
    while (i >= b->capacity) i -= b->capacity;
    return b->samples[i];
}

struct BowVec2 {
    f32 x, y;
    BowVec2(f32 fx, f32 fy) : x(fx), y(fy) {}
};

static inline f32 BowCross(const BowVec2& a, const BowVec2& b) {
    return a.x * b.y - a.y * b.x;
}

static inline f32 BowAtan2(f32 y, f32 x) {
    return atan2(y, x);
}

static inline f32 BowAbs(f32 x) {
    return __fabs(x);
}

// Inferred (names invented): swing detector state (+0x10, 0xDC bytes,
// cleared by the reset functions).
struct BowSwingState {
    u8 started;     // 0x00
    u8 b01;         // 0x01
    u8 b02;         // 0x02
    u8 released;    // 0x03
    s32 x04;        // 0x04
    u8 b08;         // 0x08
    s32 state;      // 0x0C
    s32 timer;      // 0x10
    f32 angle;      // 0x14
    f32 f18;        // 0x18
    f32 f1C;        // 0x1C
    f32 f20;        // 0x20
    f32 f24;        // 0x24
    f32 f28;        // 0x28
    u8 b2C;         // 0x2C
    f32 f30;        // 0x30
    s32 x34;        // 0x34
    s32 x38;        // 0x38
    f32 f3C;        // 0x3C
    f32 f40;        // 0x40
    f32 prevAngle;  // 0x44
    f32 f48;        // 0x48
    f32 f4C;        // 0x4C
    s32 x50;        // 0x50
    u8 b54;         // 0x54
    s32 x58[2];     // 0x58
    f32 f60;        // 0x60
    s32 x64;        // 0x64
    s32 x68;        // 0x68
    s32 x6C;        // 0x6C
    u8 pad_0x70[0x84 - 0x70];
    f32 f84;        // 0x84
    f32 f88;        // 0x88
    s32 x8C;        // 0x8C
    f32 f90;        // 0x90
    f32 f94;        // 0x94
    f32 f98;        // 0x98
    f32 f9C;        // 0x9C
    f32 fA0;        // 0xA0
    s32 xA4;        // 0xA4
    s32 xA8;        // 0xA8
    u8 bAC;         // 0xAC
    s32 xB0;        // 0xB0
    Vector3f vB4;   // 0xB4
    Vector3f vC0;   // 0xC0
    s32 xCC;        // 0xCC
    Vector3f vD0;   // 0xD0
};

struct BowSwingResult {
    u8 b0;
};

// Inferred (names invented): swing detector.
struct BowSwing {
    void* vtbl;              // 0x000
    s32 debug;               // 0x004
    BowSampleBuffer* buf;    // 0x008
    BowSwingResult result;   // 0x00C
    BowSwingState st;        // 0x010
    f32 fEC;   // 0x0EC
    f32 fF0;   // 0x0F0
    f32 fF4;   // 0x0F4
    f32 fF8;   // 0x0F8
    s32 xFC;   // 0x0FC
    f32 f100;  // 0x100
    f32 f104;  // 0x104
    s32 x108;  // 0x108
    s32 x10C;  // 0x10C
    s32 x110;  // 0x110
    u8 b114;   // 0x114
    f32 f118;  // 0x118
    s32 x11C;  // 0x11C
    s32 x120;  // 0x120
    s32 x124;  // 0x124
    s32 x128;  // 0x128
    f32 f12C;  // 0x12C
    s32 x130;  // 0x130
    f32 f134;  // 0x134
    f32 f138;  // 0x138
    s32 x13C;  // 0x13C
    f32 f140;  // 0x140
    f32 f144;  // 0x144
    s32 x148;  // 0x148

    void SetState(s32 s) {
        st.state = s;
        st.timer = -1;
    }
    BowSample& Get(int back) {
        BowSampleBuffer* b = buf;
        return BowAt(b, b->index - 1 - back);
    }
    // MATCH-PENDING (R17): second accessor for the same sample; its const
    // GetIndex/GetSamples loads are a different IRO expression from Get()'s
    // plain loads, so IRO_CommonSubs does not reuse the condition's index and
    // samples (capacity stays shared). The real RPUtl sample buffer probably
    // has its own getter API that the condition and body reach differently.
    const BowSample& GetC(int back) {
        BowSampleBuffer* b = buf;
        int i = b->GetIndex() - 1 - back;
        while (i < 0) i += b->capacity;
        while (i >= b->capacity) i -= b->capacity;
        return b->GetSamples()[i];
    }
    BowSample& Get2(int back) {
        BowSampleBuffer* b = buf;
        return BowAt(b, -2 - back + b->index);
    }
    f32 Roll(int back) {
        return BowAtan2(Get(back).raw.z, -Get(back).raw.y);
    }
    f32 RawMag(int back) {
        return VEC3Len(&Get(back).raw);
    }
};

static inline void BowSwingDebugSample(f32, f32, f32) {}


// Resort BowSwing layout (invented names; offsets from the asm).
struct BowSwing2In {
    u8 st0[0xC];             // +0x00
    s32 state;               // +0x0C
    s32 timer;               // +0x10
    u8 pad_0x14[0x44 - 0x14];
    f32 f44;                 // +0x44
    u8 pad_0x48[0x4C4 - 0x48];
    f32 f4C4;                // +0x4C4
    u8 pad_0x4C8[0xA160 - 0x4C8];
    Vector3f vecs[80];       // +0xA160
    u8 pad_0xA520[0xB980 - 0xA520];
    u8 b980;                 // +0xB980
    u8 b981;                 // +0xB981
    u8 pad_0xB982[6];
    s32 xB988;               // +0xB988
    bool bB98C;              // +0xB98C
    u8 pad_0xB98D[3];
    f32 fB990;               // +0xB990
    f32 fB994;               // +0xB994
    s32 xB998;               // +0xB998
};
struct BowSwing2 {
    void* vtbl;              // 0x000
    s32 debug;               // 0x004
    BowSampleBuffer* buf;    // 0x008
    u8 b0C;                  // 0x00C
    u8 pad_0xD[3];
    BowSwing2In in;          // 0x010
};
extern "C" void* fn_804E5C3C(void*, s32);

extern "C" {

f32 fn_804E7DB4(BowSwing2* self, f32 a) {
    BowSwing2In* in = &self->in;
    f32 deg = 180.0f * (self->in.f44 / 3.14159f);
    if (in->b981) {
        if (a < -90.0f) a = 180.0f + (180.0f + a);
        if (deg < -90.0f) deg = 180.0f + (180.0f + deg);
    }
    f32 r;
    if (a < deg) {
        if (a > 90.0f) {
            r = 5.0f;
        } else {
            r = 0.8f;
        }
    } else {
        r = 5.0f;
    }
    if (in->b980 == 0) {
        r = 5.0f;
    }
    return r;
}

f32 fn_804E7E48(BowSwing2* self) {
    BowSwing2In* in = &self->in;
    f32 mx = 0.0f;
    for (int i = 0; i < 80; i++) {
        f32 m = (f32)__fabs(PSVECMag((const VEC3*)&in->vecs[i]) - 1.0f);
        if (m > mx) mx = m;
    }
    if (self->in.bB98C == 0 && mx < 1.0f) {
        mx = 0.0f;
    } else if (mx < 2.0f) {
        mx = 2.0f;
    }
    return mx;
}

int ogws_fn_8031C388(BowSwing* self, f32* pf, int* pi) {
    if (self->st.x50 != 0 && self->st.x50 < self->x11C) {
        *pf = 1.0f;
        *pi = self->x120;
        return 1;
    }
    return 0;
}

bool fn_804E83F4(BowSwing* self) {
    BowSampleBuffer* buf = self->buf;
    if (buf->pending[0] < 0 && buf->pending[1] < 0 && buf->pending[2] < 0) {
        return false;
    }
    return true;
}

// Placeholder for a function absent from the DOL (inferred: dead-stripped;
// name and body are NOT known): its 180 and 3.14159 sit right after
// ogws_fn_8031C388's 1.0 at the head of .sdata2.
static f32 BowSwing_StrippedRadToDeg(f32 rad) {
    return 180.0f * rad / 3.14159f;
}

static inline f32 BowRadToDeg(f32 rad) {
    return 180.0f * rad / 3.14159f;
}

BowSwingResult* fn_804E842C(BowSwing* self, Vector3f* pts, int n, int flag, f32 limit, u8 dir) {
    f32 bufA[32];
    f32 bufB[32];
    Vector3f sum;
    BowSwingState* st = &self->st;

    if (n) {
        sum = Vector3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < n; i++) {
            sum += VEC3(pts[i].x, pts[i].y, pts[i].z);
        }
        sum *= 1.0f / n;
        if (sum.x < -limit) sum.x = -limit;
        if (sum.x > limit) sum.x = limit;
        if (sum.y < -limit) sum.y = -limit;
        if (sum.y > limit) sum.y = limit;
        if (sum.z < -limit) sum.z = -limit;
        if (sum.z > limit) sum.z = limit;
        st->vD0 = sum;
    } else {
        sum = st->vD0;
    }

    self->buf->SetScale(BowExcel()->f58, BowExcel()->f5C);
    self->buf->SetBias(BowExcel()->f50, BowExcel()->f54);
    self->buf->SetThreshold(limit);
    ogws_fn_801C6B64(self->buf, &sum);

    VEC3 prev = st->vB4;
    st->vB4 += (sum - st->vB4) * 0.1f;
    VEC3 delta = st->vB4 - prev;
    st->vC0 += (sum - st->vB4) * 0.5f;
    st->x68 = 0;

    VEC3 filt = self->Get(0).filtered;
    VEC3Len(&filt);

    if (!st->started) {
        BowSwingExcel* res = BowExcel();
        if (VEC3Len(&delta) < res->fD0) {
            st->xB0++;
        } else {
            st->xB0 = 0;
        }
        if (st->xB0 > self->x13C) {
            st->xA4 = 0;
            st->fA0 = BowAtan2(st->vC0.z, -st->vC0.y);
            if (st->fA0 > self->f134 && st->fA0 < self->f138) {
                st->bAC = 1;
            } else {
                st->bAC = 0;
            }
        } else {
            st->xA4++;
        }
    }

    switch (st->state) {
    case 0: {
        BowSwingExcel* res = BowExcel();
        if (VEC3Len(&delta) < res->fD0) {
            st->x38++;
        } else {
            st->x38 = 0;
        }
        bool moving = st->x38 > BowExcel()->xCC;
        if (moving) {
            st->x6C = 0;
        } else {
            st->x6C++;
        }
        f32 a = BowAtan2(st->vC0.z, -st->vC0.y);
        st->prevAngle = st->angle;
        if (moving) {
            st->angle = a;
        } else {
            st->angle = st->angle + 0.1f * (a - st->angle);
        }
        st->f3C = st->angle;
        if (moving && st->angle > self->f140 && st->angle < self->f144) {
            st->xCC++;
        } else {
            st->xCC = 0;
        }
        if (st->xCC > self->x148) {
            st->x68 = 2;
        } else {
            st->x68 = 1;
        }
        if (st->x6C < 120 && flag) {
            self->SetState(1);
            self->st.released = 1;
        }
        break;
    }
    case 1: {
        int ok = 1;
        f32 a0 = self->Roll(0);
        f32 a1 = self->Roll(1);
        if (BowAbs(a0 - a1) > BowExcel()->fC0) {
            ok = 0;
        } else {
            for (int i = 0; i < BowExcel()->xBC; i++) {
                if (VEC3Len(&self->Get(i).delta) > BowExcel()->fC4) {
                    ok = 0;
                    break;
                }
            }
        }
        if (a0 > 0.0f || !ok) {
            self->SetState(2);
        }
        if (ok) {
            f32 a = self->Roll(0);
            st->prevAngle = st->angle;
            st->angle = a;
        }
        st->f3C = st->angle;
        if (!flag && !st->started) {
            st->f18 = st->angle;
            st->started = 1;
            self->SetState(5);
            st->f48 = 0.0f;
        }
        break;
    }
    case 2: {
        if (st->timer == 0) {
            st->f40 = st->angle;
            st->f20 = 0.0f;
            st->f24 = 0.0f;
            st->f28 = 1.0f;
            st->f30 = st->angle;
        }
        VEC3 v = self->Get(0).filtered;
        f32 m = VEC3Len(&v);
        f32 target = BowAbs(m - 1.0f);
        target *= BowExcel()->f6C;
        st->f24 += 0.2f * (target - st->f24);
        if (st->timer == 0) {
            f32 d = st->angle - st->prevAngle;
            if (d < 0.0f) d = 0.0f;
            st->f24 = d;
        }
        if (st->angle > 1.570795f) {
            st->f28 -= BowExcel()->f64;
        }
        if (st->f28 < 0.0f) {
            st->f28 = 0.0f;
        }
        st->f20 += st->f24;
        if (st->f20 > 1.0f) {
            st->f20 = 1.0f;
        }
        st->angle += st->f28 * (st->f20 * BowExcel()->f68);

        VEC3 v2 = self->Get(0).filtered;
        double m2d = __fabs(VEC3Len(&v2) - 1.0f);
        f32 m2 = m2d;
        for (int i = 0; i < 2; i++) {
            f32 thr = (i == 1) ? 1.5f : 0.0f;
            if (st->x58[i] == 0 && self->RawMag(1) > thr) {
                f32 a = self->RawMag(1);
                if (a >= self->RawMag(0)) {
                    f32 b = self->RawMag(1);
                    if (b > self->RawMag(2)) {
                        st->x58[i]++;
                    }
                }
            } else if (st->x58[i] == 1) {
                if (self->RawMag(1) < 0.9f * st->f60 || i == 0) {
                    f32 a = self->RawMag(1);
                    if (a <= self->RawMag(0)) {
                        f32 b = self->RawMag(1);
                        if (b < self->RawMag(2)) {
                            st->x58[i]++;
                        }
                    }
                }
            }
        }
        if (st->f28 < 1.0f && st->x64 == 0) {
            if (st->f60 > 1.6f) {
                st->x64 = 2;
            } else {
                st->x64 = 1;
            }
        }
        if (st->f60 < self->RawMag(0)) {
            st->f60 = self->RawMag(0);
        }
        int peak = 0;
        if (st->x64 != 0) {
            int k = st->x64 - 1;
            if (st->x58[k] >= 2) {
                peak = 1;
            }
        }
        if (st->f28 < 0.3f && peak) {
            if (m2 > 0.8f) {
                if (BowAbs(self->Get(0).raw.x) < 3.5 && BowAbs(self->Get(0).raw.y) < 3.5 &&
                    BowAbs(self->Get(0).raw.z) < 3.5)
                {
                    self->SetState(4);
                    st->f1C = st->angle;
                }
            }
            if (BowAbs(self->Get(2).raw.x) < 3.5 && BowAbs(self->Get(2).raw.y) < 3.5 &&
                BowAbs(self->Get(2).raw.z) < 3.5 && BowAbs(self->Get(1).raw.x) < 3.5 &&
                BowAbs(self->Get(1).raw.y) < 3.5 && BowAbs(self->Get(1).raw.z) < 3.5 &&
                BowAbs(self->Get(0).raw.x) < 3.5 && BowAbs(self->Get(0).raw.y) < 3.5 &&
                BowAbs(self->Get(0).raw.z) < 3.5 &&
                VEC3Len(&self->Get(0).delta) > BowExcel()->fB0)
            {
                self->SetState(4);
                st->b2C = 1;
                st->f1C = st->angle;
            }
        }
        st->f3C = st->angle;
        if (!flag && !st->started) {
            st->f18 = st->angle;
            st->started = 1;
            self->SetState(5);
            st->f48 = self->RawMag(0);
            st->b08 = 1;
        }
        break;
    }
    case 3: {
        f32 a0 = self->Roll(0);
        f32 a1 = self->Roll(1);
        double dd = __fabs(a0 - a1);
        f32 d = dd;
        if (VEC3Len(&self->Get(0).delta) > BowExcel()->fB8 || d > BowExcel()->fB4) {
            self->SetState(4);
            st->x34 = 0;
        }
        st->f3C = st->angle;
        break;
    }
    case 4: {
        f32 dec = 0.0f;
        for (int i = 0; i < 32; i++) {
            if (self->Get(i).raw.x < 3.5 && self->Get(i).raw.y < 3.5 && self->Get(i).raw.z < 3.5) {
                VEC3 v = self->GetC(i).filtered;
                dec = BowAbs(VEC3Len(&v) - 1.0f) * BowExcel()->f70;
                break;
            }
        }
        st->angle -= dec;
        if (st->angle < -1.2217295f) {
            st->angle = -1.2217295f;
        }
        if (!flag && !st->started) {
            st->started = 1;
            st->f18 = st->angle;
            st->x50 = 1;
        }
        if (st->x34 == 0 && st->started) {
            self->buf->Save();
            ogws_fn_801C67B8(self->buf, self->fF4, self->fF8, self->xFC);
            self->SetState(5);
            f32 mx = VEC3Len(&self->Get(0).filtered);
            st->f48 = 0.0f;
            for (int i = 0; i < 6; i++) {
                f32 m = VEC3Len(&self->Get(i).filtered);
                if (mx < m) mx = m;
                st->f48 += VEC3Len(&self->Get(i).filtered);
            }
            st->f48 = mx;
            f32 acc[2] = {0.0f, 0.0f};
            for (int i = 0; i < self->x128; i++) {
                BowVec2 a(self->Get(i).filtered.y, self->Get(i).filtered.z);
                BowVec2 b(self->Get2(i).filtered.y, self->Get2(i).filtered.z);
                f32 c = BowCross(a, b);
                if (c < 0.0f) {
                    acc[0] -= c;
                } else {
                    acc[1] += c;
                }
            }
            if ((acc[1] - acc[0]) / st->f48 / self->x128 < self->f12C) {
                st->f48 = 0.0f;
            }
            if (st->xA4 < self->x130 && st->bAC) {
                st->f48 = 0.0f;
            }
            st->xA8 = st->xA4;
            self->buf->Restore();
        }
        st->f3C = st->angle;
        break;
    }
    }

    st->timer++;
    if (st->state >= 4) {
        st->x8C++;
        if (st->x50 > 2 && !fn_804E83F4(self)) {
            f32 mx = 0.0f;
            st->f94 = mx;
            st->f90 = mx;
            st->f98 = mx;
            st->f9C = mx;
            for (int i = 0; i < st->x50; i++) {
                f32 m = VEC3Len(&self->Get(i).filtered);
                if (mx < m) mx = m;
            }
            for (int i = 0; i < st->x50; i++) {
                BowVec2 a(self->Get(i).filtered.x, self->Get(i).filtered.z);
                BowVec2 b(self->Get2(i).filtered.x, self->Get2(i).filtered.z);
                f32 c = BowCross(a, b);
                if (c < 0.0f) {
                    st->f90 -= c;
                } else {
                    st->f94 += c;
                }
                if (a.x < 0.0f && -a.x > st->f98) {
                    st->f98 = -a.x;
                }
                if (a.x > 0.0f && a.x > st->f9C) {
                    st->f9C = a.x;
                }
            }
            st->f90 /= mx;
            st->f94 /= mx;
        }
    }

    BowAtan2(self->Get(0).raw.x, -self->Get(0).raw.y);

    if (st->x50 != 0) {
        if (st->x50 >= self->x10C && !st->b01 && !fn_804E83F4(self)) {
            st->f4C = 0.0f;
            st->f84 = 0.0f;
            st->f88 = 0.0f;
            int cnt = self->x10C + self->x108;
            for (int i = 0; i < cnt; i++) {
                bufA[i] = BowAbs(self->Get(i).filtered.x);
                bufB[i] = BowAbs(self->Get(i).filtered.x - self->Get2(i).filtered.x);
            }
            for (int i = 0; i < cnt - 1; i++) {
                for (int j = i + 1; j < cnt; j++) {
                    if (bufA[i] < bufA[j]) {
                        f32 t = bufA[i];
                        bufA[i] = bufA[j];
                        bufA[j] = t;
                    }
                    if (bufB[i] < bufB[j]) {
                        f32 t = bufB[i];
                        bufB[i] = bufB[j];
                        bufB[j] = t;
                    }
                }
            }
            for (int i = 0; i < self->x110; i++) {
                st->f4C += self->fEC * bufA[i] + self->fF0 * bufB[i];
                st->f84 += bufA[i];
                st->f88 += bufB[i];
            }
            st->f4C = st->f4C * (1.0f / self->x110) / st->f48;
            st->b01 = 1;
        }
        st->x50++;
    }

    if (st->b01 && !st->b02 && st->x50 < BowExcel()->x74) {
        int ok = 1;
        for (int i = 0; i < BowExcel()->x98; i++) {
            if (VEC3Len(&self->Get(i).delta) > BowExcel()->f9C) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            f32 rad = BowAtan2(self->Get(0).raw.x, -self->Get(0).raw.y);
            f32 deg = BowRadToDeg(rad);
            f32 len = sqrt(self->Get(0).raw.x * self->Get(0).raw.x + self->Get(0).raw.y * self->Get(0).raw.y);
            st->x04 = 3;
            if (len > BowExcel()->fA8) {
                if (!dir) {
                    deg = -deg;
                }
                if (self->b114 && deg >= BowExcel()->fA4 && deg < BowExcel()->fA0) {
                    st->x04 = 2;
                }
                if (!dir) {
                    if (st->x04 == 0) {
                        st->x04 = 1;
                    } else if (st->x04 == 1) {
                        st->x04 = 0;
                    }
                }
            }
            st->b02 = 1;
        }
    }

    if (st->x50 == BowExcel()->x74 && !st->b02) {
        st->x04 = 3;
        st->b02 = 1;
    }

    st->b54 = flag;
    for (int i = 0; i < BowExcel()->x98; i++) {
        if (VEC3Len(&self->Get(i).delta) > BowExcel()->f9C) {
            break;
        }
    }

    if (self->debug) {
        for (int i = 0; i < 64; i++) {
            BowSwingDebugSample(self->Get(i).raw.x, self->Get(i).raw.y, self->Get(i).raw.z);
        }
    }

    return &self->result;
}

int fn_804E9720(BowSampleBuffer* b, int i) {
    while (i < 0) i += b->capacity;
    while (i >= b->capacity) i -= b->capacity;
    return i;
}

void fn_804E9750(BowSwing2* self, s32 arg) {
    memset(&self->in, 0, 0xB988);
    memset(&self->b0C, 0, 1);
    self->in.bB98C = (arg == 0);
    self->in.state = 0;
    self->in.timer = -1;
}

void fn_804E97C0(BowSwing2* self) {
    fn_804E9750(self, 0);
}

void fn_804E97C8(BowSwing2* self, s32 v) {
    self->in.xB988 = v;
}

void fn_804E97D4(BowSwing2* self, s32 debug) {
    self->debug = debug;
    void* p = operator new(0x1B8);
    if (p) {
        p = fn_804E5C3C(p, 0x200);
    }
    self->buf = (BowSampleBuffer*)p;
    self->in.fB990 = -2.1991131f;
    self->in.fB994 = -0.6f;
    self->in.xB998 = 10;
    self->in.bB98C = 1;
}

f32 fn_804E9840(BowSwing2* self, s32 flag) {
    if (flag) {
        return self->in.f4C4;
    }
    return -self->in.f4C4;
}

void fn_804E985C(void*) {}

void fn_804E9860(void*) {}

}  // extern "C"
