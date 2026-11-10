// Resort Basketball (bsk) file 0x80529D10-0x8052A2B0: class with vtables 0x806E13D8/0x806E1408/0x806E1440 (ctor 0x80529FB8).
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
void fn_80367544(u8*);
void fn_803676CC(u8*);
void fn_80367CE8(u8*);
void fn_80528340(u8*);
void fn_80528440(u8*);

void fn_80529EA8(u8* p, u8 a1, f32 fa1, f32 fa2) {
    *(u8*)(p + 0x9d) = a1;
    *(u8*)(p + 0x9c) = 0;
    *(f32*)(p + 0xa4) = fa1;
    *(f32*)(p + 0xa0) = fa2;
    fn_80357194(p, p + 0x68);
}

void fn_80529EA0(u8* p) { fn_803676CC(*(u8**)(p + 0x94)); }

void fn_80529E64(u8* p) {
    fn_80367544(*(u8**)(p + 0x94));
    fn_80357194(p, p + 0x3c);
}

void fn_80529E24(u8* p) {
    ((Unk_VtAt38*)(p))->vfC();
    fn_80528440(*(u8**)(p + 0x94));
}

void fn_80529DEC(u8* p) {
    fn_80528340(*(u8**)(p + 0x94));
    fn_80367CE8(*(u8**)(p + 0x94));
}

f32 fn_80529DE4(u8* p) { return *(f32*)(p + 0xa4); }

void fn_80529DE0() {}

void fn_80529DDC() {}

}  // extern "C"
