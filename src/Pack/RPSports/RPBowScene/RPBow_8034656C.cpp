// Resort (RZTE01_01) port of Wii Sports RPBow_8034656C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <nw4r/math/math_types.h>

using nw4r::math::VEC3;

// Inferred (name invented): VEC3 whose assignment copies field by field
struct BowVec3 : VEC3 {
    BowVec3& operator=(const VEC3& rRhs) {
        x = rRhs.x;
        y = rRhs.y;
        z = rRhs.z;
        return *this;
    }
};

// Inferred (name invented): per-lane path state
struct BowPath {
    s32 pad_0x0;  // offset 0x0
    s32 mLane;    // offset 0x4
    s32 mIndex;   // offset 0x8
    u8 mDone;     // offset 0xC
    u8 pad_0xD[3];
    BowVec3 mEnd;  // offset 0x10
};

extern "C" {

extern f32 lbl_807D3A18[54];
extern f32 lbl_807D3AF0[18];
f32 lbl_806DEC30[6] = {125.0f, 124.0f, 130.0f, 131.0f, 131.0f, 131.0f};

const f32 lbl_806820C0[6] = {-16.0f, 17.23f, -33.6f, 33.7f, -49.89f, 51.29f};

void fn_804D65D4();
void fn_804D6390();
VEC3 fn_804D6314(const BowPath* pPath);
void fn_804D621C(BowPath* pPath, s32 lane, s32 index);

static inline VEC3 BowSubX(const VEC3& rPos, f32 x) {
    VEC3 off(x, 0.0f, 0.0f);
    return rPos - off;
}

#define BOW_PT1(p) ((VEC3(*)[3])lbl_807D3A18)[(p)->mLane][(p)->mIndex]
#define BOW_PT2(p) ((VEC3*)lbl_807D3AF0)[(p)->mLane]

void fn_804D65D4() {}

void fn_804D6390() {
    f32* t = lbl_807D3A18;
    f32* u = lbl_807D3AF0;
    t[0] = -11.8f;
    t[1] = 0.0f;
    t[2] = 53.0f;
    t[3] = -15.0f;
    t[4] = -1.0f;
    t[5] = 63.0f;
    t[6] = -19.0f;
    t[7] = -1.0f;
    t[8] = 72.0f;
    t[9] = 22.0f;
    t[10] = 0.0f;
    t[11] = 53.0f;
    t[12] = 19.0f;
    t[13] = -1.0f;
    t[14] = 63.0f;
    t[15] = 16.0f;
    t[16] = -1.0f;
    t[17] = 72.0f;
    t[18] = -38.0f;
    t[19] = 0.0f;
    t[20] = 53.0f;
    t[21] = -35.0f;
    t[22] = -1.0f;
    t[23] = 63.0f;
    t[24] = -31.0f;
    t[25] = -1.0f;
    t[26] = 72.0f;
    t[27] = 29.0f;
    t[28] = 0.0f;
    t[29] = 53.0f;
    t[30] = 32.0f;
    t[31] = -1.0f;
    t[32] = 63.0f;
    t[33] = 36.0f;
    t[34] = -1.0f;
    t[35] = 72.0f;
    t[36] = -45.3f;
    t[37] = 0.0f;
    t[38] = 53.0f;
    t[39] = -48.0f;
    t[40] = -1.0f;
    t[41] = 63.0f;
    t[42] = -52.0f;
    t[43] = -1.0f;
    t[44] = 72.0f;
    t[45] = 55.7f;
    t[46] = 0.0f;
    t[47] = 53.0f;
    t[48] = 52.0f;
    t[49] = -1.0f;
    t[50] = 63.0f;
    t[51] = 49.0f;
    t[52] = -1.0f;
    t[53] = 72.0f;
    u[0] = -21.0f;
    u[1] = 0.0f;
    u[2] = 40.0f;
    u[3] = 12.0f;
    u[4] = 0.0f;
    u[5] = 40.0f;
    u[6] = -29.0f;
    u[7] = 0.0f;
    u[8] = 40.0f;
    u[9] = 38.0f;
    u[10] = 0.0f;
    u[11] = 40.0f;
    u[12] = -55.0f;
    u[13] = 0.0f;
    u[14] = 40.0f;
    u[15] = 47.0f;
    u[16] = 0.0f;
    u[17] = 40.0f;
}

VEC3 fn_804D6314(const BowPath* pPath) {
    const VEC3* v = ((VEC3(*)[3])lbl_807D3A18)[pPath->mLane];
    return (v[0] + v[1] + v[2]) / 3.0f;
}

VEC3 fn_804D62A4(const BowPath* pPath) {
    return BowSubX(BOW_PT1(pPath), lbl_806820C0[pPath->mLane]);
}

VEC3 fn_804D6240(const BowPath* pPath) {
    return BowSubX(BOW_PT2(pPath), lbl_806820C0[pPath->mLane]);
}

void fn_804D6228(VEC3* pVec) {
    pVec->x = 0.0f;
    pVec->y = 0.0f;
    pVec->z = 24.0f;
}

void fn_804D621C(BowPath* pPath, s32 lane, s32 index) {
    pPath->mLane = lane;
    pPath->mIndex = index;
}

void fn_804D5F88(BowVec3* pOut, BowPath* pPath, bool* pFlag, f32* pRatio, f32 t, f32 z) {
    VEC3 a = BowSubX(BOW_PT1(pPath), lbl_806820C0[pPath->mLane]);
    VEC3 d = BowSubX(BOW_PT2(pPath), lbl_806820C0[pPath->mLane]);
    VEC3 c(0.0f, 0.0f, 24.0f);
    pPath->mDone = false;
    if (z > 0.0f) {
        d.z = z;
    }
    if (t < 120.0f) {
        f32 s = t / 120.0f;
        *pOut = a + (d - a) * s;
    } else if (t < 140.0f) {
        *pOut = d;
    } else if (t < 270.0f) {
        f32 s = (t - 140.0f) / 130.0f;
        *pOut = (c - d) * s + d;
    } else {
        *pOut = c;
        pPath->mDone = true;
    }
    if (t < lbl_806DEC30[pPath->mLane]) {
        *pFlag = false;
    } else {
        *pFlag = true;
    }
    if (pRatio) {
        *pRatio = (t - 120.0f) / 30.0f;
        if (*pRatio < 0.0f) {
            *pRatio = 0.0f;
        }
        if (*pRatio > 1.0f) {
            *pRatio = 1.0f;
        }
    }
    pOut->x += lbl_806820C0[pPath->mLane];
}

void ogws_fn_803466E4(BowVec3* pOut, BowPath* pPath, bool* pFlag, f32 t, f32 z) {
    VEC3 b = pPath->mEnd;
    VEC3 a = BowSubX(BOW_PT2(pPath), lbl_806820C0[pPath->mLane]);
    VEC3 c(0.0f, 0.0f, 24.0f);
    pPath->mDone = false;
    if (z > 0.0f) {
        a.z = z;
    }
    if (t < 120.0f) {
        f32 s = t / 120.0f;
        *pOut = b + (a - b) * s;
    } else if (t < 130.0f) {
        *pOut = a;
    } else if (t < 250.0f) {
        f32 s = (t - 130.0f) / 120.0f;
        *pOut = (c - a) * s + a;
    } else {
        *pOut = c;
        pPath->mDone = true;
    }
    if (t < 130.0f) {
        *pFlag = false;
    } else {
        *pFlag = true;
    }
    pOut->x += lbl_806820C0[pPath->mLane];
}

void fn_804D5D08(BowPath* pPath, const VEC3* pVec) {
    pPath->mEnd = *pVec;
    pPath->mEnd.x -= lbl_806820C0[pPath->mLane];
}

void fn_804D5BD0(BowVec3* pOut, BowPath* pPath, f32 t) {
    VEC3 c(0.0f, 0.0f, 20.0f);
    f32 s = t / 3.0f / 60.0f;
    pPath->mDone = false;
    // MATCH-PENDING (R17): dead increment/decrement pair on mLane; it splits the mLane value's live range so
    // the lane index colours into r8 and the zero for mDone into r9 as in retail (otherwise swapped).
    // The real source probably reads the lane through an accessor/inline not modelled here.
    pPath->mLane++;
    pPath->mLane--;
    *pOut = BowSubX(BOW_PT1(pPath), lbl_806820C0[pPath->mLane]);
    if (s > 1.0f) {
        s = 1.0f;
        pPath->mDone = true;
    }
    *pOut = (*pOut - pPath->mEnd) * s + pPath->mEnd;
    pOut->x += lbl_806820C0[pPath->mLane];
}

void fn_804D5BCC() {}

#pragma force_active on
__declspec(section ".ctors") static void (*bowInit8034656C)(void) = fn_804D6390;
#pragma force_active reset

}
