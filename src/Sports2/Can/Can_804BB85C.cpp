// Canoeing (Resort-only), .text 0x804BB85C-0x804BC530: rocks (WS2_can_rock_*). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>

extern "C" {

extern u8 lbl_806DD974[];

u8* fn_804BC4D8() { return lbl_806DD974; }

void fn_804BBC60() {}

void fn_804BBA10() {}

void fn_804BB85C(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xf0)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0xf4)))->forceKill();
}

}  // extern "C"
