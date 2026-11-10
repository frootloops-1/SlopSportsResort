// Resort shared Power Cruising/Wakeboarding engine file 0x80594890-0x805965A4: shared helper file (called from jsk and wkb files).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

u32 fn_80596320(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_80596258(u8* p) { *(u16*)(p + 0x2) = 0; }

u32 fn_80596164(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_8059609C(u8* p) { *(u16*)(p + 0x2) = 0; }

u32 fn_80595FA8(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_80595F9C(u8* p) { *(u16*)(p + 0x2) = 0; }

}  // extern "C"
