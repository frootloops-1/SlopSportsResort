// Resort Power Cruising (jsk) file 0x80599F68-0x8059A320: layout 65100_jsk_pointDis (vtable 0x806E64A8).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// Name tables (.data/.sdata); defined first so the string pool order matches.
const char* lbl_806E6498[] = {"T_point_00", "T_point_01", "T_point_02", NULL};
const char* lbl_806F3248[] = {"P_miiFace_00", NULL};
struct S2 {
    int a, b;
};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void* fn_8026F968(void* lyt, const char* name);
void* fn_8026F960(void* lyt, const char* name);
void fn_8026F760(void* lyt, void* pane, int a, int b);
void fn_8026F768(void* lyt, void* pane, int a);
void fn_8026F7BC(void* lyt, void* pane, int a, int b, S2* v);
void* fn_8027CCC0(int);
extern int lbl_806F9E20;
extern int lbl_806F9E24;
extern u8 lbl_806E64A8[];


// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers and state).
void* fn_8059A210(u8* p) {
    fn_80371668(p, 3, "WS2_game_jsk", "65100_jsk_pointDis", 1, 0, 0);
    u8* v = lbl_806E64A8;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(int*)(p + 0x114) = 0;
    *(int*)(p + 0x118) = 0;
    *(int*)(p + 0x11c) = 0;
    *(int*)(p + 0x120) = 0;
    *(int*)(p + 0x110) = 0;
    *(void**)(p + 0x110) = fn_8027CCC0(0);
    return p;
}

// First pass: updates the circle pane and the point text panes.
void fn_8059A114(u8* p, int a) {
    fn_8026F760(p + 0x94, fn_8026F960(p + 0x94, "P_circle_00"), a, 0);
    S2 tmp;
    tmp.a = lbl_806F9E20;
    tmp.b = lbl_806F9E24;
    fn_8026F7BC(p + 0x94, fn_8026F968(p + 0x94, "T_point_00"), a, 0, &tmp);
    fn_8026F768(p + 0x94, fn_8026F968(p + 0x94, "T_point_01"), a);
}

// First pass: registers the count animation and caches the three point text panes.
void fn_8059A094(u8* p) {
    fn_8027035C(p + 0x94, 2, "count", "G_count_00", 0);
    *(void**)(p + 0x118) = fn_8026F968(p + 0x94, lbl_806E6498[0]);
    *(void**)(p + 0x11c) = fn_8026F968(p + 0x94, lbl_806E6498[1]);
    *(void**)(p + 0x120) = fn_8026F968(p + 0x94, lbl_806E6498[2]);
}

}  // extern "C"
