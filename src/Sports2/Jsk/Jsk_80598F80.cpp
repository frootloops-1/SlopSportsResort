// Resort Power Cruising (jsk) file 0x80598F80-0x80599070: layout 65102_jsk_finsh (vtable 0x806E5DD0).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
extern u8 lbl_806E5DD0[];


void fn_802B73BC(s32);

void fn_80598F80() { fn_802B73BC(414); }

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_80598F88(u8* p) {
    fn_80371668(p, 2, "WS2_game_jsk", "65102_jsk_finsh", 1, 0, 0);
    u8* v = lbl_806E5DD0;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    return p;
}

}  // extern "C"
