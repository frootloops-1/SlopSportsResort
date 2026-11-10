// Canoeing (Resort-only), .text 0x804B888C-0x804B8A00: layout 65502_can_TimeLimit. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8035FB88(u8*, u8*, u8*, s32, s32, u32, u8*, u8*);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680BA8[];
extern u8 lbl_806DD000[];

u8* fn_804B88F8(u8* p, u32 a1) {
    fn_8035FB88(p, lbl_80680BA8 + 0xa, lbl_80680BA8 + 0x17, 1, 0, a1, lbl_80680BA8 + 0x2b, lbl_80680BA8 + 0x31);
    const char* nm = (const char*)(lbl_80680BA8 + 0x3c);
    *(u8**)(p + 0x30) = lbl_806DD000;
    *(u8**)(p + 0x18) = lbl_806DD000 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DD000 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DD000 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    *(u32*)(p + 0x114) = 0;
    return p;
}

void fn_804B888C() {}

}  // extern "C"
