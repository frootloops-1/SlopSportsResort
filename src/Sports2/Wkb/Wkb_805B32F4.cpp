// Resort Wakeboarding (wkb) file 0x805B32F4-0x805B3480: layout 66011_wkb_Time (vtable 0x806E81A0).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void* fn_8026F968(void* lyt, const char* name);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_806E81A0[];


void fn_805B3320() {}

// First pass: layout constructor (base ctor with arc/layout names, vtable pointers, layout name copy).
void* fn_805B3384(u8* p) {
    fn_80371668(p, 0, "WS2_game_Wkb", "66011_wkb_Time", 1, 0, 0);
    const char* nm = "Time";
    u8* v = lbl_806E81A0;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    strncpy((char*)(p + 0x34), nm, 0x20);
    return p;
}

// First pass: looks up the points text pane of the embedded layout.
void fn_805B3348(u8* p) { *(void**)(p + 0x110) = fn_8026F968(p + 0x94, "T_pts_00"); }

}  // extern "C"
