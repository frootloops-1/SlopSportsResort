// Resort shared Power Cruising/Wakeboarding engine file 0x805AEB80-0x805AFFB8: course object, vtables 0x806E7D78/0x806E7DC8 (called from jsk and wkb objects).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_805AFFB4() {}

void fn_805AFF28(u8* p, u32 v) { *(u32*)(p + 0x8) = v; }

u32 fn_805AFD20(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

u32 fn_805AFD10(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_805AFC48(u8* p) { *(u16*)(p + 0x2) = 0; }

u32 fn_805AFA80(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_805AFA74(u8* p) { *(u16*)(p + 0x2) = 0; }

void fn_805AEBEC() {}

void fn_805AEBE8() {}

s32 fn_805AEB80() { return 128; }

}  // extern "C"
