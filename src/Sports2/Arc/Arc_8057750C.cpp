// Arc_8057750C: Resort Archery unit 0x8057750C-0x80577838 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

// Pane name pointers (.sdata); defined first so the string pool order matches.
const char* lbl_806F2DF8 = "T_distance_00";
const char* lbl_806F2DFC = "T_meter_00";

void fn_802703A8(void* lyt, const char* arc, const char* name, int a, int b, int c);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_80270194(void* lyt, int a, int b);
void* fn_8026F968(void* lyt, const char* name);

// First pass: builds the distance layout (arc name, in/out animations, text boxes).
void fn_805776A4(u8* p) {
    fn_802703A8(p + 0x94, "WS2_game_arc", "65301_arc_distance", 1, 0, 0);
    fn_8027035C(p + 0x94, 0, "in", "G_inOut_00", 0);
    fn_8027035C(p + 0x94, 1, "out", "G_inOut_00", 0);
    fn_80270194(p + 0x94, 0, 1);
    *(void**)(p + 0x118) = fn_8026F968(p + 0x94, lbl_806F2DF8);
    *(void**)(p + 0x11c) = fn_8026F968(p + 0x94, lbl_806F2DFC);
}

void fn_80577634(u8* p) { *(u8*)(p + 0x115) = 0x1; }

}  // extern "C"
