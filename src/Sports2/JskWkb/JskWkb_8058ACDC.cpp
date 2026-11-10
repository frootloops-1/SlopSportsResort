// Resort shared Power Cruising/Wakeboarding engine file 0x8058ACDC-0x8058BE50: class vtable 0x806E5870.
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

s32 fn_8058BD60() { return 8; }

u32 fn_8058BD50(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_8058B780() {}

void fn_8058B760(u8* p) { *(u8*)(p + 0x221) = 4; }

}  // extern "C"
