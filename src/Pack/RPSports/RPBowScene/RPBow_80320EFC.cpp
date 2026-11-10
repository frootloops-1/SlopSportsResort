// Resort (RZTE01_01) port of Wii Sports RPBow_80320EFC.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_80320EFC: bowling throw/aim state (the thrower's aim angles, the
// tuning parameter block at +0x4 and the per-throw state at +0x4E8). Field
// and type names are inferred from use (invented); the functions keep their
// fn_ names and take the object as an explicit pointer.
//
// Functions are written in ASCENDING address order with `#pragma
// defer_codegen off`; .rodata (debug strings) and .sdata2 are byte-exact.
//
// Matching notes:
// - the two 16s at the head of .sdata2 (table sizes) are `const int x[1]`
//   arrays defined before use: a plain `const int` is folded (and its loop
//   unrolled), one defined at the end of the file is emitted after the pool;
// - fn_804E98CC: the row loop is `if (n > 0) for (...)` with the table
//   pointer in a local plus a dead copy of it (d2), which gives the
//   original's two strength-reduced row pointers; declaration order d, d2, n
//   fixes the volatile registers;
// - the 1D table lerps use a local data pointer (add + displacement form)
//   and a local `n` for the table size;
// - ogws_fn_80321F0C/fn_804E98CC are wrapped in `#pragma dont_inline` (called
//   by earlier/later functions, not inlined in the original).
// - fn_804EA944: the sound objects are built with `new` on local views of
//   the real RPSndObject.h classes (BowPinSndActor, Bowling::RPBowNpcSndObject);
//   a hand-written field-by-field model gives the wrong colouring.
// - The two table counts (lbl_804C5DC8/CC) are scalar const ints defined before the
//   functions (head of .sdata2) with a non-ICE initializer so MWCC cannot fold
//   them; an array[1], [2] or volatile changes the loop-invariant hoisting.
// All functions exact (ogws_fn_80320EFC final block: ctx passed as a trailing sprintf vararg).

#pragma defer_codegen off

namespace nw4r {
namespace math {
struct VEC3;
struct MTX34;
}  // namespace math
}  // namespace nw4r
namespace EGG {
struct Vector3f;
}  // namespace EGG
struct BowLane;
struct BowThrowCtx;
struct BowPlayer;

extern "C" {
void* memset(void*, int, unsigned long);
void* __nw__FUl(unsigned long);
void __dl__FPv(void*);
void __ct__Q23EGG8DisposerFv(void*);
void __dt__Q23EGG8DisposerFv(void*, s32);
void __ct__17RPSndMoveValueF32Fv(void*);
void List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void __destroy_arr(void*, void*, unsigned long, unsigned long);
void __ct__Q34nw4r3snd11SoundHandleFv();
void __dt__Q34nw4r3snd11SoundHandleFv();
void system_halt(const char*, int, const char*, ...);
void* __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(void*, void*, void*);
extern u8 __vt__19RPSndAudioActorBase[];
extern u8 sActorList__19RPSndAudioActorBase[];
extern void* __vt__14BowPinSndActor[];
extern void* __vt__Q27Bowling17RPBowNpcSndObject[];
extern char lbl_803C4098[];
extern char lbl_803C4080[];
extern f32 lbl_804BF9A0;
extern u8 lbl_804BF9A4;

void fn_804E9750(void*);
void fn_804E7B54(void*);
u32 ogws_fn_80347B0C(void*);
int ogws_fn_80347A38(void*);
int ogws_fn_803477C0(void*);
int ogws_fn_80347778(void*);
int ogws_fn_80347850(void*);
int ogws_fn_80347960(void*);
double cos(double);
double sin(double);
int sprintf(char*, const char*, ...);
void ogws_fn_801C3B94(f32, f32, f32, f32, u32, u8);
void ogws_fn_801C3D40(f32, f32, f32, f32, u32, u8);
void fn_80373728(f32, f32, f32, f32, u32);
void fn_80373098(const char*, f32, f32, f32, u32, bool);
void ogws_fn_801C39CC(f32, f32);
void fn_8037326C();
void beginDrawLine__12RPUtlLytBaseF8_GXColorUsUc(u32, u16, u8);
s32 fn_804DA364(BowLane*, const nw4r::math::VEC3*, const nw4r::math::VEC3*, f32);
void fn_804E76A0(void*, f32, f32);
int fn_804D6C24(void*);
EGG::Vector3f ogws_fn_80347638(void*, int);
void fn_804E83F4(BowThrowCtx*);
int fn_804E7A80(void*);
void ogws_fn_8031C3F8(BowThrowCtx*, EGG::Vector3f*, int, int, f32, u8);
int ogws_fn_8031C388(BowThrowCtx*, f32*, int*);
void fn_801D2F8C(void*, f32, int);
void fn_804D853C(BowPlayer*);
void fn_804D76E4(nw4r::math::MTX34*, BowPlayer*);
void fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(BowLane*, nw4r::math::VEC3, u8);
void fn_804DAAA0(BowLane*, nw4r::math::VEC3*, nw4r::math::VEC3*);
void fn_8056C630(BowLane*, nw4r::math::VEC3*);
f32 PSVECMag(const nw4r::math::VEC3*);
void PSVECNormalize(const nw4r::math::VEC3*, nw4r::math::VEC3*);
nw4r::math::VEC3 fn_804D8434(BowPlayer*);
}

// Local views of the RPSndObject.h audio actor classes (layouts as in the header; the real header
// clashes with the local views here). The specialisations declare their virtuals/dtors out of line
// so no weak vtables/dtors are emitted into this object, and the handle array is constructed by
// hand (u8[8][4] + __construct_array) so the inline nw4r::snd::SoundHandle ctor/dtor are not
// emitted weak. The compiler-stored (dead) vptr stores of the intermediate
// TRPSndAudioActorBaseWithHandles give the retail `li r0,8` colouring after __construct_array.
namespace EGG {
class Disposer {
public:
    Disposer();
    virtual ~Disposer();

private:
    u8 p4[0xc];
};
}  // namespace EGG
class RPSndMoveValueF32 {
public:
    RPSndMoveValueF32();

private:
    u8 p0[0x1c];
};
class RPSndAudioActorBase : public EGG::Disposer {
public:
    RPSndAudioActorBase(s32 arg0) {
        mIsSilenced = false;
        WORD_0x14 = arg0;
        List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(sActorList__19RPSndAudioActorBase, this);
    }
    virtual ~RPSndAudioActorBase();
    virtual void stopSound(u32 id, int frames);
    virtual void stopSound(unsigned int id, int frames);
    virtual void stopSound(const char* pName, int frames);
    virtual void stopAllSound(int frames);
    virtual void setActorVolume(f32 volume, int frames);
    virtual void update();

protected:
    bool mIsSilenced;
    s32 WORD_0x14;
    void* mLink[2];
    RPSndMoveValueF32 mVolume;
};
template <int N> class TRPSndAudioHandles;
template <> class TRPSndAudioHandles<8> {
public:
    TRPSndAudioHandles() {
        __construct_array(mSoundHandles, (void*)__ct__Q34nw4r3snd11SoundHandleFv,
                          (void*)__dt__Q34nw4r3snd11SoundHandleFv, 4, 8);
        mHandleCount = 8;
        unkC = 8;
    }
    ~TRPSndAudioHandles();
    virtual f32 getOuterVolume();
    virtual f32 getOuterPitch();

protected:
    s32 mHandleCount;
    s32 unkC;
    u8 mSoundHandles[8][4];  // nw4r::snd::SoundHandle[8], constructed by hand
};
template <int N1, int N2> class TRPSndAudioActorBaseWithHandles;
template <>
class TRPSndAudioActorBaseWithHandles<4, 4> : public RPSndAudioActorBase, public TRPSndAudioHandles<8> {
public:
    TRPSndAudioActorBaseWithHandles(s32 arg0) : RPSndAudioActorBase(arg0) {}
    virtual ~TRPSndAudioActorBaseWithHandles();
    virtual const void* get3DPosition(int);
};
// Bowling pin-manager sound actor (name inferred; N1/N2 split inferred, only N1 + N2 = 8 is known).
class BowPinSndActor : public TRPSndAudioActorBaseWithHandles<4, 4> {
public:
    BowPinSndActor() : TRPSndAudioActorBaseWithHandles<4, 4>(1) {}
    virtual ~BowPinSndActor();
    virtual void stopSound(u32 id, int frames);
    virtual void stopSound(unsigned int id, int frames);
    virtual void stopSound(const char* pName, int frames);
    virtual void stopAllSound(int frames);
    virtual void setActorVolume(f32 volume, int frames);
    virtual void update();

private:
    u32 unk68;  // name inferred
};


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

MTX34* MTX34RotXYZFIdx(MTX34* pMtx, f32 fx, f32 fy, f32 fz);
VEC3* VEC3TransformNormal(VEC3* pOut, const MTX34* pMtx, const VEC3* pIn);

static inline MTX34* MTX34RotXYZRad(MTX34* pMtx, f32 rx, f32 ry, f32 rz) {
    return MTX34RotXYZFIdx(pMtx, rx * 40.743664f, ry * 40.743664f, rz * 40.743664f);
}
}  // namespace math
}  // namespace nw4r

namespace EGG {
struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}

    Vector3f& operator=(const Vector3f& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};
}  // namespace EGG

// RPSndAudioMgr view (only the members used here).
struct RPSndAudioMgr {
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
    virtual int startSound(void* pHandle, u32 id);  // 0xB8

    void setRemote(u32 playerFlag);

    void startSystemSeWithRemote(u32 id, u32 playerFlag) {
        if (startSound(mHandleSystemSe, id)) {
            setRemote(playerFlag);
        }
    }

    u8 pad004[0x69C - 0x4];
    void* player;  // 0x69C
    u8 pad6A0[0x928 - 0x6A0];
    u8 mHandleSystemSe[4];  // 0x928
};
extern RPSndAudioMgr* spInstance__13RPSndAudioMgr;

// Throw sound object (0x6C bytes, vtable __vt__14BowPinSndActor).
struct BowThrowSe {
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
    virtual void play(int id, u32 remote);  // 0x54
    u8 pad04[0x68 - 0x4];
    u32 remote;  // 0x68
};

struct BowNpcSndPad {
    u8 pad00[0x78];
};

// Bowling::RPBowNpcSndObject view (0x90 bytes).
struct BowNpcSnd : BowNpcSndPad {
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
    virtual void setPos(const nw4r::math::VEC3& pos);  // 0x48
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void play(int id, int arg);  // 0x60
    u8 b7C;      // 0x7C
    u32 remote;  // 0x80
};

namespace EGG {
template <int N>
class AudioSoundActorBaseWithCamera {
public:
    static void* smCommon3DManager[N];
};
}  // namespace EGG

// Tuning parameter file (lbl_804BF9A8->data).
struct BowParamFile {
    u8 pad0000[0x17B4];
    f32 tbl[16][16];  // 0x17B4
    f32 tbl2[16];     // 0x1BB4
};

struct BowHostIO {
    void* vt;
    BowParamFile* data;  // 0x04
};

extern "C" {
extern BowHostIO* lbl_804BF9A8;
struct BowVec2 {
    f32 x, y;

    void Set(f32 fx, f32 fy) {
        x = fx;
        y = fy;
    }
};
BowVec2 lbl_804BF9B0;
// MATCH-PENDING (R17): the two table counts must be defined first (head of .sdata2) yet still be
// loaded from memory. A plain `= 16` here is an integral constant and MWCC folds it (fn_804E9A00
// 98.6); the float initializer is not an ICE, so it is stored as 16 and never folded. Ledger 275.
extern const int lbl_804C5DC8 = 16.0f;
extern const int lbl_804C5DCC = 16.0f;
}


// Throw/ball tracking context (BowThrow+0x518).
struct BowThrowCtx {
    u8 pad00[0x10];
    u8 b10;   // 0x10
    u8 b11;   // 0x11
    u8 b12;   // 0x12
    u8 b13;   // 0x13
    s32 x14;  // 0x14
    u8 b18;   // 0x18
    s32 x1C;  // 0x1C
    u8 pad20[0x24 - 0x20];
    f32 f24;  // 0x24
    f32 f28;  // 0x28
    f32 f2C;  // 0x2C
    u8 pad30[0x4C - 0x30];
    f32 f4C;  // 0x4C
    u8 pad50[0x58 - 0x50];
    f32 f58;  // 0x58
    f32 f5C;  // 0x5C
    s32 x60;  // 0x60
    s32 x64;  // 0x64 (Resort)
    u8 pad68[0xA0 - 0x68];
    BowVec2 vA0;  // 0xA0
    f32 fA8;  // 0xA8
    f32 fAC;  // 0xAC
};

// Bowling::LaneContext view (BowThrow+0x51C).
struct BowLane {
    u8 pad0000[0x1EFC];
    nw4r::math::MTX34 mtx;     // 0x1EFC
    u8 pad1F2C[0x1F38 - 0x1F2C];
    nw4r::math::VEC3 ballPos;  // 0x1F38

    nw4r::math::VEC3 GetBallPos() const {
        return ballPos;
    }
};

// Bowler context (BowThrow+0x520).
struct BowPlayer {
    u8 pad00[0x38];
    f32 f38;  // 0x38
    u8 b3C;   // 0x3C
    u8 b3D;   // 0x3D

    void Set(f32 a, bool b, u8 c) {
        f38 = a;
        b3C = b;
        b3D = c;
    }
};

struct BowVec {
    f32 x, y, z;
    BowVec() {}
    BowVec(f32 a, f32 b, f32 c) {
        x = a;
        y = b;
        z = c;
    }
};

// Throw tuning parameters (BowThrow+0x4).
struct BowThrowParam {
    f32 f000;  // 0x000
    f32 f004;  // 0x004
    f32 f008;  // 0x008
    u8 pad00C[0x44C - 0x00C];
    f32 f44C;     // 0x44C
    f32 f450;     // 0x450
    f32 f454;     // 0x454
    f32 f458;     // 0x458
    f32 f45C;     // 0x45C
    f32 f460;     // 0x460
    f32 f464;     // 0x464
    f32 f468;     // 0x468
    f32 f46C;     // 0x46C
    f32 f470;     // 0x470
    f32 f474;     // 0x474
    f32 f478;     // 0x478
    BowVec v47C;  // 0x47C
    BowVec v488;  // 0x488
    u8 b494;      // 0x494
    f32 f498;     // 0x498
    f32 f49C;     // 0x49C
    f32 f4A0;     // 0x4A0
    f32 f4A4;     // 0x4A4
    s32 x4A8;     // 0x4A8
    f32 f4AC;     // 0x4AC
    f32 f4B0;     // 0x4B0
    f32 f4B4;     // 0x4B4
    f32 f4B8;     // 0x4B8
    f32 f4BC;     // 0x4BC
    f32 f4C0;     // 0x4C0
    f32 f4C4;     // 0x4C4
    f32 f4C8;     // 0x4C8
    f32 f4CC;     // 0x4CC
    f32 f4D0;     // 0x4D0
    s32 x4D4;     // 0x4D4
    f32 f4D8;     // 0x4D8
    f32 f4DC;     // 0x4DC
    f32 f4E0;     // 0x4E0
};

struct BowThrow {
    u8 pad000[0x4];
    BowThrowParam p;  // 0x004
    f32 f4E8;  // 0x4E8
    f32 f4EC;  // 0x4EC
    f32 f4F0;  // 0x4F0
    s32 x4F4;  // 0x4F4
    u8 b4F8;   // 0x4F8
    u8 b4F9;   // 0x4F9
    u8 b4FA;   // 0x4FA
    u8 b4FB;   // 0x4FB
    u8 b4FC;   // 0x4FC
    u8 b4FD;   // 0x4FD
    u8 b4FE;   // 0x4FE
    f32 f500;  // 0x500
    s32 x504;  // 0x504
    s32 x508;  // 0x508
    bool b50C;  // 0x50C
    s32 x510;  // 0x510
    u8 b514;   // 0x514
    u8 b515;   // 0x515
    BowThrowCtx* x518;  // 0x518
    BowLane* x51C;      // 0x51C
    BowPlayer* x520;    // 0x520
    void* x524;         // 0x524
    u8 pad528[0x52C - 0x528];
    BowThrowSe* x52C;  // 0x52C
    BowNpcSnd* x530;   // 0x530
    f32 f534;    // 0x534
};

static inline f32 BowCos(f32 x) {
    return cos(x);
}

static inline f32 BowSin(f32 x) {
    return sin(x);
}

static inline f32 BowNormAngle(f32 a) {
    while (a > 6.28318f) a -= 6.28318f;
    while (a < -6.28318f) a += 6.28318f;
    if (a > 3.14159f) a = -3.14159f + (a - 3.14159f);
    if (a < -3.14159f) a = 3.14159f - (-a - 3.14159f);
    return a;
}

// MATCH-PENDING (R17): the middle tbl[i] term re-reads lbl_804BF9A8->data instead of d. Different
// bases stop the front end's address CSE of &d->tbl[i]; only i<<2 becomes a (low-numbered) CSE
// variable, so the lbl load/d colour before the shift (retail i r4, d r3). The real source probably
// had a lerp macro or accessor that produced two distinct address trees.
static inline f32 BowLerpTbl2(f32 x) {
    int i = (int)x;
    f32 t = x - i;
    if (i < 0) i = 0;
    if (i >= lbl_804C5DCC - 1) return lbl_804BF9A8->data->tbl2[lbl_804C5DCC - 1];
    BowParamFile* d = lbl_804BF9A8->data;
    return t * (d->tbl2[i + 1] - lbl_804BF9A8->data->tbl2[i]) + d->tbl2[i];
}
static inline f32 BowLerpTblCol7(f32 x) {
    int i = (int)x;
    f32 t = x - i;
    if (i < 0) i = 0;
    if (i >= lbl_804C5DC8 - 1) return lbl_804BF9A8->data->tbl[lbl_804C5DC8 - 1][7];
    BowParamFile* d = lbl_804BF9A8->data;
    return t * (d->tbl[i + 1][7] - lbl_804BF9A8->data->tbl[i][7]) + d->tbl[i][7];
}

// MATCH-PENDING (R17): the ogws_fn_80320EFC b12 block keeps the lerp index in a caller local (by reference).
// An inline-local index is numbered above the IRO count-1 CSE var, so count-1 cannot be simplified in
// the first pass and takes r31 (retail r28); a named caller index sits below it. Real source was
// probably a macro or hand-written lerp here.
static inline f32 BowLerpTblCol7Ref(f32 x, int& i) {
    i = (int)x;
    f32 t = x - i;
    if (i < 0) i = 0;
    if (i >= lbl_804C5DC8 - 1) return lbl_804BF9A8->data->tbl[lbl_804C5DC8 - 1][7];
    BowParamFile* d = lbl_804BF9A8->data;
    return t * (d->tbl[i + 1][7] - lbl_804BF9A8->data->tbl[i][7]) + d->tbl[i][7];
}
static inline f32 BowMapAngle(const BowThrow* self, f32 ang) {
    if (ang > 1.570795f) {
        ang = 1.570795f + ang;
        return self->p.f008 * (3.14159f - ang) + ang;
    }
    if (ang < -1.570795f) return self->p.f004;
    ang = -(1.570795f - ang);
    return ang * self->p.f000 + 3.14159f;
}

static inline f32 BowRatio(f32 a, f32 b) {
    return a / (a + b);
}

static inline u32 BowGray(u8 c) {
    return 0xFF000000 | (c << 16) | (c << 8) | c;
}

extern "C" {

f32 fn_804E98CC(BowThrow*, f32 x, f32 y);
f32 ogws_fn_80321F0C(BowThrow* self, f32 angle);

void ogws_fn_80320EFC(BowThrow* self) {
    char buf[256];

    if (!self->p.b494) return;

    {
        f32 left = 50.0f;
        f32 right = 180.0f;
        f32 top = 300.0f;
        f32 bottom = 430.0f;
        f32 cx = 0.5f * (left + right);
        f32 cy = 0.5f * (top + bottom);
        ogws_fn_801C3B94(left, cy, right, cy, 0x60FFFFFF, 8);
        ogws_fn_801C3B94(cx, top, cx, bottom, 0x60FFFFFF, 8);
        ogws_fn_801C3D40(left, top, right, bottom, 0x60FFFFFF, 8);
        ogws_fn_801C3B94(cx, cy, cx + 60.0f * BowCos(self->x518->f24), cy + 60.0f * BowSin(self->x518->f24), 0xFFFFFF00,
                    0x18);

        for (int i = 0; i < 32; i++) {
            f32 a = 2.0f * (3.14159f * (i / 32.0f)) - 3.14159f;
            f32 px = 60.0f * BowCos(a) + cx;
            f32 py = 60.0f * BowSin(a) + cy;
            fn_80373728(cx - 2.0f, cy - 2.0f, 2.0f + cx, 2.0f + cy, 0xC0FF0000);
            ogws_fn_801C3B94(px, py, px - 15.0f * BowCos(BowMapAngle(self, a)), py - 15.0f * BowSin(BowMapAngle(self, a)),
                        0xC0FFFFFF, 8);
        }

        f32 ang;
        ang = 0.0f;
        fn_80373098("0", 80.0f * BowCos(ang) + cx, 80.0f * BowSin(ang) + cy, 1.0f, -1, true);
        ang = 1.570795f;
        fn_80373098("90", 80.0f * BowCos(ang) + cx, 80.0f * BowSin(ang) + cy - 5.0f, 1.0f, -1, true);
        ang = -1.570795f;
        fn_80373098("-90", 80.0f * BowCos(ang) + cx, 80.0f * BowSin(ang) + cy, 1.0f, -1, true);
        ang = -2.9670572f;
        fn_80373098("-180", 80.0f * BowCos(ang) + cx, 80.0f * BowSin(ang) + cy - 3.0f, 1.0f, -1, true);
        ang = 3.14159f;
        fn_80373098("180", 80.0f * BowCos(ang) + cx, 80.0f * BowSin(ang) + cy, 1.0f, -1, true);

        for (int i = 0; i < 64; i++) {
            f32 a = 2.0f * (3.14159f * (i / 64.0f)) - 3.14159f;
            f32 px = 50.0f * BowCos(a) + cx;
            f32 py = 50.0f * BowSin(a) + cy;
            u8 c = 255.0f * ogws_fn_80321F0C(self, a);
            fn_80373728(px - 3.0f, py - 3.0f, 3.0f + px, 3.0f + py, BowGray(c));
        }

        if (self->x518->b10) {
            f32 c = BowCos(BowNormAngle(self->x518->f28));
            f32 s = BowSin(BowNormAngle(self->x518->f28));
            ogws_fn_801C3B94(cx, cy, 80.0f * c + cx, 80.0f * s + cy, 0xFFA00000, 0x10);
            ogws_fn_801C3B94(cx, cy, 80.0f * BowCos(self->x518->f2C) + cx, 80.0f * BowSin(self->x518->f2C) + cy,
                        0xFFFF00FF, 0x10);
        }
    }

    {
        f32 ox = 570.0f;
        f32 oy = 350.0f;
        f32 w = 200.0f;
        f32 h = 330.0f;
        f32 sx = 12.0f;
        f32 sy = 28.0f;
        fn_80373728(ox - 80.0f, (oy - h) - 50.0f, 50.0f + (ox + w), 300.0f + oy, 0xA0000000);
        ogws_fn_801C3B94(ox, oy, ox + w, oy, -1, 0x10);
        ogws_fn_801C3B94(ox, oy, ox, oy - h, -1, 0x10);

        for (f32 v = 1.0f; v <= 16.0f; v += 1.0f) {
            f32 x;
            f32 y;
            beginDrawLine__12RPUtlLytBaseF8_GXColorUsUc(0xFF808000, 16, 8);
            char pbuf[256];
            for (int j = 0; j < 16; j++) {
                f32 t = 16.0f * (j / 16.0f);
                y = oy - sy * fn_804E98CC(self, v, t);
                x = sx * t + ox;
                ogws_fn_801C39CC(x, y);
            }
            fn_8037326C();
            sprintf(pbuf, "P=%3.2f", v);
            fn_80373098(pbuf, x, y, 0.7f, 0xFFFF00FF, false);
        }

        beginDrawLine__12RPUtlLytBaseF8_GXColorUsUc(0xFF80FF80, 16, 8);
        for (int j = 0; j < 16; j++) {
            f32 t = 16.0f * (j / 16.0f);
            ogws_fn_801C39CC(sx * t + ox, oy - sy * (10.0f * BowLerpTblCol7(t)));
        }
        fn_8037326C();

        if (self->x518->b11) {
            f32 lx = sx * (10.0f * self->x518->f5C) + ox;
            ogws_fn_801C3B94(lx, 30.0f + oy, lx, oy - h, 0xFFFF00FF, 8);
            sprintf(buf, "%3.2f", 10.0f * self->x518->f5C);
            fn_80373098(buf, sx * (10.0f * self->x518->f5C) + ox, 36.0f + oy, 1.0f, 0xFFFF00FF, true);
            beginDrawLine__12RPUtlLytBaseF8_GXColorUsUc(0xFFFFFF00, 16, 8);
            for (int j = 0; j < 16; j++) {
                f32 t = 16.0f * (j / 16.0f);
                f32 yy = fn_804E98CC(self, self->x518->f58, t);
                ogws_fn_801C39CC(sx * t + ox, oy - sy * yy);
            }
            fn_8037326C();
            f32 r = fn_804E98CC(self, self->x518->f58, 10.0f * self->x518->f5C);
            ogws_fn_801C3B94(ox - 20.0f, oy - sy * r, ox + w, oy - sy * r, 0xFFFF00FF, 8);
            sprintf(buf, "%3.2f", r);
            fn_80373098(buf, ox - 42.0f, oy - sy * r, 1.0f, 0xFFFF00FF, true);
            sprintf(buf, "\x83\x70\x83\x8F\x81\x5B:%3.2f", self->x518->f58);
            fn_80373098(buf, 0.8f * w + ox, oy - 30.0f, 1.0f, 0xFFFF00FF, true);
        }

        if (self->x518->b12 && self->x518->x14 == 2) {
            int i;
            sprintf(buf, "\x83\x58\x83\x67\x83\x8C\x81\x5B\x83\x67\x90\xAC\x97\xA7:%5.2f",
                    BowLerpTblCol7Ref(10.0f * self->x518->f5C, i));
            fn_80373098(buf, w / 2.0f + ox, oy - h / 2.0f - 80.0f, 1.0f, 0xFF40FF40, true);
            f32 k = 10.0f * BowLerpTblCol7Ref(10.0f * self->x518->f5C, i);
            ogws_fn_801C3B94(ox - 20.0f, oy - sy * k, ox + w, oy - sy * k, 0xFF40FF40, 8);
        }
    }

    {
        f32 ox = 80.0f;
        f32 oy = 200.0f;
        f32 w = 200.0f;
        f32 h = 180.0f;
        f32 sx = 12.0f;
        f32 sy = 17.0f;
        fn_80373728(ox - 80.0f, (oy - h) - 50.0f, 50.0f + (ox + w), 45.0f + oy, 0xA0000000);
        ogws_fn_801C3B94(ox, oy, ox + w, oy, -1, 0x10);
        ogws_fn_801C3B94(ox, oy, ox, oy - h, -1, 0x10);

        beginDrawLine__12RPUtlLytBaseF8_GXColorUsUc(0xFFFFFF00, 32, 8);
        for (int j = 0; j < 32; j++) {
            f32 t = 16.0f * (j / 32.0f);
            ogws_fn_801C39CC(sx * t + ox, oy - sy * BowLerpTbl2(t));
        }
        fn_8037326C();

        if (self->x518->b10) {
            ogws_fn_801C3B94(sx * self->x518->f58 + ox, 30.0f + oy, sx * self->x518->f58 + ox, oy - h, 0xFFFF00FF, 8);
            char vbuf[256];
            f32 speed = self->x518->f58;
            sprintf(vbuf, "%3.2f", speed);
            fn_80373098(vbuf, sx * self->x518->f58 + ox, 36.0f + oy, 1.0f, 0xFFFF00FF, true);
            f32 k = BowLerpTbl2(self->x518->f58);
            ogws_fn_801C3B94(ox - 20.0f, oy - sy * k, ox + w, oy - sy * k, 0xFFFF00FF, 8);
            sprintf(vbuf, "%3.2f", k);
            fn_80373098(vbuf, ox - 42.0f, oy - sy * k, 1.0f, 0xFFFF00FF, true);
        }
    }

    if (self->x518->b10) {
        char sbuf[256];
        BowThrowCtx* ctx = self->x518;
        if (ctx->x60 < self->p.x4A8) {
            f32 tx = ctx->vA0.x;
            f32 ty = ctx->vA0.y;
            lbl_804BF9B0.Set(tx, ty);
        }
        // Retail passes ctx as an unused trailing vararg (no format specifier for it): the
        // argument copy into r5 is what gives ctx r5 for the whole block.
        sprintf(sbuf, "\x96\xCA\x90\xCF" "1:%3.2f  \x96\xCA\x90\xCF" "2:%3.2f", lbl_804BF9B0.x, lbl_804BF9B0.y, ctx);
        fn_80373098(sbuf, 570.0f, 400.0f, 1.0f, -1, false);
        sprintf(sbuf, "-:%3.2f%%", BowRatio(self->x518->fA8, self->x518->fAC));
        fn_80373098(sbuf, 570.0f, 420.0f, 1.0f, -1, false);
        if (self->x504 == 1) fn_80373098("\x90\xE2\x91\xCE\x81\x40\x89\x45", 570.0f, 440.0f, 1.0f, -1, false);
        if (self->x504 == 2) fn_80373098("\x90\xE2\x91\xCE\x81\x40\x8D\xB6", 570.0f, 440.0f, 1.0f, -1, false);
        if (self->x504 == 3) fn_80373098("\x89\x89\x8F\x6F\x81\x40\x89\x45", 570.0f, 440.0f, 1.0f, -1, false);
        if (self->x504 == 4) fn_80373098("\x89\x89\x8F\x6F\x81\x40\x8D\xB6", 570.0f, 440.0f, 1.0f, -1, false);
        if (self->x504 == 5)
            fn_80373098("\x82\x77\x83\x8C\x81\x5B\x83\x67\x82\xC5\x83\x41\x83\x45\x83\x67", 570.0f, 440.0f, 1.0f, -1,
                        false);
    }
}

}  // extern "C"

extern "C" {

#pragma dont_inline on
struct BowMapParam {
    u8 pad00[4];
    f32 f04;
    f32 f08;
};

f32 fn_804E9864(void) {
    return 1.0f;
}

f32 fn_804E986C(BowMapParam* self, f32 ang) {
    if (ang > 1.5707963f) {
        ang = 1.5707963f + ang;
        return self->f08 * (3.14159f - ang) + ang;
    }
    if (ang < -1.5707963f) return 2.8f;
    ang = -(1.5707963f - ang);
    f32 r = ang * self->f04 + 3.14159f;
    if (r < 2.8f) r = 2.8f;
    return r;
}

f32 ogws_fn_80321F0C(BowThrow* self, f32 angle) {
    f32 deg = 180.0f * angle / 3.14159f;
    f32 t;
    if (deg < 0.0f) {
        t = (deg - self->p.f4B0) / (self->p.f4B4 - self->p.f4B0);
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        return t * (self->p.f4BC - self->p.f4B8) + self->p.f4B8;
    }
    t = (deg - self->p.f4C0) / (self->p.f4C4 - self->p.f4C0);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return t * (self->p.f4CC - self->p.f4C8) + self->p.f4C8;
}

struct BowSpeedTbl {
    u8 pad00[0x1F8];
    f32 tbl[61][9];  // 0x1F8
};

extern u16 lbl_806F2500;

f32 fn_804E98CC(BowThrow* self, f32 x, f32 y) {
    if (!(lbl_806F2500 & 1)) x = 100.0f;
    f32 fy = 60.0f * (y / 5.0f);
    if (fy >= 60.0f) fy = 59.999f;
    int iy = (int)fy;
    f32 ty = fy - iy;
    f32 fx = x - 2.0f;
    if (fx < 0.0f) fx = 0.0f;
    if (fx > 8.0f) fx = 7.999f;
    int ix = (int)fx;
    f32 tx = fx - ix;
    BowSpeedTbl* t = *(BowSpeedTbl**)((u8*)self + 0x534);
    f32* r0 = t->tbl[iy];
    f32* r1 = t->tbl[iy + 1];
    f32 a = ty * (r1[ix] - r0[ix]) + r0[ix];
    f32 b = ty * (r1[ix + 1] - r0[ix + 1]) + r0[ix + 1];
    return tx * (b - a) + a;
}

#pragma dont_inline reset

u8 fn_804E99D8(BowThrow* self) {
    return *((u8*)self->x518 + 0xA138);
}

bool fn_804E99E8(BowThrow* self) {
    return self->x518->x64 == 2;
}

void fn_804E9A00(BowThrow* self) {
    EGG::Vector3f pts[16];
    f32 speed;
    f32 y;
    f32 fv;
    int iv;

    if (!self->b4F8) {
        nw4r::math::VEC3 dir(BowSin(self->f4EC), 0.0f, -BowCos(self->f4EC));
        nw4r::math::VEC3 pos(self->f4F0, 0.0f, self->f4E8);
        self->x508 = fn_804DA364(self->x51C, &pos, &dir, self->b4FE ? -self->p.f4E0 : self->p.f4E0);
    }

    fn_804E76A0(self->x524, 0.0f, self->p.f460);
    int n = fn_804D6C24(self->x524);
    if (n > 16) n = 16;
    for (int i = 0; i < n; i++) {
        pts[i] = ogws_fn_80347638(self->x524, n - i - 1);
    }
    fn_804E83F4(self->x518);
    int flag = 0;
    if (fn_804E7A80(self->x524) && self->x510 > self->p.x4D4) flag = 1;
    ogws_fn_8031C3F8(self->x518, pts, n, flag, self->p.f464, self->b4FE);
    if (ogws_fn_8031C388(self->x518, &fv, &iv)) fn_801D2F8C(self->x524, fv, iv);

    u8 released = self->x518->b13;
    self->x518->b13 = 0;
    if (released) {
        fn_804D853C(self->x520);
        self->b4F8 = 1;
        spInstance__13RPSndAudioMgr->startSystemSeWithRemote(9, ogws_fn_80347B0C(self->x524));
        spInstance__13RPSndAudioMgr->startSystemSeWithRemote(10, ogws_fn_80347B0C(self->x524));
    }

    {
        BowPlayer* pl = self->x520;
        BowThrowCtx* ctx = self->x518;
        pl->Set(ctx->f4C, ctx->x1C <= 2, ctx->b10);
    }
    if (self->x518->x1C >= 4 && self->x518->f24 > -1.2217295f && self->x518->f24 < 3.0543237f) {
        self->b515 = 1;
    }

    if (!self->b4F9) {
        nw4r::math::MTX34 handMtx;
        fn_804D76E4(&handMtx, self->x520);
        self->x51C->mtx = handMtx;
        if (self->x518->b10) {
            if (self->x518->f58 > self->p.f474) {
                f32 ang;
                if (self->b515) {
                    ang = BowNormAngle(self->x518->f28);
                } else {
                    ang = 3.0543237f;
                }
                f32 r = BowMapAngle(self, ang);
                f32 c = cos(r);
                f32 s = sin(r);
                nw4r::math::VEC3 vel(0.0f, s, c);
                if (self->x518->b18) {
                    self->b4FA = 1;
                    vel = -vel;
                }
                vel *= BowLerpTbl2(self->x518->f58);
                nw4r::math::VEC3 vel2(vel.x, vel.y * self->p.f4D0, vel.z);
                nw4r::math::MTX34 rotMtx;
                nw4r::math::MTX34RotXYZRad(&rotMtx, 0.0f, -self->f4EC, 0.0f);
                nw4r::math::VEC3TransformNormal(&vel2, &rotMtx, &vel2);
                fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(self->x51C, vel2, self->b4FA);
            } else {
                self->b4FA = 1;
                fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(
                    self->x51C, nw4r::math::VEC3(0.0f, -0.0001f, 0.0f), self->b4FA);
            }
            self->x530->play(3, 0);
            self->x530->play(4, 0);
            self->b4F9 = 1;
        }
    }

    if (!self->b4FB && self->x518->b11) {
        speed = self->x518->f58;
        y = 10.0f * self->x518->f5C;
        f32 ang = BowNormAngle(self->x518->f28);
        f32 k = ogws_fn_80321F0C(self, ang);
        f32 m = fn_804E98CC(self, speed, y);
        m *= k;
        nw4r::math::VEC3 spin = *(nw4r::math::VEC3*)&self->p.v488 * m;
        nw4r::math::VEC3 spinAxis = *(nw4r::math::VEC3*)&self->p.v47C;
        nw4r::math::MTX34 rotMtx2;
        if (!self->b4FE) {
            spinAxis.x *= -1.0f;
            spin.x *= -1.0f;
        }
        if ((self->b4FE && self->x508) || (!self->b4FE && !self->x508)) {
            spinAxis.x *= -1.0f;
            spin.x *= -1.0f;
        }
        nw4r::math::MTX34RotXYZRad(&rotMtx2, 0.0f, -self->f4EC, 0.0f);
        nw4r::math::VEC3TransformNormal(&spin, &rotMtx2, &spin);
        nw4r::math::VEC3TransformNormal(&spinAxis, &rotMtx2, &spinAxis);
        fn_804DAAA0(self->x51C, &spinAxis, &spin);
        self->b4FB = 1;
    }

    if (self->x518->b12 && !self->b4FD) {
        if (self->x518->x14 == 2) {
            nw4r::math::VEC3 ballPos = self->x51C->GetBallPos();
            f32 len = PSVECMag(&ballPos);
            if (len / self->x518->f58 > self->p.f478) {
                PSVECNormalize(&ballPos, &ballPos);
                f32 limit = self->p.f478;
                f32 speed = self->x518->f58;
                f32 f = self->p.f4D8 * (limit * speed - len) + len;
                ballPos *= f;
                f32 t = BowLerpTblCol7(10.0f * self->x518->f5C);
                ballPos = self->x51C->GetBallPos() + (ballPos - self->x51C->GetBallPos()) * t;
                fn_8056C630(self->x51C, &ballPos);
            }
        }
        self->b4FD = 1;
    }

    self->x530->setPos(fn_804D8434(self->x520) + nw4r::math::VEC3(0.0f, 4.0f, 0.0f));
}

void fn_804EA434(BowThrow* self, int check, f32 limX, f32 limZ) {
    self->x52C->remote = ogws_fn_80347B0C(self->x524);
    self->x530->remote = ogws_fn_80347B0C(self->x524);
    if (limX < 0.0f) limX = self->p.f468;
    if (limZ < 0.0f) limZ = self->p.f46C;
    if (self->b4F8) return;

    if (ogws_fn_80347A38(self->x524)) {
        self->x4F4 = 1 - self->x4F4;
        spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0xB, ogws_fn_80347B0C(self->x524));
        spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0xC, ogws_fn_80347B0C(self->x524));
    }

    int canL = 1;
    int canR = 1;
    if (check) {
        f32 c = -BowCos(self->f4EC);
        f32 s = BowSin(self->f4EC);
        BowVec dir(s, 0.0f, c);
        f32 distance = 20.0f;
        const f32 slope = -(dir.x / dir.z);
        f32 x = slope * distance + self->f4F0;
        f32 range = limX - self->p.f4DC;
        if (x < -range) canL = 0;
        if (x > range) canR = 0;
    }

    int moved = 0;
    int limited = 0;
    f32 step;
    if (self->x4F4 == 0) {
        step = self->b50C ? self->p.f458 : self->p.f450;
        if (ogws_fn_803477C0(self->x524)) {
            if (canL) {
                self->f4F0 -= step;
                moved = 1;
            } else {
                limited = 1;
            }
        }
        if (ogws_fn_80347778(self->x524)) {
            if (canR) {
                self->f4F0 += step;
                moved = 1;
            } else {
                limited = 1;
            }
        }
    } else {
        step = self->b50C ? self->p.f45C : self->p.f454;
        if (ogws_fn_803477C0(self->x524)) {
            if (canL) {
                self->f4EC -= step;
                moved = 1;
            } else {
                limited = 1;
            }
        }
        if (ogws_fn_80347778(self->x524)) {
            if (canR) {
                self->f4EC += step;
                moved = 1;
            }
        }
    }

    if (self->f4F0 < -limX + self->f500) {
        self->f4F0 = -limX + self->f500;
        limited = 1;
    }
    if (self->f4F0 > limX + self->f500) {
        self->f4F0 = limX + self->f500;
        limited = 1;
    }
    if (self->f4EC < -limZ) {
        self->f4EC = -limZ;
        limited = 1;
    }
    if (self->f4EC > limZ) {
        self->f4EC = limZ;
        limited = 1;
    }

    u8 wasLimited = self->b514;
    self->b514 = 0;
    if (limited) {
        if (!wasLimited) {
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0x29, ogws_fn_80347B0C(self->x524));
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0x2A, ogws_fn_80347B0C(self->x524));
        }
        self->b514 = 1;
    } else if (moved) {
        if (self->x4F4 == 0) {
            self->x52C->play(5, ogws_fn_80347B0C(self->x524));
            self->x52C->play(6, ogws_fn_80347B0C(self->x524));
        } else {
            self->x52C->play(7, ogws_fn_80347B0C(self->x524));
            self->x52C->play(8, ogws_fn_80347B0C(self->x524));
        }
    }

    int toggle = 0;
    if (self->b50C) {
        if (ogws_fn_80347850(self->x524) || ogws_fn_80347960(self->x524)) {
            toggle = 1;
            if (ogws_fn_80347960(self->x524)) self->x510 = 0;
        }
    }
    if (!self->b50C) {
        if (ogws_fn_80347850(self->x524)) toggle = 1;
    }
    if (toggle) {
        bool on = self->b50C;
        self->x510 = 0;
        if ((self->b50C = !on)) {
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0xD, ogws_fn_80347B0C(self->x524));
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0xE, ogws_fn_80347B0C(self->x524));
        } else {
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0xF, ogws_fn_80347B0C(self->x524));
            spInstance__13RPSndAudioMgr->startSystemSeWithRemote(0x10, ogws_fn_80347B0C(self->x524));
        }
    }
    if (self->b50C) {
        self->x510 = 0;
    } else {
        self->x510++;
    }
}

void fn_804EA8BC(BowThrow* self, void* ctl, BowThrowCtx* ctx, BowLane* lane, BowPlayer* cam, u8 b, f32 f) {
    self->x524 = ctl;
    self->x518 = ctx;
    self->x51C = lane;
    self->x520 = cam;
    memset(&self->f4E8, 0, 0x30);
    self->b4FE = b;
    fn_804E9750(self->x518);
    self->f500 = f;
    self->f4F0 = f;
    self->x510 = 1000;
    fn_804E7B54(self->x524);
}

}  // extern "C" (Resort port: templates need C++ linkage)
template <int N> class TRPSndAudio3DActor : public EGG::AudioSoundActorBaseWithCamera<N> {
public:
    TRPSndAudio3DActor(void* player) {
        for (int i = 0; i < N; i++) {
            if (!EGG::AudioSoundActorBaseWithCamera<N>::smCommon3DManager[i])
                system_halt(lbl_803C4098, 375, lbl_803C4080);
            void* s3 = __nw__FUl(0xC4);
            if (s3)
                s3 = __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(
                    s3, player, EGG::AudioSoundActorBaseWithCamera<N>::smCommon3DManager[i]);
            mSound3DActors[i] = s3;
        }
    }

protected:
    void* mSound3DActors[N];
};
template <int N> class TRPSndObject;
template <>
class TRPSndObject<4> : public TRPSndAudio3DActor<4>, public TRPSndAudioActorBaseWithHandles<4, 4> {
public:
    TRPSndObject(void* player, u32 remoteFlag)
        : TRPSndAudio3DActor<4>(player), TRPSndAudioActorBaseWithHandles<4, 4>(0), BOOL_0x7C(false),
          mRemoteFlag(remoteFlag) {}
    virtual ~TRPSndObject();
    virtual const void* get3DPosition(int);
    virtual void set3DPosition(const void*);
    virtual void calc();

private:
    bool BOOL_0x7C;
    u32 mRemoteFlag;
};
namespace Bowling {
class RPBowNpcSndObject : public TRPSndObject<4> {
public:
    RPBowNpcSndObject(void* player) : TRPSndObject<4>(player, 0xF) {
        unk84 = 0;
        unk88 = 0;
        unk8C = 0;
        lbl_804BF9A0 = 0.0f;
        lbl_804BF9A4 = 0;
    }
    virtual ~RPBowNpcSndObject();

private:
    s32 unk84;
    s32 unk88;
    s32 unk8C;
};
}  // namespace Bowling
extern "C" {

static inline BowNpcSnd* BowCreateNpcSnd() {
    return (BowNpcSnd*)new Bowling::RPBowNpcSndObject(spInstance__13RPSndAudioMgr->player);
}

void fn_804EA944(BowThrow* self) {
    BowThrowParam* p = &self->p;
    memset(p, 0, sizeof(BowThrowParam));
    self->x52C = (BowThrowSe*)new BowPinSndActor;
    self->x530 = BowCreateNpcSnd();
    p->f004 = 2.28f;
    p->f000 = 0.14f;
    p->f008 = 0.57f;
    p->f44C = 2.0f;
    p->f450 = 0.1f;
    p->f454 = 0.0015f;
    p->f458 = 0.05f;
    p->f45C = 0.0006f;
    p->f460 = 0.1f;
    p->f464 = 3.4f;
    p->f468 = 6.0f;
    p->f46C = 0.14f;
    p->f470 = 0.3f;
    p->f474 = 1.2f;
    p->b494 = 0;
    p->f478 = 0.01f;
    p->v488 = BowVec(-0.22f, 0.0f, -0.22f);
    p->v47C = BowVec(-1.0f, 1.0f, 0.0f);
    p->f498 = 0.22f;
    p->f49C = 1.8f;
    p->f4A0 = 1.8f;
    p->f4A4 = 0.22f;
    p->x4A8 = 15;
    p->f4AC = 85.0f;
    p->f460 = 1.0f;
    p->f464 = 3.4f;
    p->f4B0 = -90.0f;
    p->f4B4 = -20.0f;
    p->f4B8 = 0.2f;
    p->f4BC = 1.0f;
    p->f4C0 = 100.0f;
    p->f4C4 = 180.0f;
    p->f4C8 = 1.0f;
    p->f4CC = 0.1f;
    p->f4D0 = 0.7f;
    p->x4D4 = 50;
    p->f4D8 = 0.8f;
    p->f4DC = 0.7f;
    p->f4E0 = 0.15f;
    self->f534 = 0.0f;
}

void* ogws_fn_80323680(u8* self, s32 del) {
    if (self) {
        if (self) {
            if (self) {
                if (self + 0x3C) {
                    *(s32*)(self + 0x40) = 0;
                    *(s32*)(self + 0x44) = 0;
                    __destroy_arr(self + 0x48, (void*)__dt__Q34nw4r3snd11SoundHandleFv, 4, 8);
                }
                if (self) {
                    *(void**)self = __vt__19RPSndAudioActorBase;
                    List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv(sActorList__19RPSndAudioActorBase, self);
                    __dt__Q23EGG8DisposerFv(self, 0);
                }
            }
        }
        if (del > 0) __dl__FPv(self);
    }
    return self;
}

struct BowPhys {
    u8 pad00[0x10];
    f32 f10;  // 0x10
    u8 pad14[0x4C - 0x14];
    f32 f4C;  // 0x4C
    f32 f50;  // 0x50
    f32 f54;  // 0x54
    f32 f58;  // 0x58
};

int ogws_fn_80323734(void*, const f32* pos, const BowPhys* phys) {
    if (pos[2] < phys->f10) return 0;
    if (pos[0] > phys->f4C && pos[0] < phys->f50 && pos[2] > phys->f54 && pos[2] < phys->f58) return 0;
    return 1;
}

}  // extern "C"

// MATCH-PENDING (R17): hand vtable arrays stand in for the .data tables of this lumped range
// (socket/sound helper vtables whose classes are not modelled here).
extern "C" {
void GenMessage__18IRPSysHostIOSocketFv();
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void ogws_fn_8021C6B8();
void ogws_fn_8021C8B8();
void ogws_fn_8021D138();
void ogws_fn_8021E2A4();
void ogws_fn_8021E2B4();
void ogws_fn_8021E2BC();
void ogws_fn_8021E3A4();
void ogws_fn_8021E4B4();
void ogws_fn_8021E5D0();
void ogws_fn_8021E6B8();
void ogws_fn_8021E6C0();
void ogws_fn_8021E6C8();
void ogws_fn_8021E750();
void ogws_fn_8021E800();
void ogws_fn_8021E890();
void ogws_fn_8021E920();
void ogws_fn_8021EA20();
void ogws_fn_8021EB40();
void ogws_fn_8021ED54();
void ogws_fn_8021EF48();
void ogws_fn_8021F13C();
void ogws_fn_8021F224();
void ogws_fn_8021F2EC();
void ogws_fn_8021F434();
void ogws_fn_8021F544();
void ogws_fn_8021F654();
void ogws_fn_8021F7AC();
void ogws_fn_8021F8C4();
void ogws_fn_8021F9DC();
void ogws_fn_8021FB08();
void ogws_fn_8021FC14();
void ogws_fn_8021FE34();
void ogws_fn_80220034();
void ogws_fn_8022025C();
void ogws_fn_80220464();
void ogws_fn_8022066C();
void ogws_fn_8022071C();
void ogws_fn_8022072C();
void ogws_fn_8022073C();
void ogws_fn_802207A8();
void ogws_fn_8022094C();
void ogws_fn_80220954();
void ogws_fn_8022095C();
void ogws_fn_80220964();
void ogws_fn_8022096C();
void ogws_fn_80220974();
void ogws_fn_8022097C();
void ogws_fn_8022098C();
void ogws_fn_80254BD8();
void ogws_fn_80254C88();
void ogws_fn_80254D38();
void ogws_fn_80254D40();
void ogws_fn_80254D48();
void ogws_fn_80254DD0();
void ogws_fn_80254E80();
void ogws_fn_80254F10();
void ogws_fn_80254FA0();
void ogws_fn_802551A8();
void ogws_fn_80255384();
void ogws_fn_80255580();
void ogws_fn_80255738();
void ogws_fn_80255930();
void ogws_fn_80255AE8();
void ogws_fn_80255CA0();
void ogws_fn_80255EA8();
void ogws_fn_80256088();
void ogws_fn_802564AC();
void ogws_fn_80316418();
void fn_804C7D10();
void fn_804C7D14();
void fn_804C81CC();
void fn_804E985C();
void ogws_fn_8031ECB4();
void ogws_fn_8031EF2C();
void ogws_fn_8031EF84();
void ogws_fn_8031EFE0();
void fn_804D7920();
void ogws_fn_8031F180();
void fn_804D91FC();
void fn_804D9330();
void ogws_fn_80320C7C();
void fn_804D93D4();
void fn_804D93DC();
void ogws_fn_80320DA8();

void* lbl_803CA430[10] = {
    0, 0, (void*)ogws_fn_8031EF84, (void*)ogws_fn_8031EF2C,
    (void*)ogws_fn_8031ECB4, (void*)fn_804E985C, (void*)ogws_fn_80316418, (void*)fn_804C7D14,
    (void*)fn_804C7D10, 0,
};
void* __vt__Q27Bowling17RPBowNpcSndObject[56] = {
    0, 0, 0, 0,
    (void*)fn_804D93DC, (void*)ogws_fn_80220964, (void*)ogws_fn_8022096C, (void*)ogws_fn_80220974,
    (void*)ogws_fn_8022095C, (void*)ogws_fn_80220954, (void*)ogws_fn_8022094C, 0,
    0, (void*)ogws_fn_8022097C, (void*)ogws_fn_8021E2A4, (void*)ogws_fn_8022098C,
    (void*)ogws_fn_80320C7C, (void*)ogws_fn_8022071C, (void*)ogws_fn_8021D138, (void*)ogws_fn_8022066C,
    (void*)ogws_fn_80220464, (void*)ogws_fn_8022025C, (void*)ogws_fn_80220034, (void*)ogws_fn_8021FE34,
    (void*)ogws_fn_8021C6B8, (void*)ogws_fn_8021FB08, (void*)ogws_fn_8021FC14, (void*)ogws_fn_8021F9DC,
    (void*)ogws_fn_8021F8C4, (void*)ogws_fn_8021F7AC, (void*)ogws_fn_8021F654, (void*)ogws_fn_8021F544,
    (void*)ogws_fn_8021F434, (void*)ogws_fn_8021F224, (void*)ogws_fn_8021F2EC, (void*)ogws_fn_8021F13C,
    (void*)ogws_fn_8021EF48, (void*)ogws_fn_8021ED54, (void*)ogws_fn_8021E920, (void*)ogws_fn_8021EB40,
    (void*)ogws_fn_8021EA20, (void*)ogws_fn_8021E890, (void*)ogws_fn_8021E800, (void*)ogws_fn_8021E750,
    (void*)ogws_fn_8021E6C8, (void*)ogws_fn_8021E6C0, (void*)ogws_fn_8021E6B8, (void*)ogws_fn_8021C8B8,
    (void*)ogws_fn_8021E5D0, (void*)ogws_fn_8021E4B4, (void*)ogws_fn_8021E3A4, (void*)ogws_fn_8021E2BC,
    (void*)ogws_fn_802207A8, (void*)ogws_fn_8022073C, (void*)ogws_fn_8022072C, 0,
};
void* lbl_803CA538[14] = {
    0, 0, (void*)fn_804D9330, (void*)fn_804D91FC,
    (void*)fn_804C81CC, (void*)ogws_fn_8031EFE0, (void*)ogws_fn_80316418, (void*)ogws_fn_8031F180,
    (void*)fn_804D7920, 0, 0, (void*)fn_804D93D4,
    (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv, (void*)GenMessage__18IRPSysHostIOSocketFv,
};
void* lbl_803CA570[6] = {
    0, 0, (void*)ogws_fn_80320DA8, (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv, 0,
};
void* __vt__14BowPinSndActor[26] = {
    0, 0, (void*)ogws_fn_80323680, (void*)ogws_fn_80254F10,
    (void*)ogws_fn_80254E80, (void*)ogws_fn_80254DD0, (void*)ogws_fn_80254D48, (void*)ogws_fn_80254D40,
    (void*)ogws_fn_80254C88, 0, 0, (void*)ogws_fn_802564AC,
    (void*)ogws_fn_8021E2A4, (void*)ogws_fn_8021E2B4, (void*)ogws_fn_80254BD8, (void*)ogws_fn_80256088,
    (void*)ogws_fn_80255EA8, (void*)ogws_fn_80255CA0, (void*)ogws_fn_80255AE8, (void*)ogws_fn_80255930,
    (void*)ogws_fn_80255738, (void*)ogws_fn_80255580, (void*)ogws_fn_80255384, (void*)ogws_fn_802551A8,
    (void*)ogws_fn_80254FA0, (void*)ogws_fn_80254D38,
};
}  // extern "C"

