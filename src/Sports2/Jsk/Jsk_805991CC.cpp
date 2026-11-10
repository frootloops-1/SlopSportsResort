// Resort Power Cruising (jsk) file 0x805991CC-0x805995D8: layout 65104_jsk_caution (vtable 0x806E6010).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

// placeholder for an object called through its vtable (vptr at 0x30, slot = offset in the vtable)
struct Unk_Pad30 {
    u8 pad[0x30];
};

struct Unk_V30 : Unk_Pad30 {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4C();
};

extern "C" {
// Pane name pointer (.sdata); defined first so the string pool order matches.
const char* lbl_806F3220[] = {"T_caution_00", NULL};
void fn_802703A8(void* lyt, const char* arc, const char* name, int a, int b, int c);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void fn_80270194(void* lyt, int a, int b);
void* fn_8026F968(void* lyt, const char* name);
void* fn_8026F970(void* lyt, const char* name);


void fn_80599234(u8* p) { ((Unk_V30*)p)->vf4C(); }

// First pass: builds the caution layout (arc name, in/count/caution animations, text pane).
void fn_80599458(u8* p) {
    fn_802703A8(p + 0x94, "WS2_game_jsk", "65104_jsk_caution", 1, 0, 0);
    fn_8027035C(p + 0x94, 0, "in", "G_inOut_00", 0);
    fn_8027035C(p + 0x94, 1, "count", "G_count_00", 0);
    fn_8027035C(p + 0x94, 2, "caution", "G_caution_00", 0);
    *(void**)(p + 0x118) = fn_8026F968(p + 0x94, lbl_806F3220[0]);
}

}  // extern "C"
