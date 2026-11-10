// Resort (RZTE01_01) port of Wii Sports RPBow_803547A4.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <types.h>
#include <egg/core/eggController.h>

// Minimal local declarations to avoid pulling pool entries / inlines from shared headers.
void* operator new[](unsigned long);
void operator delete(void*);

namespace Bowling {

// Inferred (name invented)
struct BowlingVec {
    f32 x, y, z;
};

struct BowlingRecordA {  // 0x20 bytes
    u32 unk_0x00;
    u8 unk_0x04;
    u8 pad05[3];
    BowlingVec unk_0x08;
    BowlingVec unk_0x14;
};

struct BowlingRecordB {  // 0x20 bytes
    u32 unk_0x00;
    f32 unk_0x04;
    f32 unk_0x08;
    BowlingVec unk_0x0C;
    f32 unk_0x18;
    f32 unk_0x1C;
};

// Inferred: 3x4 matrix stored as 12 floats (name invented).
struct BowlingMtx {
    f32 m[12];
};

// Element-wise matrix copy through an index loop; the out-of-line copy in
// RPBow_80323790 (ogws_fn_80326A34 -> ogws_fn_80326A64) has the same loop shape.
static inline void CopyMtx(BowlingMtx* d, const BowlingMtx* s) {
    for (int i = 0; i < 12; i++) {
        d->m[i] = s->m[i];
    }
}

// Lane state snapshot source (layout from ogws_fn_80326970/ogws_fn_80327054).
struct BowlingSrc {
    u8 pad00[0x10];
    BowlingVec unk_0x10[6];
    f32 unk_0x58;
    f32 unk_0x5C;
    BowlingRecordB unk_0x60;
    BowlingMtx unk_0x80;
    BowlingMtx unk_0xB0;
    BowlingVec unk_0xE0;
    f32 unk_0xEC;
    BowlingVec unk_0xF0;
};

struct BowlingRecordC {  // 0x118 bytes
    BowlingRecordB unk_0x00;
    BowlingMtx unk_0x20;
    BowlingMtx unk_0x50;
    BowlingVec unk_0x80;
    f32 unk_0x8C;
    BowlingVec unk_0x90;
    BowlingVec unk_0x9C[6];
    f32 unk_0xE4;
    u32 unk_0xE8;
    u32 unk_0xEC;
    BowlingVec unk_0xF0;
    BowlingVec unk_0xFC;
    BowlingVec unk_0x108;
    u8 unk_0x114;
    u8 pad115[3];
};

struct BowlingContainer {
    u8 pad00[4];
    BowlingRecordB* mpB;     // 0x04
    int mCountC;             // 0x08
    BowlingRecordC* mpC;     // 0x0C
    int mIdxC;               // 0x10
    BowlingRecordC* mpCurC;  // 0x14
    int mCapB;               // 0x18
    int mIdxB;               // 0x1C
    int mCapA;               // 0x20
    int mIdxA;               // 0x24
    BowlingRecordA* mpA;     // 0x28
};

extern "C" {

void fn_804DE0EC(void*);
void fn_804DE040(void*, int);
void fn_804D9C0C(BowlingRecordB*, const BowlingRecordB*);
void fn_80243A30(BowlingMtx*, const BowlingMtx*);
void fn_80243A94(BowlingVec*, const BowlingVec*);
void fn_804C473C(void*);
void fn_804C44F0(void*);
void* __construct_new_array(void* block, void* ctor, void* dtor, unsigned long size, unsigned long n);

void fn_804DE03C(void*) {}

void fn_804DDF54(BowlingContainer* pThis, int count) {
    pThis->mCountC = count;
    pThis->mCapB = count * 8;
    if (count != 0) {
        u32 n = count;
        pThis->mCapA = 100;
        pThis->mpC = (BowlingRecordC*)__construct_new_array(operator new[](n * sizeof(BowlingRecordC) + 0x10), (void*)fn_804DE0EC, (void*)fn_804DE040, sizeof(BowlingRecordC), n);
        pThis->mpB = (BowlingRecordB*)__construct_new_array(operator new[](pThis->mCapB * 0x20 + 0x10), (void*)fn_804C473C, (void*)fn_804C44F0, 0x20, pThis->mCapB);
        pThis->mpA = (BowlingRecordA*)__construct_new_array(operator new[](pThis->mCapA * 0x20 + 0x10), (void*)fn_804DE03C, 0, 0x20, pThis->mCapA);
    } else {
        pThis->mCapA = 0;
        pThis->mpC = 0;
        pThis->mpB = 0;
        pThis->mpA = 0;
    }
}

void fn_804DDF3C(BowlingContainer* pThis) {
    pThis->mIdxC = 0;
    pThis->mpCurC = 0;
    pThis->mIdxB = 0;
    pThis->mIdxA = 0;
}

void fn_804DDE30(BowlingContainer* pThis, BowlingSrc* s) {
    if (pThis->mpC == 0) return;
    if (pThis->mIdxC >= pThis->mCountC) return;
    BowlingRecordC* d = &pThis->mpC[pThis->mIdxC++];
    pThis->mpCurC = d;
    fn_804D9C0C(&d->unk_0x00, &s->unk_0x60);
    fn_80243A30(&d->unk_0x20, &s->unk_0x80);
    fn_80243A30(&d->unk_0x50, &s->unk_0xB0);
    fn_80243A94(&d->unk_0x80, &s->unk_0xE0);
    d->unk_0x8C = s->unk_0xEC;
    fn_80243A94(&d->unk_0x90, &s->unk_0xF0);
    fn_80243A94(&d->unk_0x9C[0], &s->unk_0x10[0]);
    fn_80243A94(&d->unk_0x9C[1], &s->unk_0x10[1]);
    fn_80243A94(&d->unk_0x9C[2], &s->unk_0x10[2]);
    fn_80243A94(&d->unk_0x9C[3], &s->unk_0x10[3]);
    fn_80243A94(&d->unk_0x9C[4], &s->unk_0x10[4]);
    fn_80243A94(&d->unk_0x9C[5], &s->unk_0x10[5]);
    d->unk_0xE4 = s->unk_0x58;
    pThis->mpCurC->unk_0x114 = pThis->mpCurC->unk_0xEC = 0;
}

void fn_804DDDC4(BowlingContainer* pThis, BowlingVec* __restrict a, BowlingVec* __restrict b, BowlingVec* __restrict c) {
    BowlingRecordC* cur = pThis->mpCurC;
    if (cur == 0) return;
    cur->unk_0xF0 = *a;
    pThis->mpCurC->unk_0xFC = *b;
    pThis->mpCurC->unk_0x108 = *c;
    pThis->mpCurC->unk_0x114 = 1;
}

void fn_804DDCF4(BowlingContainer* pThis, BowlingRecordB* src, int n) {
    if (pThis->mpCurC == 0) return;
    pThis->mpCurC->unk_0xE8 = pThis->mIdxB;
    pThis->mpCurC->unk_0xEC = n;
    int i;
    for (i = 0; i < n; i++) {
        if (pThis->mIdxB < pThis->mCapB) {
            BowlingRecordB* s = &src[i];
            BowlingRecordB* d = &pThis->mpB[pThis->mIdxB];
            d->unk_0x00 = s->unk_0x00;
            d->unk_0x04 = s->unk_0x04;
            d->unk_0x08 = s->unk_0x08;
            fn_80243A94(&d->unk_0x0C, &s->unk_0x0C);
            d->unk_0x18 = s->unk_0x18;
            d->unk_0x1C = s->unk_0x1C;
            pThis->mIdxB++;
        }
    }
}

void fn_804DDC88(BowlingContainer* pThis, u8 type, BowlingVec* __restrict pos, BowlingVec* __restrict vel) {
    if (pThis->mpA == 0) return;
    if (pThis->mIdxA >= pThis->mCapA) return;
    BowlingRecordA* e = &pThis->mpA[pThis->mIdxA++];
    e->unk_0x04 = type;
    e->unk_0x08 = *pos;
    e->unk_0x14 = *vel;
    e->unk_0x00 = pThis->mIdxC;
}

}

}  // namespace Bowling

// Resort: UpdateControllerState sits directly before this file's first function
// (ogws carried it at the end of RPBowTrajectoryGuide.cpp).
extern EGG::CoreControllerMgr* lbl_806F4A08;  // Resort name of EGG::CoreControllerMgr::sInstance

namespace Bowling {

/**
 * @brief Updates the controller state bitmask
 *
 * @param pObj Unknown object data array
 */
void UpdateControllerState(u32* pObj) {
    if (pObj[3] != 0) {
        EGG::CoreController* pCtrl = lbl_806F4A08->getNthController(0);
        if (*(u32*)((u8*)pCtrl + 0x1C) & 0x100) {
            return;
        }
    }
}

} // namespace Bowling
