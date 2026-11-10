// Canoeing (Resort-only), .text 0x804BD6BC-0x804BE8B8: layout/controller manager ("ControllerManager", "StaticMem", "LayoutDrawMgr"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806DDA60 {
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

void fn_804BD6C4(u8*);
void fn_804C189C(u8*, u32, s32);
void fn_804C25B0(u8*);
void fn_804C3350(u8*, u32);

u8* fn_804BE4C0(u8* p) { return p + 0x64; }

u8* fn_804BE4B8(u8* p) { return p + 0x64; }

void fn_804BE464(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806DDA60>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_804BDF84(u8* p) { fn_804BD6C4(p); }

void fn_804BDF70(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 4 + 0x9c) = a2;
    *(u32*)(p + a1 * 4 + 0xac) = a3;
}

void fn_804BDF68(u8* p) { fn_804C25B0(*(u8**)(p + 0xc0)); }

void fn_804BDF54(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vf48(); }

void fn_804BDF30(u8* p) {
    for (s32 i = 0; i < 4; i++) {
        p[0x11c + i] = 0;
    }
}

void fn_804BDF24(u8* p, s32 i, u8 v) { p[0x11c + i] = v; }

void fn_804BDF0C(u8* p, s32 a1, u32 a2) { fn_804C3350(*(u8**)(p + a1 * 4 + 0xc4), a2); }

void fn_804BDF04(u8* p, u32 a1) { *(u32*)(p + 0x108) = a1; }

BOOL fn_804BDC84(const u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0xec); i++) {
        if (((u8**)(p + 0xd4))[i][0xd0] == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void fn_804BDAFC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe4)))->vfF4(); }

void fn_804BDAF0(u8* p, u32 a1) { fn_804C189C(*(u8**)(p + 0xe4), a1, 1); }

u8 fn_804BDAE4(u8* p) { return *(u8*)(*(u8**)(p + 0xe4) + 0xd0); }

void fn_804BDAD0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe4)))->vfF8(); }

void fn_804BDABC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe4)))->vf48(); }

void fn_804BD6C0() {}

void fn_804BD6BC() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806DDA60>::Unk_StateMachine(Unk_806DDA60*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806DDA60>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
