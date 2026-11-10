// Resort Basketball (bsk) file 0x80535D2C-0x80536910: layout holder class, vtables 0x806E1F58/0x806E1FB8/0x806E2030/0x806E20A8 (ctor 0x8053625C).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E2030 {
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

void fn_80534860(u8*);
void fn_80534A38(u8*);
void fn_80534A98(u8*);
void fn_8053529C(u8*);
void fn_80535398(u8*);
void fn_805353A4(u8*);

u8* fn_80536518(u8* p) { return p + 0x64; }

u8* fn_80536510(u8* p) { return p + 0x64; }

void fn_805364BC(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E2030>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_805364B8() {}

void fn_805364B4() {}

void fn_8053611C(u8* p, u32 a1, u32 a2, s32 a3) {
    *(u32*)(p + a3 * 4 + 0x98) = a1;
    *(u32*)(p + a3 * 4 + 0xa0) = a2;
}

void fn_80536054(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xa8)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xa8)))->vfF8();
    }
}

s32 fn_80535FEC() { return 1; }

u8 fn_80535FE0(u8* p) { return *(u8*)(*(u8**)(p + 0xa8) + 0xd0); }

void fn_80535F48(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vfF8();
    }
}

void fn_80535F40(u8* p) { fn_805353A4(*(u8**)(p + 0xac)); }

void fn_80535F38(u8* p) { fn_80535398(*(u8**)(p + 0xac)); }

void fn_80535F30(u8* p) { fn_8053529C(*(u8**)(p + 0xac)); }

u8 fn_80535F10(u8* p) { return *(u8*)(*(u8**)(p + 0xac) + 0xd0); }

void fn_80535E00(u8* p) { fn_80534A98(*(u8**)(p + 0xb0)); }

void fn_80535DF8(u8* p) { fn_80534A38(*(u8**)(p + 0xb0)); }

void fn_80535DF0(u8* p) { fn_80534860(*(u8**)(p + 0xb0)); }

u8 fn_80535DD0(u8* p) { return *(u8*)(*(u8**)(p + 0xb0) + 0xd0); }

void fn_80535DC4(u8* p, u8 a1) { *(u8*)(*(u8**)(p + 0xb0) + 0x11a) = a1; }

u32 fn_80535DB4(u8* p, s32 a1) { return *(u32*)(p + a1 * 4 + 0xb8); }

void fn_80535D2C(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb4)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb4)))->vfF8();
    }
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E2030>::Unk_StateMachine(Unk_806E2030*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E2030>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
