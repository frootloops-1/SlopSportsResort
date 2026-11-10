// Swf_8064C09C: Resort Swordplay unit 0x8064C09C-0x8064CC58 (Resort-only, no Wii Sports twin).
// common sequence (共通シーケンス).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_8032349C(u8*);
extern u8 lbl_806EEE44[];
extern void* lbl_806EEE18[];
void fn_8060CBC8(u8*, s32);
extern u8* lbl_806F5FF0;

u8* fn_8064CC4C() {
    return lbl_806EEE44;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064CC0C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8064CBC8(u8* p, u32 a) {
    fn_8032349C(p);
    *(void**)p = lbl_806EEE18;
    *(u32*)(p + 0x8) = a;
    return p;
}

void fn_8064CBBC(u8* p) {
    *(u32*)(p + 0xc) = 0;
}

void fn_8064CBB8() {}

void fn_8064C170(u8* p) {
    fn_8060CBC8(*(u8**)(lbl_806F5FF0 + 0x194), 1);
    *(u32*)(p + 0xc) = 0;
}

}  // extern "C"
