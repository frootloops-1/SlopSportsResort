// Resort shared Power Cruising/Wakeboarding engine file 0x80583C50-0x80586434: class vtable 0x806E563C (shared callers).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8059E008(u8*);
extern u8 lbl_80702EE0;

void fn_80585418(u8* p) { fn_8059E008(*(u8**)(p + 0x744)); }

void fn_80584A30() {}

void fn_80584A2C() {}

void* fn_8058490C() { return &lbl_80702EE0; }

}  // extern "C"
