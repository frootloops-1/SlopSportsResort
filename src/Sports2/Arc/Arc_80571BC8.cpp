// Arc_80571BC8: Resort Archery unit 0x80571BC8-0x8057420C (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E42C8 {
public:
    virtual void vf8();
};

extern "C" {

void fn_8057750C(void* p);
void fn_80577E54(void* p);
void fn_8057B43C(void* p);
void fn_8057BCA8(void* p);
void fn_8057BCB4(void* p);
void fn_8057C02C(void* p);
void fn_8057C070(void* p);
void fn_8057C0F4(void* p);
void fn_8057C154(void* p);

u8* fn_80573D48(u8* p) { return p + 0x64; }

u8* fn_80573D40(u8* p) { return p + 0x64; }

void fn_80572D7C(u8* p) { fn_80577E54(*(u8**)(p + 0xd0)); }

void fn_80572CA4(u8* p) { fn_8057750C(*(u8**)(p + 0xd4)); }

void fn_805724D0(u8* p) { fn_8057B43C(*(u8**)(p + 0xe0)); }

void fn_805723D0(u8* p) { fn_8057BCB4(*(u8**)(p + 0xe4)); }

void fn_805723C8(u8* p) { fn_8057BCA8(*(u8**)(p + 0xe4)); }

void fn_80572384(u8* p) { fn_8057C154(*(u8**)(p + 0xe8)); }

void fn_80572338(u8* p) { fn_8057C0F4(*(u8**)(p + 0xe8)); }

void fn_80572330(u8* p) { fn_8057C070(*(u8**)(p + 0xe8)); }

void fn_80572328(u8* p) { fn_8057C02C(*(u8**)(p + 0xe8)); }

void fn_80572198(u8* p) { *(u8*)(p + 0x110) = 0x1; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E42C8>::Unk_StateMachine(Unk_806E42C8*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E42C8>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806E42C8>::calc();
