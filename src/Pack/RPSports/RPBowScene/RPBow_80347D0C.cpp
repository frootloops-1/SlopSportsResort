// Resort (RZTE01_01) port of Wii Sports RPBow_80347D0C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPKernel/RP_DEBUG_STUB_1.h>
#include <nw4r/math/math_types.h>

// Minimal local views: the full nw4r::g3d / RPGrpModel headers pull unrelated
// pool data into .sdata2.
namespace nw4r {
namespace g3d {
class ScnObj {
public:
    enum ScnObjMtxType { MTX_LOCAL, MTX_WORLD, MTX_VIEW, MTX_TYPE_MAX };
    bool SetMtx(ScnObjMtxType type, const math::MTX34* pMtx);
};
}  // namespace g3d
}  // namespace nw4r

struct BowModelEx {
    u8 pad_0x0[0x8];
    nw4r::g3d::ScnObj* mpScnObj;  // offset 0x8
};

#define BOW_VF(n) virtual void VF_##n() {}

// Inferred (name invented): animation object driven through virtual calls
class BowAnmObj {
public:
    u8 pad_0x0[0x78];
    BOW_VF(0x8)
    BOW_VF(0xC)
    BOW_VF(0x10)
    BOW_VF(0x14)
    BOW_VF(0x18)
    BOW_VF(0x1C)
    BOW_VF(0x20)
    BOW_VF(0x24)
    BOW_VF(0x28)
    BOW_VF(0x2C)
    BOW_VF(0x30)
    BOW_VF(0x34)
    BOW_VF(0x38)
    BOW_VF(0x3C)
    BOW_VF(0x40)
    BOW_VF(0x44)
    BOW_VF(0x48)
    BOW_VF(0x4C)
    virtual void VF_0x50(int, int, f32) {}
    BOW_VF(0x54)
    virtual void VF_0x58(int, int, f32) {}
    BOW_VF(0x5C)
    BOW_VF(0x60)
    BOW_VF(0x64)
    virtual void VF_0x68(int, int, f32) {}
};

class RPGrpModel {
public:
    u8 pad_0x0[0x40];
    BowAnmObj* mpAnm;  // offset 0x40
    void Unk_801E5D00(const nw4r::math::MTX34* pMtx);
    void UpdateFrame();
    void Calc();
    void Entry();
};

namespace Bowling {

// Inferred (name invented): two models (real and reflection) driven by a
// matrix and a frame counter stepping through a table of thresholds
class BowFrameModel : public RP_DEBUG_STUB_1 {
public:
    RPGrpModel* mpModels[2];  // offset 0x4
    nw4r::math::MTX34 mMtx;   // offset 0xC
    s32 mIndex;               // offset 0x3C
    s32 mTarget;              // offset 0x40
    f32 mField44;             // offset 0x44
    f32 mFrame;               // offset 0x48
};

}  // namespace Bowling

extern "C" {

using namespace Bowling;

u8 lbl_806F5968;
u8 lbl_806F5969;

double __fabs(double);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);

BowFrameModel* fn_804D1CDC(BowFrameModel* pThis, s32 deleteFlag) {
    if (pThis) {
        if (deleteFlag > 0) {
            operator delete(pThis);
        }
    }
    return pThis;
}

void fn_804D1CD0(BowFrameModel* pThis, RPGrpModel* pModelA, RPGrpModel* pModelB) {
    pThis->mpModels[0] = pModelA;
    pThis->mpModels[1] = pModelB;
}

void fn_804D1C18(BowFrameModel* pThis) {
    for (int i = 0; i < 2; i++) {
        pThis->mpModels[i]->mpAnm->VF_0x68(0, 0, 0.0f);
        pThis->mpModels[i]->mpAnm->VF_0x58(0, 0, 0.0f);
    }
    pThis->mIndex = 0;
    pThis->mTarget = 0;
    pThis->mField44 = -175.0f;
    pThis->mFrame = 0.0f;
    lbl_806F5968 = 0;
    lbl_806F5969 = 0;
}

void fn_804D1BC0(BowFrameModel* pThis, f32 x, f32 z) {
    f32 pos[3];
    pos[0] = x;
    pos[1] = 0.0f;
    pos[2] = z;
    PSMTXIdentity(pThis->mMtx);
    PSMTXTransApply(pThis->mMtx, pThis->mMtx, pos[0], pos[1], pos[2]);
}

void fn_804D19AC(BowFrameModel* pThis) {
    struct Pair {
        f32 a;
        f32 b;
    };
    Pair table[4] = {{0.0f, 0.0f}, {0.0f, 51.0f}, {75.0f, 250.0f}, {250.0f, 505.0f}};
    bool reached = false;
    if (pThis->mFrame < table[pThis->mIndex].b) {
        pThis->mFrame += 1.0f;
    } else {
        pThis->mFrame = table[pThis->mIndex].b;
        reached = true;
    }
    if (pThis->mIndex != pThis->mTarget && reached) {
        pThis->mIndex = pThis->mTarget;
        pThis->mFrame = table[pThis->mTarget].a;
    }
    if (!lbl_806F5968 && (pThis->mFrame < 0.1f || pThis->mFrame > 504.0f)) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        pThis->mpModels[i]->mpAnm->VF_0x50(0, 0, pThis->mFrame);
    }
    nw4r::math::MTX34 mtx = pThis->mMtx;
    pThis->mpModels[0]->Unk_801E5D00(&mtx);
    pThis->mpModels[0]->UpdateFrame();
    pThis->mpModels[0]->Calc();
    nw4r::math::MTX34 refl = mtx;
    refl.m[1][0] *= -1.0f;
    refl.m[1][1] *= -1.0f;
    refl.m[1][2] *= -1.0f;
    refl.m[1][3] *= -1.0f;
    pThis->mpModels[1]->Unk_801E5D00(&refl);
    pThis->mpModels[1]->UpdateFrame();
    pThis->mpModels[1]->Calc();
    pThis->mpModels[1]->Entry();
    if (!((f32)__fabs(pThis->mMtx.m[0][3]) < 0.1f) || !lbl_806F5969) {
        pThis->mpModels[0]->Entry();
    }
}

void fn_804D19A8() {}

// MATCH-PENDING (R17): vtable of the (unmodelled) BowFrameModel class, hand-defined as an array
// (ledger 269): dtor fn_804D1CDC, fn_804D1C18, fn_804D19AC, fn_804D19A8 and three base slots.
void fn_804C7B60();
void fn_804C7D14();
void fn_804C7D10();

void* lbl_806DEB30[10] = {
    0,
    0,
    (void*)fn_804D1CDC,
    (void*)fn_804D1C18,
    (void*)fn_804D19AC,
    (void*)fn_804D19A8,
    (void*)fn_804C7B60,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
};

}  // extern "C"
