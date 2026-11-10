// Resort shared Power Cruising/Wakeboarding engine file 0x80588A6C-0x80589050: object class vtable 0x806E5790 (created by the common object factory fn_8033D45C).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80360F3C(u8*);
extern void* lbl_806E5790[];

u8* fn_80588FF4(u8* p) {
    fn_80360F3C(p);
    *(void**)(p + 0x10) = lbl_806E5790;
    return p;
}

void fn_80588FB0() {}

void fn_80588AD4() {}

void fn_80588AD0() {}

void fn_80588ACC() {}

void fn_80588A84() {}

void fn_80588A6C() {}

}  // extern "C"
