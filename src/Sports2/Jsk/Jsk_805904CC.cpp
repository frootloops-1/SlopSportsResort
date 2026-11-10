// Resort Power Cruising (jsk) file 0x805904CC-0x80594890: ring objects, vtables 0x806E5A98/0x806E5AC8/0x806E5A64 (WS2_jsk_ring*, gates).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80590914(u8*);
extern void* lbl_806F5DC0;

u32 fn_80594560(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

u32 fn_80594550(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_80594544(u8* p) { *(u16*)(p + 0x2) = 0; }

u32 fn_80594478(u8* p, s32 i) { return (*(u32**)(p + 0x4))[i]; }

void fn_8059446C(u8* p) { *(u16*)(p + 0x2) = 0; }

void fn_80593884() {}

void fn_80593880() {}

void* fn_80592E90() { return lbl_806F5DC0; }

void fn_80592298(u8* p) {
    u8* q = *(u8**)(p + 0x40);
    if (q != NULL) {
        fn_80590914(q);
    }
}

void fn_805910F4() {}

}  // extern "C"
