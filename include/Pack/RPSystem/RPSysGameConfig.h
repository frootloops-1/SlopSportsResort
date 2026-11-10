#ifndef RP_SYSTEM_GAME_CONFIG_H
#define RP_SYSTEM_GAME_CONFIG_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysTagParms.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project Game Config File (`gameConfig.ini`)
 */
class RPSysGameConfig : public RPSysTagParameters {
    RP_SINGLETON_DECL_EX(RPSysGameConfig);

private:
    RPSysStringTagParm mRootScene; // at 0x10
    RPSysStringTagParm mTVMode; // at 0x20
    RPSysStringTagParm mLanguage; // at 0x30
    RPSysStringTagParm mSound; // at 0x40
    RPSysStringTagParm mGameMode; // at 0x50
    RPSysPrimTagParm<int> mStageNo; // at 0x60
    RPSysPrimTagParm<int> mPlayerNum; // at 0x70
    RPSysPrimTagParm<int> mRemoconNum; // at 0x80
    RPSysPrimTagParm<int> mCtrlTypeNo; // at 0x90
    RPSysPrimTagParm<int> mRPPrint; // at 0xA0
    RPSysPrimTagParm<int> mRPSysPrint; // at 0xB0
    RPSysPrimTagParm<int> mRPAudPrint; // at 0xC0
    RPSysPrimTagParm<int> mRPUtlPrint; // at 0xD0
    RPSysPrimTagParm<int> mRPUserPrint; // at 0xE0
    RPSysPrimTagParm<int> mScenePatrole; // at 0xF0
    RPSysPrimTagParm<int> mInitialCostPrint; // at 0x100
};

//! @}

#endif
