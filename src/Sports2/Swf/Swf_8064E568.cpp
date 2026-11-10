// Swf_8064E568: Resort Swordplay unit 0x8064E568-0x8064E7B4 (Resort-only, no Wii Sports twin).
// layout 65025_swf_kumite_ResultText.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8064E73C(u8*, int);
void fn_8027035C(u8*, s32, const char*, const char*, s32);

void fn_8064E7AC(u8* p, int a) {
    fn_8064E73C(p - 0x94, a);
}

void fn_8064E7A4(u8* p, int a) {
    fn_8064E73C(p - 0x18, a);
}

void fn_8064E6A8(u8* p) {
    fn_8027035C(p + 0x94, 2, "loop", "G_inOut_00", 0);
}

}  // extern "C"
