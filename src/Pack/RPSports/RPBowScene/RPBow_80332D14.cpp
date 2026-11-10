// Resort (RZTE01_01) port of Wii Sports RPBow_80332D14.cpp, RPBow_80332C24.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// ---- from ogws RPBow_80332D14.cpp ----
#include <types.h>

// Minimal local nw4r::math view: <nw4r/math/math_types.h> pulls the static
// OSFastCast helpers (revolution/OS) into this object's .text.
extern "C" {
void PSMTXIdentity(f32 (*pMtx)[4]);
void PSMTXConcat(const f32 (*pA)[4], const f32 (*pB)[4], f32 (*pOut)[4]);
void PSMTXTransApply(const f32 (*pIn)[4], f32 (*pOut)[4], f32 x, f32 y, f32 z);
}

namespace nw4r {
namespace math {

struct VEC3;
static inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB);
static inline VEC3* VEC3Sub(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB);

struct _VEC3 {
    f32 x, y, z;
};

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

inline MTX34* MTX34Identity(MTX34* pMtx) {
    PSMTXIdentity(pMtx->m);
    return pMtx;
}

inline MTX34* MTX34Mult(MTX34* pOut, const MTX34* pA, const MTX34* pB) {
    PSMTXConcat(pA->m, pB->m, pOut->m);
    return pOut;
}

inline MTX34* MTX34RotXYZDeg(MTX34* pMtx, f32 dx, f32 dy, f32 dz) {
    return MTX34RotXYZFIdx(pMtx, dx * (256.0f / 360.0f), dy * (256.0f / 360.0f),
                           dz * (256.0f / 360.0f));
}

inline MTX34* MTX34Trans(MTX34* pOut, const VEC3* pTrans, const MTX34* pIn) {
    PSMTXTransApply(pIn->m, pOut->m, pTrans->x, pTrans->y, pTrans->z);
    return pOut;
}

}  // namespace math
}  // namespace nw4r

using nw4r::math::MTX34;
using nw4r::math::VEC3;

#include <Pack/RPUtility/RPUtlRandom.h>

extern "C" void system_halt(const char*, int, const char*, ...);

namespace nw4r {
namespace g3d {

// Minimal view (real class in nw4r/g3d/g3d_scnobj.h)
class ScnObj {
public:
    enum ScnObjMtxType { MTX_LOCAL, MTX_WORLD, MTX_VIEW };
    bool SetMtx(ScnObjMtxType type, const math::MTX34* pMtx);
};

}  // namespace g3d
}  // namespace nw4r

namespace EGG {

struct Matrix34f;

// Minimal view (real class in egg/gfxe/eggModelBoundingInfo.h)
class ModelBoundingInfo {
public:
    struct SphereShape {
        f32 r;        // at 0x0
        VEC3 center;  // at 0x4
    };

    template <typename TShape> struct TData {
        TShape m_shape;
        TShape* m_pShapeSet;
    };

    u8 pad_0x0[0x10];
    TData<SphereShape>* m_pSphere;  // at 0x10

    SphereShape& getShapeSphere() const {
        if (!m_pSphere) {
            system_halt("eggModelBoundingInfo.h", 99, "m_pSphere");
        }
        return m_pSphere->m_shape;
    }
};

}  // namespace EGG

// Minimal view (real class in Pack/RPGraphics/RPGrpModelAnm.h)
class RPGrpModelAnm {
public:
    enum Anm { Anm_Chr };

    u8 pad_0x0[0x68];

    virtual void VF_0x08();
    virtual void VF_0x0C();
    virtual void VF_0x10();
    virtual void VF_0x14();
    virtual void VF_0x18();
    virtual void VF_0x1C();
    virtual void VF_0x20();
    virtual void VF_0x24();
    virtual void VF_0x28();
    virtual void VF_0x2C();
    virtual void VF_0x30();
    virtual void VF_0x34();
    virtual bool StartBlend(Anm anm, u16 idx, f32 weight, f32 frame);  // at 0x38
    virtual void VF_0x3C();
    virtual bool Start(Anm anm, u16 idx, f32 frame);  // at 0x40
    virtual void VF_0x44();
    virtual void VF_0x48();
    virtual int GetNumFrame(Anm anm, u16 idx) const;  // at 0x4C
    virtual void VF_0x50();
    virtual void VF_0x54();
    virtual f32 GetFrame(Anm anm, u16 idx) const;  // at 0x58
};

// Minimal view (real class in EGG)
struct BowModelEx {
    u8 pad_0x0[0x8];
    nw4r::g3d::ScnObj* mpScnObj;  // offset 0x8
};

// Minimal view (real class in Pack/RPGraphics/RPGrpModel.h)
class RPGrpModel {
public:
    u8 pad_0x0[0x20];
    VEC3 mBaseScale;                            // offset 0x20
    RPGrpModelAnm* mpModelAnm;                  // offset 0x2C
    u8 pad_0x30[0x4];
    EGG::ModelBoundingInfo* mpBoundingInfo;     // offset 0x34
    u8 pad_0x38[0x8];
    BowModelEx* mpModelEx;                      // offset 0x40

    nw4r::g3d::ScnObj* GetScnObj() const {
        return mpModelEx->mpScnObj;
    }
    void SetScale(const VEC3& rScale) {
        mBaseScale = rScale;
    }

    void CreateBoundingInfo(unsigned long);
    void UpdateFrame();
    void Calc();
    void Entry();
};

// Minimal view (real class in Pack/RPKernel/RPSysKokeshi.h)
class RPSysKokeshi {
public:
    u8 pad_0x0[0xA4];
    RPGrpModel* mpFaceModel;       // offset 0xA4
    RPGrpModel* mpBodyModel;       // offset 0xA8
    RPGrpModel* mpLeftHandModel;   // offset 0xAC
    RPGrpModel* mpRightHandModel;  // offset 0xB0

    void GetHeadJointMtx(EGG::Matrix34f* pMtx);
    void GetLeftHandJointMtx(EGG::Matrix34f* pMtx);
    void GetRightHandJointMtx(EGG::Matrix34f* pMtx);
};

enum RFLExpression { RFLExp_Normal, RFLExp_Smile };

class RPSysKokeshiManager {
public:
    static void ChangeExpression(RPGrpModel* pModel, RFLExpression expr);
};

// Inferred (name invented): per-lane path state (RPBow_8034656C.cpp)
struct BowPath {
    s32 pad_0x0;  // offset 0x0
    s32 mLane;    // offset 0x4
    s32 mIndex;   // offset 0x8
    u8 mDone;     // offset 0xC
};

namespace Bowling {

// Inferred (name invented): view returned by fn_804D2CBC
struct NpcIdleStateSub {
    int idleState;       // offset 0x0
    int frameCounter;    // offset 0x4
    int unk_0x8;         // offset 0x8
    f32 targetRotation;  // offset 0xC
    f32 rotationSpeed;   // offset 0x10
    VEC3 pos;            // offset 0x14
};

// Inferred (name invented): idle-state block embedded in NpcContext
struct NpcIdleState {
    u8 pad00[0x14];
    s32 unk_0x14;  // offset 0x14
    u8 pad18[0x20];
    u8 flag38;     // offset 0x38
    u8 pad39[0xF];
};

// Minimal view (full definition lives in bowling.h)
struct NpcContext {
    void* vtable;               // 0x00
    RPSysKokeshi* mpKokeshi[2]; // 0x04
    RPGrpModel* mpBallModel;    // 0x0C
    u8 pad_0x10[4];             // 0x10 (Resort: extra field, +4 shift below)
    VEC3 pos_0x10;              // 0x14 (name kept from ogws)
    VEC3 rot_0x1C;              // 0x20
    f32 field_0x28;             // 0x2C
    u8 pad_0x2C[4];             // 0x30
    s32 npcState;               // 0x34
    s32 stateFrameCounter;      // 0x34
    u8 triggerThrow;            // 0x38
    u8 triggerTransition;       // 0x39
    u8 pad_0x3A[2];
    s32 field_0x3C;             // 0x3C
    f32 targetZPos;             // 0x40
    u8 field_0x44;              // 0x44
    u8 pad_0x45[3];
    BowPath* movementState;     // 0x48
    s32 field_0x4C;             // 0x4C
    u8 isHoldingBall;           // 0x50
    u8 flag_51;                 // 0x51
    u8 flag_52;                 // 0x52
    u8 flag_53;                 // 0x53
    s32 laneIdx;                // 0x54
    s32 npcIdx;                 // 0x58
    NpcIdleState subStruct;     // 0x5C
    u8 flag_A4;                 // 0xA4
    u8 flag_A5;                 // 0xA5
};

}  // namespace Bowling

// Inferred (name invented): lane model group with four models at 0xA4..0xB0
struct BowNpcModelSet {
    u8 pad00[0xA4];
    RPGrpModel* mpModelA4;
    RPGrpModel* mpModelA8;
    RPGrpModel* mpModelAC;
    RPGrpModel* mpModelB0;
};

// Inferred (name invented): holder of two model sets at 4 and 8
struct BowNpcModelOwner {
    u8 pad00[4];
    BowNpcModelSet* mpSets[2];  // 0x04
    s32 field_0x0C;             // 0x0C
};

// Inferred (name invented): colour passed by value to fn_80372FD8
struct BowColor {
    u8 r, g, b, a;
};

extern "C" {

void* memset(void*, int, unsigned long);
void* __nw__FUl(unsigned long);
void __dl__FPv(void*);
void __ct__18IRPSysHostIOSocketFv(void*);
void __dt__18IRPSysHostIOSocketFv(void*, s32);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);
void fn_804D6314(u8*, void*);
void fn_804D621C(void*, s32, s32);

VEC3 fn_804D5F88(BowPath* pPath, u8* pFlag, f32* pRatio, f32 t, f32 z);
VEC3 ogws_fn_803466E4(BowPath* pPath, u8* pFlag, f32 t, f32 z);
void fn_804D5D08(BowPath* pPath, VEC3 pos);
VEC3 fn_804D5BD0(BowPath* pPath, f32 t);
bool ogws_fn_801C3490(void* pCull, const VEC3* pPos, f32 radius);
void fn_80372FD8(RPGrpModel* pModel, int, int, BowColor color);
double sin(double);
double atan2(double, double);
double __fabs(double);

extern void* lbl_803CA700[];
u8 lbl_804BF9D8;
u8 lbl_804BF9D9;
extern s32 lbl_804BF9F4;

}  // extern "C"

namespace Bowling {

void fn_804D338C(NpcIdleState*, int, int);
NpcIdleStateSub* fn_804D2CBC(NpcIdleState*);

static inline f32 BowAbs(f32 x) {
    return __fabs(x);
}

static inline f32 BowAtan2(f32 y, f32 x) {
    return atan2(y, x);
}

// Blend the body animation of both kokeshi to `anm` (frame held in a local,
// matching the hoisted 0.0 register of the original).
static inline void ChangeNpcAnm(NpcContext* pCtx, int anm, f32 weight) {
    if (pCtx->field_0x4C != anm) {
        pCtx->field_0x4C = anm;
        f32 frame = 0.0f;
        for (int i = 0; i < 2; i++) {
            pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->StartBlend(RPGrpModelAnm::Anm_Chr, anm,
                                                                     weight, frame);
        }
    }
}

}  // namespace Bowling

using namespace Bowling;

// Functions are written in DESCENDING address order: with the unit's
// `-inline deferred` flag MWCC emits functions (and their .sdata2 pool
// constants) in reverse source order.

extern "C" {

void* ogws_fn_8033457C(void* p, s32 del) {
    if (p) {
        void* sub = (u8*)p + 0x5C;
        if (sub) {
            __dt__18IRPSysHostIOSocketFv(sub, 0);
        }
        if (p) {
            __dt__15RP_DEBUG_STUB_1Fv(p, 0);
        }
        if (del > 0) {
            __dl__FPv(p);
        }
    }
    return p;
}

void* fn_804D5B8C(void* p, s32 del) {
    if (p) {
        __dt__18IRPSysHostIOSocketFv(p, 0);
        if (del > 0) {
            __dl__FPv(p);
        }
    }
    return p;
}

void fn_804D5B28(Bowling::NpcContext* pCtx, RPSysKokeshi* pKokeshi) {
    pCtx->mpKokeshi[0] = pKokeshi;
    void* pMove = __nw__FUl(0x1C);
    if (pMove) {
        __ct__18IRPSysHostIOSocketFv(pMove);
        *(void**)pMove = lbl_803CA700;
    }
    pCtx->movementState = static_cast<BowPath*>(pMove);
    pCtx->field_0x28 = 0.0f;
}

}  // extern "C"

namespace Bowling {

void InitNpcContext(NpcContext* pCtx, int laneIdx, int npcIdx) {
    fn_804D621C(pCtx->movementState, laneIdx, npcIdx);
    pCtx->flag_51 = 0;
    if (laneIdx == 1 && npcIdx == 0) {
        pCtx->flag_51 = 1;
    }
    pCtx->laneIdx = laneIdx;
    pCtx->npcIdx = npcIdx;
}

void UpdateNpcLane(u8* pOut, const NpcContext* pCtx) {
    fn_804D6314(pOut, pCtx->movementState);
}

}  // namespace Bowling

extern "C" {

void fn_804D5A18(BowNpcModelOwner* pThis, s32 val) {
    for (int i = 0; i < 2; i++) {
        pThis->mpSets[i]->mpModelA8->CreateBoundingInfo(1);
        pThis->mpSets[i]->mpModelA4->CreateBoundingInfo(1);
        pThis->mpSets[i]->mpModelAC->CreateBoundingInfo(1);
        pThis->mpSets[i]->mpModelB0->CreateBoundingInfo(1);
    }
    pThis->field_0x0C = val;
}

void fn_804D59D0(Bowling::NpcContext* pCtx) {
    memset(&pCtx->npcState, 0, 0x14);
    pCtx->pos_0x10.z = 9999.0f;
    pCtx->field_0x44 = 0;
}

}  // extern "C"

namespace Bowling {

void fn_804D58F0(NpcContext* pCtx) {
    memset(&pCtx->npcState, 0, 0x14);
    pCtx->rot_0x1C.x = 0.0f;
    pCtx->rot_0x1C.y = 180.0f + 40.0f * RPUtlRandom::getF32() - 20.0f;
    pCtx->rot_0x1C.z = 0.0f;
    pCtx->field_0x44 = 1;
    pCtx->field_0x4C = -1;
    lbl_804BF9D8 = 0;
    fn_804D338C(&pCtx->subStruct, pCtx->laneIdx + 1, pCtx->npcIdx);
    lbl_804BF9D9 = 1;
}

void CalculateNpcBallTransform(MTX34* pOut, const NpcContext* pCtx) {
    if (pCtx->npcState == 0) {
        MTX34 m(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 9999.0f);
        *pOut = m;
        return;
    }

    MTX34 handMtx;
    MTX34 rotMtx;
    MTX34 mtx;

    pCtx->mpKokeshi[0]->GetRightHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&handMtx));
    VEC3 pos(0.0f, -1.2f, 0.6f);
    VEC3 rot(0.0f, 90.0f, 180.0f);
    nw4r::math::MTX34RotXYZDeg(&rotMtx, rot.x, rot.y, rot.z);
    nw4r::math::MTX34Identity(&mtx);
    nw4r::math::MTX34Trans(&mtx, &pos, &mtx);
    nw4r::math::MTX34Mult(&mtx, &mtx, &rotMtx);
    nw4r::math::MTX34Mult(&mtx, &handMtx, &mtx);
    *pOut = mtx;
}

}  // namespace Bowling

extern "C" void fn_804D4824(NpcContext* pCtx, void* pCull) {
    if (!pCtx->field_0x44) {
        return;
    }

    pCtx->triggerTransition = 0;
    if (pCtx->stateFrameCounter < 0) {
        pCtx->stateFrameCounter = 0;
    }

    int smile = 0;
    VEC3 prevPos = pCtx->pos_0x10;
    f32 targetRot = pCtx->rot_0x1C.y;
    f32 rotOffset = 0.0f;
    f32 rotSpeed = 0.1f;

    switch (pCtx->npcState) {
    case 0: {
        if (pCtx->stateFrameCounter == 0) {
            if (pCtx->field_0x4C != 6) {
                pCtx->field_0x4C = 6;
                RPGrpModelAnm* pAnm = pCtx->mpKokeshi[0]->mpBodyModel->mpModelAnm;
                f32 frame = RPUtlRandom::getF32() * pAnm->GetNumFrame(RPGrpModelAnm::Anm_Chr, 6);
                for (int i = 0; i < 2; i++) {
                    pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->StartBlend(
                        RPGrpModelAnm::Anm_Chr, 6, 60.0f, frame);
                }
            }
            pCtx->subStruct.flag38 = 1;
            pCtx->subStruct.unk_0x14 = lbl_804BF9F4;
        }
        NpcIdleStateSub* pSub = fn_804D2CBC(&pCtx->subStruct);
        pCtx->pos_0x10 = fn_804D5F88(pCtx->movementState, &pCtx->isHoldingBall, NULL, 0.0f,
                                     pCtx->targetZPos) +
                         pSub->pos;
        targetRot = pSub->targetRotation;
        rotSpeed = pSub->rotationSpeed;
        break;
    }
    case 1: {
        if (pCtx->stateFrameCounter == 0) {
            ChangeNpcAnm(pCtx, 7, 30.0f);
        }
        f32 ratio;
        pCtx->pos_0x10 = fn_804D5F88(pCtx->movementState, &pCtx->isHoldingBall, &ratio,
                                     pCtx->stateFrameCounter, pCtx->targetZPos);
        if (pCtx->movementState->mDone) {
            pCtx->triggerTransition = 1;
            ChangeNpcAnm(pCtx, 1, 30.0f);
        } else if (pCtx->isHoldingBall) {
            ChangeNpcAnm(pCtx, 0, 30.0f);
        }
        f32 swing = sin(3.14159f * (0.5f * ratio));
        rotOffset = 360.0f * swing;
        if (!pCtx->flag_A4) {
            rotOffset *= -1.0f;
        }
        if (pCtx->triggerTransition) {
            targetRot = 180.0f;
        } else {
            VEC3 d = pCtx->pos_0x10 - prevPos;
            if (BowAbs(d.x) > 0.0f || BowAbs(d.z) > 0.0f) {
                targetRot = 180.0f * BowAtan2(d.x, d.z) / 3.14159f;
            }
        }
        break;
    }
    case 3: {
        if (pCtx->stateFrameCounter == 0) {
            ChangeNpcAnm(pCtx, 2, 10.0f);
            pCtx->pos_0x10.z = 24.0f;
            pCtx->field_0x3C = (u32)(8.0f * RPUtlRandom::getF32()) + 110;
        }
        if (pCtx->stateFrameCounter == 210) {
            if (pCtx->field_0x4C != 3) {
                pCtx->field_0x4C = 3;
                f32 frame = 0.0f;
                for (int i = 0; i < 2; i++) {
                    pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->Start(RPGrpModelAnm::Anm_Chr, 3,
                                                                        frame);
                }
            }
            pCtx->pos_0x10.z = 4.0499992f;
        }
        if (pCtx->stateFrameCounter > 210) {
            pCtx->triggerTransition = 1;
        }
        if (pCtx->stateFrameCounter == pCtx->field_0x3C) {
            pCtx->triggerThrow = 1;
            pCtx->isHoldingBall = 0;
        }
        targetRot = 180.0f;
        break;
    }
    case 4: {
        if (pCtx->stateFrameCounter == 0) {
            ChangeNpcAnm(pCtx, 4, 30.0f);
            fn_804D5D08(pCtx->movementState, pCtx->pos_0x10);
        }
        if (pCtx->stateFrameCounter == 55) {
            ChangeNpcAnm(pCtx, 5, 10.0f);
        }
        if (pCtx->stateFrameCounter < 65) {
            break;
        }
        if (pCtx->stateFrameCounter == 65) {
            for (int i = 0; i < 2; i++) {
                f32 frame = pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->GetFrame(
                    RPGrpModelAnm::Anm_Chr, 5);
                pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->Start(RPGrpModelAnm::Anm_Chr, 7,
                                                                    frame);
            }
            pCtx->rot_0x1C.y += 180.0f;
        }
        pCtx->pos_0x10 = ogws_fn_803466E4(pCtx->movementState, &pCtx->isHoldingBall,
                                     pCtx->stateFrameCounter - 65, pCtx->targetZPos);
        if (pCtx->movementState->mDone) {
            pCtx->triggerTransition = 1;
            ChangeNpcAnm(pCtx, 1, 30.0f);
        } else if (pCtx->stateFrameCounter > 185) {
            ChangeNpcAnm(pCtx, 0, 30.0f);
        }
        if (pCtx->triggerTransition) {
            targetRot = 180.0f;
        } else {
            VEC3 d = pCtx->pos_0x10 - prevPos;
            if (BowAbs(d.x) > 0.0f || BowAbs(d.z) > 0.0f) {
                targetRot = 180.0f * BowAtan2(d.x, d.z) / 3.14159f;
            }
        }
        if (pCtx->stateFrameCounter < 185) {
            rotSpeed = 0.01f;
        }
        break;
    }
    case 5: {
        int endFrame = 65;
        if (pCtx->flag_A5) {
            endFrame = 131;
        }
        if (pCtx->stateFrameCounter == 0) {
            ChangeNpcAnm(pCtx, 4, 30.0f);
            fn_804D5D08(pCtx->movementState, pCtx->pos_0x10);
        }
        if (pCtx->stateFrameCounter == 55 && pCtx->flag_A5) {
            ChangeNpcAnm(pCtx, 8, 30.0f);
        }
        if (pCtx->flag_A5 && pCtx->stateFrameCounter > 55) {
            smile = 1;
        }
        if (pCtx->stateFrameCounter == endFrame - 10) {
            ChangeNpcAnm(pCtx, 5, 10.0f);
        }
        if (pCtx->stateFrameCounter >= endFrame) {
            if (pCtx->stateFrameCounter == endFrame) {
                for (int i = 0; i < 2; i++) {
                    f32 frame = pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->GetFrame(
                        RPGrpModelAnm::Anm_Chr, 5);
                    pCtx->mpKokeshi[i]->mpBodyModel->mpModelAnm->Start(RPGrpModelAnm::Anm_Chr, 7,
                                                                        frame);
                }
                pCtx->rot_0x1C.y -= 180.0f;
            }
            pCtx->pos_0x10 =
                fn_804D5BD0(pCtx->movementState, pCtx->stateFrameCounter - endFrame);
            if (pCtx->movementState->mDone) {
                pCtx->triggerTransition = 1;
                pCtx->npcState = 0;
                pCtx->stateFrameCounter = -1;
            }
            VEC3 d = pCtx->pos_0x10 - prevPos;
            if (BowAbs(d.x) > 0.0f || BowAbs(d.z) > 0.0f) {
                targetRot = 180.0f * BowAtan2(d.x, d.z) / 3.14159f;
            }
        }
        if (pCtx->stateFrameCounter < endFrame + 120) {
            rotSpeed = 0.01f;
        }
        break;
    }
    }

    pCtx->stateFrameCounter++;

    if (BowAbs(targetRot - pCtx->rot_0x1C.y) > BowAbs(360.0f + targetRot - pCtx->rot_0x1C.y)) {
        targetRot += 360.0f;
    }
    if (BowAbs(targetRot - pCtx->rot_0x1C.y) > BowAbs(targetRot - 360.0f - pCtx->rot_0x1C.y)) {
        targetRot -= 360.0f;
    }
    pCtx->rot_0x1C.y += rotSpeed * (targetRot - pCtx->rot_0x1C.y);

    MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);
    nw4r::math::MTX34Trans(&mtx, &pCtx->pos_0x10, &mtx);

    MTX34 rotMtx;
    nw4r::math::MTX34RotXYZDeg(&rotMtx, pCtx->rot_0x1C.x, pCtx->rot_0x1C.y + rotOffset,
                               pCtx->rot_0x1C.z);
    nw4r::math::MTX34Mult(&mtx, &mtx, &rotMtx);

    VEC3 scale(0.7f, 0.7f, 0.7f);
    MTX34 mirrorMtx = mtx;
    mirrorMtx._10 *= -1.0f;
    mirrorMtx._11 *= -1.0f;
    mirrorMtx._12 *= -1.0f;
    mirrorMtx._13 *= -1.0f;

    RPSysKokeshiManager::ChangeExpression(pCtx->mpKokeshi[0]->mpFaceModel,
                                          smile ? RFLExp_Smile : RFLExp_Normal);

    for (int i = 0; i < 2; i++) {
        MTX34 leftHandMtx;
        MTX34 rightHandMtx;
        MTX34 headMtx;

        if (pCtx->mpKokeshi[i]->mpBodyModel->GetScnObj() != NULL) {
            pCtx->mpKokeshi[i]->mpBodyModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                               i == 0 ? &mtx : &mirrorMtx);
        }
        pCtx->mpKokeshi[i]->mpBodyModel->SetScale(scale);
        pCtx->mpKokeshi[i]->mpBodyModel->UpdateFrame();

        if (pCtx->npcState == 0 && !lbl_804BF9D8) {
            continue;
        }

        pCtx->mpKokeshi[i]->mpBodyModel->Calc();
        pCtx->mpKokeshi[i]->GetHeadJointMtx(reinterpret_cast<EGG::Matrix34f*>(&headMtx));
        pCtx->mpKokeshi[i]->GetLeftHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&leftHandMtx));
        pCtx->mpKokeshi[i]->GetRightHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&rightHandMtx));

        if (i == 0 && pCtx->pos_0x10.z < 47.0f) {
            f32 x = 0.5f * headMtx._03 + 0.25f * leftHandMtx._03 + 0.25f * rightHandMtx._03;
            f32 z = 0.5f * headMtx._23 + 0.25f * leftHandMtx._23 + 0.25f * rightHandMtx._23;
            MTX34 ballMtx = mtx;
            ballMtx._03 = x;
            ballMtx._13 = 0.01f;
            ballMtx._23 = z;
            if (pCtx->mpBallModel->GetScnObj() != NULL) {
                pCtx->mpBallModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &ballMtx);
            }
            pCtx->mpBallModel->SetScale(scale);
            pCtx->mpBallModel->UpdateFrame();
            pCtx->mpBallModel->Calc();
            pCtx->mpBallModel->Entry();

            BowColor color;
            color.b = 0;
            color.g = 0;
            color.r = 0;
            f32 t = 0.6667f * (pCtx->pos_0x10.z - 45.5f);
            if (t > 1.0f) {
                t = 1.0f;
            }
            if (t < 0.0f) {
                t = 0.0f;
            }
            color.a = 60.0f * (1.0f - t);
            fn_80372FD8(pCtx->mpBallModel, 0, 0, color);
        }

        if (!pCtx->flag_A4) {
            MTX34 flipMtx(1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, -1.0f, 0.0f);
            nw4r::math::MTX34Mult(&headMtx, &headMtx, &flipMtx);
            nw4r::math::MTX34Mult(&leftHandMtx, &leftHandMtx, &flipMtx);
            nw4r::math::MTX34Mult(&rightHandMtx, &rightHandMtx, &flipMtx);
        }

        if (i != 0) {
            MTX34 flipMtx(-1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f);
            nw4r::math::MTX34Mult(&headMtx, &headMtx, &flipMtx);
        }

        if (pCtx->mpKokeshi[i]->mpFaceModel->GetScnObj() != NULL) {
            pCtx->mpKokeshi[i]->mpFaceModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                               &headMtx);
        }
        pCtx->mpKokeshi[i]->mpFaceModel->SetScale(scale);
        pCtx->mpKokeshi[i]->mpFaceModel->UpdateFrame();
        pCtx->mpKokeshi[i]->mpFaceModel->Calc();

        if (pCtx->mpKokeshi[i]->mpLeftHandModel->GetScnObj() != NULL) {
            pCtx->mpKokeshi[i]->mpLeftHandModel->GetScnObj()->SetMtx(
                nw4r::g3d::ScnObj::MTX_LOCAL, &leftHandMtx);
        }
        pCtx->mpKokeshi[i]->mpLeftHandModel->SetScale(scale);
        pCtx->mpKokeshi[i]->mpLeftHandModel->UpdateFrame();
        pCtx->mpKokeshi[i]->mpLeftHandModel->Calc();

        if (pCtx->mpKokeshi[i]->mpRightHandModel->GetScnObj() != NULL) {
            pCtx->mpKokeshi[i]->mpRightHandModel->GetScnObj()->SetMtx(
                nw4r::g3d::ScnObj::MTX_LOCAL, &rightHandMtx);
        }
        pCtx->mpKokeshi[i]->mpRightHandModel->SetScale(scale);
        pCtx->mpKokeshi[i]->mpRightHandModel->UpdateFrame();
        pCtx->mpKokeshi[i]->mpRightHandModel->Calc();

        if (i == 1 && !lbl_804BF9D9 && pCtx->pos_0x10.z > 55.0f) {
            continue;
        }

        for (int j = 0; j < 4; j++) {
            RPGrpModel* pModel;
            if (j == 0) {
                pModel = pCtx->mpKokeshi[i]->mpBodyModel;
            }
            if (j == 1) {
                pModel = pCtx->mpKokeshi[i]->mpFaceModel;
            }
            if (j == 2) {
                pModel = pCtx->mpKokeshi[i]->mpLeftHandModel;
            }
            if (j == 3) {
                pModel = pCtx->mpKokeshi[i]->mpRightHandModel;
            }
            EGG::ModelBoundingInfo::SphereShape& rSphere =
                pModel->mpBoundingInfo->getShapeSphere();
            f32 k = (pCtx->field_0x4C == 2 && j == 0) ? 3.0f : 1.0f;
            if (ogws_fn_801C3490(pCull, &rSphere.center, rSphere.r * k)) {
                pModel->Entry();
            }
        }
    }
}

// Vtables of this unit's two NPC helper objects (lbl_803CA700: the 0x1C-byte
// IRPSysHostIOSocket-derived path object built in fn_804D5B28, dtor
// fn_804D5B8C; lbl_803CA714: the object whose dtor is ogws_fn_8033457C). The
// classes are not modelled yet, so the tables are written out as data
// (slot 0 = RTTI, slot 1 = this-offset).
extern "C" {
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void GenMessage__18IRPSysHostIOSocketFv();
void fn_804D471C();
void ogws_fn_80332C2C();
void ogws_fn_80332C60();
void ogws_fn_80316418();

void* lbl_803CA700[] = {
    0, 0, (void*)fn_804D5B8C, (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
};

void* lbl_803CA714[] = {
    0,
    0,
    (void*)ogws_fn_8033457C,
    (void*)fn_804D59D0,
    (void*)fn_804D4824,
    (void*)fn_804D471C,
    (void*)ogws_fn_80316418,
    (void*)ogws_fn_80332C60,
    (void*)ogws_fn_80332C2C,
};
}  // extern "C"

// ---- from ogws RPBow_80332C24.cpp ----
#include <types.h>

namespace Bowling {

// Inferred (name invented): small record with a visibility byte and flag word
struct BowlingEntry {
    u8 pad00[2];
    u8 unk_0x02;   // offset 0x2
    u8 pad03[5];
    u16 mFlags;    // offset 0x8
};

// Inferred (name invented): holds four BowlingEntry pointers at 0xA4..0xB0
struct BowlingEntryTable {
    u8 pad00[0xA4];
    BowlingEntry* mpEntryA4;  // offset 0xA4
    BowlingEntry* mpEntryA8;  // offset 0xA8
    BowlingEntry* mpEntryAC;  // offset 0xAC
    BowlingEntry* mpEntryB0;  // offset 0xB0
};

// Inferred (name invented): object whose second word points to the table
struct BowlingEntryOwner {
    u8 pad00[4];
    BowlingEntryTable* mpTable;  // offset 0x4
    u8 pad08[0x44];
    void* mpUnk_0x4C;            // offset 0x4C
};

extern "C" {

void fn_804D5BCC(void*);

void ogws_fn_80332C60(BowlingEntryOwner* pThis, bool flag) {
    BowlingEntry* pEntry;

    pEntry = pThis->mpTable->mpEntryA8;
    if (flag) {
        pEntry->mFlags |= 1;
    } else {
        pEntry->mFlags &= ~1;
    }
    pEntry = pThis->mpTable->mpEntryA4;
    if (flag) {
        pEntry->mFlags |= 1;
    } else {
        pEntry->mFlags &= ~1;
    }
    pEntry = pThis->mpTable->mpEntryAC;
    if (flag) {
        pEntry->mFlags |= 1;
    } else {
        pEntry->mFlags &= ~1;
    }
    pEntry = pThis->mpTable->mpEntryB0;
    if (flag) {
        pEntry->mFlags |= 1;
    } else {
        pEntry->mFlags &= ~1;
    }
}

void ogws_fn_80332C2C(BowlingEntryOwner* pThis, u8 value) {
    pThis->mpTable->mpEntryA8->unk_0x02 = value;
    pThis->mpTable->mpEntryA4->unk_0x02 = value;
    pThis->mpTable->mpEntryAC->unk_0x02 = value;
    pThis->mpTable->mpEntryB0->unk_0x02 = value;
}

void fn_804D471C(BowlingEntryOwner* pThis) {
    fn_804D5BCC(pThis->mpUnk_0x4C);
}

}

}  // namespace Bowling
