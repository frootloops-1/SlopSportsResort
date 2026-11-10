#ifndef RP_SYSTEM_UNK_SINGLETONS_H
#define RP_SYSTEM_UNK_SINGLETONS_H
#include <Pack/types_pack.h>

/**
 * @file
 * @brief Placeholder declarations for Resort singletons that RP code reaches
 * through an asserting accessor.
 *
 * Resort checks every such singleton with `fn_80370BD4(instance != NULL,
 * "<ClassName>")` (a release no-op stub) before using it. The class names come
 * from those assert strings; method names are placeholders. The name strings
 * are shared between translation units (one copy per string in the DOL), so
 * they are declared here, not defined per file; how the original emitted them
 * is still open (see the lesson "RPSysSystem 39/39 but flip fails").
 */

extern "C" {
//! Singleton assert stub (no-op in release)
void fn_80370BD4(int exists, const char* pName);
}


class Nwc24Mgr;

//! Nwc24Mgr instance (.sbss 0x806F4F30)
extern Nwc24Mgr* lbl_806F4F30;

extern "C" {
//! Nwc24Mgr query used by the scene-change checks (owner unit unsplit)
BOOL fn_80283104(Nwc24Mgr* pMgr);
}

/**
 * @brief Nwc24 manager singleton accessor (asserts the instance exists)
 */
inline Nwc24Mgr* GetNwc24Mgr() {
    fn_80370BD4(lbl_806F4F30 != NULL, "Nwc24Mgr");
    return lbl_806F4F30;
}

/**
 * @brief SD card manager singleton (instance at .sbss 0x806F5240; methods at
 * 0x8035EC98-0x8035ECA8 are release stubs). Layout unknown except 0x64.
 */
class SDCardMgr {
private:
    u8 UNK_0x0[0x64];

public:
    bool mUnk64; // at 0x64
};

class StaticMem;
class ControllerManager;
class RPSysDbgScenePatroler;
class RPSysSysMsgWinMgr;

//! "StaticMem" (.data 0x806B56A8)
extern char lbl_806B56A8[];
//! "ControllerManager" (.data 0x806B53E0)
extern char lbl_806B53E0[];

/**
 * @brief Unidentified singleton (.sbss 0x806F4CD0) whose flag word bit 0
 * suspends scene calculation and drawing. Layout unknown except 0x8.
 */
class Unk_806F4CD0 {
private:
    u8 UNK_0x0[0x8];

public:
    u32 mFlags; // at 0x8
};

extern Unk_806F4CD0* lbl_806F4CD0;
extern SDCardMgr* lbl_806F5240;             //!< SDCardMgr instance
extern StaticMem* lbl_806F4E98;             //!< StaticMem instance
extern ControllerManager* lbl_806F4EE0;     //!< ControllerManager instance
extern RPSysDbgScenePatroler* lbl_806F4CE8; //!< RPSysDbgScenePatroler instance
extern RPSysSysMsgWinMgr* lbl_806F4CE0;     //!< RPSysSysMsgWinMgr instance

inline SDCardMgr* GetSDCardMgr() {
    fn_80370BD4(lbl_806F5240 != NULL, "SDCardMgr");
    return lbl_806F5240;
}

inline StaticMem* GetStaticMem() {
    fn_80370BD4(lbl_806F4E98 != NULL, lbl_806B56A8);
    return lbl_806F4E98;
}

inline ControllerManager* GetControllerManager() {
    fn_80370BD4(lbl_806F4EE0 != NULL, lbl_806B53E0);
    return lbl_806F4EE0;
}

inline RPSysSysMsgWinMgr* GetSysMsgWinMgr() {
    fn_80370BD4(lbl_806F4CE0 != NULL, "RPSysSysMsgWinMgr");
    return lbl_806F4CE0;
}

inline RPSysDbgScenePatroler* GetDbgScenePatroler() {
    fn_80370BD4(lbl_806F4CE8 != NULL, "RPSysDbgScenePatroler");
    return lbl_806F4CE8;
}

#endif
