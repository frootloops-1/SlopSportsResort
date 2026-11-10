// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/RPUtility.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

#include <Pack/RPKernel/RPSysKokeshiUnk3C.h>

// Unidentified Resort functions (placeholder names, no header owns them yet):
// - message lookup through the "MsgResMgr" singleton (lbl_806F4E48)
extern "C" const wchar_t* fn_80262164(u32 id, int arg1, int arg2);
// - replaces control characters in the Mii name with spaces
extern "C" void fn_80246DEC(RFLAdditionalInfo* pInfo);

// Resort emits the functions of this file in reverse source order.

RPSysKokeshiManager* RPSysKokeshiManager::spInstance = NULL;

/**
 * @brief Clothing texture filenames
 */
const char* RPSysKokeshiManager::CLOTHING_TEXTURE_NAMES[ClothingTexture_Max] = {
    "dummy_tex_a",
    "dummy_tex_a",
    "dummy_tex_a",
    "dummy_tex_b",
};

/**
 * @brief Lightmap texture names
 */
const char* RPSysKokeshiManager::LIGHT_TEXTURE_NAMES[LightMap_Max] = {
    "lm_0",
    "lm_1",
};

/**
 * @brief Main material name
 */
const char* RPSysKokeshiManager::MAIN_MATERIAL_NAME = "mt_main";

/**
 * @brief Face library resource filename
 */
const char* RPSysKokeshiManager::RFL_RES_NAME = "RFL_Res.dat";

/**
 * @brief Hand model filenames
 */
const char* RPSysKokeshiManager::HAND_FILE_NAMES[HandType_Max] = {
    "G3D/WS2_ava_hand1.brres",
    "G3D/WS2_ava_hand2.brres",
    "G3D/WS2_ava_hand3.brres",
    "G3D/WS2_ava_hand4.brres",
};

/**
 * @brief Creates the singleton instance
 */
void RPSysKokeshiManager::CreateInstance() {
    spInstance = new RPSysKokeshiManager();
}

/**
 * @brief Constructor
 */
RPSysKokeshiManager::RPSysKokeshiManager()
    : IRPSysHostIOSocket("KokeshiManager") {

    mpNglBuffer = new (32) u8[RFLGetWorkSize(false)];
    mFriendRandomNum = RFL_DB_CHAR_MAX;
    unk28 = unk2C = unk30 = 0.0f;
    mOutputAlpha = RPGrpModelRfl::DEFAULT_OUTPUT_ALPHA;
    mLoadError = LoadError_Success;

    mBaseScale = 0.08f;
    RPGrpModelRfl::SetBaseScale(mBaseScale);

    nw4r::math::MTX34 mtx;
    nw4r::math::MTX34Identity(&mtx);
    RPGrpModelRfl::SetMtx(mtx);

    RPSysHostIOSocketManager::AddHostIOSocket(this);
}

/**
 * @brief Destructor
 */
RPSysKokeshiManager::~RPSysKokeshiManager() {}

void RPSysKokeshiManager::Unk_80246824(u16 a, int b, int x,
                                       RPGrpTexture** ppTexA,
                                       RPGrpTexture** ppTexB,
                                       EGG::Heap* pHeap) {
    Unk_8024673C(a, b, RPSysKokeshiUnk3C::Unk_80245CAC(x), ppTexA, ppTexB,
                 pHeap);
}

void RPSysKokeshiManager::Unk_8024673C(u16 a, int b, int c,
                                       RPGrpTexture** ppTexA,
                                       RPGrpTexture** ppTexB,
                                       EGG::Heap* pHeap) {
    RPSysKokeshiUnk3C* pUnk3C = RP_GET_INSTANCE(RPSysKokeshiManager)->mpUnk3C;
    EGG::Archive* pArchive =
        RP_GET_INSTANCE(RPSysResourceManager)->GetKokeshiArchive();

    void* pFile = RPSysResourceManager::GetFileFromArchive(
        pArchive, pUnk3C->Unk_80245B7C());

    const char* pNameA = NULL;
    const char* pNameB = NULL;
    pUnk3C->Unk_80245CD4(a, b, c, &pNameA, &pNameB);

    if (ppTexA != NULL && *pNameA != '\0') {
        *ppTexA = RP_GET_INSTANCE(RPSysKokeshiManager)
                      ->CreateTexture(pFile, pNameA, pHeap);
    }

    if (ppTexB != NULL && *pNameB != '\0') {
        *ppTexB = RP_GET_INSTANCE(RPSysKokeshiManager)
                      ->CreateTexture(pFile, pNameB, pHeap);
    }
}

/**
 * @brief Creates all lightmap textures
 *
 * @param drawScene Draw scene index
 */
void RPSysKokeshiManager::CreateLightTexture(u8 drawScene) {
    RPGrpDrawPathLightMap* pLightMap = RPGrpModelManager::GetCurrent()
                                           ->GetDrawPathManager(drawScene)
                                           ->GetDrawPathLightMap();

    for (u8 i = 0; i < LightMap_Max; i++) {
        pLightMap->GetLightTextureManager()->createTexture(
            LIGHT_TEXTURE_NAMES[i]);
    }
}

/**
 * @brief Resets the manager state
 */
void RPSysKokeshiManager::Reset() {
    mOutputAlpha = RPGrpModelRfl::DEFAULT_OUTPUT_ALPHA;
}

/**
 * @brief Loads all static lifetime resources required by this manager
 */
void RPSysKokeshiManager::LoadStaticResource() {
    RPSysResourceManager* pResourceManager =
        RP_GET_INSTANCE(RPSysResourceManager);
    RPSysSystem* pSystem = RP_GET_INSTANCE(RPSysSystem);

    pResourceManager->LoadKokeshiArchive();
    EGG::Archive* pKokeshiArchive = pResourceManager->GetKokeshiArchive();

    u32 nglSize = 0;
    void* pNglRes = RPSysResourceManager::GetFileFromArchive(
        pKokeshiArchive, RFL_RES_NAME, &nglSize);

    pSystem->startLoadCount();

    RFLErrcode err = RFLErrcode_NANDCommandfail;
    s32 reason = NAND_RESULT_BUSY;

    while (err == RFLErrcode_NANDCommandfail && reason == NAND_RESULT_BUSY) {
        err = RFLInitRes(mpNglBuffer, pNglRes, nglSize, false);

        if (err == RFLErrcode_NANDCommandfail) {
            reason = RFLGetLastReason();
        }

        // Time out eventually
        if (pSystem->isLoadCountEnd()) {
            break;
        }
    }

    switch (err) {
    case RFLErrcode_Success: {
        mLoadError = LoadError_Success;
        break;
    }

    case RFLErrcode_NANDCommandfail: {
        if (reason == NAND_RESULT_CORRUPT || reason == NAND_RESULT_MAXBLOCKS ||
            reason == NAND_RESULT_MAXFILES) {
            mLoadError = LoadError_NandFull;
        } else if (reason == NAND_RESULT_UNKNOWN) {
            mLoadError = LoadError_NandUnknown;
        } else {
            mLoadError = LoadError_Fail;
        }
        break;
    }

    default: {
        mLoadError = LoadError_Fail;
        break;
    }
    }

    RPSysResourceManager::Unk_802317C8();

    for (u16 i = 0; i < RFL_DEFAULT_CHAR_MAX; i++) {
        mpGuestNames[i] = fn_80262164(i + 0x3F2, 0, 0);
    }
}

/**
 * @brief Creates a Kokeshi-related model
 */
RPGrpModel* RPSysKokeshiManager::CreateModel(void* pFile, u16 index, u8 viewNo,
                                             u32 typeOption, u32 bufferOption,
                                             EGG::Heap* pHeap) {
    RPGrpModelResManager* pResManager = RPGrpModelResManager::GetCurrent();

    BOOL enabled;
    EGG::Heap* pOldHeap;

    if (pHeap != NULL) {
        enabled = OSDisableInterrupts();
        pOldHeap = pHeap->becomeCurrentHeap();
    }

    u8 fileCreated = 0;
    RPGrpHandle fileHandle = pResManager->CreateData(
        RPGrpModelResManager::Type_ResFile, pFile, 0, &fileCreated);

    u8 mdlCreated = 0;
    void* pMdlRes = pResManager->GetPtr(RPGrpModelResManager::Type_ResMdl,
                                        fileHandle, index);
    RPGrpHandle mdlHandle = pResManager->CreateData(
        RPGrpModelResManager::Type_ResMdl, pMdlRes, 0, &mdlCreated);

    pResManager->SetParent(mdlHandle, fileHandle);

    if (pHeap != NULL) {
        OSRestoreInterrupts(enabled);
        pOldHeap->becomeCurrentHeap();
    }

    return RPGrpModel::Construct(
        mdlHandle, viewNo, typeOption,
        bufferOption | nw4r::g3d::ScnMdl::BUFFER_RESTEXOBJ |
            nw4r::g3d::ScnMdl::BUFFER_RESGENMODE |
            nw4r::g3d::ScnMdl::BUFFER_RESTEVCOLOR);
}

/**
 * @brief Creates a Kokeshi face model
 */
RPGrpModel*
RPSysKokeshiManager::CreateNigaoeModel(const RPSysKokeshiLocation& rLocation,
                                       RFLResolution resolution, u32 exprFlags,
                                       u8 viewNo) {
    RFLSetCoordinate(RFLCoordinateType_X, RFLCoordinateType_Y);

    u16 index = rLocation.GetIndex();
    RFLMiddleDB* pMiddleDB = NULL;

    if (rLocation.GetDataSource() == RFLDataSource_Middle) {
        rLocation.GetMiddleDB()->GetRFLMiddleDB(index, &pMiddleDB, &index);
    }

    return RPGrpModelRfl::Construct(rLocation.GetDataSource(), index, pMiddleDB,
                                    resolution, exprFlags | RFLExpFlag_Normal,
                                    viewNo);
}

/**
 * @brief Creates a Kokeshi-related texture
 */
RPGrpTexture* RPSysKokeshiManager::CreateTexture(void* pFile, const char* pName,
                                                 EGG::Heap* pHeap) {
    RPGrpModelResManager* pResManager = RPGrpModelResManager::GetCurrent();

    BOOL enabled;
    EGG::Heap* pOldHeap;

    if (pHeap != NULL) {
        enabled = OSDisableInterrupts();
        pOldHeap = pHeap->becomeCurrentHeap();
    }

    u8 fileCreated = 0;
    RPGrpHandle fileHandle = pResManager->CreateData(
        RPGrpModelResManager::Type_ResFile, pFile, 0, &fileCreated);

    u8 texCreated = 0;
    void* pTexRes = pResManager->GetPtr(RPGrpModelResManager::Type_ResTex,
                                        fileHandle, pName);
    RPGrpHandle texHandle = pResManager->CreateData(
        RPGrpModelResManager::Type_ResTex, pTexRes, 0, &texCreated);

    pResManager->SetParent(texHandle, fileHandle);

    if (pHeap != NULL) {
        OSRestoreInterrupts(enabled);
        pOldHeap->becomeCurrentHeap();
    }

    return new RPGrpTexture(fileHandle, pName);
}

/**
 * @brief Creates a Kokeshi-related texture
 *
 * @param pTexData Texture data
 */
RPGrpTexture* RPSysKokeshiManager::CreateTexture(void* pTexData) {
    return static_cast<RPGrpTexture*>(pTexData);
}

/**
 * @brief Changes the clothing textures of the specified Mii model
 */
void RPSysKokeshiManager::ChangeTexture(RPGrpModel* pModel,
                                        RPGrpTexture* pTextureA,
                                        RPGrpTexture* pTextureB,
                                        RPSysKokeshiUnkTex* pX) {
    if (pTextureA != NULL) {
        if (pModel->ReplaceTexture(CLOTHING_TEXTURE_NAMES[ClothingTexture_A],
                                   *pTextureA, true) == 0 &&
            pX != NULL) {
            for (int i = 0; i < 3; i++) {
                const char* pName = NULL;
                mpUnk3C->Unk_80245CD4(pX->mUnk68, pX->mUnkA4Flag, i, &pName, NULL);
                if (pModel->ReplaceTexture(pName, *pTextureA, true) != 0) {
                    break;
                }
            }
        }
    }

    if (pTextureB != NULL) {
        pModel->ReplaceTexture(CLOTHING_TEXTURE_NAMES[ClothingTexture_B],
                               *pTextureB, true);
    }
}

/**
 * @brief Sets the material colors of the specified Mii model
 */
void RPSysKokeshiManager::SetMatColor(RPGrpModel* pModel, const GXColor* pBody,
                                      const GXColor* pSkin) {
    RPGrpModelMaterial* pMaterial = pModel->GetMaterial(MAIN_MATERIAL_NAME);

    static const u8 TEV_REGS[] = {0, 0, 0, 1};

    RPGrpModelMaterial::TevColor& rTevColor = pMaterial->GetTevColor();

    if (pBody != NULL) {
        rTevColor.SetColor(TEV_REGS[0], *pBody);
    }

    if (pSkin != NULL) {
        rTevColor.SetColor(TEV_REGS[3], *pSkin);
    }

    pMaterial->SetSyncFlags(0x30);
}

/**
 * @brief Gets the additional info about the specified Mii
 */
void RPSysKokeshiManager::GetAdditionalInfo(
    const RPSysKokeshiLocation& rLocation, RFLAdditionalInfo* pInfo) {

    u16 index = rLocation.GetIndex();
    RFLMiddleDB* pMiddleDB = NULL;

    if (rLocation.GetDataSource() == RFLDataSource_Middle) {
        rLocation.GetMiddleDB()->GetRFLMiddleDB(index, &pMiddleDB, &index);
    }

    RFLGetAdditionalInfo(pInfo, rLocation.GetDataSource(), pMiddleDB, index);
    fn_80246DEC(pInfo);
}

/**
 * @brief Removes the base scale of the model from the transformation matrix
 *
 * @param[out] pOut Transformation matrix with scaling removed
 * @param pModel Model whose scale should be used
 * @param pIn Initial transformation matrix
 */
void RPSysKokeshiManager::GetModelBaseScaleInvalidatedMtx(
    nw4r::math::MTX34* pOut, const RPGrpModel* pModel, const nw4r::math::MTX34* pIn) {

    nw4r::math::VEC3 scale = pModel->GetBaseScale();
    nw4r::math::VEC3 scaleInv;
    scaleInv.x = 1.0f / scale.x;
    scaleInv.y = 1.0f / scale.y;
    scaleInv.z = 1.0f / scale.z;

    nw4r::math::MTX34Copy(pOut, pIn);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pOut->m[i][j] *= (&scaleInv.x)[j];
        }
    }
}

/**
 * @brief Gets the archive filename for the specified hand type
 *
 * @param type Hand model type
 */
const char* RPSysKokeshiManager::GetHandFileName(u32 type) {
    return HAND_FILE_NAMES[type];
}

u16 RPSysKokeshiManager::Unk_80246008(int a, int b) {
    static const u16 TABLE[][2] = {
        {0, 0},
        {0, 1},
        {0, 1},
        {0, 0},
    };

    return TABLE[a][b];
}

/**
 * @brief Gets the name of the specified lightmap texture
 *
 * @param i Lightmap index
 */
const char* RPSysKokeshiManager::GetLightTextureName(u32 i) {
    return LIGHT_TEXTURE_NAMES[i];
}

bool RPSysKokeshiManager::Unk_80245FC0(int x) {
    static const int VALUES[] = {11, 12, 13};

    for (int i = 0; i < ARRAY_SIZE(VALUES); i++) {
        if (x == VALUES[i]) {
            return false;
        }
    }

    return true;
}

bool RPSysKokeshiManager::Unk_80245FA4(int x) {
    static const int VALUES[] = {14};

    for (int i = 0; i < ARRAY_SIZE(VALUES); i++) {
        if (x == VALUES[i]) {
            return true;
        }
    }

    return false;
}
