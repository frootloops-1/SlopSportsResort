// RPBow_804F8CD8: Resort Bowling unit (Resort-only layout UI, no ogws twin).
// First pass: only the small accessor/stub functions are written; fn_ names are Resort
// addresses, struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
extern "C" {

void fn_80371554(void*);
void fn_804F8CD8(void*);

void fn_804F8D8C(void* p) { fn_804F8CD8(p); }

void fn_804F8F18(u8* p, u32 x) {
    *(u32*)(p + 0x16c) = x;
    fn_80371554(p);
}

void fn_804F8FD0() {}

}  // extern "C"
