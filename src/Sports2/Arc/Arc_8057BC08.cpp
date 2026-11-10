// Arc_8057BC08: Resort Archery unit 0x8057BC08-0x8057C020 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

// Pane name pointers (.sdata); defined first so the string pool order matches.
const char* lbl_806F2E78 = "N_AbtnText_00";
const char* lbl_806F2E7C = "N_ZbtnText_00";

void fn_802703A8(void* lyt, const char* arc, const char* name, int a, int b, int c);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void* fn_8026F970(void* lyt, const char* name);

// First pass: builds the operate-text layout (arc name, in/out/keyDeside animations, text panes).
void fn_8057BE88(u8* p) {
    fn_802703A8(p + 0x94, "WS2_game_arc", "65303_arc_operate_Text", 1, 0, 0);
    fn_8027035C(p + 0x94, 0, "in", "G_in_00", 0);
    fn_8027035C(p + 0x94, 1, "out", "G_out_00", 0);
    fn_8027035C(p + 0x94, 2, "keyDeside", "G_keyDeside_00", 0);
    *(void**)(p + 0x114) = fn_8026F970(p + 0x94, lbl_806F2E78);
    *(void**)(p + 0x118) = fn_8026F970(p + 0x94, lbl_806F2E7C);
}

void fn_8057BCB4(u8* p) { *(u8*)(p + 0x111) = 0x1; }

void fn_8057BCA8(u8* p) { *(u8*)(p + 0x112) = 0x1; }

}  // extern "C"
