// Resort shared Power Cruising/Wakeboarding engine file 0x8059A320-0x8059D994: player avatar (WS2_jsk_ava_*/WS2_wkb_ava_* animations, splash effects).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8059A348(u8* p) { *(u16*)(p + 0x8) |= 0x4; }

void fn_8059A338(u8* p) { *(u16*)(p + 0x8) |= 0x2; }

}  // extern "C"
