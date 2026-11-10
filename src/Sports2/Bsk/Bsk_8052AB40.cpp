// Resort Basketball (bsk) file 0x8052AB40-0x8052B120: class vtable 0x806E14A8 (ctor 0x8052B094), pass-cut effect.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
};

void fn_8050E1B0(u8*, u32);
void fn_8050F214(u8*, s32, s32);
void fn_8050F3A8(u8*, s32, s32);
void fn_8050F430(u8*, s32, s32, u32);
void fn_8050F640(u8*, s32);

void fn_8052B04C(u8* p, u32 a1) { *(u32*)(p + 0x10) = a1; }

void fn_8052B020(u8* p) {
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0x4) = 0;
    *(u8*)(p + 0x1c) = 1;
    *(u32*)(p + 0x18) = 0;
    (*(void (**)(u8*, s32))(*(u8**)(*(u8**)(p + 0x20)) + 0xc))(*(u8**)(p + 0x20), 0);
}

void fn_8052AF7C(u8* p) {
    fn_8050F430(*(u8**)(*(u8**)(p + 0x10) + 0x164), 0, 0, *(u32*)(p + 0x10));
    fn_8050F3A8(*(u8**)(*(u8**)(p + 0x10) + 0x164), 0, 0);
    fn_8050F214(*(u8**)(*(u8**)(p + 0x10) + 0x164), 0, 0);
    fn_8050F640(*(u8**)(*(u8**)(p + 0x10) + 0x164), 0);
    fn_8050E1B0(*(u8**)(*(u8**)(p + 0x10) + 0x164), *(u32*)(p + 0x18));
    ((Unk_VtAt0*)(*(u8**)(p + 0x20)))->vfC();
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

}  // extern "C"
