// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVObj { virtual void vf08(); virtual void vf0C(); };
extern void* lbl_806E0EC0[];
void* fn_8051AA38(void* p); // Bsk_8051A5C4 ctor
void* fn_8051B7FC(u8* p) {
    *(void**)p = lbl_806E0EC0;
    *(u32*)(p + 0xC) = 0;
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x14) = 0;
    void* o = operator new(4);
    if (o != NULL) {
        o = fn_8051AA38(o);
    }
    *(void**)(p + 0x14) = o;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8051B7BC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8051B7B4(u8* p, u32 v) { *(u32*)(p + 0xc) = v; }

void fn_8051B780(u8* p) {
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0x4) = 0;
    *(f32*)(p + 0x18) = 0.0f;
    *(f32*)(p + 0x1C) = 0.0f;
    *(f32*)(p + 0x20) = 0.0f;
    p[0x24] = 0;
    (*(UnkVObj**)(p + 0x14))->vf0C();
}

void fn_8051B774(u8* p) { *(f32*)(p + 0x20) = 0.0f; }

f32 fn_8051B76C(u8* p) { return *(f32*)(p + 0x20); }

} // extern "C"
