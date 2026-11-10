// Resort Basketball (bsk) file 0x8052B120-0x8052B34C: class vtable 0x806E14B8 (ctor 0x8052B310).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_805121DC(u8*);
extern u8 lbl_806E14B8[];

u8* fn_8052B310(u8* p) {
    fn_805121DC(p);
    *(u8**)(p) = lbl_806E14B8;
    return p;
}

}  // extern "C"
