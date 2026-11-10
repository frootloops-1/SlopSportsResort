// Canoeing (Resort-only), .text 0x804B6D58-0x804B727C. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8035D6C8(u8*);
void fn_804B6DD0(u8* p);
extern u8 lbl_806DCAC0[];

// Deleting destructor of a class without a base destructor.
void* fn_804B723C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_804B7200(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DCAC0;
    return p;
}

void fn_804B7064(u8* p) { *(u8*)(p + 0x8) = 1; }

void fn_804B6DD0(u8* p) {
    *(u32*)(p) = 0;
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    *(u8*)(p + 0xc) = 0;
}

void fn_804B6D58(u8* p) {
    fn_804B6DD0(p);
    fn_804B6DD0(p + 0x10);
    fn_804B6DD0(p + 0x20);
    fn_804B6DD0(p + 0x30);
    fn_804B6DD0(p + 0x40);
    fn_804B6DD0(p + 0x50);
    fn_804B6DD0(p + 0x60);
    fn_804B6DD0(p + 0x70);
    *(u32*)(p + 0x80) = 0;
    *(u32*)(p + 0x84) = 0;
    *(u32*)(p + 0x88) = 0;
    *(u32*)(p + 0x8c) = 0;
}

}  // extern "C"
