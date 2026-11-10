// Resort Basketball (bsk) file 0x8053D760-0x8053FD00: class with vtables 0x806E2C10/0x806E2D90/0x806E2DD0 (ctor 0x8053F7F4).
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
    virtual void vf50(s32);
};

u8* fn_80504C60(u8*);
u8* fn_8052440C(u8*);
void fn_805333E0(u8*, s32, u32);
void fn_80535DF8(u8*);
void fn_80535F38(u8*);
u32 fn_8053D88C(u8*, s32);
void fn_8053E9C4(u8*, s32);
void fn_8053EA6C(u8*);
extern u8* lbl_806F5A28;

void fn_8053F6D0(u8* p) {
    fn_8053EA6C(p);
    ((Unk_VtAt38*)(p))->vfC();
}

void fn_8053F43C(u8* p) {
    *(u32*)(p + 0xf8) = 0;
    *(u32*)(p + 0xfc) = 0;
}

void fn_8053EE60(u8* p) {
    *(u32*)(p + 0xf8) = 0;
    fn_80535F38(*(u8**)(p + 0xec));
    fn_80535DF8(*(u8**)(p + 0xec));
}

void fn_8053EC6C(u8* p) {
    *(u32*)(p + 0xf8) = 0;
    u8* t0 = fn_80504C60(p);
    *(u32*)(p + 0xf0) = *(u32*)(t0 + 0x100);
    u8* t1 = fn_8052440C(t0);
    *(u32*)(p + 0xf4) = *(u32*)(t1 + 0x244);
}

void fn_8053DFBC(u8* p, u32 a1) {
    *(u32*)(p) = a1;
    *(u32*)(p + 0x4) = 0;
    *(u8*)(p + 0x8) = 0;
}

void fn_8053DA78(u8* p) {
    u32 t0 = fn_8053D88C(p, 0);
    fn_805333E0(*(u8**)(p + 0x4), 4, t0);
    fn_8053E9C4(*(u8**)(p), 1);
}

void fn_8053DA14(u8* p) {
    u32 t0 = fn_8053D88C(p, 0);
    fn_805333E0(*(u8**)(p + 0x4), 5, t0);
    fn_8053E9C4(*(u8**)(p), 1);
    ((Unk_VtAt38*)(lbl_806F5A28))->vf50(1);
}

void fn_8053D9B0(u8* p) {
    u32 t0 = fn_8053D88C(p, 0);
    fn_805333E0(*(u8**)(p + 0x4), 7, t0);
    fn_8053E9C4(*(u8**)(p), 1);
    ((Unk_VtAt38*)(lbl_806F5A28))->vf50(1);
}

void fn_8053D94C(u8* p) {
    u32 t0 = fn_8053D88C(p, 1);
    fn_805333E0(*(u8**)(p + 0x4), 8, t0);
    fn_8053E9C4(*(u8**)(p), 1);
    ((Unk_VtAt38*)(lbl_806F5A28))->vf50(1);
}

void fn_8053D8E8(u8* p) {
    u32 t0 = fn_8053D88C(p, 1);
    fn_805333E0(*(u8**)(p + 0x4), 9, t0);
    fn_8053E9C4(*(u8**)(p), 1);
    ((Unk_VtAt38*)(lbl_806F5A28))->vf50(1);
}

void fn_8053D870(u8* p) {
    *(u32*)(p) = 0;
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0xc) = 0;
    *(u8*)(p + 0x10) = 0;
}

}  // extern "C"
