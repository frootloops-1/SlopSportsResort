// Resort (RZTE01_01) port of Wii Sports RPBow_8034C95C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/types_pack.h>
#include <string.h>

#include <Pack/RPUtility/RPUtlRandom.h>

// Inferred (name invented): tuning constants for the background NPC idle state
struct NpcIdleConfig {
    // total size: 0x48
    s32 turnChanceDenom;      // offset 0x0
    f32 turnRange;            // offset 0x4
    f32 turnSpeed;            // offset 0x8
    s32 walkChanceDenom;      // offset 0xC
    s32 seatChanceDenom;      // offset 0x10
    s32 bounceMin;            // offset 0x14
    s32 bounceRange;          // offset 0x18
    f32 bounceGravity;        // offset 0x1C
    f32 bounceVelocity;       // offset 0x20
    s32 lookChanceDenom;      // offset 0x24
    f32 lookRange;            // offset 0x28
    f32 lookSpeed;            // offset 0x2C
    s32 lookDurationRange;    // offset 0x30
    f32 swingGravity;         // offset 0x34
    f32 swingScale;           // offset 0x38
    f32 swingStep;            // offset 0x3C
    f32 swingSpeed;           // offset 0x40
};

extern "C" {
extern NpcIdleConfig lbl_807D39D4;
s32 lbl_806F5970;
extern s32 lbl_806F5974;
extern s32 lbl_806F5978;
extern f32 lbl_807D39C8[3];
void fn_80380F24(void*);
double sin(double);
}

struct NpcVec3 {
    f32 x, y, z;
    NpcVec3(f32 fx, f32 fy, f32 fz) : x(fx), y(fy), z(fz) {}
};

namespace Bowling {

// Inferred (name invented): helper object owned by NpcIdleState (size 0x1C)
struct NpcHelper {
    u8 pad_0x0[0x4];
    f32 f04;        // offset 0x4
    f32 f08;        // offset 0x8
    f32 f0C;        // offset 0xC
    f32 f10;        // offset 0x10
    s32 i14;        // offset 0x14
    void SetVec(const f32* pVec) {
        f08 = pVec[0];
        f0C = pVec[1];
        f10 = pVec[2];
    }
    bool b18;       // offset 0x18
    u8 pad_0x19[3];
};

struct NpcIdleState {
    // total size: 0x48
    void* vptr;       // offset 0x0
    s32 unk_0x04;     // offset 0x4
    s32 unk_0x08;     // offset 0x8
    s32 state;        // offset 0xC
    s32 frame;        // offset 0x10
    s32 unk_0x14;     // offset 0x14
    f32 rotation;     // offset 0x18
    f32 rotationSpeed;  // offset 0x1C
    f32 pad_0x20;     // offset 0x20
    f32 posY;         // offset 0x24
    f32 pad_0x28;     // offset 0x28
    s32 bounces;      // offset 0x2C
    f32 bounceVel;    // offset 0x30
    s32 countdown;    // offset 0x34
    u8 flag38;        // offset 0x38
    u8 pad_0x39[3];
    f32 swingVel;     // offset 0x3C
    f32 swingT;       // offset 0x40
    u8 flag44;        // offset 0x44
    u8 pad_0x45[3];
    f32 timer;                  // offset 0x48
    NpcHelper* pHelper;         // offset 0x4C
};

void fn_804D338C(NpcIdleState* pState, int param_2, int param_3);
void* fn_804D2CBC(NpcIdleState* pState);

}  // namespace Bowling

using Bowling::NpcHelper;

extern "C" {

void fn_804D3574() {}

void __ct__18IRPSysHostIOSocketFv(void*);
NpcHelper* fn_80380F5C(NpcHelper*);
extern void* lbl_806DEBD8[];

Bowling::NpcIdleState* fn_804D3520(Bowling::NpcIdleState* pThis) {
    __ct__18IRPSysHostIOSocketFv(pThis);
    pThis->vptr = lbl_806DEBD8;
    NpcHelper* pHelper = (NpcHelper*)operator new(0x1C);
    if (pHelper) {
        pHelper = fn_80380F5C(pHelper);
    }
    pThis->pHelper = pHelper;
    return pThis;
}

void fn_804D3490() {
    NpcIdleConfig* pCfg = &lbl_807D39D4;
    pCfg->turnChanceDenom = 120;
    pCfg->turnRange = 100.0f;
    pCfg->turnSpeed = 0.01f;
    pCfg->walkChanceDenom = 1300;
    pCfg->seatChanceDenom = 500;
    pCfg->bounceMin = 2;
    pCfg->bounceRange = 5;
    pCfg->bounceGravity = -0.04f;
    pCfg->bounceVelocity = 0.3f;
    pCfg->lookChanceDenom = 30;
    pCfg->lookRange = 100.0f;
    pCfg->lookSpeed = 0.1f;
    pCfg->lookDurationRange = 300;
    pCfg->swingGravity = -0.06f;
    pCfg->swingScale = 0.8f;
    pCfg->swingStep = 0.04f;
    pCfg->swingSpeed = 1.0f;
}

}  // extern "C"

namespace Bowling {

void fn_804D338C(NpcIdleState* pState, int param_2, int param_3) {
    pState->unk_0x04 = param_2;
    pState->unk_0x08 = param_3;
    memset(&pState->state, 0, 0x40);

    pState->rotation = 180.0f + 80.0f * RPUtlRandom::getF32() - 40.0f;
    pState->rotationSpeed = 0.01f;
    pState->state = 0;
    pState->frame = -1;

    NpcVec3 zero(0.0f, 0.0f, 0.0f);
    lbl_806F5974 = 0;
    lbl_806F5978 = 0;
    lbl_806F5970 = 0;
    lbl_807D39C8[0] = zero.x;
    lbl_807D39C8[1] = zero.y;
    lbl_807D39C8[2] = zero.z;
    fn_80380F24(pState->pHelper);
    pState->pHelper->i14 = 1;
}

void* fn_804D2CBC(NpcIdleState* pState) {
    NpcIdleConfig* pCfg = &lbl_807D39D4;
    s32 event = 0;

    if (pState->unk_0x14 != lbl_806F5978) {
        event = lbl_806F5974;
        pState->unk_0x14 = lbl_806F5978;
    }

    if (pState->frame < 0) {
        pState->frame = 0;
    }

    switch (pState->state) {
    case 0:
        pState->timer = 0.0f;
        if (RPUtlRandom::getU32(pCfg->turnChanceDenom) == 0) {
            pState->rotation = 180.0f + pCfg->turnRange * RPUtlRandom::getF32() - 0.5f * pCfg->turnRange;
        }
        pState->rotationSpeed = pCfg->turnSpeed;
        if (RPUtlRandom::getU32(pCfg->walkChanceDenom) == 0) {
            pState->state = 1;
            pState->frame = -1;
        }
        if (RPUtlRandom::getU32(pCfg->seatChanceDenom) == 0 || pState->flag38 != 0) {
            pState->flag38 = 0;
            pState->state = 2;
            pState->frame = -1;
        }
        if (event == 1) {
            pState->state = 3;
            pState->frame = -1;
        }
        break;
    case 1:
        if (pState->frame == 0) {
            pState->bounces = pCfg->bounceMin + RPUtlRandom::getU32(pCfg->bounceRange);
            pState->bounceVel = pCfg->bounceVelocity;
        }
        pState->bounceVel += pCfg->bounceGravity;
        pState->posY += pState->bounceVel;
        if (pState->posY < 0.0f) {
            pState->posY = 0.0f;
            if (--pState->bounces <= 0) {
                pState->state = 0;
                pState->frame = -1;
            }
            pState->bounceVel = pCfg->bounceVelocity;
        }
        if (event == 1) {
            pState->state = 3;
            pState->frame = -1;
        }
        break;
    case 2:
        if (pState->frame == 0) {
            pState->countdown = RPUtlRandom::getU32(pCfg->lookDurationRange);
        }
        if (RPUtlRandom::getU32(pCfg->lookChanceDenom) == 0) {
            pState->rotation = 180.0f + pCfg->lookRange * RPUtlRandom::getF32() - 0.5f * pCfg->lookRange;
        }
        pState->rotationSpeed = pCfg->lookSpeed;
        if (--pState->countdown < 0) {
            pState->state = 0;
            pState->frame = -1;
        }
        if (event == 1) {
            pState->state = 3;
            pState->frame = -1;
        }
        break;
    case 3:
        if (pState->frame == 0) {
            pState->swingVel = pCfg->swingScale + 0.2f * (pCfg->swingScale * RPUtlRandom::getF32());
            pState->swingT = 0.0f;
            if (RPUtlRandom::getU32(2) == 0) {
                pState->flag44 = 1;
            } else {
                pState->flag44 = 0;
            }
        }
        pState->swingT += pCfg->swingStep;
        if (pState->swingT > 1.0f) {
            pState->swingT = 1.0f;
        }
        {
        f32 swing = (f32)sin(0.5f * (3.14159f * pState->swingT));
        pState->rotation = 180.0f + 2.0f * (360.0f * swing);
        }
        if (pState->swingT > 0.99f) {
            pState->rotation = 180.0f;
        }
        if (pState->flag44 != 0) {
            pState->rotation = 360.0f - pState->rotation;
        }
        pState->rotationSpeed = pCfg->swingSpeed;
        pState->swingVel += pCfg->swingGravity;
        pState->posY += pState->swingVel;
        if (pState->posY < 0.0f) {
            pState->posY = 0.0f;
            pState->state = 4;
            pState->frame = -1;
            lbl_806F5970 = 0;
        }
        break;
    case 4:
        if (pState->frame > 130) {
            pState->timer -= 0.05f;
            if (pState->timer < 0.0f) {
                pState->timer = 0.0f;
                pState->state = 0;
                pState->frame = -1;
            }
        } else {
            pState->timer += 1.0f / 15.0f;
            if (pState->timer > 1.0f) {
                pState->timer = 1.0f;
            }
        }
        if (event == 2) {
            pState->state = 0;
            pState->frame = -1;
            pState->timer = 0.0f;
        }
        break;
    }

    pState->frame++;
    pState->pHelper->f04 = pState->timer;
    pState->pHelper->SetVec(lbl_807D39C8);
    return &pState->state;
}

}  // namespace Bowling

extern "C" {

void fn_804D2B2C(Bowling::NpcIdleState* pThis) {
    pThis->timer -= 1.0f / 60.0f;
    if (pThis->timer < 0.0f) {
        pThis->timer = 0.0f;
    }
    pThis->pHelper->f04 = pThis->timer;
}

void fn_804D2B18(Bowling::NpcIdleState* pThis, s32 arg) {
    pThis->pHelper->b18 = (arg == 0);
}

NpcHelper* fn_804D2B10(Bowling::NpcIdleState* pThis) {
    return pThis->pHelper;
}

}  // extern "C"
