#ifndef RP_SYSTEM_BOOT_SCENE_H
#define RP_SYSTEM_BOOT_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysScene.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysLayout;
class RPSysLytAnmObj;
class RPSysProjectLocal;

/**
 * @brief Pack Project bootup scene
 * @details Shows the wrist strap warning screen, then changes to the pack's
 * boot scene once a button is pressed (or after a timeout).
 */
class RPSysBootScene : public RPSysScene {
public:
    virtual ~RPSysBootScene(); // at 0x8

    virtual void Configure();    // at 0x44
    virtual void LoadResource(); // at 0x48
    virtual void Reset();        // at 0x4C
    virtual void Calculate();    // at 0x50
    virtual void Exit();         // at 0x54
    virtual void taskAsync();    // at 0x58

    virtual void UserDraw(); // at 0x5C

private:
    enum EState {
        EState_FadeIn,
        EState_Wait,
        EState_Input,
        EState_Exit,
    };

private:
    void CalculateInput();

private:
    RPSysProjectLocal* mpProjectLocal; // at 0x44
    RPSysLayout* mpLayout;             // at 0x48
    RPSysLytAnmObj* mpAnmObj;          // at 0x4C
    s32 mState;                        // at 0x50
    s32 mTimer;                        // at 0x54
};

//! @}

#endif
