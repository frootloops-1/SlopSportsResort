// Resort Basketball (bsk) file 0x80531A10-0x80531C40: class vtable 0x806E18E8 (ctor 0x80531C04).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_805121DC(u8*);
extern u8 lbl_806E18E8[];

u8* fn_80531C04(u8* p) {
    fn_805121DC(p);
    *(u8**)(p) = lbl_806E18E8;
    return p;
}

}  // extern "C"
