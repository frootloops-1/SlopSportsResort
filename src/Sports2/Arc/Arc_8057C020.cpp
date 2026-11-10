// Arc_8057C020: Resort Archery unit 0x8057C020-0x8057C4CC (Resort-only, no Wii Sports twin).
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

extern "C" {

void fn_8057C2D8(u8* p) { *(u8*)(p + 0x111) = 0x1; }

}  // extern "C"
