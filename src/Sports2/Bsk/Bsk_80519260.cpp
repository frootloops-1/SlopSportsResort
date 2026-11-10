// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

extern u8 lbl_807D47E8[];
extern void* lbl_806E0EA0[];
void* fn_8051A4EC(u8* p) {
    *(void**)p = lbl_806E0EA0;
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x14) = 0;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8051A4AC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8051A4A4(u8* p, u32 v) { *(u32*)(p + 0x10) = v; }

f32 fn_8051A418() { return -50.0f; }

f32 fn_8051A284() { return 1.25f; }

void* fn_8051A278() { return lbl_807D47E8; }

BOOL fn_8051A098(u8* p) { return *(s32*)(p + 0x4) == 10; }

void fn_80519438() {}

} // extern "C"
