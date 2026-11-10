// Canoeing (Resort-only), .text 0x804BB5F4-0x804BB85C: layout 65508_can_Duck_Result. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_802B73BC();
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680F00[];
extern u8 lbl_806DD810[];

void fn_804BB7D8() {}

u8* fn_804BB754(u8* p, u32 a1) {
    fn_80371668(p, 1, lbl_80680F00 + 0x3c, lbl_80680F00 + 0x49, 1, 0, a1);
    const char* nm = (const char*)(lbl_80680F00 + 0x5f);
    *(u8**)(p + 0x30) = lbl_806DD810;
    *(u8**)(p + 0x18) = lbl_806DD810 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DD810 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DD810 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    return p;
}

void fn_804BB5FC(u8* p) { fn_8027035C(p + 0x94, 0, lbl_80680F00, lbl_80680F00 + 0x8, 0); }

void fn_804BB5F4() { ((void (*)(void*))fn_802B73BC)((void*)1037); }

}  // extern "C"
