// Canoeing (Resort-only), .text 0x804A3BC0-0x804A3DD8: field object base class (vtable 0x806DBFA0). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Vec3Copy { u32 x, y, z; }; // 12-byte block, copied word by word
Vec3Copy fn_804A3DB8(const u8* p) { return **(Vec3Copy**)(p + 0x40); }

}  // extern "C"
