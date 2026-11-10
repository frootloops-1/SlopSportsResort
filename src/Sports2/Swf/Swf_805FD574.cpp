// Swf_805FD574: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void __ct__Q34nw4r4math4VEC3Fv(u8*);
void fn_8032349C(u8*);
extern f32 lbl_806F37E0;
extern u8 lbl_806EBC88[];
extern void* lbl_806EBC28[];

s32 fn_805FF238() { return 0x0; }

u8* fn_805FF210() { return lbl_806EBC88; }

void* fn_805FF1D0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_805FF170(u8* p) {
    fn_8032349C(p);
    *(void***)(p + 0x0) = lbl_806EBC28;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x30);
    *(s32*)(p + 0xa0) = 0x0;
    *(s32*)(p + 0x8) = 0x0;
    return p;
}

void fn_805FF16C() {}

void fn_805FF028() {}

void fn_805FEF94() {}

void fn_805FEF10() {}

f32 fn_805FEC9C() { return lbl_806F37E0; }

s32 fn_805FE878() { return 0x0; }

s32 fn_805FDA10() { return 0x0; }

void fn_805FD880() {}


// ---- hand-written (first pass) ----
struct Unk_Vec3f { f32 x, y, z; };

void fn_805FF21C(u8*, Unk_Vec3f* d, Unk_Vec3f* s) {
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
}

int fn_805FDD38(u8*, Unk_Vec3f* d, u8*, Unk_Vec3f* s) {
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
    return 0;
}

}  // extern "C"
