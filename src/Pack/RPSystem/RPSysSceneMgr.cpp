// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPAudio.h>
#include <Pack/RPSystem.h>
#include <Pack/RPSystem/RPSysUnkSingletons.h>

#include <egg/core.h>

#include <revolution/VI.h>

// Resort audio-system entry points (0x802B7xxx, owner unit not split; the
// Wii Sports versions were RPSndAudioMgr::resetSystem/shutdownSystem)
extern "C" {
void fn_802B7078(int frame);
void fn_802B7058(int frame);
void fn_802B7064();
}

/**
 * Resort emits this file's functions in reverse source order: the last
 * definition here is the first function in .text (0x8022FEF8).
 */

RPSysSceneMgr* RPSysSceneMgr::spInstance = NULL;

RPSysSceneMgr* RPSysSceneMgr::CreateInstance(EGG::Heap* pHeap) {
    if (spInstance == NULL) {
        spInstance = new (pHeap) RPSysSceneMgr(pHeap);
        return spInstance;
    }

    return NULL;
}

RPSysScene* RPSysSceneMgr::getCurrentSceneRP() const {
    return static_cast<RPSysScene*>(getCurrentScene());
}

void RPSysSceneMgr::Unk_802309EC(bool value) {
    mUnk38 = value;
}

bool RPSysSceneMgr::Unk_802309E4() const {
    return mUnk38;
}

bool RPSysSceneMgr::softReset(bool fromHBM) {
    if (mState == EState_Normal) {
        mState = EState_SoftReset;

        if (fromHBM) {
            mUnk38 = true;
            resetFadeFrame();
            resetFadeColor(true);
            mpSceneFader->setStatus(EGG::Fader::STATUS_PREPARE_IN);
        }

        return true;
    }

    return false;
}

bool RPSysSceneMgr::returnToMenu(s32 type, bool fromHBM) {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSaveDataMgr)->setSaveDisable(true);
        mState = EState_ReturnToMenu;
        mReturnToMenu = type;

        if (fromHBM) {
            VISetBlack(TRUE);
        }

        return true;
    }

    return false;
}

bool RPSysSceneMgr::shutdownSystem(bool fromHBM) {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSaveDataMgr)->setSaveDisable(true);
        mState = EState_Shutdown;

        if (fromHBM) {
            VISetBlack(TRUE);
        }

        return true;
    }

    return false;
}

bool RPSysSceneMgr::isNormalState() const {
    return mState == EState_Normal;
}

bool RPSysSceneMgr::Unk_80230854() const {
    return mState == EState_Guard;
}

bool RPSysSceneMgr::isShutDownReserved() const {
    return mState == EState_Shutdown;
}

s32 RPSysSceneMgr::getReturnToMenu() const {
    return mReturnToMenu;
}

void RPSysSceneMgr::resetGuard() {
    if (mState == EState_Guard) {
        mState = EState_Normal;
        fn_802B7064();
    }
}

bool RPSysSceneMgr::isApplicationEndReserved() {
    bool reserved = true;

    if (mState != EState_ReturnToMenu && mState != EState_Shutdown) {
        reserved = false;
    }

    return reserved;
}

bool RPSysSceneMgr::isDvdErrorApplicationEnd() {
    return mState != EState_Normal;
}

bool RPSysSceneMgr::changeNextSceneAfterFade(s32 id, bool reconfigure) {
    enum EMethod {
        Default,
        ChangeSiblingSceneAfterFadeOut,
        ReInitCurrentSceneAfterFadeOut,
        ChangeScene,
    };

    EMethod method;

    if (getCurrentSceneRP() != NULL) {
        s32 current = getCurrentSceneRP()->getSceneID();
        RP_GET_INSTANCE(RPSysSceneCreator)->getExitType(current);

        if (current == id) {
            if (reconfigure) {
                method = ChangeSiblingSceneAfterFadeOut;
            } else {
                method = ReInitCurrentSceneAfterFadeOut;
            }
        } else {
            method = ChangeSiblingSceneAfterFadeOut;
        }
    } else {
        method = ChangeScene;
    }

    switch (method) {
    case Default:
    case ChangeSiblingSceneAfterFadeOut: {
        return changeSiblingSceneAfterFadeOut(id);
    }
    case ReInitCurrentSceneAfterFadeOut: {
        return reinitCurrentSceneAfterFadeOut();
    }
    case ChangeScene: {
        changeScene(id);
        return true;
    }
    default: {
        return false;
    }
    }
}

void RPSysSceneMgr::resetFadeFrame() {
    mpSceneFader->setFrame(DEFAULT_FADE_FRAME);
    mCurrentFader->setFrame(DEFAULT_FADE_FRAME);
}

u16 RPSysSceneMgr::getFadeFrame() {
    return mpSceneFader->getFrame();
}

void RPSysSceneMgr::setFadeFrame(u16 frame) {
    mpSceneFader->setFrame(frame);
    mCurrentFader->setFrame(frame);
}

void RPSysSceneMgr::resetFadeColor(bool scene) {
    nw4r::ut::Color color = 0x000000FF;

    if (scene) {
        mpSceneFader->setColor(color);
    }

    mCurrentFader->setColor(color);
}

void RPSysSceneMgr::Unk_80230610(nw4r::ut::Color color) {
    mCurrentFader->setColor(color);
}

EGG::Fader::EStatus RPSysSceneMgr::getSceneStatus() {
    return mpSceneFader->getStatus();
}

void RPSysSceneMgr::setSceneStatus(EGG::Fader::EStatus status) {
    mpSceneFader->setStatus(status);
}

bool RPSysSceneMgr::startMgrFadeIn() {
    return fadeIn();
}

bool RPSysSceneMgr::startSceneFadeIn() {
    return mpSceneFader->fadeIn();
}

bool RPSysSceneMgr::startSceneFadeOut() {
    return mpSceneFader->fadeOut();
}

bool RPSysSceneMgr::Unk_80230580() {
    return mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT;
}

bool RPSysSceneMgr::Unk_80230544() {
    return mpSceneFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT;
}

bool RPSysSceneMgr::isDisplay() {
    bool display = false;

    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT &&
        mpSceneFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT) {
        display = true;
    }

    return display;
}

void RPSysSceneMgr::Unk_802304C4(u32 value) {
    mpMgrFader->setUnk24(value);
    mpSceneFader->setUnk24(value);
}

bool RPSysSceneMgr::Unk_80230474() {
    bool fading = false;

    if (Unk_80230408() || isFadeOut()) {
        fading = true;
    }

    return fading;
}

bool RPSysSceneMgr::Unk_80230408() {
    bool fadeIn = false;

    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_FADE_IN ||
        mpSceneFader->getStatus() == EGG::Fader::STATUS_FADE_IN) {
        fadeIn = true;
    }

    return fadeIn;
}

bool RPSysSceneMgr::isFadeOut() {
    bool fadeOut = false;

    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_FADE_OUT ||
        mpSceneFader->getStatus() == EGG::Fader::STATUS_FADE_OUT) {
        fadeOut = true;
    }

    return fadeOut;
}

bool RPSysSceneMgr::isTaskFinished() {
    if (RP_GET_INSTANCE(RPSysSaveDataMgr)->isNandAccessFinish() &&
        fn_80283104(GetNwc24Mgr()) &&
        !RP_GET_INSTANCE(RPSysSystem)->getNandThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getDvdThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getWc24Thread()->isTaskExist()) {
        return true;
    }

    return false;
}

bool RPSysSceneMgr::isSceneChangeEnable() {
    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT &&
        RP_GET_INSTANCE(RPSysSaveDataMgr)->isNandAccessFinish() &&
        fn_80283104(GetNwc24Mgr()) &&
        !RP_GET_INSTANCE(RPSysSystem)->getNandThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getDvdThread()->isTaskExist() &&
        !RP_GET_INSTANCE(RPSysSystem)->getWc24Thread()->isTaskExist()) {
        return true;
    }

    return false;
}

bool RPSysSceneMgr::calcSceneFader() {
    return mpSceneFader->calc();
}

void RPSysSceneMgr::drawSceneFader() {
    mpSceneFader->draw();
}

void RPSysSceneMgr::calcCurrentFader() {
    EGG::SceneManager::calcCurrentFader();

    if (mCurrentFader->getStatus() == EGG::Fader::STATUS_PREPARE_OUT) {
        resetFadeColor(false);
    }
}

void RPSysSceneMgr::drawMgrFader() {
    mCurrentFader->draw();
}

void RPSysSceneMgr::calcCurrentScene() {
    updateState();
    EGG::SceneManager::calcCurrentScene();
}

void RPSysSceneMgr::updateState() {
    if (mState == EState_Normal) {
        RP_GET_INSTANCE(RPSysSystem)->setCallBack();
        return;
    }

    if (isSceneChangeEnable()) {
        bool success = false;

        if (mState == EState_SoftReset) {
            success = RP_GET_INSTANCE(RPSysSceneCreator)->changeSoftReset();
        } else if (mState == EState_ReturnToMenu || mState == EState_Shutdown) {
            success = changeSceneAfterFadeOut(0);
        }

        if (success) {
            resetFadeFrame();
            resetFadeColor(false);

            if (mState == EState_SoftReset) {
                fn_802B7078(DEFAULT_FADE_FRAME);
                mState = EState_Guard;
            } else if (mState == EState_ReturnToMenu ||
                       mState == EState_Shutdown) {
                fn_802B7058(DEFAULT_FADE_FRAME);
            }
        }
    }
}

RPSysSceneMgr::RPSysSceneMgr(EGG::Heap* pHeap)
    : EGG::SceneManager(NULL),
      mpParentHeap(pHeap),
      mState(EState_Normal),
      mReturnToMenu(0),
      mUnk38(false) {
    mCurrentFader = mpMgrFader = new Unk_8023B9D0(
        0.0f, 0.0f, RP_GET_INSTANCE(RPSysSystem)->getFBWidth(),
        RP_GET_INSTANCE(RPSysSystem)->getFBHeight());

    mpSceneFader = new Unk_8023B9D0(0.0f, 0.0f,
                                    RP_GET_INSTANCE(RPSysSystem)->getFBWidth(),
                                    RP_GET_INSTANCE(RPSysSystem)->getFBHeight());

    resetFadeFrame();
    resetFadeColor(true);
}

RPSysSceneMgr::~RPSysSceneMgr() {}
