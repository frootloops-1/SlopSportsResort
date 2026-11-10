// Resort Basketball (bsk) file 0x80534CCC-0x80535268: layout 65400_bsk_PointCount, vtable 0x806E1BF8.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8025ED28(u8*);
u8* fn_8026F6AC(u8*, s32);
void fn_8026FEF0(u8*, s32, s32);

void fn_80534E64(u8* p) {
    fn_8026FEF0(p + 0x94, 2, 0);
    u8* t1 = fn_8026F6AC(p + 0x94, 2);
    fn_8025ED28(t1);
    fn_8026FEF0(p + 0x94, 3, 0);
    u8* t4 = fn_8026F6AC(p + 0x94, 3);
    fn_8025ED28(t4);
    *(u8*)(p + 0x118) = 0;
    *(u32*)(p + 0x11c) = 0;
    *(u32*)(p + 0x120) = 0;
}

void fn_80534D3C(u8* p, u32 a1, u32 a2) {
    *(u8*)(p + 0x118) = 1;
    *(u32*)(p + 0x11c) = a1;
    *(u32*)(p + 0x120) = a2;
}

}  // extern "C"
