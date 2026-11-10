// Canoeing (Resort-only), .text 0x804A4500-0x804A4B08: grass (WS2_can_water_grass2). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_804A4388(u8*);
extern u8 lbl_806DC09C[];

void fn_804A4B04() {}

u8* fn_804A4AF8() { return lbl_806DC09C; }

void fn_804A4748(u8* p) { fn_804A4388(p); }

void fn_804A4708(u8* p) {
    f32* v = *(f32**)(p + 0x98);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = v[4] = v[5] = 0.0f;
    v = *(f32**)(p + 0x9c);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = v[4] = v[5] = 0.0f;
}

}  // extern "C"
