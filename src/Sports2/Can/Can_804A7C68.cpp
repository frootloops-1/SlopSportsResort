// Canoeing (Resort-only), .text 0x804A7C68-0x804A8754: layout draw manager ("LayoutDrawMgr"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806DC238 {
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

void fn_80277724(u8*);
u8 fn_804A7CE8(u8*, u32, u32, u32);
void fn_804B8B10(u8*);

u8* fn_804A835C(u8* p) { return p + 0x64; }

u8* fn_804A8354(u8* p) { return p + 0x64; }

void fn_804A8300(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806DC238>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_804A80A8(u8* p) { fn_80277724(p + 0x94); }

void fn_804A7F68(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 4 + 0x9c) = a2;
    *(u32*)(p + a1 * 4 + 0xac) = a3;
}

void fn_804A7F58(u8* p, u32 a1) {
    *(u32*)(p + 0xcc) = a1;
    *(u8*)(p + 0xd0) = 1;
}

void fn_804A7EF0(u8* p) {
    ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vfF4();
    ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF4();
    *(u32*)(*(u8**)(p + 0xc0) + 0x114) = 50;
    ((Unk_StateMachineBase*)(p + 0x64))->request(0);
}

u8 fn_804A7ECC(const u8* p) {
    if (*(*(u8**)(p + 0xbc) + 0xd0) == 0) {
        return 0;
    }
    return *(*(u8**)(p + 0xc0) + 0xd0);
}

void fn_804A7E7C(u8* p) {
    ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vfF8();
    ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF8();
}

void fn_804A7E34(u8* p, u32 a1, u32 a2) {
    *(u32*)(*(u8**)(p + 0xbc) + 0x104) = a1;
    *(u32*)(*(u8**)(p + 0xc0) + 0x110) = a2;
    *(u8*)(p + 0xd2) = 0;
    u8 t0 = fn_804A7CE8(p, a1, a2, *(u32*)(p + 0xc0));
    *(u8*)(p + 0xd1) = t0;
}

void fn_804A7E2C(u8* p) { fn_804B8B10(*(u8**)(p + 0xc8)); }

u8 fn_804A7E20(u8* p) { return *(u8*)(*(u8**)(p + 0xc8) + 0xd0); }

void fn_804A7E0C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc8)))->vfF8(); }

void fn_804A7DF8(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc8)))->vf48(); }

u32 fn_804A7D9C(u8* p) { return *(u32*)(p + 0xc4); }

void fn_804A7CDC(u8* p) { *(u8*)(p + 0xd1) = 0; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806DC238>::Unk_StateMachine(Unk_806DC238*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806DC238>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
