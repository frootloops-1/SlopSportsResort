#include <Pack/RPSystem.h>

RPSysGameConfig* RPSysGameConfig::spInstance = NULL;

RPSysGameConfig* RPSysGameConfig::CreateInstance(EGG::Heap* pHeap) {
    if (spInstance == NULL) {
        spInstance = new (pHeap) RPSysGameConfig(pHeap);
        return spInstance;
    }
    return NULL;
}

/**
 * @brief Constructor
 *
 * @param pHeap Parent heap
 */
RPSysGameConfig::RPSysGameConfig(EGG::Heap* pHeap)
    : RPSysTagParameters("GameConfig"),
      mpParentHeap(pHeap),
      mRootScene(this, "RootScene"),
      mTVMode(this, "TVMode"),
      mLanguage(this, "Language"),
      mSound(this, "Sound"),
      mGameMode(this, "GameMode"),
      mStageNo(this, "StageNo"),
      mPlayerNum(this, "PlayerNum"),
      mRemoconNum(this, "RemoconNum"),
      mCtrlTypeNo(this, "CtrlTypeNo"),
      mRPPrint(this, "RPPrint"),
      mRPSysPrint(this, "RPSysPrint"),
      mRPAudPrint(this, "RPAudPrint"),
      mRPUtlPrint(this, "RPUtlPrint"),
      mRPUserPrint(this, "RPUserPrint"),
      mScenePatrole(this, "ScenePatrole"),
      mInitialCostPrint(this, "InitialCostPrint") {

    mPlayerNum.set(0);
    mRemoconNum.set(0);
    mCtrlTypeNo.set(0);
    mRPPrint.set(0);
    mRPSysPrint.set(0);
    mRPUtlPrint.set(0);
    mRPAudPrint.set(0);
    mRPUserPrint.set(0);
    mRootScene.set(NULL);
    mTVMode.set(NULL);
    mLanguage.set(NULL);
    mSound.set(NULL);
    mGameMode.set(NULL);
    mStageNo.set(0);
    mScenePatrole.set(0);
    mInitialCostPrint.set(0);
}

/**
 * @brief Destructor
 */
RPSysGameConfig::~RPSysGameConfig() {}
