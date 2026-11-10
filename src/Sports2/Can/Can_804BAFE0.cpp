// Canoeing (Resort-only), .text 0x804BAFE0-0x804BB2AC: layout 65506_can_duckPoint. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
void fn_804BB110(u8*, s32);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680E68[];
extern u8 lbl_806DD5C0[];

void fn_804BB224(u8* p) { fn_804BB110(p, 0); }

u8* fn_804BB198(u8* p, u32 a1) {
    fn_80371668(p, 10, lbl_80680E68 + 0x16, lbl_80680E68 + 0x23, 1, 0, a1);
    const char* nm = (const char*)(lbl_80680E68 + 0x37);
    u8* v = lbl_806DD5C0;
    *(u8**)(p + 0x30) = v;
    *(u8**)(p + 0x18) = v + 0x8;
    *(u8**)(p + 0x94) = v + 0x78;
    *(u8**)(p + 0x98) = v + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    *(u32*)(p + 0x110) = 0;
    return p;
}

void fn_804BB09C() {}

}  // extern "C"
