// Resort Power Cruising (jsk) file 0x805B53C8-0x805B5AE0: layout 65124_jsk_VS_explain (vtable 0x806E8480).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// MATCH-PENDING (R17): ledger #12. Unused static that only seeds the string pool; inferred, not proven.
// The unit's header declares a (dead-stripped) pane name; its literal still leads the pool.
static const char* sIllustName = "N_illust_00";
// Root pane name table (.data) and text pane name pointers (.sdata).
const char* lbl_806E8468[] = {"N_Hold_Root_00", "N_turn_Root_00", "N_accel_Root_00", "N_btn_Root_00", "N_Hold_Root_01", NULL};
const char* lbl_806F3588[] = {"T_manual_00", "T_manual_01"};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void* fn_8026F6AC(void* lyt, int a);
void fn_8025ED28();
void* fn_8026F970(void* lyt, const char* name);
void* fn_8026F968(void* lyt, const char* name);
extern u8 lbl_806E8480[];


// First pass: layout constructor (base ctor with arc/layout names, vtable pointers, state).
void* fn_805B59D0(u8* p) {
    fn_80371668(p, 7, "WS2_game_jsk", "65124_jsk_VS_explain", 1, 0, 0);
    u8* v = lbl_806E8480;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(int*)(p + 0xa20) = 5;
    *(u8*)(p + 0x114) = 50;
    *(u8*)(p + 0xa38) = 1;
    *(u8*)(p + 0x115) = 0;
    *(u8*)(p + 0x116) = 0;
    return p;
}

// First pass: registers the in/out/turn/accel animations and caches the root and text panes.
void fn_805B5668(u8* p) {
    fn_8027035C(p + 0x94, 2, "in", "G_inOut_01", 0);
    fn_8027035C(p + 0x94, 3, "out", "G_inOut_01", 0);
    fn_8027035C(p + 0x94, 5, "turn", "G_turn_00", 0);
    fn_8027035C(p + 0x94, 6, "accel", "G_accel_00", 0);
    fn_8026FEF0(p + 0x94, 5, 0);
    fn_8026F6AC(p + 0x94, 5);
    fn_8025ED28();
    fn_8026FEF0(p + 0x94, 6, 0);
    fn_8026F6AC(p + 0x94, 6);
    fn_8025ED28();
    for (int i = 0; i < 5; i++) {
        ((void**)(p + 0xa24))[i] = fn_8026F970(p + 0x94, lbl_806E8468[i]);
    }
    for (int i = 0; i < 2; i++) {
        ((void**)(p + 0xa3c))[i] = fn_8026F968(p + 0x94, lbl_806F3588[i]);
    }
}

}  // extern "C"
