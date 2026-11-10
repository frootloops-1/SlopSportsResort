// Arc_8057AC9C: Resort Archery unit 0x8057AC9C-0x8057B014 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

// Pane name table (.data); defined first so the string pool order matches.
const char* lbl_806E4A08[] = {"N_Hold_Root_00", "N_Abtn_Root_00", "N_draw_Root_00", "N_Zbtn_Root_00"};

void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void* fn_8026F970(void* lyt, const char* name);
extern u8 lbl_806E4A18[];

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers and state).
void* fn_8057AEFC(u8* p) {
    fn_80371668(p, 6, "WS2_game_arc", "65310_arc_explain", 1, 0, 0);
    u8* v = lbl_806E4A18;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(u8*)(p + 0x110) = 0;
    *(u8*)(p + 0x111) = 0;
    *(int*)(p + 0x114) = 4;
    for (int i = 0; i < 4; i++) {
        ((int*)(p + 0x118))[i] = 0;
    }
    return p;
}

// First pass: builds the draw/Zbtn animations and looks up the four root panes.
void fn_8057AE5C(u8* p) {
    fn_8027035C(p + 0x94, 2, "draw", "G_draw_00", 0);
    fn_8027035C(p + 0x94, 3, "Zbtn", "G_Zbtn_00", 0);
    for (int i = 0; i < 4; i++) {
        ((void**)(p + 0x118))[i] = fn_8026F970(p + 0x94, lbl_806E4A08[i]);
    }
}

void fn_8057AEF0(u8* p) { *(u8*)(p + 0x111) = 0x1; }

}  // extern "C"
