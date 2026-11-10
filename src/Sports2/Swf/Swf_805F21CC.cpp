// Swf_805F21CC: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
};

extern "C" {


void fn_8032349C(u8*);
void fn_805F5960(u8*);
void fn_805F598C(u8*);
void fn_805F59F0(u8*);
void fn_805F6D08(u8*);
void fn_805F76DC(u8*);
void fn_806022C8(u8*);
extern u8 lbl_806EB9B4[];
extern void* lbl_806EB990[];

u8* fn_805F53E4() { return lbl_806EB9B4; }

void* fn_805F53A4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805F4AF4() { return 0x0; }

void fn_805F4944() {}

u8* fn_805F39B8(u8* p) { return *(u8**)(p + 0x64) + 0x1a4; }

u8* fn_805F39AC(u8* p) { return *(u8**)(p + 0x64) + 0x1b0; }

void fn_805F3980(u8* p) { fn_806022C8(*(u8**)(p + 0x74)); }

s32 fn_805F3974(u8* p) { return *(s32*)(*(u8**)(p + 0x70) + 0x94); }

void fn_805F396C(u8* p) { fn_805F76DC(*(u8**)(p + 0x64)); }

void fn_805F3904(u8* p) { fn_805F6D08(*(u8**)(p + 0x64)); }

s32 fn_805F38CC(u8* p) { return *(s32*)(*(u8**)(p + 0x68) + 0xc); }

void fn_805F38A0(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x70)))->vf40(); }

void fn_805F388C(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x70)))->vf44(); }

s32 fn_805F3868() { return 0x0; }

s32 fn_805F37AC(u8* p) { return *(s32*)(*(u8**)(p + 0x80) + 0x10); }

s32 fn_805F37A0(u8* p) { return *(s32*)(*(u8**)(p + 0x64) + 0x14); }

s32 fn_805F3794(u8* p) { return *(s32*)(*(u8**)(p + 0x64) + 0x18); }

s32 fn_805F3668() { return 0x0; }

void fn_805F3654(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x70)))->vf38(); }

u8* fn_805F3400(u8* p) { return *(u8**)(p + 0x70) + 0x88; }

f32 fn_805F33F8() { return 1.0f; }

f32 fn_805F33F0() { return 1.0f; }

void fn_805F3370() {}

void fn_805F3304(u8* p) { fn_805F598C(*(u8**)(p + 0x64)); }

void fn_805F3300() {}

void fn_805F32FC() {}

void fn_805F3254() {}

void fn_805F3250() {}

void fn_805F324C() {}

void fn_805F3248() {}

s32 fn_805F2AFC() { return 0x0; }

s32 fn_805F2AF4() { return 0x0; }

void fn_805F2A28(u8* p) { fn_805F59F0(*(u8**)(p + 0x64)); }

void fn_805F2A24() {}

void fn_805F299C(u8* p) { fn_805F5960(*(u8**)(p + 0x64)); }

void fn_805F28CC(u8* p, s32 v) { *(s32*)(*(u8**)(p + 0x64) + 0xc4) = v; }

s32 fn_805F28C0(u8* p) { return *(s32*)(*(u8**)(p + 0x64) + 0xc4); }

void fn_805F28B4(u8* p, s32 v) { *(s32*)(*(u8**)(p + 0x7c) + 0x220) = v; }

void fn_805F26A8() {}


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;
extern f32 lbl_806F3748;
void fn_805FF240(u8*);
void fn_80627ED0(u8*);
void fn_805F58B4(u8*);
struct Unk_Sel;
void fn_805F5304(Unk_Sel*, u8*);
void fn_805F3A2C(u8*);
void fn_805F6CF4(u8*, s32);
void fn_805F9418(u8*, f32, f32, f32);
void fn_805FEE88(u8*, u8*);
void fn_805F9798(u8*, s32);
void fn_805F5944(u8*);
void fn_805F5A60(u8*);
void fn_805F5ABC(u8*);
void fn_80649804(u8*);
void fn_805F22D0(u8*);
void fn_805F3504(u8*);
f32 fn_80328080(f32);

int fn_805F37B8(u8* p) {
    if (*(s32*)(*(u8**)(lbl_806F5FF0 + 0x190) + 0x8) == 2) {
        return *(s32*)(*(u8**)(p + 0x80) + 0x10);
    }
    return *(f32*)(*(u8**)(p + 0x80) + 0x360) >= lbl_806F3748;
}

f32 fn_805F3688(u8* p) {
    f32 v = *(f32*)(p + 0x38) + *(f32*)(*(u8**)(p + 0x64) + 0xd0);
    if (v > 1.0f) {
        v = 1.0f;
    }
    return v;
}

f32 fn_805F3670(u8* p) {
    u8* q = *(u8**)(p + 0x70);
    return fn_80328080(*(f32*)(q + 0x3c) * *(f32*)(q + 0x3c) + *(f32*)(q + 0x44) * *(f32*)(q + 0x44));
}

u8* fn_805F3618(u8* p) {
    if (*(s32*)(p + 0xc8) == 0) {
        fn_805F3504(p);
    }
    return p + 0x8c;
}

u8* fn_805F35DC(u8* p) {
    if (*(s32*)(p + 0xc8) == 0) {
        fn_805F3504(p);
    }
    return p + 0x98;
}

void fn_805F29E4(u8* p) {
    fn_805F5ABC(*(u8**)(p + 0x64));
    fn_80649804(*(u8**)(p + 0x80));
    fn_805F22D0(p);
}

void fn_805F29A4(u8* p) {
    fn_805F5A60(*(u8**)(p + 0x64));
    fn_80649804(*(u8**)(p + 0x80));
    fn_805F22D0(p);
}

void fn_805F2980(u8* p) {
    if (*(s32*)(*(u8**)(p + 0x80) + 0x10) == 0) {
        fn_805F5944(*(u8**)(p + 0x64));
    }
}

void fn_805F295C(u8* p) {
    *(s32*)(p + 0x18) = 1;
    *(u32*)(p + 0x1c) |= 8;
    u8* q = *(u8**)(p + 0x64);
    fn_805F9798(q, *(s32*)(q + 0xe4));
}

void fn_805F2944(u8* p, s32 b) {
    if (b == 0) {
        *(s32*)(*(u8**)(p + 0x68) + 0x14) = 1;
    }
}

void fn_805F2888(u8* p, s32 b) {
    u8* q = *(u8**)(p + 0x64);
    if (b != 0) {
        *(u32*)(q + 0xe0) |= 2;
    } else {
        *(u32*)(q + 0xe0) &= ~2;
    }
}

void fn_805F2868(u8* p, s32 i) {
    *(s32*)(p + 0xe4) = i;
    u8* old = *(u8**)(p + 0x70);
    u8* n = *(u8**)(p + 0xe8 + i * 4);
    *(u8**)(p + 0x70) = n;
    fn_805FEE88(n, old);
}

void fn_805F27A0(u8* p, f64 x, f64 y, f64 z) {
    *(f32*)(p + 0x2c) = x;
    *(f32*)(p + 0x30) = y;
    *(f32*)(p + 0x34) = z;
    fn_805F9418(*(u8**)(p + 0x64), x, y, z);
}

void fn_805F2718(u8* p, s32 v) {
    fn_805F6CF4(*(u8**)(p + 0x64), v);
    *(s32*)(p + 0x150) = v;
}

void fn_805F261C(u8* p, s32 v) {
    *(s32*)(p + 0x60) = v;
    fn_805F5304((Unk_Sel*)(p + 0x40), (u8*)v);
    fn_805F3A2C(p);
}

u32 fn_805F2424(u8* p) { return *(u32*)(p + 0x138) & 0x10; }

f32 fn_805F2408(u8* p) {
    f32 a = *(f32*)(p + 0x12c);
    f32 b = *(f32*)(p + 0x120);
    return b >= a ? b : a;
}


struct Unk_Vec3f { f32 x, y, z; };
void fn_805F74E4(u8*, u8*, u8*, f32);

int fn_805F51EC(s32* a, s32* b) {
    int r = 0;
    if (a[0] == b[0] && a[1] == b[1]) {
        r = 1;
    }
    return r;
}

void fn_805F3A0C(u8* p, Unk_Vec3f* v) {
    u8* q = *(u8**)(p + 0x7c);
    *(f32*)(q + 0x204) = v->x;
    *(f32*)(q + 0x208) = v->y;
    *(f32*)(q + 0x20c) = v->z;
}

u8* fn_805F39E8(u8* p) {
    u8* q = *(u8**)(p + 0x80);
    if (*(s32*)(q + 0x10) != 0) {
        return q + 0x210;
    }
    return *(u8**)(p + 0x70) + 0xc;
}

u8* fn_805F39C4(u8* p) {
    u8* q = *(u8**)(p + 0x80);
    if (*(s32*)(q + 0x10) != 0) {
        return q + 0x21c;
    }
    return *(u8**)(p + 0x70) + 0x18;
}

u8* fn_805F3988(u8* p) {
    u8* q = *(u8**)(p + 0x80);
    if (*(s32*)(q + 0x10) != 0) {
        return q + 0x348;
    }
    return *(u8**)(p + 0x70) + 0x3c;
}

void fn_805F390C(u8* p, s32 i) {
    if (*(s32*)(p + 0x134) != 1) {
        return;
    }
    if (*(s32*)(*(u8**)(p + 0x80) + 0x10) != 0) {
        return;
    }
    f32 v = 0.002f * *(f32*)(p + 0x124 + i * 0xc);
    if (v < 0.5f) {
        v = 0.5f;
    }
    fn_805F74E4(*(u8**)(p + 0x64), *(u8**)(p + 0x70) + 0x88, *(u8**)(lbl_806F5FF0 + 0x158) + 0x34, v);
}

int fn_805F38D8(u8* p) {
    if (*(s32*)(p + 0x18) != 0) {
        return *(s32*)(*(u8**)(p + 0x68) + 0x14) == 2;
    }
    return 1;
}

int fn_805F38B4(u8* p) { return *(s32*)(*(u8**)(p + 0x78) + 0x104) == 1; }

int fn_805F3870(u8* p) { return *(f32*)(*(u8**)(p + 0x78) + 0x124) > 0.0f; }


struct Unk_Sel { s32 state; s32 val; u8* a; u8* b; };

void fn_805F538C(Unk_Sel* p) {
    p->state = 0;
    p->val = 0;
    p->a = 0;
    p->b = 0;
}

void fn_805F5348(Unk_Sel* p, u8* a) {
    p->a = a;
    if (a != NULL) {
        p->state = 1;
        p->val = *(s32*)(a + 0xc);
    } else if (p->b != NULL) {
        p->state = 2;
    } else {
        p->state = 0;
    }
}

void fn_805F5304(Unk_Sel* p, u8* b) {
    p->b = b;
    if (b != NULL) {
        p->state = 2;
    } else {
        u8* a = p->a;
        if (a != NULL) {
            p->state = 1;
            p->val = *(s32*)(a + 0xc);
        } else {
            p->state = 0;
        }
    }
}

}  // extern "C"
