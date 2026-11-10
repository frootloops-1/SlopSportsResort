// Resort (RZTE01_01) port of Wii Sports RPBow_8034E974.cpp (ogws source, CC0).
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
    virtual void VF_0x18(int);
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
    virtual nw4r::math::MTX34* ReferWorldMtx(u16 nodeIdx) const;  // at 0x54

    void Unk_801E5D00(const nw4r::math::MTX34* pMtx);
    void UpdateFrame();
    void Calc();
    void Entry();
};

extern "C" {
void system_halt(const char*, int, const char*, ...);
extern u8 lbl_806F5960;
extern s32 lbl_806F5948;
f32 fn_804C485C(s32);
void fn_8024E34C(RPGrpModel*, u32);
extern const char lbl_803C5428[];
extern const char lbl_803C5418[];
}

// Inferred (name invented): minimal view of RPGrpShadowTexture
class RPGrpShadowTexture {
public:
    u8 pad_0x0[0x70];
    f32 mRadius;  // offset 0x70 (Resort)
    void SetRadius(f32 radius) {
        mRadius = radius;
    }
    void AddModel(RPGrpModel* pModel, f32 scale);
};

// Inferred (name invented): object driven through virtual calls by the slot set
struct BowSlotObj {
    virtual void VF_0x8() {}
    virtual void VF_0xC() {}
    virtual void VF_0x10() {}
    virtual void VF_0x14() {}
    virtual void VF_0x18() {}
    virtual void VF_0x1C() {}
    virtual void VF_0x20() {}
    virtual void VF_0x24(int arg);
    virtual int VF_0x28();
    virtual bool VF_0x2C();
};

struct BowSlotInfo {
    u8 pad_0x0[0x34];
    u8 mFlag34;  // offset 0x34
};

// Inferred (name invented): array of twelve-byte slots starting at offset 0xC
struct BowSlot {
    BowSlotObj* mpObj;  // offset 0x0
    u8 mActive;         // offset 0x4
    u8 mStarted;        // offset 0x5
    u8 pad_0x6[2];
    s32 mCount;         // offset 0x8
    bool Check() { return mpObj->VF_0x2C(); }
};

struct BowSlotSet {
    u8 pad_0x0[0xC];
    BowSlot mSlots[16];   // offset 0xC
    u8 pad_0xCC[0xF0 - 0xCC];
    BowSlotInfo* mpInfo;  // offset 0xF0
    s32 mCurrent;         // offset 0xF4
    u8 pad_0xF8[8];
    s32 mFlag100;         // offset 0x100
};

namespace Bowling {

// Inferred (name invented): two models (real and reflection) with ten pin
// matrix pairs and a shadow texture
class BowPinMtxSet : public RP_DEBUG_STUB_1, public IRPGrpModelCallback {
public:
    RPGrpModel* mpModels[2];          // offset 0x8
    RPGrpModel* mpModel2;             // offset 0x10 (Resort)
    nw4r::math::MTX34 mMtx[10][2];    // offset 0x14
    RPGrpShadowTexture* mpShadow;     // offset 0x3D4
    s32 mShadowAdded;                 // offset 0x3D8
};

}  // namespace Bowling

extern "C" {

using namespace Bowling;

bool fn_80372C18(const nw4r::math::MTX34* pCullMtx, const nw4r::math::VEC3* pPos, f32 radius);
void __dt__15RP_DEBUG_STUB_1Fv(void*, s32);

BowPinMtxSet* fn_804D0988(BowPinMtxSet* pThis, s32 deleteFlag);
void fn_804D03F4(BowPinMtxSet* pThis, RPGrpModel* pModel);

void ogws_fn_8034F6A0(BowSlotSet* pThis, int index, int arg) {
    if (index == 0) {
        if (arg != 0 && !pThis->mSlots[index].mStarted) {
            pThis->mFlag100 = 1;
        }
        if (arg == 0 || pThis->mpInfo->mFlag34 == 0) {
            pThis->mFlag100 = 0;
        }
    }
    pThis->mSlots[index].mActive = arg;
    if (arg == 0) {
        return;
    }
    pThis->mSlots[index].mStarted = 1;
    pThis->mCurrent = index;
}

int ogws_fn_8034F570(BowSlotSet* pThis, int arg) {
    int order[4] = {2, 13, 14, 15};
    for (u32 i = 0; i < 4; i++) {
        int k = order[i];
        if (pThis->mSlots[k].mStarted && pThis->mSlots[k].mpObj->VF_0x28() && pThis->mSlots[k].mCount > 0) {
            if (k == 0) {
                pThis->mFlag100 = 0;
            }
            pThis->mSlots[k].mActive = 0;
            pThis->mSlots[k].mpObj->VF_0x24(0);
            pThis->mSlots[k].mStarted = 0;
            return 1;
        }
        if (k == arg) {
            return 0;
        }
    }
    if (arg != -1) {
        return !pThis->mSlots[arg].mStarted;
    }
    return !pThis->mSlots[pThis->mCurrent].mStarted;
}

// The trailing blr after the bctr tail call is MWCC's dead exit block, not a
// separate function: symbols.txt's 4-byte ogws_fn_8034F56C at 0x8034F56C belongs to this one.
bool ogws_fn_8034F53C(BowSlotSet* pThis) {
    if (pThis->mCurrent == -1) {
        return true;
    } else {
        return pThis->mSlots[pThis->mCurrent].mpObj->VF_0x2C();
    }
}

#pragma dont_inline on

BowPinMtxSet* fn_804D09D0(void* pThis, s32 deleteFlag) {
    return fn_804D0988((BowPinMtxSet*)((u8*)pThis - 4), deleteFlag);
}

void fn_804D09C8(void* pThis, RPGrpModel* pModel) {
    fn_804D03F4((BowPinMtxSet*)((u8*)pThis - 4), pModel);
}

#pragma dont_inline reset

BowPinMtxSet* fn_804D0988(BowPinMtxSet* pThis, s32 deleteFlag) {
    if (pThis) {
        if (deleteFlag > 0) {
            operator delete(pThis);
        }
    }
    return pThis;
}

void fn_804D08F4(BowPinMtxSet* pThis, RPGrpModel* pModelA, RPGrpModel* pModelB) {
    pThis->mpModels[0] = pModelA;
    pThis->mpModels[1] = pModelB;
    pThis->mpModels[0]->SetCallback(pThis);
    if (pThis->mpModels[1] != NULL) {
        pThis->mpModels[1]->SetCallback(pThis);
    }
    fn_8024E34C(pThis->mpModels[0], 1);
    pThis->mpModel2 = NULL;
}

void fn_804D08E4(BowPinMtxSet* pThis, RPGrpModel* pModel) {
    pThis->mpModel2 = pModel;
    fn_8024E34C(pModel, 1);
}

void fn_804D08D8() {
    lbl_806F5960 = 0;
}

void ogws_fn_8034F440() {}

void fn_804D0574(BowPinMtxSet* pThis) {
    nw4r::math::MTX34 mtx;
    int useAlt = 0;
    if (pThis->mpModel2 != NULL) {
        if (fn_804C485C(lbl_806F5948) > 0.0f) {
            useAlt = 1;
        }
    }
    PSMTXIdentity(mtx);
    if (pThis->mShadowAdded == 0) {
        if (useAlt) {
            pThis->mpShadow->AddModel(pThis->mpModel2, 1.0f);
        } else {
            pThis->mpShadow->AddModel(pThis->mpModels[0], 1.0f);
        }
        nw4r::math::VEC3 minV(0.0f, 0.0f, 0.0f);
        nw4r::math::VEC3 maxV(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < 10; i++) {
            nw4r::math::VEC3 p(pThis->mMtx[i][0].m[0][3], pThis->mMtx[i][0].m[1][3],
                               pThis->mMtx[i][0].m[2][3]);
            if (i == 0 || minV.x > p.x) minV.x = p.x;
            if (i == 0 || minV.y > p.y) minV.y = p.y;
            if (i == 0 || minV.z > p.z) minV.z = p.z;
            if (i == 0 || maxV.x < p.x) maxV.x = p.x;
            if (i == 0 || maxV.y < p.y) maxV.y = p.y;
            if (i == 0 || maxV.z < p.z) maxV.z = p.z;
        }
        nw4r::math::VEC3 center = (minV + maxV) * 0.5f;
        f32 maxDist = 0.0f;
        for (int i = 0; i < 10; i++) {
            nw4r::math::VEC3 diff = nw4r::math::VEC3(pThis->mMtx[i][0].m[0][3],
                                                     pThis->mMtx[i][0].m[1][3],
                                                     pThis->mMtx[i][0].m[2][3]) -
                                    center;
            f32 d = PSVECMag(diff);
            if (maxDist < d) maxDist = d;
        }
        pThis->mpShadow->SetRadius((maxDist + 4.0f) / 2.0f);
        mtx.m[0][3] = center.x;
        mtx.m[1][3] = center.y;
        mtx.m[2][3] = center.z;
    }
    for (int i = 0; i < 2; i++) {
        if (pThis->mpModels[i] != NULL && (i != 0 || !useAlt)) {
            pThis->mpModels[i]->Unk_801E5D00(&mtx);
            pThis->mpModels[i]->UpdateFrame();
            pThis->mpModels[i]->Calc();
            pThis->mpModels[i]->Entry();
        }
    }
    if (useAlt) {
        pThis->mpModel2->VF_0x18(2);
        pThis->mpModel2->SetCallback(pThis);
        pThis->mpModel2->Unk_801E5D00(&mtx);
        pThis->mpModel2->UpdateFrame();
        pThis->mpModel2->Calc();
        pThis->mpModel2->Entry();
    }
}

void fn_804D0570() {}

void fn_804D03F4(BowPinMtxSet* pThis, RPGrpModel* pModel) {
    for (int i = 0; i < 2; i++) {
        if (pModel == pThis->mpModels[i]) {
            for (u16 j = 0; j < 10; j++) {
                *pModel->ReferWorldMtx(j + 1) = pThis->mMtx[j][i];
            }
        }
    }
    if (pModel == pThis->mpModel2) {
        for (u16 j = 0; j < 10; j++) {
            nw4r::math::MTX34 m;
            PSMTXIdentity(m);
            nw4r::math::VEC3 scale(1.0f, 1.0f, 1.0f);
            PSMTXScaleApply(m, m, scale.x, scale.y, scale.z);
            PSMTXConcat(pThis->mMtx[j][0], m, m);
            *pModel->ReferWorldMtx(j + 1) = m;
        }
    }
}

void fn_804CFFB8__7BowlingFPviPQ34nw4r4math5MTX34PQ34nw4r4math5MTX34b(
    void* pArg, int index, const nw4r::math::MTX34* pCullMtx, const nw4r::math::MTX34* pSrc,
    bool skipAdjust, f32 y) {
    BowPinMtxSet* pThis = (BowPinMtxSet*)pArg;
    nw4r::math::MTX34 trans(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -y, 0.0f, 0.0f, 1.0f, 0.0f);
    nw4r::math::MTX34 out1;
    PSMTXConcat(*pSrc, trans, out1);
    nw4r::math::VEC3 t;
    nw4r::math::VEC3 pos1(out1.m[0][3], out1.m[1][3], out1.m[2][3]);
    if (!fn_80372C18(pCullMtx, &pos1, 4.0f) && !lbl_806F5960) {
        pThis->mMtx[index][0] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, -193.0f);
    } else {
        pThis->mMtx[index][0] = out1;
    }

    if (pSrc->m[2][3] < -196.0f) {
        pThis->mMtx[index][1] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, -193.0f);
        return;
    }

    nw4r::math::MTX34 trans2(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -y, 0.0f, 0.0f, 1.0f, 0.0f);
    nw4r::math::MTX34 out2;
    nw4r::math::MTX34 refl = *pSrc;
    refl.m[1][0] *= -1.0f;
    refl.m[1][1] *= -1.0f;
    refl.m[1][2] *= -1.0f;
    refl.m[1][3] *= -1.0f;
    PSMTXConcat(refl, trans2, out2);

    if (!skipAdjust) {
        f32 margin = 0.6f;
        nw4r::math::VEC3 pts[6] = {
            nw4r::math::VEC3(0.0f, margin, 0.0f), nw4r::math::VEC3(0.0f, 1.2f, 0.0f),
            nw4r::math::VEC3(0.0f, 1.8f, 0.0f),   nw4r::math::VEC3(0.0f, 2.4f, 0.0f),
            nw4r::math::VEC3(0.0f, 2.9f, 0.0f),   nw4r::math::VEC3(0.0f, 3.3f, 0.0f)};
        f32 minOff = 0.0f;
        for (u32 i = 0; i < 6; i++) {
            PSMTXMultVec(out2.m, (const Vec*)&pts[i], (Vec*)&t);
            if (t.y > -margin && t.z > -192.0f + margin) {
                f32 d = -margin - t.y;
                if (minOff > d) {
                    minOff = d;
                }
            }
        }
        out2.m[1][3] += minOff;
    }

    nw4r::math::VEC3 pos2(out2.m[0][3], out2.m[1][3], out2.m[2][3]);
    if (!fn_80372C18(pCullMtx, &pos2, 4.0f)) {
        pThis->mMtx[index][1] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, -193.0f);
    } else {
        pThis->mMtx[index][1] = out2;
    }
}

}  // extern "C"

extern "C" {

void fn_804CFED0(void* pArg, int index) {
    BowPinMtxSet* pThis = (BowPinMtxSet*)pArg;
    f32 x = (index == 0) ? 0.0f : pThis->mMtx[0][0].m[0][3];
    for (; index < 10; index++) {
        pThis->mMtx[index][0] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, x, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, -193.0f);
        pThis->mMtx[index][1] = nw4r::math::MTX34(0.0f, 0.0f, 0.0f, x, 0.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 0.0f, -193.0f);
    }
}

}  // extern "C"

// Tables of this unit written out as data under their address labels (vtables:
// slot 0 = RTTI, slot 1 = this-offset; the classes are not modelled with their
// full virtual lists yet).
extern "C" {
void ogws_fn_80316418();
void fn_804C7D14();
void fn_804C7D10();
void EditJointLocalMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34PQ34nw4r4math4VEC3();
void EditJointWorldMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34();
void ReferViewMtx__19IRPGrpModelCallbackFP10RPGrpModel();

void* lbl_803CA9D8[] = {
    0,
    0,
    (void*)fn_804D0988,
    (void*)ogws_fn_8034F440,
    (void*)fn_804D0574,
    (void*)fn_804D0570,
    (void*)ogws_fn_80316418,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
    0,
    (void*)fn_804D09D0,
    (void*)EditJointLocalMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34PQ34nw4r4math4VEC3,
    (void*)EditJointWorldMtx__19IRPGrpModelCallbackFP10RPGrpModelUsPQ34nw4r4math5MTX34,
    (void*)fn_804D09C8,
    (void*)ReferViewMtx__19IRPGrpModelCallbackFP10RPGrpModel,
    (void*)fn_804D03F4,
};
}  // extern "C"
