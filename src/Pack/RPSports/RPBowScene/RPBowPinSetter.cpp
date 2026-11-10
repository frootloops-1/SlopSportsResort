// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

#define SWEEPER_BALL_Z_TRIGGER -192.0f
#define SWEEPER_FRAME_LIFT_PINS 0x73
#define SWEEPER_FRAME_START_SWEEP 0xAF
#define SWEEPER_FRAME_PLACE_PINS 0xF5
#define SWEEPER_FRAME_END 0x1B8

/**
 * @brief Resets the pin setter state
 *
 * @param pContext Lane context
 * @param isNewRack Flag indicating if this is a new rack
 */
void ResetPinSetterState(LaneContext* pContext, u8 isNewRack) {
    memset(&pContext->setterAnm, 0, 0x10);
    pContext->setterAnm.isNewRack = isNewRack;

    PinSetter* pSetter = pContext->pPinSetter;
    pSetter->sequencePhase = 0;
    pSetter->primaryState = 0;
    pSetter->frameTimer = 0.0f;
}

/**
 * @brief Triggers the pin setter animation sequence
 *
 * @param pContext Lane context
 * @param spawnNewRack Flag indicating if a new rack should be spawned
 */
void TriggerPinSetter(LaneContext* pContext, int spawnNewRack) {
    if (pContext->setterAnm.sequenceFrameCount == 0) {
        pContext->setterAnm.sequenceFrameCount = 1;
        if (spawnNewRack != 0) {
            pContext->setterAnm.isNewRack = 1;
        }
    }
}

/**
 * @brief Updates the pin setter state and animations
 *
 * @param pContext Lane context
 * @return 1 on success, otherwise 0
 */
int UpdatePinSetter(LaneContext* pContext) {
    int currentAnimMode = pContext->throwContext.animationMode;
    pContext->setterAnm.animOffsetZ = 0.0f;
    pContext->setterAnm.animRotationY = -180.5f;

    if (currentAnimMode == 2) {
        return 1;
    }

    int sequenceFrame = pContext->setterAnm.sequenceFrameCount;
    if (sequenceFrame == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            pContext->pPinManager->pPinBodies[i]->mode_0x28C = 0;
        }

        nw4r::math::VEC3 ballPos(pContext->throwContext.ballMtx._03, pContext->throwContext.ballMtx._13, pContext->throwContext.ballMtx._23);

        if (ballPos.z < SWEEPER_BALL_Z_TRIGGER) {
            pContext->pPinSetter->sequencePhase = 1;
        }
        return 1;
    }

    if (currentAnimMode != 0) {
        return 1;
    }

    if (sequenceFrame == 1 && pContext->setterAnm.isNewRack == 0) {
        pContext->pPinSetter->sequencePhase = 2;
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_LIFT_PINS && pContext->setterAnm.isNewRack == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            if (pContext->pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pContext->pPinManager->pPinBodies[i]->mode_0x28C = 1;
            }
        }
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_START_SWEEP) {
        pContext->pPinSetter->sequencePhase = 3;
    }

    if (pContext->setterAnm.sequenceFrameCount > SWEEPER_FRAME_START_SWEEP) {
        pContext->setterAnm.animOffsetZ = 0.28f * ((float)pContext->setterAnm.sequenceFrameCount - (float)SWEEPER_FRAME_START_SWEEP);
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && pContext->setterAnm.isNewRack == 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            if (pContext->pPinManager->pPinBodies[i]->unkFlag_0x250 == 0) {
                pContext->pPinManager->pPinBodies[i]->mode_0x28C = 3;
            }
        }
    }

    if (pContext->setterAnm.sequenceFrameCount == SWEEPER_FRAME_PLACE_PINS && pContext->setterAnm.isNewRack != 0) {
        for (int i = 0; i < pContext->pinCount; i++) {
            pContext->pPinManager->pPinBodies[i]->VF_0x04();

            pContext->pPinManager->pPinBodies[i]->isActive = 1;

            pContext->pPinManager->pPinBodies[i]->SetRackPose(
                nw4r::math::VEC3(pContext->pPinManager->pPinBodies[i]->field_0xFC.x, 8.0f,
                                 pContext->pPinManager->pPinBodies[i]->field_0xFC.z));

            pContext->pPinManager->pPinBodies[i]->mode_0x28C = 3;
        }
    }

    pContext->setterAnm.sequenceFrameCount++;
    return 1;
}

/**
 * @brief Tests whether the pin setter is currently active
 *
 * @param pContext Lane context
 * @return 1 if active, 0 otherwise
 */
int IsPinSetterActive(LaneContext* pContext) {
    int frame = pContext->setterAnm.sequenceFrameCount;
    if (frame != 0 && frame < SWEEPER_FRAME_END) {
        return 1;
    }
    return 0;
}

/**
 * @brief Unknown function (stubbed). Wii Sports fn_803345F0.
 */
void fn_804E5100(LaneContext* /* unused */) {
    ;
}

} // namespace Bowling
