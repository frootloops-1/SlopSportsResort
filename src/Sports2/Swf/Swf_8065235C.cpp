// Swf_8065235C: Resort Swordplay unit 0x8065235C-0x8065277C (Resort-only, no Wii Sports twin).
// layout 65051_swf_training_profDis.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_80652704(u8*, int);

void fn_80652774(u8* p, int a) {
    fn_80652704(p - 0x94, a);
}

void fn_8065276C(u8* p, int a) {
    fn_80652704(p - 0x18, a);
}

}  // extern "C"
