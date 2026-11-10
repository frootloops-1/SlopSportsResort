// Resort shared Power Cruising/Wakeboarding engine file 0x80586434-0x80587A3C: class vtable 0x806E56F0 (JetSki / WS2_jsk_koukasen / WS2_wkb_koukasen).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8037DBA8(u8*);
void fn_8037DF1C(u8*);
void fn_8037E1B4(u8*);

void fn_80586450(u8* p) { fn_8037DF1C(*(u8**)(p + 0x2f8)); }

void fn_80586448(u8* p) { fn_8037DBA8(*(u8**)(p + 0x2f8)); }

void fn_80586440(u8* p) { fn_8037E1B4(*(u8**)(p + 0x2f8)); }

void fn_80586434() {}

}  // extern "C"
