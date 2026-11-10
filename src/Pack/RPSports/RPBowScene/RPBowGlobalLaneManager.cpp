// Resort (RZTE01_01) port of Wii Sports RPBowGlobalLaneManager.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <types.h>
#include <nw4r/math.h>

// Minimal local views of the bowling types (see bowling.h). bowling.h is not
// included because its headers pull unrelated pool data into .sdata/.sdata2.

// The symbol name of fn_804CFFB8 (symbols.txt) encodes a pointer for the pin
// matrix and no radius; the real parameters are a const-ref temp and the f32
// pin radius (same as RPBow_803433E4), so it is declared by its symbol name.
extern "C" void fn_804CFFB8__7BowlingFPviPQ34nw4r4math5MTX34PQ34nw4r4math5MTX34b(
    void* pArrEntry, int validCount, nw4r::math::MTX34* pResultMtx, const nw4r::math::MTX34& rMtx,
    f32 pinRadius, bool flag);

namespace Bowling {

struct LaneBvhData;

struct PinPhysicsBody {
    u8 pad_0x0[0x4];
    nw4r::math::VEC3 position;  // offset 0x4
    u8 pad_0x10[0x5C - 0x10];
    nw4r::math::VEC3 basisX;    // offset 0x5C
    nw4r::math::VEC3 basisY;    // offset 0x68
    nw4r::math::VEC3 basisZ;    // offset 0x74
    u8 pad_0x80[0x251 - 0x80];
    u8 isActive;                // offset 0x251
};

struct PinManager {
    PinPhysicsBody* pPinBodies[10];  // offset 0x0
};

struct PinStatus {
    // total size: 0x14
    u32 pinBits[4];  // 0x0
    s32 pinCount;    // 0x10
};

struct ThrowContext {
    int throwState;             // offset 0x0
    nw4r::math::MTX34 ballMtx;  // offset 0x4
    u8 pad_0x34[0x108 - 0x34];
};

struct LaneContext {
    virtual void VF_0x00();
    virtual void VF_0x04();
    virtual f32 GetPinRadius();  // vtable +0x10 (Resort) (name as in RPBow_803433E4)

    PinManager* pPinManager;     // offset 0x4
    LaneBvhData* pLaneBvhData;   // offset 0x8
    u8 pad_0xC[0x8];
    u8 pad_0x14[0x4];
    int pinCount;                // offset 0x18 (Resort)
    u8 pad_0x1C[0x2BEC - 0x1C];
    ThrowContext throwContext;   // offset 0x2BEC (Resort)
    u8 pad_0x2CF4[0x2D2C - 0x2CF4];
    float laneXOffset;           // offset 0x2D2C (Resort)
    u8 pad_0x2D30[0x2D94 - 0x2D30];
    int laneStateTarget;         // offset 0x2D94 (Resort)
};

struct SomeUnkManager0 {
    u8 pad_0x0[0x18];
    void* arr[7];  // offset 0x18 (Resort)
};

struct RPBowActiveBall {
    u8 pad_0x0[0x44];
    nw4r::math::MTX34 mtx;  // offset 0x44
    f32 field_0x74;         // offset 0x74
};

struct SceneEntities {
    u8 pad_0x0[0x30];
    RPBowActiveBall* balls[7];  // offset 0x30
};

struct SceneObjectManager {
    void* vtable;            // offset 0x0
    SceneEntities entities;  // offset 0x4
};

struct BowlingPhysicsData {
    u8 pad_0x0[0x118];
    f32 field_118;  // offset 0x118
};

extern BowlingPhysicsData gBowlingPhysicsData;

class RPBowGlobalLaneManager {
public:
    // total size: 0x24
    u8 pad_00[0x04];         // offset 0x0
    LaneContext* pLanes[7];  // offset 0x4
    u8 isInitialized;        // offset 0x20
    u8 field_0x21;           // offset 0x21
    u8 pad_22[0x2];          // offset 0x22

    void InitializeBallManagerLanes();
    void SetupBallManagerLaneObjects(void* arg1, void* arg2);
    void ResetLanePinsAndAnimations();
    void SetLaneUnknownState(int value);
    void UpdateBallsPhysics();
    void TickNpcLanes();
    void UpdateLaneItems(int val, void* obj, SomeUnkManager0* someMgr, bool isPlayerTurn);
    void UpdateBallsMdl(SceneObjectManager* vballmgr);
};

/**
 * @brief Lane X offsets
 * @details X position of each lane (Resort .data 0x806DED78, {0, -16.1, 17.6, -33.75, 33.6,
 * -49.85, 51.15, 0}). Referenced from several units, so it is not owned by this one (it sits in
 * the .data gap before RPBow_80323790); declared extern here.
 */
extern float gLaneXOffsets[8];

// Extern Functions
void ResetPinSetterState(LaneContext* pLane, u8 arg);
void fn_804DD210(LaneContext* pLane, PinStatus* pStatus);
nw4r::math::MTX34* fn_804C81D0(SomeUnkManager0* pSomeMgr, void* pObj, int val);
extern "C" void fn_804CFED0(void* pArrEntry, int validCount);
extern "C" void fn_804DD130(LaneContext* pLane);
void fn_804DD5FC(LaneContext* pLane);
void fn_804E3DFC(LaneBvhData* pBvhData, void* pArg1, void* pArg2);
void fn_804DB074(LaneContext* pLane);

/**
 * @brief Tests whether the ball's X position falls inside the hit-box radius of any lane boundary
 *
 * @param pBallXPos Ball's X position
 * @param radius Hit-box radius
 * @return True if the ball intersects with a lane boundary, false otherwise
 */
bool CheckBallLaneIntersection(float* pBallXPos, float radius) {
    for (int i = 0; i < 7; i++) {
        if (*pBallXPos > gLaneXOffsets[i] - radius && *pBallXPos < radius + gLaneXOffsets[i]) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Initializes the context state and logic for all 7 lanes
 */
void RPBowGlobalLaneManager::InitializeBallManagerLanes() {
    for (int i = 0; i < 7; i++) {
        fn_804DD5FC(pLanes[i]);
    }
}

/**
 * @brief Submits parameters to setup secondary components attached to each lane and flags the manager as initialized
 *
 * @param pArg1 First setup parameter
 * @param pArg2 Second setup parameter
 */
void RPBowGlobalLaneManager::SetupBallManagerLaneObjects(void* pArg1, void* pArg2) {
    for (int i = 0; i < 7; i++) {
        fn_804E3DFC(pLanes[i]->pLaneBvhData, pArg1, pArg2);
    }
}

/**
 * @brief Resets the pin layout mask to a fresh set of 10 standing pins for all 7 lanes
 */
void RPBowGlobalLaneManager::ResetLanePinsAndAnimations() {
    for (int i = 0; i < 7; i++) {
        LaneContext* pLane = pLanes[i];
        PinStatus status;
        status.pinBits[3] = -1;
        status.pinBits[2] = -1;
        status.pinBits[1] = -1;
        status.pinBits[0] = -1;
        status.pinCount = 10;

        fn_804DD210(pLane, &status);
        ResetPinSetterState(pLanes[i], 0);
    }
}

/**
 * @brief Pushes target state updates to all lanes
 *
 * @param value Target state value
 */
void RPBowGlobalLaneManager::SetLaneUnknownState(int value) {
    for (int i = 0; i < 7; i++) {
        pLanes[i]->laneStateTarget = value;
    }
}

/**
 * @brief Ensures lane position offsets are correctly pushed to memory
 * @details Computes ball physics on NPC lanes, and skips computing it on the player lane unless conditions dictate otherwise.
 */
void RPBowGlobalLaneManager::UpdateBallsPhysics() {
    for (int i = 0; i < 7; i++) {
        pLanes[i]->laneXOffset = gLaneXOffsets[i];
        fn_804DD130(pLanes[i]);
    }
}

/**
 * @brief Executes a sub-tick physics/state update on the player lane and all 6 NPC lanes
 */
void RPBowGlobalLaneManager::TickNpcLanes() {
    for (int i = 0; i < 7; i++) {
        fn_804DB074(pLanes[i]);
    }
}

// MATCH-PENDING (R17): these accessors only reproduce the pin-matrix temporary and CSE shape of UpdateLaneItems (99.7 -> 100).
// name inferred from the sibling RPBowNpcManager::GetPinWorldMatrix pattern in bowling.h.
extern "C" int fn_804D952C(PinPhysicsBody* pBody);
extern "C" nw4r::math::MTX34 fn_804D398C(PinPhysicsBody* pBody);

static inline int IsLanePinActive(LaneContext* pLane, int pinIndex) {
    if (pinIndex >= pLane->pinCount) {
        return false;
    }
    return fn_804D952C(pLane->pPinManager->pPinBodies[pinIndex]);
}

static inline nw4r::math::MTX34 GetLanePinWorldMatrix(LaneContext* pLane, int pinIndex) {
    if (pinIndex >= pLane->pinCount) {
        nw4r::math::MTX34 matrix;
        nw4r::math::MTX34Identity(&matrix);
        return matrix;
    } else {
        return fn_804D398C(pLane->pPinManager->pPinBodies[pinIndex]);
    }
}

/**
 * @brief Iterates the 7 lane item arrays to synthesize their 3D world space transforms and registers them back into the game engine's scene
 *
 * @param val Unknown integer value
 * @param pObj Pointer to an object
 * @param pSomeMgr Manager object
 * @param isPlayerTurn Indicates if it is currently the player's turn
 */
void RPBowGlobalLaneManager::UpdateLaneItems(int val, void* pObj, SomeUnkManager0* pSomeMgr, bool isPlayerTurn) {
    nw4r::math::MTX34* pResultMtx = fn_804C81D0(pSomeMgr, pObj, val);

    for (int i = 0; i < 7; i++) {
        void* pArrEntry = pSomeMgr->arr[i];
        int validCount = 0;

        for (int j = 0; j < 10; j++) {
            if (IsLanePinActive(pLanes[i], j)) {
                fn_804CFFB8__7BowlingFPviPQ34nw4r4math5MTX34PQ34nw4r4math5MTX34b(
                    pArrEntry, validCount, pResultMtx, GetLanePinWorldMatrix(pLanes[i], j),
                    pLanes[i]->GetPinRadius(), i == 0 && isPlayerTurn);
                validCount++;
            }
        }
        fn_804CFED0(pArrEntry, validCount);
    }
}

/**
 * @brief Applies physics matrix translations onto the game's ball models
 * @details Also artificially moves the ball out of view bounds (y = 9999.0f) if it falls completely below the floor bounds.
 *
 * @param pBallMgr Scene object manager for balls
 */
void RPBowGlobalLaneManager::UpdateBallsMdl(SceneObjectManager* pBallMgr) {
    for (int i = 0; i < 7; i++) {
        LaneContext* pLane = pLanes[i];
        RPBowActiveBall* pBall = pBallMgr->entities.balls[i];

        nw4r::math::MTX34 mtx = pLane->throwContext.ballMtx;
        if (mtx._23 < -210.0f) {
            mtx._23 = 9999.0f;
        }

        float field_118 = gBowlingPhysicsData.field_118;
        pBall->mtx = mtx;
        pBall->field_0x74 = field_118;
    }
}

} // namespace Bowling
