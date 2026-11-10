// Canoeing (Resort-only), .text 0x804BE8B8-0x804BFB30: layout/controller manager (second copy). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806DDBD0 {
public:
    virtual void vf8();
};

extern "C" {

BOOL fn_802EDC9C(u8* p);
void fn_80353714(u8* p, s32 a, f32 f);
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

void fn_80349B74(u8*, s32);
void fn_8035144C(u8*);
void fn_80351528(u8*);
void fn_80374B3C(u8*);
void fn_804B7328(u8*);
void fn_804BB088(u8*);
void fn_804BB430(u8*);
void fn_804BB618(u8*);

u8* fn_804BF738(u8* p) { return p + 0x64; }

u8* fn_804BF730(u8* p) { return p + 0x64; }

void fn_804BF6DC(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806DDBD0>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

void fn_804BEEEC(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 4 + 0x9c) = a2;
    *(u32*)(p + a1 * 4 + 0xac) = a3;
}

u8 fn_804BEE50(u8* p) { return *(u8*)(*(u8**)(p + 0xbc) + 0xd0); }

void fn_804BEE3C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vf48(); }

void fn_804BEE34(u8* p) { fn_80351528(*(u8**)(p + 0xbc)); }

void fn_804BEE2C(u8* p) { fn_8035144C(*(u8**)(p + 0xbc)); }

void fn_804BEE24(u8* p) { fn_804B7328(*(u8**)(p + 0xe0)); }

u8 fn_804BEE18(u8* p) { return *(u8*)(*(u8**)(p + 0xe0) + 0xd0); }

void fn_804BEE04(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe0)))->vfF8(); }

void fn_804BEDF0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe0)))->vf48(); }

void fn_804BEDE8(u8* p) { fn_80374B3C(*(u8**)(p + 0xc4)); }

u8 fn_804BEDDC(u8* p) { return *(u8*)(*(u8**)(p + 0xc4) + 0xd0); }

u8 fn_804BEDD0(u8* p) { return *(u8*)(*(u8**)(p + 0xc4) + 0x11e); }

void fn_804BEDBC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc4)))->vfF8(); }

void fn_804BEDA8(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc4)))->vf48(); }

void fn_804BED9C(u8* p) { fn_80349B74(*(u8**)(p + 0xc0), 0); }

u8 fn_804BED90(u8* p) { return *(u8*)(*(u8**)(p + 0xc0) + 0xd0); }

u8 fn_804BED84(u8* p) { return *(u8*)(*(u8**)(p + 0xc0) + 0x116); }

void fn_804BED70(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF8(); }

void fn_804BED5C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vf48(); }

BOOL fn_804BECC0(const u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0x94); i++) {
        if (((u8**)(p + 0xd0))[i][0xd0] == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void fn_804BECA4(u8* p, s32 a1) {
    *(u16*)(*(u8**)(p + a1 * 4 + 0xd0) + 0x13c) = *(u16*)(*(u8**)(p + a1 * 4 + 0xd0) + 0x13c) | 0x1;
}

BOOL fn_804BEC64(const u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0x94); i++) {
        if (!(*(u16*)(((u8**)(p + 0xd0))[i] + 0x13c) & 1)) {
            return FALSE;
        }
    }
    return TRUE;
}

void fn_804BEA48(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xcc)))->vf48(); }

void fn_804BEA38(const u8* p) { fn_80353714(*(u8**)(p + 0xc8), 0, 1.0f); }

u8 fn_804BEA2C(u8* p) { return *(u8*)(*(u8**)(p + 0xc8) + 0x112); }

void fn_804BEA18(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xf8)))->vfF4(); }

void fn_804BEA04(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xf8)))->vfF8(); }

void fn_804BE9F0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xf8)))->vf48(); }

void fn_804BE9DC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xfc)))->vfF4(); }

u8 fn_804BE9D0(u8* p) { return *(u8*)(*(u8**)(p + 0xfc) + 0xd0); }

void fn_804BE9C8(u8* p) { fn_804BB088(*(u8**)(p + 0xfc)); }

void fn_804BE9B4(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xfc)))->vfF8(); }

void fn_804BE9A0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xfc)))->vf48(); }

void fn_804BE998(u8* p) { fn_804BB430(*(u8**)(p + 0x100)); }

BOOL fn_804BE948(const u8* p) {
    BOOL r = FALSE;
    u8* q = *(u8**)(p + 0x100);
    if (fn_802EDC9C(q + 0x94) && !(*(u16*)(q + 0x11c) & 2)) {
        r = TRUE;
    }
    return r;
}

void fn_804BE924(u8* p, s32 v) {
    u8* q = *(u8**)(p + 0x100);
    if (*(s32*)(q + 0x110) != v) {
        *(u16*)(q + 0x11c) |= 1;
        *(s32*)(q + 0x114) = v;
    }
}

void fn_804BE910(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0x100)))->vfF8(); }

void fn_804BE8FC(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0x100)))->vf48(); }

void fn_804BE8F4(u8* p) { fn_804BB618(*(u8**)(p + 0x104)); }

u8 fn_804BE8E8(u8* p) { return *(u8*)(*(u8**)(p + 0x104) + 0xd0); }

void fn_804BE8D4(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0x104)))->vfF8(); }

void fn_804BE8C0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0x104)))->vf48(); }

void fn_804BE8BC() {}

void fn_804BE8B8() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806DDBD0>::Unk_StateMachine(Unk_806DDBD0*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806DDBD0>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
