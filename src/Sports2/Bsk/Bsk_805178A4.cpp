// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void fn_80516C3C(void* p, int del); // base dtor
void fn_80517BD8();

// Deleting destructor: only the base destructor runs.
void* fn_80518EC8(void* p, int del) {
    if (p != NULL) {
        fn_80516C3C(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80518EC4() {}

void fn_80518E9C(u8* p) {
    *(u32*)(p + 0x98) = 0;
    for (int i = 0; i < 6; i++) {
        ((u32*)(p + 0x9C))[i] = 0;
    }
}

void fn_80518DF8(u8* p, const f32* f) { *(f32*)(p + 0xB4) = *f; }

void fn_80518344(u8* p) { *(f32*)(p + 0x140) = 120.0f; }

void fn_80518340(void* p) { ((void (*)(void*))fn_80517BD8)(p); }

} // extern "C"
