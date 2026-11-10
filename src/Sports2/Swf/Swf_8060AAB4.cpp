// Swf_8060AAB4: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_8060C2E8(u8*);
extern u8 lbl_806EC040[];
extern void* lbl_806EC018[];

u8* fn_8060B15C() { return lbl_806EC040; }

void* fn_8060B11C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8060B0E0(u8* p) {
    fn_8060C2E8(p);
    *(void***)(p + 0x0) = lbl_806EC018;
    return p;
}


// ---- hand-written (first pass) ----
struct Unk_Vec3f { f32 x, y, z; };
extern Unk_Vec3f lbl_807D0318;

void fn_8060B0B4(u8* p) {
    *(s32*)(p + 0x50) = 0;
    Unk_Vec3f* v = (Unk_Vec3f*)(p + 0x54);
    v->x = lbl_807D0318.x;
    v->y = lbl_807D0318.y;
    v->z = lbl_807D0318.z;
}

}  // extern "C"
