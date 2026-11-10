#ifndef RP_SYSTEM_SCENE_H
#define RP_SYSTEM_SCENE_H
#include <Pack/types_pack.h>

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysCommonObject;

class IRPSysSceneUnk68;

/**
 * @brief Pack Project scene
 */
class RPSysScene : public EGG::Scene, public IRPGrpDrawObject {
    friend class RPSysSceneCreator;

public:
    struct UnkStruct {
        u32 unk0;

        UnkStruct() : unk0(0) {}
    };

public:
    RPSysScene();

    virtual void calc() override;                 // at 0xC
    virtual void draw() override;                 // at 0x10
    virtual void enter() override;                // at 0x14
    virtual void exit() override;                 // at 0x18
    virtual void reinit() override;               // at 0x1C
    virtual void incoming_childDestroy() override; // at 0x20
    virtual void outgoing_childCreate() override; // at 0x24

    // IRPGrpDrawObject vtable: 0x28-0x3B

    virtual UnkStruct& VF_0x3C() {
        return sUnkStruct;
    } // at 0x3C
    virtual u32 VF_0x40() {
        return 'SYS_';
    } // at 0x40
    virtual void pauseCallBack(bool /* enter */) {} // at 0x44
    virtual s32 VF_0x48() {
        return 3;
    } // at 0x48
    virtual void VF_0x4C() {}     // at 0x4C
    virtual void Configure();     // at 0x50
    virtual void LoadResource() {} // at 0x54
    virtual void Reset();         // at 0x58
    virtual void Calculate();     // at 0x5C
    virtual void Exit();          // at 0x60
    virtual void VF_0x64() {}     // at 0x64
    virtual void taskAsync() {}   // at 0x68

    static void* Unk_8022F30C();

    bool isSceneDisplay() const;
    bool isSceneBlank() const;
    bool isSceneChangeEnable() const;
    bool isNandAccessEnable() const;
    bool Unk_8022FD68() const;
    bool Unk_8022FE10() const;

    void setFadeFrame(u16 frame);
    nw4r::ut::Color getFadeColor() const;
    void setFadeColor(nw4r::ut::Color color);
    void setSceneFadeColor(nw4r::ut::Color color);
    bool startFadeIn();
    bool startFadeOut();

    void setDimming(bool enable);

    void setCreatorSceneID(s32 id);
    s32 getCreatorSceneID() const;

    RPGrpRenderer* getRenderer() const {
        return mpRenderer;
    }

    void setChildScene();

    void drawTimeStamp(nw4r::ut::Color color);
    void setTaskAsync();
    bool isTaskAsyncFinish() const;

    void Unk_8022FC08();
    void Unk_8022FC5C();
    void Unk_8022FCB8();
    void Unk_8022FCBC();
    void Unk_8022FCC4();
    void Unk_8022FCCC();

private:
    void incomingScene();
    void outgoingScene();
    void exitScenePost();
    void init();
    void Unk_8022FCD4();
    void Unk_8022F404() DECOMP_DONT_INLINE;
    void loadUpdate();
    void initTaskAsync();
    void enableLoadMessage();
    void load();
    void loadMessage();
    void updateDvdEndMessage();
    void updateNandEndMessage();

    static void loadResourceFunc(void* pArg);
    static void taskAsyncFunc(void* pArg);

private:
    enum {
        EFlag_LoadMessage,      //!< Display "Now Loading" message
        EFlag_TaskAsyncSet,     //!< The scene requested an asynchronous task
        EFlag_TaskAsyncRunning, //!< The asynchronous task is running
        EFlag_IsChild,          //!< This scene was created as a child
    };

private:
    static UnkStruct sUnkStruct;

    s32 mPauseCount;                     // at 0x38
    RPGrpRenderer* mpRenderer;           // at 0x3C
    RPSysCommonObject* mpCommonObject;   // at 0x40
    RPSysEffectCreator* mpEffectCreator; // at 0x44
    EGG::Heap* mpHeapMem1;               // at 0x48
    EGG::Heap* mpHeapDepend;             // at 0x4C
    EGG::Heap* mpSceneHeap;              // at 0x50
    EGG::TBitFlag<u32> mFlags;           // at 0x54
    s32 mCreatorSceneID;                 // at 0x58
    bool mUnk5C;                         // at 0x5C
    EGG::ColorFader* mpFader;            // at 0x60
    bool mUnk64;                         // at 0x64
    IRPSysSceneUnk68* mpUnk68;           // at 0x68
    s32 mPhase;                          // at 0x6C
};

//! @}

#endif
