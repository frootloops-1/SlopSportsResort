// Arc_80549568: Resort Archery unit 0x80549568-0x8055567C (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E3490 {
public:
    virtual void vf8();
};

extern "C" {

extern u8 lbl_807D4FF0[];
extern void* lbl_806F5B30;
extern void* lbl_806F5B34;

void fn_8055424C(u8* p) { *(u32*)(p + 0x170) = 0x0; }

void fn_80550B4C() {}

void fn_80550B48() {}

void fn_80550B10() {}

u8* fn_805509D8(u8* p) { return *(u8**)(p + 0x38) + 0x8; }

u8* fn_805509CC(u8* p) { return *(u8**)(p + 0x38) + 0x8; }

u8* fn_805509C0(u8* p) { return *(u8**)(p + 0x38) + 0x14; }

u8* fn_805509B4(u8* p) { return *(u8**)(p + 0x38) + 0x20; }

void fn_8054D610() {}

void fn_8054CDD0() {}

void fn_8054CD68() {}

void fn_8054CD58() {
    lbl_806F5B30 = NULL;
    lbl_806F5B34 = NULL;
}

void fn_8054CB10() {}

void fn_8054CB0C() {}

void fn_8054CB08() {}

void fn_8054C73C() {}

void fn_8054C738() {}

void fn_8054C698() {}

void fn_8054C5DC() {}

f32 fn_8054C294(u8* p) { return *(f32*)(p + 0x2ec); }

void fn_8054A1B4(u8* p, u32 v) { *(u32*)(p + 0x0) = v; }

void fn_80549D2C() {}

void fn_80549D28() {}

void fn_80549D24() {}

void fn_80549D20() {}

void fn_80549D1C() {}

void fn_80549D18() {}

void* fn_8054962C() { return lbl_807D4FF0; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template void Unk_StateMachine<Unk_806E3490>::calc();
template void Unk_StateMachine<Unk_806E3490>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template Unk_StateMachine<Unk_806E3490>::Unk_StateMachine(Unk_806E3490*, s32, EGG::Heap*);
