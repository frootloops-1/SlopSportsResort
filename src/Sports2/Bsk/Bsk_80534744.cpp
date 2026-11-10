// Resort Basketball (bsk) file 0x80534744-0x80534CCC: layout 65402_bsk_shootCountDown, vtable 0x806E1AD8.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8025ED28(u8*);
u8* fn_8026F6AC(u8*, s32);
void fn_8026F720(u8*, u32, u32, s32);
u32 fn_8026F958(u8*, u32);
void fn_8026FEF0(u8*, s32, s32);
void fn_803715C0(u8*, s32, s32);
void fn_80534860(u8* p);
extern u32 lbl_806F2A90;
extern u8 lbl_806E1AD8[];

u8* fn_80534BE8(u8* p) {
    fn_803715C0(p, 7, 0);
    *(u8**)(p + 0x30) = lbl_806E1AD8;
    *(u8**)(p + 0x18) = lbl_806E1AD8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806E1AD8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806E1AD8 + 0x88;
    *(u32*)(p + 0x110) = 0;
    *(u8*)(p + 0x114) = 0;
    *(u8*)(p + 0x11a) = 0;
    return p;
}

void fn_80534A98(u8* p) { *(u8*)(p + 0x114) = 1; }

void fn_80534A34(u8* p) { fn_80534860(p); }

void fn_80534930(u8* p, u32 a1) {
    u32 t0 = fn_8026F958(p + 0x94, lbl_806F2A90);
    fn_8026F720(p + 0x94, t0, a1, 0);
}

void fn_80534860(u8* p) {
    *(u16*)(p + 0x116) = 0x12c;
    fn_8026FEF0(p + 0x94, 2, 0);
    u8* t1 = fn_8026F6AC(p + 0x94, 2);
    fn_8025ED28(t1);
    fn_8026FEF0(p + 0x94, 3, 0);
    u8* t4 = fn_8026F6AC(p + 0x94, 3);
    fn_8025ED28(t4);
    fn_8026FEF0(p + 0x94, 4, 0);
    u8* t7 = fn_8026F6AC(p + 0x94, 4);
    fn_8025ED28(t7);
    fn_8026FEF0(p + 0x94, 5, 0);
    u8* t10 = fn_8026F6AC(p + 0x94, 5);
    fn_8025ED28(t10);
    fn_8026FEF0(p + 0x94, 6, 0);
    u8* t13 = fn_8026F6AC(p + 0x94, 6);
    fn_8025ED28(t13);
}

}  // extern "C"
