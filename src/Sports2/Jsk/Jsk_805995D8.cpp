// Resort Power Cruising (jsk) file 0x805995D8-0x80599B9C: layout 65105_jsk_guideArrow (vtable 0x806E6140).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// Name tables and pointers (.data/.sdata); defined first so the string pool order matches.
const char* lbl_806E6130[] = {"N_center_00", "N_1P_Pos_00", "N_2P_Pos_00", NULL};
const char* lbl_806F3228[] = {"P_%carrow_%02d", NULL};
const char* lbl_806F3230[] = {"N_Larrow_00", "N_Rarrow_00"};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void* fn_8026F970(void* lyt, const char* name);
void* fn_8026F960(void* lyt, const char* name);
extern u8 lbl_806E6140[];


void fn_80599B1C(u8* p) { *(u8*)(p + 0x124) = 1; }

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers and state).
void* fn_80599A28(u8* p) {
    fn_80371668(p, 3, "WS2_game_jsk", "65105_jsk_guideArrow", 1, 0, 0);
    u8* v = lbl_806E6140;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(int*)(p + 0x110) = 2;
    *(u8*)(p + 0x124) = 0;
    *(int*)(p + 0x128) = -1;
    return p;
}

// First pass: registers the loop animation and caches the arrow panes and the left arrow position.
void fn_80599748(u8* p) {
    fn_8027035C(p + 0x94, 2, "loop", "G_loop_00", 0);
    *(void**)(p + 0x114) = fn_8026F970(p + 0x94, lbl_806F3230[0]);
    *(void**)(p + 0x118) = fn_8026F970(p + 0x94, lbl_806F3230[1]);
    u8* pane = (u8*)fn_8026F960(p + 0x94, "P_Larrow_00");
    *(f32*)(p + 0x11c) = *(f32*)(pane + 0x44);
    *(f32*)(p + 0x120) = *(f32*)(pane + 0x48);
}

}  // extern "C"
