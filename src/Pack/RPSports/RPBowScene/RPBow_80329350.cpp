// Resort (RZTE01_01) port of Wii Sports RPBow_80329350.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPSports/RPBowScene/bowling.h>

namespace Bowling {

// Inferred (name invented): raw BVH query result record (0x24 bytes)
struct BvhHit {
    f32 unk_0x00[3];  // offset 0x0
    f32 unk_0x0C[4];  // offset 0xC
    u16 type;         // offset 0x1C
    u16 pad1E;        // offset 0x1E
    u8 pad20[4];      // offset 0x20
};

// Inferred (name invented): compacted BVH query result record (0x20 bytes)
struct BvhHitOut {
    f32 unk_0x00[4];  // offset 0x0
    u32 type;         // offset 0x10
    f32 unk_0x14[3];  // offset 0x14
};

extern "C" {

int fn_80379F5C(BvhEntryHeader* pHeader, BvhHit* pHits, int max);
int fn_8037A2A8(BvhEntryHeader* pHeader, BvhHit* pHits, int max);
void fn_8037A684(BvhEntryHeader* pHeader, void* pData);

}

void fn_804E3DFC(LaneBvhData* pData, void* pArg1, void* pArg2) {
    pData->pObj1 = new BvhEntryHeader;
    fn_8037A684(pData->pObj1, pArg1);
    pData->pObj2 = new BvhEntryHeader;
    fn_8037A684(pData->pObj2, pArg2);
}

extern "C" {

int fn_804E3D48(LaneBvhData* pData, BvhHitOut* pOut, int max) {
    BvhHit hits[0x40];
    int count = fn_80379F5C(pData->pObj2, hits, 0x40);
    if (count > max) {
        count = max;
    }
    for (int i = 0; i < count; i++) {
        pOut->type = hits[i].type;
        pOut->unk_0x00[0] = hits[i].unk_0x0C[0];
        pOut->unk_0x00[1] = hits[i].unk_0x0C[1];
        pOut->unk_0x00[2] = hits[i].unk_0x0C[2];
        pOut->unk_0x00[3] = hits[i].unk_0x0C[3];
        pOut->unk_0x14[0] = hits[i].unk_0x00[0];
        pOut->unk_0x14[1] = hits[i].unk_0x00[1];
        pOut->unk_0x14[2] = hits[i].unk_0x00[2];
        pOut++;
    }
    return count;
}

int fn_804E3C0C(LaneBvhData* pData, BvhHitOut* pOut, int max, const nw4r::math::VEC3* pPos, int flag, bool alt, f32 margin) {
    BvhHit hits[0x40];
    int count;
    if (alt) {
        count = fn_8037A2A8(pData->pObj1, hits, 0x40);
    } else {
        count = fn_80379F5C(pData->pObj1, hits, 0x40);
    }
    if (count > max) {
        count = max;
    }
    int skipped = 0;
    for (int i = 0; i < count; i++) {
        int type = hits[i].type;
        pOut->type = type;
        if (type == 3 && (pPos->y + margin < pData->field_0x14 || flag == 0)) {
            skipped++;
        } else if (type == 6) {
            skipped++;
        } else {
            pOut->unk_0x00[0] = hits[i].unk_0x0C[0];
            pOut->unk_0x00[1] = hits[i].unk_0x0C[1];
            pOut->unk_0x00[2] = hits[i].unk_0x0C[2];
            pOut->unk_0x00[3] = hits[i].unk_0x0C[3];
            pOut->unk_0x14[0] = hits[i].unk_0x00[0];
            pOut->unk_0x14[1] = hits[i].unk_0x00[1];
            pOut->unk_0x14[2] = hits[i].unk_0x00[2];
            pOut++;
        }
    }
    return count - skipped;
}

void fn_804E3C08() {}

}

}  // namespace Bowling
