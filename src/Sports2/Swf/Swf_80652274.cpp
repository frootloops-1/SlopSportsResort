// Swf_80652274: Resort Swordplay unit 0x80652274-0x8065235C (Resort-only, no Wii Sports twin).
// layout 65050_swf_training_indicate.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_806522E4(u8*, int);

void fn_80652354(u8* p, int a) {
    fn_806522E4(p - 0x94, a);
}

void fn_8065234C(u8* p, int a) {
    fn_806522E4(p - 0x18, a);
}

}  // extern "C"
