#ifndef RP_KERNEL_PAUSE_MENU_H
#define RP_KERNEL_PAUSE_MENU_H

#include <nw4r/lyt.h>
#include <Pack/types_pack.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class RPSysLayout;
class RPSysLytBounding;
class RPSysLytAnmObj;
class RPSysLytTextBox;
class RPSysLytResAccessor;
namespace EGG {
class CoreController;
}

/**
 * @brief Library that handles pause menu layout.
 */

class RPUtlLytFrameCursor {
public:
    RPUtlLytFrameCursor(); // fn_801C9C8C
    virtual ~RPUtlLytFrameCursor();
    virtual void vf_0x0C(); // vtable offset 0x0C
    virtual void vf_0x10();
    virtual void draw(); // vtable offset 0x14

private:
    u8 mPAD_0x04[0x254];
};

class RPSysPauseMenu {
public:
    RPSysPauseMenu();
    ~RPSysPauseMenu();
    void draw();
    void fn_801A0CE0();
    void fn_801A0E30();
    void fn_801A1130();
    void fn_801A1A5C();
    void fn_801A1DAC();
    u8 fn_801A16BC();

    enum {
        ANM_STATE_OFF,
        ANM_STATE_ON,
        ANM_PUSH,

        ANM_MAX
    };

    struct Entry {
        void reset() {
            mpPane = NULL;
            mpBounding = NULL;
            mpTextBox = NULL;
            for (int j = 0; j < ANM_MAX; j++) {
                mpAnmObj[j] = NULL;
            }
        }

        u8 mState;                    // at 0x0
        u8 mPrevState;                // at 0x1
        u8 mPAD_0x02[2];
        nw4r::lyt::Pane* mpPane;      // at 0x4
        RPSysLytBounding* mpBounding; // at 0x8
        RPSysLytTextBox* mpTextBox;   // at 0xC
        //! [0]/[1]: "active" anim per state, [2]: "push" anim
        RPSysLytAnmObj* mpAnmObj[ANM_MAX]; // at 0x10
    };

private:
    // Inlined helpers (names inferred)
    static s32 getAnmFrameNum(RPSysLytAnmObj* pAnmObj);
    EGG::CoreController* getController();
    bool isCursorHold(u32 buttons);
    bool isCursorInside();
    bool updateCursorKey();
    void updateCursor();
    void resetEntries();
    void decide();

private:
    RPSysLytResAccessor* mpResAccessor; // at 0x0
    RPSysLayout* mLayout; // at 0x4
    RPSysLytAnmObj* mpInAnmObj;  // at 0x8
    RPSysLytAnmObj* mpOutAnmObj; // at 0xC
    int mUNK_0x10;
    nw4r::lyt::Pane* mpCenterPane; // at 0x14 ("N_center_00")
    nw4r::lyt::Pane* mpBgPane; // at 0x18 ("N_bg_00")
    Entry mEntries[3]; // at 0x1C
    RPUtlLytFrameCursor* mUtlCursor; // at 0x70
    int mUNK_0x74;
    u8 mUNK_0x78;
    u8 mUNK_0x79;
    u8 mUNK_0x7A;
    u8 mUNK_0x7B;
    u8 mUNK_0x7C;
    u8 mUNK_0x7D;
    u8 mUNK_0x7E;
    u8 mUNK_0x7F;
    u8 mUNK_0x80;
    u8 mPAD_0x81[3];
    int mUNK_0x84;
};

//! @}

#endif
