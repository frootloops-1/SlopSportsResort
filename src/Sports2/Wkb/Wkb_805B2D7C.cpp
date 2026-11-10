// Resort Wakeboarding (wkb) file 0x805B2D7C-0x805B3070: layout 66010_wkb_pointGet (vtable 0x806E7F68).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
struct S2 {
    int a, b;
};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void* fn_8026F968(void* lyt, const char* name);
void* fn_8026F960(void* lyt, const char* name);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026F7FC(void* lyt, void* a, void* b, int c, int d, int e, int f, int g, int h);
void fn_80371554(void* p);
void fn_8026F768(void* lyt, void* pane, int a);
void fn_8026F7BC(void* lyt, void* pane, int a, int b, S2* v);
void fn_8026F760(void* lyt, void* pane, int a, int b);
void fn_8027CEB8(void* pane, void* c, int d);
extern int lbl_806F9E20;
extern int lbl_806F9E24;
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_806E7F68[];


void fn_805B2FF4() {}

// First pass: layout constructor (base ctor with arc/layout names, vtable pointers, layout name copy).
void* fn_805B2F70(u8* p) {
    fn_80371668(p, 1, "WS2_game_Wkb", "66010_wkb_pointGet", 1, 0, 0);
    const char* nm = "PointGet";
    u8* v = lbl_806E7F68;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    strncpy((char*)(p + 0x34), nm, 0x20);
    return p;
}

// First pass: looks up the score/point text panes and the circle picture, then registers the jump anim.
void fn_805B2EF8(u8* p) {
    *(void**)(p + 0x110) = fn_8026F968(p + 0x94, "T_jumpScore_00");
    *(void**)(p + 0x114) = fn_8026F968(p + 0x94, "T_jumpPt_00");
    *(void**)(p + 0x118) = fn_8026F960(p + 0x94, "P_circle_00");
    fn_8027035C(p + 0x94, 0, "pointGet", "G_jump_00", 0);
}

// First pass: sets the point value and updates the layout panes (and the mii face when given).
void fn_805B2E20(u8* p, int a, int b, void* c) {
    *(int*)(p + 0x11c) = a;
    fn_8026F7FC(p + 0x94, *(void**)(p + 0x110), *(void**)(p + 0x114), 1, 0x32, 0x33, *(int*)(p + 0x11c), 0, 0);
    fn_80371554(p);
    fn_8026F768(p + 0x94, *(void**)(p + 0x114), b);
    S2 tmp;
    tmp.a = lbl_806F9E20;
    tmp.b = lbl_806F9E24;
    fn_8026F7BC(p + 0x94, *(void**)(p + 0x110), b, 0, &tmp);
    fn_8026F760(p + 0x94, *(void**)(p + 0x118), b, 0);
    if (c != NULL) {
        fn_8027CEB8(fn_8026F960(p + 0x94, "P_miiFace_00"), c, 0);
    }
}

void fn_805B2E1C() {}

}  // extern "C"
