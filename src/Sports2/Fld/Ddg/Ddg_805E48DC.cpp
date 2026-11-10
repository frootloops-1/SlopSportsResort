// Ddg_805E48DC: Resort Frisbee Dog unit 0x805E48DC-0x805E5264 (Resort-only, no Wii Sports twin).
// field/map: DiskDog.carc, WS2_fld_field.brres/.kcl/.pmp, WS2_fld_field_atDemo (vtable 0x806EAB40).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

// Deleting destructor of a class without a base destructor.
void* fn_805E5224(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

}  // extern "C"
