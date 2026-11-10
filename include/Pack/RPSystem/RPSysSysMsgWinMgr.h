#ifndef RP_SYSTEM_SYS_MSG_WIN_MGR_H
#define RP_SYSTEM_SYS_MSG_WIN_MGR_H
#include <Pack/types_pack.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Resort system message window (placeholder)
 *
 * ctor 0x80271E70 (base ctor 0x802724F8), vtable 0x806BB278 stored at 0x30:
 * the members come before the first virtual function.
 */
class Unk_80271E70 {
public:
    char UNK_0x0[0x30];

public:
    virtual void Unk_08(); // at 0x8
    virtual void Unk_0C(); // at 0xC
    virtual void Unk_10(); // at 0x10
    virtual void Unk_14(); // at 0x14
    virtual void Unk_18(); // at 0x18
    virtual void Unk_1C(); // at 0x1C
    virtual void Unk_20(); // at 0x20
    virtual void Unk_24(); // at 0x24
    virtual void Unk_28(); // at 0x28
    virtual void Unk_2C(); // at 0x2C
    virtual void Unk_30(); // at 0x30
    virtual void Unk_34(); // at 0x34
    virtual void Unk_38(); // at 0x38
    virtual void Unk_3C(); // at 0x3C
    virtual void Unk_40(); // at 0x40
    virtual void Unk_44(); // at 0x44
    virtual int Unk_48();  // at 0x48 (0x802A60F8)
};

/**
 * @brief Resort system message window manager
 *
 * Name from the string RPSysSaveDataMgr passes with its instance pointer
 * (lbl_806F4CE0) to the singleton check 0x80370BD4. Layout partial.
 */
class RPSysSysMsgWinMgr {
public:
    char UNK_0x0[0x14];
    //! Set by 0x80235D70, -1 when no window is shown
    int mState;               // at 0x14
    //! Returned by 0x80235D18
    Unk_80271E70* mpWindow;   // at 0x18
};

//! @}

#endif
