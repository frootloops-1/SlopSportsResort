// Resort Power Cruising (jsk) file 0x805AD7DC-0x805AE610: balloon / time-extend objects, vtables 0x806E7AF8/0x806E7AC0 (WS2_jsk_baloon_*).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

// placeholder for an object called through its vtable (vptr at 0xC, slot = offset in the vtable)
struct Unk_PadC {
    u8 pad[0xC];
};

struct Unk_VC : Unk_PadC {
    virtual void vf08();
    virtual void vf0C();
};

extern "C" {

void fn_80296224(u8*);
extern f32 lbl_806F34A4;
extern void* lbl_806F5F30;

u32 fn_805AE49C(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_805AE490(u8* p) { *(u16*)(p + 0x2) = 0; }

void fn_805ADEC4(u8* p) { (*(Unk_VC**)(p + 0x28))->vf0C(); }

void fn_805ADEC0() {}

void fn_805ADEBC() {}

void* fn_805ADE84() { return lbl_806F5F30; }

void fn_805AD7EC() {}

void fn_805AD7E8() {}

void fn_805AD7E4(u8* p) { fn_80296224(p); }

f32 fn_805AD7DC() { return lbl_806F34A4; }

}  // extern "C"
