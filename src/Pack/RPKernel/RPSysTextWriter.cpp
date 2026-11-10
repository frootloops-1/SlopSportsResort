// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPGraphics.h>
#include <Pack/RPKernel.h>
#include <Pack/RPSystem.h>

#include <nw4r/math.h>

#include <revolution/GX.h>

#include <cstdarg>
#include <cstring>

RPSysTextWriter* RPSysTextWriter::spInstance = NULL;

// Resort: no DestroyInstance exists in the retail binary
void RPSysTextWriter::CreateInstance() {
    spInstance = new RPSysTextWriter();
}

RPSysTextWriter::RPSysTextWriter() {
    nw4r::ut::RomFont* pRomFont =
        RP_GET_INSTANCE(RPSysFontManager)->GetRomFont();

    SetFont(*pRomFont);

    mIsInBegin = false;
}

RPSysTextWriter::~RPSysTextWriter() {}

void RPSysTextWriter::Reset() {
    SetAlpha(255);

    EnableFixedWidth(false);
    SetFixedWidth(0.0f);

    ResetColorMapping();
    SetGradationMode(GRADMODE_NONE);
    SetTextColor(nw4r::ut::Color::ELEMENT_MAX);

    SetScale(1.0f, 1.0f);
    SetCursor(0.0f, 0.0f, 0.0f);

    EnableLinearFilter(true, true);
    SetCharSpace(0.0f);
    SetLineSpace(0.0f);
    SetTabWidth(4);
    SetDrawFlag(0);
}

void RPSysTextWriter::SetCursorFlipped(f32 x, f32 y) {
    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();
    if (pScreen->GetCanvasMode() == RPGrpScreen::CANVAS_CC) {
        y = -y;
    }
    SetCursor(x, y);
}

void RPSysTextWriter::SetCursorZeroCenter(f32 x, f32 y) {
    RPGrpScreen* pScreen = RPGrpRenderer::GetCurrentScreen();

    if (pScreen->GetCanvasMode() == RPGrpScreen::CANVAS_CC) {
        y = -y;
    }

    switch (pScreen->GetCanvasMode()) {
    case RPGrpScreen::CANVAS_CC: {
        x = x * pScreen->GetWidth() / 2;
        y = y * pScreen->GetHeight() / 2;
        break;
    }

    case RPGrpScreen::CANVAS_LU: {
        x = (x + 1.0f) * pScreen->GetWidth() / 2;
        y = (-y + 1.0f) * pScreen->GetHeight() / 2;
        break;
    }

    default: {
        break;
    }
    }

    SetCursor(x, y);
}

void RPSysTextWriter::Printf(f32 x, f32 y, const char* pMsg, ...) {
    std::va_list list;
    va_start(list, pMsg);

    SetCursorFlipped(x, y);
    VPrintf(pMsg, list);

    va_end(list);
}

void RPSysTextWriter::PrintZeroCenter(f32 x, f32 y, const char* pMsg) {
    SetCursorZeroCenter(x, y);
    Print(pMsg, std::strlen(pMsg));
}

void RPSysTextWriter::PrintfZeroCenter(f32 x, f32 y, const char* pMsg, ...) {
    std::va_list list;
    va_start(list, pMsg);

    SetCursorZeroCenter(x, y);
    VPrintf(pMsg, list);

    va_end(list);
}

/**
 * @brief Sets up a GX context for rendering
 */
void RPSysTextWriter::Begin() {
    mIsInBegin = true;
    SetupGX();

    // Always pass the Z test (draw over everything)
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);

    nw4r::math::MTX34 posMtx;
    nw4r::math::MTX34Identity(&posMtx);

    // Correct for centered canvas mode
    // TODO(kiwi) How exactly does this work?
    if (RPGrpRenderer::GetCurrentScreen()->GetCanvasMode() ==
        RPGrpScreen::CANVAS_CC) {

        posMtx._01 = -posMtx._01;
        posMtx._11 = -posMtx._11;
        posMtx._21 = -posMtx._21;
    }

    GXLoadPosMtxImm(posMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

/**
 * @brief Ends the rendering context
 */
void RPSysTextWriter::End() {
    mIsInBegin = false;
}

