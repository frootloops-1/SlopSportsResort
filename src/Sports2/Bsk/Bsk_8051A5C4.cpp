// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

extern void* lbl_806E0EB0[];
void* fn_8051AA38(void* p) {
    *(void**)p = lbl_806E0EB0;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8051A9F8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8051A9F4() {}

} // extern "C"
