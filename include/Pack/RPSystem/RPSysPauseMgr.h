#ifndef RP_SYSTEM_PAUSE_MGR_H
#define RP_SYSTEM_PAUSE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel.h>
#include <Pack/RPSingleton.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Pause menu manager
 */
class RPSysPauseMgr {
    RP_SINGLETON_DECL_EX(RPSysPauseMgr);

public:
    //! Number of tracked remotes
    static const int REMOTE_NUM = 4;
    //! Length of the remote motion history, in frames
    static const int HISTORY_LEN = 30;

public:
    void init();
    void calc();
    void draw();
    void loadResource();

    bool isPause() const {
        return mFlags & 1;
    }

private:
    void checkEnterPause();
    bool isRemoteStill(s32 chan);

private:
    u32 mFlags;                             // at 0x8
    s32 mFrame;                             // at 0xC
    f32 mAccSpeed[REMOTE_NUM][HISTORY_LEN]; // at 0x10
    RPSysPauseMenu* mPauseMenu;             // at 0x1F0
};

//! @}

#endif
