// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void fn_8051218C(void* p, int del); // base dtor
void* fn_805121DC(void* p, void* a); // Bsk_8051185C ctor
extern void* lbl_806E0A98[];
void fn_80510EBC();

void* fn_80511510(u8* p, void* a) {
    fn_805121DC(p, a);
    *(void**)p = lbl_806E0A98;
    *(u32*)(p + 0x44) = 0;
    return p;
}

// Deleting destructor: only the base destructor runs.
void* fn_805114C0(void* p, int del) {
    if (p != NULL) {
        fn_8051218C(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80511338(void* p) { ((void (*)(void*))fn_80510EBC)(p); }

} // extern "C"
