// RPBow_804F9944: Resort Bowling unit (Resort-only layout UI, no ogws twin).
// First pass: only the small accessor/stub functions are written; fn_ names are Resort
// addresses, struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
extern "C" {

void fn_802B73BC(int);

void fn_804F9944() { fn_802B73BC(0x44f); }

void fn_804F9A98() {}

}  // extern "C"
