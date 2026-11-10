// Swf_8064BC30: Resort Swordplay unit 0x8064BC30-0x8064C09C (Resort-only, no Wii Sports twin).
// Duel opening (対戦オープニング).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_805FF170(u8*);
extern u8 lbl_806EEE00[];
extern void* lbl_806EEDA0[];
void fn_805FF02C(u8*);

int fn_8064C094() {
    return 1;
}

u8* fn_8064C088() {
    return lbl_806EEE00;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064C048(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8064C00C(u8* p) {
    fn_805FF170(p);
    *(void**)p = lbl_806EEDA0;
    return p;
}

void fn_8064BC30(u8* p) {
    fn_805FF02C(p);
}

}  // extern "C"
