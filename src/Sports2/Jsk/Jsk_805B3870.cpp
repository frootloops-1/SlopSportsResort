// Resort Power Cruising (jsk) file 0x805B3870-0x805B3AF4: layout 65113_jsk_TimePoint (vtable 0x806E82E8).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {
// Format string pointer (.sdata); defined first so the string pool order matches.
const char* lbl_806F3558[] = {"G_point_%02d", NULL};
void* fn_80371668(void* p, int a, const char* arc, const char* name, int b, int c, int d);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
int snprintf(char* buf, unsigned long n, const char* fmt, ...);
extern u8 lbl_806E82E8[];


// First pass: layout constructor (base ctor with arc/layout names, then vtable pointers).
void* fn_805B39FC(u8* p) {
    fn_80371668(p, 8, "WS2_game_Jsk", "65113_jsk_TimePoint", 1, 0, 0);
    u8* v = lbl_806E82E8;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    *(int*)(p + 0x114) = 0;
    *(int*)(p + 0x110) = 0;
    return p;
}

// First pass: registers the complete animation and the five point-get animations.
void fn_805B3974(u8* p) {
    fn_8027035C(p + 0x94, 2, "complete", "G_complete_00", 0);
    for (int i = 0; i < 5; i++) {
        char name[0x20];
        snprintf(name, 0x20, lbl_806F3558[0], i);
        fn_8027035C(p + 0x94, i + 3, "timeGet", name, 0);
    }
}

}  // extern "C"
