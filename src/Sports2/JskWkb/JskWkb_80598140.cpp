// Resort shared Power Cruising/Wakeboarding engine file 0x80598140-0x805982C0: object class vtable 0x806E5BC0 (factory-created).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80360F3C(u8*);
extern void* lbl_806E5BC0[];

u8* fn_80598284(u8* p) {
    fn_80360F3C(p);
    *(void**)(p + 0x10) = lbl_806E5BC0;
    return p;
}

void fn_80598240() {}

void fn_80598158() {}

void fn_80598154() {}

void fn_80598150() {}

void fn_8059814C() {}

void fn_80598148() {}

void fn_80598144() {}

void fn_80598140() {}

}  // extern "C"
