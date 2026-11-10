// Swf_8062E938: Resort Swordplay unit 0x8062E938-0x80630330 (Resort-only, no Wii Sports twin).
// Speed Slice sequence (SJIS name 薪割りシーケンス), state functions in 12-byte pointer-to-member tables.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EDD48[];
extern void* lbl_806EDCC8[];

u8* fn_80630324() {
    return lbl_806EDD48;
}

// Deleting destructor of a class without a base destructor.
void* fn_806302E4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806302A0(u8* p, u32 a) {
    fn_8032349C(p);
    *(void**)p = lbl_806EDCC8;
    *(u32*)(p + 0x8) = a;
    return p;
}

void fn_80630260() {}

}  // extern "C"
