// Resort (RZTE01_01) port of Wii Sports RPBow_8033FD0C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPGraphics/IRPGrpModelCallback.h>
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

class RPGrpModel {
public:
    u8 pad_0x0[0x48];  // fields; vtable at 0x48 (Resort layout)

    BOW_VF(0x8)
    BOW_VF(0xC)
    BOW_VF(0x10)
    BOW_VF(0x14)
    BOW_VF(0x18)
    BOW_VF(0x1C)
    BOW_VF(0x20)
    BOW_VF(0x24)
    BOW_VF(0x28)
    virtual IRPGrpModelCallback* SetCallback(IRPGrpModelCallback* pCallback);  // at 0x2C
    BOW_VF(0x30)
    BOW_VF(0x34)
    BOW_VF(0x38)
    BOW_VF(0x3C)
    BOW_VF(0x40)
    BOW_VF(0x44)
    BOW_VF(0x48)
    BOW_VF(0x4C)
    BOW_VF(0x50)
    virtual nw4r::math::MTX34* ReferWorldMtx(u16 nodeIdx) const;  // at 0x44

    void Unk_801E5D00(const nw4r::math::MTX34* pMtx);
    void UpdateFrame();
    void Calc();
    void Entry();
};

namespace Bowling {

// Inferred (name invented): model pair with per-joint world matrices
class BowJointMtxSet : public RP_DEBUG_STUB_1, public IRPGrpModelCallback {
public:
    RPGrpModel* mpModels[2];         // offset 0x8
    nw4r::math::MTX34 mMtx[100][2];   // offset 0x10
};

}  // namespace Bowling

extern "C" {

using namespace Bowling;

void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);

void fn_804D0C38(BowJointMtxSet* pThis, RPGrpModel* pModel);
BowJointMtxSet* fn_804D0DE4(BowJointMtxSet* pThis, s32 deleteFlag);

#pragma dont_inline on

void ogws_fn_80340304() {}

BowJointMtxSet* fn_804D0E2C(void* pThis, s32 deleteFlag) {
    return fn_804D0DE4((BowJointMtxSet*)((u8*)pThis - 4), deleteFlag);
}

void fn_804D0E24(void* pThis, RPGrpModel* pModel) {
    fn_804D0C38((BowJointMtxSet*)((u8*)pThis - 4), pModel);
}

#pragma dont_inline reset

BowJointMtxSet* fn_804D0DE4(BowJointMtxSet* pThis, s32 deleteFlag) {
    if (pThis) {
        if (deleteFlag > 0) {
            operator delete(pThis);
        }
    }
    return pThis;
}

void fn_804D0D6C(BowJointMtxSet* pThis, RPGrpModel* pModelA, RPGrpModel* pModelB) {
    pThis->mpModels[0] = pModelA;
    pThis->mpModels[1] = pModelB;
    pThis->mpModels[0]->SetCallback(pThis);
    pThis->mpModels[1]->SetCallback(pThis);
}

void fn_804D0D68() {}

void fn_804D0CF8(BowJointMtxSet* pThis) {
    nw4r::math::MTX34 mtx;
    PSMTXIdentity(mtx);
    for (int i = 0; i < 2; i++) {
        pThis->mpModels[i]->Unk_801E5D00(&mtx);
        pThis->mpModels[i]->UpdateFrame();
        pThis->mpModels[i]->Calc();
        pThis->mpModels[i]->Entry();
    }
}

void fn_804D0CF4() {}

void fn_804D0C38(BowJointMtxSet* pThis, RPGrpModel* pModel) {
    for (int i = 0; i < 2; i++) {
        if (pModel == pThis->mpModels[i]) {
            for (u16 j = 0; j < 100; j++) {
                *pModel->ReferWorldMtx(j + 1) = pThis->mMtx[j][i];
            }
        }
    }
}

void fn_804D0AA8(BowJointMtxSet* pThis, int index, const nw4r::math::MTX34* pSrc, f32 y) {
    nw4r::math::MTX34 trans(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -y, 0.0f, 0.0f, 1.0f, 0.0f);
    nw4r::math::MTX34 out1;
    PSMTXConcat(*pSrc, trans, out1);
    pThis->mMtx[index][0] = out1;

    nw4r::math::MTX34 trans2(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -y, 0.0f, 0.0f, 1.0f, 0.0f);
    nw4r::math::MTX34 out2;
    nw4r::math::MTX34 refl = *pSrc;
    refl.m[1][0] *= -1.0f;
    refl.m[1][1] *= -1.0f;
    refl.m[1][2] *= -1.0f;
    refl.m[1][3] *= -1.0f;
    PSMTXConcat(refl, trans2, out2);
    pThis->mMtx[index][1] = out2;
}

void fn_804D09D8(BowJointMtxSet* pThis, int index) {
    for (; index < 100; index++) {
        pThis->mMtx[index][0] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, 0.0f);
        pThis->mMtx[index][1] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, 0.0f);
    }
}

}  // extern "C"

// Vtable of BowJointMtxSet (primary + IRPGrpModelCallback thunks), written as a
// data table under its address label: the class is not modelled with its virtual list yet.
extern "C" {
void fn_804C7B60();
void fn_804C7D14();
void fn_804C7D10();
void fn_801E687C();
void fn_801E6880();
void fn_801D75DC();

void* lbl_806DEA88[18] = {
    0,
    0,
    (void*)fn_804D0DE4,
    (void*)fn_804D0D68,
    (void*)fn_804D0CF8,
    (void*)fn_804D0CF4,
    (void*)fn_804C7B60,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
    0,
    (void*)fn_804D0E2C,
    (void*)fn_801E687C,
    (void*)fn_801E6880,
    (void*)fn_804D0E24,
    (void*)fn_801D75DC,
    (void*)fn_804D0C38,
    0,
};
}  // extern "C"
