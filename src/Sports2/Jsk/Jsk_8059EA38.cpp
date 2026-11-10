// Resort Power Cruising (jsk) file 0x8059EA38-0x805A0AFC: jsk HUD manager: vtables 0x806E6D18/0x806E6D48/0x806E6DC0, drives the jsk layouts.
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E6DC0 {
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

void fn_80374B3C(u8*);

u8* fn_805A0704(u8* p) { return p + 0x64; }

u8* fn_805A06FC(u8* p) { return p + 0x64; }

void fn_8059F7B8(u8* p, u32 v) { *(u32*)(p + 0xec) = v; }

void fn_8059EB20(u8* p) { (*(Unk_V30**)(p + 0xbc))->vfF4(); }

void fn_8059EB0C(u8* p) { (*(Unk_V30**)(p + 0xbc))->vfF8(); }

void fn_8059EAF8(u8* p) { (*(Unk_V30**)(p + 0xbc))->vf48(); }

void fn_8059EAF0(u8* p) { fn_80374B3C(*(u8**)(p + 0xe4)); }

u8 fn_8059EAC0(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0x11d); }

u8 fn_8059EAB4(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0x11e); }

u8 fn_8059EAA8(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0xd0); }

void fn_8059EA94(u8* p) { (*(Unk_V30**)(p + 0xe4))->vf48(); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E6DC0>::Unk_StateMachine(Unk_806E6DC0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E6DC0>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806E6DC0>::calc();
