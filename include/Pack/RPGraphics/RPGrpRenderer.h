#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class IRPGrpDrawObject;
class RPGrpCamera;
class RPGrpModelManager;
class RPGrpScreen;
class RPGrpView;

/**
 * @brief Rendering engine
 *
 * Resort layout (ctor 0x802547B0, `new` size 0xA0): data members first, the
 * vtable pointer (dtor only, 0x806B9E2C) at 0x9C.
 */
class RPGrpRenderer {
public:
    //! Maximum number of renderer views
    static const int MAX_VIEW = 32;

public:
    /**
     * @brief Gets the currently active manager instance
     */
    static RPGrpRenderer* GetCurrent() {
        return spCurrent;
    }

    /**
     * @brief Gets the view currently being rendered to
     */
    static RPGrpView* GetCurrentView() {
        return sCurrent.pView;
    }

    RPGrpView* GetView(int idx) const {
        return mpDrawViews[idx];
    }

    /**
     * @brief Gets the screen currently being rendered to
     */
    static RPGrpScreen* GetCurrentScreen() {
        return sCurrent.pScreen;
    }

    static void Begin();
    static void End();

    static void StartDebugDraw();

    static RPGrpRenderer* Construct(EGG::Allocator* pAllocator, u16 id);

    void Rendering();
    void Destruct();
    void BecomeCurrent();

    void AppendDrawObject(IRPGrpDrawObject* pObject);
    void AppendDrawObject(IRPGrpDrawObject& rObject) {
        AppendDrawObject(&rObject);
    }

    void PreCalculate();
    void PostCalculate();
    void CalculateInPause();

    IRPGrpDrawObject* GetDrawList() const {
        return mpDrawList;
    }

    RPGrpModelManager* GetModelManager() const {
        return mpModelManager;
    }

public:
    // Resort: the "current view" statics are one 0x40-byte bss block at
    // 0x807CEEF0 (lbl_807CEEF0). Evidence: RPGrpRenderer.s 0x802543F8-0x80254434
    // (writes), 0x802548BC (init of +0x3c), 0x80253F80 and RPSysTextWriter
    // (read of +0x3c).
    struct CurrentData {
        u8 viewNo; // at 0x0 (copy of byte 0 of the view)
        RPGrpView* pView; // at 0x4, view currently being rendered to
        nw4r::math::MTX34 viewMtx; // at 0x8, saved camera matrix
        RPGrpCamera* pCamera; // at 0x38
        RPGrpScreen* pScreen; // at 0x3C, screen currently being rendered to
    };

    static CurrentData sCurrent;

public:
    RPGrpRenderer(u16 id, EGG::Allocator* pAllocator);

    //! Currently active renderer
    static RPGrpRenderer* spCurrent;

    // Resort flags (unk2): 0x1 views linked, 0x2 rendered once,
    // 0x8 cleared -> model manager flag (PostCalculate), 0x10/0x20 effect
    // draw options (Rendering)
    enum {
        EFlag_ViewsLinked = 1 << 0,
        EFlag_Rendered = 1 << 1,
        EFlag_3 = 1 << 3,
        EFlag_4 = 1 << 4,
        EFlag_5 = 1 << 5,
    };

    u16 unk0; // at 0x0
    u16 unk2; // at 0x2
    GXColor mClearColor; // at 0x4
    IRPGrpDrawObject* mpDrawList; // at 0x8
    IRPGrpDrawObject* mpDrawTail; // at 0xC
    RPGrpView* mpDrawViews[MAX_VIEW]; // at 0x10
    RPGrpView* mpViewList; // at 0x90
    RPGrpModelManager* mpModelManager; // at 0x94
    u32 mUnk98; // at 0x98, bit mask of views disabled during capture

public:
    virtual ~RPGrpRenderer() {} // at 0x8
};

//! @}

#endif
