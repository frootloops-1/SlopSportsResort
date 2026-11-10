// RPBow_804F7864: Resort Bowling unit (Resort-only layout UI, no ogws twin).
// First pass: only the small accessor/stub functions are written; fn_ names are Resort
// addresses, struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
extern "C" {

void fn_804F7864() {}

void fn_804F7868() {}

void fn_804F7C18(u8* p, int i, u32 a, u32 b) {
    ((u32*)(p + 0x98))[i] = a;
    ((u32*)(p + 0xa8))[i] = b;
}

void fn_804F7DE0(u8* p, u8* q) {
    *(u8**)(p + 0xb8) = q;
    *(u32*)(p + 0x94) = *(u32*)(q + 0x8);
}

void* fn_804F8190(u8* p) { return p + 0x64; }

void* fn_804F8198(u8* p) { return p + 0x64; }

}  // extern "C"
