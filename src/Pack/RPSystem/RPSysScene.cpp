// Keep the header-only .sdata2 constant (cm2hw) out of this object
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPAudio.h>
#include <Pack/RPAudio/Unk_802BCF00.h>
#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>
#include <Pack/RPSystem/RPSysSysMsgWinMgr.h>
#include <Pack/RPSystem/RPSysUnkSingletons.h>

#include <egg/core.h>

#include <revolution/GX.h>
#include <revolution/OS.h>

/**
 * Resort rewrote this file. Its functions are emitted in reverse source
 * order: the last definition here is the first function in .text
 * (0x8022F30C), the first one is 0x8022FE18.
 *
 * Statements marked "NEEDS" are known from the asm but cannot be written
 * until a shared header gains the member/accessor (see the task note).
 */

// Placeholders for objects/functions whose owners are not split or named yet
extern RPSysDvdStatus* lbl_806F4CB8;   // RPSysDvdStatus::spInstance
extern void* lbl_806F4D00;

extern "C" {
// RPSysScene functions outside this split (0x802311B0-0x80231588)
void fn_802311B0(RPSysScene* pScene);
void fn_802312E4(RPSysScene* pScene);
void fn_8023131C(RPSysScene* pScene);
void fn_802314E4(RPSysScene* pScene);

// RPSysCommonObject (Resort, 8 bytes)
void fn_8023282C(RPSysCommonObject* pObj);
void fn_802328D8(RPSysCommonObject* pObj);
void fn_8023299C(RPSysCommonObject* pObj);

// RPSysEffectMgr

// Singletons reached through the asserting accessors
void* fn_80269E6C(StaticMem* pMem);
void fn_8026A33C(StaticMem* pMem, RPSysScene* pScene);
void fn_8026A618(StaticMem* pMem);
void fn_80277A00(ControllerManager* pMgr);
void fn_80237DDC(RPSysDbgScenePatroler* pPatroler);
void fn_80237E90(RPSysDbgScenePatroler* pPatroler);
void fn_8035EC98(SDCardMgr* pMgr);
void fn_8035EC9C(SDCardMgr* pMgr, s32 id);
void fn_8035ECA0(SDCardMgr* pMgr);
void fn_8035ECA4(SDCardMgr* pMgr);

// Others
void fn_802416A4();
void fn_8023BD6C(void* pObj);
void fn_802325E0(RPSysResourceManager* pMgr);
}

RPSysScene::UnkStruct RPSysScene::sUnkStruct;

inline void RPSysScene::outgoingScene() {
    RPSysCoreController::stopMotorAll();
    RP_GET_INSTANCE(RPSysEffectMgr)->stopAllEffect();
    RP_GET_INSTANCE(RPSysEffectMgr)->resetCreator(mpEffectCreator);
}

bool RPSysScene::isSceneDisplay() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->isDisplay();
}

bool RPSysScene::Unk_8022FE10() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->Unk_80230474();
}

bool RPSysScene::isSceneChangeEnable() const {
    return RP_GET_INSTANCE(RPSysSceneMgr)->isSceneChangeEnable();
}

bool RPSysScene::isNandAccessEnable() const {
    return !RP_GET_INSTANCE(RPSysSceneMgr)->isFadeOut() &&
           RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished();
}

bool RPSysScene::Unk_8022FD68() const {
    return !RP_GET_INSTANCE(RPSysSceneMgr)->isFadeOut() &&
           RP_GET_INSTANCE(RPSysSceneMgr)->isTaskFinished();
}

void RPSysScene::setFadeFrame(u16 frame) {
    RP_GET_INSTANCE(RPSysSceneMgr)->setFadeFrame(frame);
}

void RPSysScene::Unk_8022FCD4() {
    RPSysSystem* pSystem = RP_GET_INSTANCE(RPSysSystem);
    mpHeapMem1 = pSystem->Unk_8022D650(pSystem->getUnkHeap10(), 1, -1, TRUE, 0,
                                       TRUE);
    mpHeapMem1->mName = "sceneMem1";

    mpHeapDepend = RP_GET_INSTANCE(RPSysSystem)->Unk_8022D650(
        RP_GET_INSTANCE(RPSysSystem)->getUnkHeap14(), 1, -1, TRUE, 0, TRUE);
    mpHeapDepend->mName = "sceneDependOnTarget";
}

void RPSysScene::Unk_8022FCCC() {
    mpHeapMem1->becomeCurrentHeap();
}

void RPSysScene::Unk_8022FCC4() {
    mpHeapDepend->becomeCurrentHeap();
}

void RPSysScene::Unk_8022FCBC() {
    getHeap()->becomeCurrentHeap();
}

void RPSysScene::Unk_8022FCB8() {}

void RPSysScene::Unk_8022FC5C() {
    if (mPauseCount == 0) {
        RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneRP()->pauseCallBack(
            true);
    }

    mPauseCount++;
}

void RPSysScene::Unk_8022FC08() {
    if (mPauseCount == 1) {
        pauseCallBack(false);
    }

    mPauseCount--;
}

RPSysScene::RPSysScene()
    : mpRenderer(NULL),
      mpCommonObject(NULL),
      mpEffectCreator(NULL),
      mpHeapMem1(NULL),
      mpHeapDepend(NULL),
      mpSceneHeap(NULL),
      mCreatorSceneID(-1),
      mpUnk68(NULL) {
    mUnk5C = false;
    mpFader = NULL;
    mPhase = 0;
}

void RPSysScene::Configure() {}

void RPSysScene::enter() {
    if (RP_GET_INSTANCE(RPSysSceneMgr)->Unk_80230854()) {
        fn_8026A618(GetStaticMem());
        RP_GET_INSTANCE(RPSysSceneMgr)->resetGuard();
    }

    RP_GET_INSTANCE(RPSysHomeMenuMgr)->disable(true);
    fn_80237E90(GetDbgScenePatroler());

    mPhase = 0;
    OSGetTick();
    RP_GET_INSTANCE(RPSysResourceManager)->setUnk60(false);
    init();
    OSGetTick();

    mPhase = 1;
    RP_GET_INSTANCE(RPSysResourceManager)->setUnk60(true);

    if (RP_GET_INSTANCE(RPSysSceneMgr)->getCurrentSceneID() !=
        RP_GET_INSTANCE(RPSysSceneMgr)->getPreviousSceneID()) {
        fn_802325E0(RP_GET_INSTANCE(RPSysResourceManager));
    }

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->drawMgrFader();
        fn_802314E4(this);
        fn_8023131C(this);
    }

    OSGetTick();
    mPhase = 2;
    RP_GET_INSTANCE(RPSysResourceManager)->setUnk60(false);
    Configure();
    OSGetTick();

    mPhase = 3;
    RP_GET_INSTANCE(RPSysResourceManager)->setUnk60(true);

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->drawMgrFader();
        fn_802314E4(this);
        fn_8023131C(this);
    }

    RP_GET_INSTANCE(RPSysResourceManager)->setUnk60(false);
    OSGetTick();

    mPhase = 4;
    incomingScene();
    Reset();

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->startMgrFadeIn();
    }

    OSGetTick();
}

void RPSysScene::reinit() {
    mPhase = 4;
    outgoingScene();
    incomingScene();
    Reset();

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->startMgrFadeIn();
    }
}

void RPSysScene::Reset() {}

void RPSysScene::incoming_childDestroy() {
    mPhase = 4;
    incomingScene();
    Reset();

    if (!mFlags.onBit(EFlag_IsChild)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->startMgrFadeIn();
    }
}

void RPSysScene::Calculate() {}

void RPSysScene::calc() {
    mPhase = 5;
    RP_GET_INSTANCE(RPSysHomeMenuMgr)->update();
    VF_0x64();

    // Resort reads the status inline here (no isErrorOccured call)
    if (lbl_806F4CB8->getErrorStatus() >= 0) {
        fn_802328D8(mpCommonObject);

        if (lbl_806F4EE0 != NULL) {
            fn_80277A00(GetControllerManager());
        }

        if (RP_GET_INSTANCE(RPSysSceneMgr)->isNormalState() &&
            !RP_GET_INSTANCE(RPSysHomeMenuMgr)->isActive() && GetSysMsgWinMgr()->mState == -1 &&
            !(lbl_806F4CD0->mFlags & 1)) {
            mpRenderer->PreCalculate();
            Calculate();
            mUnk5C = true;
            mpRenderer->PostCalculate();
        } else {
            mpRenderer->CalculateInPause();
        }

        fn_8023BD6C(lbl_806F4D00);
        fn_8023282C(mpCommonObject);
        fn_80237DDC(GetDbgScenePatroler());
        fn_8035ECA4(GetSDCardMgr());
    }

    fn_802311B0(this);
}

void RPSysScene::draw() {
    mPhase = 6;
    RPGrpRenderer::Begin();
    mpRenderer->Rendering();
    RPGrpRenderer::StartDebugDraw();
    RPGrpRenderer::End();
    Unk_8022F404();
}

void RPSysScene::outgoing_childCreate() {
    outgoingScene();
}

void RPSysScene::Exit() {}

void RPSysScene::exit() {
    mPhase = 7;
    outgoingScene();
    Exit();
    exitScenePost();
}

void RPSysScene::init() {
    getHeap()->mName = "sceneMem2";
    Unk_8022FCD4();

    fn_8026A33C(GetStaticMem(), this);

    EGG::Allocator* pAllocator = new EGG::Allocator(mpHeapMem1, 32);
    mpRenderer = RPGrpRenderer::Construct(pAllocator, getSceneID());
    mpRenderer->BecomeCurrent();
    RPGrpRenderer::GetCurrent()->AppendDrawObject(*this);

    mpCommonObject = new RPSysCommonObject();
    mpEffectCreator = new RPSysEffectCreator(RPSysEffectMgr::EDrawScene_Scene);

    RP_GET_INSTANCE(RPSysKokeshiManager)->Reset();
    mpUnk68 = &lbl_806F5088->mUnk5F0->mUnk04;
    mpUnk68->VF_0xC(true);

    fn_802416A4();
    RP_GET_INSTANCE(RPSysEffectMgr)->fn_8023D454();
    RP_GET_INSTANCE(RPSysEffectMgr)
        ->setCreator(mpEffectCreator, RPSysEffectMgr::EDrawScene_Scene);
    RP_GET_INSTANCE(RPSysSaveDataMgr)->fn_802336BC();
    RP_GET_INSTANCE(RPSysTextWriter)->Reset();

    mpFader = new EGG::ColorFader(0.0f, 0.0f,
                                  RP_GET_INSTANCE(RPSysSystem)->getFBWidth(),
                                  RP_GET_INSTANCE(RPSysSystem)->getFBHeight());
    mpFader->setStatus(EGG::Fader::STATUS_PREPARE_IN);
    mUnk64 = true;
}

void RPSysScene::incomingScene() {
    if (!mFlags.onBit(EFlag_IsChild)) {
        fn_802312E4(this);
    }

    mpRenderer->BecomeCurrent();
    fn_8023299C(mpCommonObject);
    RP_GET_INSTANCE(RPSysSceneMgr)->resetFadeFrame();
    RP_GET_INSTANCE(RPSysSceneMgr)->setSceneStatus(
        EGG::Fader::STATUS_PREPARE_OUT);
    RP_GET_INSTANCE(RPSysSystem)->setDimming(TRUE);
    RP_GET_INSTANCE(RPSysSystem)->Unk_8022D5D4(5);

    fn_8035EC9C(GetSDCardMgr(), getSceneID());
    GetSDCardMgr()->mUnk64 = true;

    mPauseCount = 0;
}

void RPSysScene::Unk_8022F404() {
    if (!mUnk5C) {
        mpFader->draw();
    }
}

void RPSysScene::exitScenePost() {
    GXDrawDone();
    mpRenderer->Destruct();

    if (mpHeapMem1 != NULL) {
        RP_GET_INSTANCE(RPSysSystem)->destroyHeap(mpHeapMem1, true);
    }

    if (mpHeapDepend != NULL) {
        RP_GET_INSTANCE(RPSysSystem)->destroyHeap(mpHeapDepend, true);
    }

    if (mpSceneHeap != NULL) {
        RP_GET_INSTANCE(RPSysSystem)->destroyHeap(mpSceneHeap, true);
    }

    fn_8035ECA0(GetSDCardMgr());
    fn_8035EC98(GetSDCardMgr());
    GetSDCardMgr()->mUnk64 = false;
}

void RPSysScene::setCreatorSceneID(s32 id) {
    mCreatorSceneID = id;
}

void* RPSysScene::Unk_8022F30C() {
    if (lbl_806F4E98 != NULL) {
        return fn_80269E6C(lbl_806F4E98);
    }

    return NULL;
}
