// Resort Power Cruising (jsk) file 0x805B5AE0-0x805B5FD8: layout 65122_jsk_VS_caution (vtable 0x806E85A0).
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
// Pane name pointers (.sdata); defined first so the string pool order matches.
const char* lbl_806F3590 = "T_caution_00";
const char* lbl_806F3594 = "N_center_00";
const char* lbl_806F3598[] = {"N_%dP_Pos_00", NULL};
void fn_802703A8(void* lyt, const char* arc, const char* name, int a, int b, int c);
void fn_8027035C(void* lyt, int idx, const char* anim, const char* group, int b);
void fn_8026FEF0(void* lyt, int a, int b);
void fn_80270194(void* lyt, int a, int b);
void* fn_8026F968(void* lyt, const char* name);
void* fn_8026F970(void* lyt, const char* name);


void fn_805B5BD8(u8* p) { ((Unk_V30*)p)->vf4C(); }

// First pass: builds the VS caution layout (arc name, in/count/caution animations, text pane).
void fn_805B5E40(u8* p) {
    fn_802703A8(p + 0x94, "WS2_game_jsk", "65122_jsk_VS_caution", 1, 0, 0);
    fn_8027035C(p + 0x94, 0, "in", "G_inOut_00", 0);
    fn_8027035C(p + 0x94, 1, "count", "G_count_00", 0);
    fn_8027035C(p + 0x94, 2, "caution", "G_caution_00", 0);
    *(void**)(p + 0x124) = fn_8026F968(p + 0x94, lbl_806F3590);
}

}  // extern "C"
