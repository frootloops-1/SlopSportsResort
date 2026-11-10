#ifndef RP_SYSTEM_PLAYER_SELECT_SCENE_H
#define RP_SYSTEM_PLAYER_SELECT_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPSystem/RPSysScene.h>

struct SelectUnk80;
struct SelectUnk84;
class RPSysLayout;

//! @addtogroup rp_system
//! @{

/**
 * @brief Pack Project player select scene
 */
class RPSysPlayerSelectScene : public RPSysScene {
public:
    virtual ~RPSysPlayerSelectScene(); // at 0x8

    virtual void Configure();    // at 0x44
    virtual void LoadResource(); // at 0x48
    virtual void Reset();        // at 0x4C
    virtual void Calculate();    // at 0x50
    virtual void Exit();         // at 0x54
    virtual void UserDraw();     // at 0x5C

private:
    // Inferred helpers (names kept as addresses)
    void fn_801D3140(s32 player, bool a, bool b);
    void fn_801D33E8(s32 id);
    bool fn_801D3538();
    void fn_801D3620();
    void fn_801D3720(s32 nextState, s32 phase);
    void fn_801D3970();
    void fn_801D3A34();
    void fn_801D3C48();
    void fn_801D3DD0();
    void fn_801D4020();
    void fn_801D41B0();
    void fn_801D4390();
    void fn_801D4460();
    void calcState11();

private:
    s32 mState;       // at 0x44
    s32 mNextState;   // at 0x48
    u8 mDisconnected; // at 0x4C
    u8 mSaveStarted;  // at 0x4D
    u8 unk4E[4];      // at 0x4E
    u8 mFlag52;       // at 0x52
    u8 unk53;         // at 0x53
    s32 mPlayerIdx;   // at 0x54
    s32 mMode;        // at 0x58
    u32 mFrame;       // at 0x5C
    s32 unk60;        // at 0x60
    s32 unk64;        // at 0x64
    void* mpUnk68;    // at 0x68
    void* mpUnk6C;    // at 0x6C
    RPSysLayout* mpLayout; // at 0x70
    void* mpUnk74;    // at 0x74
    void* mpUnk78;    // at 0x78
    void* mpUnk7C;    // at 0x7C
    SelectUnk80* mpUnk80; // at 0x80
    SelectUnk84* mpUnk84; // at 0x84
    void* mpUnk88;    // at 0x88
};

//! @}

#endif
