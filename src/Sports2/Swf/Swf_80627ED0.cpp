// Swf_80627ED0: Resort Swordplay unit 0x80627ED0-0x80629B98 (Resort-only, no Wii Sports twin).
// "モーション" (motion) owner: vtable 0x806ED980, name 0x806ED994.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

extern "C" {

BOOL fn_80626440(void*);
BOOL fn_8062644C(void*);
void fn_8032349C(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);
void* fn_8062784C(void*, void*);
extern f32 lbl_806F5108[2];
extern u8 lbl_806ED980[];
extern char lbl_806ED994[];

char* fn_80629AEC() { return lbl_806ED994; }

void* fn_80629AAC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80629A1C(u8* p, void* a) {
    fn_8032349C(p);
    *(u8**)p = lbl_806ED980;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x1c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x28);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x34);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x4c);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x58);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x64);
    PTR(p, 0x8) = a;
    void* q = operator new(0x1e8);
    if (q != NULL) {
        q = fn_8062784C(q, a);
    }
    PTR(p, 0xc) = q;
    return p;
}

void fn_80629738(u8* p) { S32(p, 0x228) = S32(p, 0x228) + 1; }

void fn_80628C90(u8* p) {
    F32(p, 0x210) = lbl_806F5108[0];
    F32(p, 0x214) = lbl_806F5108[1];
    F32(p, 0x218) = lbl_806F5108[0];
    F32(p, 0x21c) = lbl_806F5108[1];
}

f32 fn_80628778(u8* p, f32 a, f32 b, f32 c, f32 d) {
    if (S32(p, 0x228) >= 2) {
        return b;
    }
    f32 t = c * (b - a);
    if (t > d) {
        t = d;
    } else if (t < -d) {
        t = -d;
    }
    return a + t;
}

BOOL fn_80627EFC(u8* p) {
    if (S32(p, 0x228) > 0) {
        return FALSE;
    }
    return fn_8062644C(PTR(p, 0xc));
}

BOOL fn_80627EDC(u8* p) {
    if (S32(p, 0x228) > 0) {
        return FALSE;
    }
    return fn_80626440(PTR(p, 0xc));
}

void fn_80627ED0(u8* p) { S32(p, 0x228) = 2; }

}  // extern "C"
