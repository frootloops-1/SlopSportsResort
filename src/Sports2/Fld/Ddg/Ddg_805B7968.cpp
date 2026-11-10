// Ddg_805B7968: Resort Frisbee Dog unit 0x805B7968-0x805BA6C0 (Resort-only, no Wii Sports twin).
// targets/signs: fld_signC_tex_*, WS2_fld_targetA, WS2_fld_signC, WS2_fld_circleShadow, WS2_fld_target_line (vtable 0x806E8820).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

// Deleting destructor of a class without a base destructor.
void* fn_805BA550(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805BA548() { return 5; }

void fn_805B801C() {}

}  // extern "C"
