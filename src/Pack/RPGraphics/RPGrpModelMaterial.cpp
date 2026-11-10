// The shared headers pull in g3d_gpu.h (`static const u8 cm2hw[]`), which emits a
// stray .sdata2 entry this object lacks. Pre-define its include guard.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

// Color/alpha channel pair for each channel color index (GetChanColor)
static const u8 scChannels[2][2] = {{GX_COLOR0, GX_ALPHA0},
                                    {GX_COLOR1, GX_ALPHA1}};

// Same table, used by SetResChanColor (Calc)
static const u8 scChanColorChannels[2][2] = {{GX_COLOR0, GX_ALPHA0},
                                             {GX_COLOR1, GX_ALPHA1}};

// Default pixel engine settings (copied in the constructor)
static const RPGrpModelMaterial::PixInfo scDefaultPixInfo = {
    GX_ALWAYS,         // alphaComp0
    GX_ALWAYS,         // alphaComp1
    0,                 // alphaRef0
    0,                 // alphaRef1
    GX_AOP_OR,         // alphaOp
    TRUE,              // zTest
    TRUE,              // zUpdate
    GX_LEQUAL,         // zCompare
    GX_BM_NONE,        // blendType
    GX_BL_SRCALPHA,    // blendSrc
    GX_BL_INVSRCALPHA, // blendDst
    GX_LO_CLEAR,       // blendOp
    FALSE,             // dstAlphaEnable
    0,                 // dstAlpha
};

/**
 * @brief Destructor
 */
RPGrpModelMaterial::~RPGrpModelMaterial() {}

inline bool RPGrpModelMaterial::GetResChanCtrl(u8 idx, ChanCtrl& rCtrl) {
    GXBool enable;
    GXColorSrc ambSrc, matSrc;
    GXLightID lightMask;
    GXDiffuseFn diffuseFn;
    GXAttnFn attnFn;

    if (GetResMatChan().GXGetChanCtrl(static_cast<GXChannelID>(idx), &enable,
                                      &ambSrc, &matSrc, &lightMask,
                                      &diffuseFn, &attnFn)) {
        rCtrl.enable = enable != 0;
        rCtrl.lightMask = lightMask;
        rCtrl.ambSrc = ambSrc;
        rCtrl.matSrc = matSrc;
        rCtrl.diffuseFn = diffuseFn;
        rCtrl.attnFn = attnFn;
        return true;
    }

    return false;
}

inline void RPGrpModelMaterial::InitTevColor() {
    nw4r::g3d::ResMatTevColor color = GetResMatTevColor();
    for (int i = 0; i < ETevKColor_Max; i++) {
        color.GXGetTevKColor(static_cast<GXTevKColorID>(i), &mTevColor.mKColors[i]);
    }
    for (int i = 0; i < ETevColor_Max; i++) {
        color.GXGetTevColorS10(static_cast<GXTevRegID>(i + GX_TEVREG0),
                               &mTevColor.mColors[i]);
    }
}

inline void RPGrpModelMaterial::InitTevSwap() {
    nw4r::g3d::ResTev tev = GetResTev();
    for (int i = 0; i < GX_MAX_TEVSWAP; i++) {
        GXTevColorChan r, g, b, a;
        if (tev.GXGetTevSwapModeTable(static_cast<GXTevSwapSel>(i), &r, &g,
                                      &b, &a)) {
            mSwapTables[i][0] = r;
            mSwapTables[i][1] = g;
            mSwapTables[i][2] = b;
            mSwapTables[i][3] = a;
        }
    }
}

inline void RPGrpModelMaterial::InitEffectMtx() {
    nw4r::g3d::ResTexSrt srt = GetResTexSrt();
    for (u32 i = 0; i < 8; i++) {
        nw4r::math::MTX34 mtx;
        if (srt.GetEffectMtx(i, &mtx)) {
            mpEffectMtxs[i] = reinterpret_cast<const nw4r::math::MTX34*>(
                &srt.ref().effect[i].effectMtx);
        }
    }
}

/**
 * @brief Constructor
 *
 * @param pModel Parent model
 * @param idx Material index
 */
RPGrpModelMaterial::RPGrpModelMaterial(RPGrpModel* pModel, u16 idx)
    : mSyncFlags(0),
      unk4(0),
      unk6(3),
      mPix(scDefaultPixInfo),
      unk78(NULL),
      mResMat(pModel->GetScnMdlSimple() != NULL
                  ? pModel->GetScnMdlSimple()->GetResMdl().GetResMat(idx)
                  : nw4r::g3d::ResMat(NULL)),
      mCopiedMatAccess(pModel->GetScnMdl() != NULL ? pModel->GetScnMdl() : NULL,
                       idx) {

    for (int i = 0; i < 8; i++) {
        mpEffectMtxs[i] = NULL;
    }

    for (int i = 0; i < GX_ALPHA1 - GX_COLOR0 + 1; i++) {
        mpChanCtrls[i] = NULL;
    }

    for (int i = 0; i < 2; i++) {
        mpChanColors[i] = NULL;
    }

    for (int i = 0; i < GX_MAX_TEVSWAP; i++) {
        mSwapTables[i][0] = GX_CH_RED;
        mSwapTables[i][1] = GX_CH_GREEN;
        mSwapTables[i][2] = GX_CH_BLUE;
        mSwapTables[i][3] = GX_CH_ALPHA;
    }

    GetGenMode(mGenMode);

    for (int i = 0; i < GX_ALPHA1 - GX_COLOR0 + 1; i++) {
        ChanCtrl ctrl;
        if (GetResChanCtrl(i, ctrl)) {
            if (mpChanCtrls[i] == NULL) {
                mpChanCtrls[i] = new ChanCtrl;
            }
            *mpChanCtrls[i] = ctrl;
        }
    }

    for (int i = 0; i < 2; i++) {
        ChanColorInfo info;
        if (GetChanColor(i, info)) {
            if (mpChanColors[i] == NULL) {
                mpChanColors[i] = new ChanColorInfo;
            }
            *mpChanColors[i] = info;
        }
    }

    GetPix(mPix);
    unk78 = new u8[mGenMode.numTevStages];

    InitTevColor();
    InitTevSwap();
    InitEffectMtx();

    for (int i = 0; i < 8; i++) {
        nw4r::g3d::ResTexSrt srt = GetResTexSrt();
        u32 mode;
        int camRef, lightRef;
        if (srt.GetMapMode((u8)i, &mode, &camRef, &lightRef) && camRef == 0) {
            camRef = -1;
            srt.SetMapMode((u8)i, mode, camRef, lightRef);
        }
    }
}

inline void RPGrpModelMaterial::CalcGenMode() {
    nw4r::g3d::ResGenMode mode = GetResGenMode();

    mode.GXSetNumChans(mGenMode.numChans);
    mode.GXSetNumTexGens(mGenMode.numTexGens);
    mode.GXSetNumTevStages(mGenMode.numTevStages);
    mode.GXSetNumIndStages(mGenMode.numIndStages);

    mode.GXSetCullMode((unk6 & 1) ? static_cast<GXCullMode>(mGenMode.cullMode)
                                  : GX_CULL_ALL);

    if (unk6 & 1) {
        unk6 |= 2;
    } else {
        unk6 &= ~2;
    }
}

inline void RPGrpModelMaterial::SetResChanCtrl(u8 idx,
                                               const ChanCtrl& rCtrl) {
    GetResMatChan().GXSetChanCtrl(static_cast<GXChannelID>(idx), rCtrl.enable,
                                  static_cast<GXColorSrc>(rCtrl.ambSrc),
                                  static_cast<GXColorSrc>(rCtrl.matSrc),
                                  static_cast<GXLightID>(rCtrl.lightMask),
                                  static_cast<GXDiffuseFn>(rCtrl.diffuseFn),
                                  static_cast<GXAttnFn>(rCtrl.attnFn));
    GetResMatChan().EndEdit();
}

inline void RPGrpModelMaterial::SetResChanColor(u8 idx,
                                                const ChanColorInfo& rInfo) {
    GetResMatChan().GXSetChanMatColor(
        static_cast<GXChannelID>(scChanColorChannels[idx][0]),
        rInfo.matColor);
    GetResMatChan().GXSetChanMatColor(
        static_cast<GXChannelID>(scChanColorChannels[idx][1]),
        rInfo.matColor);
    GetResMatChan().GXSetChanAmbColor(
        static_cast<GXChannelID>(scChanColorChannels[idx][0]),
        rInfo.ambColor);
    GetResMatChan().GXSetChanAmbColor(
        static_cast<GXChannelID>(scChanColorChannels[idx][1]),
        rInfo.ambColor);
    GetResMatChan().EndEdit();
}

inline void RPGrpModelMaterial::CalcPix() {
    nw4r::g3d::ResMatPix pix = GetResMatPix();
    pix.GXSetAlphaCompare(static_cast<GXCompare>(mPix.alphaComp0),
                          mPix.alphaRef0, static_cast<GXAlphaOp>(mPix.alphaOp),
                          static_cast<GXCompare>(mPix.alphaComp1),
                          mPix.alphaRef1);
    pix.GXSetZMode(mPix.zTest, static_cast<GXCompare>(mPix.zCompare),
                   mPix.zUpdate);
    pix.GXSetBlendMode(static_cast<GXBlendMode>(mPix.blendType),
                       static_cast<GXBlendFactor>(mPix.blendSrc),
                       static_cast<GXBlendFactor>(mPix.blendDst),
                       static_cast<GXLogicOp>(mPix.blendOp));
    pix.GXSetDstAlpha(mPix.dstAlphaEnable, mPix.dstAlpha);
    pix.EndEdit();
}

inline void RPGrpModelMaterial::CalcTevColor() {
    nw4r::g3d::ResMatTevColor color = GetResMatTevColor();
    for (int i = 0; i < ETevKColor_Max; i++) {
        color.GXSetTevKColor(static_cast<GXTevKColorID>(i), mTevColor.mKColors[i]);
    }
    for (int i = 0; i < ETevColor_Max; i++) {
        color.GXSetTevColorS10(static_cast<GXTevRegID>(i + GX_TEVREG0),
                               mTevColor.mColors[i]);
    }
    color.EndEdit();
}

inline void RPGrpModelMaterial::CalcTevSwap() {
    for (int i = 0; i < GX_MAX_TEVSWAP; i++) {
        GetResTev().GXSetTevSwapModeTable(
            static_cast<GXTevSwapSel>(i),
            static_cast<GXTevColorChan>(mSwapTables[i][0]),
            static_cast<GXTevColorChan>(mSwapTables[i][1]),
            static_cast<GXTevColorChan>(mSwapTables[i][2]),
            static_cast<GXTevColorChan>(mSwapTables[i][3]));
    }
    GetResTev().EndEdit();
}

inline void RPGrpModelMaterial::CalcTexSrt() {
    nw4r::g3d::ResTexSrt srt = GetResTexSrt();
    for (int i = 0; i < 8; i++) {
        if (mpEffectMtxs[i] != NULL) {
            srt.SetEffectMtx((u8)i, mpEffectMtxs[i]);
        }
    }
}

/**
 * @brief Applies pending changes to the material resource
 */
void RPGrpModelMaterial::Calc() {
    bool cullSynced = (unk6 & 1) == ((unk6 >> 1) & 1);
    if ((mSyncFlags & ESyncFlag_ResGenMode) || !cullSynced) {
        CalcGenMode();
    }

    if (mSyncFlags & ESyncFlag_ResMatChanCtrl) {
        for (int i = 0; i < GX_ALPHA1 - GX_COLOR0 + 1; i++) {
            if (mpChanCtrls[i] != NULL) {
                SetResChanCtrl(i, *mpChanCtrls[i]);
            }
        }
    }

    if (mSyncFlags & ESyncFlag_ResMatChanColor) {
        for (int i = 0; i < 2; i++) {
            if (mpChanColors[i] != NULL) {
                SetResChanColor(i, *mpChanColors[i]);
            }
        }
    }

    if (mSyncFlags & ESyncFlag_ResMatPix) {
        CalcPix();
    }

    if (mSyncFlags & ESyncFlag_ResMatTev) {
        CalcTevColor();
    }

    if (mSyncFlags & ESyncFlag_ResTevSwap) {
        CalcTevSwap();
    }

    if (mSyncFlags & ESyncFlag_ResTexSrt) {
        CalcTexSrt();
    }

    mSyncFlags = 0;
    unk4 = 0;
}

/**
 * @brief Gets generic mode settings from this material
 */
void RPGrpModelMaterial::GetGenMode(GenModeInfo& rInfo) {
    rInfo.numChans = GetResGenMode().GXGetNumChans();
    rInfo.numTevStages = GetResGenMode().GXGetNumTevStages();
    rInfo.numTexGens = GetResGenMode().GXGetNumTexGens();
    rInfo.numIndStages = GetResGenMode().GXGetNumIndStages();
    rInfo.cullMode = GetResGenMode().GXGetCullMode();
}

/**
 * @brief Gets pixel engine settings from this material
 */
void RPGrpModelMaterial::GetPix(PixInfo& rInfo) {
    nw4r::g3d::ResMatPix pix = GetResMatPix();

    GXCompare comp0, comp1;
    GXAlphaOp op;
    u8 ref0, ref1;
    if (pix.GXGetAlphaCompare(&comp0, &ref0, &op, &comp1, &ref1)) {
        rInfo.alphaComp0 = comp0;
        rInfo.alphaComp1 = comp1;
        rInfo.alphaRef0 = ref0;
        rInfo.alphaRef1 = ref1;
        rInfo.alphaOp = op;
    }

    GXBool zTest, zUpdate;
    GXCompare zComp;
    if (pix.GXGetZMode(&zTest, &zComp, &zUpdate)) {
        rInfo.zTest = zTest != 0;
        rInfo.zUpdate = zUpdate != 0;
        rInfo.zCompare = zComp;
    }

    GXBlendMode blend;
    GXBlendFactor src, dst;
    GXLogicOp logic;
    if (pix.GXGetBlendMode(&blend, &src, &dst, &logic)) {
        rInfo.blendType = blend;
        rInfo.blendSrc = src;
        rInfo.blendDst = dst;
        rInfo.blendOp = logic;
    }

    GXBool dstAlphaEnable;
    u8 dstAlpha;
    if (pix.GXGetDstAlpha(&dstAlphaEnable, &dstAlpha)) {
        rInfo.dstAlphaEnable = dstAlphaEnable != 0;
        rInfo.dstAlpha = dstAlpha;
    }
}

/**
 * @brief Gets ambient/material colors of the specified color channel pair
 *
 * @return Whether any color was found
 */
bool RPGrpModelMaterial::GetChanColor(u8 idx, ChanColorInfo& rInfo) {
    const u8* pChannel = scChannels[idx];
    bool found = false;

    for (int i = 0; i < 2; i++, pChannel++) {
        GXColor mat;
        GXColor amb;
        bool hasMat = GetResMatChan().GXGetChanMatColor(
            static_cast<GXChannelID>(*pChannel), &mat);
        bool hasAmb = GetResMatChan().GXGetChanAmbColor(
            static_cast<GXChannelID>(*pChannel), &amb);

        if (hasMat || hasAmb) {
            found = true;

            if (i == 0) {
                if (hasMat) {
                    rInfo.matColor.r = mat.r;
                    rInfo.matColor.g = mat.g;
                    rInfo.matColor.b = mat.b;
                } else {
                    rInfo.matColor.b = 255;
                    rInfo.matColor.g = 255;
                    rInfo.matColor.r = 255;
                }

                if (hasAmb) {
                    rInfo.ambColor.r = amb.r;
                    rInfo.ambColor.g = amb.g;
                    rInfo.ambColor.b = amb.b;
                } else {
                    rInfo.ambColor.b = 255;
                    rInfo.ambColor.g = 255;
                    rInfo.ambColor.r = 255;
                }
            } else {
                if (hasMat) {
                    rInfo.matColor.a = mat.a;
                } else {
                    rInfo.matColor.a = 255;
                }

                if (hasAmb) {
                    rInfo.ambColor.a = amb.a;
                } else {
                    rInfo.ambColor.a = 255;
                }
            }
        }
    }

    return found;
}
/**
 * @brief Applies generic mode settings to this material
 */
void RPGrpModelMaterial::SetGenMode(const GenModeInfo& rInfo) {
    nw4r::g3d::ResGenMode mode = GetResGenMode();

    mode.GXSetNumChans(rInfo.numChans);
    mode.GXSetNumTexGens(rInfo.numTexGens);
    mode.GXSetNumTevStages(rInfo.numTevStages);
    mode.GXSetNumIndStages(rInfo.numIndStages);

    mode.GXSetCullMode((unk6 & 1) ? static_cast<GXCullMode>(rInfo.cullMode)
                                  : GX_CULL_ALL);

    if (unk6 & 1) {
        unk6 |= 2;
    } else {
        unk6 &= ~2;
    }
}

/**
 * @brief Sets manual map mode of this material's texture SRT
 */
void RPGrpModelMaterial::SetManualMapMode(u32 id) {
    EGG::G3DUtility::setManualMapMode(GetResTexSrt(), id);
}
