// Swf_8065137C: Resort Swordplay unit 0x8065137C-0x80651A64 (Resort-only, no Wii Sports twin).
// layout 65030_swf_tameshi_profDis.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_806519EC(u8*, int);

void fn_80651A5C(u8* p, int a) {
    fn_806519EC(p - 0x94, a);
}

void fn_80651A54(u8* p, int a) {
    fn_806519EC(p - 0x18, a);
}

}  // extern "C"
