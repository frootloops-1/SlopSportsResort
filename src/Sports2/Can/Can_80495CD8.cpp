// Canoeing (Resort-only), .text 0x80495CD8-0x80496010. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8028FD8C(u8*);

void fn_8049600C(u8* p) { fn_8028FD8C(p); }

}  // extern "C"
