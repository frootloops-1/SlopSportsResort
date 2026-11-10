// Canoeing (Resort-only), .text 0x80494264-0x80494884: camera base class (vtable 0x806DBDA0). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/gfxe/eggScreen.h>
#include <revolution/MTX.h>

extern "C" {

void fn_80359828(u8*, u8*);
void fn_804944D0(u8*);

void fn_80494880() {}

// Deleting destructor of a class without a base destructor.
void* fn_80494840(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804944CC(u8* p) { fn_804944D0(p); }

u32 fn_8049447C(u8* p, u8* a1) {
    fn_80359828(p + 0xc, a1 + 0xc);
    *(u32*)(p + 0x34) = *(u32*)(a1 + 0x34);
    *(u32*)(p + 0x30) = *(u32*)(a1 + 0x30);
    *(u32*)(p + 0x38) = *(u32*)(a1 + 0x38);
    return *(u32*)(a1 + 0x30);
}

f32 fn_8049427C(const u8* p, const Vec* v) {
    return *(f32*)(p + 0x44) * PSVECSquareDistance(*(Vec**)(p + 0x4c), v);
}

// Widens a 4:3 value for the standard TV mode.
f32 fn_80494264(f32 x) {
    if (EGG::Screen::GetTVMode() == EGG::Screen::TV_MODE_STD) {
        x *= 1.3443708f;
    }
    return x;
}

}  // extern "C"
