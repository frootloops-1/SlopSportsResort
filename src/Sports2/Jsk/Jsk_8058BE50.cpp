// Resort Power Cruising (jsk) file 0x8058BE50-0x8058D034: class vtable 0x806E5898 (calls jsk-only course objects).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80348DCC(u8*);
void fn_8058D038(u8*);
void fn_805934EC(u8*);
void fn_80593568(u8*);
void fn_805935D4(u8*);

void fn_8058C074(u8* p) { fn_805935D4(*(u8**)(p + 0x38)); }

void fn_8058C02C() {}

void fn_8058C024(u8* p) { fn_80593568(*(u8**)(p + 0x38)); }

void fn_8058C01C(u8* p) { fn_805934EC(*(u8**)(p + 0x38)); }

void fn_8058C018() {}

void fn_8058BFC0() {}

void fn_8058BF68(u8* p) { fn_80348DCC(p); }

void fn_8058BF64() {}

void fn_8058BF04() {}

void fn_8058BE58(u8* p) { fn_8058D038(*(u8**)(p + 0x34)); }

void fn_8058BE54() {}

void fn_8058BE50() {}

}  // extern "C"
