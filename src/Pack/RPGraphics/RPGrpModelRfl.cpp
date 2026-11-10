// Use scene and resource declarations without the animation-controller umbrella.
// GetAnmPlayPolicy's unused weak table otherwise adds eight bytes to .sdata.
#define NW4R_PUBLIC_G3D_H
#define EGG_PUBLIC_GFXE_H
#define NW4R_G3D_PLATFORM_GPU_H

namespace nw4r {
namespace g3d {
// Only derived callback objects are constructed in this translation unit.
class __declspec(novtable) IScnObjCallback;
} // namespace g3d
} // namespace nw4r

#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/g3d/g3d_scnmdl1mat1shp.h>
#include <nw4r/g3d/g3d_scnproc.h>
#include <nw4r/g3d/g3d_scnrfl.h>
#include <nw4r/g3d/res/g3d_resanmchr.h>
#include <nw4r/g3d/res/g3d_resanmclr.h>
#include <nw4r/g3d/res/g3d_resanmscn.h>
#include <nw4r/g3d/res/g3d_resanmshp.h>
#include <nw4r/g3d/res/g3d_resanmtexpat.h>
#include <nw4r/g3d/res/g3d_resanmtexsrt.h>
#include <nw4r/g3d/res/g3d_resanmvis.h>
#include <nw4r/g3d/res/g3d_resfile.h>

#include <egg/gfxe/eggModelEx.h>

#include <Pack/RPGraphics/RPGrpModelRfl.h>
#include <Pack/RPGraphics/RPGrpModelRecord.h>
#include <Pack/RPGraphics/RPGrpTexture.h>

#include <RVLFaceLib.h>
#include <revolution/GX.h>

#include <cstring>

static inline bool IsRflDrawHidden(const u16* flags) {
    return (*flags & 0x100) != 0;
}

static inline void SetRflOutputAlpha(const u8* alpha) {
    GXColor color = {0, 0, 0, *alpha};
    GXSetTevKColor(GX_KCOLOR3, color);
}

const u8 RPGrpModelRfl::DEFAULT_OUTPUT_ALPHA = 128;

RPGrpModel* RPGrpModelRfl::spDrawModel = NULL;
f32 RPGrpModelRfl::sBaseScale = 1.0f;

// clang-format off
nw4r::math::MTX34 RPGrpModelRfl::lbl_804A4608(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f
);
// clang-format on

RFLDrawCoreSetting RPGrpModelRfl::sDrawCoreSetting;

RPGrpModelRfl* RPGrpModelRfl::Construct(RFLDataSource src, u16 index,
                                        RFLMiddleDB* pMiddleDB,
                                        RFLResolution resolution, u32 exprFlags,
                                        u8 viewNo, u32 /* arg6 */) {

    RPGrpModelRfl* p = new RPGrpModelRfl(resolution, exprFlags, viewNo);

    p->Configure();

    if (!p->GetScnRfl()->SetupCharModel(src, index, pMiddleDB)) {
        src = RFLDataSource_Default;
        index = 0;
        pMiddleDB = NULL;

        p->GetScnRfl()->SetupCharModel(RFLDataSource_Default, 0, NULL);
    }

    p->mDataSource = src;
    p->mIndex = index;
    p->mpMiddleDB = pMiddleDB;

    // Manually fire the DrawProc callback as a way to get the char model
    p->GetScnRfl()->SetDrawProc(GetCharModelDrawProc);
    p->GetScnRfl()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_DRAW_OPA, 0, NULL);

    p->GetScnRfl()->SetDrawProc(DrawProc);

    return p;
}

RPGrpModelRfl::RPGrpModelRfl(RFLResolution resolution, u32 exprFlags, u8 viewNo)
    : RPGrpModel(viewNo),
      mFlagsRfl(EFlag_5 | EFlag_6 | EFlag_7),
      mOutputAlpha(128),
      mMaterialType(MaterialType_0),
      mpRflParent(NULL),
      mpCharModel(NULL),
      mExprFlags(exprFlags) {

    u32 size;
    nw4r::g3d::ScnRfl* pScnRfl = nw4r::g3d::ScnRfl::Construct(
        spAllocator, &size, resolution, exprFlags, sizeof(RPGrpModelRfl*));

    *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData()) = this;

    mpModelEx = new EGG::ModelEx(pScnRfl);
}

void RPGrpModelRfl::Configure() {
    RPGrpModel::Configure();

    sDrawCoreSetting.txcGenNum = 3;
    sDrawCoreSetting.txcID = GX_TEXCOORD0;
    sDrawCoreSetting.texMapID = GX_TEXMAP0;
    sDrawCoreSetting.tevStageNum = 4;
    sDrawCoreSetting.tevSwapTable = GX_TEV_SWAP0;
    sDrawCoreSetting.tevKColorID = GX_KCOLOR0;
    sDrawCoreSetting.tevOutRegID = GX_TEVREG2;
    sDrawCoreSetting.posNrmMtxID = GX_PNMTX0;
    sDrawCoreSetting.reverseCulling = false;

    GetScnRfl()->SetLightSetIdx(LIGHT_SET_IDX);
    GetScnRfl()->SetFogIdx(FOG_IDX);
    GetScnRfl()->SetAmbientColor((GXColor){255, 255, 255, 255});
    mBrightnessColor = (GXColor){255, 255, 255, 255};

    InternalCalc();
}

void RPGrpModelRfl::CreateAnm() {}

u16 RPGrpModelRfl::ReplaceTexture(const char* pName,
                                  const RPGrpTexture& rTexture,
                                  bool /* keepFilterWrap */) {
    if (std::strcmp(pName, "lm_0") == 0) {
        mLightTexObj0 = rTexture.GetTexObj();
        mFlagsRfl |= 1;
    } else if (std::strcmp(pName, "lm_1") == 0) {
        mLightTexObj1 = rTexture.GetTexObj();
        mFlagsRfl |= 2;
    } else {
        return 0;
    }

    return 1;
}

void RPGrpModelRfl::InternalCalc() {
    if (!mReverseCulling) {
        nw4r::math::VEC3 scale(mBaseScale.x * sBaseScale,
                               mBaseScale.y * sBaseScale,
                               mBaseScale.z * sBaseScale);

        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(scale);
        }

        mFlagsRfl &= ~EFlag_ReverseCulling;
    } else {
        const nw4r::math::_VEC3& rMag = GEOMETRY_MAGNIFY[mReverseCulling - 1];

        nw4r::math::VEC3 scale(mBaseScale.x * rMag.x * sBaseScale,
                               mBaseScale.y * rMag.y * sBaseScale,
                               mBaseScale.z * rMag.z * sBaseScale);

        if (GetScnLeaf() != NULL) {
            GetScnLeaf()->SetScale(scale);
        }

        mFlagsRfl |= EFlag_ReverseCulling;
    }

    if (GetScnObj() != NULL) {
        GetScnObj()->G3dProc(nw4r::g3d::G3dObj::G3DPROC_CALC_WORLD, 0, NULL);
    }

    if (mpRecord != NULL) {
        nw4r::math::MTX34 worldMtx;
        spCalcWorldMtxArray = &worldMtx;

        GetScnRfl()->GetMtx(nw4r::g3d::ScnObj::MTX_WORLD, spCalcWorldMtxArray);
        mpRecord->Calc(this);
        GetScnRfl()->SetMtx(nw4r::g3d::ScnObj::MTX_WORLD, spCalcWorldMtxArray);

        spCalcWorldMtxArray = NULL;
    }
}

#pragma optimization_level 2
void RPGrpModelRfl::CalcBeforeDraw() {
    RPGrpModel::CalcBeforeDraw();
    if (IsRflDrawHidden(&mFlagsRfl)) {
        mpModelEx->setVisible(false);
        mFlagsRfl |= 0x200;
    } else {
        mFlagsRfl &= ~0x200;
    }
}
#pragma optimization_level reset
void RPGrpModelRfl::DrawProc(nw4r::g3d::ScnRfl* pScnRfl,
                             const RFLCharModel* pModel, u32 diffMask,
                             u32 specMask, GXColor ambColor, bool opa) {

    RPGrpModelRfl* p = *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData());
    p->DrawGX(pModel, diffMask, specMask, ambColor, opa, false);
}

void RPGrpModelRfl::GetCharModelDrawProc(nw4r::g3d::ScnRfl* pScnRfl,
                                         const RFLCharModel* pModel,
                                         u32 /* diffMask */, u32 /* specMask */,
                                         GXColor /* ambColor */,
                                         bool /* opa */) {
    RPGrpModelRfl* p = *static_cast<RPGrpModelRfl**>(pScnRfl->GetUserData());
    p->mpCharModel = pModel;
}

void RPGrpModelRfl::DrawGX(const RFLCharModel* pModel, u32 diffMask,
                           u32 specMask, GXColor ambColor, bool opa,
                           bool arg5) {

    bool bVar4 = !(mFlagsRfl & EFlag_8) || (arg5 && spDrawModel == NULL);

    bool bVar6 = !arg5 || (arg5 && IsEntered() && IsVisible());

    bool useMat =
        !(EGG::ModelEx::getDrawFlag() & EGG::ModelEx::cDrawFlag_IgnoreMaterial);

    bool bVar7 = true;
    bool drawFlag = true;
    if ((unkC & 0x20) == 0 && (mFlagsRfl & 8) == 0) drawFlag = false;
    if (!drawFlag && mDrawGroup != 1) bVar7 = false;
    bool bVar2 = (mFlagsRfl & 0x400) || mDrawGroup == 1;

    bool bVar5;
    bool bVar3;
    bool samePass = (opa && bVar7) || (!opa && !bVar7);
    bVar3 = opa & bool(mFlagsRfl & 0x40);
    bVar5 = samePass & bool(mFlagsRfl & 0x80);

    if (!useMat) {
        if (bVar3) {
            RFLDrawShape(mpCharModel);
        }
        return;
    }

    bool bVar9 = bVar3 || bVar5;
    u32 diffMaskSub = diffMask;

    // Accidental bitwise AND?
    if (bVar6 & bVar9) {
        if (bVar4) {
            static const u8 TEV_STAGE_NUM[MaterialType_Max] = {4, 4, 3};
            // MATCH-PENDING (R17): hand-schedule this four-instruction setup.
            // Plain C++ delays spDrawModel's store until after the table load
            // and address add; retail stores it between lis and lbzx. The
            // original C++ scheduling inputs remain unrecovered.
            register u32 type = mMaterialType;
            register const u8* table = TEV_STAGE_NUM;
            register RPGrpModel* model = this;
            register RFLDrawCoreSetting* setting;
            asm {
                .scheduling off
                lis setting, sDrawCoreSetting@ha
                stw model, spDrawModel
                lbzx type, table, type
                addi setting, setting, sDrawCoreSetting@l
            }
            setting->tevStageNum = type;
            setting->reverseCulling = bool(mFlagsRfl & EFlag_ReverseCulling);

            RFLLoadMaterialSetting(setting);
            RFLLoadVertexSetting(setting);

            if (mMaterialType == MaterialType_1) {
                ambColor = (GXColor){0, 0, 0, 255};
            }

            diffMaskSub = diffMask;

            if (!(mFlagsRfl & EFlag_5)) {
                diffMaskSub = 0;
                ambColor.a = 255;
            }

            diffMask = 0;

            GXSetNumChans(1);

            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG,
                          GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
            GXSetChanCtrl(GX_ALPHA0, (mFlagsRfl & EFlag_5) ? GX_TRUE : GX_FALSE,
                          GX_SRC_REG, GX_SRC_REG,
                          static_cast<GXLightID>(diffMaskSub), GX_DF_CLAMP,
                          GX_AF_SPOT);
            GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG,
                          GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

            GXSetChanAmbColor(GX_COLOR0A0, ambColor);
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){255, 255, 255, 255});

            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

            GXLoadTexObj(&mLightTexObj0, GX_TEXMAP1);
            GXLoadTexObj(&mLightTexObj1, GX_TEXMAP2);

            GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                              GX_TRUE, GX_PTTEXMTX0);
        }

        nw4r::math::MTX34 viewMtx;
        GetScnRfl()->GetMtx(nw4r::g3d::ScnObj::MTX_VIEW, &viewMtx);
        viewMtx._03 = viewMtx._13 = viewMtx._23 = 0.0f;

        GXLoadTexMtxImm(viewMtx, GX_TEXMTX0, GX_MTX_3x4);

        nw4r::math::MTX34 trans, scale;
        PSMTXScale(scale, 0.5f, -0.5f, 0.0f);
        PSMTXTrans(trans, 0.5f, 0.5f, 1.0f);

        nw4r::math::MTX34 postMtx;
        nw4r::math::MTX34Mult(&postMtx, &trans, &scale);
        GXLoadTexMtxImm(postMtx, GX_PTTEXMTX0, GX_MTX_3x4);

        GXTevStageID stage = GX_TEVSTAGE1;

        if (bVar4) {
            GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN,
                                  GX_CH_BLUE, GX_CH_ALPHA);

            GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_RED, GX_CH_RED,
                                  GX_CH_ALPHA);

            GXSetTevDirect(GX_TEVSTAGE0);

            switch (mMaterialType) {
            case MaterialType_0: {
            case MaterialType_1:
                GXSetTevDirect(GX_TEVSTAGE1);
                GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1,
                              GX_COLOR0A0);
                GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC,
                                GX_CC_RASA, GX_CC_RASC);
                GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A2);
                GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE2);
                GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_CPREV,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE3);
                GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD1, GX_TEXMAP2,
                              GX_COLOR0A0);
                GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_TEXC,
                                GX_CC_RASA, GX_CC_CPREV);
                GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);

                stage = GX_TEVSTAGE3;
                break;
            }

            case MaterialType_2: {
                GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K2);
                GXSetTevKColor(GX_KCOLOR2, mBrightnessColor);

                GXSetTevDirect(GX_TEVSTAGE1);
                GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO,
                                GX_CC_ZERO, GX_CC_KONST);
                GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A2);
                GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE2);
                GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP2);
                GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                              GX_COLOR_NULL);
                GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO,
                                GX_CC_ZERO, GX_CC_CPREV);
                GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                stage = GX_TEVSTAGE2;
                break;
            }

            default: {
                break;
            }
            }
        }

        if (bVar3) {
            if (bVar4) {
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_NEVER, 0);
                GXSetTevKAlphaSel(stage, GX_TEV_KASEL_K3_A);
                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_KONST);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                               GX_LO_COPY);
            }

            GXSetTevKColor(GX_KCOLOR3, (GXColor){0, 0, 0, mOutputAlpha});
            RFLDrawOpaCore(mpCharModel, &sDrawCoreSetting);
        }

        if (bVar5) {
            if (bVar4) {
                GXSetZCompLoc(GX_FALSE);

                if (!bVar2) {
                    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_NEVER, 0);
                } else {
                    GXSetAlphaCompare(GX_GREATER, 128, GX_AOP_OR, GX_NEVER, 0);
                }

                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_APREV);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                               GX_LO_COPY);
            }

            RFLDrawXluCore(mpCharModel, &sDrawCoreSetting);
        }
    }

    if (mpRflParent != NULL) {
        mpRflParent->DrawGX(pModel, diffMask, specMask, ambColor, bVar3, true);
    }

    if (spDrawModel == this) {
        spDrawModel = NULL;
    }
}

const char* RPGrpModelRfl::GetJointName(u16 /* idx */) const {
    static const char JOINT_NAME[] = "dummy";
    return JOINT_NAME;
}

const char* RPGrpModelRfl::GetMaterialName(u16 /* idx */) const {
    static const char MATERIAL_NAME[] = "dummy";
    return MATERIAL_NAME;
}

const char* RPGrpModelRfl::GetShapeName(u16 /* idx */) const {
    static const char SHAPE_NAME[] = "dummy";
    return SHAPE_NAME;
}
