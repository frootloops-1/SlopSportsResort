// Resort (RZTE01_01) port of Wii Sports RPBow_8031EFE4.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_8031EFE4: bowling camera/bowler presentation context (BowCam: the
// player Kokeshi pair per lane, animation blend state, the HostIO sound and
// actor objects). Field and type names are inferred from use (invented);
// the functions keep their fn_ names and take the object as an explicit
// pointer.
//
// Functions are written in ASCENDING address order with
// `#pragma defer_codegen off` so .text and the .sdata2 literal pool come out
// in the original order (the unit owns its pool: literals, not lbl_ externs;
// the 30 at 0x804C5D50 is a `const int[1]` defined before fn_804D7AA4).
//
// Matching notes:
// - fn_804D76E4/fn_804D8434 take `const BowCam*`: with a const self MWCC
//   hoists field loads above stores through the hidden return pointer;
// - fn_804D8434/fn_804D7AA4 write the position maths in place (an inline
//   helper reverses the stack order of the VEC3 temporaries); 127.99989 is
//   MTX34RotXYZRad(.., 3.14159f, ..) folded;
// - kokeshi models get mBaseScale through SetBaseScale(const VEC3&) of a local
//   VEC3 (the frsp on the scale comes from that copy);
// - fn_804D863C: `deg = deg + 180.0f + 180.0f` gives the unfolded 180+180;
// - fn_804D7920/ogws_fn_8031F180: a one-trip bowler loop gives (index + base) adds;
// - ogws_fn_80320968: new+ctor in a static inline returning the pointer, and
//   `u8* b` declared before `s32 i` in the ctor inline, fix the
//   callee-saved assignment;
// - ogws_fn_80320C7C: `u8*` self param and real SoundArchivePlayer/SoundPlayer
//   views (reference return) for the StopAllSound loop;
// - dont_inline only around the D8C/D94 thunks (it blocks inlining inside the
//   functions it covers, not inlining of them).
// - fn_804D8558: the mode is an enum-typed ?: in the fn_804D8F20 argument
//   (args set up before the branch; an int ?: becomes branchless).

#pragma defer_codegen off

namespace nw4r {
namespace math {
struct _VEC3 {
    f32 x, y, z;
};

struct VEC3;
static inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB);
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

struct _MTX34 {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
        };
        f32 m[3][4];
    };
};

struct MTX34 : _MTX34 {
    MTX34() {}
    // clang-format off
    MTX34(f32 f00, f32 f01, f32 f02, f32 f03,
          f32 f10, f32 f11, f32 f12, f32 f13,
          f32 f20, f32 f21, f32 f22, f32 f23) {
        _00 = f00; _01 = f01; _02 = f02; _03 = f03;
        _10 = f10; _11 = f11; _12 = f12; _13 = f13;
        _20 = f20; _21 = f21; _22 = f22; _23 = f23;
    }
    // clang-format on
};

MTX34* MTX34RotXYZFIdx(MTX34* pMtx, f32 fx, f32 fy, f32 fz);

static inline MTX34* MTX34RotXYZRad(MTX34* pMtx, f32 rx, f32 ry, f32 rz) {
    return MTX34RotXYZFIdx(pMtx, 40.743664f * rx, 40.743664f * ry, 40.743664f * rz);
}

static inline MTX34* MTX34RotXYZDeg(MTX34* pMtx, f32 dx, f32 dy, f32 dz) {
    return MTX34RotXYZFIdx(pMtx, 0.7111111f * dx, 0.7111111f * dy, 0.7111111f * dz);
}
}  // namespace math

namespace g3d {
class ScnObj {
public:
    enum ScnObjMtxType { MTX_LOCAL, MTX_WORLD, MTX_VIEW };
    void SetMtx(ScnObjMtxType type, const math::MTX34* pMtx);
};
}  // namespace g3d
}  // namespace nw4r

namespace EGG {
struct Vector3f : nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(f32 fx, f32 fy, f32 fz) : nw4r::math::VEC3(fx, fy, fz) {}

    Vector3f& operator=(const nw4r::math::VEC3& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};

struct Matrix34f : nw4r::math::MTX34 {
    Matrix34f() {}
};

template <int N>
class AudioSoundActorBaseWithCamera {
public:
    static void* smCommon3DManager[N];
};
}  // namespace EGG

typedef nw4r::math::VEC3 VEC3;
typedef nw4r::math::MTX34 MTX34;

struct BowAnmPad {
    u8 pad00[0x68];
};

// RPGrpModelAnm view (vtable at +0x68; only the slots used here).
class RPGrpModelAnm : public BowAnmPad {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual s16 SetBlendAnm(int anm, u8 slot, u16 idx);           // 0x18
    virtual void v1C();
    virtual void SetBlendWeight(int anm, u8 slot, f32 w, u8 unk);  // 0x20
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual bool Cancel(int anm, u16 idx);                         // 0x3C
    virtual void Start(s32 anm, s32 idx, f32 frame);               // 0x40
    virtual void v44();
    virtual void v48();
    virtual int GetNumFrame(int anm, u16 idx) const;               // 0x4C
    virtual void v50();
    virtual void SetFrame(int anm, u16 idx, f32 frame);            // 0x54
    virtual void v58();
    virtual void SetUpdateRate(int anm, u16 idx, f32 rate);        // 0x5C
};

class RPGrpModel {
public:
    struct ModelEx {
        u8 _00[0x8];
        nw4r::g3d::ScnObj* mpScnObj;  // 0x8
    };

    nw4r::g3d::ScnObj* GetScnObj() const {
        return mpModelEx->mpScnObj;
    }
    void SetBaseScale(f32 scale) {
        mBaseScale.x = mBaseScale.y = mBaseScale.z = scale;
    }
    void SetBaseScale(const nw4r::math::VEC3& rScale) {
        mBaseScale.x = rScale.x;
        mBaseScale.y = rScale.y;
        mBaseScale.z = rScale.z;
    }

    void UpdateFrame();
    void Calc();
    void Entry();

    u8 _00[0x2];
    u8 mDrawGroup;  // 0x2
    u8 _03[0x8 - 0x3];
    u16 mFlags;  // 0x8
    u8 _0A[0x20 - 0xA];
    nw4r::math::_VEC3 mBaseScale;  // 0x20
    RPGrpModelAnm* mpModelAnm;     // 0x2C
    u8 _30[0x40 - 0x30];
    ModelEx* mpModelEx;  // 0x40
};

class RPSysKokeshi {
public:
    void GetHeadJointMtx(EGG::Matrix34f* pMtx);
    void GetLeftHandJointMtx(EGG::Matrix34f* pMtx);
    void GetRightHandJointMtx(EGG::Matrix34f* pMtx);

    u8 _00[0xA4];
    RPGrpModel* mpNigaoeModel;     // 0xA4
    RPGrpModel* mpBodyModel;       // 0xA8
    RPGrpModel* mpLeftHandModel;   // 0xAC
    RPGrpModel* mpRightHandModel;  // 0xB0
};

class RPGrpModelResManager {
public:
    void GetResultTransform(u16, u16, f32, EGG::Matrix34f*, EGG::Vector3f*, EGG::Vector3f*,
                            EGG::Vector3f*);
    static RPGrpModelResManager* spCurrent;
};

struct BowSndPad {
    u8 pad00[0x78];
};

// Bowling::RPBowNpcSndObject view (vtable at +0x78).
struct BowNpcSnd : BowSndPad {
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
    virtual void setPos(const VEC3& pos);  // 0x48
};

// Colour passed by value to fn_80372FD8.
struct BowColor {
    u8 r, g, b, a;
};

// BowExcelGlobal.bin view: blend frame table in 6-degree steps.
struct BowFrameEnt {
    f32 a, b;
};
struct BowExcel {
    u8 pad00[0xD4];
    BowFrameEnt frameTbl[31];  // 0xD4
};

struct BowHostIO {
    virtual void* d(s32);
    BowExcel* data;  // 0x04
};

struct BowLanePair {
    RPSysKokeshi* p[2];
};

// Body animation ids passed to fn_804D8F20 (inferred: names unknown; an enum-typed
// ?: is not folded into branchless code by MWCC, an int-typed one is).
enum BowAnmId { BOW_ANM_0, BOW_ANM_1, BOW_ANM_2, BOW_ANM_3, BOW_ANM_4, BOW_ANM_5 };

struct BowAnmPair {
    u16 id[2];
    f32 frame[2];

    BowAnmPair& operator=(const BowAnmPair& rOther) {
        id[0] = rOther.id[0];
        id[1] = rOther.id[1];
        frame[0] = rOther.frame[0];
        frame[1] = rOther.frame[1];
        return *this;
    }
};

// Inferred (name invented): bowler presentation/camera context.
struct BowCam {
    u8 pad00[0x8];
    s32 idx;              // 0x08
    u8 padResort0C[4];    // Resort: inserted word (pos is at 0x10)
    EGG::Vector3f pos;    // 0x10
    f32 scale;            // 0x18
    f32 f1C;              // 0x1C
    f32 f20;              // 0x20
    f32 sideOfs;          // 0x24
    f32 rate;             // 0x28
    f32 alpha;            // 0x2C
    u8 padResort30[0xC];  // Resort: 0xC more before state (position guess); +0x10 total
    s32 state;            // 0x40
    s32 stateFrame;       // 0x34
    f32 angle;            // 0x38
    u8 b3C;               // 0x3C
    u8 pad3D[3];
    f32 fade;             // 0x40
    f32 dist;             // 0x44
    f32 yaw;              // 0x48
    f32 f4C;              // 0x4C
    MTX34 m50;            // 0x50
    u8 pad80[4];
    u8 b84;               // 0x84
    u8 b85;               // 0x85
    u8 pad86[2];
    s32 sndStep;          // 0x88
    BowLanePair lane[2];  // 0x8C
    u8 pad9C[0xAC - 0x9C];
    BowAnmPair anm[2];    // 0xAC
    f32 weight[2];        // 0xC4
    f32 fCC;              // 0xCC
    f32 fD0;              // 0xD0
    u16 resD4;            // 0xD4
    u16 resD6;            // 0xD6
    u16 resD8;            // 0xD8
    u8 padDA[2];
    EGG::Vector3f vDC;    // 0xDC
    f32 fE8;              // 0xE8
    f32 fEC;              // 0xEC
    u8 flag[4];           // 0xF0
    BowNpcSnd* snd;       // 0xF4
    f32 sndFrame[4];      // 0xF8
    f32 sndVol[4];        // 0x108
    RPGrpModel* obj118;   // 0x118
    f32 f11C;             // 0x11C
    void* act[4];         // 0x120
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
void PSMTXConcat(const MTX34*, const MTX34*, MTX34*);
void PSMTXIdentity(MTX34*);
void PSMTXTransApply(const MTX34*, MTX34*, f32, f32, f32);
double cos(double);
double sin(double);
void* memset(void*, int, unsigned long);
void* __nw__FUl(unsigned long);
void __dl__FPv(void*);
void __dt__18IRPSysHostIOSocketFv(void*, s32);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);
void fn_804D75F0(BowNpcSnd*, f32);
void fn_80372FD8(RPGrpModel* pModel, int, int, BowColor color);
void ogws_fn_801FFD00(void*);
void ogws_fn_801FFE90(void*, void*);
void* ogws_fn_801FFE98(void*);
void* __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(void*, void*, void*);
void __ct__Q23EGG8DisposerFv(void*);
void __ct__17RPSndMoveValueF32Fv(void*);
void List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void __destroy_arr(void*, void*, unsigned long, unsigned long);
void __ct__Q34nw4r3snd11SoundHandleFv();
void __dt__Q34nw4r3snd11SoundHandleFv();
void __dt__Q23EGG8DisposerFv(void*, s32);
void system_halt(const char*, int, const char*, ...);
void* __ct__18IRPSysHostIOSocketFv(void*);
void* LoadGameCommonArchive__20RPSysResourceManagerFlPQ23EGG4Heap(s32, void*);
void* LoadGameLocalArchive__20RPSysResourceManagerFlPQ23EGG4Heap(s32, void*);
void* GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(void*, const char*, u32*);
extern u8 __vt__19RPSndAudioActorBase[];
extern u8 sActorList__19RPSndAudioActorBase[];
extern u8 lbl_803C3E14[];
extern u8 __vt__Q27Bowling17RPBowNpcSndObject[];
extern u8 lbl_803CA570[];
extern char lbl_803C4098[];
extern char lbl_803C4080[];
extern f32 lbl_804BF9A0;
extern u8 lbl_804BF9A4;
struct BowSndMgr {
    u8 pad[0x69C];
    void* player;
};
extern BowSndMgr* spInstance__13RPSndAudioMgr;
BowHostIO* lbl_804BF9A8;

void fn_804D863C(BowCam* self);
void fn_804D8F20(BowCam* self, s32 a, s32 b);
}

static inline RPGrpModelAnm* BowBodyAnm(BowCam* self, int i) {
    return self->lane[self->idx].p[i]->mpBodyModel->mpModelAnm;
}

extern "C" {

MTX34 fn_804D76E4(const BowCam* self) {
    EGG::Matrix34f handMtx;
    self->lane[self->idx].p[0]->GetRightHandJointMtx(&handMtx);
    VEC3 pos(0.6f, 0.0f, -1.2f);
    VEC3 rot(-90.0f, 0.0f, 180.0f);
    MTX34 rotMtx;
    nw4r::math::MTX34RotXYZDeg(&rotMtx, rot.x, rot.y, rot.z);
    if (self->flag[self->idx] == 0) {
        MTX34 flipMtx(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
        PSMTXConcat(&rotMtx, &flipMtx, &rotMtx);
    }
    MTX34 out;
    PSMTXIdentity(&out);
    PSMTXTransApply(&out, &out, pos.x, pos.y, pos.z);
    PSMTXConcat(&out, &rotMtx, &out);
    PSMTXConcat(&handMtx, &out, &out);
    return out;
}

// Both setters loop over a single bowler slot: the one-trip loop keeps the
// original (index + base) operand order of the lane-pair address adds.
void fn_804D7920(BowCam* self, u8 v) {
    for (int i = 0; i < 1; i++) {
        self->lane[self->idx].p[i]->mpBodyModel->mDrawGroup = v;
        self->lane[self->idx].p[i]->mpNigaoeModel->mDrawGroup = v;
        self->lane[self->idx].p[i]->mpLeftHandModel->mDrawGroup = v;
        self->lane[self->idx].p[i]->mpRightHandModel->mDrawGroup = v;
    }
    self->obj118->mDrawGroup = v;
}

#define BOW_SET_BIT0(sub, on)   \
    if (on) {                   \
        (sub)->mFlags |= 1;     \
    } else {                    \
        (sub)->mFlags &= ~1;    \
    }

void ogws_fn_8031F180(BowCam* self, s32 on) {
    RPGrpModel* sub;
    for (int i = 0; i < 1; i++) {
        sub = self->lane[self->idx].p[i]->mpBodyModel;
        BOW_SET_BIT0(sub, on)
        sub = self->lane[self->idx].p[i]->mpNigaoeModel;
        BOW_SET_BIT0(sub, on)
        sub = self->lane[self->idx].p[i]->mpLeftHandModel;
        BOW_SET_BIT0(sub, on)
        sub = self->lane[self->idx].p[i]->mpRightHandModel;
        BOW_SET_BIT0(sub, on)
    }
    sub = self->obj118;
    BOW_SET_BIT0(sub, on)
}

extern const int lbl_804C5D50[1];
const int lbl_804C5D50[1] = {30};

void fn_804D7AA4(BowCam* self, f32 rate) {
    EGG::Matrix34f mtx;
    MTX34 rot180;
    MTX34 mirror;
    EGG::Matrix34f lhand;
    EGG::Matrix34f rhand;
    EGG::Matrix34f head;

    switch (self->state) {
    case 1:
        self->fade += 0.0055555557f;
        if (self->fade > 1.0f) {
            self->state = 2;
            self->stateFrame = -1;
        }
        break;
    }
    self->stateFrame++;

    f32 c = -(f32)cos(self->yaw);
    VEC3 dir(sin(self->yaw), 0.0f, c);
    VEC3 side(dir.z, 0.0f, -dir.x);
    self->pos = VEC3(0.0f, 0.0f, self->dist) + dir * self->fade * self->dist;
    self->pos += VEC3(self->f4C, 0.0f, 0.0f);
    self->pos += self->vDC;
    nw4r::math::MTX34RotXYZRad(&self->m50, 0.0f, -self->yaw, 0.0f);
    fn_804D863C(self);

    if (self->anm[0].id[0] == 0 && self->sndStep < 4 &&
        self->anm[0].frame[0] > self->sndFrame[self->sndStep]) {
        fn_804D75F0(self->snd, self->sndVol[self->sndStep]);
        self->sndStep++;
    }
    self->snd->setPos(self->pos);

    nw4r::math::MTX34RotXYZRad(&rot180, 0.0f, 3.14159f, 0.0f);
    PSMTXIdentity(&mtx);
    PSMTXConcat(&rot180, &mtx, &mtx);
    PSMTXConcat(&self->m50, &mtx, &mtx);

    f32 ofs;
    if (self->flag[self->idx]) {
        ofs = self->sideOfs;
    } else {
        ofs = -self->sideOfs;
    }
    if (self->b85) {
        ofs = 0.0f;
    }
    VEC3 trans = VEC3(self->f4C - nw4r::math::VEC3Dot(&self->vDC, &side), self->vDC.y,
                      self->dist + nw4r::math::VEC3Dot(&self->vDC, &dir)) +
                 side * ofs;
    PSMTXTransApply(&mtx, &mtx, trans.x, trans.y, trans.z);

    f32 scale = self->scale;
    VEC3 scl(scale, scale, scale);
    mirror = mtx;
    mirror._10 *= -1.0f;
    mirror._11 *= -1.0f;
    mirror._12 *= -1.0f;
    mirror._13 *= -1.0f;

    for (int i = 0; i < 2; i++) {
        if (self->lane[self->idx].p[i]->mpBodyModel->GetScnObj() != NULL) {
            self->lane[self->idx].p[i]->mpBodyModel->GetScnObj()->SetMtx(
                nw4r::g3d::ScnObj::MTX_LOCAL, i == 0 ? &mtx : &mirror);
        }
        self->lane[self->idx].p[i]->mpBodyModel->SetBaseScale(scl);
        self->lane[self->idx].p[i]->mpBodyModel->UpdateFrame();
        self->lane[self->idx].p[i]->mpBodyModel->Calc();
        self->lane[self->idx].p[i]->GetHeadJointMtx(&head);
        self->lane[self->idx].p[i]->GetLeftHandJointMtx(&lhand);
        self->lane[self->idx].p[i]->GetRightHandJointMtx(&rhand);

        if (i == 0) {
            f32 ratio = self->vDC.z / self->dist;
            int frame = (int)(ratio * (f32)(lbl_804C5D50[0] - 2));
            f32 unused = frame;
            MTX34 ballMtx = mtx;
            ballMtx._03 = head._03;
            ballMtx._13 = self->f11C;
            ballMtx._23 = head._23;
            if (self->obj118->GetScnObj() != NULL) {
                self->obj118->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &ballMtx);
            }
            self->obj118->SetBaseScale(scl * 1.0f);
            self->obj118->UpdateFrame();
            self->obj118->Calc();
            self->obj118->Entry();

            BowColor color;
            color.b = 0;
            color.g = 0;
            color.r = 0;
            f32 a = rate * self->alpha;
            if (a > 1.0f) {
                a = 1.0f;
            }
            color.a = 60.0f * a;
            fn_80372FD8(self->obj118, 0, 0, color);
        }

        MTX34 rotR;
        VEC3 r1(90.0f, 0.0f, 0.0f);
        nw4r::math::MTX34RotXYZDeg(&rotR, r1.x, r1.y, r1.z);
        PSMTXConcat(&rhand, &rotR, &rhand);
        MTX34 rotL;
        VEC3 r2(-90.0f, 0.0f, 0.0f);
        nw4r::math::MTX34RotXYZDeg(&rotL, r2.x, r2.y, r2.z);
        PSMTXConcat(&lhand, &rotL, &lhand);

        if (self->flag[self->idx] == 0) {
            MTX34 flip(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f);
            PSMTXConcat(&head, &flip, &head);
            PSMTXConcat(&lhand, &flip, &lhand);
            PSMTXConcat(&rhand, &flip, &rhand);
        }
        if (i != 0) {
            MTX34 flip2(-1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            PSMTXConcat(&head, &flip2, &head);
        }

        if (self->lane[self->idx].p[i]->mpNigaoeModel->GetScnObj() != NULL) {
            self->lane[self->idx].p[i]->mpNigaoeModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                                          &head);
        }
        self->lane[self->idx].p[i]->mpNigaoeModel->SetBaseScale(scl);
        self->lane[self->idx].p[i]->mpNigaoeModel->UpdateFrame();
        self->lane[self->idx].p[i]->mpNigaoeModel->Calc();

        if (self->lane[self->idx].p[i]->mpLeftHandModel->GetScnObj() != NULL) {
            self->lane[self->idx].p[i]->mpLeftHandModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                                            &lhand);
        }
        self->lane[self->idx].p[i]->mpLeftHandModel->SetBaseScale(scl);
        self->lane[self->idx].p[i]->mpLeftHandModel->UpdateFrame();
        self->lane[self->idx].p[i]->mpLeftHandModel->Calc();

        if (self->lane[self->idx].p[i]->mpRightHandModel->GetScnObj() != NULL) {
            self->lane[self->idx].p[i]->mpRightHandModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                                             &rhand);
        }
        self->lane[self->idx].p[i]->mpRightHandModel->SetBaseScale(scl);
        self->lane[self->idx].p[i]->mpRightHandModel->UpdateFrame();
        self->lane[self->idx].p[i]->mpRightHandModel->Calc();

        self->lane[self->idx].p[i]->mpBodyModel->Entry();
        self->lane[self->idx].p[i]->mpNigaoeModel->Entry();
        self->lane[self->idx].p[i]->mpLeftHandModel->Entry();
        self->lane[self->idx].p[i]->mpRightHandModel->Entry();
    }
}

VEC3 fn_804D8434(const BowCam* self) {
    f32 c = -(f32)cos(self->yaw);
    VEC3 dir(sin(self->yaw), 0.0f, c);
    VEC3 r = VEC3(0.0f, 0.0f, self->dist) + dir * self->fade * self->dist;
    r += VEC3(self->f4C, 0.0f, 0.0f);
    return r;
}

void fn_804D853C(BowCam* self) {
    self->state = 1;
    self->stateFrame = -1;
    fn_804D8F20(self, 0, 1);
}

struct BowV3 {
    f32 x, y, z;
    BowV3() {}
    ~BowV3() {}
};

void fn_804D8558(BowCam* self, s32 flag, u8 v) {
 memset(&self->state, 0, 0x5C);
 self->pos = VEC3(0.0f, 0.0f, 0.0f);
 self->dist = 20.0f;
 self->state = 0;
 self->stateFrame = -1;
 self->anm[0].id[0] = 0; self->anm[0].id[1] = 0;
 self->anm[0].frame[0] = 0.0f; self->anm[0].frame[1] = 0.0f;
 self->anm[1].id[0] = 0; self->anm[1].id[1] = 0;
 self->anm[1].frame[0] = 0.0f; self->anm[1].frame[1] = 0.0f;
 self->weight[0] = self->weight[1] = 0.0f;
 fn_804D8F20(self, 3, flag != 0 ? BOW_ANM_4 : BOW_ANM_5);
 self->weight[0] = self->weight[1] = 1.0f;
 self->vDC = VEC3(0.0f, 0.0f, 0.0f);
 self->b85 = v;
}

void fn_804D863C(BowCam* self) {
    EGG::Vector3f pos[2];
    pos[0].x = 0.0f;
    pos[0].y = 0.0f;
    pos[0].z = 0.0f;
    pos[1].x = 0.0f;
    pos[1].y = 0.0f;
    pos[1].z = 0.0f;

    if (self->anm[0].id[1] == 1 && self->b3C == 0) {
        self->anm[0].id[1] = 2;
        self->anm[1].id[1] = 1;
        for (int i = 0; i < 2; i++) {
            BowBodyAnm(self, i)->Start(0, 2, 0.0f);
        }
        self->weight[1] = 0.0f;
    }

    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            if (self->anm[j].id[k] == 5) {
                self->anm[j].frame[k] += 1.0f;
                if (self->anm[j].frame[k] >= (f32)BowBodyAnm(self, 0)->GetNumFrame(0, 5)) {
                    self->anm[j].frame[k] -= (f32)BowBodyAnm(self, 0)->GetNumFrame(0, 5);
                }
            }
            if (self->anm[j].id[k] == 3) {
                self->anm[j].frame[k] += 1.0f;
                if (self->anm[j].frame[k] >= (f32)BowBodyAnm(self, 0)->GetNumFrame(0, 3)) {
                    self->anm[j].frame[k] -= (f32)BowBodyAnm(self, 0)->GetNumFrame(0, 3);
                }
                RPGrpModelResManager::spCurrent->GetResultTransform(self->resD6, self->resD8, self->anm[j].frame[k],
                                                                   NULL, &pos[j], NULL, NULL);
                pos[j].y -= 5.4f;
                pos[j] *= 0.7f;
            }
            if (self->anm[j].id[k] == 0) {
                self->anm[j].frame[k] += self->fEC;
                RPGrpModelResManager::spCurrent->GetResultTransform(self->resD4, self->resD8, self->anm[j].frame[k],
                                                                   NULL, &pos[j], NULL, NULL);
                pos[j].y -= 5.4f;
                pos[j] *= 0.7f;
            }
            if (self->anm[j].id[k] == 1 || self->anm[j].id[k] == 4) {
                f32 deg = 180.0f * self->angle / 3.14159f;
                while (deg > 180.0f) {
                    deg -= 360.0f;
                }
                while (deg < -180.0f) {
                    deg += 360.0f;
                }
                if (self->anm[j].id[k] == 4) {
                    if (deg < -90.0f) {
                        deg = -90.0f + (-deg - 90.0f);
                    } else if (deg > 90.0f) {
                        deg = 90.0f - (deg - 90.0f);
                    }
                } else {
                    if (deg > 0.0f) {
                        self->b84 = 1;
                    }
                    if (deg < -90.0f) {
                        if (self->b84) {
                            deg = deg + 180.0f + 180.0f;
                        } else {
                            deg = -90.0f + (-deg - 90.0f);
                        }
                    }
                }
                f32 t = (90.0f + deg) / 6.0f;
                BowExcel* d = lbl_804BF9A8->data;
                f32 target = (t - (int)t) * (d->frameTbl[(int)t + 1].a - d->frameTbl[(int)t].a) + d->frameTbl[(int)t].a;
                self->anm[j].frame[k] += self->rate * (target - self->anm[j].frame[k]);
            }
            if (self->anm[j].id[k] == 2) {
                f32 deg = 180.0f * self->angle / 3.14159f;
                while (deg > 180.0f) {
                    deg -= 360.0f;
                }
                while (deg < -180.0f) {
                    deg += 360.0f;
                }
                if (deg < -90.0f) {
                    deg = deg + 180.0f + 180.0f;
                }
                f32 t = (90.0f + deg) / 6.0f;
                BowExcel* d = lbl_804BF9A8->data;
                f32 target = (t - (int)t) * (d->frameTbl[(int)t + 1].b - d->frameTbl[(int)t].b) + d->frameTbl[(int)t].b;
                self->anm[j].frame[k] += self->rate * (target - self->anm[j].frame[k]);
            }
        }
    }

    for (int k = 0; k < 2; k++) {
        self->weight[k] += 0.033333335f;
        if (self->weight[k] > 1.0f) {
            for (int i = 0; i < 2; i++) {
                BowBodyAnm(self, i)->Cancel(0, self->anm[1].id[k]);
            }
            self->weight[k] = 1.0f;
        }
    }

    self->vDC = pos[0] * self->weight[0] + pos[1] * (1.0f - self->weight[0]);

    for (int i = 0; i < 2; i++) {
        RPGrpModelAnm* anm = BowBodyAnm(self, i);
        anm->SetBlendWeight(0, 0, self->weight[0], 0);
        anm->SetBlendWeight(0, 1, self->weight[1], 0);
        anm->SetBlendWeight(0, 2, 1.0f - self->weight[0], 0);
        anm->SetBlendWeight(0, 3, 1.0f - self->weight[1], 0);
        anm->SetBlendAnm(0, 0, self->anm[0].id[0]);
        anm->SetBlendAnm(0, 1, self->anm[0].id[1]);
        anm->SetBlendAnm(0, 2, self->anm[1].id[0]);
        anm->SetBlendAnm(0, 3, self->anm[1].id[1]);
        anm->SetFrame(0, self->anm[0].id[0], self->anm[0].frame[0]);
        anm->SetFrame(0, self->anm[0].id[1], self->anm[0].frame[1]);
        anm->SetFrame(0, self->anm[1].id[0], self->anm[1].frame[0]);
        anm->SetFrame(0, self->anm[1].id[1], self->anm[1].frame[1]);
        anm->SetUpdateRate(0, self->anm[0].id[0], 0.0f);
        anm->SetUpdateRate(0, self->anm[1].id[1], 0.0f);
        anm->SetUpdateRate(0, self->anm[0].id[0], 0.0f);
        anm->SetUpdateRate(0, self->anm[1].id[1], 0.0f);
    }
    ogws_fn_801FFD00(self->act[self->idx]);
}

void fn_804D8F20(BowCam* self, s32 a, s32 b) {
    s32 i;
    self->anm[1] = self->anm[0];
    self->anm[0].id[0] = a;
    self->anm[0].id[1] = b;
    self->anm[0].frame[0] = 0.0f;
    self->anm[0].frame[1] = 0.0f;
    for (i = 0; i < 2; i++) {
        BowBodyAnm(self, i)->Start(0, a, 0.0f);
        BowBodyAnm(self, i)->Start(0, b, 0.0f);
    }
    self->weight[0] = 0.0f;
    self->weight[1] = 0.0f;
}

void ogws_fn_80320930(u8* self, s32 a, s32 b, s32 c, void* d) {
    *(u16*)(self + 0xD4) = a;
    *(u16*)(self + 0xD8) = c;
    *(u16*)(self + 0xD6) = b;
    *(void**)(self + 0x118) = d;
}

void ogws_fn_80320944(BowCam* self, s32 i, RPSysKokeshi* p0, RPSysKokeshi* p1) {
    self->lane[i].p[0] = p0;
    self->lane[i].p[1] = p1;
    ogws_fn_801FFE90(self->act[i], p0->mpNigaoeModel);
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

static inline BowNpcSnd* BowNewSnd() {
    u8* a = (u8*)__nw__FUl(0x90);
    if (a) a = (u8*)BowSndCt(a, spInstance__13RPSndAudioMgr->player);
    return (BowNpcSnd*)a;
}

void ogws_fn_80320968(BowCam* self) {
    s32 i;
    self->snd = BowNewSnd();
    for (i = 0; i < 4; i++) {
        void* p = __nw__FUl(0x14);
        if (p) p = ogws_fn_801FFE98(p);
        self->act[i] = p;
    }
}

void fn_804D91FC(BowCam* self) {
    self->scale = 0.7f;
    self->f1C = 5.0f;
    self->f20 = 1.8f;
    self->sideOfs = 2.0f;
    self->fCC = 1.0f;
    self->fD0 = 0.08f;
    self->fE8 = -0.2f;
    self->fEC = 1.0f;
    self->idx = 0;
    self->rate = 1.0f;
    self->sndFrame[0] = 52.0f;
    self->sndFrame[1] = 72.0f;
    self->sndFrame[2] = 89.0f;
    self->sndFrame[3] = 105.0f;
    self->sndVol[0] = 0.5f;
    self->sndVol[1] = 0.4f;
    self->sndVol[2] = 0.4f;
    self->sndVol[3] = 1.0f;
    self->f11C = 0.01f;
    self->vDC = VEC3(0.0f, 0.0f, 0.0f);
    self->alpha = 2.7f;
    fn_804D8558(self, 1, 0);
}


void* fn_804D9330(void* p, s32 del) {
    if (p) {
        __dt__18IRPSysHostIOSocketFv((u8*)p + 4, 0);
        if (p) {
            __dt__15RP_DEBUG_STUB_1Fv(p, 0);
        }
        if (del > 0) __dl__FPv(p);
    }
    return p;
}

namespace nw4r {
namespace snd {
class SoundPlayer {
public:
    void StopAllSound(int fadeFrames);
};
class SoundArchivePlayer {
public:
    u32 GetSoundPlayerCount() const {
        return mSoundPlayerCount;
    }
    SoundPlayer& GetSoundPlayer(u32 idx);

    u8 _00[0x30];
    u32 mSoundPlayerCount;  // 0x30
};
}  // namespace snd
}  // namespace nw4r

class RPSndUtility {
public:
    static nw4r::snd::SoundArchivePlayer* spSoundArchivePlayer;
};

static inline void BowStopAllSound() {
    for (u32 i = 0; i < RPSndUtility::spSoundArchivePlayer->GetSoundPlayerCount(); i++) {
        RPSndUtility::spSoundArchivePlayer->GetSoundPlayer(i).StopAllSound(0);
    }
}

void* ogws_fn_80320C7C(u8* self, s32 del) {
    if (self) {
        if (self) {
            *(void**)(self + 0x78) = lbl_803C3E14;
            *(void**)(self + 0x10) = lbl_803C3E14 + 8;
            *(void**)(self + 0x4C) = lbl_803C3E14 + 0x2C;
            BowStopAllSound();
            if (self) {
                if (self + 0x10) {
                    if (self + 0x4C) {
                        *(s32*)(self + 0x50) = 0;
                        *(s32*)(self + 0x54) = 0;
                        __destroy_arr(self + 0x58, (void*)__dt__Q34nw4r3snd11SoundHandleFv, 4, 8);
                    }
                    if (self + 0x10) {
                        *(void**)(self + 0x10) = __vt__19RPSndAudioActorBase;
                        List_Remove__Q24nw4r2utFPQ34nw4r2ut4ListPv(sActorList__19RPSndAudioActorBase, self + 0x10);
                        __dt__Q23EGG8DisposerFv(self + 0x10, 0);
                    }
                }
            }
        }
        if (del > 0) __dl__FPv(self);
    }
    return self;
}
#pragma dont_inline on
// Multiple-inheritance thunks (this - 8) into the Resort methods fn_804D6D74 / fn_804D6D78 and the
// deleting destructor fn_804D9330.
void fn_804D6D74(void* p);
void* fn_804D6D78(void* p, void* a, int b, void* c);
void fn_804D93D4(void* p) { fn_804D6D74((u8*)p - 8); }
void* fn_804D93DC(void* p, void* a, int b, void* c) { return fn_804D6D78((u8*)p - 8, a, b, c); }
void* fn_804D93E4(void* p, s32 del) { return fn_804D9330((u8*)p - 8, del); }
#pragma dont_inline reset

// ogws ArchivePlayer-style file lookup (address unplaced in Resort; kept from the ogws port).
void* ogws_fn_GetFileFromArchive(void** self, const char* name) {
    return GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(self[2], name, 0);
}

void* ogws_fn_80320DA8(void* p, s32 del) {
    if (p) {
        __dt__18IRPSysHostIOSocketFv(p, 0);
        if (del > 0) __dl__FPv(p);
    }
    return p;
}

void ogws_fn_80320E00(void** self) {
    self[2] = LoadGameCommonArchive__20RPSysResourceManagerFlPQ23EGG4Heap(-1, 0);
    self[3] = LoadGameLocalArchive__20RPSysResourceManagerFlPQ23EGG4Heap(-1, 0);
    self[1] = GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(self[2], "BowExcelGlobal.bin", 0);
}

void ogws_fn_80320E60() {
    if (lbl_804BF9A8) {
        lbl_804BF9A8->d(1);
    }
    lbl_804BF9A8 = 0;
}

void ogws_fn_80320EA4() {
    u8* p = (u8*)__nw__FUl(0x10);
    if (p) {
        __ct__18IRPSysHostIOSocketFv(p);
        *(void**)p = lbl_803CA570;
        *(s32*)(p + 4) = 0;
    }
    lbl_804BF9A8 = (BowHostIO*)p;
}

void ogws_fn_80320EF8() {}

}  // extern "C"
