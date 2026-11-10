// Ddg_805C29FC: Resort Frisbee Dog unit 0x805C29FC-0x805C3AA8 (Resort-only, no Wii Sports twin).
// class with vtable 0x806E8D68 (draw-pass object, own .sdata2 pool 0.85/1.0).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

// Deleting destructor of a class without a base destructor.
void* fn_805C3A68(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805C3868() {}

void fn_805C3090() {}

void fn_805C308C() {}

void fn_805C2A00() {}

void fn_805C29FC() {}

}  // extern "C"
