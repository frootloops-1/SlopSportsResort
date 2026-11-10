// Canoeing (Resort-only), .text 0x8049A1BC-0x8049B30C. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <revolution/MTX.h>

extern "C" {

struct Vec3f { f32 x, y, z; };
struct Vec3w { u32 x, y, z; };
void fn_8049AEBC(u8*);

void fn_8049B29C() {}

void fn_8049B1B0(u8* p) { fn_8049AEBC(p); }

void fn_8049AC20(u8* p) { *(u32*)(p + 0x1c) = *(u32*)(p + 0x14); }

// Pops the next queued point: copies its position and value, advances the cursor.
BOOL fn_8049ABCC(u8* p, Vec3f* pos, f32* val) {
    while (*(u8**)(p + 0x1c) != p + 0x14) {
        u8* e = *(u8**)(p + 0x1c);
        *pos = *(Vec3f*)(e - 0x10);
        *val = *(f32*)(*(u8**)(p + 0x1c) - 0x4);
        *(u32*)(p + 0x1c) = **(u32**)(p + 0x1c);
        return TRUE;
    }
    return FALSE;
}

void fn_8049ABA4(u8* p, const Vec3f* v, f32 f) {
    *(u32*)(p + 0x20) = *(u32*)(p + 0x14);
    *(Vec3f*)(p + 0x24) = *v;
    *(f32*)(p + 0x30) = f;
}

void fn_8049A9C8(u8* p, const Vec3f* v, f32 f) {
    *(u32*)(p + 0x34) = *(u32*)(p + 0x14);
    *(Vec3f*)(p + 0x38) = *v;
    *(f32*)(p + 0x44) = f;
}

void fn_8049A7A0(u8* p, const Vec3f* v, f32 f) {
    *(u32*)(p + 0x48) = *(u32*)(p + 0x14);
    *(Vec3f*)(p + 0x4c) = *v;
    *(f32*)(p + 0x58) = f;
}

}  // extern "C"
