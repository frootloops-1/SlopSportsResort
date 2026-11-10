// Ddg_805E61A0: Resort Frisbee Dog unit 0x805E61A0-0x805E6F5C (Resort-only, no Wii Sports twin).
// class with vtable 0x806EAC18 / 0x806EAC30.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

struct Unk_VtAt34 {
    u8 unk0[0x34];
    virtual void vf8(u32, u32);
};

void fn_80331678(u8*, u8*, u8*);
void fn_8033219C(u8*, u32);
void fn_80334984(u8*);
void fn_805E60CC(u8*, u8*);
extern u8 lbl_806EAC18[];

// Deleting destructor of a class without a base destructor.
void* fn_805E6EE4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8 fn_805E6298(u8* p, u8* a1) {
    *(u32*)(p + 0xc) = *(u32*)(a1 + 0xc);
    fn_8033219C(*(u8**)(a1 + 0x10), *(u32*)(p + 0x10));
    *(f32*)(*(u8**)(p + 0x14) + 0x3c) = *(f32*)(*(u8**)(a1 + 0x14) + 0x3c);
    *(f32*)(*(u8**)(p + 0x14) + 0x40) = *(f32*)(*(u8**)(a1 + 0x14) + 0x40);
    *(f32*)(*(u8**)(p + 0x14) + 0x44) = *(f32*)(*(u8**)(a1 + 0x14) + 0x44);
    *(f32*)(*(u8**)(p + 0x14)) = *(f32*)(*(u8**)(p + 0x10) + 0x4);
    *(f32*)(*(u8**)(p + 0x14) + 0x4) = *(f32*)(*(u8**)(p + 0x10) + 0x8);
    *(f32*)(*(u8**)(p + 0x14) + 0x8) = *(f32*)(*(u8**)(p + 0x10) + 0xc);
    *(u32*)(*(u8**)(p + 0x14) + 0xc) = *(u32*)(*(u8**)(p + 0x10) + 0x1c);
    *(u32*)(*(u8**)(p + 0x14) + 0x10) = *(u32*)(*(u8**)(p + 0x10) + 0x20);
    *(u32*)(*(u8**)(p + 0x14) + 0x14) = *(u32*)(*(u8**)(p + 0x10) + 0x24);
    *(u32*)(*(u8**)(p + 0x14) + 0x18) = *(u32*)(*(u8**)(p + 0x10) + 0x28);
    *(u32*)(*(u8**)(p + 0x14) + 0x1c) = *(u32*)(*(u8**)(p + 0x10) + 0x2c);
    *(u32*)(*(u8**)(p + 0x14) + 0x20) = *(u32*)(*(u8**)(p + 0x10) + 0x30);
    *(u32*)(*(u8**)(p + 0x14) + 0x24) = *(u32*)(*(u8**)(p + 0x10) + 0x34);
    *(u32*)(*(u8**)(p + 0x14) + 0x28) = *(u32*)(*(u8**)(p + 0x10) + 0x38);
    *(u32*)(*(u8**)(p + 0x14) + 0x2c) = *(u32*)(*(u8**)(p + 0x10) + 0x3c);
    ((Unk_VtAt34*)(*(u8**)(p + 0x14)))->vf8(*(u32*)(p + 0x14), *(u32*)(p + 0x10));
    *(u16*)(p + 0x18) = *(u16*)(a1 + 0x18);
    *(u8*)(p + 0x1a) = *(u8*)(a1 + 0x1a);
    *(f32*)(p + 0x1c) = *(f32*)(a1 + 0x1c);
    *(f32*)(p + 0x20) = *(f32*)(a1 + 0x20);
    *(f32*)(p + 0x24) = *(f32*)(a1 + 0x24);
    *(u32*)(p + 0x28) = *(u32*)(a1 + 0x28);
    return *(u8*)(a1 + 0x1a);
}

u8* fn_805E628C(u8* p) { return *(u8**)(p + 0x10) + 0x4; }

u8* fn_805E6280(u8* p) { return *(u8**)(p + 0x10) + 0x10; }

u8* fn_805E6274(u8* p) { return *(u8**)(p + 0x10) + 0x40; }

u8* fn_805E6268(u8* p) { return *(u8**)(p + 0x10) + 0x1c; }

u8* fn_805E622C(u8* p) {
    fn_80331678(*(u8**)(p + 0x10) + 0x4c, *(u8**)(p + 0x10) + 0x4, *(u8**)(p + 0x10) + 0x1c);
    return *(u8**)(p + 0x10) + 0x4c;
}

// Deleting destructor of a class without a base destructor.
void* fn_805E61EC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_805E61A0(u8* p, u32 a1) {
    fn_80334984(p);
    *(u32*)(p + 0x8) = a1;
    *(u8**)(p) = lbl_806EAC18;
    fn_805E60CC(p, lbl_806EAC18);
    return p;
}

}  // extern "C"
