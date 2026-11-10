// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVec3f { f32 x, y, z; };
struct UnkMtx34 { u32 w[12]; };
struct UnkVObjAt0C { u8 _00[0xC]; virtual void vf08(); virtual void vf0C(void* a); };
void fn_80500444(void* p, void* a);
void fn_805008A0(void* p);
const char* fn_80500C38() {
    static char sName[] = "Ball";
    return sName;
}

// Deleting destructor of a class without a base destructor.
void* fn_80500BF8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

UnkVec3f fn_80500B50(const f32* m) {
    UnkVec3f v;
    v.x = m[4];
    v.y = m[8];
    v.z = m[12];
    return v;
}

void fn_80500B2C(u8* p, const UnkMtx34* src) { *(UnkMtx34*)(p + 4) = *src; }

void fn_80500AC4(f32* m, const UnkVec3f* v) {
    UnkVec3f t = *v;
    m[4] = t.x;
    m[8] = t.y;
    m[12] = t.z;
}

// Deleting destructor of a class without a base destructor.
void* fn_80500210(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804FFE48(u8* p) { *(u32*)(p + 0x44) &= ~0x30; }

void fn_804FFE28(u8* p) {
    u32 flags = *(u32*)(p + 0x44);
    if ((flags & 1) && !(flags & 4)) {
        fn_805008A0(*(void**)(p + 0xC));
    }
}

void fn_804FFBE8() {}

void fn_804FFBB8(u8* p, void* a) {
    UnkVObjAt0C* o = *(UnkVObjAt0C**)(p + 0x38);
    if (o != NULL && (*(u32*)(p + 0x44) & 1)) {
        o->vf0C(a);
    }
}

void fn_804FFBB0(u8* p, u32 v) { *(u32*)(p + 0x34) = v; }

void fn_804FFB88(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x1;
    } else {
        *(u32*)(p + 0x44) &= ~0x1;
    }
}

void fn_804FFB60(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x8;
    } else {
        *(u32*)(p + 0x44) &= ~0x8;
    }
}

void fn_804FFB34(u8* p, BOOL b, u32 x) {
    if (b) {
        *(u32*)(p + 0x58) = x;
        *(u32*)(p + 0x44) |= 4;
    } else {
        *(u32*)(p + 0x44) &= ~4;
    }
}

void fn_804FFB0C(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x2;
    } else {
        *(u32*)(p + 0x44) &= ~0x2;
    }
}

void fn_804FFAE4(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x40;
    } else {
        *(u32*)(p + 0x44) &= ~0x40;
    }
}

void fn_804FFAD4(u8* p) { *(u32*)(p + 0x44) &= ~0x180; }

void fn_804FFAAC(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x100;
    } else {
        *(u32*)(p + 0x44) &= ~0x100;
    }
}

void fn_804FFA84(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x44) |= 0x80;
    } else {
        *(u32*)(p + 0x44) &= ~0x80;
    }
}

void fn_804FFA64(UnkVec3f* out, u8* p) {
    const f32* m = *(f32**)(p + 0xC);
    out->x = m[4];
    out->y = m[8];
    out->z = m[12];
}

void fn_804FFA44(u8* p, u32 x) {
    *(u32*)(p + 0x40) = x;
    ((u32*)*(u8**)(*(u8**)(*(u8**)(p + 0x34) + 0x38) + 0x18))[*(s32*)(p + 0x3C) * 2] = x;
}

f32 fn_804FFA30(u8* p) { return *(f32*)(p + 0x48) * *(f32*)(p + 0x4C) - 0.01f; }

void fn_804FF590(u8* p, u8* a) {
    if (*(s32*)(a + 0x24) == 1) {
        *(u32*)(p + 0x44) |= 0x10;
    } else if (*(s32*)(a + 0x24) == 5) {
        *(u32*)(p + 0x44) |= 0x20;
    }
    fn_80500444(*(void**)(p + 0xC), a);
}

void fn_804FF57C(u8* p, u8* a) {
    *(u32*)(p + 0x50) = *(u32*)(a + 0x24);
    *(f32*)(p + 0x54) = *(f32*)(a + 0x3C);
}

} // extern "C"
