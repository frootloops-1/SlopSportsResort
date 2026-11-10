// Resort Power Cruising (jsk) file 0x80597C94-0x80598140: test object, vtable 0x806E5B58 (jsk_test, effect_test).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

// placeholder for an object called through its vtable (vptr at 0x0, slot = offset in the vtable)
struct Unk_V0 {
    virtual void vf08();
};

extern "C" {

void fn_80598114(u8* p) { ((Unk_V0*)p)->vf08(); }

void fn_80598074() {}

void fn_80597F04() {}

void fn_80597F00() {}

void fn_80597EFC() {}

void fn_80597EF8() {}

void fn_80597D40() {}

void fn_80597C94() {}

}  // extern "C"
