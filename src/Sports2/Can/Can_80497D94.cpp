// Canoeing (Resort-only), .text 0x80497D94-0x80498BEC. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

extern u8* lbl_806F5838; // Config instance
void fn_804988AC(u8* p, s32 i);
struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14(u32);
    virtual void vf18(s32);
    virtual void vf1C();
};

void fn_8048B270(u8*);
void fn_8048B3B4(u8*);
void fn_8048B460(u8*);
void fn_8048B590(u8*);
void fn_804976AC(u8*);
void fn_804976C0(u8*);
void fn_80497828(u8*, u32, u32, u32);
void fn_80498538(u8*);
void fn_804985A4(u8*);

// Deleting destructor of a class without a base destructor.
void* fn_80498B78(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80498980(u8* p) { fn_804988AC(p, *(s32*)(lbl_806F5838 + 0x40) % 3); }

BOOL fn_804987B8(s32* p, s32 v) {
    if (*p < v) {
        *p = v;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80498798(s32* p, s32 v) {
    if (*p > v) {
        *p = v;
        return TRUE;
    }
    return FALSE;
}

void fn_80498630(u8* p, u32 a1, u32 a2) {
    fn_8048B590(*(u8**)(p + 0x10));
    fn_80497828(*(u8**)(p + 0x1c), a1, *(u32*)(*(u8**)(*(u8**)(p + 0x30) + 0x10) + 0x8), *(u32*)(p + 0xc));
    ((Unk_VtAt0*)(*(u8**)(p + 0x20)))->vf14(a2);
}

void fn_804985C8(u8* p) {
    fn_8048B3B4(*(u8**)(p + 0x10));
    ((Unk_VtAt0*)(*(u8**)(p + 0x20)))->vf18(0);
    *(u8*)(p + 0x2c) = 0;
    fn_804976C0(*(u8**)(p + 0x1c));
    fn_804985A4(p);
    fn_80498538(p);
}

void fn_804985A4(u8* p) {
    p[0x34] = 0;
    *(s32*)(p + 0x38) = 4;
    *(f32*)(p + 0x3c) = 0.0f;
    *(f32*)(p + 0x40) = 0.0f;
    *(f32*)(p + 0x44) = 0.0f;
}

void fn_8049855C(u8* p) {
    fn_8048B460(*(u8**)(p + 0x10));
    fn_804985A4(p);
    fn_804976AC(*(u8**)(p + 0x1c));
    fn_80498538(p);
}

void fn_80498538(u8* p) {
    for (s32 i = 0; i < 6; i++) {
        ((f32*)(p + 0x48))[i] = 0.0f;
    }
}

void fn_80498524(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x20)))->vf1C(); }

void fn_804982D4(u8* p) { fn_8048B270(*(u8**)(p + 0x10)); }

u32 fn_80498130(u8* p) { return *(u32*)(*(u8**)(p + 0x10) + 0xc); }

u32 fn_80498124(u8* p) { return *(u32*)(*(u8**)(p + 0x10) + 0x10); }

void fn_80497ECC(u8* p, f32 v, BOOL second) {
    if (v >= 0.2f) {
        if (second) {
            *(f32*)(p + 0x48) += 1.0f;
        } else {
            *(f32*)(p + 0x4c) += 1.0f;
        }
    }
}

void fn_80497EBC(u8* p) {
    *(f32*)(p + 0x60) = 0.0f;
    *(f32*)(p + 0x64) = 0.0f;
}

}  // extern "C"
