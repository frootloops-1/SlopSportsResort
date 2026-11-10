// Resort (RZTE01_01) port of Wii Sports RPBowTrajectoryGuide.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPSports/RPBowScene/bowling.h>

struct BowTGGlobal {
    u8 pad[0x18];
    s32 f18;
};
extern BowTGGlobal* lbl_806F5950;
extern "C" void fn_80372FD8(RPGrpModel* pModel, int unk1, int unk2, GXColor color);

namespace Bowling {

/**
 * @brief Destructor
 */
// MATCH-PENDING (R17): ledger #9. Hand-written mangled dtor; real source is a class dtor (base dtors trivial in Resort).
extern "C" void* __dt__Q27Bowling20RPBowTrajectoryGuideFv(void* pThis, s32 deleteFlag) {
    if (pThis != NULL && deleteFlag > 0) {
        operator delete(pThis);
    }
    return pThis;
}

/**
 * @brief Sets the main directional indicator models for the trajectory guide
 *
 * @param pMainModel Primary guide model
 * @param pUnkModel Secondary guide model
 */
void RPBowTrajectoryGuide::SetMainModels(RPGrpModel* pMainModel, RPGrpModel* pUnkModel) {
    mpMainModel = pMainModel;
    mpUnkModel = pUnkModel;
}

/**
 * @brief Assigns a dot model to a specific index in the guide path
 *
 * @param index Index of the dot model
 * @param pDotModel Point model along the trajectory
 */
void RPBowTrajectoryGuide::SetDotModel(u32 index, RPGrpModel* pDotModel) {
    mpDotModels[index] = pDotModel;
}

/**
 * @brief Initializes the trajectory guide state upon scene startup
 */
void RPBowTrajectoryGuide::Initialize() {
    Reset();
}

/**
 * @brief Resets the trajectory guide state for a new shot
 */
void RPBowTrajectoryGuide::Reset() {
    mActiveModelIndex = 0;
    mIsVisible = 0;
    mStartX = 0.0f;
    mAngle = 0.0f;
    unk_0x60 = 0;
    mLimitWidth = 0.0f;
    mLimitCenter = 0.0f;
    unk_0xB0 = 0.0f;
}

/**
 * @brief Renders the trajectory guide
 * @details Computes transforms and pushes both the main indicator (arrow) and
 * the individual path dots to the renderer to visually represent the player's aim.
 */
void RPBowTrajectoryGuide::Draw() {
    if (mIsVisible == 0) return;

    f32 cosAngle = std::cos(mAngle);
    f32 nCosAngle = -cosAngle;
    f32 sinAngle = std::sin(mAngle);

    nw4r::math::VEC3 vecB(sinAngle, 0.0f, nCosAngle);
    nw4r::math::VEC3 vecA(0.0f, -1.0f, 0.0f);
    nw4r::math::VEC3 vecCross;
    nw4r::math::VEC3Cross(&vecCross, &vecB, &vecA);

    nw4r::math::VEC3 vecBase(mStartX, 0.0f, 20.0f);

    nw4r::math::MTX34 mtx(
        1.0f, 0.0f, 0.0f, vecBase.x,
        0.0f, 1.0f, 0.0f, vecBase.y + 0.03f,
        0.0f, 0.0f, 1.0f, vecBase.z
    );

    (&mpMainModel)[mActiveModelIndex]->Unk_801E5D00(&mtx);

    (&mpMainModel)[mActiveModelIndex]->UpdateFrame();
    (&mpMainModel)[mActiveModelIndex]->Calc();
    (&mpMainModel)[mActiveModelIndex]->Entry();

    nw4r::math::MTX34 mtx2(
        vecCross.x, vecA.x, vecB.x, 0.0f,
        vecCross.y, vecA.y, vecB.y, 0.0f,
        vecCross.z, vecA.z, vecB.z, 0.0f
    );

    int numDots;
    if (lbl_806F5950->f18 == 0) {
        numDots = 16;
    } else {
        numDots = (int)(1.7f * (17.0f * unk_0xB0) + 16.0f);
    }

    GXColor color;
    if (mActiveModelIndex == 0) {
        color.r = 0;
        color.g = 0;
        color.b = 255;
    } else {
        color.r = 255;
        color.g = 0;
        color.b = 0;
    }

    for (int i = 0; i < numDots && i < 33; i++) {
        nw4r::math::VEC3 vecFinal = vecBase + ((vecB * 6.0f) * static_cast<f32>(i));

        f32 width = mLimitWidth;
        f32 diffX = vecFinal.x - mLimitCenter;

        if (diffX < -width || diffX > width) {
            if (vecFinal.z < -6.0f) {
                continue;
            }
        }

        mtx2._03 = vecFinal.x;
        mtx2._13 = vecFinal.y + 0.03f;
        mtx2._23 = vecFinal.z;

        mpDotModels[i]->Unk_801E5D00(&mtx2);

        mpDotModels[i]->UpdateFrame();
        mpDotModels[i]->Calc();
        mpDotModels[i]->Entry();
        fn_80372FD8(mpDotModels[i], 0, 0, color);
    }
}

extern "C" void fn_804CF020() {}

} // namespace Bowling

// Tables of this unit written out as data under their address labels (vtables:
// slot 0 = RTTI, slot 1 = this-offset; the classes are not modelled with their
// full virtual lists yet).
extern "C" {
void* __dt__Q27Bowling20RPBowTrajectoryGuideFv(void*, s32);
void Initialize__Q27Bowling20RPBowTrajectoryGuideFv();
void Draw__Q27Bowling20RPBowTrajectoryGuideFv();
void fn_804CF020();
void fn_804C7B60();
void fn_804C7D14();
void fn_804C7D10();

void* lbl_806DE9E0[] = {
    0,
    0,
    (void*)__dt__Q27Bowling20RPBowTrajectoryGuideFv,
    (void*)Initialize__Q27Bowling20RPBowTrajectoryGuideFv,
    (void*)Draw__Q27Bowling20RPBowTrajectoryGuideFv,
    (void*)fn_804CF020,
    (void*)fn_804C7B60,
    (void*)fn_804C7D14,
    (void*)fn_804C7D10,
    0,
};
}  // extern "C"
