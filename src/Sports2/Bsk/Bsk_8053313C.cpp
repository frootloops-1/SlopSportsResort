// Resort Basketball (bsk) file 0x8053313C-0x80534744: layout holder class, vtables 0x806E1940/0x806E19A8/0x806E1A20/0x806E1A98 (ctor 0x80533FD4).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E1A20 {
public:
    virtual void vf8();
};

extern "C" {

struct Unk_VtAt30 {
    u8 unk0[0x30];
    virtual void vf8();
    virtual void vfC();
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

void fn_8053594C(u8*);
void fn_80535958(u8*);
void fn_80535964(u8*);
void fn_805371E4(u8*);
void fn_8053AB50(u8*);

u8* fn_8053434C(u8* p) { return p + 0x64; }

u8* fn_80534344(u8* p) { return p + 0x64; }

void fn_805342F0(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E1A20>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_80533D20(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xa4)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xa4)))->vfF8();
    }
}

u8 fn_80533D14(u8* p) { return *(u8*)(*(u8**)(p + 0xa4) + 0xd0); }

void fn_80533A80(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vfF8();
    }
}

void fn_80533A78(u8* p) { fn_80535964(*(u8**)(p + 0xac)); }

void fn_80533A70(u8* p) { fn_80535958(*(u8**)(p + 0xac)); }

void fn_80533A68(u8* p) { fn_8053594C(*(u8**)(p + 0xac)); }

u8 fn_80533A40(u8* p) { return *(u8*)(*(u8**)(p + 0xac) + 0xd0); }

void fn_80533A1C(u8* p) { *(u8*)(*(u8**)(p + 0xac) + 0x121) = 1; }

void fn_80533A0C(u8* p) { *(u8*)(*(u8**)(p + 0xac) + 0x121) = 0; }

void fn_80533974(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb0)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb0)))->vfF8();
    }
}

void fn_8053396C(u8* p) { fn_805371E4(*(u8**)(p + 0xb0)); }

void fn_80533960(u8* p, u8 a1) { *(u8*)(*(u8**)(p + 0xb0) + 0x111) = a1; }

u8 fn_80533954(u8* p) { return *(u8*)(*(u8**)(p + 0xb0) + 0xd0); }

void fn_8053331C(u8* p) { fn_8053AB50(*(u8**)(p + 0xb8)); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E1A20>::Unk_StateMachine(Unk_806E1A20*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E1A20>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
