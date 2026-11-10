// Resort (RZTE01_01) port of Wii Sports RPBow_80348158.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_80348158: bowling camera path player (debug print, interpolation,
// update, rate table) and the built-in camera cut table (ogws_fn_80348858).
// Types and names are inferred (invented).
//
// Functions are written in ASCENDING address order with
// `#pragma defer_codegen off`: under the unit's `-inline deferred` flag the
// local GXColor aggregate initialiser in fn_804CCE3C is pooled at parse time
// (first in .sdata2); non-deferred codegen puts it mid-pool like the
// original, with the strings and float literals in address order.
// Avoid `#pragma dont_inline` around fn_804CCBB8 or the functions near it:
// in this mode it stopped every inline (VEC3 operators, sinf) inside
// fn_804CCBB8. Only fn_804CD180 (which must call fn_804CD000) is wrapped.

#include <Pack/types_pack.h>
#include <revolution/GX/GXTypes.h>

#pragma defer_codegen off

// Minimal local nw4r::math view: <nw4r/math/math_types.h> pulls the static
// OSFastCast helpers (revolution/OS) into this object's .text.
namespace nw4r {
namespace math {

struct _VEC3 {
    f32 x, y, z;
};

struct VEC3 : _VEC3 {
    VEC3() {}
    VEC3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    VEC3 operator+(const VEC3& rRhs) const;
    VEC3 operator-(const VEC3& rRhs) const;
    VEC3 operator*(f32 x) const;
    VEC3& operator+=(const VEC3& rRhs);
};

inline VEC3* VEC3Add(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB) {
    register f32 work0, work1, work2;
    asm {
        psq_l  work0, 0(pA), 0, 0
        psq_l  work1, 0(pB), 0, 0
        ps_add work2, work0, work1
        psq_st work2, 0(pOut), 0, 0
        psq_l  work0, 8(pA), 1, 0
        psq_l  work1, 8(pB), 1, 0
        ps_add work2, work0, work1
        psq_st work2, 8(pOut), 1, 0
    }
    return pOut;
}

inline VEC3* VEC3Scale(register VEC3* pOut, register const VEC3* pIn, register f32 scale) {
    register f32 work0, work1;
    asm {
        psq_l    work0, 0(pIn), 0, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, 0(pOut), 0, 0
        psq_l    work0, 8(pIn), 1, 0
        ps_muls0 work1, work0, scale
        psq_st   work1, 8(pOut), 1, 0
    }
    return pOut;
}

inline VEC3* VEC3Sub(register VEC3* pOut, register const VEC3* pA, register const VEC3* pB) {
    register f32 work0, work1, work2;
    asm {
        psq_l  work0, 0(pA), 0, 0
        psq_l  work1, 0(pB), 0, 0
        ps_sub work2, work0, work1
        psq_st work2, 0(pOut), 0, 0
        psq_l  work0, 8(pA), 1, 0
        psq_l  work1, 8(pB), 1, 0
        ps_sub work2, work0, work1
        psq_st work2, 8(pOut), 1, 0
    }
    return pOut;
}

inline VEC3 VEC3::operator+(const VEC3& rRhs) const {
    VEC3 out;
    VEC3Add(&out, this, &rRhs);
    return out;
}
inline VEC3 VEC3::operator-(const VEC3& rRhs) const {
    VEC3 out;
    VEC3Sub(&out, this, &rRhs);
    return out;
}
inline VEC3 VEC3::operator*(f32 x) const {
    VEC3 out;
    VEC3Scale(&out, this, x);
    return out;
}
inline VEC3& VEC3::operator+=(const VEC3& rRhs) {
    VEC3Add(this, this, &rRhs);
    return *this;
}

}  // namespace math
}  // namespace nw4r

// Vector with a user-declared assignment (component copies), like
// EGG::Vector3f; it makes the entry assignment memberwise.
struct BowCamVec {
    f32 x, y, z;
    BowCamVec& operator=(const BowCamVec& r) {
        x = r.x;
        y = r.y;
        z = r.z;
        return *this;
    }
};

// Inferred (name invented): camera output block written by the path player
struct BowCamParams {
    nw4r::math::VEC3 pos;     // offset 0x0
    nw4r::math::VEC3 target;  // offset 0xC
    nw4r::math::VEC3 up;      // offset 0x18
    f32 field_24;             // offset 0x24
    s32 field_28;             // offset 0x28
};

// Inferred (name invented): one camera path entry (0x78 bytes)
struct BowCamEntry {
    char name[0x20];          // offset 0x0
    s32 type;                 // offset 0x20
    BowCamVec from;           // offset 0x24
    BowCamVec to;             // offset 0x30
    f32 angleB0;              // offset 0x3C
    f32 angleA0;              // offset 0x40
    f32 angleB1;              // offset 0x44
    f32 angleA1;              // offset 0x48
    f32 rangeLo;              // offset 0x4C
    f32 rangeHi;              // offset 0x50
    f32 duration;             // offset 0x54
    f32 field_58;             // offset 0x58
    f32 field_5C;             // offset 0x5C
    nw4r::math::VEC3 offset;  // offset 0x60
    u8 hold;                  // offset 0x6C
    f32 rate;                 // offset 0x70
    s32 next;                 // offset 0x74
};

// Inferred (name invented): camera path player with a table of 24 entries
struct BowCamPath {
    u8 pad_0x0[0x4];
    BowCamParams params;      // offset 0x4
    s32 index;                // offset 0x30
    BowCamEntry entries[24];  // offset 0x34
    f32 time;                 // offset 0xB74
    f32 blend;                // offset 0xB78
    u8 paused;                // offset 0xB7C
    u8 pad_0xB7D[7];
    f32 field_B84;            // offset 0xB84
};

struct BowGlobal730 {
    u8 pad_0x0[0x6C];
    void* field_6C;
};

namespace EGG {
struct Screen {
    static int sTVMode;
};
}  // namespace EGG

extern "C" {

extern BowGlobal730* lbl_804BF730;
struct BowModeGlobal {
    u8 pad_0x0[0x18];
    s32 mode;
};
extern BowModeGlobal* lbl_806F5950;

int sprintf(char*, const char*, ...);
char* strcpy(char*, const char*);
void* memset(void*, int, unsigned long);
double sin(double);
double cos(double);
static inline float sinf(float x) {
    return sin(x);
}
static inline float cosf(float x) {
    return cos(x);
}
void fn_80373098(const char*, f32, f32, f32, u32, bool);
void ogws_fn_801F5634(void*, int, int, GXColor);

extern const char lbl_803931C0[400] =
    "\x83\x4A\x83\x81\x83\x89\x96\xBC:%s\0"
    "\x83\x8C\x81\x5B\x83\x67:%3.2f\0"
    "\x8D\xC5\x8F\x49\x83\x8C\x81\x5B\x83\x67:%3.2f\0"
    "\x83\x8C\x81\x5B\x83\x67\x83\x58\x83\x50\x81\x5B\x83\x8B:%3.2f\0"
    "IDLE\0"
    "OPENING_1\0"
    "OPENING_2\0"
    "OPENING_3\0"
    "THROWSTART\0"
    "TRIAL_STAGEINFO\0"
    "TRIAL_NEXTSTAGEINFO\0"
    "GATE_STATEINFO\0"
    "GATE_NEXTSTATEINFO\0"
    "RESULT\0"
    "RESULT_1\0"
    "RESULT_2\0"
    "100PIN_STAGEINFO[0]\0"
    "100PIN_STAGEINFO[9]\0"
    "100PIN_STAGEINFO[%d]\0"
    "100PIN_REPLAY1[0]\0"
    "100PIN_REPLAY1[9]\0"
    "100PIN_REPLAY1[%d]\0"
    "100PIN_REPLAY2[0]\0"
    "100PIN_REPLAY2[9]\0"
    "100PIN_REPLAY2[%d]\0"
    "100PIN_REPLAY3[%d]\0";

// MATCH-PENDING (R17): ledger #6.
// Placeholder for a function absent from the DOL (inferred: dead-stripped debug
// print; its body is NOT known): only its 40.0 survives, at the head of .sdata2.
static f32 BowCam_StrippedDebug(f32 x) {
    return x + 40.0f;
}

void fn_804CCBB8(BowCamPath* pThis, BowCamParams* pOut, const BowCamEntry* pEntry, f32 t) {
    f32 b0 = 3.14159f * (pEntry->angleB0 / 180.0f);
    f32 a0 = 3.14159f * (pEntry->angleA0 / 180.0f);
    f32 b1 = 3.14159f * (pEntry->angleB1 / 180.0f);
    f32 a1 = 3.14159f * (pEntry->angleA1 / 180.0f);
    nw4r::math::VEC3 from(pEntry->from.x, pEntry->from.y, pEntry->from.z);
    nw4r::math::VEC3 to(pEntry->to.x, pEntry->to.y, pEntry->to.z);
    pOut->pos = from + (to - from) * t;
    f32 angleB = t * (b1 - b0) + b0;
    f32 angleA = t * (a1 - a0) + a0;
    nw4r::math::VEC3 dir(sinf(angleB - 1.570795f) * sinf(angleA), cosf(angleB - 1.570795f),
                         sinf(angleB - 1.570795f) * cosf(angleA));
    pOut->target = pOut->pos + dir;
    pOut->up = nw4r::math::VEC3(0.0f, 1.0f, 0.0f);
    pOut->field_24 = pEntry->field_58;
    if (EGG::Screen::sTVMode == 0) {
        pOut->field_24 = pEntry->field_5C * pThis->field_B84 + pOut->field_24;
    }
    pOut->field_28 = 2;
    pOut->pos += pEntry->offset;
    pOut->target += pEntry->offset;
}

void fn_804CD120(BowCamPath* pThis, s32 index);
void fn_80266D64(void*, int, int, int, int);
extern void* lbl_806F4E58;

void fn_804CCE3C(BowCamPath* pThis) {
    BowCamEntry* e = &pThis->entries[pThis->index];
    BowCamParams* pParams = &pThis->params;
    f32 dt = 1.0f / e->duration;
    f32 prev = pThis->time;
    if (e->hold == 0 && pThis->paused == 0) {
        pThis->time = prev + dt;
    }
    if (pThis->time > 1.0f) {
        pThis->time = 1.0f;
    }
    f32 a = pThis->time * (e->rangeHi - e->rangeLo) + e->rangeLo;
    f32 delta = pThis->time - prev;
    pThis->blend += delta * ((f32)sin(3.14159f * a) * (f32)sin(3.14159f * a));
    if (pThis->blend > 1.0f) {
        pThis->blend = 1.0f;
    }
    switch (e->type) {
    case 0:
        fn_804CCBB8(pThis, pParams, e, pThis->blend * e->rate);
    }
    if (e->next != 0 && pThis->time + dt >= 1.0f) {
        if ((u32)(e->next - 10) <= 5 || (u32)(e->next - 1) <= 7) {
            fn_80266D64(lbl_806F4E58, 1, 2, 1, 0);
        }
        fn_804CD120(pThis, e->next);
    }
}

int fn_804CCFE4(BowCamPath* pThis) {
    return pThis->time >= 0.999f;
}

extern "C" const f32 lbl_804C665C;
void fn_804CD000(BowCamPath* pThis) {
    f32 one, pi, first, step, sum, x, a;
    pi = 3.14159f;
    one = 1.0f;
    step = lbl_804C665C;
    for (int i = 0; i < 24; i++) {
        BowCamEntry* e = &pThis->entries[i];
        sum = 0.0f;
        for (x = 0.0f; x <= one; x += step) {
            a = x * (e->rangeHi - e->rangeLo) + e->rangeLo;
            first = (f32)sin(pi * a);
            f32 second = (f32)sin(pi * a);
            second *= first;
            f32 v = step * second;
            sum += v;
        }
        e->rate = one / sum;
    }
}

extern "C" const f32 lbl_804C665C = 0.01f;

void fn_804CD120(BowCamPath* pThis, s32 index) {
    if (lbl_806F5950->mode == 1 && (u32)(index - 1) <= 3) {
        index += 4;
    }
    memset(&pThis->time, 0, 12);
    pThis->index = index;
}

void fn_804CD180(BowCamPath* pThis) {
    fn_804CD120(pThis, 0);
    fn_804CD000(pThis);
}

}  // extern "C"

static inline void BowLerp(BowCamEntry* e, const BowCamEntry* a, const BowCamEntry* b, f32 t) {
    e->from.x = t * (b->from.x - a->from.x) + a->from.x;
    e->from.y = t * (b->from.y - a->from.y) + a->from.y;
    e->from.z = t * (b->from.z - a->from.z) + a->from.z;
    e->to.x = t * (b->to.x - a->to.x) + a->to.x;
    e->to.y = t * (b->to.y - a->to.y) + a->to.y;
    e->to.z = t * (b->to.z - a->to.z) + a->to.z;
    e->angleB0 = t * (b->angleB0 - a->angleB0) + a->angleB0;
    e->angleA0 = t * (b->angleA0 - a->angleA0) + a->angleA0;
    e->angleB1 = t * (b->angleB1 - a->angleB1) + a->angleB1;
    e->angleA1 = t * (b->angleA1 - a->angleA1) + a->angleA1;
}

extern "C" void fn_804CD1B8(BowCamPath* pThis) {
    BowCamEntry* e;
    memset(pThis->entries, 0, sizeof(pThis->entries));
    e = &pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x3F));
    e->field_58 = 45.0f;
    e->rangeLo = 0.0f;
    e->rangeHi = 1.0f;
    e->duration = 60.0f;
    e = &pThis->entries[1];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x44));
    e->field_58 = 40.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 360.0f;
    e->from.x = -5.0f;
    e->from.y = 4.0f;
    e->from.z = -145.0f;
    e->to.x = 5.0f;
    e->to.y = 4.0f;
    e->to.z = -145.0f;
    e->angleB0 = -7.0f;
    e->angleA0 = -0.0f;
    e->angleB1 = -7.0f;
    e->angleA1 = -0.0f;
    e = &pThis->entries[2];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x4E));
    e->field_58 = 45.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 360.0f;
    e->from.x = -15.0f;
    e->from.y = 2.0f;
    e->from.z = -150.0f;
    e->to.x = -15.0f;
    e->to.y = 4.0f;
    e->to.z = -150.0f;
    e->angleB0 = -5.0f;
    e->angleA0 = -27.0f;
    e->angleB1 = -5.0f;
    e->angleA1 = -27.0f;
    e = &pThis->entries[3];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x58));
    e->field_58 = 40.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 360.0f;
    e->from.x = -10.0f;
    e->from.y = 26.6f;
    e->from.z = 93.0f;
    e->to.x = 10.0f;
    e->to.y = 26.0f;
    e->to.z = 93.0f;
    e->angleB0 = -30.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -30.0f;
    e->angleA1 = -0.0f;
    e = &pThis->entries[4];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x62));
    e->field_58 = 39.0f;
    e->hold = 1;
    e->from.x = 5.5f;
    e->from.y = 4.2f;
    e->from.z = 1.0f;
    e->to.x = 0.0f;
    e->to.y = 0.0f;
    e->to.z = 0.0f;
    e->angleB0 = 3.0f;
    e->angleA0 = 165.0f;
    e->angleB1 = 0.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[5];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x6D));
    e->field_58 = 40.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 1.0f;
    e->duration = 240.0f;
    e->from.x = 0.0f;
    e->from.y = 2.0f;
    e->from.z = -173.0f;
    e->to.x = 0.0f;
    e->to.y = 3.0f;
    e->to.z = -165.0f;
    e->angleB0 = 3.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = 0.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[6];
    *e = pThis->entries[5];
    strcpy(e->name, (lbl_803931C0 + 0x7D));
    e->next = 5;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.9f;
    e->duration = 90.0f;
    e->from.x = -18.0f;
    e->from.y = 2.0f;
    e->from.z = -173.0f;
    e->to.x = 0.37f;
    e->to.y = 2.0f;
    e->to.z = -173.0f;
    e->angleB0 = 3.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = 3.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[7];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x91));
    e->field_58 = 35.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 1.0f;
    e->duration = 90.0f;
    e->from.x = 0.0f;
    e->from.y = 20.0f;
    e->from.z = -25.0f;
    e->to.x = 0.0f;
    e->to.y = 20.0f;
    e->to.z = 32.0f;
    e->angleB0 = -20.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -20.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[8];
    *e = pThis->entries[7];
    strcpy(e->name, (lbl_803931C0 + 0xA0));
    e->next = 7;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.8f;
    e->duration = 80.0f;
    e->from.x = -18.0f;
    e->from.y = 20.0f;
    e->from.z = -25.0f;
    e->to.x = 0.37f;
    e->to.y = 20.0f;
    e->to.z = -25.0f;
    e->angleB0 = -20.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -20.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[9];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0xB3));
    e->next = 10;
    e->field_58 = 45.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 400.0f;
    e->from.x = -10.0f;
    e->from.y = 9.0f;
    e->from.z = -120.0f;
    e->to.x = 10.0f;
    e->to.y = 9.0f;
    e->to.z = -120.0f;
    e->angleB0 = -10.0f;
    e->angleA0 = 28.0f;
    e->angleB1 = -10.0f;
    e->angleA1 = 28.0f;
    e = &pThis->entries[10];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0xBA));
    e->next = 11;
    e->field_58 = 35.0f;
    e->rangeLo = 0.4f;
    e->rangeHi = 0.6f;
    e->duration = 600.0f;
    e->from.x = -61.0f;
    e->from.y = 23.0f;
    e->from.z = 20.0f;
    e->to.x = -30.0f;
    e->to.y = 34.0f;
    e->to.z = 13.0f;
    e->angleB0 = -23.0f;
    e->angleA0 = 225.5f;
    e->angleB1 = -30.0f;
    e->angleA1 = 213.0f;
    e = &pThis->entries[11];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0xC3));
    e->next = 9;
    e->field_58 = 47.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.7f;
    e->duration = 420.0f;
    e->from.x = 0.0f;
    e->from.y = 3.0f;
    e->from.z = 10.0f;
    e->to.x = 0.0f;
    e->to.y = 3.0f;
    e->to.z = -130.0f;
    e->angleB0 = -9.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -9.0f;
    e->angleA1 = -0.0f;
    e = &pThis->entries[12];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0xCC));
    e->field_58 = 35.0f;
    e->rangeLo = 0.0f;
    e->rangeHi = 1.0f;
    e->duration = 240.0f;
    e->from.x = 0.0f;
    e->from.y = 8.0f;
    e->from.z = -178.0f;
    e->to.x = 0.0f;
    e->to.y = 15.0f;
    e->to.z = -172.0f;
    e->angleB0 = -45.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -50.0f;
    e->angleA1 = 0.0f;
    e = &pThis->entries[21];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0xE0));
    e->field_58 = 35.0f;
    e->rangeLo = 0.0f;
    e->rangeHi = 1.0f;
    e->duration = 240.0f;
    e->from.x = 0.0f;
    e->from.y = 8.0f;
    e->from.z = -170.0f;
    e->to.x = 0.0f;
    e->to.y = 37.0f;
    e->to.z = -135.0f;
    e->angleB0 = -45.0f;
    e->angleA0 = 0.0f;
    e->angleB1 = -49.0f;
    e->angleA1 = 0.0f;
    for (int i = 1; i < 9; i++) {
        e = &pThis->entries[i + 12];
        f32 t = (f32)i / 9.0f;
        *e = pThis->entries[12];
        sprintf(e->name, (lbl_803931C0 + 0xF4), i);
        BowLerp(e, &pThis->entries[12], &pThis->entries[21], t);
    }
    e = &pThis->entries[22];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x109));
    e->field_58 = 40.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 120.0f;
    e->from.x = -5.5f;
    e->from.y = 14.0f;
    e->from.z = -172.0f;
    e->to.x = 5.5f;
    e->to.y = 14.0f;
    e->to.z = -172.0f;
    e->angleB0 = -40.0f;
    e->angleA0 = -20.0f;
    e->angleB1 = -38.0f;
    e->angleA1 = 20.0f;
    e = &pThis->entries[31];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x11B));
    e->field_58 = 45.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 120.0f;
    e->from.x = -10.0f;
    e->from.y = 18.0f;
    e->from.z = -170.0f;
    e->to.x = 5.0f;
    e->to.y = 18.0f;
    e->to.z = -180.0f;
    e->angleB0 = -40.0f;
    e->angleA0 = -20.0f;
    e->angleB1 = -40.0f;
    e->angleA1 = 14.0f;
    for (int i = 1; i < 9; i++) {
        e = &pThis->entries[i + 22];
        f32 t = (f32)i / 9.0f;
        *e = pThis->entries[22];
        sprintf(e->name, (lbl_803931C0 + 0x12D), i);
        BowLerp(e, &pThis->entries[22], &pThis->entries[31], t);
    }
    e = &pThis->entries[32];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x140));
    e->field_58 = 45.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 120.0f;
    e->from.x = -7.0f;
    e->from.y = 10.0f;
    e->from.z = -210.0f;
    e->to.x = 7.0f;
    e->to.y = 10.0f;
    e->to.z = -210.0f;
    e->angleB0 = -33.0f;
    e->angleA0 = 210.0f;
    e->angleB1 = -33.0f;
    e->angleA1 = 160.0f;
    e = &pThis->entries[41];
    *e = pThis->entries[0];
    strcpy(e->name, (lbl_803931C0 + 0x152));
    e->field_58 = 45.0f;
    e->rangeLo = 0.5f;
    e->rangeHi = 0.5f;
    e->duration = 120.0f;
    e->from.x = -20.0f;
    e->from.y = 10.0f;
    e->from.z = -230.0f;
    e->to.x = 12.0f;
    e->to.y = 12.0f;
    e->to.z = -240.0f;
    e->angleB0 = -30.0f;
    e->angleA0 = 221.0f;
    e->angleB1 = -28.0f;
    e->angleA1 = 161.33f;
    for (int i = 1; i < 9; i++) {
        e = &pThis->entries[i + 32];
        f32 t = (f32)i / 9.0f;
        *e = pThis->entries[32];
        sprintf(e->name, (lbl_803931C0 + 0x164), i);
        BowLerp(e, &pThis->entries[32], &pThis->entries[41], t);
    }

    for (int i = 10; i < 22; i++) {
        e = &pThis->entries[i];
        int k = (i - 12) % 10;
        e->from.z += 3.0f * (f32)-k - 3.12f;
        e->to.z += 3.0f * (f32)-k - 3.12f;
    }
    for (int i = 0; i < 10; i++) {
        pThis->entries[i + 42] = pThis->entries[i + 12];
        sprintf(pThis->entries[i + 42].name, (lbl_803931C0 + 0x177), i);
    }
    pThis->entries[42].from.x = 0.0f;
    pThis->entries[42].from.y = 10.0f;
    pThis->entries[42].from.z = -173.0f;
    pThis->entries[42].angleB0 = -32.0f;
    pThis->entries[42].angleA0 = 0.0f;
    pThis->entries[51].from.x = 0.0f;
    pThis->entries[51].from.y = 32.0f;
    pThis->entries[51].from.z = -160.0f;
    pThis->entries[51].angleB0 = -40.0f;
    pThis->entries[51].angleA0 = 0.0f;
    for (int i = 0; i < 10; i++) {
        e = &pThis->entries[i + 42];
        e->to = e->from;
        e->angleB1 = e->angleB0;
        e->angleA1 = e->angleA0;
    }
    for (int i = 1; i < 9; i++) {
        e = &pThis->entries[i + 42];
        f32 t = (f32)i / 9.0f;
        *e = pThis->entries[42];
        BowLerp(e, &pThis->entries[42], &pThis->entries[51], t);
    }
}
