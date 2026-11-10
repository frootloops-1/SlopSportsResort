// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void* fn_80356294(void* p, int n);
void* fn_80516AEC(void* p, f32 f);
extern void* lbl_806E0898[];
extern u8 lbl_806F5A38;
struct UnkVec3f { f32 x, y, z; };
f32 fn_80356A90(f32* a, f32* b, f32 f);
f32 lbl_806F2620 = 0.1f;
void* fn_8050A6E0(u8* p) {
    *(void**)p = lbl_806E0898;
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0x6C) = 0;
    *(f32*)(p + 0x74) = 0.3f;
    *(f32*)(p + 0x78) = 0.01f;
    *(f32*)(p + 0x7C) = 0.004f;
    *(f32*)(p + 0x114) = 0.015f;
    *(f32*)(p + 0x118) = 0.045f;
    *(f32*)(p + 0x11C) = 0.85f;
    void* o = operator new(0xC);
    if (o != NULL) {
        o = fn_80356294(o, 4);
    }
    *(void**)(p + 0x8) = o;
    o = operator new(0x1C);
    if (o != NULL) {
        o = fn_80516AEC(o, 0.0f);
    }
    *(void**)(p + 0x120) = o;
    lbl_806F5A38 = 0;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8050A6A0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8050A698(u8* p, u32 v) { *(u32*)(p + 0x4) = v; }

void fn_8050A694() {}

void fn_8050A690() {}

void fn_8050A438(u8* p) {
    *(f32*)(p + 0x84) = fn_80356A90((f32*)(p + 0x84), (f32*)(p + 0x88), 0.1f);
    *(f32*)(p + 0x88) = 0.0f;
}

void fn_8050A3A4(u8* p) {
    *(f32*)(p + 0x78) = 0.01f;
    *(f32*)(p + 0x7C) = 0.004f;
    *(f32*)(p + 0x74) = 0.3f;
    *(f32*)(p + 0xF4) = 0.02f;
}

int fn_8050A294(u8* p) {
    if (__fabs(*(f32*)(p + 0x84)) < lbl_806F2620) {
        return 1;
    }
    return 3;
}

void fn_8050A0D8(u8* p, const UnkVec3f* v) {
    *(UnkVec3f*)(p + 0x9C) = *v;
    *(u32*)(p + 0xB4) = 0;
}

void fn_8050A07C(u8* p, const UnkVec3f* v, u32 x) {
    *(UnkVec3f*)(p + 0xB8 + *(s32*)(p + 0xB4) * 0xC) = *(UnkVec3f*)(p + 0x9C);
    *(u32*)(p + 0xDC + *(s32*)(p + 0xB4) * 4) = x;
    *(UnkVec3f*)(p + 0x9C) = *v;
    (*(s32*)(p + 0xB4))++;
}

void fn_8050A02C(u8* p, const UnkVec3f* v) {
    *(u32*)(p + 0x6C) |= 0x400;
    *(UnkVec3f*)(p + 0xE8) = *v;
}

void fn_80509F38(u8* p) { *(f32*)(*(u8**)(p + 0x120) + 0xC) = 0.0f; }

void fn_80509F10(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x6c) |= 0x10;
    } else {
        *(u32*)(p + 0x6c) &= ~0x10;
    }
}

void fn_80509EE8(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x6c) |= 0x20;
    } else {
        *(u32*)(p + 0x6c) &= ~0x20;
    }
}

void fn_80509ED4(u8* p, u32 x) {
    *(u32*)(p + 0x90) = x;
    *(u32*)(p + 0x6C) |= 0x200;
}

void fn_80509EAC(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x6c) |= 0x8;
    } else {
        *(u32*)(p + 0x6c) &= ~0x8;
    }
}

void fn_80509E84(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x6c) |= 0x40;
    } else {
        *(u32*)(p + 0x6c) &= ~0x40;
    }
}

void fn_80509E70(u8* p, f32 f) {
    *(f32*)(p + 0x98) = f;
    *(u32*)(p + 0x6C) |= 0x80;
}

BOOL fn_80509D94(u8* p, f32 f1, f32 f2, f32 f3) {
    if (*(f32*)(p + 0x110) > f1) {
        *(f32*)(p + 0x100) = f2;
        *(f32*)(p + 0x104) = *(f32*)(p + 0x11C);
        *(f32*)(p + 0x108) = f3;
        *(f32*)(p + 0x10C) = 8.0f;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80509D4C(u8* p, f32 f) {
    if (0.0f == *(f32*)(p + 0x10) && 0.0f == *(f32*)(p + 0x28) && *(f32*)(p + 0x110) >= f &&
        *(f32*)(p + 0x10C) < 0.0f) {
        return TRUE;
    }
    return FALSE;
}

u32 fn_80509D40(u8* p) { return *(u32*)(p + 0x6c) & 1; }

BOOL fn_80509D10(u8* p, f32 f) {
    u32 flags = *(u32*)(p + 0x6C);
    if (!(flags & 0x80) && !(flags & 1) && *(f32*)(p + 0x94) > f) {
        return TRUE;
    }
    return FALSE;
}

u32 fn_80509D04(u8* p) { return (*(u32*)(p + 0x6c) >> 8) & 1; }

u32 fn_80509CF8(u8* p) { return (*(u32*)(p + 0x6c) >> 11) & 1; }

} // extern "C"
