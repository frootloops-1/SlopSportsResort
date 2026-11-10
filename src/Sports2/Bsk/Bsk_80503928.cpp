// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVObjAt38 { u8 _00[0x38]; virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C(); virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C(); virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C(); virtual void vf50(BOOL b); };
extern u8 lbl_806F5A24;
BOOL fn_80533A4C(void* p);
void fn_80533A68(void* p);
void fn_80533A70(void* p);
void fn_802B5B04(void* p);
void fn_80503928(void* p); // defined in asm (not written)
void fn_805043A4(u8* p);
void fn_80503A20(u8* p, u32 x);
extern void* lbl_806F5A20;
void fn_802B5C0C();
void fn_80501E20();
void fn_80501EB8();

void fn_80504C98() {}

void fn_80504C84(u8* p) {
    *(f32*)(p + 0x0) = 0.0f;
    *(f32*)(p + 0x4) = 0.0f;
    *(f32*)(p + 0x8) = 0.0f;
}

int fn_80504C7C() { return 0; }

int fn_80504C74() { return 0; }

void fn_80504C70() {}

void fn_80504C6C() {}

void fn_80504C68() {}

void* fn_80504C60() { return lbl_806F5A20; }

void fn_805046CC() {}

void fn_805046C8() {}

void fn_805046C0(u8* p) { ((void (*)(void*))fn_802B5C0C)(*(void**)(p + 0x104)); }

void* fn_8050456C(u8* p) { return *(void**)(p + 0x88); }

void* fn_80504564(u8* p) { return *(void**)(p + 0x8c); }

void fn_8050455C(u8* p) { ((void (*)(void*))fn_80501EB8)(*(void**)(p + 0x3c)); }

void* fn_80504550(u8* p) { return *(void**)(*(u8**)(p + 0xfc) + 0x94); }

void fn_805043F8(u8* p, void*, u32 x) {
    for (int i = 0; i < 4; i++) {
        fn_80503A20(*(u8**)(p + 0x12C + i * 4), x);
    }
    fn_802B5B04(*(void**)(p + 0x104));
}

void fn_805043E4(u8* p, BOOL b) {
    if (b) {
        fn_805043A4(p);
        return;
    }
    fn_80533A70(*(void**)(p + 0x100));
}

void fn_805043A4(u8* p) {
    if (!fn_80533A4C(*(void**)(p + 0x100))) {
        fn_80533A68(*(void**)(p + 0x100));
    }
}

void fn_80503D1C(u8* p) {
    for (int i = 0; i < 4; i++) {
        fn_80503928(*(void**)(p + 0x12C + i * 4));
    }
}

void fn_80503B6C(u8* p) { ((void (*)(void*))fn_80501E20)(*(void**)(p + 0x3c)); }

void fn_80503B30(u8* p) {
    for (int i = 0; i < 2; i++) {
        if (((s32*)(p + 0x11C))[i] != 0) {
            ((s32*)(p + 0x124))[i] += ((s32*)(p + 0x11C))[i];
        }
        ((s32*)(p + 0x11C))[i] = 0;
    }
}

BOOL fn_80503AF8(u8* p) {
    for (int i = 0; i < 4; i++) {
        if ((*(u8**)(p + 0x12C + i * 4))[0x14]) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL fn_80503AE8() { return lbl_806F5A24 != 0; }

void fn_80503AB4(UnkVObjAt38* p) {
    if (lbl_806F5A24) {
        p->vf50(TRUE);
    } else {
        p->vf50(FALSE);
    }
}

void fn_80503A9C(u32* p) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
}

void fn_80503A7C(u8* p) {
    *(u32*)(p + 0x0) = 0;
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0xC) = 0;
    *(u32*)(p + 0x10) = 0;
    p[0x14] = 0;
}

BOOL fn_80503A6C(u8* p) { return *(u32*)(p + 0xc) == 0; }

void fn_80503A44(u8* p, u8* a) {
    *(u8**)(p + 0x0) = a;
    *(u32*)(p + 0x4) = *(u32*)(*(u8**)(a + 0x160) + 0x25C);
    *(u32*)(p + 0xC) = 1;
    *(u32*)(p + 0x10) = 0;
    p[0x14] = 0;
}

void fn_80503A20(u8* p, u32 x) {
    if (*(u32*)(p + 4) == x && *(s32*)(p + 0xC) == 1) {
        *(s32*)(p + 0xC) = 2;
    }
}

} // extern "C"
