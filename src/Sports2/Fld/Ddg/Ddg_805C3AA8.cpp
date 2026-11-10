// Ddg_805C3AA8: Resort Frisbee Dog unit 0x805C3AA8-0x805C7090 (Resort-only, no Wii Sports twin).
// dog animation/model: WS2_fld_dog_* animation and effect names, WS2_fld_dog.brres (vtable 0x806E8FA8).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {
extern u32 lbl_80688C30[];

// Deleting destructor of a class without a base destructor.
void* fn_805C6E44(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805C6E3C() { return 14; }

void fn_805C6268() {}

u32 fn_805C625C(u8* p) { return *(u32*)(*(u8**)(p + 0x164) + 0x40); }

u32 fn_805C6248(u8*, s32 i) { return lbl_80688C30[i]; }

}  // extern "C"
