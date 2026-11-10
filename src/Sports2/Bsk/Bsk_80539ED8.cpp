// Resort Basketball (bsk) file 0x80539ED8-0x8053AB50: ball stand, vtables 0x806E26A0/0x806E26D8.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80356CA0(u8*);
void fn_80515384(u8*);
extern u8 lbl_806E26D8[];

u8* fn_8053AA44(u8* p) {
    fn_80515384(p);
    *(u8**)(p) = lbl_806E26D8;
    return p;
}

void fn_8053A3C8(u8* p) { fn_80356CA0(*(u8**)(p + 0x94)); }

void fn_8053A3C4() {}

}  // extern "C"
