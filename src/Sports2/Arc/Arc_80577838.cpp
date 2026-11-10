// Arc_80577838: Resort Archery unit 0x80577838-0x80578790 (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

void fn_805780E4(u8* p) { *(u8*)(p + 0x11a) = 0x1; }

}  // extern "C"
