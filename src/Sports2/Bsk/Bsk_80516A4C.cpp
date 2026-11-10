// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

extern void* lbl_806E0DF0[];
void* fn_80516AEC(u8* p, f32 f) {
    *(void**)p = lbl_806E0DF0;
    *(f32*)(p + 0x4) = f;
    *(f32*)(p + 0x8) = 0.0f;
    *(f32*)(p + 0xC) = 0.0f;
    *(f32*)(p + 0x10) = 0.0f;
    *(f32*)(p + 0x14) = 0.0f;
    *(f32*)(p + 0x18) = 0.0f;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80516AAC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

} // extern "C"
