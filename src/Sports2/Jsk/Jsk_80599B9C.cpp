// Resort Power Cruising (jsk) file 0x80599B9C-0x80599DEC: layout 65106_jsk_tachometer (vtable 0x806E6260).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// Pane name pointer (.sdata); defined first so the string pool order matches.
const char* lbl_806F3240[] = {"N_center_00", NULL};
void fn_802703A8(void* lyt, const char* arc, const char* name, int a, int b, int c);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void fn_80270194(void* lyt, int a, int b);
void* fn_8026F968(void* lyt, const char* name);
void* fn_8026F970(void* lyt, const char* name);
void* fn_8026F6CC(void* lyt);
void* fn_8025CE24(void* a);


// First pass: builds the tachometer layout (arc name, in/out/upDown animations, panes).
void fn_80599C2C(u8* p) {
    fn_802703A8(p + 0x94, "WS2_game_jsk", "65106_jsk_tachometer", 1, 0, 0);
    fn_8027035C(p + 0x94, 0, "in", "G_upDown_00", 0);
    fn_8027035C(p + 0x94, 1, "out", "G_upDown_00", 0);
    fn_8027035C(p + 0x94, 2, "upDown", "G_upDown_00", 0);
    fn_8026FEF0(p + 0x94, 0, 0);
    fn_8026FEF0(p + 0x94, 1, 0);
    fn_80270194(p + 0x94, 0, 1);
    *(void**)(p + 0x114) = fn_8025CE24(fn_8026F6CC(p + 0x94));
    *(void**)(p + 0x118) = fn_8026F970(p + 0x94, lbl_806F3240[0]);
}

}  // extern "C"
