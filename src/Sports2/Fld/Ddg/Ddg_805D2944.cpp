// Ddg_805D2944: Resort Frisbee Dog unit 0x805D2944-0x805D483C (Resort-only, no Wii Sports twin).
// shoot effect (WS2_fld_shoot).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of the state machine at +0x8 (vtable 0x806EA468, ctor fn_805D4288).
class Unk_806EA468 {
public:
    virtual void vf8();
};

extern "C" {

void PSMTXConcat(u8*, u8*, u8*);
void PSMTXCopy(u8*, u8*, u8*);
void fn_80330568(u8*, u8*);
void fn_803305B4(u8*, u8*);
void fn_80331678(u8*, u8*, u8*);


struct Unk_Blk30 {
    u32 w[12];
};

// Deleting destructor of a class without a base destructor.
void* fn_805D475C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805D3BE8(u8* p) { ((Unk_StateMachine<Unk_806EA468>*)(p + 0x8))->calc(); }

void fn_805D3BB8(u8* p) {
    if (*(u32*)(p + 0xc) - 2 <= 1 && (*(u16*)(p + 0x254) & 0x20)) {
        (*(s32*)(*(u8**)(p + 0x258) + 0x34))++;
    }
}

void fn_805D37B4(u8* p) {
    fn_80331678(p + 0xc8, p + 0x38, p + 0x80);
    PSMTXConcat(*(u8**)(p + 0x260) + 0xb8, p + 0xc8, p + 0xf8);
    fn_80330568(p + 0xa4, p + 0xf8);
    fn_803305B4(p + 0x44, p + 0xf8);
}

void fn_805D2BD8(u8* p, Unk_Blk30* out) { *out = *(Unk_Blk30*)(p + 0x124); }

void fn_805D2BA8(u8* p, s32 i, Unk_Blk30* out) { *out = ((Unk_Blk30*)(p + 0x154))[i]; }

void fn_805D2B2C(u8* p, u8* a1) { PSMTXCopy(a1, p + 0x128, p); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for the unwritten owner ctor fn_805D4288
// (it calls the state machine ctor and setState).
template Unk_StateMachine<Unk_806EA468>::Unk_StateMachine(Unk_806EA468*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA468>::setState(const StateFn&, const StateFn&, s32);
