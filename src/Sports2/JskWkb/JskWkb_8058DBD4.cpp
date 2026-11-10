// Resort shared Power Cruising/Wakeboarding engine file 0x8058DBD4-0x8058F908: collision object, vtable 0x806E5940 (jsk_col_* and wkb_col_* names).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8058C140(u8*);
void fn_805A7B54(u8*);
void fn_805A7C5C(u8*);

void fn_8058F270() {}

void fn_8058E3E0() {}

void fn_8058E2B0() {}

void fn_8058E224() {}

void fn_8058DE68(u8* p) { *(u8*)(p + 0x2d) = 1; }

void fn_8058DE14(u8* p) {
    u8* q = *(u8**)(p + 0x20);
    if (q != NULL) {
        fn_805A7B54(q);
    }
}

void fn_8058DE08(u8* p) { *(u8*)(p + 0x2d) = 4; }

void fn_8058DDF4(u8* p) {
    u8* q = *(u8**)(p + 0x20);
    if (q != NULL) {
        fn_805A7C5C(q);
    }
}

void fn_8058DCDC(u8* p) {
    u8* q = *(u8**)(p + 0x1c);
    if (q != NULL) {
        fn_8058C140(q);
    }
}

}  // extern "C"
