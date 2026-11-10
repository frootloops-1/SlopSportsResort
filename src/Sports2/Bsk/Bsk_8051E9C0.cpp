// Resort Basketball (bsk) file 0x8051E9C0-0x80520E80: class with vtables 0x806E0EF0/0x806E0F98/0x806E0FF0 (ctor 0x805208A0), button/defense-mark icons.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt38 {
    u8 unk0[0x38];
    virtual void vf8();
    virtual void vfC();
};

void fn_80357194(u8*, u8*);
void fn_8050B4B8(u8*);
void fn_80535DB4(u8*, u32, u8*);
extern u8* lbl_806F5A28;

void fn_80520558(u8* p) { ((Unk_VtAt38*)(p))->vfC(); }

void fn_80520114(u8* p) {
    fn_80535DB4(*(u8**)(lbl_806F5A28 + 0x328), *(u32*)(p + 0x128), lbl_806F5A28);
}

void fn_8051FA6C(u8* p) { fn_80357194(p, p + 0xec); }

void fn_8051F954(u8* p) { fn_8050B4B8(*(u8**)(*(u8**)(*(u8**)(p + 0x118)) + 0x158)); }

void fn_8051EDBC() {}

void fn_8051EDB8() {}

void fn_8051ECE0() {}

void fn_8051EA80() {}

void fn_8051EA7C() {}

void fn_8051E9C0() {}

}  // extern "C"
