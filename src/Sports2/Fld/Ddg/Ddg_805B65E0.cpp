// Ddg_805B65E0: Resort Frisbee Dog unit 0x805B65E0-0x805B7968 (Resort-only, no Wii Sports twin).
// scene helpers + a class with vtables 0x806E8790/0x806E87F0 and a state-machine template instance (0x806E8810).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E87F0 {
public:
    virtual void vf8();
};

extern "C" {

struct Unk_VtAt0 {
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
};

void fn_80348868(u8*);
void fn_805D2094(u8*);
void fn_805D34B8(u8*);
void fn_805D3BB8(u8*);
void fn_805D3BF0(u8*);

void fn_802ABB5C(u8*, s32);

// Deleting destructor of a class without a base destructor.
void* fn_805B790C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805B7908() {}

void fn_805B7058(u8* p, s32 a1) {
    if (a1 != *(s32*)(p + 0xe8)) {
        *(s32*)(p + 0xe8) = a1;
        *(s32*)(*(u8**)(p + 0x80) + 0x3c) = a1;
    }
}

void fn_805B6FEC(u8* p) {
    *(u16*)(*(u8**)(p + 0xf8) + 0x6c) = *(u16*)(*(u8**)(p + 0xf8) + 0x6c) | 0x10;
    ((Unk_StateMachine<Unk_806E87F0>*)(p + 0x2c))->calc();
    fn_805D3BF0(*(u8**)(p + 0x7c));
    fn_805D2094(*(u8**)(p + 0x80));
    ((Unk_VtAt0*)(*(u8**)(p + 0x84)))->vf20();
    *(u32*)(p + 0x78) = 0;
}

void fn_805B6FA0() {}

void fn_805B6F3C() {}

void fn_805B6F38() {}

void fn_805B6EDC() {}

void fn_805B6ED8() {}

void fn_805B6C98() {}

void fn_805B6C84(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x84)))->vf30(); }

void fn_805B6C38(u8* p) {
    fn_80348868(*(u8**)(p + 0x70));
    fn_805D3BB8(*(u8**)(p + 0x7c));
    ((Unk_VtAt0*)(*(u8**)(p + 0x84)))->vf34();
}

void fn_805B6618() {}

void fn_805B65FC(u8* p) {
    if (*(u8*)(p + 0x74) != 0) {
        fn_802ABB5C(*(u8**)(p + 0xfc), 1);
    }
}

void fn_805B65E8(u8* p) {
    *(u16*)(*(u8**)(p + 0xf8) + 0x6c) = *(u16*)(*(u8**)(p + 0xf8) + 0x6c) & ~0x10;
}

void fn_805B65E0(u8* p) { fn_805D34B8(*(u8**)(p + 0x7c)); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E87F0>::Unk_StateMachine(Unk_806E87F0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E87F0>::setState(const StateFn&, const StateFn&, s32);
