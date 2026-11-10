// Resort Power Cruising (jsk) file 0x805AC80C-0x805ACC08: layouts 65111_jsk_holdRemote / 65112_jsk_Advice_explain (vtables 0x806E7838/0x806E7958).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// MATCH-PENDING (R17): ledger #12. Unused static that only seeds the string pool; inferred, not proven.
// The unit's header declares a (dead-stripped) pane name array; its literals still lead the pool.
static const char* sPaneNames[] = {"N_Left_00", "N_Right_00", "N_pos_00"};
// Root pane name pointers (.sdata).
const char* lbl_806F3458[] = {"N_accel_Root_00", "N_dash_Root_00"};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void* fn_8026F6AC(void* lyt, int a);
void fn_8025ED28();
void* fn_8026F970(void* lyt, const char* name);
extern u8 lbl_806E7838[];
extern u8 lbl_806E7958[];


// First pass: layout constructor (base ctor with arc/layout names, vtable pointers, name array).
void* fn_805ACA90(u8* p) {
    fn_80371668(p, 4, "WS2_game_jsk", "65112_jsk_Advice_explain", 1, 0, 0);
    u8* v = lbl_806E7958;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(int*)(p + 0x114) = 0;
    *(void**)(p + 0x114) = operator new[](8);
    return p;
}

// First pass: registers the accel/dash animations and caches the two root panes.
void fn_805AC880(u8* p) {
    fn_8027035C(p + 0x94, 2, "accel", "G_accel_00", 0);
    fn_8027035C(p + 0x94, 3, "dash", "G_dash_00", 0);
    fn_8026FEF0(p + 0x94, 2, 0);
    fn_8026F6AC(p + 0x94, 2);
    fn_8025ED28();
    fn_8026FEF0(p + 0x94, 3, 0);
    fn_8026F6AC(p + 0x94, 3);
    fn_8025ED28();
    for (int i = 0; i < 2; i++) {
        ((void**)*(void**)(p + 0x114))[i] = fn_8026F970(p + 0x94, lbl_806F3458[i]);
    }
}

// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_805AC80C(u8* p) {
    fn_80371668(p, 2, "WS2_game_jsk", "65111_jsk_holdRemote", 1, 0, 0);
    u8* v = lbl_806E7838;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    return p;
}

}  // extern "C"
