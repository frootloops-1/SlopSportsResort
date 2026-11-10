// Swf_80643A54: Resort Swordplay unit 0x80643A54-0x80643B54 (Resort-only, no Wii Sports twin).
// rule base (ルール基底).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_80328488(u8*);
extern u8 lbl_806EE880[];
extern void* lbl_806EE830[];

u8* fn_80643B48() {
    return lbl_806EE880;
}

u8* fn_80643B0C(u8* p) {
    fn_80328488(p);
    *(void**)p = lbl_806EE830;
    return p;
}

}  // extern "C"
