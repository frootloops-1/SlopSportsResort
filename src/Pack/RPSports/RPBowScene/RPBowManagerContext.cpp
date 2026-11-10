// Resort (RZTE01_01) port of Wii Sports RPBowManagerContext.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// g3d_gpu.h (`static const u8 cm2hw[]`) emits a stray .sdata2 entry that this
// object lacks. Pre-define its include guard so it is skipped; nothing here uses it.
#define NW4R_G3D_PLATFORM_GPU_H

#include <Pack/RPSports/RPBowScene/bowling.h>
#include <Pack/RPUtility/RPUtlRandom.h>

namespace Bowling {

struct WeightedLanes {
    u8 data[15];
};

static inline int GetBallReturnIndex(int lane) {
    int sBallReturnMapping[] = { 0, 1, 0, 3, 2, 3 };
    return sBallReturnMapping[lane];
}

static const WeightedLanes sTargetLaneWeights = {{
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x01, 0x01, 0x02,
    0x02, 0x03, 0x03, 0x04, 0x05
}};

/**
 * @brief Initializes the manager context and its sub-managers
 */
void RPBowManagerContext::Initialize() {
    for (int i = 0; i < 6; i++) {
        mpManagers[i] = new RPBowNpcManager();
        mpManagers[i]->InitAudioActors(i);
    }
    mIsEnabled = 0;
}

/**
 * @brief Links NPC lanes to ball returns and balls
 *
 * @param pLaneManager Global lane manager instance
 * @param pSceneObjectManager Scene object manager instance
 */
void Bowling::RPBowManagerContext::LinkNpcLanes(RPBowGlobalLaneManager* pLaneManager, SceneObjectManager* pSceneObjectManager) {
    for (int i = 0; i < 6; i++) {
        mpManagers[i]->Setup(
            pLaneManager->pLanes[i + 1],
            pSceneObjectManager->entities.npcs[i * 3 + 0],
            pSceneObjectManager->entities.npcs[i * 3 + 1],
            pSceneObjectManager->entities.npcs[i * 3 + 2],
            i,
            pSceneObjectManager->entities.ballReturns[GetBallReturnIndex(i)],
            pSceneObjectManager->entities.balls[i + 1]
        );
    }
}

/**
 * @brief Sets the state flag for all NPC managers
 *
 * @param flag Status value applied to each NPC manager
 */
void RPBowManagerContext::SetNpcStateFlags(u8 flag) {
    for (int i = 0; i < 6; i++) {
        mpManagers[i]->SetStateFlag(flag);
    }
}

/**
 * @brief Updates the six NPC bowling lanes and starts a new NPC turn if permitted
 *
 * @details Lanes closer to the player are heavily preferred when a new NPC is activated.
 * A maximum of 2 NPCs are allowed to be active at once. New NPCs have a 1-in-180 chance to start per frame.
 */
void RPBowManagerContext::UpdateNpcs() {
    int activeCount = 0;

    for (int i = 0; i < 6; i++) {
        mpManagers[i]->Update();

        if (mpManagers[i]->IsLaneIdle() == 0) {
            activeCount++;
        }
    }

    if (activeCount >= 2) {
        return;
    }

    int targetLane = -1;

    if ((RPUtlRandom::getU32() % 180) == 0) {
        WeightedLanes weightedLanes = sTargetLaneWeights;
        u32 idx = (u32)(RPUtlRandom::getF32() * 15.0f);
        targetLane = weightedLanes.data[idx];
    }

    if (targetLane != -1) {
        if (mpManagers[targetLane]->IsLaneIdle() != 0) {
            mpManagers[targetLane]->ActivateNpcTurn();
        }
    }
}

/**
 * @brief Prints debug information for all NPC managers
 */
void RPBowManagerContext::DebugPrintStates() {
    if (mIsEnabled != 0) {
        for (int i = 0; i < 6; i++) {
            mpManagers[i]->DebugPrintNpcState();
        }
    }
}

}  // namespace Bowling
