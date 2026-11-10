// Resort Wakeboarding (wkb) file 0x805A568C-0x805A673C: wkb HUD manager: vtables 0x806E7038/0x806E7010/0x806E70C4, drives the wkb layouts.
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E70B0 {
public:
    virtual void vf8();
};

// placeholder for an object called through its vtable (vptr at 0x30, slot = offset in the vtable)
struct Unk_Pad30 {
    u8 pad[0x30];
};

struct Unk_V30 : Unk_Pad30 {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6C();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8C();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98();
    virtual void vf9C();
    virtual void vfA0();
    virtual void vfA4();
    virtual void vfA8();
    virtual void vfAC();
    virtual void vfB0();
    virtual void vfB4();
    virtual void vfB8();
    virtual void vfBC();
    virtual void vfC0();
    virtual void vfC4();
    virtual void vfC8();
    virtual void vfCC();
    virtual void vfD0();
    virtual void vfD4();
    virtual void vfD8();
    virtual void vfDC();
    virtual void vfE0();
    virtual void vfE4();
    virtual void vfE8();
    virtual void vfEC();
    virtual void vfF0();
    virtual void vfF4();
    virtual void vfF8();
};

extern "C" {

void fn_805A9F08(u8*);
void fn_805AA2F0(u8*);
void fn_805B2D7C(u8*);
void fn_805B3184(u8*);
void fn_805B32F4(u8*);

u8* fn_805A6344(u8* p) { return p + 0x64; }

u8* fn_805A633C(u8* p) { return p + 0x64; }

void fn_805A5B80(u8* p) { fn_805AA2F0(*(u8**)(p + 0xc0)); }

void fn_805A5B78(u8* p) { fn_805AA2F0(*(u8**)(p + 0xc0)); }

void fn_805A5B70(u8* p) { fn_805A9F08(*(u8**)(p + 0xc0)); }

u8 fn_805A5AE0(u8* p) { return *(u8*)(*(u8**)(p + 0xcc) + 0x11e); }

void fn_805A5ACC(u8* p) { (*(Unk_V30**)(p + 0xd8))->vfF4(); }

void fn_805A5AB8(u8* p) { (*(Unk_V30**)(p + 0xd8))->vfF8(); }

void fn_805A5AB0(u8* p) { fn_805B32F4(*(u8**)(p + 0xd8)); }

void fn_805A5AA8(u8* p) { fn_805B3184(*(u8**)(p + 0xdc)); }

void fn_805A5A94(u8* p) { (*(Unk_V30**)(p + 0xdc))->vf48(); }

void fn_805A5A80(u8* p) { (*(Unk_V30**)(p + 0xdc))->vf4C(); }

void fn_805A5A50(u8* p) { (*(Unk_V30**)(p + 0xe0))->vfF8(); }

void fn_805A5A48(u8* p) { fn_805B2D7C(*(u8**)(p + 0xe0)); }

u8 fn_805A5A30(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0x112); }

u8 fn_805A5A24(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0x113); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E70B0>::Unk_StateMachine(Unk_806E70B0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E70B0>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806E70B0>::calc();
