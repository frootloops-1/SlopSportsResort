// Canoeing (Resort-only), .text 0x804A4B08-0x804A5880: grass (WS2_can_water_grass). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

extern u8 lbl_806DC104[];

void fn_804A5794() {}

u8* fn_804A5788() { return lbl_806DC104; }

void fn_804A5768(f32* v) {
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    v[4] = 0.0f;
    v[5] = 0.0f;
}

void fn_804A5244(u8* p) {
    for (s32 i = 0; i < 3; i++) {
        f32* v = (f32*)(*(u8**)(p + 0x10c) + i * 0x18);
        v[0] = v[1] = v[2] = 0.0f;
        v[3] = v[4] = v[5] = 0.0f;
    }
}

f32 fn_804A5050(f32 a, f32 b, f32 t) { return t * (b - a) + a; }

}  // extern "C"
