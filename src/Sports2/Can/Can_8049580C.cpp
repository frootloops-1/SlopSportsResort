// Canoeing (Resort-only), .text 0x8049580C-0x80495CD8. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8035D6C8(u8*);
extern u8 lbl_806DBDF0[];

void fn_80495C24(u8* p, u32 a1) {
    *(u32*)(p + 0x14) = a1;
    *(u32*)(*(u8**)(p + 0x10) + 0x8) = a1;
}

// Deleting destructor of a class without a base destructor.
void* fn_80495BE4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80495BA8(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DBDF0;
    return p;
}

}  // extern "C"
