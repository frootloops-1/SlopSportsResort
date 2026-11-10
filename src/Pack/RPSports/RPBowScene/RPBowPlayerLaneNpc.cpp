// Resort (RZTE01_01) port of Wii Sports RPBowPlayerLaneNpc.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPUtility/RPUtlRandom.h>
#include <nw4r/math/math_types.h>
#include <Pack/RPKernel/RPSysController.h>
#include <egg/core.h>

using nw4r::math::MTX34;
using nw4r::math::VEC3;

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
    virtual void VF_0x38();
    virtual void VF_0x3C();
    virtual bool Start(Anm anm, u16 idx, f32 frame);  // at 0x40
    virtual void VF_0x44();
    virtual void VF_0x48();
    virtual int GetNumFrame(Anm anm, u16 idx) const;  // at 0x4C
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
    VEC3 mBaseScale;            // offset 0x20
    RPGrpModelAnm* mpModelAnm;  // offset 0x2C
    u8 pad_0x30[0x10];
    BowModelEx* mpModelEx;      // offset 0x40

    nw4r::g3d::ScnObj* GetScnObj() const {
        return mpModelEx->mpScnObj;
    }
    void SetScale(const VEC3& rScale) {
        mBaseScale = rScale;
    }

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

namespace Bowling {

// Minimal view (bowling.h)
struct NpcIdleStateSub {
    int idleState;         // offset 0x0
    int frameCounter;      // offset 0x4
    int unk_0x8;           // offset 0x8
    f32 targetRotation;    // offset 0xC
    f32 rotationSpeed;     // offset 0x10
    VEC3 pos;              // offset 0x14
};

// Minimal view (bowling.h): IRPSysHostIOSocket base plus state
struct NpcIdleState {
    void* vptr;           // offset 0x0
    u8 pad_0x4[0x44];
};

void fn_804D338C(NpcIdleState* pIdleState, int param_2, int param_3);
NpcIdleStateSub* fn_804D2CBC(NpcIdleState* pIdleState);

// Inferred (name invented): view of RPBowPlayerLaneNpc
struct LaneNpc {
    void* vptr;                   // offset 0x0
    u8 socket[4];                 // offset 0x4 (IRPSysHostIOSocket)
    RPSysKokeshi* mKokeshis[2];   // offset 0x8
    u32 unk10;                    // offset 0x10 (Resort)
    u32 index;                    // offset 0x14
    VEC3 pos;                     // offset 0x18
    VEC3 rot;                     // offset 0x24
    u8 isVisible;                 // offset 0x30
    u8 pad_0x31[0x3];
    NpcIdleState npcIdleState;    // offset 0x34
};

// Inferred (name invented): per-player controller wrapper
struct BowCtrl {
    s32 mId;         // offset 0x0
    s32 mChannel;    // offset 0x4
    bool mEnabled;   // offset 0x8
    bool mArmed;     // offset 0x9
    u8 pad_0xA[2];
    s32 mButtons[4]; // offset 0xC

    EGG::CoreController* GetCtrl() const {
        return Get(mChannel);
    }
    int GetReadLength() const {
        return GetCtrl()->getReadLength();
    }
    static EGG::CoreController* Get(int ch) {
        return EGG::CoreControllerMgr::instance()->getNthController(ch);
    }
};

}  // namespace Bowling

// Inferred (name invented): channel mapper stored in .sbss
struct ChannelMap;

extern "C" {

using namespace Bowling;

extern VEC3 lbl_804BD270[4];
u8 lbl_804BF9E0;

double __fabs(double);

static inline f32 BowAbs(f32 x) {
    return __fabs(x);
}

void __dt__18IRPSysHostIOSocketFv(void*, s32);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);

extern ChannelMap* lbl_804BF740;

int ogws_fn_801F93C4(ChannelMap* pMap, int id);
int ogws_fn_801F9390(ChannelMap* pMap, int id);
void ogws_fn_801F8360(int arg0, int arg1);
int ogws_fn_801F841C(int arg0);

LaneNpc* ogws_fn_803474F4(LaneNpc* pThis, s32 deleteFlag);
void ogws_fn_80347574();

#pragma force_active on
__declspec(section ".ctors") static void (*bowInit80347574)(void) = ogws_fn_80347574;
#pragma force_active reset

void ogws_fn_80347D08() {}

void ogws_fn_80347CF8(BowCtrl* pThis) {
    pThis->mId = 0;
    pThis->mChannel = 0;
}

void ogws_fn_80347C9C(BowCtrl* pThis, int id) {
    pThis->mId = id;
    pThis->mEnabled = true;
    pThis->mArmed = false;
    if (lbl_804BF740) {
        pThis->mChannel = ogws_fn_801F93C4(lbl_804BF740, id);
    } else {
        pThis->mChannel = id;
    }
}

void ogws_fn_80347BA8(BowCtrl* pThis) {
    for (int i = 0; i < 4; i++) {
        int ch = ogws_fn_801F93C4(lbl_804BF740, i);
        pThis->mButtons[i] = i;
        if (EGG::CoreControllerMgr::instance()->getNthController(ch)->down(0x8)) {
            pThis->mButtons[i] = 0;
        }
        if (EGG::CoreControllerMgr::instance()->getNthController(ch)->down(0x1)) {
            pThis->mButtons[i] = 1;
        }
        if (EGG::CoreControllerMgr::instance()->getNthController(ch)->down(0x4)) {
            pThis->mButtons[i] = 2;
        }
        if (EGG::CoreControllerMgr::instance()->getNthController(ch)->down(0x2)) {
            pThis->mButtons[i] = 3;
        }
        if (ogws_fn_801F841C(ogws_fn_801F9390(lbl_804BF740, i))) {
            pThis->mButtons[i] += 4;
        }
    }
}

void fn_804D6C70(BowCtrl* pThis) {
    if (lbl_804BF740) {
        pThis->mChannel = ogws_fn_801F93C4(lbl_804BF740, pThis->mId);
    } else {
        pThis->mChannel = pThis->mId;
    }
}

int ogws_fn_80347B0C(BowCtrl* pThis) {
    int ch = pThis->mChannel;
    if (ch == 0) {
        return 1;
    }
    if (ch == 1) {
        return 2;
    }
    if (ch == 2) {
        return 4;
    }
    return ch == 3 ? 8 : 0;
}

bool ogws_fn_80347AC4(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->downTrigger(0x800);
}

bool ogws_fn_80347AB4() {
    return RPSysCoreController::spActiveController->downTrigger(0x800);
}

void ogws_fn_80347A80(BowCtrl* pThis) {
    ogws_fn_801F8360(ogws_fn_801F9390(lbl_804BF740, pThis->mId), 0);
}

bool ogws_fn_80347A38(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->downTrigger(0x800);
}

void fn_804E7B54(BowCtrl* pThis) {
    pThis->mArmed = false;
}

bool fn_804E7A80(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    if (!pThis->mArmed) {
        if (!pThis->GetCtrl()->down(0x400)) {
            pThis->mArmed = true;
        }
        return false;
    }
    return pThis->GetCtrl()->down(0x400);
}

bool ogws_fn_80347960(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->downTrigger(0x400);
}

bool ogws_fn_803478E0(const BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    bool result = true;
    if (!pThis->GetCtrl()->downTrigger(0x200) && !pThis->GetCtrl()->downTrigger(0x100)) {
        result = false;
    }
    return result;
}

bool ogws_fn_80347898(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->down(0x8);
}

bool ogws_fn_80347850(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->downTrigger(0x8);
}

bool ogws_fn_80347808(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->down(0x4);
}

bool ogws_fn_803477C0(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->down(0x1);
}

bool ogws_fn_80347778(BowCtrl* pThis) {
    if (!pThis->mEnabled) {
        return false;
    }
    return pThis->GetCtrl()->down(0x2);
}

void fn_804E76A0(BowCtrl* pThis, f32 a, f32 b) {
    pThis->GetCtrl()->setAccParam(a, b);
}

extern "C" void* sInstance__Q23EGG17CoreControllerMgr;
extern "C" EGG::CoreController* getNthController__Q23EGG17CoreControllerMgrFi(void*, int);
int fn_804D6C24(const BowCtrl* pThis) {
    return getNthController__Q23EGG17CoreControllerMgrFi(sInstance__Q23EGG17CoreControllerMgr, pThis->mChannel)->getReadLength();
}

EGG::Vector3f ogws_fn_80347638(const BowCtrl* pThis, int index) {
    f32 x, y, z;
    z = pThis->GetCtrl()->getCoreStatus(index)->acc.z;
    y = pThis->GetCtrl()->getCoreStatus(index)->acc.y;
    x = pThis->GetCtrl()->getCoreStatus(index)->acc.x;
    return EGG::Vector3f(x, y, z);
}

void fn_801D2F8C(BowCtrl* pThis, f32 power, int frame) {
    pThis->GetCtrl()->startPowerFrameRumble(power, frame, false);
}

// Compiler-generated destructor thunk (IRPSysHostIOSocket base at 0x4); never inlined
#pragma push
#pragma dont_inline on
void ogws_fn_803475DC(void* pThis, s32 deleteFlag) {
    ogws_fn_803474F4(reinterpret_cast<LaneNpc*>((u8*)pThis - 4), deleteFlag);
}
#pragma pop

void ogws_fn_80347574() {
    lbl_804BD270[0].x = -4.5f;
    lbl_804BD270[0].y = 0.0f;
    lbl_804BD270[0].z = 53.0f;
    lbl_804BD270[1].x = -3.0f;
    lbl_804BD270[1].y = -0.5f;
    lbl_804BD270[1].z = 60.0f;
    lbl_804BD270[2].x = -0.7f;
    lbl_804BD270[2].y = -1.0f;
    lbl_804BD270[2].z = 70.0f;
    lbl_804BD270[3].x = 6.0f;
    lbl_804BD270[3].y = -1.0f;
    lbl_804BD270[3].z = 72.0f;
}

LaneNpc* ogws_fn_803474F4(LaneNpc* pThis, s32 deleteFlag) {
    if (pThis) {
        NpcIdleState* pState = &pThis->npcIdleState;
        if (pState) {
            __dt__18IRPSysHostIOSocketFv(pState, 0);
        }
        __dt__18IRPSysHostIOSocketFv(pThis->socket, 0);
        if (pThis) {
            __dt__15RP_DEBUG_STUB_1Fv(pThis, 0);
        }
        if (deleteFlag > 0) {
            operator delete(pThis);
        }
    }
    return pThis;
}

void ogws_fn_803474E4(LaneNpc* pThis, RPSysKokeshi* pKokeshi0, RPSysKokeshi* pKokeshi1, u32 index) {
    pThis->mKokeshis[0] = pKokeshi0;
    pThis->mKokeshis[1] = pKokeshi1;
    pThis->index = index;
}

void fn_804D6B94(LaneNpc* pThis) {
    f32 table[4][2] = {{0.0f, 55.0f}, {0.0f, 61.0f}, {0.0f, 68.0f}, {-4.0f, 74.0f}};
    VEC3 pos(-table[pThis->index][0], 0.0f, table[pThis->index][1]);
    pThis->pos = pos;
    VEC3 rot(0.0f, 180.0f, 0.0f);
    pThis->rot = rot;
}

void fn_804D6A40(LaneNpc* pThis) {
    RPGrpModelAnm* pAnm = pThis->mKokeshis[0]->mpBodyModel->mpModelAnm;
    f32 frame = RPUtlRandom::getF32() * pAnm->GetNumFrame(RPGrpModelAnm::Anm_Chr, 0);

    for (int i = 0; i < 2; i++) {
        pThis->mKokeshis[i]->mpBodyModel->mpModelAnm->Start(RPGrpModelAnm::Anm_Chr, 0, frame);
    }

    pThis->isVisible = 0;
    fn_804D338C(&pThis->npcIdleState, 0, pThis->index);
    lbl_804BF9E0 = 1;
}

void fn_804D65D8(LaneNpc* pThis) {
    NpcIdleStateSub* pSub = fn_804D2CBC(&pThis->npcIdleState);
    pThis->pos = lbl_804BD270[pThis->index] + pSub->pos;

    f32 target = pSub->targetRotation;
    f32 speed = pSub->rotationSpeed;
    if (BowAbs(target - pThis->rot.y) > BowAbs(360.0f + target - pThis->rot.y)) {
        target += 360.0f;
    }
    if (BowAbs(target - pThis->rot.y) > BowAbs(target - 360.0f - pThis->rot.y)) {
        target -= 360.0f;
    }
    pThis->rot.y += speed * (target - pThis->rot.y);

    MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);
    nw4r::math::MTX34Trans(&mtx, &pThis->pos, &mtx);

    MTX34 rotMtx;
    nw4r::math::MTX34RotXYZDeg(&rotMtx, pThis->rot.x, pThis->rot.y, pThis->rot.z);
    nw4r::math::MTX34Mult(&mtx, &mtx, &rotMtx);

    VEC3 scale(0.7f, 0.7f, 0.7f);
    MTX34 mirrorMtx = mtx;
    mirrorMtx._10 *= -1.0f;
    mirrorMtx._11 *= -1.0f;
    mirrorMtx._12 *= -1.0f;
    mirrorMtx._13 *= -1.0f;

    for (int i = 0; i < 2; i++) {
        MTX34 leftHandMtx;
        MTX34 rightHandMtx;
        MTX34 headMtx;

        if (pThis->mKokeshis[i]->mpBodyModel->GetScnObj() != NULL) {
            pThis->mKokeshis[i]->mpBodyModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL,
                                                               i == 0 ? &mtx : &mirrorMtx);
        }
        pThis->mKokeshis[i]->mpBodyModel->SetScale(scale);
        pThis->mKokeshis[i]->mpBodyModel->UpdateFrame();

        if (!pThis->isVisible) {
            continue;
        }

        pThis->mKokeshis[i]->mpBodyModel->Calc();

        pThis->mKokeshis[i]->GetHeadJointMtx(reinterpret_cast<EGG::Matrix34f*>(&headMtx));
        pThis->mKokeshis[i]->GetLeftHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&leftHandMtx));
        pThis->mKokeshis[i]->GetRightHandJointMtx(reinterpret_cast<EGG::Matrix34f*>(&rightHandMtx));

        if (i != 0) {
            MTX34 flipMtx(
               -1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f
            );
            nw4r::math::MTX34Mult(&headMtx, &headMtx, &flipMtx);
        }

        if (pThis->mKokeshis[i]->mpFaceModel->GetScnObj() != NULL) {
            pThis->mKokeshis[i]->mpFaceModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &headMtx);
        }
        pThis->mKokeshis[i]->mpFaceModel->SetScale(scale);
        pThis->mKokeshis[i]->mpFaceModel->UpdateFrame();
        pThis->mKokeshis[i]->mpFaceModel->Calc();

        if (pThis->mKokeshis[i]->mpLeftHandModel->GetScnObj() != NULL) {
            pThis->mKokeshis[i]->mpLeftHandModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &leftHandMtx);
        }
        pThis->mKokeshis[i]->mpLeftHandModel->SetScale(scale);
        pThis->mKokeshis[i]->mpLeftHandModel->UpdateFrame();
        pThis->mKokeshis[i]->mpLeftHandModel->Calc();

        if (pThis->mKokeshis[i]->mpRightHandModel->GetScnObj() != NULL) {
            pThis->mKokeshis[i]->mpRightHandModel->GetScnObj()->SetMtx(nw4r::g3d::ScnObj::MTX_LOCAL, &rightHandMtx);
        }
        pThis->mKokeshis[i]->mpRightHandModel->SetScale(scale);
        pThis->mKokeshis[i]->mpRightHandModel->UpdateFrame();
        pThis->mKokeshis[i]->mpRightHandModel->Calc();

        if (i == 1 && !lbl_804BF9E0) {
            continue;
        }

        pThis->mKokeshis[i]->mpBodyModel->Entry();
        pThis->mKokeshis[i]->mpFaceModel->Entry();
        pThis->mKokeshis[i]->mpLeftHandModel->Entry();
        pThis->mKokeshis[i]->mpRightHandModel->Entry();
    }
}

// MATCH-PENDING (R17): vtable of the (unmodelled) LaneNpc class, hand-defined as an array (ledger 268):
// primary part (dtor ogws_fn_803474F4, fn_804D6B94, fn_804D65D8, fn_804D65D4, three base slots) followed by the
// IRPSysHostIOSocket secondary part (thunk ogws_fn_803475DC).
void fn_804D65D4();
void ogws_fn_80316418();
void fn_804C7D14();
void fn_804C7D10();
void ListenPropertyEvent__18IRPSysHostIOSocketFv();
void GenMessage__18IRPSysHostIOSocketFv();

void* lbl_803CA8B0[14] = {
    0,
    0,
    (void*)ogws_fn_803474F4,
    (void*)fn_804D6B94,
    (void*)fn_804D65D8,
    (void*)fn_804D65D4,
    (void*)ogws_fn_80316418,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
    0,
    (void*)ogws_fn_803475DC,
    (void*)ListenPropertyEvent__18IRPSysHostIOSocketFv,
    (void*)GenMessage__18IRPSysHostIOSocketFv,
};

}
