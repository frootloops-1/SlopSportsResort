// Resort Basketball (bsk) file 0x8051B8B4-0x8051C92C (was unk/sinit_8051B8B4.cpp): class vtable
// 0x806E0ED0 (Bsk::Unk_806E0ED0). The real file, class and member names are unknown: every Unk_* type
// and mUnk* member below is a placeholder named after its address or offset.
#include <nw4r/math.h>

using nw4r::math::VEC3;

// 12-byte vector in .bss, referenced from 500+ places (possibly a shared zero vector; unconfirmed)
extern const VEC3 lbl_807D1558;

// Unnamed functions in other units (signatures inferred from their call sites/bodies)
extern "C" {
void* fn_80504C60();             // returns a global instance pointer
void* fn_8050456C(void* pObj);   // returns pObj+0x88
BOOL fn_8050F354(void* pObj);
BOOL fn_8050C6C4(void* pObj, void* pArg, const VEC3* pA, const VEC3* pB, const VEC3* pC, BOOL flag, f32 f);
f32 fn_803569FC(const f32& rX, const f32& rLo, const f32& rHi, const f32& rOutLo, const f32& rOutHi);
void fn_80356940(VEC3* pVec);
void fn_8021D094(VEC3* pOut, const VEC3* pIn, f32 scale);
void fn_80356330(nw4r::math::MTX34* pOut, const nw4r::math::MTX34* pA, const nw4r::math::MTX34* pB, f32 t);
void fn_80356A64(VEC3* pOut, const VEC3* pA, const VEC3* pB, f32 t); // lerp
f32 fn_80356ACC(f32 x, const f32& rLo, const f32& rHi);           // clamp
void fn_8050F430(void* pObj);
void fn_8050F3A8(void* pObj, BOOL a, BOOL b);
void fn_8050EB48(void* pObj);
}

namespace Bsk {

struct Unk_ArgC {
    char unk0[0x34];
    VEC3 mUnk34; // at 0x34
    VEC3 mUnk40; // at 0x40
};

struct Unk_Arg {
    char unk0[0xC];
    Unk_ArgC* mUnkC; // at 0xC
    char unk10[0x44 - 0x10];
    u32 mUnk44; // at 0x44
};

struct Unk_Obj {
    char unk0[0x4];
    nw4r::math::MTX34 mMtx; // at 0x4
    char unk34[0x64 - 0x34];
    VEC3 mUnk64; // at 0x64
    VEC3 mUnk70; // at 0x70
    VEC3 mUnk7C; // at 0x7C
    f32 mUnk88;  // at 0x88
    f32 mUnk8C;  // at 0x8C
};

struct Unk_8 {
    char unk0[0x30];
    nw4r::math::MTX34 mUnk30; // at 0x30
    nw4r::math::MTX34 mUnk60; // at 0x60
    char unk90[0xF0 - 0x90];
    nw4r::math::MTX34 mUnkF0; // at 0xF0
};

struct Unk_B8 {
    char unk0[0x40];
    Unk_Obj* mUnk40[2]; // at 0x40
};

struct Unk_164 {
    char unk0[0xB8];
    Unk_B8* mUnkB8; // at 0xB8
};

struct Unk_4 {
    char unk0[0x164];
    Unk_164* mUnk164; // at 0x164
};

struct Unk_158 {
    virtual void Unk08();
    virtual void Unk0C();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1C();
    virtual void Unk20();
    virtual void Unk24();
    virtual BOOL Unk28();

    char unk4[0xBC - 0x4];
    f32 mUnkBC; // at 0xBC
    f32 GetUnkBC() const { return mUnkBC; }
};

struct Unk_Mgr {
    char unk0[0x158];
    Unk_158* mUnk158; // at 0x158
};

static f32 sUnk_806F27FC = -180.0f;
static f32 sUnk_806F2800 = 180.0f;
static f32 sUnk_806F2804 = 20.0f;
static f32 sUnk_806F2808 = 60.0f;
static f32 sUnk_806F280C = 0.2f;
static f32 sUnk_806F2810 = 1.2f;

static VEC3 sUnk_807D48F8[] = {
    VEC3(0.4f, 0.0f, 1.0f),  VEC3(2.0f, 0.2f, 1.5f),  VEC3(0.4f, 0.0f, 1.0f),
    VEC3(3.0f, 0.2f, 1.5f),  VEC3(0.2f, 0.0f, 1.0f),  VEC3(-0.2f, 0.0f, 1.0f),
    VEC3(0.0f, 1.0f, 0.0f),  VEC3(0.0f, 1.0f, 0.0f),  VEC3(0.0f, 0.0f, 0.0f),
};

class Unk_806E0ED0 {
public:
    Unk_806E0ED0() : m4(NULL), m8(NULL) {}
    virtual ~Unk_806E0ED0() {}
    virtual void Reset();

    void SetUnk4(Unk_4* p);
    const VEC3& GetUnk24(int i) const { return m24[i]; }
    bool Unk_8051BB0C(Unk_Arg* pArg);
    void Unk_8051BDA8(nw4r::math::MTX34* pOut, const nw4r::math::MTX34* pPrev,
                      const nw4r::math::MTX34* pTarget, BOOL reset, f32 scale);
    void Unk_8051BF34(nw4r::math::MTX34* pMtx, f32 limit);
    void Unk_8051C51C();

private:
    Unk_4* m4;   // at 0x4
    Unk_8* m8;   // at 0x8
    VEC3 mC;     // at 0xC
    VEC3 m18;    // at 0x18
    VEC3 m24[2]; // at 0x24
    bool m3C;    // at 0x3C
    bool m3D;    // at 0x3D
    u32 m40;     // at 0x40
    u32 m44;     // at 0x44
};

void Unk_806E0ED0::SetUnk4(Unk_4* p) {
    m4 = p;
}

void Unk_806E0ED0::Reset() {
    mC = lbl_807D1558;
    m18 = lbl_807D1558;
    m24[0] = lbl_807D1558;
    m24[1] = lbl_807D1558;
    m3C = false;
    m3D = false;
    m40 = 0;
    m44 = 0;
}

void Unk_806E0ED0::Unk_8051C51C() {
    const VEC3* pTable = sUnk_807D48F8;

    m40 = 0;
    m44 = 0;
    m3C = false;

    Unk_Mgr* pMgr = static_cast<Unk_Mgr*>(fn_8050456C(fn_80504C60()));
    if (pMgr->mUnk158->Unk28()) {
        m3D = false;
    } else {
        m3D = true;
    }

    m4->mUnk164->mUnkB8->mUnk40[0]->mUnk88 = 0.0f;
    m4->mUnk164->mUnkB8->mUnk40[1]->mUnk88 = 0.0f;
    m4->mUnk164->mUnkB8->mUnk40[0]->mUnk8C = 0.0f;
    m4->mUnk164->mUnkB8->mUnk40[1]->mUnk8C = 0.0f;
    m4->mUnk164->mUnkB8->mUnk40[0]->mUnk64 = pTable[4];
    m4->mUnk164->mUnkB8->mUnk40[1]->mUnk64 = pTable[5];
    m4->mUnk164->mUnkB8->mUnk40[0]->mUnk70 = pTable[6];
    m4->mUnk164->mUnkB8->mUnk40[1]->mUnk70 = pTable[7];
    m4->mUnk164->mUnkB8->mUnk40[0]->mUnk7C = pTable[8];
    m4->mUnk164->mUnkB8->mUnk40[1]->mUnk7C = pTable[8];

    fn_8050F430(m4->mUnk164);
    fn_8050F3A8(m4->mUnk164, TRUE, FALSE);
    fn_8050EB48(m4->mUnk164);

    PSMTXCopy(m8->mUnk30, m8->mUnk60);

    nw4r::math::MTX34 rot;
    nw4r::math::MTX34RotXYZDeg(&rot, -65.0f, 0.0f, 0.0f);

    nw4r::math::MTX34 mtx;
    PSMTXConcat(m8->mUnk60, rot, mtx);

    Unk_8051BF34(&mtx, 30.0f);
    Unk_8051BDA8(&m8->mUnkF0, &m8->mUnkF0, &mtx, TRUE, 8.0f);
}

void Unk_806E0ED0::Unk_8051BF34(nw4r::math::MTX34* pMtx, f32 limit) {
    VEC3 axisZ, axisX, axisY;
    axisX.x = pMtx->_00;
    axisX.y = pMtx->_10;
    axisX.z = pMtx->_20;
    axisY.x = pMtx->_01;
    axisY.y = pMtx->_11;
    axisY.z = pMtx->_21;
    axisZ.x = pMtx->_02;
    axisZ.y = pMtx->_12;
    axisZ.z = pMtx->_22;

    f32 angle = fn_80356ACC(nw4r::math::Atan2Deg(axisZ.z, axisZ.y), sUnk_806F27FC, sUnk_806F2800);
    if (angle < 0.0f) {
        angle += 360.0f;
    }

    if (limit == 0.0f) {
        limit = 30.0f;
    }

    if (limit < 60.0f) {
        if (angle < limit) {
            angle += 360.0f;
        }
        limit += 360.0f;
    }

    f32 mid = 0.5f * (60.0f + limit);
    if (angle > 60.0f && angle <= mid) {
        angle = 0.2f * (angle - 60.0f) + 60.0f;
    } else if (angle > mid && angle < limit) {
        angle = limit - 0.2f * (limit - angle);
    }

    if (angle > 360.0f) {
        angle -= 360.0f;
    }

    axisZ.x = 0.0f;
    axisZ.y = nw4r::math::CosDeg(angle);
    axisZ.z = nw4r::math::SinDeg(angle);

    pMtx->_02 = axisZ.x;
    pMtx->_12 = axisZ.y;
    pMtx->_22 = axisZ.z;

    PSVECCrossProduct(axisZ, axisX, axisY);

    pMtx->_01 = axisY.x;
    pMtx->_11 = axisY.y;
    pMtx->_21 = axisY.z;
}

void Unk_806E0ED0::Unk_8051BDA8(nw4r::math::MTX34* pOut, const nw4r::math::MTX34* pPrev,
                                const nw4r::math::MTX34* pTarget, BOOL reset, f32 scale) {
    VEC3 target;
    target.x = pTarget->_02;
    target.y = pTarget->_12;
    target.z = pTarget->_22;
    target *= scale;

    if (reset) {
        *pOut = *pTarget;
    } else {
        fn_80356330(pOut, pPrev, pTarget, 0.08f);
    }

    if (reset) {
        mC = target;
        m18 = lbl_807D1558;
    }

    f32 rate = 0.15f;
    VEC3 step = target - mC;
    step *= rate;

    VEC3 vel;
    fn_80356A64(&vel, &m18, &step, 0.2f);
    m18 = vel;
    mC += m18;

    pOut->_03 = mC.x;
    pOut->_13 = mC.y;
    pOut->_23 = mC.z;
}

bool Unk_806E0ED0::Unk_8051BB0C(Unk_Arg* pArg) {
    const VEC3* pTable = sUnk_807D48F8;
    Unk_Mgr* pMgr = static_cast<Unk_Mgr*>(fn_8050456C(fn_80504C60()));
    bool result = false;

    if ((pArg->mUnk44 & 1) && !(pArg->mUnk44 & 4) && fn_8050F354(m4->mUnk164)) {
        for (int i = 0; i < 2; i++) {
            Unk_Obj* pObj = m4->mUnk164->mUnkB8->mUnk40[i];

            if (!m3D && fn_8050C6C4(pObj, pArg, &pTable[2], &pTable[3],
                                    &lbl_807D1558, FALSE, -10.0f)) {
                m3D = true;
                f32 scale = fn_803569FC(pMgr->mUnk158->GetUnkBC(), sUnk_806F2804,
                                        sUnk_806F2808, 0.94f, 0.98f);
                pArg->mUnkC->mUnk34 = pArg->mUnkC->mUnk34 * scale;
                pArg->mUnkC->mUnk40 = pArg->mUnkC->mUnk40 * 1.0f;
            }

            VEC3 delta(pObj->mMtx._03, pObj->mMtx._13, pObj->mMtx._23);
            delta -= GetUnk24(i);

            f32 maxLen = sUnk_806F2810;
            if (nw4r::math::VEC3Len(&delta) > maxLen) {
                fn_80356940(&delta);
                fn_8021D094(&delta, &delta, maxLen);
            }

            if (m3C) {
                delta = lbl_807D1558;
            }

            VEC3 push = delta * sUnk_806F280C;
            if (fn_8050C6C4(pObj, pArg, &pTable[0], &pTable[1], &push, TRUE,
                            -10.0f) &&
                !m3C) {
                m3C = true;
                result = true;
                break;
            }
        }
    }

    return result;
}

} // namespace Bsk
