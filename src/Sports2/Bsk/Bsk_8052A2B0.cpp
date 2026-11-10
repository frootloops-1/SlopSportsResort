// Resort Basketball (bsk) file 0x8052A2B0-0x8052AB40: class vtable 0x806E1488 (ctor 0x8052AA84).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_805121DC(u8*);
extern u8 lbl_806E1488[];

u8* fn_8052AA84(u8* p) {
    fn_805121DC(p);
    *(u8**)(p) = lbl_806E1488;
    return p;
}

}  // extern "C"
