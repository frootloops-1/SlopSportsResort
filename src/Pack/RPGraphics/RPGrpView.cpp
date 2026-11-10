// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks; nothing here uses it, so pre-define its include guard.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

/******************************************************************************
 *
 * RPGrpView
 *
 ******************************************************************************/

/**
 * @brief View clipper instance
 */
RPGrpView::Clipper RPGrpView::sClipper;

// Resort: .sdata 0x806F0C00 (value 1); bit 0 selects the first of the two
// identical blur paths in ScreenEffect::Draw
u16 lbl_806F0C00 = 1;

/**
 * @brief Constructor
 *
 * @param no View ID
 */
RPGrpView::RPGrpView(u8 no)
    : mViewNo(no),
      mDrawScene(0),
      mFlags(EFlag_10 | EFlag_5 | EFlag_SysDraw | EFlag_SysCalc),
      mProjType(EProjType_Max),
      mClearColor((GXColor){0, 0, 0, 255}),
      mpScreen(NULL),
      unk14(0),
      mpScreenEffect(NULL),
      mpUnk1C(NULL) {

    mpUnk1C = new RPGrpScreen();
}

/**
 * @brief Attaches a screen effect to this view
 */
void RPGrpView::CreateScreenEffect() {
    mpScreenEffect = new ScreenEffect();
}

/**
 * @brief Updates this view's state
 */
void RPGrpView::Calc() {
    if (!IsSysCalc()) {
        return;
    }

    mpUnk1C->CopyFromAnother(*GetEnableScreen());

    switch (mProjType) {
    case EProjType_Persp: {
        mpUnk1C->SetProjectionType(EGG::Screen::PROJ_PERSP);
        break;
    }

    case EProjType_Ortho: {
        mpUnk1C->SetProjectionType(EGG::Screen::PROJ_ORTHO);

        if (GetType() == EType_Render2D) {
            RPGrpScreen* pScreen = mpUnk1C;
            pScreen->SetNearZ(-10000.0f);
            pScreen->SetFarZ(10000.0f);
        }
        break;
    }

    default: {
        break;
    }
    }

    if (mFlags & EFlag_11) {
        mpUnk1C->fn_801B8974();
    }

    if (mFlags & EFlag_12) {
        mpUnk1C->SetUnkFlag6();
    }
}

/**
 * @brief Prepares this view for a new frame
 */
void RPGrpView::PrepareDraw() {
    if (!IsSysCalc()) {
        return;
    }

    if (mProjType == EProjType_Persp) {
        sClipper.Calc(mpUnk1C);
    }
}

/**
 * @brief Clears the framebuffer of the attached screen
 */
void RPGrpView::ClearBuffer() {
    GXColor clearColor = EGG::StateGX::getEfbClearColor();
    u8 flags = 0;

    if (mFlags & EFlag_FillBufferColor) {
        clearColor.r = GetClearColor().r;
        clearColor.g = GetClearColor().g;
        clearColor.b = GetClearColor().b;

        flags |= EGG::Screen::FILLBUFFER_COLOR;
    }

    if (mFlags & EFlag_FillBufferAlpha) {
        clearColor.a = GetClearColor().a;

        // Spelled out: "|=" here drops the u8 truncation retail keeps
        flags = flags | EGG::Screen::FILLBUFFER_ALPHA;
    }

    if (mFlags & EFlag_FillBufferTexture) {
        flags |= EGG::Screen::FILLBUFFER_TEXTURE;
    }

    if (flags != 0) {
        GetEnableScreen()->FillBufferGX(flags, GetClearColor());
        EGG::StateGX::setEfbClearColor(clearColor);
    }

    if (mpScreenEffect != NULL) {
        mpScreenEffect->Draw(GetEnableScreen());
    }
}

/**
 * @brief Attaches a new screen to this view
 *
 * @param pScreen Screen rendering surface
 * @return Previously attached screen
 */
RPGrpScreen* RPGrpView::AttachScreen(RPGrpScreen* pScreen) {
    RPGrpScreen* pOldScreen = mpScreen;
    mpScreen = pScreen;
    return pOldScreen;
}

/**
 * @brief Configures the GX projection matrix
 */
void RPGrpView::SetProjectionGX() const {
    EGG::DrawGX::SetCameraMtx(GetEnableCamera()->GetSavedCameraMatrix());
    mpUnk1C->SetProjectionGX();
}

/**
 * @brief Converts a position from world-space to screen-space
 *
 * @param[out] pScreenPos Position in screen-space
 * @param rWorldPos Position in world-space
 */
void RPGrpView::GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                                 const nw4r::math::VEC3& rWorldPos) const {
    if (GetCamera() != NULL) {
        GetCamera()->GetWorldToScreen(pScreenPos, rWorldPos, GetEnableScreen());
    } else {
        GetEnableScreen()->GetViewToScreen(pScreenPos, rWorldPos);
    }
}

/**
 * @brief Converts a position from screen-space to world-space
 *
 * @param[out] pWorldPos Position in world-space
 * @param rScreenPos Position in screen-space
 */
void RPGrpView::GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                                 const nw4r::math::VEC2& rScreenPos) const {
    if (GetCamera() != NULL) {
        GetCamera()->GetScreenToWorld(pWorldPos, rScreenPos, GetEnableScreen());
    } else {
        GetEnableScreen()->GetScreenToView(pWorldPos, rScreenPos);
    }
}

/**
 * @brief Gets the screen used by this view.
 * @details If no screen is attached, this function returns the root screen.
 */
RPGrpScreen* RPGrpView::GetEnableScreen() const {
    return GetScreen() != NULL ? GetScreen() : &RPGrpScreen::GetRootScreen();
}

/**
 * @brief Gets the camera used by this view.
 * @details If no camera is attached, this function returns the default
 * camera.
 */
RPGrpCamera* RPGrpView::GetEnableCamera() const {
    return GetCamera() != NULL ? GetCamera() : &RPGrpCamera::GetDefaultCamera();
}

const nw4r::math::MTX34& RPGrpView::fn_80255A14() const {
    return GetEnableCamera()->GetSavedCameraMatrix();
}

/**
 * @brief Gets the camera currently attached to this view
 */
RPGrpCamera* RPGrpView::GetCamera() const {
    return NULL;
}

/******************************************************************************
 *
 * Clipper
 *
 ******************************************************************************/

/**
 * @brief Re-calculates this clipper's clipping planes
 *
 * @param pScreen Screen rendering surface
 */
void RPGrpView::Clipper::Calc(const RPGrpScreen* pScreen) {
    // MATCH-PENDING (R17): named local for the 1.0f numerator; only swaps the
    // f0/f1 colouring of the constant and tanFovy (inline FInv-style helpers,
    // local tan/near/inv did not)
    f32 one = 1.0f;
    f32 ny = pScreen->GetNearZ() * (one / pScreen->GetTanFovy());
    f32 nx = ny * pScreen->GetAspect() *
             (pScreen->GetScale().x / pScreen->GetScale().y);

    nw4r::math::VEC3 bl(-nx, -ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 tl(-nx, ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 tr(nx, ny, -pScreen->GetNearZ());
    nw4r::math::VEC3 br(nx, -ny, -pScreen->GetNearZ());

    nw4r::math::VEC3Cross(&mPlanes[0], &tl, &bl);
    nw4r::math::VEC3Cross(&mPlanes[1], &tr, &tl);
    nw4r::math::VEC3Cross(&mPlanes[2], &br, &tr);
    nw4r::math::VEC3Cross(&mPlanes[3], &bl, &br);

    nw4r::math::VEC3Normalize(&mPlanes[0], &mPlanes[0]);
    nw4r::math::VEC3Normalize(&mPlanes[1], &mPlanes[1]);
    nw4r::math::VEC3Normalize(&mPlanes[2], &mPlanes[2]);
    nw4r::math::VEC3Normalize(&mPlanes[3], &mPlanes[3]);
}

/******************************************************************************
 *
 * ScreenEffect
 *
 ******************************************************************************/

/**
 * @brief Constructor
 */
void RPGrpView::ScreenEffect::fn_80255864() {
    mColorMultiply = EGG::DrawGX::WHITE;
    mColorAdd = EGG::DrawGX::BLACK;
    mColorBlend = (GXColor){0, 0, 0, 0};

    mBlurOffset = 1.2f;
    mBlurAlpha = 0;
}

/**
 * @brief Draws this effect to the specified screen
 *
 * @param pScreen Screen rendering surface
 */
void RPGrpView::ScreenEffect::Draw(const RPGrpScreen* pScreen) {
    bool needBlur = mBlurAlpha > 0;

    bool needMul = mColorMultiply.r != 255 || mColorMultiply.g != 255 ||
                   mColorMultiply.b != 255;

    bool needAdd = (mColorAdd.r != 0 || mColorAdd.g != 0 || mColorAdd.b != 0) &&
                   mColorAdd.a > 0;

    bool needNormal = mColorBlend.a > 0;

    if (needBlur || needMul || needAdd || needNormal) {
        EGG::StateGX::GXSetColorUpdate_(true);
        EGG::StateGX::GXSetAlphaUpdate_(false);

        EGG::StateGX::fn_801A415C();

        EGG::Screen clone(*pScreen);
        clone.SetNearZ(0.0f);
        clone.SetFarZ(1.0f);
        clone.SetCanvasMode(EGG::Screen::CANVAS_LU);
        clone.SetProjectionType(EGG::Screen::PROJ_ORTHO);
        clone.SetProjectionGX();

        const EGG::Screen::DataEfb& rEfb = pScreen->GetDataEfb();
        u16 x = static_cast<u16>(rEfb.vp.x);
        u16 y = static_cast<u16>(rEfb.vp.y);
        // Downscaled for mipmapping
        u16 halfWidth = static_cast<u16>(rEfb.vp.width / 2);
        u16 halfHeight = static_cast<u16>(rEfb.vp.height / 2);

        if (needBlur) {
            if (lbl_806F0C00 & 1) {
            // Screenshot used as a base for blurring
            EGG::TextureBuffer* pScreenCapture = EGG::TextureBuffer::alloc( //
                halfWidth,                                                  //
                halfHeight,                                                 //
                GX_TF_RGBA8);

            // Backup of original pixels that will be clobbered by blurring
            EGG::TextureBuffer* pScreenBackup = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                             //
                halfHeight / 2,                                            //
                GX_TF_RGBA8);

            // Blur posteffect result in texture form
            EGG::TextureBuffer* pEffectCapture = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                              //
                halfHeight / 2,                                             //
                GX_TF_RGBA8);

            // Save the appearance of the screen space
            // that will be overwritten by the blur posteffect.
            pScreenBackup->capture(x, y);

            // Take a screenshot to use as a base for blurring
            pScreenCapture->setVFilterBlur();
            pScreenCapture->capture(x, y, true);

            EGG::PostEffectBlurSimple eff;
            eff.mRadius = mBlurOffset;
            eff.mTevScale = GX_CS_SCALE_1;
            eff.mAlpha = 200;
            eff.mUseTwoStages = false;
            eff.setCapTexture(pScreenCapture);
            eff.setBlendMode(EGG::PostEffectBase::cBlendMode_None);

            // Draw the result of the blur posteffect (downscaled)
            eff.draw(pScreen->GetWidth() / 4.0f, pScreen->GetHeight() / 4.0f);

            // Capture the posteffect result as a new texture
            pEffectCapture->setVFilterBlur();
            pEffectCapture->capture(x, y);

            nw4r::math::MTX34 proj;
            EGG::DrawGX::BeginDrawScreen(true, true, true);

            // Restore the pixels overwritten by the posteffect work
            PSMTXScale(                      //
                proj,                        //
                pScreen->GetWidth() / 4.0f,  //
                pScreen->GetHeight() / 4.0f, //
                1.0f);
            pScreenBackup->load(GX_TEXMAP0);
            EGG::DrawGX::DrawScreenTexture(proj, EGG::DrawGX::WHITE);

            // Upscale the blur effect to the entire screen
            PSMTXScale(proj, pScreen->GetWidth(), pScreen->GetHeight(), 1.0f);
            pEffectCapture->load(GX_TEXMAP0);
            GXColor color = (GXColor){255, 255, 255, mBlurAlpha};
            EGG::DrawGX::DrawScreenTexture(proj, color);

            pScreenBackup->free();
            pScreenCapture->free();
            pEffectCapture->free();
            } else {
            // Screenshot used as a base for blurring
            EGG::TextureBuffer* pScreenCapture = EGG::TextureBuffer::alloc( //
                halfWidth,                                                  //
                halfHeight,                                                 //
                GX_TF_RGBA8);

            // Backup of original pixels that will be clobbered by blurring
            EGG::TextureBuffer* pScreenBackup = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                             //
                halfHeight / 2,                                            //
                GX_TF_RGBA8);

            // Blur posteffect result in texture form
            EGG::TextureBuffer* pEffectCapture = EGG::TextureBuffer::alloc( //
                halfWidth / 2,                                              //
                halfHeight / 2,                                             //
                GX_TF_RGBA8);

            // Save the appearance of the screen space
            // that will be overwritten by the blur posteffect.
            pScreenBackup->capture(x, y);

            // Take a screenshot to use as a base for blurring
            pScreenCapture->setVFilterBlur();
            pScreenCapture->capture(x, y, true);

            EGG::PostEffectBlurSimple eff;
            eff.mRadius = mBlurOffset;
            eff.mTevScale = GX_CS_SCALE_1;
            eff.mAlpha = 200;
            eff.mUseTwoStages = false;
            eff.setCapTexture(pScreenCapture);
            eff.setBlendMode(EGG::PostEffectBase::cBlendMode_None);

            // Draw the result of the blur posteffect (downscaled)
            eff.draw(pScreen->GetWidth() / 4.0f, pScreen->GetHeight() / 4.0f);

            // Capture the posteffect result as a new texture
            pEffectCapture->setVFilterBlur();
            pEffectCapture->capture(x, y);

            nw4r::math::MTX34 proj;
            EGG::DrawGX::BeginDrawScreen(true, true, true);

            // Restore the pixels overwritten by the posteffect work
            PSMTXScale(                      //
                proj,                        //
                pScreen->GetWidth() / 4.0f,  //
                pScreen->GetHeight() / 4.0f, //
                1.0f);
            pScreenBackup->load(GX_TEXMAP0);
            EGG::DrawGX::DrawScreenTexture(proj, EGG::DrawGX::WHITE);

            // Upscale the blur effect to the entire screen
            PSMTXScale(proj, pScreen->GetWidth(), pScreen->GetHeight(), 1.0f);
            pEffectCapture->load(GX_TEXMAP0);
            GXColor color = (GXColor){255, 255, 255, mBlurAlpha};
            EGG::DrawGX::DrawScreenTexture(proj, color);

            pScreenBackup->free();
            pScreenCapture->free();
            pEffectCapture->free();
            }
        }

        if (needMul || needAdd || needNormal) {
            EGG::DrawGX::BeginDrawScreen(true, false, false);

            nw4r::math::MTX34 proj;
            PSMTXScale(proj, pScreen->GetWidth(), pScreen->GetHeight(), 1.0f);

            if (needMul) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_MUL);
                EGG::DrawGX::DrawScreen(proj, mColorMultiply);
            }

            if (needAdd) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_ADD_ALPHA);
                EGG::DrawGX::DrawScreen(proj, mColorAdd);
            }

            if (needNormal) {
                EGG::DrawGX::SetBlendMode(EGG::DrawGX::BLEND_NORMAL);
                EGG::DrawGX::DrawScreen(proj, mColorBlend);
            }
        }
    }
}
