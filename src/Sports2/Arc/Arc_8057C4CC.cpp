// Arc_8057C4CC: Resort Archery unit 0x8057C4CC-0x8057C790 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

// Pane name pointers (.sdata); defined first so the string pool order matches.
const char* lbl_806F2E90[] = {"N_10point_00", "N_10point_T_00"};

void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
extern u8 lbl_806E4F18[];

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_8057C6A4(u8* p) {
    fn_80371668(p, 2, "WS2_game_arc", "65305_arc_perfect", 1, 0, 0);
    u8* v = lbl_806E4F18;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    return p;
}

void fn_8057C698(u8* p) { *(u8*)(p + 0x110) = 0x1; }

}  // extern "C"
