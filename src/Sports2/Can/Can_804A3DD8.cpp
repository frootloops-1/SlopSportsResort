// Canoeing (Resort-only), .text 0x804A3DD8-0x804A4500: tree (WS2_can_tree, .sdata "Tree"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80359828(u8*, u8*);
void fn_80359908(u8*);
void fn_80359988(u8*);
void fn_8035A050(u8*);
void fn_804A3CF0(u8*);
void fn_804A79C4(u8*, u8*);
extern u8 lbl_806DC020[];

u8* fn_804A44B0(u8* p) {
    fn_804A3CF0(p);
    *(u8**)(p) = lbl_806DC020;
    *(u32*)(p + 0x74) = 0;
    *(u32*)(p + 0x78) = 0;
    *(u32*)(p + 0x7c) = -1;
    return p;
}

void fn_804A41EC() {}

void fn_804A41E8() {}

const char* fn_804A41E0() {
    static char sName[] = "Tree";
    return sName;
}

void fn_804A3FC8(u8* p) {
    f32* v = *(f32**)(p + 0x98);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = v[4] = v[5] = 0.0f;
}

}  // extern "C"
