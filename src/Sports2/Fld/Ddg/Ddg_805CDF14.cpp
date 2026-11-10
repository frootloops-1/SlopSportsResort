// Ddg_805CDF14: Resort Frisbee Dog unit 0x805CDF14-0x805CEE7C (Resort-only, no Wii Sports twin).
// catch marks: WS2_fld_signA/B, WS2_fld_mark_success/miss, WS2_fld_circleShadow.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_80334984(u8*);
extern u8 lbl_806E9FEC[];

// Deleting destructor of a class without a base destructor.
void* fn_805CEE1C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_805CEDE0(u8* p) {
    fn_80334984(p);
    *(u8**)(p) = lbl_806E9FEC;
    return p;
}

}  // extern "C"
