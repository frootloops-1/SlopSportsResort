// Canoeing (Resort-only), .text 0x804B9448-0x804B9D44: fountains (WS2_can_fountain_S/L). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>

extern "C" {

void fn_804A42C4(u8* p, f32 a, f32 b, f32 c, f32 d);
extern u8 lbl_806DD414[];

u8* fn_804B9CFC() { return lbl_806DD414; }

void fn_804B9C54(u8* p) {
    fn_804A42C4(p, 1.0f, 1.0f, 0.0f, 100.0f);
    *(f32*)(p + 0x70) = 150.0f;
    p[0x90] = 1;
}

void fn_804B96B4(u8* p) { *(u8*)(p + 0x90) = 1; }

void fn_804B96B0() {}

void fn_804B9480() {}

void fn_804B9448(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0x94)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0x98)))->forceKill();
}

}  // extern "C"
