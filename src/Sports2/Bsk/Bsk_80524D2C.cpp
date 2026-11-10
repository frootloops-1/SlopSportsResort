// Resort Basketball (bsk) file 0x80524D2C-0x80525BF4: class vtable 0x806E1238 (ctor 0x80525B3C).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

extern u8 lbl_806E1238[];

void fn_80525B3C(u8* p) {
    *(u8**)(p) = lbl_806E1238;
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0xc) = 0;
}

void fn_80525AF4(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

}  // extern "C"
