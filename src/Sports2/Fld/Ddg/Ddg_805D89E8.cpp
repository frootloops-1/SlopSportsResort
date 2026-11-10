// Ddg_805D89E8: Resort Frisbee Dog unit 0x805D89E8-0x805DADC0 (Resort-only, no Wii Sports twin).
// player state class (vtable 0x806EA768) and helper 0x806EA838.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EA838 {
public:
    virtual void vf8();
};

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
};

extern u32 lbl_806F5F90;

void fn_805DAD5C(u8* p, s32 state) { ((Unk_StateMachineBase*)(p + 0x4))->request(state); }

bool fn_805DAD54(u8* p, s32 state) { return ((Unk_StateMachineBase*)(p + 0x4))->isState(state); }

// Deleting destructor of a class without a base destructor.
void* fn_805DAD14(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u32* fn_805DA9EC() { return &lbl_806F5F90; }

void fn_805DA6F4(u8* p) { ((Unk_StateMachine<Unk_806EA838>*)(p + 0x4))->calc(); }

void fn_805DA6E4(u8* p) { ((Unk_VtAt0*)(p))->vf18(); }

void fn_805D8BAC(u8* p) { *(u16*)(p + 0x34) = 0; }

void fn_805D8B90(u8* p) {
    u32* q = *(u32**)(p + 0x38);
    q[2] = q[0];
    q[4] = q[3] = q[0];
}

u32 fn_805D8AB0(u8* p) { return *(u32*)(p + 0x70); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EA838>::Unk_StateMachine(Unk_806EA838*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA838>::setState(const StateFn&, const StateFn&, s32);
