// Resort Wakeboarding (wkb) file 0x805AA6F8-0x805AB8E0: boat avatars, vtables 0x806E7660/0x806E7678/0x806E7690 (WS2_wkb_ava_boat_*).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80360640(u8*);
void fn_805AAF20(u8*);

u32 fn_805AB7A4(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_805AB33C(u8* p, f32 v) { *(f32*)(p + 0x24) = v; }

s32 fn_805AB334() { return 8; }

void fn_805AB304(u8* p) { fn_80360640(p + 0x1c); }

void fn_805AAF1C() {}

void fn_805AAD4C() {}

void fn_805AACA0(u8* p) { fn_805AAF20(p); }

void fn_805AAAFC() {}

void fn_805AAA54(u8* p) { fn_805AAF20(p); }

void fn_805AA6F8() {}

}  // extern "C"
