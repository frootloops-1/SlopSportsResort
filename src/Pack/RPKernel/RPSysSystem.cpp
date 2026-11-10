// Keep the header-only .sdata2 constant (cm2hw) out of this object
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPKernel.h>
#include <Pack/RPAudio.h>
#include <Pack/RPAudio/Unk_802BCF00.h>
#include <Pack/RPSystem.h>
#include <Pack/RPSystem/RPSysUnkSingletons.h>

#include <egg/core.h>


#include <revolution/DVD.h>
#include <revolution/OS.h>
#include <revolution/SC.h>
#include <revolution/VI.h>

// Resort .rodata 0x806653F8
static const u16 sExceptionPadInfo[8] = {
    0x8000, 0x0800, 0x0400, 0x0200, 0x0100, 0x1000, 0x0010, 0x0000,
};

RPSysConfigData RPSysSystem::sConfigData(0);
RPSysSystem* RPSysSystem::spInstance;
GXRenderModeObj* RPSysSystem::spRenderModeObj;
RPSysRenderMode::EFormat RPSysSystem::sRenderModeFormat;
u32 RPSysSystem::sRenderModeWaitStart;
RPSysSystem::EDiskCheck RPSysSystem::sDiskCheckResult;
u32 RPSysSystem::sXfbMemorySize;
u32 RPSysSystem::sEffectMemorySize;

// Placeholders for symbols that symbols.txt has not named yet
extern u16 lbl_806F49F8;                     // EGG::SceneManager heap option flag
extern RPSysDvdStatus* lbl_806F4CB8;         // RPSysDvdStatus::spInstance
extern RPSysProjectLocal* lbl_806F4CA0;      // RPSysProjectLocal::spInstance

extern "C" {
// OS
void fn_8004FB90(void (*pCallback)()); // OSSetResetCallback
void fn_8004FC80(void (*pCallback)()); // OSSetPowerCallback
void fn_80020630(u8);
void VISetTrapFilter(BOOL enable);

// EGG
void fn_801B9818(int tvMode);                           // EGG::Screen::SetTVMode
EGG::Heap* fn_801C0B30(u32, u32, EGG::Heap*, u16, u32); // EGG heap create (kind 3)
void fn_801C2D18(u32 size, EGG::Heap* pHeap);           // EGG::GraphicsFifo::create
void fn_801CEBB8(u16, u16, u16, u32, u32);              // EGG::Exception::create
void fn_801CEC48(const u16* pPadInfo);                  // EGG::Exception::setPadInfo
void fn_80370BCC(EGG::Heap*, EGG::Heap*, EGG::Heap*);
void setPadInfo__Q23EGG9ExceptionFPCUs(void*, u32); // misnamed debug stub

// RP
void fn_8022FE4C(u16* pXOrigin, u16* pWidth, int format, bool wide); // RPSysRenderMode::adjust
void fn_80237624(RPSysSystem* pSystem, u8 rate);
BOOL fn_80237910(RPSysSystem* pSystem);
RPSysSceneCreator* fn_8022EEB4(EGG::Heap* pHeap);
void fn_8022EDFC(RPSysSceneCreator* pCreator, int, int);
void fn_80230CEC(EGG::Heap* pHeap);
void fn_80230AE4(RPSysProjectLocal* pLocal);
void fn_802330C8(EGG::Heap* pHeap);
void fn_80254A18(u16 width, u16 height);
void fn_802549D0(u8 red, u8 green, u8 blue);
void fn_80232720();
void fn_802348AC();
void fn_80249DE0();
void fn_80240934();
void fn_802820DC(EGG::Heap* pHeap);
RPSndAudioMgr* fn_802BCF84(EGG::Heap* pHeap);
void fn_802426D0(EGG::Heap* pHeap);
void fn_8025C9EC();
void fn_802BC97C(Unk_802BCF00* pMgr, u8 mode);
void fn_802417CC();
void fn_80276F00(EGG::Heap* pHeap);
void fn_80235FAC(EGG::Heap* pHeap);
void fn_80235418(EGG::Heap* pHeap);
void fn_80235860(EGG::Heap* pHeap);
void fn_8026A894(EGG::Heap* pHeap);
void fn_8023ABFC(EGG::Heap* pHeap);
void fn_8023859C(EGG::Heap* pHeap);
void fn_80283284(EGG::Heap* pHeap);
void fn_802832D4(EGG::Heap* pHeap);
void fn_80292B14(EGG::Heap* pHeap);
void fn_8035ED74(EGG::Heap* pHeap);
void fn_8035ECA8(void* pMgr, EGG::Heap* pHeap, int);
void fn_802977F4(EGG::Heap* pHeap);
void fn_8023BBF0(EGG::Heap* pHeap);
}


//! Unidentified 1-byte object created by createEffectWork (ctor fn_802A4CA8)
class Unk_802A4CA8 {
public:
    Unk_802A4CA8();
};

void RPSysSystem::initialize() {
    EGG::BaseSystem::configure(&sConfigData);
    DVDInit();

    void* pMem1Lo = OSGetMEM1ArenaLo();
    void* pMem1Hi = OSGetMEM1ArenaHi();
    void* pMem2Lo = OSGetMEM2ArenaLo();
    void* pMem2Hi = OSGetMEM2ArenaHi();

    void* pMem1Arena = OSInitAlloc(pMem1Lo, pMem1Hi, 2);
    void* pMem2Arena = OSInitAlloc(pMem2Lo, pMem2Hi, 2);

    pMem1Lo = ROUND_UP_PTR(pMem1Arena, 32);
    pMem2Lo = ROUND_UP_PTR(pMem2Arena, 32);

    pMem1Arena = ROUND_DOWN_PTR(pMem1Hi, 32);
    pMem2Arena = ROUND_DOWN_PTR(pMem2Hi, 32);

    sConfigData.mCodeStart =
        static_cast<OSBootInfo*>(OSPhysicalToCached(OS_PHYS_BOOT_INFO));
    sConfigData.mCodeEnd = pMem1Lo;
    sConfigData.mMem1Start = pMem1Lo;
    sConfigData.mMem1End = pMem1Arena;
    sConfigData.mMem2Start = pMem2Lo;
    sConfigData.mMem2End = pMem2Arena;
    sConfigData.mMemorySize =
        static_cast<OSBootInfo*>(sConfigData.mCodeStart)->physMemSize;

    OSSetMEM1ArenaLo(pMem1Arena);
    OSSetMEM1ArenaHi(pMem1Arena);
    OSSetMEM2ArenaLo(pMem2Arena);
    OSSetMEM2ArenaHi(pMem2Arena);

    EGG::Heap::initialize();
    u32 heapSizeMem1;
    u32 heapSizeMem2;
    void* pMem1Start;
    void* pMem2Start;
    pMem1Start = sConfigData.mMem1Start;
    heapSizeMem1 = (u32)sConfigData.mMem1End - (u32)pMem1Start;
    pMem2Start = sConfigData.mMem2Start;
    heapSizeMem2 = (u32)sConfigData.mMem2End - (u32)pMem2Start;
    setPadInfo__Q23EGG9ExceptionFPCUs(pMem1Start, heapSizeMem1);
    sConfigData.mRootHeapMem1 = EGG::ExpHeap::create(pMem1Start, heapSizeMem1, 1);
    sConfigData.mRootHeapMem1->mName = "RootMem1";
    sConfigData.mRootHeapMem2 =
        EGG::ExpHeap::create(pMem2Start, heapSizeMem2, 1);
    sConfigData.mRootHeapMem2->mName = "RootMem2";
    sConfigData.mRootHeapDebug = NULL;
    sConfigData.mSystemHeap =
        EGG::ExpHeap::create(0x480000, sConfigData.mRootHeapMem1, 1);
    sConfigData.mSystemHeap->mName = "System";
    sConfigData.mSystemHeap->becomeCurrentHeap();
    fn_801C2D18(0x80000, NULL);
    setupTVMode();
    setupRenderMode();

    sConfigData.mVideo = new EGG::Video(spRenderModeObj);
    sConfigData.mXfbMgr = new EGG::XfbManager();

    sXfbMemorySize = sConfigData.mRootHeapMem2->getAllocatableSize();
    for (int i = 0; i < 2; i++) {
        sConfigData.mXfbMgr->attach(new EGG::Xfb(sConfigData.mRootHeapMem2));
    }
    sXfbMemorySize -= sConfigData.mRootHeapMem2->getAllocatableSize();

    sConfigData.mDisplay = new EGG::AsyncDisplay(1);
    getConfigData()->getDisplay()->Unk_clearEfbFlag1();

    EGG::Thread::initialize();
    sConfigData.mParentThread = new EGG::Thread(OSGetCurrentThread(), 4);
    sConfigData.mPerfView = new EGG::ProcessMeter(true);

    EGG::DvdFile::initialize();
    fn_801CEBB8(0x80, 0x20, 4, 0, 1);
    fn_801CEC48(sExceptionPadInfo);
    sConfigData.mRootHeapMem2->becomeCurrentHeap();
    fn_80370BCC(sConfigData.mSystemHeap, sConfigData.mRootHeapMem1,
                sConfigData.mRootHeapMem2);
}

void RPSysSystem::create() {
    spInstance = new (sConfigData.mSystemHeap, 4) RPSysSystem;
}

RPSysSystem::~RPSysSystem() {}

void RPSysSystem::setup() {
    fn_8025C9EC();
    nw4r::lyt::LytInit();
    Unk_8022DC18();
    createFromSystemHeap();
    Unk_8022D88C();
    createEffectWork();

    mpUnkHeap28 = Unk_8022D650(
        sConfigData.mRootHeapMem1, 1,
        sConfigData.mRootHeapMem1->getAllocatableSize() - 0x200, false, 0,
        true);
    mpUnkHeap2C = Unk_8022D650(
        sConfigData.mRootHeapMem2, 1,
        sConfigData.mRootHeapMem2->getAllocatableSize() - 0xC00000, false, 0,
        true);

    Unk_8022D518();
    RP_GET_INSTANCE(RPSysFontManager)->LoadRomFont();
    u8 soundMode = SCGetSoundMode();
    fn_802BC97C(lbl_806F5088, soundMode);
    fn_802417CC();
    waitRenderModeChange();
    fn_8022EDFC(RP_GET_INSTANCE(RPSysSceneCreator), 0, 0);
}

RPSysSystem::RPSysSystem() {
    mpUnkHeap04 = NULL;
    mpResourceHeap = NULL;
    mpResCacheHeap = NULL;
    mpUnkHeap10 = NULL;
    mpAssertHeap = NULL;
    mpUnkHeap1C = NULL;
    mpUnkHeap20 = NULL;
    mpUnkHeap24 = NULL;
    mpUnkHeap28 = NULL;
    mpUnkHeap2C = NULL;
    mpCurrentHeap = NULL;
    OSInitMutex(&mCurrentHeapMutex);
    mpTaskThreadInfo = NULL;
    mUnk50 = false;
    mUnk51 = true;
    fn_80237624(this, 1);
    mLoadCount = 0;
    mpTimeStampString = NULL;
}

void RPSysSystem::Unk_8022DC18() {
    mpUnkHeap04 = Unk_8022D650(sConfigData.mRootHeapMem2, 1, 0x200000, true, 0, true);
    Unk_8022D650(sConfigData.mRootHeapMem1, 1, 0x80000, false, 0, true);
    Unk_8022D650(sConfigData.mRootHeapMem2, 1, 0x80000, false, 0, true);

    mpResourceHeap = Unk_8022D650(sConfigData.mRootHeapMem2, 1, 0x1780000, true, 0, true);
    mpResourceHeap->mName = "resource";

    mpResCacheHeap = Unk_8022D650(sConfigData.mRootHeapMem2, 1, 0x420000, false, 0, true);
    mpResCacheHeap->mName = "resCache";

    mpAssertHeap = Unk_8022D650(sConfigData.mRootHeapMem2, 1, 0x100, true, 0, true);
    mpAssertHeap->disableAllocation();

    mpUnkHeap10 = Unk_8022D650(sConfigData.mRootHeapMem1, 1, 0x580000, true, 0, true);
    mpUnkHeap14 = Unk_8022D650(sConfigData.mRootHeapMem1, 1, 0x400000, true, 0, true);
}

void RPSysSystem::createFromSystemHeap() {
    lockHeap(sConfigData.mSystemHeap);

    RPSysGameConfig::CreateInstance(sConfigData.mSystemHeap);
    RPSysHostIOSocketManager::CreateInstance();
    fn_80230CEC(sConfigData.mSystemHeap);
    fn_80230AE4(lbl_806F4CA0);
    if (!lbl_806F4CA0->isMplsMoviePlayed()) {
        OSExecl("sys/mpls_movie/player.dol", "", "", "ASPECT_RATIO_AUTO", NULL);
    }

    RPSysCoreController::initialize();
    sConfigData.mSceneMgr = RPSysSceneMgr::CreateInstance(sConfigData.mSystemHeap);
    RP_GET_INSTANCE(RPSysSceneMgr)
        ->setCreator(fn_8022EEB4(sConfigData.mSystemHeap));
    fn_802330C8(sConfigData.mSystemHeap);
    fn_80254A18(spRenderModeObj->fbWidth, spRenderModeObj->efbHeight);
    fn_80232720();
    fn_802348AC();
    RPSysTextWriter::CreateInstance();
    fn_80249DE0();
    fn_80240934();
    RPSysEffectMgr::CreateInstance();
    fn_802820DC(NULL);
    sConfigData.mAudioMgr = fn_802BCF84(sConfigData.mSystemHeap);
    fn_802426D0(sConfigData.mSystemHeap);

    mpTaskThreadInfo = new Unk_8023873C();
    mpTaskThreadInfo->Unk_802386A8();
    mpTimeStampString = static_cast<char*>(EGG::Heap::alloc(0x80, 0x20, NULL));

    Unk_8022D594();
}

void RPSysSystem::createEffectWork() {
    lockHeap(sConfigData.mRootHeapMem1);

    Unk_802BCFE4 audioArg;
    audioArg.mpHeap = sConfigData.mRootHeapMem2;
    audioArg.mUnk08 = 0xA00000;
    audioArg.mUnk1C = 2;
    lbl_806F5088->initialize(&audioArg);

    new Unk_802A4CA8();

    RPSysEffectMgr::EffectArg effectArg;
    effectArg.maxEffect = 100;
    effectArg.maxEmitter = 200;
    effectArg.maxParticleManager = 250;
    effectArg.maxParticle = 1500;
    effectArg.pHeap = sConfigData.mRootHeapMem1;
    sEffectMemorySize = effectArg.pHeap->getAllocatableSize();
    RP_GET_INSTANCE(RPSysEffectMgr)->createMemoryManager(&effectArg);
    RP_GET_INSTANCE(RPSysEffectMgr)
        ->setCreator(new (effectArg.pHeap, 4) RPSysEffectCreator(1), 1);
    sEffectMemorySize -= effectArg.pHeap->getAllocatableSize();

    Unk_8022D594();
}

void RPSysSystem::Unk_8022D88C() {
    lockHeap(mpUnkHeap04);

    fn_80276F00(mpUnkHeap04);
    RPSysKokeshiManager::CreateInstance();
    fn_80235FAC(mpUnkHeap04);
    fn_80235418(mpUnkHeap04);
    fn_80235860(mpUnkHeap04);
    RPSysSaveDataMgr::CreateInstance(mpUnkHeap04);
    RPSysHomeMenuMgr::CreateInstance(mpUnkHeap04);
    fn_8026A894(NULL);
    fn_8023ABFC(NULL);
    fn_8023859C(NULL);
    fn_80283284(mpUnkHeap04);
    fn_802832D4(mpUnkHeap04);
    fn_80292B14(NULL);
    fn_8035ED74(NULL);
    fn_8035ECA8(GetSDCardMgr(), mpUnkHeap04, 0x14);
    Unk_806F4D50::CreateInstance(mpUnkHeap04);
    fn_802977F4(NULL);
    fn_8023BBF0(NULL);

    Unk_8022D594();
}

void RPSysSystem::setupTVMode() {
    int i;

    VIInit();
    for (i = 0; i < 60; i++) {
        if (SCCheckStatus() == SC_STATUS_OK) {
            break;
        }
        VIWaitForRetrace();
    }
    if (SCGetAspectRatio() == SC_ASPECT_WIDE) {
        fn_801B9818(EGG::Screen::TV_MODE_WIDE);
    } else {
        fn_801B9818(EGG::Screen::TV_MODE_STD);
    }
}

void RPSysSystem::setupRenderMode() {
    if (VIGetDTVStatus() == 1 && SCGetProgressiveMode() == 1) {
        sRenderModeFormat = RPSysRenderMode::EFormat_NtscProg;
    } else {
        sRenderModeFormat = RPSysRenderMode::EFormat_Ntsc;
    }

    spRenderModeObj = RPSysRenderMode::getRenderMode(sRenderModeFormat);
    fn_8022FE4C(&spRenderModeObj->viXOrigin, &spRenderModeObj->viWidth,
                sRenderModeFormat,
                EGG::Screen::GetTVMode() == EGG::Screen::TV_MODE_WIDE);

    if ((u32)sRenderModeFormat == RPSysRenderMode::EFormat_NtscProg ||
        (u32)sRenderModeFormat == RPSysRenderMode::EFormat_PalProg) {
        if ((u32)VIGetScanMode() == VI_SCANMODE_PROG) {
            sRenderModeWaitStart = 0;
        } else {
            sRenderModeWaitStart = OS_TICKS_TO_MSEC(OSGetTime());
        }
    } else if ((u32)sRenderModeFormat == RPSysRenderMode::EFormat_Pal60) {
        if ((u32)VIGetTvFormat() == VI_TVFORMAT_EURGB60) {
            sRenderModeWaitStart = 0;
        } else {
            sRenderModeWaitStart = OS_TICKS_TO_MSEC(OSGetTime());
        }
    } else {
        sRenderModeWaitStart = 0;
    }
}

void RPSysSystem::setDisplayClearColor(nw4r::ut::Color color) {
    sConfigData.mDisplay->setClearColor(color);
}

EGG::Heap* RPSysSystem::Unk_8022D650(EGG::Heap* pParent, s32 kind, u32 size,
                                     BOOL clear, u32 unitSize, BOOL unused) {
#pragma unused(unused)
    EGG::Heap* pHeap = NULL;
    u16 opt = MEM_HEAP_OPT_CLEAR_ALLOC;
    if (!clear) {
        opt = 0;
    }

    switch (kind) {
    case 1:
        pHeap = EGG::ExpHeap::create(size, pParent, opt);
        break;
    case 2:
        pHeap = EGG::FrmHeap::create(size, pParent, opt);
        break;
    case 3:
        pHeap = fn_801C0B30(size, unitSize, pParent, opt, 0);
        break;
    }

    return pHeap;
}

void RPSysSystem::destroyHeap(EGG::Heap* pHeap, bool unused) {
#pragma unused(unused)
    pHeap->destroy();
}

void RPSysSystem::startLoadCount() {
    mLoadCount = 0;
}

bool RPSysSystem::isLoadCountEnd() const {
    return mLoadCount > 300;
}

void RPSysSystem::createTimeStamp() {
    EGG::DvdRipper::loadToMainRAM("timeStamp.txt", (u8*)mpTimeStampString,
                                  NULL, EGG::DvdRipper::ALLOC_DIR_HEAD);
}

void RPSysSystem::Unk_8022D5E4() {
    mUnk50 = true;
}

void RPSysSystem::setDimming(BOOL dim) {
    VIEnableDimming(dim);
}

void RPSysSystem::Unk_8022D5D4(u8 value) {
    fn_80020630(value);
}

void RPSysSystem::Unk_8022D594() {
    mpCurrentHeap->becomeCurrentHeap();
    mpCurrentHeap = NULL;
    OSUnlockMutex(&mCurrentHeapMutex);
}

void RPSysSystem::Unk_8022D518() {
    VISetTrapFilter(TRUE);
    VISetTrapFilter(FALSE);
    sConfigData.mPerfView->setVisible(false);
    fn_802549D0(0xFF, 0xFF, 0xFF);
    fn_8004FB90(softResetCallBack);
    fn_8004FC80(shutdownSystemCallBack);
    lbl_806F49F8 = 1;
}

void RPSysSystem::waitRenderModeChange() {
    if (sRenderModeWaitStart != 0) {
        VISetBlack(TRUE);

        u32 waitEnd = sRenderModeWaitStart + 1600;
        for (int i = 0; i < 100; i++) {
            if ((u32)OS_TICKS_TO_MSEC(OSGetTime()) > waitEnd) {
                return;
            }

            VIFlush();
            VIWaitForRetrace();
        }
    }
}

void RPSysSystem::Unk_8022D494() {}

bool RPSysSystem::Unk_8022D440() {
    DVDCommandBlock block;
    sDiskCheckResult = EDiskCheck_Busy;
    DVDCheckDiskAsync(&block, Unk_8022D328);

    while (sDiskCheckResult == EDiskCheck_Busy) {
        VIWaitForRetrace();
    }

    return sDiskCheckResult == EDiskCheck_Ok;
}

void RPSysSystem::setCallBack() {
    fn_8004FB90(softResetCallBack);
    fn_8004FC80(shutdownSystemCallBack);
}

void RPSysSystem::softResetCallBack() {
    if (fn_80237910(spInstance)) {
        if (lbl_806F4CB8->getErrorStatus() < 0) {
            RP_GET_INSTANCE(RPSysSceneMgr)->returnToMenu(0, false);
        } else if (spInstance->mUnk50) {
            VIEnableDimming(FALSE);

            if (RP_GET_INSTANCE(RPSysSceneMgr)->isNormalState() &&
                !RP_GET_INSTANCE(RPSysHomeMenuMgr)->softReset()) {
                RP_GET_INSTANCE(RPSysSceneMgr)->softReset(false);
            }
        }
    }
}

void RPSysSystem::shutdownSystemCallBack() {
    if (fn_80237910(spInstance)) {
        RP_GET_INSTANCE(RPSysSceneMgr)->shutdownSystem(false);
    }
}

void RPSysSystem::Unk_8022D328(s32 result, DVDCommandBlock* pBlock) {
#pragma unused(pBlock)
    sDiskCheckResult = result != 0 ? EDiskCheck_Ok : EDiskCheck_Error;
}
