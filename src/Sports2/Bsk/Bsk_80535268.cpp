// Resort Basketball (bsk) file 0x80535268-0x80535700: layout 65401_bsk_shootClock, vtable 0x806E1D18.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt0 {
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
    virtual u8* vf68();
};

void fn_8026F720(u8*, u32, u32, s32);
void fn_8026F828(u8*, u32, s32, s32, s32, s32, s32);
u32 fn_8026F958(u8*, u32);
void fn_8026FEDC(u8*, s32);
void fn_803715C0(u8*, s32, s32);
extern u32 lbl_806F2AA8;
extern u8 lbl_806E1D18[];

u8* fn_80535624(u8* p) {
    fn_803715C0(p, 3, 0);
    *(u8**)(p + 0x30) = lbl_806E1D18;
    *(u8**)(p + 0x18) = lbl_806E1D18 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E1D18 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E1D18 + 0x88;
    *(u16*)(p + 0x112) = 0;
    return p;
}

void fn_805353A4(u8* p) { *(u8*)(p + 0x110) = 1; }

void fn_80535398(u8* p) { *(u8*)(p + 0x110) = 0; }

void fn_8053534C(u8* p, u32 a1) {
    u32 t0 = fn_8026F958(p + 0x94, lbl_806F2AA8);
    fn_8026F720(p + 0x94, t0, a1, 0);
}

void fn_8053529C(u8* p) {
    *(u16*)(p + 0x112) = 0x4b0;
    fn_8026F828(p + 0x94, *(u32*)(p + 0x124), 0, 50, 20, 1, 0);
    fn_8026FEDC(p + 0x94, 2);
    u8* t2 = ((Unk_VtAt0*)(*(u8**)(p + 0x124)))->vf68();
    *(u16*)(t2 + 0x10) = *(s16*)(p + 0x114);
    *(u16*)(t2 + 0x12) = *(s16*)(p + 0x116);
    *(u16*)(t2 + 0x14) = *(s16*)(p + 0x118);
    *(u16*)(t2 + 0x16) = *(s16*)(p + 0x11a);
    *(u16*)(t2 + 0x18) = *(s16*)(p + 0x11c);
    *(u16*)(t2 + 0x1a) = *(s16*)(p + 0x11e);
    *(u16*)(t2 + 0x1c) = *(s16*)(p + 0x120);
    *(u16*)(t2 + 0x1e) = *(s16*)(p + 0x122);
}

}  // extern "C"
