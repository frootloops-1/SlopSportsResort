// Resort Basketball (bsk) file 0x80536910-0x805371E4: layout 65420_bsk_3Pcontest_PointCount, vtable 0x806E20F0.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {



void fn_80536B7C(u8* p) {
    *(u8*)(p + 0x116) = 0;
    *(u8*)(p + 0x115) = 0;
}

void fn_805369F0(u8* p, u32 a1) {
    *(u8*)(p + 0x116) = 1;
    *(u32*)(p + 0x11c) = *(u32*)(p + 0x118);
    *(u32*)(p + 0x118) = a1;
}

}  // extern "C"
