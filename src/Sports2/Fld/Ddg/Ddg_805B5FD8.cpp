// Ddg_805B5FD8: Resort Frisbee Dog unit 0x805B5FD8-0x805B65E0 (Resort-only, no Wii Sports twin).
// Frisbee Dog RP scene class (vtable 0x806E86C0, ctor in unk/sinit_8022E364; first user of the weak "SceneBase" name); creates Sp2::Fld::Ddg::Scene (fn_805C28D0).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
};

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

void fn_80335558(u8*);
void fn_803355C4(u8*);
void fn_80335764(u8*);
void fn_80335808(u8*);

void fn_805B62E8(u8* p) {
    ((Unk_VtAt30*)(*(u8**)(p + 0x15c)))->vf1C();
    fn_80335808(*(u8**)(p + 0x160));
    ((Unk_VtAt0*)(*(u8**)(p + 0x154)))->vf10();
    ((Unk_VtAt30*)(*(u8**)(p + 0x15c)))->vf24();
}

void fn_805B6288(u8* p) {
    *(u8*)(p + 0x164) = 0;
    ((Unk_VtAt30*)(*(u8**)(p + 0x15c)))->vf2C();
    fn_80335764(*(u8**)(p + 0x160));
    ((Unk_VtAt0*)(*(u8**)(p + 0x154)))->vf18();
}

void fn_805B61EC(u8* p) { fn_803355C4(*(u8**)(p + 0x160)); }

void fn_805B6194(u8* p) {
    fn_80335558(*(u8**)(p + 0x160));
    ((Unk_VtAt0*)(*(u8**)(p + 0x154)))->vf1C();
    ((Unk_VtAt30*)(*(u8**)(p + 0x15c)))->vf44();
}

void fn_805B6184(u8* p) { *(u8*)(p + 0x164) = *(u8*)(p + 0x164) | 0x1; }

}  // extern "C"
