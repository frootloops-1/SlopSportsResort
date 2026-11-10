// Swf_806464DC: Resort Swordplay unit 0x806464DC-0x8064BC30 (Resort-only, no Wii Sports twin).
// ragdoll (ラグドール) and constraint (コンストレイント); __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

extern u8 lbl_806EED80[];
extern u8 lbl_806EED8C[];
extern char lbl_806F3D20[8];

u8* fn_8064BBA8() {
    return lbl_806EED80;
}

u8* fn_8064BB9C() {
    return lbl_806EED8C;
}

char* fn_8064BB94() {
    return lbl_806F3D20;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064BB54(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064BB14(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064BAD4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8064BA94(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8064B6A0() {}

}  // extern "C"
