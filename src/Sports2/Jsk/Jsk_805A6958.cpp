// Resort Power Cruising (jsk) file 0x805A6958-0x805A6D28: layout 65110_jsk_explain (vtable 0x806E7290).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>
#include <nw4r/math.h>

using nw4r::math::VEC3;

extern "C" {
// Name tables (.data); defined first so the string pool order matches.
const char* lbl_806E7270[] = {"N_Left_00", "N_Right_00", "N_pos_00"};
const char* lbl_806E727C[] = {"N_Hold_Root_00", "N_turn_Root_00", "N_accel_Root_00", "N_btn_Root_00", "N_Hold_Root_01"};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void* fn_8026F6AC(void* lyt, int a);
void fn_8025ED28();
void* fn_8026F970(void* lyt, const char* name);
extern u8 lbl_806E7290[];


// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_805A6C3C(u8* p) {
    fn_80371668(p, 5, "WS2_game_jsk", "65110_jsk_explain", 1, 0, 0);
    u8* v = lbl_806E7290;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    return p;
}

// First pass: registers the turn/accel animations, caches the root panes and the pane positions.
void fn_805A6958(u8* p) {
    fn_8027035C(p + 0x94, 3, "turn", "G_turn_00", 0);
    fn_8027035C(p + 0x94, 4, "accel", "G_accel_00", 0);
    fn_8026FEF0(p + 0x94, 3, 0);
    fn_8026F6AC(p + 0x94, 3);
    fn_8025ED28();
    fn_8026FEF0(p + 0x94, 4, 0);
    fn_8026F6AC(p + 0x94, 4);
    fn_8025ED28();
    for (int i = 0; i < 5; i++) {
        ((void**)(p + 0x114))[i] = fn_8026F970(p + 0x94, lbl_806E727C[i]);
    }
    u8* pane = (u8*)fn_8026F970(p + 0x94, lbl_806E7270[0]);
    *(void**)(p + 0x128) = pane;
    u8* root = *(u8**)(p + 0x114);
    *(f32*)(p + 0x12c) = *(f32*)(pane + 0x2c);
    *(f32*)(p + 0x130) = *(f32*)(pane + 0x30);
    *(f32*)(p + 0x134) = *(f32*)(pane + 0x34);
    u8* a = (u8*)fn_8026F970(p + 0x94, lbl_806E7270[2]);
    u8* b = (u8*)fn_8026F970(p + 0x94, lbl_806E7270[1]);
    VEC3 sum = *(VEC3*)(b + 0x2c) + *(VEC3*)(a + 0x2c);
    VEC3 d = sum - *(VEC3*)(root + 0x2c);
    *(f32*)(p + 0x138) = d.x;
    *(f32*)(p + 0x13c) = d.y;
    *(f32*)(p + 0x140) = d.z;
}

}  // extern "C"
