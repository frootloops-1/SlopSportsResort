// Resort Wakeboarding (wkb) file 0x805A6D28-0x805A8C64: tow boat (loc_ava_captain, wkb_boat, WS2_wkb_motorboat).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

u32 fn_805A8924(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_805A8918(u8* p) { *(u16*)(p + 0x2) = 0; }

void fn_805A7B54(u8* p) { *(u16*)(p + 0x530) |= 0x10; }

void fn_805A71E4() {}

}  // extern "C"
