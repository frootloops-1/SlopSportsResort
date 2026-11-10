// RPBow_804F9054: Resort Bowling unit (Resort-only layout UI, no ogws twin).
// First pass: only the small accessor/stub functions are written; fn_ names are Resort
// addresses, struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
extern "C" {

void fn_80371554(void*);
void fn_804F9054(void*);

void fn_804F9108(void* p) { fn_804F9054(p); }

void fn_804F9294(u8* p, u32 x) {
    *(u32*)(p + 0x43c) = x;
    fn_80371554(p);
}

void fn_804F934C() {}

}  // extern "C"
