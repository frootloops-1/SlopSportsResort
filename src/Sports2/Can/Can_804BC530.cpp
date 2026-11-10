// Canoeing (Resort-only), .text 0x804BC530-0x804BD6BC: camera (vtable 0x806DD980, derives from 0x806DBDA0). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_804947A8(u8*);
extern u8* lbl_806F58E8;
extern u8 lbl_806DD980[];

u8* fn_804BD5D0(u8* p, u32 a1, u32 a2) {
    fn_804947A8(p);
    *(u32*)(p + 0x70) = a1;
    *(u8**)(p) = lbl_806DD980;
    *(u32*)(p + 0x74) = a2;
    return p;
}

u32 fn_804BD47C() { return *(u32*)(lbl_806F58E8 + 0x78); }

}  // extern "C"
