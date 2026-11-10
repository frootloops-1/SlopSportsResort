#ifndef RP_GRAPHICS_MODEL_MATERIAL_H
#define RP_GRAPHICS_MODEL_MATERIAL_H
#include <Pack/types_pack.h>

#include <nw4r/g3d.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Model material setting
 */
class RPGrpModelMaterial {
public:
    enum ESyncFlag {
        ESyncFlag_ResGenMode = 1 << 0,
        ESyncFlag_ResMatChanCtrl = 1 << 1,   // inferred name
        ESyncFlag_ResMatPix = 1 << 3,        // inferred name
        ESyncFlag_ResMatTev = 1 << 4,
        ESyncFlag_ResTexSrt = 1 << 9,        // inferred name
        ESyncFlag_ResMatChanColor = 1 << 11, // inferred name
        ESyncFlag_ResTevSwap = 1 << 12,      // inferred name
    };

    enum ETevColor {
        ETevColor_Reg0,
        ETevColor_Reg1,
        ETevColor_Reg2,

        ETevColor_Max
    };

    enum ETevKColor {
        ETevKColor_Reg0,
        ETevKColor_Reg1,
        ETevKColor_Reg2,
        ETevKColor_Reg3,

        ETevKColor_Max
    };

    struct ChanCtrl {
        u8 enable;    // at 0x0
        u8 lightMask; // at 0x1
        u8 ambSrc;    // at 0x2
        u8 matSrc;    // at 0x3
        u8 diffuseFn; // at 0x4
        u8 attnFn;    // at 0x5
        u8 unk6[2];   // at 0x6 (never written)
    };

    //! @brief Generic mode settings (matches order of fields at 0x7 below)
    struct GenModeInfo {
        u8 numChans;      // at 0x0
        u8 numTexGens;    // at 0x1
        u8 numTevStages;  // at 0x2
        u8 numIndStages;  // at 0x3
        u8 cullMode;      // at 0x4
    };

    //! @brief Pixel engine settings
    struct PixInfo {
        u8 alphaComp0;    // at 0x0
        u8 alphaComp1;    // at 0x1
        u8 alphaRef0;     // at 0x2
        u8 alphaRef1;     // at 0x3
        u8 alphaOp;       // at 0x4
        u8 zTest;         // at 0x5
        u8 zUpdate;       // at 0x6
        u8 zCompare;      // at 0x7
        u8 blendType;     // at 0x8
        u8 blendSrc;      // at 0x9
        u8 blendDst;      // at 0xA
        u8 blendOp;       // at 0xB
        u8 dstAlphaEnable; // at 0xC
        u8 dstAlpha;      // at 0xD
        u8 unkE;           // at 0xE
        u8 unkF;           // at 0xF
    };

    //! @brief Channel colors
    struct ChanColorInfo {
        GXColor ambColor; // at 0x0
        GXColor matColor; // at 0x4
    };

    //! @brief TEV register colors (Resort: one block at 0xC; SetMatColor
    //! 0x80246164 addresses it through a single base pointer)
    struct TevColor {
        GXColor mKColors[ETevKColor_Max];   // at 0x0
        GXColorS10 mColors[ETevColor_Max];  // at 0x10

        void SetColor(u8 reg, const GXColor& rColor) {
            mColors[reg].r = rColor.r;
            mColors[reg].g = rColor.g;
            mColors[reg].b = rColor.b;
            mColors[reg].a = rColor.a;
        }
    };

private:
    // Resort layout, sizeof 0xB8 (ctor 0x80259044, RPGrpModel::CreateMaterial
    // 0x8024E1FC allocates 0xB8, vptr at 0xB4)
    u16 mSyncFlags; // at 0x0
    u8 unk6;        // at 0x2 (ctor stores 3)
    GenModeInfo mGenMode; // at 0x3 (unverified)
    u16 unk4;             // at 0x8 (unverified)
    char unkA[2];
    TevColor mTevColor;                               // at 0xC
    PixInfo mPix;                                     // at 0x34
    ChanColorInfo* mpChanColors[2];                   // at 0x44 (unverified)
    const nw4r::math::MTX34* mpEffectMtxs[8];         // at 0x4C
    u8 mSwapTables[GX_MAX_TEVSWAP][4];                // at 0x6C
    nw4r::g3d::ResMat mResMat;                           // at 0x7C
    nw4r::g3d::ScnMdl::CopiedMatAccess mCopiedMatAccess; // at 0x80

public:
    RPGrpModelMaterial(RPGrpModel* pModel, u16 idx);
    virtual ~RPGrpModelMaterial(); // at 0x8

private:
    // Not found in the Resort layout (no room before the vptr at 0xB4); kept
    // after it for the ogws-derived source only.
    ChanCtrl* mpChanCtrls[GX_ALPHA1 - GX_COLOR0 + 1];
    u8* unk78; // new u8[numTevStages], otherwise unused here

public:
    TevColor& GetTevColor() {
        return mTevColor;
    }


    void Calc();

    void SetManualMapMode(u32 id);
    void SetGenMode(const GenModeInfo& rInfo);
    void GetGenMode(GenModeInfo& rInfo);
    bool GetChanColor(u8 idx, ChanColorInfo& rInfo);
    void GetPix(PixInfo& rInfo);

private:
    // Constructor helpers (inferred names)
    bool GetResChanCtrl(u8 idx, ChanCtrl& rCtrl);
    void InitTevColor();
    void InitTevSwap();
    void InitEffectMtx();

    // Calc helpers (inferred names)
    void CalcGenMode();
    void SetResChanCtrl(u8 idx, const ChanCtrl& rCtrl);
    void SetResChanColor(u8 idx, const ChanColorInfo& rInfo);
    void CalcPix();
    void CalcTevColor();
    void CalcTevSwap();
    void CalcTexSrt();

    // First word of the copied material access is its ScnMdl pointer
    bool HasCopiedMat() const {
        return *reinterpret_cast<void* const*>(&mCopiedMatAccess) != NULL;
    }

    nw4r::g3d::ResTexSrt GetResTexSrt() {
        if (!HasCopiedMat()) {
            return mResMat.GetResTexSrt();
        }
        nw4r::g3d::ResTexSrt srt = mCopiedMatAccess.GetResTexSrt(false);
        if (srt.IsValid()) {
            return srt;
        }
        return mResMat.GetResTexSrt();
    }

    nw4r::g3d::ResMatChan GetResMatChan() {
        if (!HasCopiedMat()) {
            return mResMat.GetResMatChan();
        }
        nw4r::g3d::ResMatChan chan = mCopiedMatAccess.GetResMatChan(false);
        if (chan.IsValid()) {
            return chan;
        }
        return mResMat.GetResMatChan();
    }

    nw4r::g3d::ResGenMode GetResGenMode() {
        if (!HasCopiedMat()) {
            return mResMat.GetResGenMode();
        }
        nw4r::g3d::ResGenMode mode = mCopiedMatAccess.GetResGenMode(false);
        if (mode.IsValid()) {
            return mode;
        }
        return mResMat.GetResGenMode();
    }

    nw4r::g3d::ResMatPix GetResMatPix() {
        if (!HasCopiedMat()) {
            return mResMat.GetResMatPix();
        }
        nw4r::g3d::ResMatPix pix = mCopiedMatAccess.GetResMatPix(false);
        if (pix.IsValid()) {
            return pix;
        }
        return mResMat.GetResMatPix();
    }

    nw4r::g3d::ResMatTevColor GetResMatTevColor() {
        if (!HasCopiedMat()) {
            return mResMat.GetResMatTevColor();
        }
        nw4r::g3d::ResMatTevColor color =
            mCopiedMatAccess.GetResMatTevColor(false);
        if (color.IsValid()) {
            return color;
        }
        return mResMat.GetResMatTevColor();
    }

    nw4r::g3d::ResTev GetResTev() {
        if (!HasCopiedMat()) {
            return static_cast<const nw4r::g3d::ResMat&>(mResMat).GetResTev();
        }
        nw4r::g3d::ResTev tev = mCopiedMatAccess.GetResTev(false);
        if (tev.IsValid()) {
            return tev;
        }
        return static_cast<const nw4r::g3d::ResMat&>(mResMat).GetResTev();
    }

public:
    void SetSyncFlags(u32 flags) {
        mSyncFlags |= flags;
    }

    u8 GetCullMode() const {
        return mGenMode.cullMode;
    }
    void SetCullMode(GXCullMode cullMode) {
        mGenMode.cullMode = cullMode;
    }

    void SetTevKColor(ETevKColor idx, GXColor color) {
        mTevColor.mKColors[idx] = color;
    }
    void SetTevKColor(ETevKColor idx, u8 r, u8 g, u8 b) {
        mTevColor.mKColors[idx].r = r;
        mTevColor.mKColors[idx].g = g;
        mTevColor.mKColors[idx].b = b;
    }

    void SetTevColor(ETevColor idx, GXColorS10 color) {
        mTevColor.mColors[idx] = color;
    }
    void SetTevColor(ETevColor idx, const GXColor& color) {
        mTevColor.mColors[idx].r = color.r;
        mTevColor.mColors[idx].g = color.g;
        mTevColor.mColors[idx].b = color.b;
        mTevColor.mColors[idx].a = color.a;
    }
    void SetTevColor(ETevColor idx, u8 r, u8 g, u8 b, u8 a) {
        mTevColor.mColors[idx].r = r;
        mTevColor.mColors[idx].g = g;
        mTevColor.mColors[idx].b = b;
        mTevColor.mColors[idx].a = a;
    }
    void SetTevColorAlpha(ETevColor idx, u8 alpha) {
        mTevColor.mColors[idx].a = alpha;
    }
};

//! @}

#endif
