// Ddg_805D51B8: Resort Frisbee Dog unit 0x805D51B8-0x805D89E8 (Resort-only, no Wii Sports twin).
// avatar/disk tail (WS2_fld_disk_tail%s, head/chest/wrist joints; vtables 0x806EA560, 0x806EA5F0).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EA5F0 {
public:
    virtual void vf8();
};

extern "C" {

void fn_805B65FC(u8*);
void fn_805B6C38(u8*);

void fn_805D8898() {}

void fn_805D754C(u8* p) { fn_805B6C38(p + 0x98); }

void fn_805D71A8(u8* p) { fn_805B65FC(p + 0x98); }

void fn_805D6C24() {}

void fn_805D60EC(u8* p) {
    ((Unk_StateMachineBase*)(p + 0x1a0))->request(2);
    ((Unk_StateMachineBase*)(p + 0xc4))->requestIfIdle(0);
}

BOOL fn_805D5F7C(u8* p, u32 m) { return (*(u16*)(p + 0x44) & m) == 0; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EA5F0>::Unk_StateMachine(Unk_806EA5F0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA5F0>::setState(const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806EA5F0>::calc();
