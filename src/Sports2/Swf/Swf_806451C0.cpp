// Swf_806451C0: Resort Swordplay unit 0x806451C0-0x80645564 (Resort-only, no Wii Sports twin).
// layout 65022_swf_kumite_life.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_806454EC(u8*, int);
void fn_8026FEF0(u8*, s32, s32);
u8* fn_8026F6AC(u8*, s32);
void fn_8025ED28(u8*);

void fn_8064555C(u8* p, int a) {
    fn_806454EC(p - 0x94, a);
}

void fn_80645554(u8* p, int a) {
    fn_806454EC(p - 0x18, a);
}

void fn_806452DC(u8* p) {
    fn_8026FEF0(p + 0x94, 2, 0);
    fn_8025ED28(fn_8026F6AC(p + 0x94, 2));
    fn_8026FEF0(p + 0x94, 3, 0);
    fn_8025ED28(fn_8026F6AC(p + 0x94, 3));
    fn_8026FEF0(p + 0x94, 4, 0);
    fn_8025ED28(fn_8026F6AC(p + 0x94, 4));
}

}  // extern "C"
