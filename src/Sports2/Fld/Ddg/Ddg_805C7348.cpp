// Ddg_805C7348: Resort Frisbee Dog unit 0x805C7348-0x805CA164 (Resort-only, no Wii Sports twin).
// layout manager / point text (bvN_miss_00, N_pts*_00; vtables 0x806E9048, 0x806E9120, 0x806E9198).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E9198 {
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

void fn_80277724(u8*);
void fn_80370E0C(u8*);
void fn_805CAE28(u8*);
void fn_805CAE84(u8*);
void fn_805CAEC8(u8*, u32, s32);
void fn_805CAF0C(u8*);
void fn_805CAF70(u8*);
void fn_805CAFC4(u8*);
void fn_805CF0F4(u8*);
void fn_805EA20C(u8*, u32);
void fn_805EB5C4(u8*);

struct Unk_Lyt30 {
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
void fn_8027765C(u8*, u8, s32);
void fn_8026FFE0(u8*);

u8* fn_805C9D6C(u8* p) { return p + 0x64; }

u8* fn_805C9D64(u8* p) { return p + 0x64; }

void fn_805C9D10(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806E9198>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_805C9CC0(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_805C9C70(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_805C9C20(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_805C9BD0(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_805C9414(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc8)))->vf48(); }

void fn_805C93F0(u8* p, u32 a1, u32 a2, u32 a3, u32 a4) {
    *(u32*)(p + 0xe4) = a1;
    *(u32*)(p + 0xe0) = a3;
    *(u32*)(p + 0xe8) = a2;
    *(u32*)(p + 0xec) = a4;
    *(u32*)(p + 0xfc) = 0;
    ((Unk_StateMachineBase*)(p + 0x64))->request(7);
}

void fn_805C93E4(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->isState(0); }

u32 fn_805C93D0(u8* p, s32 i) { return *(u32*)(*(u8**)(p + 0xa4) + i * 0x58 + 0x184); }

void fn_805C930C(u8* p) { fn_805CAFC4(*(u8**)(p + 0xa4)); }

u32 fn_805C92F8(u8* p, s32 i) { return *(u32*)(*(u8**)(p + 0xa4) + i * 0x58 + 0x184); }

void fn_805C92F0(u8* p) { fn_805CAF70(*(u8**)(p + 0xa4)); }

void fn_805C92E8(u8* p) { fn_805CAF0C(*(u8**)(p + 0xa4)); }

void fn_805C92E0(u8* p) { fn_805CAE84(*(u8**)(p + 0xa4)); }

void fn_805C92D8(u8* p) { fn_805CAE28(*(u8**)(p + 0xa4)); }

void fn_805C92CC(u8* p, u32 a1) { fn_805CAEC8(*(u8**)(p + 0xa4), a1, 2); }

void fn_805C92C0(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->request(3); }

u32 fn_805C92B0(u8* p) { return *(u8*)(*(u8**)(p + 0x9c) + 0x100) & 1; }

void fn_805C929C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0x9c)))->vf48(); }

void fn_805C9288(u8* p) {
    *(u8*)(*(u8**)(p + 0x9c) + 0x100) = *(u8*)(*(u8**)(p + 0x9c) + 0x100) | 0x10;
}

u32 fn_805C9278(u8* p) { return (*(u8*)(*(u8**)(p + 0x9c) + 0x100) >> 1) & 1; }

void fn_805C9108(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xa4)))->vf48(); }

void fn_805C90E4(u8* p) {
    Unk_Lyt30* q = *(Unk_Lyt30**)(p + 0xa4);
    if (*(u8*)((u8*)q + 0xd0) != 0) {
        q->vfF8();
    }
}

void fn_805C90A8(u8* p) {
    ((Unk_StateMachineBase*)(p + 0x64))->request(5);
    *(u8*)(p + 0x101) = 0;
}

void fn_805C9084(u8* p) {
    Unk_Lyt30* q = *(Unk_Lyt30**)(p + 0xa8);
    if (*(u8*)((u8*)q + 0xd0) != 0) {
        q->vfF8();
    }
}

u8 fn_805C9078(u8* p) { return *(u8*)(*(u8**)(p + 0xa8) + 0xd0); }

u8 fn_805C906C(u8* p) { return *(u8*)(*(u8**)(p + 0xa8) + 0xd3); }

u8 fn_805C9060(u8* p) { return *(u8*)(*(u8**)(p + 0xa8) + 0xd1); }

void fn_805C904C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xa8)))->vf48(); }

void fn_805C8F6C(u8* p) { fn_805CF0F4(*(u8**)(p + 0xac)); }

void fn_805C8F58(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vf48(); }

void fn_805C8B18(u8* p) { fn_805EB5C4(*(u8**)(p + 0xa0)); }

void fn_805C8A60(u8* p, s32 a1, u32 a2) { *(u32*)(*(u8**)(p + 0xb0) + a1 * 4 + 0x2a4) = a2; }

u32 fn_805C8A4C(u8* p, s32 a1) { return *(u32*)(*(u8**)(p + 0xb0) + a1 * 4 + 0x2a4); }

void fn_805C8A38(u8* p, s32 a1) {
    fn_805EA20C(*(u8**)(p + 0xb0), *(u32*)(*(u8**)(p + 0xb0) + a1 * 4 + 0x2a4));
}

void fn_805C88EC(u8* p) { fn_80370E0C(*(u8**)(p + 0xcc)); }

void fn_805C88C8(u8* p) {
    Unk_Lyt30* q = *(Unk_Lyt30**)(p + 0xcc);
    if (*(u8*)((u8*)q + 0xd0) != 0) {
        q->vfF8();
    }
}

void fn_805C88B4(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xcc)))->vf48(); }

void fn_805C87FC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xd4)))->vf48(); }

BOOL fn_805C8728(u8* p) {
    u8* q = *(u8**)(p + 0xd0);
    return *(u8*)(q + 0xd0) != 0 && *(u8*)(q + 0x11d) != 0;
}

BOOL fn_805C8700(u8* p) {
    u8* q = *(u8**)(p + 0xd0);
    return *(u8*)(q + 0xd0) != 0 && *(u8*)(q + 0x11e) != 0;
}

void fn_805C86DC(u8* p) {
    Unk_Lyt30* q = *(Unk_Lyt30**)(p + 0xd0);
    if (*(u8*)((u8*)q + 0xd0) != 0) {
        q->vfF8();
    }
}

void fn_805C86C8(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xd0)))->vf48(); }

void fn_805C864C(u8* p) {
    Unk_Lyt30* q = *(Unk_Lyt30**)(p + 0xbc);
    if (*(u8*)((u8*)q + 0xd0) != 0) {
        q->vfF8();
    }
}

u8 fn_805C8640(u8* p) { return *(u8*)(*(u8**)(p + 0xbc) + 0xd0); }

void fn_805C8634(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->request(9); }

void fn_805C8624(u8* p) { ((Unk_VtAt30*)(p))->vf48(); }

void fn_805C8014(u8* p) { fn_80277724(p + 0x94); }

void fn_805C800C(u8* p) { fn_80277724(p + 0x94); }

void fn_805C8004(u8* p) { fn_80277724(p + 0x94); }

void fn_805C7FFC(u8* p) { fn_80277724(p + 0x94); }

void fn_805C7FF4(u8* p) { fn_80277724(p + 0x94); }

void fn_805C7AE8(u8* p, u32 a1, u32 a2, s32 a3) {
    *(u32*)(p + a3 * 4 + 0x104) = a1;
    *(u32*)(p + a3 * 4 + 0x114) = a2;
}

void fn_805C7AE4() {}

void fn_805C7AE0() {}

void fn_805C7AD4(u8* p) { *(u8*)(p + 0x100) = 0; }

void fn_805C776C() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E9198>::Unk_StateMachine(Unk_806E9198*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E9198>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
