// Resort Basketball (bsk) file 0x80520E80-0x8052450C: player class, vtables 0x806E10F0/0x806E11B8 (ctor 0x80523BE4, cpu/SkillData.exbin), helper vtable 0x806E10E0.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

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
};

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
    virtual void vf54();
    virtual u32 vf58();
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
};

void fn_80269ED0(u8*, s32, s32);
void fn_803571BC(u8*, u8*);
void fn_805017C4(u8*, u32, u32);
void fn_80503D1C(u8*);
void fn_80503D68(u8*);
void fn_80503E4C(u8*, f32);
void fn_80504194(u8*);
void fn_805044D4(u8*);
void fn_805046C0(u8*);
void fn_8052247C(u8*);
void fn_80522510(u8*);
void fn_8053F630(u8*, u32);
extern u8* lbl_806F4E98;
extern u32 lbl_806F5AA8;
extern u8 lbl_806E10E0[];

void fn_805244DC(u8* p) { *(u8**)(p + 0x27c) = *(u8**)(p + 0x27c) + 0x1; }

void fn_805244D8() {}

void fn_805244D4() {}

u32 fn_8052440C() { return lbl_806F5AA8; }

void fn_805235F0(u8* p) { fn_80504194(p); }

void fn_80523590(u8* p) {
    ((Unk_VtAt38*)(p))->vfC();
    fn_8052247C(p);
    fn_80503E4C(p, *(f32*)(p + 0x114));
    ((Unk_VtAt38*)(*(u8**)(p + 0xfc)))->vf1C();
}

void fn_80523524(u8* p) {
    fn_805046C0(p);
    fn_80503D68(p);
    fn_80503D1C(p);
    ((Unk_VtAt38*)(p))->vf80();
    fn_80522510(p);
    ((Unk_VtAt38*)(*(u8**)(p + 0xfc)))->vf20();
}

void fn_805234DC(u8* p) {
    fn_805044D4(p);
    ((Unk_VtAt30*)(*(u8**)(p + 0x244)))->vf44();
    lbl_806F5AA8 = 0;
}

s32 fn_80523414() { return 0; }

u32 fn_80523190(u8* p, s32 a1) { return *(u32*)(p + a1 * 4 + 0x58); }

void fn_80523180(u8* p, u8* a1) { fn_805017C4(p, *(u32*)(a1 + 0x3c), *(u32*)(a1 + 0x274)); }

void fn_80523050(u8* p) {
    u32 t0 = ((Unk_VtAt38*)(p))->vf58();
    fn_8053F630(*(u8**)(p + 0x108), t0);
}

void fn_80523048(u8* p) { fn_803571BC(p, p + 0x194); }

void fn_80523040(u8* p) { fn_803571BC(p, p + 0x1c0); }

void fn_80523038(u8* p) { fn_803571BC(p, p + 0x1ec); }

void fn_8052213C() { fn_80269ED0(lbl_806F4E98, 0, 1); }

u8 fn_80522134(u8* p) { return *(u8*)(p + 0x24d); }

void fn_805218A4(u8* p) {
    *(u8*)(p + 0x119) = 0;
    *(u8*)(p + 0x11a) = 0;
}

void fn_80521478(u8* p) { *(u8**)(p) = lbl_806E10E0; }

}  // extern "C"
