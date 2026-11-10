#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/RPSystem/RPSysSysMsgWinMgr.h>
#include <Pack/RPSystem/RPSysUnkSingletons.h>
#include <Pack/common_message.h>
#include <Pack/sports_message.h>

#include <egg/core.h>

#include <revolution/NAND.h>
#include <revolution/TPL.h>
#include <revolution/VF.h>

/**
 * @brief Pack-specific message file name
 */
#if defined(PACK_SPORTS)
#define PACK_MSG_FILE_NAME "sports_message.bmg"
#elif defined(PACK_PARTY)
#define PACK_MSG_FILE_NAME "party_message.bmg"
#endif

/**
 * @brief Banner icon TPL file name
 */
#define BANNER_ICON_FILE_NAME "banner.tpl"

/**
 * @brief Banner file names
 */
const char* RPSysSaveDataMgr::BANNER_FILE_NAMES[EBannerType_Max] = {
    "banner.bin",     // EBannerType_Real
    "/tmp/banner.bin" // EBannerType_Temp
};

/**
 * @brief Save file name
 */
const char* RPSysSaveDataMgr::SAVE_FILE_NAME = "Sports2.dat";


extern "C" {
void fn_80235D70(RPSysSysMsgWinMgr*, int);
Unk_80271E70* fn_80235D18(RPSysSysMsgWinMgr*);
void fn_80271DE4(Unk_80271E70*, int, ...);
void fn_802378BC(RPSysSystem*);
const wchar_t* fn_80262164(u32, int, int);
void fn_802317C8();
int fn_802315C8();
int fn_802315C0();
int fn_802315D0(int);
void* fn_802625D0(void*, EGG::Heap*);
void fn_802623D0(void*);
void fn_802624DC(void*);
int fn_802624B0(void*);
int fn_80262484(void*);
int fn_80262464(void*);
int fn_80262414(void*);
void fn_802624D0(void*);
void fn_8026253C(void*);
}

RPSysSaveDataMgr* RPSysSaveDataMgr::spInstance = NULL;

RPSysSaveDataMgr* RPSysSaveDataMgr::CreateInstance(EGG::Heap* pHeap) {
    if (spInstance == NULL) {
        spInstance = new (pHeap) RPSysSaveDataMgr(pHeap);
        return spInstance;
    }

    return NULL;
}

bool RPSysSaveDataMgr::requestNandFunc(void (*pFunc)(void*), bool arg) {
    if (prepareAccess(arg)) {
        RPSysSystem* pSystem = RP_GET_INSTANCE(RPSysSystem);
        EGG::TaskThread* pThread = pSystem->getNandThread();
        OSMessage msg = pSystem->getNandEndMessage();
        pThread->request(pFunc, NULL, msg);

        return true;
    }

    return false;
}

RPSportsSystemData* RPSysSaveDataMgr::fn_80234544() {
    return &mpSaveData->pBuffer->systemData;
}

void RPSysSaveDataMgr::fn_802343B8(const RPSportsSystemData* pSystemData) {
    mpSaveData->pBuffer->systemData = *pSystemData;
}

RPSportsPlayerData* RPSysSaveDataMgr::fn_8023439C(u32 idx) {
    return &mpSaveData->pBuffer->playerData[idx];
}

void RPSysSaveDataMgr::fn_802341D8(u32 idx,
                                   const RPSportsPlayerData* pPlayerData) {
    mpSaveData->pBuffer->playerData[idx] = *pPlayerData;
}

s32 RPSysSaveDataMgr::fn_802341A8(u32 answer) {
    if (answer == 0) {
        return 0;
    }

    if ((answer & 1) || (answer & 4)) {
        return 1;
    }

    return 2;
}

bool RPSysSaveDataMgr::existBannerFile() {
    if (!mbError) {
        u8 type;
        mNandErrorCode = NANDGetType(BANNER_FILE_NAMES[EBannerType_Real], &type);

        if (mNandErrorCode == NAND_RESULT_OK) {
            return true;
        }

        if (mNandErrorCode != NAND_RESULT_NOEXISTS) {
            mbError = true;
        }
    }

    return false;
}

bool RPSysSaveDataMgr::createBannerFile() {
    if (!mbError) {
        mNandErrorCode =
            NANDCreate(BANNER_FILE_NAMES[EBannerType_Temp],
                       NAND_PERM_RUSR | NAND_PERM_WUSR | NAND_PERM_RGRP |
                           NAND_PERM_ROTH,
                       0);

        if (mNandErrorCode != NAND_RESULT_OK &&
            mNandErrorCode != NAND_RESULT_EXISTS) {

            mbError = true;
            return false;
        }

        saveBannerFile(EBannerType_Temp);

        if (mbError) {
            return false;
        }

        char homeDir[NAND_MAX_PATH];
        mNandErrorCode = NANDGetHomeDir(homeDir);

        if (mNandErrorCode == NAND_RESULT_OK) {
            mNandErrorCode = fn_802315C8();
        }

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        mNandErrorCode = NANDMove(BANNER_FILE_NAMES[EBannerType_Temp], homeDir);

        if (mNandErrorCode == NAND_RESULT_OK ||
            mNandErrorCode == NAND_RESULT_EXISTS) {

            return true;
        }

        mbError = true;
        return false;
    }

    return false;
}

bool RPSysSaveDataMgr::saveBannerFile(EBannerType type) {
    if (!mbError) {
        NANDFileInfo info;
        mNandErrorCode =
            NANDOpen(BANNER_FILE_NAMES[type], &info, NAND_ACCESS_WRITE);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        mNandErrorCode = NANDWrite(&info, mpBannerFile, mBannerFileSize);

        if (mNandErrorCode != mBannerFileSize) {
            NANDClose(&info);
            mbError = true;
            return false;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        return true;
    }

    return false;
}

bool RPSysSaveDataMgr::deleteBannerFile() {
    mNandErrorCode = NANDDelete(BANNER_FILE_NAMES[EBannerType_Real]);

    if (mNandErrorCode == NAND_RESULT_OK ||
        mNandErrorCode == NAND_RESULT_NOEXISTS) {

        return true;
    }

    mbError = true;
    return false;
}

bool RPSysSaveDataMgr::existNandMemorySync() {
    if (!mbError) {
        mNandErrorCode =
            NANDCheck((mClusterFileSize / NAND_CLUSTER_SIZE) +
                          (mClusterFileSize % NAND_CLUSTER_SIZE != 0),
                      2, &mNandCheckAnswer);

        if (mNandErrorCode == NAND_RESULT_OK) {
            if (mNandCheckAnswer == 0) {
                mNandCheckAnswer = fn_802315C0();
            }

            if (mNandCheckAnswer == 0) {
                return true;
            }
        } else {
            mbError = true;
        }
    }

    return false;
}

bool RPSysSaveDataMgr::existSaveFile() {
    if (!mbError) {
        u8 type;
        mNandErrorCode = NANDGetType(SAVE_FILE_NAME, &type);

        if (mNandErrorCode == NAND_RESULT_OK) {
            return true;
        }

        if (mNandErrorCode != NAND_RESULT_NOEXISTS) {
            mbError = true;
        }
    }

    return false;
}

bool RPSysSaveDataMgr::createSaveFile() {
    if (!mbError) {
        mNandErrorCode =
            NANDCreate(SAVE_FILE_NAME,
                       NAND_PERM_RUSR | NAND_PERM_WUSR | NAND_PERM_RGRP |
                           NAND_PERM_ROTH,
                       0);

        if (mNandErrorCode != NAND_RESULT_OK &&
            mNandErrorCode != NAND_RESULT_EXISTS) {

            mbError = true;
            return false;
        }

        fn_8026253C(mpSaveData);
        return saveSync();
    }

    return false;
}

bool RPSysSaveDataMgr::deleteSaveFile() {
    mNandErrorCode = NANDDelete(SAVE_FILE_NAME);

    if (mNandErrorCode == NAND_RESULT_OK ||
        mNandErrorCode == NAND_RESULT_NOEXISTS) {

        return true;
    }

    mbError = true;
    return false;
}

bool RPSysSaveDataMgr::saveSync() {
    if (!mbError) {
        fn_802624DC(mpSaveData);
        fn_802623D0(mpSaveData);

        NANDFileInfo info;
        mNandErrorCode = NANDOpen(SAVE_FILE_NAME, &info, NAND_ACCESS_WRITE);

        if (mNandErrorCode == NAND_RESULT_OK) {
            mNandErrorCode = fn_802315C8();
        }

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        mNandErrorCode =
            NANDWrite(&info, mpSaveData->pBuffer, mpSaveData->size);

        if (mNandErrorCode != mpSaveData->size) {
            NANDClose(&info);
            mbError = true;
            return false;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        return true;
    }

    return false;
}

bool RPSysSaveDataMgr::loadSync() {
    if (!mbError) {
        NANDFileInfo info;
        mNandErrorCode = NANDOpen(SAVE_FILE_NAME, &info, NAND_ACCESS_READ);

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        mNandErrorCode =
            NANDRead(&info, mpSaveData->pBuffer, mpSaveData->size);

        if (mNandErrorCode >= 0) {
            if (mNandErrorCode != mpSaveData->size) {
                mNandErrorCode = 0;
                NANDClose(&info);
                mSaveCheckFlags |= 8;
                return false;
            }
        } else {
            NANDClose(&info);
            mbError = true;
            return false;
        }

        mNandErrorCode = NANDClose(&info);

        if (mNandErrorCode == NAND_RESULT_OK) {
            mNandErrorCode = fn_802315C8();
        }

        if (mNandErrorCode != NAND_RESULT_OK) {
            mbError = true;
            return false;
        }

        mSaveCheckFlags = 0;

        if (!fn_802624B0(mpSaveData)) {
            mSaveCheckFlags |= 1;
            return false;
        }

        if (!fn_80262484(mpSaveData)) {
            mSaveCheckFlags |= 2;
            return false;
        }

        if (!fn_80262464(mpSaveData)) {
            mSaveCheckFlags |= 8;
            return false;
        }

        if (!fn_80262414(mpSaveData)) {
            mSaveCheckFlags |= 4;
            return false;
        }

        if (fn_802315D0(4)) {
            mSaveCheckFlags |= 4;
            return false;
        }

        fn_802624D0(mpSaveData);
        return true;
    }

    return false;
}

bool RPSysSaveDataMgr::existPackFileAsync() {
    return requestNandFunc(existPackFileFunc, true);
}

bool RPSysSaveDataMgr::existNandMemoryAsync() {
    return requestNandFunc(existNandMemoryFunc, true);
}

bool RPSysSaveDataMgr::createPackFileAsync() {
    return requestNandFunc(createPackFileFunc, true);
}

bool RPSysSaveDataMgr::deletePackFileAsync() {
    return requestNandFunc(deletePackFileFunc, true);
}

bool RPSysSaveDataMgr::loadAsync() {
    return requestNandFunc(loadDataFunc, true);
}

bool RPSysSaveDataMgr::saveAsync() {
    if (requestNandFunc(saveDataFunc, false)) {
        mFlags.setBit(EFlag_5);
        return true;
    }

    return false;
}

bool RPSysSaveDataMgr::isAsyncFinish() const {
    return mFlags.offBit(EFlag_NandAccess) && mFlags.offBit(EFlag_AsyncSave);
}

bool RPSysSaveDataMgr::isNandAccessFinish() const {
    return mFlags.offBit(EFlag_NandAccess);
}

bool RPSysSaveDataMgr::isPackFileExist() const {
    return mFlags.onBit(EFlag_BannerFileExist) &&
           mFlags.onBit(EFlag_SaveFileExist);
}

bool RPSysSaveDataMgr::isNandMemoryExist() const {
    return mFlags.onBit(EFlag_NandMemoryExist);
}

bool RPSysSaveDataMgr::isSaveFileBroken() const {
    return mSaveCheckFlags != 0;
}

bool RPSysSaveDataMgr::isErrorOccured() const {
    return !mFlags.onBit(EFlag_DisableSave) && mbError;
}

s32 RPSysSaveDataMgr::getErrorCode() const {
    if (isErrorOccured()) {
        return mNandErrorCode;
    }

    return 0;
}

void RPSysSaveDataMgr::setSaveDisable(bool disable) {
    mFlags.changeBit(EFlag_DisableSave, disable);
}

u32 RPSysSaveDataMgr::getUserBlockSize() const {
    return (mClusterFileSize / NAND_BLOCK_SIZE) +
           (mClusterFileSize % NAND_BLOCK_SIZE != 0);
}

void RPSysSaveDataMgr::resetSaveData() {
    fn_8026253C(mpSaveData);
}

void RPSysSaveDataMgr::finishNandAccess() {
    mFlags.resetBit(EFlag_NandAccess);
}

void RPSysSaveDataMgr::update(bool display) {
    u32 access = mFlags.getDirect() & (1 << EFlag_NandAccess);

    if (!access && mFlags.offBit(EFlag_AsyncSave)) {
        return;
    }

    if (access) {
        return;
    }

    bool error = !mFlags.onBit(EFlag_DisableSave) && mbError;

    if (error) {
        if (!display) {
            return;
        }

        if (mNandErrorCode == -4 || mNandErrorCode == -9 ||
            mNandErrorCode == -11 || mNandErrorCode == -64) {

            showBusyWindow();
        } else if (mFlags.onBit(EFlag_5)) {
            showErrorWindow();
        } else {
            mFlags.resetBit(EFlag_AsyncSave);
        }
    } else {
        mFlags.resetBit(EFlag_AsyncSave);
    }
}

void RPSysSaveDataMgr::initBanner() {
    EGG::Heap* pHeap =
        RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP()->getHeap();

    fn_802317C8();

    const wchar_t* pSaveTitleMsg = fn_80262164(0x15F90, 0, 0);
    const wchar_t* pSaveSubTitleMsg = fn_80262164(0x15F90, 1, 0);

    NANDInitBanner(mpBannerFile, 0, pSaveTitleMsg, pSaveSubTitleMsg);

    u8* pTplBuffer =
        static_cast<u8*>(EGG::Heap::alloc(mBannerFileSize, 32, pHeap));

    void* pTplFile =
        EGG::DvdRipper::loadToMainRAM(BANNER_ICON_FILE_NAME, pTplBuffer, pHeap,
                                      EGG::DvdRipper::ALLOC_DIR_HEAD);

    TPLPalette* pPalette = static_cast<TPLPalette*>(pTplFile);
    TPLBind(pPalette);

    TPLDescriptor* pBannerTexture = TPLGet(pPalette, ETplIndex_BannerTexture);

    memcpy(mpBannerFile->bannerTexture, pBannerTexture->textureHeader->data,
           sizeof(mpBannerFile->bannerTexture));

    for (int i = 0; i < BANNER_ICON_FRAME_NUM; i++) {
        TPLDescriptor* pIconTexture =
            TPLGet(pPalette, ETplIndex_IconTexture + i);

        if (pIconTexture != NULL) {
            memcpy(mpBannerFile->iconTexture[i],
                   pIconTexture->textureHeader->data, NAND_BANNER_ICON_SIZE);

            int speed = mpBannerFile->iconSpeed & ~(0b11 << (i * 2));
            mpBannerFile->iconSpeed = speed | ((2 & 0b11) << (i * 2));
        }
    }

    // Frame with a speed of zero marks the end of the animation (two bits
    // per frame; the NAND_BANNER_SET_ICON_SPEED macro shifts by the frame
    // index only)
    mpBannerFile->iconSpeed =
        mpBannerFile->iconSpeed & ~(0b11 << (BANNER_ICON_FRAME_NUM * 2)) |
        ((0 & 0b11) << (BANNER_ICON_FRAME_NUM * 2));
}

void RPSysSaveDataMgr::fn_802336BC() {
    mFlags.makeAllZero();
}

bool RPSysSaveDataMgr::prepareAccess(bool arg) {
    if (mFlags.onBit(EFlag_DisableSave) && arg) {
        return false;
    }

    if (RP_GET_INSTANCE(RPSysSceneMgr)
            ->getCurrentSceneRP()
            ->isNandAccessEnable()) {

        clearError();

        mFlags.setBit(EFlag_NandAccess);
        mFlags.setBit(EFlag_AsyncSave);
        mFlags.resetBit(EFlag_5);

        return true;
    }

    return false;
}

void RPSysSaveDataMgr::clearError() {
    mbError = false;
    mNandErrorCode = NAND_RESULT_OK;
    mNandCheckAnswer = 0;
    mSaveCheckFlags = 0;

    mFlags.resetBit(EFlag_ErrorWindow);
    mFlags.resetBit(EFlag_AsyncSave);
}

void RPSysSaveDataMgr::showBusyWindow() {
    if (mFlags.offBit(EFlag_ErrorWindow)) {
        RPSysSysMsgWinMgr* pMgr = GetSysMsgWinMgr();

        if (pMgr->mState == -1) {
            fn_802378BC(RP_GET_INSTANCE(RPSysSystem));
            fn_80235D70(pMgr, 0);

            if (mNandErrorCode == -64) {
                fn_80271DE4(fn_80235D18(pMgr), 0x277E, 0);
            } else {
                fn_80271DE4(fn_80235D18(pMgr), 0x2774, 0);
            }

            mFlags.setBit(EFlag_ErrorWindow);
        }
    }
}

void RPSysSaveDataMgr::showErrorWindow() {
    RPSysSysMsgWinMgr* pMgr = GetSysMsgWinMgr();

    if (mFlags.offBit(EFlag_ErrorWindow)) {
        if (pMgr->mState == -1) {
            fn_80235D70(pMgr, 0);
            fn_80271DE4(fn_80235D18(pMgr), 0x2775, 0);

            mFlags.setBit(EFlag_ErrorWindow);
        }
    } else if (fn_80235D18(pMgr)->Unk_48()) {
        RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(0, false);
    }
}

void RPSysSaveDataMgr::existPackFileFunc(void* /* pArg */) {
    RPSysSaveDataMgr* pMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

    pMgr->mFlags.changeBit(EFlag_BannerFileExist, pMgr->existBannerFile());
    pMgr->mFlags.changeBit(EFlag_SaveFileExist, pMgr->existSaveFile());
}

void RPSysSaveDataMgr::existNandMemoryFunc(void* /* pArg */) {
    RPSysSaveDataMgr* pMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

    pMgr->mFlags.changeBit(EFlag_NandMemoryExist, pMgr->existNandMemorySync());
}

void RPSysSaveDataMgr::createPackFileFunc(void* /* pArg */) {
    RPSysSaveDataMgr* pMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

    pMgr->mFlags.changeBit(EFlag_SaveFileExist, pMgr->createSaveFile());
    pMgr->mFlags.changeBit(EFlag_BannerFileExist, pMgr->createBannerFile());
}

void RPSysSaveDataMgr::deletePackFileFunc(void* /* pArg */) {
    RPSysSaveDataMgr* pMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

    pMgr->mFlags.changeBit(EFlag_BannerFileExist, !pMgr->deleteBannerFile());
    pMgr->mFlags.changeBit(EFlag_SaveFileExist, !pMgr->deleteSaveFile());
}

void RPSysSaveDataMgr::loadDataFunc(void* /* pArg */) {
    RP_GET_INSTANCE(RPSysSaveDataMgr)->loadSync();
}

void RPSysSaveDataMgr::saveDataFunc(void* /* pArg */) {
    RPSysSaveDataMgr* pMgr = RP_GET_INSTANCE(RPSysSaveDataMgr);

    if (pMgr->mFlags.offBit(EFlag_DisableSave)) {
        pMgr->saveSync();
        pMgr->saveBannerFile(EBannerType_Real);
    }
}

RPSysSaveDataMgr::RPSysSaveDataMgr(EGG::Heap* pHeap)
    : IRPSysHostIOSocket("Save File"), mpParentHeap(pHeap) {

    mSaveCheckFlags = 0;
    mFlags.makeAllZero();
    clearError();

    mBannerFileSize = SAVE_BANNER_SIZE;

    SaveBuffer* pBuf = new (pHeap, 32) SaveBuffer;
    if (pBuf != NULL) {
        pBuf = static_cast<SaveBuffer*>(fn_802625D0(pBuf, pHeap));
    }
    mpSaveData = pBuf;

    u32 saveSize = mpSaveData->size;
    u32 bannerSize = mBannerFileSize;
    mClusterFileSize = (bannerSize / NAND_CLUSTER_SIZE +
                        saveSize / NAND_CLUSTER_SIZE +
                        (bannerSize % NAND_CLUSTER_SIZE != 0) +
                        (saveSize % NAND_CLUSTER_SIZE != 0)) *
                       NAND_CLUSTER_SIZE;

    mpBannerFile = static_cast<NANDBanner*>(
        EGG::Heap::alloc(sizeof(NANDBanner), 32, pHeap));

    memset(mpBannerFile->title, 0, sizeof(mpBannerFile->title));
    memset(mpBannerFile->subtitle, 0, sizeof(mpBannerFile->subtitle));
}

RPSysSaveDataMgr::~RPSysSaveDataMgr() {}
