// Resort Basketball (bsk) file 0x8052F2A4-0x80531A10: class with vtables 0x806E1708/0x806E1820/0x806E18A0 (ctor 0x80531138).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt38 {
    u8 unk0[0x38];
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
    virtual u8* vf54();
};

void fn_80357194(u8*, u8*);
void fn_803571BC(u8*, u8*);
void fn_804FD384(u8*, s32);
u8* fn_80504C60(u8*);
void fn_80509E5C(u8*);
void fn_80509E84(u8*, s32);
void fn_80509F10(u8*, s32);
void fn_80513B08(u8*, s32, u8*, u32);

void fn_80531078(u8* p, u8* a1) {
    *(u8**)(p + 0x1ec) = a1;
    *(u32*)(p + 0x1f0) = *(u32*)(a1 + 0x158);
    *(u32*)(p + 0x1f4) = *(u32*)(a1 + 0x15c);
    *(u32*)(p + 0x1f8) = *(u32*)(a1 + 0x160);
    *(u32*)(p + 0x1fc) = *(u32*)(a1 + 0x164);
}

void fn_80530FA8(u8* p) { *(u32*)(p + 0x1c8) = *(u32*)(p + 0x1c8) & ~0x2; }

s32 fn_80530B10(u8* p, u32 a1) {
    fn_804FD384(*(u8**)(p + 0x1ec), 1);
    *(u32*)(p + 0x200) = a1;
    fn_80357194(p, p + 0x170);
    return 1;
}

s32 fn_80530AE8(u8* p) {
    fn_80357194(p, p + 0x19c);
    return 1;
}

s32 fn_80530AC0(u8* p) {
    fn_80357194(p, p + 0x3c);
    return 1;
}

void fn_80530AB8(u8* p) { fn_803571BC(p, p + 0x3c); }

void fn_80530AB0(u8* p) { fn_803571BC(p, p + 0x94); }

void fn_80530AA8(u8* p) { fn_803571BC(p, p + 0xec); }

void fn_805308F4() {}

void fn_805308F0() {}

void fn_805304FC() {}

void fn_80530364() {}

void fn_805301D0(u8* p) { fn_80509F10(*(u8**)(p + 0x1f4), 1); }

void fn_80530154(u8* p) {
    *(u32*)(p + 0x1cc) = 0;
    *(u32*)(p + 0x1d0) = 0;
    u8* t0 = fn_80504C60(p);
    u8* t1 = ((Unk_VtAt38*)(t0))->vf54();
    *(f32*)(p + 0x228) = *(f32*)(*(u8**)(*(u8**)(*(u8**)(t1 + 0x58) + 0x160) + 0x278) + 0x28);
    *(f32*)(p + 0x22c) = *(f32*)(*(u8**)(*(u8**)(*(u8**)(t1 + 0x58) + 0x160) + 0x278) + 0x2c);
    *(f32*)(p + 0x230) = *(f32*)(*(u8**)(*(u8**)(*(u8**)(t1 + 0x58) + 0x160) + 0x278) + 0x30);
    fn_80513B08(*(u8**)(p + 0x1f8), 1, p + 0x228, *(u32*)(*(u8**)(*(u8**)(t1 + 0x58) + 0x160) + 0x278));
}

void fn_8052FC74(u8* p) { fn_80509E84(*(u8**)(p + 0x1f4), 1); }

void fn_8052FA6C(u8* p) { fn_80509E5C(*(u8**)(p + 0x1f4)); }

void fn_8052FA60(u8* p) { fn_80509F10(*(u8**)(p + 0x1f4), 0); }

}  // extern "C"
