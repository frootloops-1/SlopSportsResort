// Ddg_805CCE88: Resort Frisbee Dog unit 0x805CCE88-0x805CDABC (Resort-only, no Wii Sports twin).
// layout 65205_fldBbtnText.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E9DA0 {
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
};

void fn_802700EC(u8*);
void fn_80270194(u8*, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
void fn_802A609C(u8*);
void fn_805CD4DC(u8*);
void fn_805CD588(u8*, s32, s32, s32, s32);
extern u8 __ptmf_null[];
extern u8 lbl_806894E0[];
extern u8 lbl_806E9B18[];
extern u8 lbl_806E9B24[];
extern u8 lbl_806E9B30[];
struct Unk_LytVt30 {
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
    virtual BOOL vf48();
    virtual void vf4C();
};
void fn_802777A8(u8*);
void fn_80277808(u8*);
struct Unk_Vt94 {
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
};
BOOL fn_8026FF08(u8*);
void fn_8027765C(u8*, u8, s32);
void fn_8026FFE0(u8*);

void fn_805CD768() {}

void fn_805CD700() {}

void fn_805CD4DC(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_805CD430(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_805CD3E8(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_80277808((u8*)p + 0x94);
    }
}

void fn_805CD3A0(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_802777A8((u8*)p + 0x94);
    }
}

void fn_805CD340(Unk_LytVt30* p) {
    if (fn_8026FF08((u8*)p + 0x94)) {
        p->vf4C();
        ((Unk_Vt94*)((u8*)p + 0x94))->vf70();
    }
}

u8* fn_805CD338(u8* p) { return p + 0x64; }

u8* fn_805CD330(u8* p) { return p + 0x64; }

void fn_805CD2DC(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E9DA0>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_805CD2D4(u8* p) { return p + 0x64; }

u8* fn_805CD2CC(u8* p) { return p + 0x64; }

u8* fn_805CD0A0(u8* p) {
    fn_805CD588(p, 2, 3, 0, 0);
    *(u8**)(p + 0x18) = lbl_806E9B30 + 0x8;
    *(u8**)(p + 0x30) = lbl_806E9B30;
    *(u8**)(p + 0x94) = lbl_806E9B30 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E9B30 + 0x88;
    ((Unk_StateMachine<Unk_806E9DA0>*)(p + 0x64))->setState(*(Unk_StateMachine<Unk_806E9DA0>::StateFn*)__ptmf_null, *(Unk_StateMachine<Unk_806E9DA0>::StateFn*)lbl_806E9B18, 0);
    ((Unk_StateMachine<Unk_806E9DA0>*)(p + 0x64))->setState(*(Unk_StateMachine<Unk_806E9DA0>::StateFn*)__ptmf_null, *(Unk_StateMachine<Unk_806E9DA0>::StateFn*)lbl_806E9B24, 1);
    *(u32*)(p + 0x104) = 0;
    *(u8*)(p + 0x100) = 0;
    return p;
}

void fn_805CD024(u8* p) {
    *(u8*)(p + 0x100) = *(u8*)(p + 0x100) | 0x8;
    fn_805CD4DC(p);
}

void fn_805CCF80(u8* p) {
    fn_802703A8(p + 0x94, lbl_806894E0, lbl_806894E0 + 0xd, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_806894E0 + 0x1f, lbl_806894E0 + 0x22, 0);
    fn_8027035C(p + 0x94, 1, lbl_806894E0 + 0x2d, lbl_806894E0 + 0x37, 0);
    fn_8027035C(p + 0x94, 2, lbl_806894E0 + 0x45, lbl_806894E0 + 0x22, 0);
    fn_80270194(p + 0x94, 0, 2);
}

void fn_805CCF7C() {}

void fn_805CCE88(u8* p) {
    *(u8*)(p + 0x100) = *(u8*)(p + 0x100) | 0x1;
    ((Unk_StateMachineBase*)(p + 0x64))->request(0);
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E9DA0>::Unk_StateMachine(Unk_806E9DA0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E9DA0>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
