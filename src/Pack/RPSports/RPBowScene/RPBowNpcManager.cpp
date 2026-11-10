// Resort (RZTE01_01) port of Wii Sports RPBowNpcManager.cpp, RPBow_80330FE8.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// ---- from ogws RPBowNpcManager.cpp ----
#define NW4R_G3D_PLATFORM_GPU_H
#include <Pack/RPSports/RPBowScene/bowling.h>

extern "C" int rand();
extern "C" int sprintf(char* s, const char* format, ...);

extern const f32 lbl_804C618C;
extern const f32 lbl_804C6188;
extern f32 lbl_804BF9A0;
extern u8 lbl_804BF9A4;
extern "C" void fn_80373098(const char* message, f32 x, f32 y, f32 scale, u32 rgba, bool centered);

namespace Bowling {

// Extern functions:
void fn_804D58F0(NpcContext* pContext);
void InitNpcContext(NpcContext* pContext, int laneIdx, int npcIdx);

// States for RPBowNpcManager::Update()
enum NpcBowlingStates {
    NPC_BOWLING_STATE_IDLE = 0,               // Inactive, ball hidden off-screen
    NPC_BOWLING_STATE_WAIT_PREPARE_LINE = 1,  // Walk to approach area, pick up ball
    NPC_BOWLING_STATE_PREPARE = 2,            // Idle at line, RNG delay before bowling
    NPC_BOWLING_STATE_RUN = 3,                // Swing and release ball
    NPC_BOWLING_STATE_SEE = 4,                // Watch ball roll, handle result SFX
    NPC_BOWLING_STATE_BACK = 5,               // Walk to ball return or back to seat
};

// Sound object whose vtable lives at 0x78 (data before the first virtual)
struct BowNpcSndData {
    u8 unk0[0x78];
};

struct BowNpcSnd : BowNpcSndData {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void SetPosition(u8* pPos);  // 0x48
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void PlaySound(u32 id, int arg);  // 0x60
};

void CalculateNpcBallTransform(nw4r::math::MTX34* pOut, const NpcContext* pCtx);
void CalculateNpcThrowVelocity(nw4r::math::VEC3* pOut, const RPBowNpcManager* pManager,
                               nw4r::math::VEC3* pPos, const PinStatus* pPins);
void UpdateNpcLane(u8* pOut, const NpcContext* pCtx);
int IsPinSetterActive(LaneContext* pLane);
void ResetPinSetterState(LaneContext* pLane, u8 isNewRack);
void fn_804DA72C(PinStatus* pOut, LaneContext* pLane);
int fn_804DA820(LaneContext* pLane);
void fn_804DD210(LaneContext* pLane, PinStatus* pStatus);
extern "C" void fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(LaneContext* pLane, nw4r::math::VEC3* pVel, u8 arg);
extern "C" u8 lbl_804BF998;
// MATCH-PENDING (R17): by-value view of fn_804DA72C (same symbol, hidden struct-return pointer in r3).
// Update's BACK state needs compiler temporaries for the two pin-count checks (frame slots 0x78/0x64 and
// the &temp pointer coloured as an IRO value); the real source probably declares one by-value getter
// (or a wrapper) and the pointer-out calls above are the inconsistent spelling.
extern "C" PinStatus fn_804DA72C__7BowlingFPQ27Bowling9PinStatusPQ27Bowling11LaneContext(LaneContext* pLane);

// Starts a fresh rack: all ten pins standing
// MATCH-PENDING (R17): invented inline helper; its local is added to Update's frame only at
// deferred-inline time (below the by-value fn_804DA72C temporaries), as in the target frame layout.
static inline void SetFullRack(LaneContext* pLane) {
    PinStatus pins;
    pins.pinBits[3] = -1;
    pins.pinBits[2] = -1;
    pins.pinBits[1] = -1;
    pins.pinBits[0] = -1;
    pins.pinCount = 10;
    fn_804DD210(pLane, &pins);
}

// True when the standing pins left over form a split
static inline bool IsSplitLeave(const PinStatus* pPins) {
    if (lbl_804BF998) {
        return true;
    }
    if (pPins->pinBits[0] & 1) {
        return false;
    }
    const int pinRows[10] = {3, 2, 4, 1, 3, 5, 0, 2, 4, 6};
    int mask = 0;
    for (int i = 0; i < pPins->pinCount; i++) {
        if (pPins->pinBits[i / 30] & (1 << (i % 30))) {
            mask |= 1 << pinRows[i];
        }
    }
    for (int i = 0; i < 5; i++) {
        if ((mask & (1 << i)) && !(mask & (1 << (i + 1)))) {
            for (int j = i + 2; j < 7; j++) {
                if (mask & (1 << j)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Sound object with extra words after the base RPSndObject. Real class, kept as a comment: the
// hand-built constructor below needs local views of TRPSndAudioHandles<8> /
// TRPSndAudioActorBaseWithHandles<4,4>, which cannot coexist with an instantiated RPSndObject.
// class RPBowNpcSndObject : public RPSndObject {
// public:
//     RPBowNpcSndObject(nw4r::snd::SoundArchivePlayer& rPlayer, nw4r::snd::Sound3DManager& rManager)
//         : RPSndObject(rPlayer, rManager) {
//         field_0x84 = 0;
//         field_0x88 = 0;
//         field_0x8C = 0;
//         lbl_804BF9A0 = lbl_804C6188;
//         lbl_804BF9A4 = false;
//     }
//
//     int field_0x84;
//     int field_0x88;
//     int field_0x8C;
// };

/**
 * @brief Initializes audio-related structures for the manager
 * @details Allocates memory for sound actors and configures 3D audio settings.
 *
 * @param laneIdx Index of the lane
 */
// void RPBowNpcManager::InitAudioActors(int laneIdx) {
//     ;
// }

/**
 * @brief Configures internal pointers and prepares initial contexts
 *
 * @param pLaneContext Pointer to the lane physics and gameplay context
 * @param pNpc0 Pointer to the first NPC object
 * @param pNpc1 Pointer to the second NPC object
 * @param pNpc2 Pointer to the third NPC object
 * @param laneIdx Lane index
 * @param pReturnRack Rack containing usable balls
 * @param pAudioStruct Pointer to the audio structure
 */
}  // namespace Bowling

// MATCH-PENDING (R17): the RPBowNpcSndObject constructor chain (TRPSndAudio3DActor<4> ->
// TRPSndAudioActorBaseWithHandles<4,4> + TRPSndAudioHandles<8>) is written out by hand, as in
// RPBow_80329658/80320EFC/8031EFE4. The real inlined template constructors reference their weak
// vtables/assert strings by mangled name; the retail copies kept by the linker live in
// RPTns_8021ba24's .data. The vtables now carry their mangled names (__vt__36...<4,4>,
// __vt__21TRPSndAudioHandles<8>, named below through local views), but the assert strings are
// still lbl_803C4080/4098 (their @STRING@__ct__21TRPSndAudio3DActor<4>... names cannot be written in
// C++), and the real `new RPBowNpcSndObject(...)` would also emit the template's weak functions here.
extern "C" {
void* __nw__FUl(unsigned long);
void* __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(
    void*, void*, void*);
void __ct__Q23EGG8DisposerFv(void*);
void __ct__17RPSndMoveValueF32Fv(void*);
void List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(void*, void*);
void __construct_array(void*, void*, void*, unsigned long, unsigned long);
void __ct__Q34nw4r3snd11SoundHandleFv();
void __dt__Q34nw4r3snd11SoundHandleFv();
extern u8 __vt__19RPSndAudioActorBase[];
extern u8 sActorList__19RPSndAudioActorBase[];
extern u8 __vt__Q27Bowling17RPBowNpcSndObject[];
extern char lbl_803C4098[];
extern char lbl_803C4080[];
}

// Retail weak template vtables (kept once, in RPTns_8021ba24 .data). Empty local views so the
// hand-built constructor code can name the compiler's vtable symbols: the static member __vt of
// TRPSndAudioHandles<8> mangles to __vt__21TRPSndAudioHandles<8> (likewise for <4,4>).
template <int N> class TRPSndAudioHandles;
template <> class TRPSndAudioHandles<8> {
public:
    static u8 __vt[];
};
template <int N1, int N2> class TRPSndAudioActorBaseWithHandles;
template <> class TRPSndAudioActorBaseWithHandles<4, 4> {
public:
    static u8 __vt[];
};

// Derived only to reach the protected smCommon3DManager table, like the real
// TRPSndAudio3DActor<4> constructor does.
struct BowNpcSndBuilder : public EGG::AudioSoundActorBaseWithCamera<4> {
static void* Ct(u8* a, void* player) {
    u8* b;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (!smCommon3DManager[i])
            system_halt(lbl_803C4098, 375, lbl_803C4080);
        void* s3 = __nw__FUl(0xC4);
        if (s3)
            s3 = __ct__Q34nw4r3snd12Sound3DActorFRQ34nw4r3snd18SoundArchivePlayerRQ34nw4r3snd14Sound3DManager(
                s3, player, smCommon3DManager[i]);
        ((void**)a)[i] = s3;
    }
    b = a + 0x10;
    __ct__Q23EGG8DisposerFv(b);
    *(void**)b = __vt__19RPSndAudioActorBase;
    __ct__17RPSndMoveValueF32Fv(b + 0x20);
    b[0x10] = 0;
    *(s32*)(b + 0x14) = 0;
    List_Append__Q24nw4r2utFPQ34nw4r2ut4ListPv(sActorList__19RPSndAudioActorBase, b);
    *(void**)(b + 0x3C) = TRPSndAudioHandles<8>::__vt;
    __construct_array(b + 0x48, (void*)__ct__Q34nw4r3snd11SoundHandleFv,
                      (void*)__dt__Q34nw4r3snd11SoundHandleFv, 4, 8);
    *(s32*)(b + 0x40) = 8;
    *(s32*)(b + 0x44) = 8;
    *(void**)b = TRPSndAudioActorBaseWithHandles<4, 4>::__vt;
    *(void**)(b + 0x3C) = TRPSndAudioActorBaseWithHandles<4, 4>::__vt + 0x24;
    a[0x7C] = 0;
    *(s32*)(a + 0x80) = 0xF;
    *(void**)(a + 0x78) = __vt__Q27Bowling17RPBowNpcSndObject;
    *(void**)(a + 0x10) = __vt__Q27Bowling17RPBowNpcSndObject + 8;
    *(void**)(a + 0x4C) = __vt__Q27Bowling17RPBowNpcSndObject + 0x2C;
    *(s32*)(a + 0x84) = 0;
    *(s32*)(a + 0x88) = 0;
    *(s32*)(a + 0x8C) = 0;
    lbl_804BF9A0 = lbl_804C6188;
    lbl_804BF9A4 = 0;
    return a;
}
};

static inline void* BowNewNpcSnd() {
    u8* a = (u8*)__nw__FUl(0x90);
    if (a) a = (u8*)BowNpcSndBuilder::Ct(a, &RPSndAudioMgr::instance()->getPlayer());
    return a;
}

namespace Bowling {

extern "C" void* fn_802BA8D8(void* pObj, void* pHeap, int align);
extern "C" void fn_804D39F0(RPBowNpcManager* pThis, int state);
extern "C" void* sCurrentHeap__Q23EGG4Heap;  // EGG::Heap::sCurrentHeap (private)

void RPBowNpcManager::InitAudioActors(int laneIdx) {
    (void)laneIdx;
    void* pSnd = __nw__FUl(0xD4);
    if (pSnd) {
        pSnd = fn_802BA8D8(pSnd, sCurrentHeap__Q23EGG4Heap, 8);
    }
    mpSoundAudioMgr = pSnd;
}

void RPBowNpcManager::Setup(LaneContext* pLaneContext, NpcContext* pNpc0, NpcContext* pNpc1, NpcContext* pNpc2, int laneIdx, RPBowBallReturnRack* pReturnRack, void* pAudioStruct) {
    mpNpcs[0] = pNpc0;
    mpNpcs[1] = pNpc1;
    mpNpcs[2] = pNpc2;

    mpLaneContext = pLaneContext;
    mLaneIdx = laneIdx;
    mpReturnRack = pReturnRack;
    mpSomeAudioStruct = pAudioStruct;

    memset(&mStateId, 0, 12);

    for (int i = 0; i < 3; i++) {
        fn_804D58F0(mpNpcs[i]);
        InitNpcContext(mpNpcs[i], mLaneIdx, i);
    }

    mpCurrentNpc = mpNpcs[0];
    mCurrentNpcIdx = 0;
}

/**
 * @brief Tests whether the lane is idle
 *
 * @return 1 if idle, 0 otherwise
 */
int RPBowNpcManager::IsLaneIdle() {
    return mStateId == 0;
}

/**
 * @brief Sets the NPC state flag
 *
 * @param flag Status value applied
 */
void RPBowNpcManager::SetStateFlag(u8 flag) {
    mDisableResultSfx = flag;
}

/**
 * @brief Activates a new NPC turn for the lane
 * @details Cycles to the next NPC in the lane (0->1->2->0).
 */
extern "C" int IsBallOnRack__Q27Bowling19RPBowBallReturnRackFl(RPBowBallReturnRack*, s32);
void RPBowNpcManager::ActivateNpcTurn() {
    memset(&mStateId, 0, 12);
    fn_804D39F0(this, 1);
    mpLaneContext->throwContext.throwState = 0;

    mpCurrentNpc = mpNpcs[mCurrentNpcIdx];

    int nextIdx = mCurrentNpcIdx; // TODO: remove?
    mCurrentNpcIdx = mCurrentNpcIdx + 1;
    if (mCurrentNpcIdx == 3) {
        mCurrentNpcIdx = 0;
    }
}

void RPBowNpcManager::Update() {
    nw4r::math::MTX34 idleMtx;
    nw4r::math::MTX34 ballMtx;
    nw4r::math::MTX34 mtxC;
    nw4r::math::MTX34 mtxB;
    nw4r::math::MTX34 mtxA;
    PinStatus throwAllOnes;
    PinStatus after;
    PinStatus secondInit;
    PinStatus latest;

    if (mStateTimer < 0) {
        mStateTimer = 0;
    }

    switch (mStateId) {
    case NPC_BOWLING_STATE_IDLE: {
        idleMtx._23 = 9999.0f;
        mpLaneContext->throwContext.ballMtx = idleMtx;
        mActiveSubObjIdx = -1;
        break;
    }
    case NPC_BOWLING_STATE_WAIT_PREPARE_LINE:
        if (mActiveSubObjIdx < 0) {
            mActiveSubObjIdx = mpReturnRack->SelectBallForNPC();
        }
        if (mActiveSubObjIdx >= 0) {
            mpCurrentNpc->targetZPos = mpReturnRack->mBalls[mActiveSubObjIdx].mPos.z +
                                       gBallReturnRackConstants.mPositionOffsets[mpReturnRack->mRackIndex].z;
        } else {
            mpCurrentNpc->targetZPos = -999.0f;
        }
        if (mStateTimer == 0) {
            NpcContext* npc = mpCurrentNpc;
            npc->npcState = NPC_STATE_WALK_TO_APPROACH_AREA;
            npc->stateFrameCounter = -1;
            npc->triggerTransition = 0;
        }
        if (mpCurrentNpc->triggerTransition) {
            mStateId = NPC_BOWLING_STATE_PREPARE;
            mStateTimer = -1;
        }
        if (mpCurrentNpc->isHoldingBall) {
            mpLaneContext->throwContext.throwState = 0;
            *(s32*)((u8*)mpSomeAudioStruct + 0x78) = mpReturnRack->GetBallSlotIndex(mActiveSubObjIdx);
            if (IsBallOnRack__Q27Bowling19RPBowBallReturnRackFl(mpReturnRack, mActiveSubObjIdx)) {
                mpReturnRack->RemoveBallFromRack(mActiveSubObjIdx);
            }
        }
        mHasReleasedBall = false;
        break;
    case NPC_BOWLING_STATE_PREPARE:
        if (rand() % 100 == 0 && mStateTimer > 0x50 && !IsPinSetterActive(mpLaneContext)) {
            mStateId = NPC_BOWLING_STATE_RUN;
            mStateTimer = -1;
        }
        break;
    case NPC_BOWLING_STATE_RUN: {
        if (mStateTimer == 0) {
            NpcContext* npc = mpCurrentNpc;
            npc->npcState = NPC_STATE_BOWL;
            npc->stateFrameCounter = -1;
            npc->triggerTransition = 0;
            ResetPinSetterState(mpLaneContext, mIsSecondThrow);
            mHasPlayedGutterSfx = false;
            if (mIsSecondThrow) {
                fn_804DA72C(&secondInit, mpLaneContext);
                fn_804DD210(mpLaneContext, &secondInit);
            } else {
                SetFullRack(mpLaneContext);
            }
        }
        u8 throwNow = mpCurrentNpc->triggerThrow;
        mpCurrentNpc->triggerThrow = 0;
        if (throwNow) {
            f32 y;
            f32 z;
            CalculateNpcBallTransform(&mtxA, mpCurrentNpc);
            z = mtxA._23;
            CalculateNpcBallTransform(&mtxB, mpCurrentNpc);
            y = mtxB._13;
            CalculateNpcBallTransform(&mtxC, mpCurrentNpc);
            nw4r::math::VEC3 pos(mtxC._03, y, z);
            nw4r::math::VEC3 throwVel;
            if (mIsSecondThrow) {
                nw4r::math::VEC3 vel;
                CalculateNpcThrowVelocity(&vel, this, &pos, &mPinStatus);
                throwVel = vel;
            } else {
                throwAllOnes.pinBits[3] = -1;
                throwAllOnes.pinBits[2] = -1;
                throwAllOnes.pinBits[1] = -1;
                throwAllOnes.pinBits[0] = -1;
                throwAllOnes.pinCount = 10;
                nw4r::math::VEC3 vel;
                CalculateNpcThrowVelocity(&vel, this, &pos, &throwAllOnes);
                throwVel = vel;
            }
            nw4r::math::VEC3 dir = throwVel;
            fn_804DAD34__7BowlingFPQ27Bowling11LaneContextPQ34nw4r4math4VEC3(mpLaneContext, &dir, 0);
            mHasReleasedBall = true;
        }
        if (mpCurrentNpc->triggerTransition) {
            mStateId = NPC_BOWLING_STATE_SEE;
            mStateTimer = -1;
        }
        break;
    }
    case NPC_BOWLING_STATE_SEE:
        if (!mHasPlayedGutterSfx && mpLaneContext->throwContext.isGutterBall && !mDisableResultSfx) {
            ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x34, 0);
            mHasPlayedGutterSfx = true;
        }
        if (fn_804DA820(mpLaneContext)) {
            mpReturnRack->SpawnBallOnRack(mActiveSubObjIdx);
            mActiveSubObjIdx = -1;
            mStateId = NPC_BOWLING_STATE_BACK;
            mStateTimer = -1;
            fn_804DA72C(&after, mpLaneContext);
            if (!mDisableResultSfx) {
                if (!mIsSecondThrow) {
                    if (after.GetStandingPinCount() == 0) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x2F, 0);
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x50, 0);
                    } else if (after.GetStandingPinCount() <= 3) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x31, 0);
                    } else if (after.GetStandingPinCount() <= 9) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x32, 0);
                    }
                } else if (after.GetStandingPinCount() == 0) {
                    if (IsSplitLeave(&mPinStatus)) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x33, 0);
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x52, 0);
                    } else {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x30, 0);
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x51, 0);
                    }
                } else {
                    int nowCount = after.GetStandingPinCount();
                    int prevCount = mPinStatus.GetStandingPinCount();
                    if (nowCount != prevCount) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x36, 0);
                    } else if (!mHasPlayedGutterSfx) {
                        ((BowNpcSnd*)mpSoundAudioMgr)->PlaySound(0x35, 0);
                    }
                }
            }
            fn_804DA72C(&latest, mpLaneContext);
            mPinStatus = latest;
        }
        break;
    case NPC_BOWLING_STATE_BACK:
        if (mStateTimer == 0) {
            if (mIsSecondThrow || fn_804DA72C__7BowlingFPQ27Bowling9PinStatusPQ27Bowling11LaneContext(mpLaneContext).GetStandingPinCount() == 0) {
                mShouldReturnToSeat = true;
            } else {
                mShouldReturnToSeat = false;
            }
        }
        if (mStateTimer == 0) {
            if (mShouldReturnToSeat) {
                if (fn_804DA72C__7BowlingFPQ27Bowling9PinStatusPQ27Bowling11LaneContext(mpLaneContext).GetStandingPinCount() == 0) {
                    mpCurrentNpc->flag_A5 = 1;
                } else {
                    mpCurrentNpc->flag_A5 = 0;
                }
                NpcContext* npc = mpCurrentNpc;
                npc->npcState = NPC_STATE_WALK_BACK_TO_SEAT;
                npc->stateFrameCounter = -1;
                npc->triggerTransition = 0;
            } else {
                NpcContext* npc = mpCurrentNpc;
                npc->npcState = NPC_STATE_WALK_TO_BALL_RETURN;
                npc->stateFrameCounter = -1;
                npc->triggerTransition = 0;
            }
        }
        if (!mShouldReturnToSeat) {
            if (mActiveSubObjIdx < 0) {
                mActiveSubObjIdx = mpReturnRack->SelectBallForNPC();
            }
            if (mActiveSubObjIdx >= 0) {
                mpCurrentNpc->targetZPos = mpReturnRack->mBalls[mActiveSubObjIdx].mPos.z +
                                           gBallReturnRackConstants.mPositionOffsets[mpReturnRack->mRackIndex].z;
            } else {
                mpCurrentNpc->targetZPos = -999.0f;
            }
        }
        if (!mShouldReturnToSeat && mpCurrentNpc->isHoldingBall) {
            mpLaneContext->throwContext.throwState = 0;
            *(s32*)((u8*)mpSomeAudioStruct + 0x78) = mpReturnRack->GetBallSlotIndex(mActiveSubObjIdx);
            if (IsBallOnRack__Q27Bowling19RPBowBallReturnRackFl(mpReturnRack, mActiveSubObjIdx)) {
                mpReturnRack->RemoveBallFromRack(mActiveSubObjIdx);
            }
        }
        if (mpCurrentNpc->triggerTransition) {
            if (mShouldReturnToSeat) {
                if (mActiveSubObjIdx >= 0) {
                    mpReturnRack->ReleaseBallFromNPC(mActiveSubObjIdx);
                    mActiveSubObjIdx = -1;
                }
                mStateId = NPC_BOWLING_STATE_IDLE;
                mStateTimer = -1;
            } else {
                mIsSecondThrow = true;
                mStateId = NPC_BOWLING_STATE_PREPARE;
                mStateTimer = -1;
            }
            mpLaneContext->throwContext.throwState = 0;
        }
        break;
    }

    u8 laneBuf[12];
    mStateTimer++;
    UpdateNpcLane(laneBuf, mpCurrentNpc);
    ((BowNpcSnd*)mpSoundAudioMgr)->SetPosition(laneBuf);
    if (mpCurrentNpc->isHoldingBall) {
        CalculateNpcBallTransform(&ballMtx, mpCurrentNpc);
        mpLaneContext->throwContext.ballMtx = ballMtx;
    }
}

void RPBowNpcManager::DebugPrintNpcState() {
    const char* stateNames[6] = {"IDLE", "WAIT_PREPARE_LINE", "PREPARE", "RUN", "SEE", "BACK"};
    char buf[256];
    int x = 400;
    int y = mLaneIdx * 20 + 100;
    int phy = mpLaneContext->throwContext.throwState;

    sprintf(buf, "NPC[%d(%s)] %s  phy:%d", mLaneIdx, mIsSecondThrow ? "2nd" : "1st",
            stateNames[mStateId], phy);

    fn_80373098(buf, x, y, lbl_804C618C, -1, true);
}


/**
 * @brief Updates the manager's state machine
 */
// void RPBowNpcManager::Update() {
//     ;
// }

/**
 * @brief Prints debug information for this NPC manager
 * @details Example string formats: 'NPC[0(1st)] PREPARE phy:0'
 */
// void RPBowNpcManager::DebugPrintNpcState() {
//     ;
// }

// Small helpers kept out of line in the retail TU (descending address order: emitted in reverse).
// MATCH-PENDING (R17): ledger #8. retail keeps this state setter out of line; dont_inline stops the deferred inliner
// from folding it into ActivateNpcTurn (needs a docs/marker-ledger.md row).
#pragma dont_inline on
extern "C" void fn_804D39F0(RPBowNpcManager* pThis, int state) {
    pThis->mStateId = state;
    pThis->mStateTimer = -1;
}
#pragma dont_inline reset

extern "C" nw4r::math::MTX34 fn_804D398C(PinPhysicsBody* pBody) {
    return nw4r::math::MTX34(
        pBody->basisX.x, pBody->basisY.x, pBody->basisZ.x, pBody->position.x,
        pBody->basisX.y, pBody->basisY.y, pBody->basisZ.y, pBody->position.y,
        pBody->basisX.z, pBody->basisY.z, pBody->basisZ.z, pBody->position.z);
}

extern "C" bool fn_804D395C(const u32* pBits, int index) {
    return (pBits[index / 30] & (1 << (index % 30))) != 0;
}

extern "C" u32 fn_804D3954(const u32* pObj) {
    return pObj[4];
}

} // namespace Bowling

// ---- from ogws RPBow_80330FE8.cpp ----
#include <Pack/RPUtility/RPUtlRandom.h>
#include <nw4r/math.h>

extern const f32 lbl_804C6188;
extern const f32 lbl_804C618C;

namespace Bowling {

// Resort: CalculateNpcThrowVelocity shares this TU with RPBowNpcManager (one .sdata2 pool,
// called from RPBowNpcManager::Update); the types come from bowling.h.

void CalculateNpcThrowVelocity(nw4r::math::VEC3* pOut,
                               const RPBowNpcManager* pManager,
                               nw4r::math::VEC3* pPos,  // non-const: matches (inlined VEC3Sub keeps this load after the dir store); symbol renamed accordingly
                               const PinStatus* pPins) {
    int target = 0;
    for (int i = 9; i >= 0; i--) {
        if (pPins->pinBits[i / 30] & (1 << (i % 30))) {
            target = i;
        }
    }

    nw4r::math::VEC3 pinPos(pManager->GetPinWorldMatrix(target)._03,
                            pManager->GetPinWorldMatrix(target)._13,
                            pManager->GetPinWorldMatrix(target)._23);

    nw4r::math::VEC3 dir;
    nw4r::math::VEC3Sub(&dir, &pinPos, pPos);
    dir.y = lbl_804C6188;
    nw4r::math::VEC3Normalize(&dir, &dir);

    nw4r::math::VEC3 up(lbl_804C6188, lbl_804C618C, lbl_804C6188);
    nw4r::math::VEC3 side;
    nw4r::math::VEC3Cross(&side, &dir, &up);

    nw4r::math::MTX34 mtx(side.x, up.x, dir.x, lbl_804C6188,
                          side.y, up.y, dir.y, lbl_804C6188,
                          side.z, up.z, dir.z, lbl_804C6188);

    f32 spread = 0.05f;
    if (pPins->GetStandingPinCount() == 10) {
        spread = 0.06f;
    }
    if (pPins->GetStandingPinCount() == 1) {
        spread = 0.08f;
    }

    nw4r::math::VEC3 vel;
    vel.z = 3.0f * RPUtlRandom::getF32() + 5.029318f;
    vel.y = 0.5f * RPUtlRandom::getF32() + 1.130258f;
    vel.x = spread * (2.0f * RPUtlRandom::getF32() - lbl_804C618C);

    nw4r::math::VEC3TransformNormal(pOut, &mtx, &vel);
}

}  // namespace Bowling

extern const f32 lbl_804C6188 = 0.0f;
extern const f32 lbl_804C618C = 1.0f;
