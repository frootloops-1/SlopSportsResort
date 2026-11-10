// Keep the header-only .sdata2 constant (cm2hw) out of this object
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPAudio.h>
#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <egg/math.h>

#include <homebuttonMiniLib.h>

#include <nw4r/ut.h>

#include <revolution/GX.h>
#include <revolution/VI.h>

#include <cstring>

/**
 * Resort emits this file's functions in reverse source order: the last
 * definition here is the first function in .text (0x80242750).
 */

// Placeholders for symbols that symbols.txt has not named yet
extern RPSysDvdStatus* lbl_806F4CB8;    // RPSysDvdStatus::spInstance
extern RPSysProjectLocal* lbl_806F4CA0; // RPSysProjectLocal::spInstance
extern EGG::CoreControllerMgr* lbl_806F4A08; // EGG::CoreControllerMgr::sInstance

extern "C" {
// HBM API missing from homebuttonMiniLib/HBMApi.h
void HBMCreateSound(void* pSoundData, void* pMemBuf, u32 memSize);
void HBMUpdateSound();

// RPSndAudioMgr wrappers (0x802B7030..)
void fn_802B7030();
void fn_802B7044();
void fn_802B70C0(int);
}

/******************************************************************************
 *
 * Statics (.sbss order: 0x806F4D50, 0x806F4D54, 0x806F4D58)
 *
 ******************************************************************************/

Unk_806F4D50* Unk_806F4D50::spInstance = NULL;

/**
 * @brief HOME Menu sound archive manager (unused in Resort)
 */
RPSndHomeMenuArcMgr* RPSysHomeMenuMgr::spHomeMenuArcMgr = NULL;

RPSysHomeMenuMgr* RPSysHomeMenuMgr::spInstance = NULL;

/******************************************************************************
 *
 * RPSysHomeMenuMgr
 *
 ******************************************************************************/


RPSysHomeMenuMgr* RPSysHomeMenuMgr::CreateInstance(EGG::Heap* pHeap) {
    if (spInstance == NULL) {
        spInstance = new (pHeap) RPSysHomeMenuMgr(pHeap);
        return spInstance;
    }

    return NULL;
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysHomeMenuMgr::RPSysHomeMenuMgr(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mIsInitialized = false;
    mIsDisabled = false;
    mUnk51 = false;

    mpBanIcon = new (pHeap) BanIcon();
    init();

    std::memset(&mHBMDataInfo, 0, sizeof(mHBMDataInfo));
    std::memset(&mHBMControllerData, 0, sizeof(mHBMControllerData));

    mpProjectLocal = lbl_806F4CA0;

    mHBMDataInfo.layoutBuf = NULL;
    mHBMDataInfo.spkSeBuf = NULL;
    mHBMDataInfo.msgBuf = NULL;
    mHBMDataInfo.configBuf = NULL;
    mHBMDataInfo.mem = new (pHeap) u8[HBM_WORK_SIZE];
    mHBMDataInfo.sound_callback = NULL;
    mHBMDataInfo.backFlag = FALSE;
    mHBMDataInfo.region = SC_LANG_EN;
    mHBMDataInfo.cursor = FALSE;
    mHBMDataInfo.configBufSize = HBM_CONFIG_SIZE;
    mHBMDataInfo.memSize = HBM_WORK_SIZE;
    if (mpProjectLocal->getFrameRate() == RPSysProjectLocal::EFrameRate_50Hz) {
        mHBMDataInfo.frameDelta = 60.0f / 50.0f;
    } else {
        mHBMDataInfo.frameDelta = 60.0f / 60.0f;
    }
    mHBMDataInfo.adjust.x = 1.0f;
    mHBMDataInfo.adjust.y = 1.0f;
    mHBMDataInfo.pAllocator = NULL;

    std::memset(mHBMDataInfo.mem, 0, HBM_WORK_SIZE);

    mpSoundWork = new (pHeap) u8[HBM_SOUND_WORK_SIZE];
}

/**
 * @brief Destructor
 */
RPSysHomeMenuMgr::~RPSysHomeMenuMgr() {}

/**
 * @brief Initializes this manager's state
 */
void RPSysHomeMenuMgr::init() {
    mIsDisabled = false;
    mIsActive = false;
    mIsVisible = false;
    mIsSoftReset = false;

    mMenuState = EMenuState_End;
    mAccIndex = 0;

    for (int i = 0; i < KPAD_MAX_CONTROLLERS; i++) {
        for (int j = 0; j < ACC_HISTORY_LENGTH; j++) {
            mAccValue[i][j] = 1.0f;
        }
    }

    VISetBlack(FALSE);
    disable(false);
}

/**
 * @brief Initializes the HBM library
 */
void RPSysHomeMenuMgr::initHomeButtonInfo() {
    EGG::Archive* pCommonArchive = RPSysResourceManager::Unk_802317D4();
    EGG::Archive* pLocalArchive = RPSysResourceManager::Unk_802317C8();

    HBMDataInfo* pHBMDataInfo = &mHBMDataInfo;

    void* pIconTexture = RPSysResourceManager::GetFileFromArchive(
        pCommonArchive, "/HomeMenu/homeBtnIcon.bti");

    mpBanIcon->setTexture(static_cast<EGG::ResTIMG*>(pIconTexture));

    switch (mpProjectLocal->getLanguage()) {
    case RPSysProjectLocal::EArea_England:
    case RPSysProjectLocal::EArea_USA: {
        pHBMDataInfo->region = SC_LANG_EN;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_ENG.arc");
        break;
    }

    case RPSysProjectLocal::EArea_France:
    case RPSysProjectLocal::EArea_Unk8: {
        pHBMDataInfo->region = SC_LANG_FR;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_FRA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Germany: {
        pHBMDataInfo->region = SC_LANG_DE;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_GER.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Italy: {
        pHBMDataInfo->region = SC_LANG_IT;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_ITA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Spain:
    case RPSysProjectLocal::EArea_Unk9: {
        pHBMDataInfo->region = SC_LANG_SP;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_SPA.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Netherlands: {
        pHBMDataInfo->region = SC_LANG_NL;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_NED.arc");
        break;
    }

    case RPSysProjectLocal::EArea_Japan: {
        pHBMDataInfo->region = SC_LANG_JP;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn.arc");
        break;
    }

    default: {
        pHBMDataInfo->region = SC_LANG_EN;

        pHBMDataInfo->layoutBuf = RPSysResourceManager::GetFileFromArchive(
            pLocalArchive, "/HomeMenu/homeBtn_ENG.arc");
        break;
    }
    }

    pHBMDataInfo->spkSeBuf = RPSysResourceManager::GetFileFromArchive(
        pCommonArchive, "/HomeMenu/SpeakerSe.arc");

    pHBMDataInfo->msgBuf = RPSysResourceManager::GetFileFromArchive(
        pCommonArchive, "/HomeMenu/home_nosave.csv");

    pHBMDataInfo->configBuf = RPSysResourceManager::GetFileFromArchive(
        pCommonArchive, "/HomeMenu/config.txt");

    HBMCreate(pHBMDataInfo);

    void* pSoundData = RPSysResourceManager::GetFileFromArchive(
        pCommonArchive, "/HomeMenu/HomeButtonSe.arc");

    HBMCreateSound(pSoundData, mpSoundWork, HBM_WORK_SIZE);
    HBMSetAdjustFlag(TRUE);

    mIsInitialized = true;
    mUnk51 = false;
}

/**
 * @brief Checks whether the HOME Menu should be opened
 */
void RPSysHomeMenuMgr::checkMenuStart() {
    bool start = false;

    for (int i = 0; i < KPAD_MAX_CONTROLLERS; i++) {
        if (lbl_806F4A08->getNthController(i)->downTrigger(EGG::cCORE_BUTTON_HOME)) {
            start = mUnk51 && Unk_80242EC0(i);
            break;
        }
    }

    if (!start) {
        return;
    }

    if (mIsDisabled || lbl_806F4CB8->getErrorStatus() < 0) {
        mpBanIcon->switchOn();
    } else if (RP_GET_INSTANCE(RPSysSceneMgr)
                   ->getCurrentSceneRP()
                   ->isSceneChangeEnable()) {
        mMenuState = EMenuState_Start;
        mIsActive = true;
        mIsVisible = false;

        fn_802B7044();
    } else {
        mpBanIcon->switchOn();
    }
}

void RPSysHomeMenuMgr::Unk_802430A4() {
    mMenuState = EMenuState_Open;
    mIsSoftReset = true;

    HBMInit();

    RPSysCoreController::stopMotorAll();
    RPSysCoreController::pushDpdCtrlStackAll(true);
    RPSysCoreController::pushKPADParamStackAll();

    RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP()->Unk_8022FC5C();

    mIsSoftReset = false;
    mpBanIcon->Unk_80242970();
}

void RPSysHomeMenuMgr::Unk_80243060() {
    mMenuState = EMenuState_End;
    mIsActive = false;
    mIsVisible = false;

    fn_802B7030();

    RPSysCoreController::popDpdCtrlStackAll();
    RPSysCoreController::popKPADParamStackAll();

    RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP()->Unk_8022FC08();
}

/**
 * @brief Checks whether the HOME Menu should be closed
 */
void RPSysHomeMenuMgr::checkMenuEnd() {
    if (lbl_806F4CB8->getErrorStatus() >= 0) {
        mIsVisible = true;

        switch (HBMCalc(&mHBMControllerData)) {
        case HBM_SELECT_BTN2: {
            mMenuState = EMenuState_Reset;
            RP_GET_INSTANCE(RPSysSceneMgr)->softReset(true);
            fn_802B70C0(0);
            break;
        }

        case HBM_SELECT_BTN1: {
            RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(0, true);
            Unk_80243060();
            break;
        }

        case HBM_SELECT_HOMEBTN: {
            Unk_80243060();
            break;
        }
        }
    } else {
        for (int i = 0; i < KPAD_MAX_CONTROLLERS; i++) {
            if (lbl_806F4A08->getNthController(i)->downTrigger(EGG::cCORE_BUTTON_HOME)) {
                mpBanIcon->switchOn();
                break;
            }
        }
    }
}

bool RPSysHomeMenuMgr::Unk_80242EC0(int chan) {
    for (int i = 0; i < ACC_HISTORY_LENGTH; i++) {
        if (EGG::Mathf::abs(mAccValue[chan][i] - 1.0f) > 0.4f) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Performs a soft reset
 *
 * @return Whether HBM will perform the reset
 */
bool RPSysHomeMenuMgr::softReset() {
    if (mIsActive && !mIsSoftReset) {
        HBMStartBlackOut();
        mIsSoftReset = true;
    }

    return mIsActive;
}

void RPSysHomeMenuMgr::Unk_80242E64() {
    mUnk51 = true;
}

/**
 * @brief Updates this manager's state
 */
void RPSysHomeMenuMgr::update() {
    for (int i = 0; i < KPAD_MAX_CONTROLLERS; i++) {
        mAccValue[i][mAccIndex] =
            lbl_806F4A08->getNthController(i)->getCoreStatus()->acc_value;
    }

    if (++mAccIndex >= ACC_HISTORY_LENGTH) {
        mAccIndex = 0;
    }

    mHBMDataInfo.adjust.x =
        static_cast<f32>(RPGrpScreen::GetSizeXMax()) /
        static_cast<f32>(RPGrpScreen::GetSizeXMax(RPGrpScreen::TV_MODE_STD));
    mHBMDataInfo.adjust.y = 1.0f;

    if (mIsActive) {
        for (s32 chan = 0; chan < KPAD_MAX_CONTROLLERS; chan++) {
            RPSysCoreController* pController =
                static_cast<RPSysCoreController*>(
                    lbl_806F4A08->getNthController(chan));

            if (pController != NULL && pController->isCoreBaseDevice()) {
                mKPADStatus[chan] = *pController->getCoreStatus();

                mHBMControllerData.wiiCon[chan].kpad = &mKPADStatus[chan];
                mHBMControllerData.wiiCon[chan].pos = mKPADStatus[chan].pos;

                // Classic-style devices: 2 classic, 16/17 (Resort SDK
                // types beyond this project's WPAD.h), 7 MotionPlus + classic
                u8 devType = mKPADStatus[chan].dev_type;
                if (devType == WPAD_DEV_CLASSIC || devType == 16 ||
                    devType == 17 || devType == 7) {
                    mHBMControllerData.wiiCon[chan].use_devtype =
                        WPAD_DEV_CORE;
                } else {
                    mHBMControllerData.wiiCon[chan].use_devtype = devType;
                }
            } else {
                mHBMControllerData.wiiCon[chan].kpad = NULL;
                mHBMControllerData.wiiCon[chan].pos.x = 10000.0f;
                mHBMControllerData.wiiCon[chan].pos.y = 10000.0f;
            }
        }
    }

    if (mIsInitialized) {
        switch (mMenuState) {
        case EMenuState_End: {
            checkMenuStart();
            break;
        }

        case EMenuState_Start: {
            Unk_802430A4();
            break;
        }

        case EMenuState_Open: {
            checkMenuEnd();
            break;
        }

        case EMenuState_Reset: {
            Unk_80243060();
            break;
        }
        }

        mpBanIcon->calc();
        HBMUpdateSound();
    }
}

/**
 * @brief Renders the HOME Menu if it is visible
 */
void RPSysHomeMenuMgr::draw() {
    if (!mIsInitialized) {
        return;
    }

    if (isActive() && mIsVisible) {
        HBMDraw();
    }
}

/**
 * @brief Renders the ban icon if it is visible
 */
void RPSysHomeMenuMgr::drawBanIcon() {
    if (!mIsInitialized) {
        return;
    }

    if (mpBanIcon->isDisp()) {
        mpBanIcon->draw();
    }
}

/******************************************************************************
 *
 * BanIcon
 *
 ******************************************************************************/

//! Width of the area the ban icon is anchored to (4:3 units)
#define BANICON_X 552.0f
//! Height of the area the ban icon is anchored to
#define BANICON_Y 388.0f

//! Width of the ban icon
#define BANICON_SIZE 28.0f

/**
 * @brief Resets this icon's state
 */
void RPSysHomeMenuMgr::BanIcon::clear() {
    mState = EState_Hide;
    mTimer = 0;
    mAlpha = 0;
}

/**
 * @brief Enables this icon
 */
void RPSysHomeMenuMgr::BanIcon::switchOn() {
    if (mState == EState_Hide) {
        mState = EState_FadeIn;
        mTimer = 0;
        mAlpha = 0;
    }
}

/**
 * @brief Updates this icon's state
 */
void RPSysHomeMenuMgr::BanIcon::calc() {
    switch (mState) {
    case EState_Hide: {
        break;
    }

    case EState_FadeIn: {
        if (++mTimer < FADE_LENGTH) {
            mAlpha = mTimer * 255 / FADE_LENGTH;
        } else {
            mState = EState_Disp;
            mTimer = 0;
            mAlpha = 255;
        }
        break;
    }

    case EState_Disp: {
        if (++mTimer >= DISP_LENGTH) {
            mState = EState_FadeOut;
            mTimer = 0;
        }

        mAlpha = 255;
        break;
    }

    case EState_FadeOut: {
        if (++mTimer < FADE_LENGTH) {
            mAlpha = 255 - mTimer * 255 / FADE_LENGTH;
        } else {
            mState = EState_Hide;
            mTimer = 0;
            mAlpha = 0;
        }
        break;
    }
    }
}

void RPSysHomeMenuMgr::BanIcon::Unk_80242970() {
    switch (mState) {
    case EState_FadeIn: {
        mTimer = FADE_LENGTH - 1 - mTimer;
        mState = EState_FadeOut;
        calc();
        break;
    }

    case EState_Disp: {
        mTimer = 0;
        mState = EState_FadeOut;
        calc();
        break;
    }
    }
}

/**
 * @brief Renders this icon's state
 */
void RPSysHomeMenuMgr::BanIcon::draw() {
    GXColor color;
    color.r = color.g = color.b = 255;
    color.a = mAlpha;

    RPGrpScreen screen;
    screen.SetCanvasMode(RPGrpScreen::CANVAS_CC);
    screen.SetNearZ(-10000.0f);
    screen.SetFarZ(10000.0f);
    screen.SetProjectionType(RPGrpScreen::PROJ_ORTHO);
    screen.SetProjectionGX();

    f32 x = -RPGrpScreen::GetSizeXMax() * 0.45f;
    f32 y = -RPGrpScreen::GetSizeYMax() * 0.425f;

    screen.BeginDrawQuadTexture(false);

    screen.DrawQuadTexture(x, y + 56.0f, x + 56.0f, y, mpTexture, color);
}

/******************************************************************************
 *
 * Unk_806F4D50
 *
 ******************************************************************************/

Unk_806F4D50* Unk_806F4D50::CreateInstance(EGG::Heap* pHeap) {
    if (spInstance == NULL) {
        spInstance = new (pHeap) Unk_806F4D50(pHeap);
        return spInstance;
    }

    return NULL;
}

Unk_806F4D50::Unk_806F4D50(EGG::Heap* pHeap) : mpParentHeap(pHeap) {
    mUnk08 = false;
}

Unk_806F4D50::~Unk_806F4D50() {}
