#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>
#include <Pack/RPSystem/RPSysScene.h>

#include <egg/core.h>

#include <nw4r/ut.h>

//! @addtogroup rp_system
//! @{


/**
 * @brief Unidentified Resort fader (ctor 0x8023B9D0, vtable 0x806B9210, 0x28
 * bytes). Owned by unk/text_802348E0.cpp; name not proven.
 */
class Unk_8023B9D0 : public EGG::ColorFader {
public:
    Unk_8023B9D0(f32 x, f32 y, f32 width, f32 height,
                 nw4r::ut::Color color = 0x00000000,
                 EStatus status = STATUS_PREPARE_IN);

    void setUnk24(u32 value) {
        mUnk24 = value;
    }

private:
    u32 mUnk24; // at 0x24
};

/**
 * @brief Pack Project scene manager
 * @note Resort: 0x44 bytes (CreateInstance 0x802309FC, ctor 0x8022FF48)
 */
class RPSysSceneMgr : public EGG::SceneManager {
    RP_SINGLETON_DECL_EX(RPSysSceneMgr);

public:
    virtual void calcCurrentScene() override; // at 0x10
    virtual void calcCurrentFader() override; // at 0x14

    RPSysScene* getCurrentSceneRP() const;

    bool softReset(bool fromHBM);
    bool returnToMenu(bool fromHBM);
    bool returnToMenu(s32 type, bool fromHBM);
    bool shutdownSystem(bool fromHBM);

    bool isNormalState() const;
    bool Unk_80230854() const;
    bool isShutDownReserved() const;
    s32 getReturnToMenu() const;
    void resetGuard();
    bool isApplicationEndReserved();
    bool isDvdErrorApplicationEnd();

    bool changeNextSceneAfterFade(s32 id, bool reconfigure = false);

    void resetFadeFrame();
    u16 getFadeFrame();
    void setFadeFrame(u16 frame);
    void resetFadeColor(bool scene);
    void resetFadeColor();
    nw4r::ut::Color getFadeColor();
    void Unk_80230610(nw4r::ut::Color color);
    void setFadeColor(nw4r::ut::Color color);
    void setSceneFadeColor(nw4r::ut::Color color);

    EGG::Fader::EStatus getSceneStatus();
    void setSceneStatus(EGG::Fader::EStatus status);

    bool startMgrFadeIn();
    bool startSceneFadeIn();
    bool startSceneFadeOut();

    bool Unk_80230580();
    bool Unk_80230544();
    bool isDisplay();
    bool isBlank();
    void Unk_802304C4(u32 value);
    bool Unk_80230474();
    bool Unk_80230408();
    bool isFadeOut();
    bool isTaskFinished();
    bool isSceneChangeEnable();

    bool calcSceneFader();
    void drawSceneFader();
    void drawMgrFader();

    void updateState();

    bool Unk_802309E4() const;
    void Unk_802309EC(bool value);

private:
    enum EState {
        EState_Normal,       //!< Normal operation
        EState_Guard,        //!< Prevents operations during soft reset
        EState_SoftReset,    //!< Perform soft reset
        EState_ReturnToMenu, //!< Return to system menu
        EState_Shutdown      //!< Shutdown the system
    };

    //! The default fade duration, in frames
    static const int DEFAULT_FADE_FRAME = 20;

private:
    s32 mState;                 // at 0x30
    s32 mReturnToMenu;          // at 0x34
    bool mUnk38;                // at 0x38
    Unk_8023B9D0* mpSceneFader; // at 0x3C
    Unk_8023B9D0* mpMgrFader;   // at 0x40
};

//! @}

#endif
