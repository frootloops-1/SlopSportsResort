#ifndef RP_SPORTS_COMMON_MENU_KOKESHI_MGR_H
#define RP_SPORTS_COMMON_MENU_KOKESHI_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/IRPSysHostIOSocket.h>
#include <Pack/RPKernel/IRPSysKokeshiCtrlDataCallback.h>

#include <revolution/GX.h>

//! @addtogroup rp_sports
//! @{

// Forward declarations
class RPGrpCamera;
class RPSysKokeshiCtrlMgr;
class RPSysKokeshiHead;

/**
 * @brief Menu Mii manager (player select and similar menus)
 *
 * Layout inferred from RSPE01_01 (size 0xB8). Field names are inferred.
 */
class RPSysMenuKokeshiMgr : public IRPSysHostIOSocket,
                            public IRPSysKokeshiCtrlDataCallback {
public:
    //! A Mii chosen for one player slot (16 bytes, at 0x8 + slot * 0x10)
    struct Slot {
        RPSysKokeshiHead* pHead; // at 0x0
        s32 group;               // at 0x4
        u16 index;               // at 0x8
        s8 type;                 // at 0xA
        u8 unkB;
        u16 unkC;
        u16 unkE;
    };

    enum { GROUP_MAX = 6, SLOT_MAX = 4 };

    RPSysMenuKokeshiMgr(u8 camera, u8 lightSet);
    virtual ~RPSysMenuKokeshiMgr(); // at 0x8

    virtual void onCreateResource(s32 chan, u8 index);  // at 0x8 (callback)
    virtual void onReleaseResource(s32 chan, u8 index); // at 0xC (callback)

    // Public: the unnamed helper functions of this object access the fields.
    Slot mSlots[SLOT_MAX];          // at 0x8
    u8 mFade;                       // at 0x48
    s32 mAlpha;                     // at 0x4C
    u8 mDirty;                      // at 0x50
    u8 mCamera;                     // at 0x51
    u8 mLightSet;                   // at 0x52
    u8 mCount[GROUP_MAX];           // at 0x53
    GXColor mColor;                 // at 0x59
    f32 mScaleX;                    // at 0x60
    f32 mScaleY;                    // at 0x64
    RPGrpCamera* mpCamera;          // at 0x68
    struct {
        void** pA;                  // at 0x6C + group * 8
        void** pB;                  // at 0x70 + group * 8
    } mPtrs[GROUP_MAX];
    RPSysKokeshiHead** mpHeads[GROUP_MAX]; // at 0x9C
    RPSysKokeshiCtrlMgr* mpCtrlMgr; // at 0xB4
};

//! @}

#endif
