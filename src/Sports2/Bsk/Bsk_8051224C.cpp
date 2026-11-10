// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVec3w { u32 x, y, z; };
extern void* lbl_806E0AF8[];
void fn_80356330(void* a, void* b, void* c);
void* fn_80512930(u8* p, u32 x) {
    *(void**)p = lbl_806E0AF8;
    *(u32*)(p + 8) = x;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805128F0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805127AC(u8* p, void* out) { fn_80356330(out, p + 0x3C, p + 0xC); }

void fn_80512460() {}

void fn_8051245C() {}

} // extern "C"
