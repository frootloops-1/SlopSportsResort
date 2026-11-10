// Resort shared Power Cruising/Wakeboarding engine file 0x8058F908-0x805904CC: class vtable 0x806E59B8 (factory-created).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8028BDF4(u8*);
void fn_8028C380(u8*);
void fn_8058FAC8(u8*);
void fn_805956D4(u8*);

void fn_8058FB60() {}

void fn_8058FB5C() {}

void fn_8058FB58() {}

void fn_8058FB54(u8* p) { fn_8058FAC8(p); }

void fn_8058FAC0(u8* p) { fn_8028BDF4(*(u8**)(p + 0x18)); }

void fn_8058FABC() {}

void fn_8058F940() {}

void fn_8058F908(u8* p) {
    fn_8028C380(*(u8**)(p + 0x18));
    fn_805956D4(*(u8**)(p + 0x1c));
}

}  // extern "C"
