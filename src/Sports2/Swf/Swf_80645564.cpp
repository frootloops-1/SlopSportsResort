// Swf_80645564: Resort Swordplay unit 0x80645564-0x806457E0 (Resort-only, no Wii Sports twin).
// layout 65020_swf_kumite_enemyNumber.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_80645768(u8*, int);

void fn_806457D8(u8* p, int a) {
    fn_80645768(p - 0x94, a);
}

void fn_806457D0(u8* p, int a) {
    fn_80645768(p - 0x18, a);
}

}  // extern "C"
