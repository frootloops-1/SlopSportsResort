#ifndef RP_KERNEL_SYSTEM_WINDOW_MGR_H
#define RP_KERNEL_SYSTEM_WINDOW_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysMessage;
class RPSysLayout;
class RPSysLytAnmObj;
class RPSysLytBounding;
class RPSysLytResAccessor;
class RPSysLytTextBox;
namespace nw4r {
namespace lyt {
class Pane;
}
} // namespace nw4r
class RPSndAudioMgr;

/**
 * @brief System window manager
 */
class RPSysSystemWinMgr {
    RP_SINGLETON_DECL_EX(RPSysSystemWinMgr);

public:
    enum E_ALIGN {};

    enum E_BUTTON {
        E_BUTTON_YES,
        E_BUTTON_NO,
    };

    enum E_WINDOW_TYPE {
        E_WINDOW_TYPE_TEXT,
        E_WINDOW_TYPE_ERROR,
    };

    enum E_RESULT {
        RESULT_NONE,
        RESULT_WAIT,
        RESULT_YES,
        RESULT_NO,
        RESULT_4,
        RESULT_5,
        RESULT_CONTINUE,
    };

    enum ESound {};

public:
    void setSystemWindow(E_WINDOW_TYPE type, u32 group, RPSysMessage* pMessage,
                         int argc, ...);

    void setCursors();

    void setDefaultCursor(E_BUTTON button) {
        unkAF = 0;
        unkB0 = button;
        mHover[0] = 0;
        mHover[1] = 0;
        mHover[2] = 0;
        mHover[3] = 0;
    }

    E_RESULT getResult() {
        return mResult;
    }

    /**
     * @brief Per-button layout data (stride 0x1C)
     */
    struct Button {
        void reset() {
            pPane = NULL;
            pBounds = NULL;
            pText = NULL;
            pAnm[0] = NULL;
            pAnm[1] = NULL;
            pAnm[2] = NULL;
            unk19 = 0;
        }

        nw4r::lyt::Pane* pPane;    // at 0x0 (N_choices*)
        RPSysLytBounding* pBounds; // at 0x4 (B_choices*)
        RPSysLytTextBox* pText;    // at 0x8 (T_choices*)
        RPSysLytAnmObj* pAnm[3];   // at 0xC (active, active, push)
        u8 unk18;                  // at 0x18
        u8 unk19;                  // at 0x19
    };

    // Fields are public so the extern "C" fn_801Axxxx helpers can use them
    RPSysLytResAccessor* mpResAccessor; // at 0x8
    RPSysLayout* mpLayout;      // at 0xC
    Button mButton[2];          // at 0x10
    nw4r::lyt::Pane* mpPane48; // at 0x48
    u32 unk4C;                  // at 0x4C
    u32 unk50;                  // at 0x50
    RPSysLytAnmObj* mpAnmA[2];  // at 0x54 (inAButton, blinkAButton)
    u32 unk5C;                  // at 0x5C
    u32 unk60;                  // at 0x60
    nw4r::lyt::Pane* mpPane64; // at 0x64
    RPSysLytTextBox* mpPane68; // at 0x68
    RPSysLytTextBox* mpPane6C; // at 0x6C
    RPSysLytTextBox* mpPane70; // at 0x70
    RPSysLytTextBox* mpPane74; // at 0x74
    RPSysLytAnmObj* mpAnm78;    // at 0x78 (in)
    RPSysLytAnmObj* mpAnm7C;    // at 0x7C (out)
    s32 unk80;                  // at 0x80
    u16 unk84;                  // at 0x84
    s32 unk88;                  // at 0x88
    s32 unk8C;                  // at 0x8C
    E_RESULT mResult;           // at 0x90
    u16 unk94;                  // at 0x94
    u16 unk96;                  // at 0x96
    u32 unk98;                  // at 0x98
    RPSysMessage* mpMessage;    // at 0x9C
    u32 unkA0;                  // at 0xA0
    void* unkA4;                // at 0xA4
    u8 unkA8;                   // at 0xA8
    u8 unkA9;                   // at 0xA9
    u8 unkAA;                   // at 0xAA
    u8 mHover[4];               // at 0xAB
    u8 unkAF;                   // at 0xAF
    u8 unkB0;                   // at 0xB0
    u8 unkB1;                   // at 0xB1
    u8 unkB2;                   // at 0xB2
    u8 unkB3;                   // at 0xB3
    struct Slot {
        s32 player;  // at 0x0
        s32 channel; // at 0x4
    } mSlot[4];                 // at 0xB4
    u8 unkD4[2];                // at 0xD4
    u8 unkD6;                   // at 0xD6
    f32 unkD8;                  // at 0xD8
    f32 unkDC;                  // at 0xDC
};

//! @}

#endif
