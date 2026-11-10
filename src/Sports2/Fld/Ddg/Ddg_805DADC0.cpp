// Ddg_805DADC0: Resort Frisbee Dog unit 0x805DADC0-0x805DC06C (Resort-only, no Wii Sports twin).
// class with vtables 0x806EA898/0x806EA948.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EA948 {
public:
    virtual void vf8();
};

extern "C" {

bool fn_805DC05C(u8* p, s32 state) { return ((Unk_StateMachineBase*)(p + 0x4))->isState(state); }

// Deleting destructor of a class without a base destructor.
void* fn_805DC01C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805DBAC0(u8* p) { ((Unk_StateMachine<Unk_806EA948>*)(p + 0x4))->calc(); }

void fn_805DBABC() {}

void fn_805DBAB0(u8* p) { ((Unk_StateMachineBase*)(p + 0x4))->request(*(u32*)(p + 0x40)); }

void fn_805DB284(u8* p) {
    u32* q = *(u32**)(p + 0x3c);
    q[2] = q[0];
    q[4] = q[3] = q[0];
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EA948>::Unk_StateMachine(Unk_806EA948*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA948>::setState(const StateFn&, const StateFn&, s32);
