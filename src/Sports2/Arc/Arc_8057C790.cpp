// Arc_8057C790: Resort Archery unit 0x8057C790-0x8057C8B8 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
extern u8 lbl_806E5038[];

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_8057C7C4(u8* p) {
    fn_80371668(p, 2, "WS2_game_Arc", "65311_arc_pose_attention", 1, 0, 0);
    u8* v = lbl_806E5038;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(u8*)(p + 0x110) = 0;
    return p;
}

void fn_8057C7B8(u8* p) { *(u8*)(p + 0x110) = 0x0; }

}  // extern "C"
