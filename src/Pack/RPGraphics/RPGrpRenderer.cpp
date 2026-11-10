// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks; nothing here uses it, so pre-define its include guard.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem/RPSysSysMsgWinMgr.h>
#include <Pack/RPSystem/RPSysUnkSingletons.h>

#include <egg/core.h>
#include <egg/gfxe.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

#include <revolution/GX.h>

// Resort: functions are emitted in reverse source order (-inline deferred);
// they are defined here last-first (highest address first).

/******************************************************************************
 * Externals with placeholder names
 ******************************************************************************/
extern "C" {
// RPGrpModelManager (Resort, unnamed; ogws names in comments)
void fn_80252424();                         // fn_801ADEB0 (static)
void fn_8025243C(RPGrpModelManager* pMgr); // fn_801ADEC8 (Destruct)
void fn_802524C8(RPGrpModelManager* pMgr); // fn_801ADF18 (after Rendering)
void fn_8025251C(RPGrpModelManager* pMgr); // fn_801ADF78
void fn_80252570(RPGrpModelManager* pMgr); // fn_801ADFD0 (CalculateInPause)
void fn_80252604(RPGrpModelManager* pMgr); // fn_801AE070 (PostCalculate)
void fn_80252734(RPGrpModelManager* pMgr); // fn_801AE160 (PreCalculate)

// EGG::GfxEngine (Resort): configuration ctor, initialize, beginDraw
void fn_801AF3FC(void* pConfig);
void fn_801AF204(void* pConfig, EGG::Heap* pHeap);
void fn_801AF34C();


// EGG::PostEffectBase::setProjection (Resort, inferred)
void fn_801B5C88(const EGG::Screen& rScreen);

// RPSysLayout::drawInit (Resort, inferred from the ogws counterpart)
void fn_8025CAAC();

// RPGrpScreen::Initialize (Resort)
void fn_80254FA8(const u16* pMaxX, const u16* pMaxY);

// RPSysEffectMgr (Resort)
s32 fn_8023D7F8(RPSysEffectMgr* pMgr);
}

// EGG::StateGX::s_modifyRatio (Resort, unnamed)
extern f32 lbl_806F09C0;

// EGG::IBinary<T> extension strings (Resort, unnamed)
extern const char* lbl_806F09D0; // DrawPathBloom
extern const char* lbl_806F09D8; // DrawPathDOF
extern const char* lbl_806F09FC; // LightManager
extern const char* lbl_806F0A28; // LightObject
extern const char* lbl_806F0A04; // LightTexture
extern const char* lbl_806F0A08; // LightTextureManager
extern const char* lbl_806F09E8; // "pfobj"
extern const char* lbl_806F09F0; // "pfog"

// Stand-in for EGG::IBinary<T>::SetBinaryExtension (Resort statics unnamed)
static inline void SetBinaryExtension(const char*& rExtension,
                                      const char* pName) {
    rExtension = pName;
}



/******************************************************************************
 * Statics
 ******************************************************************************/

// Draw callback base registered with the draw path managers (name unknown;
// vtable 0x806B9E38, ctor 0x80254DFC, dtor 0x80254CE4)
class IRPGrpRendererProc {
public:
    IRPGrpRendererProc() {}
    virtual ~IRPGrpRendererProc() {}  // at 0x8
    virtual void VF_0xC(u16 idx) = 0; // at 0xC
    virtual void VF_0x10() = 0;       // at 0x10
};

// Draw callback (name invented; vtable 0x806B9E18)
class RPGrpRendererProc : public IRPGrpRendererProc {
public:
    RPGrpRendererProc() : mEnable(true), mOption(true) {}

    virtual ~RPGrpRendererProc() {} // at 0x8
    virtual void VF_0xC(u16 idx);   // at 0xC
    virtual void VF_0x10();         // at 0x10

    // name inferred
    void Configure(bool enable, bool option) {
        mEnable = enable;
        mOption = option;
    }

    bool mEnable; // at 0x4
    bool mOption; // at 0x5
};

RPGrpRendererProc lbl_806F4DF8;

// Resort: identity matrix, used as the camera matrix after rendering
nw4r::math::MTX34 lbl_807CEEC0(1.0f, 0.0f, 0.0f, 0.0f, //
                               0.0f, 1.0f, 0.0f, 0.0f, //
                               0.0f, 0.0f, 1.0f, 0.0f);

GXColor lbl_806F4E00 = EGG::DrawGX::BLACK;

RPGrpRenderer* RPGrpRenderer::spCurrent;
u8 lbl_806F4E08;
EGG::TextureBuffer* lbl_806F4E0C;
// Only byte 0 is accessed, but the object is 2 bytes (lbl_806F4E12 sits at
// +2); a separate unreferenced byte would be dead-stripped
u8 lbl_806F4E10[2];
bool lbl_806F4E12;

RPGrpRenderer::CurrentData RPGrpRenderer::sCurrent;

s32 lbl_806F0BF8 = 12;
// Capture state flags (Resort): 0x2 capture enabled, 0x4 captured
union CaptureFlags {
    u16 raw;
    struct {
        u16 unk0 : 13;
        u16 captured : 1; // 0x4
        u16 enable : 1;   // 0x2
        u16 unk15 : 1;    // 0x1
    } bits;
};
CaptureFlags lbl_806F0BFC = {2};
s16 lbl_806F0BFE = -1;


extern "C" bool fn_80253BB4();
extern "C" void fn_80253F18(RPGrpRenderer* pRenderer);
extern "C" void fn_80253F60(RPGrpRenderer* pRenderer);
extern "C" void fn_802540B0();
extern "C" void fn_80254100(RPGrpRenderer* pRenderer);
extern "C" void fn_802542AC(RPGrpRenderer* pRenderer);
extern "C" void fn_802549A8();
extern "C" void fn_80254AE8(int idx, bool dither);

static inline void DrawAll(RPGrpRenderer* pRenderer) {
    for (IRPGrpDrawObject* pObject = pRenderer->mpDrawList; pObject != NULL;
         pObject = pObject->GetNext()) {
        pObject->UserDraw();
    }
}

static inline void DrawAllGX(RPGrpRenderer* pRenderer) {
    RPGrpRenderer::GetCurrentView()->PrepareDrawGX();

    for (IRPGrpDrawObject* pObject = pRenderer->mpDrawList; pObject != NULL;
         pObject = pObject->GetNext()) {
        pObject->UserDraw();
    }
}

/******************************************************************************
 * Functions (highest address first)
 ******************************************************************************/

// name inferred
static inline const EGG::Screen::DataEfb&
InitEfbTexData(RPSysEffectMgr::EfbTexData& rData) {
    const EGG::Screen::DataEfb& rEfb =
        RPGrpRenderer::GetCurrentScreen()->GetDataEfb();

    rData.format = GX_TF_RGB565;
    rData.width = static_cast<u16>(rEfb.vp.width / 2.0f);
    rData.height = static_cast<u16>(rEfb.vp.height / 2.0f);
    return rEfb;
}


extern "C" void fn_80254AE8(int idx, bool dither) {
    // MATCH-PENDING (R17): volatile makes MWCC reload the table entries after
    // each call (as the original does); the real declaration is unknown (the
    // tables are in .rodata, so they were const).
    static const volatile u32 sGroupNormal[] = {0x60, 0x30, 0x40, 0x50};
    static const volatile u32 sGroupCapture[] = {0x70, 0x00, 0x10, 0x20};

    u8 drawScene = RPGrpRenderer::sCurrent.pView->GetDrawScene();

    EGG::StateGX::AutoColorUpdate colorUpdate(true);
    EGG::StateGX::AutoAlphaUpdate alphaUpdate(false);
    EGG::StateGX::AutoDither ditherState(dither);

    RPSysEffectMgr* pEffectMgr = RPSysEffectMgr::instance();

    if (pEffectMgr->fn_8023D5DC(sGroupCapture[idx], drawScene)) {
        RPSysEffectMgr::EfbTexData data;
        const EGG::Screen::DataEfb& rEfb = InitEfbTexData(data);

        EGG::TextureBuffer* pBuffer =
            EGG::TextureBuffer::alloc(data.width, data.height, GX_TF_RGB565);

        pBuffer->enableInvalidateTex();
        pBuffer->capture(static_cast<u16>(rEfb.vp.x),
                         static_cast<u16>(rEfb.vp.y), true, -1);

        pEffectMgr->setCaptureEfb(pBuffer->getBuffer(), data);
        pBuffer->free();

        pEffectMgr->draw(RPGrpRenderer::sCurrent.viewMtx, drawScene,
                         sGroupCapture[idx]);
    }

    if (pEffectMgr->fn_8023D5DC(sGroupNormal[idx], drawScene)) {
        pEffectMgr->draw(RPGrpRenderer::sCurrent.viewMtx, drawScene,
                         sGroupNormal[idx]);
    }
}

/**
 * @brief Initializes the graphics systems
 */
extern "C" void fn_80254A18(u16 width, u16 height) {
    // EGG::GfxEngine configuration (Resort; layout partly unknown)
    struct {
        u16 width;  // at 0x0
        u16 height; // at 0x2
        u8 unk4[0x8 - 0x4];
        u32 unk8; // at 0x8
        u8 unkC[0xE - 0xC];
        u16 unkE; // at 0xE
        u8 unk10[0x28 - 0x10];
    } config;

    fn_801AF3FC(&config);
    config.width = width;
    config.height = height;
    config.unk8 = 1;
    config.unkE = 0x800;
    fn_801AF204(&config, NULL);

    nw4r::g3d::G3dInit(false);

    SetBinaryExtension(lbl_806F09D0, "pblm");
    SetBinaryExtension(lbl_806F09D8, "pdof");
    SetBinaryExtension(lbl_806F09FC, "plight");
    SetBinaryExtension(lbl_806F0A28, "plobj");
    SetBinaryExtension(lbl_806F0A04, "pltex");
    SetBinaryExtension(lbl_806F0A08, "plmap");
    SetBinaryExtension(lbl_806F09E8, "pfobj");
    SetBinaryExtension(lbl_806F09F0, "pfog");

    RPGrpCamera::Initialize();

    u16 maxX[2] = {608, 812};
    u16 maxY[2] = {height, height};
    fn_80254FA8(maxX, maxY);

    fn_80252424();
    fn_802549A8();
}

// MATCH-PENDING (R17): the .rodata string pool (0x80666B68) starts with these
// four names, so the original had a function using them that the linker
// dead-stripped; its body and name are unknown (name inferred).
extern "C" const char* RPGrpRenderer_GetDrawSceneName(int idx) {
    switch (idx) {
    case 0:
        return "2d";
    case 1:
        return "3d";
    case 2:
        return "3dAfter";
    default:
        return "3dFree";
    }
}

extern "C" void fn_802549D0(u8 red, u8 green, u8 blue) {
    lbl_806F4E00.r = red;
    lbl_806F4E00.g = green;
    lbl_806F4E00.b = blue;
    lbl_806F4E00.a = 0;

    RPSysSystem::instance()->setDisplayClearColor(lbl_806F4E00);
}

extern "C" GXColor* fn_802549C8() {
    return &lbl_806F4E00;
}

extern "C" void fn_802549A8() {
    RPGrpRenderer::sCurrent.viewNo = 32;
    RPGrpRenderer::sCurrent.pView = NULL;
    PSMTXIdentity(RPGrpRenderer::sCurrent.viewMtx);
}

void RPGrpRenderer::Begin() {
    lbl_806F4E08 = 0;
    lbl_806F0BF8 = 11;
    sCurrent.pScreen = NULL;

    fn_801AF34C();
    lbl_806F09C0 = RPSysSystem::instance()->Unk_80237918();
}

void RPGrpRenderer::StartDebugDraw() {
    RPGrpScreen screen(RPGrpScreen::GetRootScreen());
    screen.SetNearZ(0.0f);
    screen.SetFarZ(1.0f);
    screen.SetProjectionOrtho();
    screen.SetProjectionGX();

    GXLoadPosMtxImm(lbl_807CEEC0, GX_PNMTX0);
    GXLoadNrmMtxImm(lbl_807CEEC0, GX_PNMTX0);
}

void RPGrpRenderer::End() {
    sCurrent.pScreen = &RPGrpScreen::GetRootScreen();
    lbl_806F0BF8 = 12;
}

RPGrpRenderer* RPGrpRenderer::Construct(EGG::Allocator* pAllocator, u16 id) {
    RPGrpRenderer* pRenderer = new RPGrpRenderer(id, pAllocator);
    pRenderer->BecomeCurrent();
    lbl_806F0BF8 = 12;
    return pRenderer;
}

RPGrpRenderer::RPGrpRenderer(u16 id, EGG::Allocator* pAllocator)
    : unk0(id),
      unk2(EFlag_3 | EFlag_4 | EFlag_5),
      mClearColor((GXColor){0, 0, 0, 128}),
      mpViewList(NULL),
      mUnk98(0) {

    mpModelManager = new RPGrpModelManager(pAllocator, pAllocator);

    for (int i = 0; i < MAX_VIEW; i++) {
        mpDrawViews[i] = NULL;
    }

    mpDrawList = mpDrawTail = NULL;
}

void RPGrpRenderer::Destruct() {
    fn_8025243C(mpModelManager);
    fn_802540B0();
}

// -inline deferred would auto-inline this into Construct and Rendering
#pragma push
#pragma dont_inline on
void RPGrpRenderer::BecomeCurrent() {
    spCurrent = this;
    mpModelManager->fn_801AE21C();
    lbl_806F4E10[0] = 8;
}
#pragma pop

extern "C" void fn_802546DC(RPGrpRenderer* pRenderer) {
    fn_8025251C(pRenderer->mpModelManager);
    lbl_806F0BF8 = 0;
    DrawAll(pRenderer);

    if (lbl_806F0BFC.raw & 2) {
        fn_80254100(pRenderer);
    }
}

void RPGrpRenderer::Rendering() {
    lbl_806F4E08++;
    BecomeCurrent();
    fn_802549A8();
    lbl_806F4E12 = !lbl_806F4E12;

    for (RPGrpView* pView = mpViewList; pView != NULL;
         pView = pView->GetNextView()) {
        if (!pView->IsSysCalc()) {
            continue;
        }

        sCurrent.pView = pView;
        sCurrent.viewNo = pView->GetViewNo();
        sCurrent.pCamera = pView->GetEnableCamera();
        sCurrent.pScreen = pView->GetEnableScreen();
        PSMTXCopy(pView->fn_80255A14(), sCurrent.viewMtx);

        lbl_806F4DF8.Configure(pView->IsEffectDraw(), (unk2 & EFlag_5) != 0);

        bool capture = (lbl_806F0BFC.raw & 2) && sCurrent.viewNo == lbl_806F0BFE;

        EGG::StateGX::GXSetColorUpdate_(true);
        EGG::StateGX::GXSetAlphaUpdate_(false);

        if (capture) {
            fn_80253F60(this);
        }

        lbl_806F0BF8 = 1;
        DrawAll(this);
        pView->PrepareDraw();

        lbl_806F0BF8 = 2;
        DrawAllGX(this);
        pView->Draw();

        if (pView->GetType() == RPGrpView::EType_Render2D &&
            pView->IsDraw2DEffect()) {
            EGG::StateGX::resetGX();
            fn_8025CAAC();

            lbl_806F0BF8 = 5;
            DrawAllGX(this);

            if (pView->IsEffectDraw()) {
                GetCurrentView()->GetUnk1C()->SetProjectionGX();
                fn_80254AE8(0, (unk2 >> 4) & 1);
            }
        }

        lbl_806F0BF8 = 3;
        DrawAllGX(this);

        if (capture) {
            fn_80253F18(this);
        }
    }

    fn_802524C8(mpModelManager);
    EGG::DrawGX::SetCameraMtx(lbl_807CEEC0);

    unk2 |= EFlag_Rendered;
    lbl_806F0BF8 = 11;
    fn_802549A8();
}

void RPGrpRenderer::PreCalculate() {
    fn_80252734(mpModelManager);
}

void RPGrpRenderer::PostCalculate() {
    mpModelManager->SetUnk50(!(unk2 & EFlag_3));
    fn_80252604(mpModelManager);

    if (mpDrawTail != NULL) {
        mpDrawTail->mpNext = NULL;
    }

    fn_802542AC(this);
}

void RPGrpRenderer::CalculateInPause() {
    fn_80252570(mpModelManager);
    fn_802542AC(this);
}

extern "C" void fn_802542AC(RPGrpRenderer* pRenderer) {
    for (RPGrpView* pView = pRenderer->mpViewList; pView != NULL;
         pView = pView->GetNextView()) {
        pView->Calc();
    }
}

extern "C" void fn_80254240(RPGrpRenderer* pRenderer) {
    if (!fn_80253BB4()) {
        lbl_806F0BF8 = 4;
        DrawAll(pRenderer);
    }
}

extern "C" void fn_80254100(RPGrpRenderer* pRenderer) {
    if (fn_80253BB4()) {
        if (!(lbl_806F0BFC.raw & 4)) {
            pRenderer->mUnk98 = 0;

            for (RPGrpView* pView = pRenderer->mpViewList; pView != NULL;
                 pView = pView->GetNextView()) {
                if (pView->IsSysCalc()) {
                    pRenderer->mUnk98 |= 1 << pView->GetViewNo();
                }
            }

            if (RP_GET_INSTANCE(RPSysHomeMenuMgr)->isActive()) {
                lbl_806F0BFE = 31;
            } else {
                bool busy = true;
                if (!(lbl_806F4CD0->mFlags & 1)) {
                    if (GetSysMsgWinMgr()->mState == -1) {
                        busy = false;
                    }
                }
                if (busy) {
                    lbl_806F0BFE = 29;
                }
            }

            pRenderer->mUnk98 &= ~(1 << 31);
            pRenderer->mUnk98 &= ~(1 << 29);
        } else {
            for (RPGrpView* pView = pRenderer->mpViewList; pView != NULL;
                 pView = pView->GetNextView()) {
                if (pRenderer->mUnk98 & (1 << pView->GetViewNo())) {
                    pView->ClearSysCalc();
                }
            }
        }
    } else {
        fn_802540B0();
    }
}

extern "C" void fn_802540B0() {
    if ((lbl_806F0BFC.raw & 4)) {
        lbl_806F0BFC.bits.captured = false;

        if (lbl_806F4E0C != NULL) {
            lbl_806F4E0C->free();
            lbl_806F4E0C = NULL;
        }

        lbl_806F0BFE = -1;
    }
}

extern "C" void fn_80253F60(RPGrpRenderer* /* pRenderer */) {
    if (!fn_80253BB4()) {
        return;
    }

    RPGrpScreen* pScreen = RPGrpRenderer::sCurrent.pScreen;

    if (!(lbl_806F0BFC.raw & 4)) {
        lbl_806F0BFC.bits.captured = true;

        const EGG::Screen::DataEfb& rEfb = pScreen->GetDataEfb();
        lbl_806F4E0C = EGG::TextureBuffer::alloc(
            static_cast<u16>(rEfb.vp.width), static_cast<u16>(rEfb.vp.height),
            GX_TF_RGBA8);
        lbl_806F4E0C->capture(static_cast<u16>(rEfb.vp.x),
                              static_cast<u16>(rEfb.vp.y), false, -1);

        EGG::StateGX::fn_801A415C();
    } else {
        fn_801B5C88(*pScreen);

        EGG::PostEffectSimple effect;
        effect.setSimpleBlendMode(EGG::PostEffectSimple::cBlendMode_Opa);
        effect.setCapTexture(lbl_806F4E0C);
        effect.draw(pScreen->GetWidth(), pScreen->GetHeight());
    }
}

extern "C" void fn_80253F18(RPGrpRenderer* pRenderer) {
    if (!(lbl_806F0BFC.raw & 4)) {
        return;
    }

    for (RPGrpView* pView = pRenderer->mpViewList; pView != NULL;
         pView = pView->GetNextView()) {
        if (pRenderer->mUnk98 & (1 << pView->GetViewNo())) {
            pView->SetSysCalc();
        }
    }
}

extern "C" RPGrpView* fn_80253E90(RPGrpRenderer* pRenderer, u8 viewNo,
                                  RPGrpCamera* pCamera, RPGrpScreen* pScreen) {
    RPGrpViewRender3D* pView = new RPGrpViewRender3D(viewNo);
    pView->AttachCamera(pCamera);
    pView->AttachScreen(pScreen);
    pRenderer->mpDrawViews[viewNo] = pView;
    return pView;
}

extern "C" RPGrpView* fn_80253E1C(RPGrpRenderer* pRenderer, u8 viewNo,
                                  RPGrpScreen* pScreen) {
    RPGrpViewRender2D* pView = new RPGrpViewRender2D(viewNo);
    pView->AttachScreen(pScreen);
    pView->SetDrawScene(255);
    pRenderer->mpDrawViews[viewNo] = pView;
    return pView;
}

extern "C" void fn_80253D68(RPGrpRenderer* pRenderer) {
    for (int i = 0; i < RPGrpModelManager::MAX_SCENE; i++) {
        RPGrpModelScene* pScene =
            pRenderer->mpModelManager->GetModelScene(static_cast<u8>(i));

        if (pScene != NULL) {
            pScene->GetDrawPathManager()->SetUnk14(&lbl_806F4DF8);
        }
    }

    RPGrpView* pPrev = NULL;
    for (int i = 0; i < RPGrpRenderer::MAX_VIEW; i++) {
        RPGrpView* pView = pRenderer->GetView(i);
        if (pView != NULL) {
            if (pPrev != NULL) {
                pPrev->SetNextView(pView);
            } else {
                pRenderer->mpViewList = pView;
            }
            pPrev = pView;
        }
    }

    if (pPrev != NULL) {
        pPrev->SetNextView(NULL);
    }

    pRenderer->unk2 |= RPGrpRenderer::EFlag_ViewsLinked;
}

void RPGrpRenderer::AppendDrawObject(IRPGrpDrawObject* pObject) {
    if (mpDrawTail != NULL) {
        mpDrawTail->mpNext = pObject;
        mpDrawTail = pObject;
    } else {
        mpDrawTail = pObject;
        mpDrawList = pObject;
    }
}

extern "C" void fn_80253D34() {
    RPGrpRenderer::GetCurrentView()->SetProjectionGX();
}

extern "C" void fn_80253D10() {
    EGG::StateGX::resetGX();
    fn_8025CAAC();
}

extern "C" void fn_80253D08() {
    nw4r::g3d::G3DState::Invalidate(0x7FF);
}

extern "C" bool fn_80253BB4() {
    bool d = true;
    bool c = true;
    bool b = false;
    bool a = true;

    if (!RP_GET_INSTANCE(RPSysHomeMenuMgr)->isActive()) {
        bool busy = true;
        if (!(lbl_806F4CD0->mFlags & 1)) {
            if (GetSysMsgWinMgr()->mState == -1) {
                busy = false;
            }
        }
        if (!busy) {
            a = false;
        }
    }

    if (a) {
        if (lbl_806F0BFE == -1) {
            b = true;
        }
    }

    if (!b) {
        bool e = false;
        if (lbl_806F0BFE == 31) {
            if (RP_GET_INSTANCE(RPSysHomeMenuMgr)->isActive()) {
                e = true;
            }
        }
        if (!e) {
            c = false;
        }
    }

    if (!c) {
        bool f = false;
        if (lbl_806F0BFE == 29) {
            bool busy = true;
            if (!(lbl_806F4CD0->mFlags & 1)) {
                if (GetSysMsgWinMgr()->mState == -1) {
                    busy = false;
                }
            }
            if (busy) {
                f = true;
            }
        }
        if (!f) {
            d = false;
        }
    }

    return d;
}

void RPGrpRendererProc::VF_0xC(u16 idx) {
    static const s32 sState[8] = {6, 7, 10, 8, 9, 13, 13, 13};

    s32 state = sState[idx];
    if (state != 13) {
        lbl_806F0BF8 = state;
        DrawAllGX(RPGrpRenderer::GetCurrent());
    } else if (mEnable) {
        switch (idx) {
        case 5: {
            fn_80254AE8(1, mOption);
            break;
        }
        case 6: {
            fn_80254AE8(2, mOption);
            break;
        }
        case 7: {
            if (fn_8023D7F8(RPSysEffectMgr::instance()) != -1) {
                fn_80254AE8(3, mOption);
            }
            break;
        }
        }
    }
}

void RPGrpRendererProc::VF_0x10() {}

