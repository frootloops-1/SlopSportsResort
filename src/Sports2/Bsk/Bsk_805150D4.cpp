// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVec3f { f32 x, y, z; };
void fn_80516C3C(void* p, int del); // base dtor
void* fn_80516C7C(void* p); // Bsk_80516B18 base ctor
extern void* lbl_806E0DA0[];
extern f32 lbl_807D1564[3];
void* fn_80515384(u8* p) {
    fn_80516C7C(p);
    *(void**)p = lbl_806E0DA0;
    *(f32*)(p + 0x94) = lbl_807D1564[0];
    *(f32*)(p + 0x98) = lbl_807D1564[1];
    *(f32*)(p + 0x9C) = lbl_807D1564[2];
    return p;
}

// Deleting destructor: only the base destructor runs.
void* fn_80515334(void* p, int del) {
    if (p != NULL) {
        fn_80516C3C(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80515330() {}

void fn_80515314(u8* p, const UnkVec3f* v) { *(UnkVec3f*)(p + 0x94) = *v; }

} // extern "C"
