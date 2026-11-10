// Canoeing (Resort-only), .text 0x804B727C-0x804B7530: layout 65530_can_explain. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u32);
extern u8 lbl_80680988[];
extern u8 lbl_806DCAF8[];

void fn_804B74AC() {}

u8* fn_804B7438(u8* p, u32 a1) {
    fn_80371668(p, 5, lbl_80680988 + 0x98, lbl_80680988 + 0xa5, 1, 0, a1);
    *(u8**)(p + 0x30) = lbl_806DCAF8;
    *(u8**)(p + 0x18) = lbl_806DCAF8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DCAF8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DCAF8 + 0x88;
    return p;
}

void fn_804B7280(u8* p) {
    fn_8027035C(p + 0x94, 0, lbl_80680988 + 0x39, lbl_80680988 + 0x43, 0);
    fn_8027035C(p + 0x94, 1, lbl_80680988 + 0x52, lbl_80680988 + 0x5b, 0);
    fn_8027035C(p + 0x94, 2, lbl_80680988 + 0x5, lbl_80680988 + 0x69, 0);
    fn_8027035C(p + 0x94, 3, lbl_80680988 + 0xa, lbl_80680988 + 0x73, 0);
    fn_8027035C(p + 0x94, 4, lbl_80680988 + 0x7f, lbl_80680988 + 0x84, 0);
}

void fn_804B727C() {}

}  // extern "C"
