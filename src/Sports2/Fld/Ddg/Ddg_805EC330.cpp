// Ddg_805EC330: Resort Frisbee Dog unit 0x805EC330-0x805EDAC0 (Resort-only, no Wii Sports twin).
// balloons: WS2_fld_balloon, WS2_fld_mii_balloon, WS2_fld_baloon_hit/punc.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EB400 {
public:
    virtual void vf8();
};

extern "C" {

void fn_8028FD8C(u8*);

void fn_805EDA28(u32* p, u8* a1) {
    u32 x = *(u32*)(a1 + 0x74);
    u32 y = *(u32*)(a1 + 0x78);
    u32 z = *(u32*)(a1 + 0x7c);
    p[0] = x;
    p[1] = y;
    p[2] = z;
}

// Deleting destructor of a class without a base destructor.
void* fn_805ED9E8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805ECDEC(u8* p) {
    ((Unk_StateMachine<Unk_806EB400>*)(p + 0x14))->calc();
    fn_8028FD8C(p);
}

void fn_805EC60C(u8* p) {
    if (*(s32*)(p + 0x8) == 0) {
        *(f32*)(p + 0x25c) *= 0.96f;
        if (*(f32*)(p + 0x25c) < 0.1f) {
            *(f32*)(p + 0x25c) = 0.1f;
        }
    }
}

void fn_805EC608() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EB400>::Unk_StateMachine(Unk_806EB400*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EB400>::setState(const StateFn&, const StateFn&, s32);
