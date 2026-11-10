// Swf_8064E330: Resort Swordplay unit 0x8064E330-0x8064E568 (Resort-only, no Wii Sports twin).
// layout 65024_swf_kumite_roundDis.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8064E4F0(u8*, int);
extern s32 lbl_806F3D58;
void fn_802B7138(s32);

void fn_8064E560(u8* p, int a) {
    fn_8064E4F0(p - 0x94, a);
}

void fn_8064E558(u8* p, int a) {
    fn_8064E4F0(p - 0x18, a);
}

void fn_8064E330(u8* p) {
    if (lbl_806F3D58 == *(s32*)(p + 0x74)) {
        fn_802B7138(0x17);
    }
}

}  // extern "C"
