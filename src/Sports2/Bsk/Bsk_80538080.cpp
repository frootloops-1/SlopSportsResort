// Resort Basketball (bsk) file 0x80538080-0x80539324: layout holder class, vtables 0x806E24C0/0x806E2500/0x806E2578/0x806E25F0 (ctor 0x80538BA0).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E2578 {
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

void fn_80353714(u8*, s32);
void fn_8053B084(u8*);
void fn_8053B218(u8*);
void fn_8053B244(u8*);
void fn_8053B254(u8*);
void fn_8053B2A4(u8*);
void fn_8053B3EC(u8*);
void fn_8053B410(u8*);

u8* fn_80538F2C(u8* p) { return p + 0x64; }

u8* fn_80538F24(u8* p) { return p + 0x64; }

void fn_80538ED0(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E2578>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_80538ECC() {}

void fn_80538EC8() {}

void fn_805389A0(u8* p, u32 a1, u32 a2, s32 a3) {
    *(u32*)(p + a3 * 4 + 0x98) = a1;
    *(u32*)(p + a3 * 4 + 0xa8) = a2;
}

void fn_80538860(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb8)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xb8)))->vfF8();
    }
}

void fn_805386D8(u8* p) { fn_8053B410(*(u8**)(p + 0xc4)); }

void fn_805386D0(u8* p) { fn_8053B244(*(u8**)(p + 0xc4)); }

void fn_805384BC(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vfF8();
    }
}

void fn_80538348(u8* p) { fn_8053B3EC(*(u8**)(p + 0xc4)); }

void fn_80538340(u8* p) { fn_8053B218(*(u8**)(p + 0xc4)); }

void fn_805382FC(u8* p) {
    fn_8053B084(*(u8**)(p + 0xc0));
    ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF4();
}

void fn_805382CC(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF8();
    }
}

u8 fn_805382C0(u8* p) { return *(u8*)(*(u8**)(p + 0xc0) + 0xd0); }

void fn_805382B4(u8* p, u8 a1) { *(u8*)(*(u8**)(p + 0xc4) + 0x110) = a1; }

void fn_80538108(u8* p, u32 a1) {
    if (a1 != 0) {
        ((Unk_VtAt30*)(*(u8**)(p + 0xc8)))->vf4C();
    } else {
        ((Unk_VtAt30*)(*(u8**)(p + 0xc8)))->vfF8();
    }
}

void fn_805380C4(u8* p) { fn_80353714(*(u8**)(p + 0xcc), 0); }

u8 fn_805380B8(u8* p) { return *(u8*)(*(u8**)(p + 0xcc) + 0x112); }

void fn_805380B0(u8* p) { fn_8053B2A4(*(u8**)(p + 0xc4)); }

void fn_805380A8(u8* p) { fn_8053B254(*(u8**)(p + 0xc4)); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E2578>::Unk_StateMachine(Unk_806E2578*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E2578>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
