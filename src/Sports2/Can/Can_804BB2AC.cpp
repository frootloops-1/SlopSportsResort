// Canoeing (Resort-only), .text 0x804BB2AC-0x804BB5F4: layout 65507_can_getDuck_Number. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680EB0[];
extern u8 lbl_806DD6E8[];

void fn_804BB570() {}

u8* fn_804BB4DC(u8* p, u32 a1) {
    fn_80371668(p, 1, lbl_80680EB0 + 0x1f, lbl_80680EB0 + 0x2c, 1, 0, a1);
    const char* nm = (const char*)(lbl_80680EB0 + 0x45);
    *(u8**)(p + 0x30) = lbl_806DD6E8;
    *(u8**)(p + 0x18) = lbl_806DD6E8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DD6E8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DD6E8 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    *(u32*)(p + 0x110) = 0;
    *(u32*)(p + 0x114) = 0;
    *(u16*)(p + 0x11c) = 0;
    return p;
}

void fn_804BB2AC() {}

}  // extern "C"
