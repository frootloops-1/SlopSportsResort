// Ddg_805DC06C: Resort Frisbee Dog unit 0x805DC06C-0x805DF4D0 (Resort-only, no Wii Sports twin).
// game rules: AreaQuestion[ %d ], BalloonLevel[ %s ], SkillData.exbin (vtable 0x806EA9A8).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EAA60 {
public:
    virtual void vf8();
};

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC(s32);
};

void fn_805D8AF8(u8*);

// Deleting destructor of a class without a base destructor.
void* fn_805DF464(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805DE9B4(u8* p) {
    ((Unk_StateMachine<Unk_806EAA60>*)(p + 0x14))->calc();
    *(u8*)(p + 0x9b) = 0;
}

void fn_805DE9A8(u8* p) { ((Unk_StateMachineBase*)(p + 0x14))->request(1); }

void fn_805DC698(u8* p) {
    u32* q = *(u32**)(p + 0x10);
    q[2] = q[0];
    q[4] = q[3] = q[0];
}

s32 fn_805DC618(u8* p) {
    if (*(s32*)(p + 0xa0) == 2) {
        return 2;
    }
    return -1;
}

BOOL fn_805DC5EC(u8* p) { return fn_805DC618(p) == 2; }

u32 fn_805DC1BC(u8* p) { return (*(u16*)(*(u8**)(p + 0x50) + 0x34) >> 3) & 1; }

void fn_805DC1B4(u8* p) { fn_805D8AF8(*(u8**)(p + 0x50)); }

u32 fn_805DC0B0(u8* p) {
    if (*(s32*)(p + 0x78) == 0) {
        return *(u32*)(*(u8**)(p + 0x74) + *(s32*)(p + 0x70) * 0x38 + 0x10);
    }
    return *(u32*)(p + 0x70);
}

void fn_805DC094(u8* p) { *(s32*)(*(u8**)(p + 0x50) + *(s32*)(p + 0x70) * 8 + 0x40) = -1; }

u32 fn_805DC084(u8* p) { return (*(u16*)(*(u8**)(p + 0x50) + 0x34) >> 5) & 1; }

void fn_805DC06C(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x50)))->vfC(5); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EAA60>::Unk_StateMachine(Unk_806EAA60*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EAA60>::setState(const StateFn&, const StateFn&, s32);
