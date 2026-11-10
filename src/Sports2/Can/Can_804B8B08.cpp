// Canoeing (Resort-only), .text 0x804B8B08-0x804B8C70: layout 65504_can_restDistance. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_802B73BC();
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680C20[];
extern u8 lbl_806DD240[];

void fn_804B8BEC() {}

u8* fn_804B8B68(u8* p, u32 a1) {
    fn_80371668(p, 0, lbl_80680C20 + 0xe, lbl_80680C20 + 0x1b, 1, 0, a1);
    const char* nm = (const char*)(lbl_80680C20 + 0x32);
    *(u8**)(p + 0x30) = lbl_806DD240;
    *(u8**)(p + 0x18) = lbl_806DD240 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DD240 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DD240 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    return p;
}

void fn_804B8B08() { ((void (*)(void*))fn_802B73BC)((void*)1034); }

}  // extern "C"
