// Ddg_805EB33C: Resort Frisbee Dog unit 0x805EB33C-0x805EC01C (Resort-only, no Wii Sports twin).
// layout 65207_fldZoomBtnText.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EB178 {
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
void fn_805EBAE8(u8*, s32, s32, s32, s32);
extern u8 __ptmf_null[];
extern u8 lbl_80689E00[];
extern u8 lbl_806EAEE0[];
extern u8 lbl_806EAF08[];
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

void fn_805EBCC8() {}

void fn_805EBC60() {}

void fn_805EB9E0(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_805EB998(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_80277808((u8*)p + 0x94);
    }
}

void fn_805EB950(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_802777A8((u8*)p + 0x94);
    }
}

void fn_805EB8F0(Unk_LytVt30* p) {
    if (fn_8026FF08((u8*)p + 0x94)) {
        p->vf4C();
        ((Unk_Vt94*)((u8*)p + 0x94))->vf70();
    }
}

u8* fn_805EB8E8(u8* p) { return p + 0x64; }

u8* fn_805EB8E0(u8* p) { return p + 0x64; }

void fn_805EB88C(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806EB178>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_805EB884(u8* p) { return p + 0x64; }

u8* fn_805EB87C(u8* p) { return p + 0x64; }

void fn_805EB508(u8* p) {
    fn_802703A8(p + 0x94, lbl_80689E00 + 0xe, lbl_80689E00 + 0x1b, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_80689E00 + 0x30, lbl_80689E00 + 0x33, 0);
    fn_8027035C(p + 0x94, 1, lbl_80689E00 + 0x3e, lbl_80689E00 + 0x4b, 0);
    fn_8027035C(p + 0x94, 2, lbl_80689E00 + 0x59, lbl_80689E00 + 0x4b, 0);
    fn_8027035C(p + 0x94, 3, lbl_80689E00 + 0x67, lbl_80689E00 + 0x33, 0);
    fn_80270194(p + 0x94, 0, 3);
}

void fn_805EB504() {}

void fn_805EB3AC(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->request(0); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EB178>::Unk_StateMachine(Unk_806EB178*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EB178>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
