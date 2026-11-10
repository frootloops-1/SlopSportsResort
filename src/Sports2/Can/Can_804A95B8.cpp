// Canoeing (Resort-only), .text 0x804A95B8-0x804A9868: layout 65510_can_Time. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8026F828(u8*, u32, s32, s32, u32, s32, s32);
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
char* strncpy(char* dst, const char* src, unsigned long n);
void fn_804A96A8(u8* p);
extern u8 lbl_806806C8[];
extern u8 lbl_806DC680[];

u8* fn_804A9748(u8* p, u32 a1) {
    fn_80371668(p, 1, lbl_806806C8 + 0x1c, lbl_806806C8 + 0x29, 1, 0, a1);
    const char* nm = (const char*)(lbl_806806C8 + 0x38);
    *(u8**)(p + 0x30) = lbl_806DC680;
    *(u8**)(p + 0x18) = lbl_806DC680 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DC680 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DC680 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    *(u32*)(p + 0x110) = 0;
    *(u32*)(p + 0x114) = 50;
    *(u32*)(p + 0x118) = -1;
    *(u32*)(p + 0x11c) = -1;
    return p;
}

void fn_804A9744(void* p) { ((void (*)(void*))fn_804A96A8)(p); }

void fn_804A96C8() {}

void fn_804A96A8(u8* p) { fn_8026F828(p + 0x94, *(u32*)(p + 0x120), 17, 50, *(u32*)(p + 0x110), 1, 0); }

void fn_804A95B8(u8* p) {
    *(u32*)(p + 0x118) = -1;
    *(u32*)(p + 0x11c) = -1;
}

}  // extern "C"
