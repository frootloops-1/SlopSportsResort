// Canoeing (Resort-only), .text 0x804B9D44-0x804BAA34: big fish (WS2_can_big_fish). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>

extern "C" {

extern u8 lbl_806DD47C[];

u8* fn_804BA9EC() { return lbl_806DD47C; }

void fn_804BA084() {}

void fn_804B9F30() {}

void fn_804B9D44(u8* p) { ((RPSysEffect*)(*(u8**)(p + 0xd8)))->forceKill(); }

}  // extern "C"
