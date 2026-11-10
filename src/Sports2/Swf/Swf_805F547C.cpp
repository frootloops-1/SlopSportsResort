// Swf_805F547C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_8064ED30(u8*);
extern u8 lbl_806EBB48[];

u8* fn_805FAE18() { return lbl_806EBB48; }

void fn_805FAAD8() {}

void fn_805FA9AC() {}

void fn_805FA9A8() {}

void* fn_805FA844(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805FA804(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805FA7C4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805FA784(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_805FA6EC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805F5C38(u8* p) { fn_8064ED30(*(u8**)(p + 0xc0)); }


// ---- hand-written (first pass) ----
struct Unk_Copy30 { u32 w[12]; };
struct Unk_Copy6C { u32 w[27]; };
struct Unk_VtAt48 {
    u8 pad[0x48];
    virtual void vf8(); virtual void vfC(); virtual void vf10(); virtual void vf14(); virtual void vf18();
    virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C(); virtual void vf40();
    virtual void vf44(); virtual void vf48(); virtual void vf4C(); virtual u8* vf50(s32);
};

extern u8* lbl_806F5FF0;
extern s32 lbl_806F5FAC;
extern s32 lbl_806F5FB0;
extern u8 lbl_807D0378[];
void fn_80602BD4(u8*, u8*);
void fn_805F711C(u8*);
void fn_80638DCC(u8*);
void fn_805F6330(u8*, s32, s32, s32);
void fn_805F6C9C(u8*);

void fn_805FACF8(u8*, Unk_Copy6C* d, Unk_Copy6C* s) { *d = *s; }

void fn_805FA684() {
    lbl_806F5FAC = 0;
    lbl_806F5FB0 = 0;
}

void fn_805F6CF4(u8* p, s32 i) {
    *(s32*)(p + 0x40) = *(s32*)(p + 0x44 + i * 4);
    fn_805F6C9C(p);
}

void fn_805F6C84(u8* p, s32 i) {
    *(s32*)(p + 0x50) = i;
    *(s32*)(p + 0x4c) = *(s32*)(p + 0x54 + i * 4);
}

u8* fn_805F6AA4(u8* p) {
    u8* q = *(u8**)(p + 0x30);
    if (q != NULL) {
        return ((Unk_VtAt48*)*(u8**)(q + 0x20))->vf50(0x13);
    }
    return lbl_807D0378;
}

int fn_805F5C20(u8* p) { return *(s32*)(*(u8**)(p + 0xc0) + 0x14) == 2; }

void fn_805F5ABC(u8* p) { fn_805F6330(p, 10, -1, 0); }
void fn_805F59F0(u8* p) { fn_805F6330(p, 0, -1, 0); }
void fn_805F599C(u8* p) { fn_805F6330(p, 7, -1, 0); }
void fn_805F598C(u8* p) { fn_805F6330(p, 8, -1, 0); }

void fn_805F5960(u8* p) {
    if (*(s32*)(p + 0x11c) == 4) {
        fn_805F6330(p, 5, *(s32*)(p + 0x120) != 6, 0);
    }
}

void fn_805F5944(u8* p) { fn_805F6330(p, 6, *(s32*)(p + 0x120) != 8, 0); }

void fn_805F5930(u8* p) {
    u8* q = *(u8**)(p + 0xcc);
    if (q != NULL) {
        fn_80638DCC(q);
    }
}

void fn_805F58B4(u8* p) {
    *(u32*)(p + 0xe0) &= ~1;
    fn_805F711C(p);
}

void fn_805F547C(u8* p, Unk_Copy30* src) {
    *(Unk_Copy30*)(p + 0x84) = *src;
    fn_80602BD4(lbl_806F5FF0, *(u8**)(p + 0x80));
}


void __ct__Q34nw4r4math4VEC3Fv(u8*);

u8* fn_805FA8F4(u8* p) {
    __ct__Q34nw4r4math4VEC3Fv(p + 0xc);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    return p;
}

}  // extern "C"
