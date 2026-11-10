// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void fn_80357524(void* p, int del); // base dtor
void fn_80357564(void* p); // base ctor
extern void* lbl_806E0AD8[];
extern u32 sTVMode__Q23EGG6Screen;
void* fn_805121DC(u8* p, void* a) {
    fn_80357564(p);
    *(void**)p = lbl_806E0AD8;
    *(void**)(p + 0x38) = a;
    *(u32*)(p + 0x3C) = 0;
    *(f32*)(p + 0x40) = sTVMode__Q23EGG6Screen == 0 ? 1.18f : 1.0f;
    return p;
}

// Deleting destructor: only the base destructor runs.
void* fn_8051218C(void* p, int del) {
    if (p != NULL) {
        fn_80357524(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8051213C(u8* p) {
    u8* a = *(u8**)(p + 0x38);
    u8* o = *(u8**)(a + 4);
    *(f32*)(p + 0x4) = *(f32*)(o + 0xC0);
    *(f32*)(p + 0x8) = *(f32*)(o + 0xC4);
    *(f32*)(p + 0xC) = *(f32*)(o + 0xC8);
    o = *(u8**)(a + 4);
    *(f32*)(p + 0x10) = *(f32*)(o + 0xCC);
    *(f32*)(p + 0x14) = *(f32*)(o + 0xD0);
    *(f32*)(p + 0x18) = *(f32*)(o + 0xD4);
    *(f32*)(p + 0x28) = *(f32*)(*(u8**)(*(u8**)(a + 0x38) + 0x10) + 0x10);
}

void fn_80511B0C(void*, u8* p) { *(u32*)(p + 0x0) = 0; }

} // extern "C"
