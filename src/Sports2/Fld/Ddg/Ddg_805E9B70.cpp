// Ddg_805E9B70: Resort Frisbee Dog unit 0x805E9B70-0x805EA20C (Resort-only, no Wii Sports twin).
// small class with vtable 0x806EACE8.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_805E6298(u8*);
void fn_805E9B70(u8*, u32, u32);

// Deleting destructor of a class without a base destructor.
void* fn_805EA1CC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805EA1B8(u8* p) {
    *(u32*)(p + 0x8) = *(u32*)(p);
    *(u32*)(p + 0xc) = *(u32*)(p);
    *(u32*)(p + 0x10) = *(u32*)(p);
}

void fn_805EA04C(u8* p) {
    fn_805E6298(*(u8**)(p + 0x134));
    *(u32*)(*(u8**)(p + 0x13c) + 0x8) = *(u32*)(*(u8**)(p + 0x13c));
    *(u32*)(*(u8**)(p + 0x13c) + 0xc) = *(u32*)(*(u8**)(p + 0x13c));
    *(u32*)(*(u8**)(p + 0x13c) + 0x10) = *(u32*)(*(u8**)(p + 0x13c));
    *(u32*)(p + 0x140) = 0;
    fn_805E9B70(p + 0x8, *(u32*)(*(u8**)(p + 0x13c)), *(u32*)(p + 0x13c));
}

}  // extern "C"
