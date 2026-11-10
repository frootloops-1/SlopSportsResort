// Ddg_805CBDF0: Resort Frisbee Dog unit 0x805CBDF0-0x805CCE88 (Resort-only, no Wii Sports twin).
// layout 65200_diskPointCount / 65203_fldCatchPts.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E9A18 {
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
void fn_802A609C(u8*);
void fn_805CC06C(u8*);
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

void fn_805CCB34() {}

void fn_805CCA70() {}

void fn_805CC84C(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_805CC804(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_80277808((u8*)p + 0x94);
    }
}

void fn_805CC7BC(Unk_LytVt30* p) {
    if (!p->vf48()) {
        fn_802777A8((u8*)p + 0x94);
    }
}

void fn_805CC75C(Unk_LytVt30* p) {
    if (fn_8026FF08((u8*)p + 0x94)) {
        p->vf4C();
        ((Unk_Vt94*)((u8*)p + 0x94))->vf70();
    }
}

u8* fn_805CC754(u8* p) { return p + 0x64; }

u8* fn_805CC74C(u8* p) { return p + 0x64; }

void fn_805CC6F8(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E9A18>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_805CC6F0(u8* p) { return p + 0x64; }

u8* fn_805CC6E8(u8* p) { return p + 0x64; }

void fn_805CC460(u8* p) { fn_805CC06C(p); }

void fn_805CBF90() {}

void fn_805CBDFC(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 8 + 0x120) = a3;
    *(u32*)(p + a1 * 8 + 0x124) = a2;
}

void fn_805CBDF0(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->request(1); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E9A18>::Unk_StateMachine(Unk_806E9A18*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E9A18>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
