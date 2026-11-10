// Ddg_805E6F5C: Resort Frisbee Dog unit 0x805E6F5C-0x805E9B70 (Resort-only, no Wii Sports twin).
// disk: WS2_fld_disk, WS2_fld_disk_tail*, WS2_fld_disk_sand_* (vtables 0x806EAC48, 0x806EACB8).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EACB8 {
public:
    virtual void vf8();
};

extern "C" {

void fn_805E6CE8(u8*, u32);

// Deleting destructor of a class without a base destructor.
void* fn_805E9B10(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805E9284(u8* p) { ((Unk_StateMachine<Unk_806EACB8>*)(p + 0xc))->calc(); }

void fn_805E71CC(u8* p, u32 a1, u32 a2) {
    *(u32*)(p + 0x3c) = a1;
    *(u32*)(p + 0x8) = a2;
    fn_805E6CE8(*(u8**)(p + 0x19c), a2);
    ((Unk_StateMachineBase*)(p + 0xc))->request(1);
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EACB8>::Unk_StateMachine(Unk_806EACB8*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EACB8>::setState(const StateFn&, const StateFn&, s32);
