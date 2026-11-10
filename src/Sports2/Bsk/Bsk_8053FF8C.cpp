// Resort Basketball (bsk) file 0x8053FF8C-0x80542EA8: class vtable 0x806E2E48 (ctor 0x80542CF0).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
};


void fn_80542EA4() {}

void fn_80542EA0() {}

void fn_80542E9C() {}

void fn_80542AF4() {}

void fn_80542AE0(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x104)))->vfC(); }

void fn_80542ACC(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x104)))->vf10(); }

s32 fn_80542AC4() { return 1; }

f32 fn_80542A68(u8* p) { return *(f32*)(*(u8**)(p + 0x104) + 0xc); }

f32 fn_80542A60(u8* p) { return *(f32*)(p + 0x12c); }

f32 fn_80541FA0(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x30); }

f32 fn_80541F90(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x48); }

f32 fn_80541F80(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x44); }

f32 fn_80541F78(u8* p) { return *(f32*)(p + 0x14c); }

f32 fn_80541F5C(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0xc); }

f32 fn_80541EB4(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x8); }

f32 fn_80541EA4(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x64); }

f32 fn_80541DFC(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x104) + 0x8) + 0x2c); }

}  // extern "C"
