// Swf_8064CF28: Resort Swordplay unit 0x8064CF28-0x8064E0EC (Resort-only, no Wii Sports twin).
// layout 65021_swf_kumite_enemyName; __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8064E05C(u8*, int);

void fn_8064E0E4(u8* p, int a) {
    fn_8064E05C(p - 0x94, a);
}

void fn_8064E0DC(u8* p, int a) {
    fn_8064E05C(p - 0x18, a);
}

}  // extern "C"
