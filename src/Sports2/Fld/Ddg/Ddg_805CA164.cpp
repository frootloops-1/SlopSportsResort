// Ddg_805CA164: Resort Frisbee Dog unit 0x805CA164-0x805CAE14 (Resort-only, no Wii Sports twin).
// layout 65202_fldCatchText (WS2_game_fld).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E9508 {
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

void fn_802700EC(u8*);
void fn_80270194(u8*, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
void fn_8027765C(u8*, u32, s32);
void fn_80277768(u8*);
void fn_802A609C(u8*);
void fn_805CA88C(u8*, s32, s32, s32, s32);
extern u8 __ptmf_null[];
extern u8 lbl_80689170[];
extern u8 lbl_806E9250[];
extern u8 lbl_806E929C[];
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

void fn_805CAAC8() {}

void fn_805CAA6C(u8* p) {
    u32 t0 = ((Unk_VtAt30*)(p))->vf48();
    fn_8027765C(p + 0x94, t0, 0);
    fn_80277768(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(u32*)(p + 0xfc));
}

void fn_805CAA04() {}

void fn_805CA7E0(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_805CA798(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_80277808((u8*)p + 0x94);
    }
}

void fn_805CA750(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_802777A8((u8*)p + 0x94);
    }
}

void fn_805CA6F0(Unk_LytVt30* p) {
    if (fn_8026FF08((u8*)p + 0x94)) {
        p->vf4C();
        ((Unk_Vt94*)((u8*)p + 0x94))->vf70();
    }
}

u8* fn_805CA6E8(u8* p) { return p + 0x64; }

u8* fn_805CA6E0(u8* p) { return p + 0x64; }

void fn_805CA68C(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E9508>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_805CA684(u8* p) { return p + 0x64; }

u8* fn_805CA67C(u8* p) { return p + 0x64; }

void fn_805CA2E8(u8* p) {
    fn_802703A8(p + 0x94, lbl_80689170 + 0x54, lbl_80689170 + 0x61, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_80689170 + 0x74, lbl_80689170 + 0x77, 0);
    fn_8027035C(p + 0x94, 1, lbl_80689170 + 0x82, lbl_80689170 + 0x77, 0);
    fn_80270194(p + 0x94, 0, 1);
}

void fn_805CA2E4() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E9508>::Unk_StateMachine(Unk_806E9508*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E9508>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
