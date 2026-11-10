// Canoeing (Resort-only), .text 0x804A9868-0x804A9C80: layout 65520_can_TableScore. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80270194(u8*, u8*, u8*);
void fn_80371554(u8*);
void fn_804A987C(u8*, u32);

void fn_804A9AEC(u8* p) {
    fn_80270194(p + 0x94, *(u8**)(*(u8**)(p + 0x120)) + -0x1, *(u8**)(*(u8**)(p + 0x120)) + 0x3);
    fn_80371554(p);
    fn_804A987C(p, *(u32*)(p + 0x120));
}

void fn_804A9A1C() {}

void fn_804A9868(u8* p, s32 a1, u32 a2, u32 a3) {
    *(u32*)(p + a1 * 4 + 0x4) = a2;
    *(u32*)(p + a1 * 4 + 0x14) = a3;
}

}  // extern "C"
