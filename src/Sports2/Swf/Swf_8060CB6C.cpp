// Swf_8060CB6C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).

struct Unk_VtAt30 {
    u8 pad[0x30];
    virtual void vf8(); virtual void vfC(); virtual void vf10(); virtual void vf14(); virtual void vf18();
    virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C(); virtual void vf40();
    virtual void vf44(); virtual void vf48(); virtual void vf4C(); virtual void vf50(); virtual void vf54();
    virtual void vf58(); virtual void vf5C(); virtual void vf60(); virtual void vf64(); virtual void vf68();
    virtual void vf6C(); virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C(); virtual void vf90();
    virtual void vf94(); virtual void vf98(); virtual void vf9C(); virtual void vfA0(); virtual void vfA4();
    virtual void vfA8(); virtual void vfAC(); virtual void vfB0(); virtual void vfB4(); virtual void vfB8();
    virtual void vfBC(); virtual void vfC0(); virtual void vfC4(); virtual void vfC8(); virtual void vfCC();
    virtual void vfD0(); virtual void vfD4(); virtual void vfD8(); virtual void vfDC(); virtual void vfE0();
    virtual void vfE4(); virtual void vfE8(); virtual void vfEC(); virtual void vfF0(); virtual void vfF4();
    virtual void vfF8();
};

extern "C" {


void fn_80277724(u8*);
void fn_80374B3C(u8*);
void fn_8037FAC8(u8*);
void fn_8037FB94(u8*);
void fn_805F09CC(u8*);
void fn_805F0B08(u8*);
void fn_805FB0EC(u8*);
void fn_80610928(u8*);
void fn_80612650(u8*);
void fn_806530E4(u8*);
extern u8 lbl_806EC36C[];
extern void* lbl_806EC318[];

u8* fn_8060E6B4() { return lbl_806EC36C; }

void* fn_8060E674(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8060E614(u8* p) { fn_805F0B08(*(u8**)(p + 0x48)); }

void fn_8060E5BC(u8* p) { fn_805F09CC(*(u8**)(p + 0x48)); }

s32 fn_8060E184(u8* p) { return *(s32*)(*(u8**)(p + 0x48) + 0x54); }

u8* fn_8060DD30(u8* p) { return p + 0x64; }

u8* fn_8060DD28(u8* p) { return p + 0x64; }

void* fn_8060DC94(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8060D8AC(u8* p) { fn_80277724(p + 0x94); }

void fn_8060D8A4(u8* p) { fn_80277724(p + 0x94); }

void fn_8060D2F8(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xb0)))->vf48(); }

void fn_8060D2E4(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vfF4(); }

void fn_8060D2D0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xac)))->vf48(); }

void fn_8060D290() {}

void fn_8060D1F8(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xd8)))->vf48(); }

void fn_8060D1F0(u8* p) { fn_8037FB94(*(u8**)(p + 0xd8)); }

void fn_8060D1E8(u8* p) { fn_8037FAC8(*(u8**)(p + 0xd8)); }

void fn_8060D19C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xa8)))->vfF4(); }

void fn_8060D120(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vfF8(); }

void fn_8060D118(u8* p) { fn_80610928(*(u8**)(p + 0xc0)); }

void fn_8060D104(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xc0)))->vf48(); }

void fn_8060D05C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xb8)))->vfF8(); }

u8 fn_8060D050(u8* p) { return *(u8*)(*(u8**)(p + 0xb8) + 0x110); }

void fn_8060D048(u8* p) { fn_80612650(*(u8**)(p + 0xb8)); }

void fn_8060D034(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xb4)))->vfF4(); }

void fn_8060D020(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xb4)))->vf48(); }

void fn_8060CF90(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vfF8(); }

u8 fn_8060CF84(u8* p) { return *(u8*)(*(u8**)(p + 0xbc) + 0xd0); }

void fn_8060CF70(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xbc)))->vf48(); }

void fn_8060CF50(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xd0)))->vfF8(); }

u8 fn_8060CF44(u8* p) { return *(u8*)(*(u8**)(p + 0xd0) + 0x116); }

void fn_8060CC88(u8* p) { fn_806530E4(*(u8**)(p + 0xc8)); }

u8 fn_8060CBE4(u8* p) { return *(u8*)(*(u8**)(p + 0xd4) + 0xd0); }

void fn_8060CBD0(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xd4)))->vf48(); }

void fn_8060CBC8(u8* p) { fn_80374B3C(*(u8**)(p + 0xe0)); }

void fn_8060CBB4(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe0)))->vfF8(); }

u8 fn_8060CBA8(u8* p) { return *(u8*)(*(u8**)(p + 0xe0) + 0x11d); }

void fn_8060CB6C(u8* p) { ((Unk_VtAt30*)(*(u8**)(p + 0xe0)))->vf48(); }


// ---- hand-written (first pass) ----
void fn_80349B74(u8*, s32);
void fn_80610FAC(u8*);
void fn_80611E14(u8*, s32);
void fn_803805E0(u8*, s32);

s32 fn_8060E190(u8* p) {
    if (*(s32*)(p + 0x14) != 0) {
        return *(u32*)(*(u8**)(p + 0x48) + 0x4c) & 1;
    }
    return 0;
}

s32 fn_8060E164(u8* p) {
    if (*(s32*)(p + 0x14) != 0) {
        return *(s32*)(*(u8**)(p + 0x48) + 0x44);
    }
    return 0;
}

s32 fn_8060E140(u8* p) {
    if (*(s32*)(p + 0x14) != 0) {
        return *(u32*)(*(u8**)(p + 0x48) + 0x4c) & 4;
    }
    return 0;
}

void fn_8060E128(u8* p, f32 f) {
    *(s32*)(*(u8**)(p + 0x48) + 0x2624) = 1;
    *(f32*)(*(u8**)(p + 0x48) + 0x2628) = f;
}

void fn_8060D498(u8* p, s32 a, s32 b, s32 i) {
    *(s32*)(p + 0x98 + i * 4) = a;
    *(s32*)(p + 0xa0 + i * 4) = b;
}

void fn_8060D294(u8* p, s32 v) {
    *(u8*)(*(u8**)(p + 0xd8) + 0x1a4) = v == 1;
    if (v == 0) {
        *(s32*)(*(u8**)(p + 0xd8) + 0x100) = 0;
    }
    (*(Unk_VtAt30**)(p + 0xd8))->vfF4();
}

void fn_8060D260(u8* p, s32 b) {
    if (b != 0) {
        (*(Unk_VtAt30**)(p + 0xd8))->vf4C();
    } else {
        (*(Unk_VtAt30**)(p + 0xd8))->vfF8();
    }
}

u8* fn_8060D1B0(u8* p) {
    fn_803805E0(*(u8**)(p + 0xdc), 0);
    return *(u8**)(p + 0xdc);
}

void fn_8060D0C4(u8* p, s32 v) {
    fn_80610FAC(*(u8**)(p + 0xc0));
    fn_80611E14(*(u8**)(p + 0xbc), v);
}

void fn_8060CF64(u8* p) { fn_80349B74(*(u8**)(p + 0xd0), 0); }

void fn_8060CBF0(u8* p, s32 b) {
    if (b != 0) {
        (*(Unk_VtAt30**)(p + 0xd4))->vf4C();
    } else {
        Unk_VtAt30* q = *(Unk_VtAt30**)(p + 0xd4);
        if (*((u8*)q + 0xd0) != 0) {
            q->vfF8();
        }
    }
}

int fn_8060CB80(u8* p) {
    u8* q = *(u8**)(p + 0xe0);
    int r = 0;
    if (*(u8*)(q + 0x11e) != 0 && *(u8*)(q + 0xd0) != 0) {
        r = 1;
    }
    return r;
}


u8* fn_805F0B0C(u8*, s32);

u8* fn_8060E61C(u8* p) {
    fn_805FB0EC(p);
    *(void***)p = lbl_806EC318;
    u8* o = (u8*)operator new(0x262c);
    if (o != NULL) {
        o = fn_805F0B0C(o, 0);
    }
    *(u8**)(p + 0x48) = o;
    return p;
}

}  // extern "C"
