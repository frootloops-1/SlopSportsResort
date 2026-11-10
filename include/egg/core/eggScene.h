#ifndef EGG_CORE_SCENE_H
#define EGG_CORE_SCENE_H
#include <egg/types_egg.h>

#include <egg/core/eggDisposer.h>

namespace EGG {

// Forward declarations
class Heap;
class SceneManager;

// Resort: derives from Disposer (ctor 0x801C82A4 calls __ct__Q23EGG8DisposerFv; fields 0x10-0x2C, size 0x30)
class Scene : public Disposer {
public:
    Scene();
    virtual ~Scene(); // at 0x8

    virtual void calc() {}                  // at 0xC
    virtual void draw() {}                  // at 0x10
    virtual void enter() {}                 // at 0x14
    virtual void exit() {}                  // at 0x18
    virtual void reinit() {}                // at 0x1C
    virtual void incoming_childDestroy() {} // at 0x20
    virtual void outgoing_childCreate() {}  // at 0x24

    Heap* getHeap() const {
        return mHeap;
    }
    Heap* getHeap_Mem1() const {
        return mHeap_Mem1;
    }
    Heap* getHeap_Mem2() const {
        return mHeap_Mem2;
    }
#if defined(VERSION_RSPE01_01)
    Heap* getHeap_Debug() const {
        return mHeap_Debug;
    }
#endif

    Scene* getParentScene() const {
        return mParentScene;
    }
    void setParentScene(Scene* pScene) {
        mParentScene = pScene;
    }

    Scene* getChildScene() const {
        return mChildScene;
    }
    void setChildScene(Scene* pScene) {
        mChildScene = pScene;
    }

    s32 getSceneID() const {
        return mSceneID;
    }
    void setSceneID(s32 id) {
        mSceneID = id;
    }

    SceneManager* getSceneMgr() const {
        return mSceneMgr;
    }
    void setSceneMgr(SceneManager* pSceneMgr) {
        mSceneMgr = pSceneMgr;
    }

private:
    Heap* mHeap;             // at 0x10
    Heap* mHeap_Mem1;        // at 0x14
    Heap* mHeap_Mem2;        // at 0x18
    Heap* mHeap_Debug;       // at 0x1C
    Scene* mParentScene;     // at 0x20
    Scene* mChildScene;      // at 0x24
    s32 mSceneID;            // at 0x28
    SceneManager* mSceneMgr; // at 0x2C
};

} // namespace EGG

#endif
