// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

extern void* lbl_806E0A78[];
void* fn_8050D120(u8* p, u8 b);
int fn_8053D054(void* p);
BOOL fn_8050BB68(void* p);
extern void* lbl_806E0A88[];
struct UnkMtx34 { u32 w[12]; };
struct UnkVec3f { f32 x, y, z; };
BOOL fn_8053D07C(void* p, int id, f32 a, f32 b, int c, int d);
// Deleting destructor of a class without a base destructor.
void* fn_80510BF0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80510BE8(u8* p, u32 v) { *(u32*)(p + 0xb4) = v; }

void* fn_8050FF80(u8* p) { return *(void**)(p + 0x64); }

void fn_8050F640(u8* p, u8 v) { (*(u8**)(p + 0xbc))[0xd8] = v; }

void fn_8050F614(u8* p, const UnkVec3f* v) {
    (*(u8**)(p + 0xC0))[0xDA] = 1;
    *(UnkVec3f*)(*(u8**)(p + 0xC0) + 0xC0) = *v;
}

void fn_8050F5E8(u8* p, const UnkVec3f* v) {
    (*(u8**)(p + 0xC4))[0xDA] = 1;
    *(UnkVec3f*)(*(u8**)(p + 0xC4) + 0xC0) = *v;
}

void fn_8050F4CC(u8* p, const UnkMtx34* m) {
    *(UnkMtx34*)(*(u8**)(p + 0xC0) + 0x30) = *m;
    *(UnkMtx34*)(*(u8**)(p + 0xC4) + 0x30) = *m;
}

void fn_8050F4B8(u8* p, u8 b) {
    (*(u8**)(p + 0xC0))[0xD8] = b;
    (*(u8**)(p + 0xC4))[0xD8] = b;
}

u8 fn_8050F300(u8* p) {
    int i;
    if (fn_8050BB68(*(void**)(*(u8**)(p + 0xB4) + 0x158))) {
        i = 3;
    } else {
        i = 4;
    }
    return (*(u8**)(p + 0xBC + i * 4))[0xD8];
}

u8* fn_8050F258(u8* p) {
    int i;
    if (fn_8050BB68(*(void**)(*(u8**)(p + 0xB4) + 0x158))) {
        i = 3;
    } else {
        i = 4;
    }
    return *(u8**)(p + 0xBC + i * 4) + 0x90;
}

void fn_8050F24C(u8* p, f32 v) { *(f32*)(*(u8**)(p + 0xbc) + 0xd4) = v; }

void fn_8050F238(u8* p, f32 f) {
    *(f32*)(*(u8**)(p + 0xC8) + 0xD4) = f;
    *(f32*)(*(u8**)(p + 0xCC) + 0xD4) = f;
}

void fn_8050F214(u8* p, u8 a, u8 b) {
    (*(u8**)(p + 0xD0))[0xD8] = a;
    (*(u8**)(p + 0xD4))[0xD8] = a;
    (*(u8**)(p + 0xD0))[0xD9] = b;
    (*(u8**)(p + 0xD4))[0xD9] = b;
}

void fn_8050F038(u8* p, u8 b, f32 f) {
    p[0xE9] = b;
    *(f32*)(p + 0xEC) = f;
}

BOOL fn_8050EFA8(u8* p) { return fn_8053D054(*(void**)(p + 0xD8)) == 0x26; }

BOOL fn_8050EEFC(u8* p) {
    u32 id = fn_8053D054(*(void**)(p + 0xD8)) - 0x28;
    BOOL ret = FALSE;
    if (id <= 3) {
        ret = TRUE;
    }
    return ret;
}

int fn_8050EEA0(u8* p, f32 f) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 11, f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050ED70(u8* p, f32 f) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 0, f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050ECB0(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 8, 20.0f, 0.0f, 0, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050EBA8(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 34, 10.0f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050EB48(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 39, 10.0f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050E9B0(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 35, 5.0f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050E848(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 33, 5.0f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

int fn_8050E150(u8* p) {
    *(s32*)(p + 0xDC) = -1;
    if (fn_8053D07C(*(void**)(p + 0xD8), 42, 3.0f, 0.0f, 1, 0)) {
        *(f32*)(p + 0xac) = 1.0f;
    }
    return 1;
}

void fn_8050D2FC(u8* p, u32 a, f32 f1, f32 f2, u8 b) {
    *(u32*)(p + 0xDC) = a;
    *(f32*)(p + 0xE0) = f1;
    *(f32*)(p + 0xE4) = f2;
    p[0xE8] = b;
}

// Deleting destructor of a class without a base destructor.
void* fn_8050D1D4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8050D120(u8* p, u8 b) {
    *(void**)p = lbl_806E0A88;
    p[0x90] = b;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_8050D0E0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8050C4BC() {}

} // extern "C"
