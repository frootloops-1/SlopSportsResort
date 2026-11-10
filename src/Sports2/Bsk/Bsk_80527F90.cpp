// Resort Basketball (bsk) file 0x80527F90-0x8052876C: classes with vtables 0x806E1300/0x806E1318/0x806E1330.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80367B20(u8*, u32, u32);
extern u8* lbl_806F59D8;

void fn_805285B0(u8* p, u32 a1) { fn_80367B20(p, a1, *(u32*)(lbl_806F59D8 + 0x4c)); }

void fn_80528228() {}

}  // extern "C"
