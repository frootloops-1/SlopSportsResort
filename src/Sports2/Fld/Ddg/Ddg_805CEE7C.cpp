// Ddg_805CEE7C: Resort Frisbee Dog unit 0x805CEE7C-0x805CFBAC (Resort-only, no Wii Sports twin).
// layout 65206_adviceText.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EA2B0 {
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
    virtual u32 vf48();
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
};

void fn_8025EC94(u8*);
u8* fn_8026F6AC(u8*, s32);
void fn_8026FEF0(u8*, s32, s32);
void fn_802700EC(u8*);
void fn_80270194(u8*, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
void fn_8027765C(u8*, u32, s32);
void fn_80277768(u8*);
void fn_802A609C(u8*);
void fn_805CF624(u8*, s32, s32, s32, s32);
extern u8 __ptmf_null[];
extern u8 lbl_806896A0[];
extern u8 lbl_806EA000[];
extern u8 lbl_806EA048[];
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

void fn_805CF860() {}

void fn_805CF804(u8* p) {
    u32 t0 = ((Unk_VtAt30*)(p))->vf48();
    fn_8027765C(p + 0x94, t0, 0);
    fn_80277768(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(u32*)(p + 0xfc));
}

void fn_805CF79C() {}

void fn_805CF578(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_805CF530(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_80277808((u8*)p + 0x94);
    }
}

void fn_805CF4E8(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_802777A8((u8*)p + 0x94);
    }
}

void fn_805CF488(Unk_LytVt30* p) {
    if (fn_8026FF08((u8*)p + 0x94)) {
        p->vf4C();
        ((Unk_Vt94*)((u8*)p + 0x94))->vf70();
    }
}

u8* fn_805CF480(u8* p) { return p + 0x64; }

u8* fn_805CF478(u8* p) { return p + 0x64; }

void fn_805CF424(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806EA2B0>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_805CF41C(u8* p) { return p + 0x64; }

u8* fn_805CF414(u8* p) { return p + 0x64; }

void fn_805CF068(u8* p) {
    fn_802703A8(p + 0x94, lbl_806896A0 + 0xc, lbl_806896A0 + 0x19, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_806896A0 + 0x2a, lbl_806896A0 + 0x2d, 0);
    fn_8027035C(p + 0x94, 1, lbl_806896A0 + 0x38, lbl_806896A0 + 0x2d, 0);
    fn_80270194(p + 0x94, 0, 1);
}

void fn_805CF064() {}

void fn_805CF044(u8* p) {
    if (--*(s32*)(p + 0x104) <= 0) {
        ((Unk_StateMachineBase*)(p + 0x64))->request(1);
    }
}

void fn_805CEFFC(u8* p) {
    fn_8026FEF0(p + 0x94, 0, 1);
    u8* t1 = fn_8026F6AC(p + 0x94, 0);
    fn_8025EC94(t1);
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EA2B0>::Unk_StateMachine(Unk_806EA2B0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA2B0>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
