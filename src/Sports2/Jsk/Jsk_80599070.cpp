// Resort Power Cruising (jsk) file 0x80599070-0x805991CC: layout 65103_jsk_manual (vtable 0x806E5EF0).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
extern u8 lbl_806E5EF0[];


void fn_801ED220(u8*);

void fn_805991B0(u8* p) { fn_801ED220(p); }

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_805990D4(u8* p) {
    fn_80371668(p, 3, "WS2_game_jsk", "65103_jsk_manual", 1, 0, 0);
    u8* v = lbl_806E5EF0;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    return p;
}

// First pass: registers the loop animation of the embedded layout.
void fn_805990B8(u8* p) { fn_8027035C(p + 0x94, 2, "loop", "G_loop_00", 0); }

}  // extern "C"
