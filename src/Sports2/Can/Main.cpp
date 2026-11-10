// Canoeing (Resort-only), .text 0x804AE800-0x804B171C: singleton "Main" (WiiRemote.carc, Env/WS2_can.*). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>
#include <nw4r/math.h>
#include <revolution/MTX.h>

extern "C" {

s32 fn_804B2300(u8* p);
f32 fn_8049427C(const u8* p, const Vec* v);
u32 fn_804BD998(u8* p);
extern u8* lbl_806F5838; // Config instance
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_804B14E8(u8* p); // ctor
extern void* lbl_806F58E8; // instance
extern void* lbl_806F58EC; // heap
struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
};

struct Unk_VtAt30 {
    u8 unk0[0x30];
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

void __ct__Q23EGG8DisposerFv(u8*);
void fn_8025C380(u8*);
void fn_8025C3F0(u8*);
void fn_8026C8E8(u8*, s32);
void fn_8028BF1C(u8*);
void fn_8028BF70(u8*, s32);
void fn_8035D6C8(u8*);
void fn_80499B3C(u8*);
void fn_8049E274(u8*);
void fn_804AF100(u8*, u32);
void fn_804AF154(u8*, u32);
extern u8* lbl_806F5898;
extern u8* lbl_806F58A0;
extern u8* lbl_806F5924;
extern u8 lbl_806DCA30[];
extern u8 lbl_806DCA78[];

void fn_804B15EC(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F58E8 == NULL && lbl_806F58EC == NULL, "Main");
    lbl_806F58EC = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0xac, pHeap, 4);
        if (p != NULL) {
            p = fn_804B14E8((u8*)p);
        }
        lbl_806F58E8 = p;
    } else {
        void* p = operator new(0xac);
        if (p != NULL) {
            p = fn_804B14E8((u8*)p);
        }
        lbl_806F58E8 = p;
    }
}

void fn_804B15DC() {
    lbl_806F58E8 = NULL;
    lbl_806F58EC = NULL;
}

u8* fn_804B14E8(u8* p) {
    fn_8035D6C8(p);
    fn_8025C3F0(p + 0x8);
    *(u8**)(p) = lbl_806DCA30;
    *(u8**)(p + 0x10) = lbl_806DCA30 + 0x14;
    __ct__Q23EGG8DisposerFv(p + 0x28);
    *(u8**)(p + 0x28) = lbl_806DCA78;
    *(u16*)(p + 0x80) = 0;
    fn_8026C8E8(p + 0x8, 0);
    *(u8*)(p + 0x20) = 0;
    *(u8*)(p + 0x21) = 8;
    fn_8025C380(p + 0x8);
    return p;
}

u32 fn_804B084C(u8* p) { return *(u32*)(p + 0x4c); }

void fn_804B01BC(u8* p) {
    *(u32*)(p + 0x8c) = -1;
    *(u32*)(p + 0x90) = -1;
}

void fn_804AFADC(u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0x4c); i++) {
        ((u8**)(p + 0x3c))[i][0x7c] = 0;
    }
}

void fn_804AFAA8(u8* p) {
    for (s32 i = 0; i < *(s32*)(p + 0x4c); i++) {
        ((u8**)(p + 0x3c))[i][0x7c] = 1;
    }
}

void fn_804AFA94(u8* p) { *(u8*)(*(u8**)(*(u8**)(p + 0x50)) + 0x18) = 0; }

void fn_804AFA40(u8* p) {
    s32 i = 0;
    s32 n = fn_804B2300(p);
    for (; i < n; i++) {
        (*(u8***)(p + 0x50))[i][0x18] = 1;
    }
}

void fn_804AFA08(u8* p) {
    fn_80499B3C(lbl_806F5898);
    *(u8*)(p + 0x38) = 1;
}

void fn_804AF778(u8* p) { *(u32*)(p + 0x6c) = 90; }

void fn_804AF0F4(u8* p) { fn_804AF154(p, *(u32*)(lbl_806F5924 + 0x48)); }

void fn_804AF0E8(u8* p) { fn_804AF100(p, *(u32*)(lbl_806F5924 + 0x48)); }

u8* fn_804AF0D0(const u8* p) { return ((u8**)(p + 0x3c))[*(s32*)(lbl_806F5924 + 0x48)]; }

f32 fn_804AF094(const u8* p) { return (f32)(*(s32*)(p + 0x8c) - *(s32*)(p + 0x84)) / 60.0f; }

// Frames since the start mark at 0x90 (-1 = none), in seconds.
f32 fn_804AF048(const u8* p) {
    if (*(s32*)(p + 0x90) == -1) {
        return 0.0f;
    }
    return (f32)(*(s32*)(p + 0x84) - *(s32*)(p + 0x90)) / 60.0f;
}

void fn_804AEE78() {
    u8* q = *(u8**)(lbl_806F58A0 + 0x28);
    fn_8028BF70(q, 0);
    fn_8028BF1C(q);
}

void fn_804AED88(u8* p) {
    fn_8049E274(lbl_806F58A0);
    ((Unk_VtAt0*)(*(u8**)(p + 0x7c)))->vf1C();
    ((Unk_VtAt30*)(*(u8**)(p + 0x70)))->vf44();
    ((Unk_VtAt30*)(*(u8**)(p + 0x74)))->vf44();
    ((Unk_VtAt30*)(*(u8**)(p + 0x78)))->vf44();
}

BOOL fn_804AEA20(const u8* p) {
    u8* cur = *(u8**)(p + 0x60);
    BOOL r = FALSE;
    if (*(u8**)(p + 0x64) == cur && *(s32*)(cur + 0x8c) != 4) {
        r = TRUE;
    }
    return r;
}

u8* fn_804AE8F8(u8* p) { return *(u8**)(p + 0x64) + 0xc; }

u32 fn_804AE8E8(u8* p, s32 a1) { return *(u32*)(p + a1 * 4 + 0x3c); }

u32 fn_804AE8B0(const u8* p, s32 mode) {
    BOOL ok = FALSE;
    if (lbl_806F5924[0x18] != 0 && mode == 1) {
        ok = TRUE;
    }
    if (ok) {
        return fn_804BD998(*(u8**)(p + 0x78));
    }
    return 0;
}

f32 fn_804AE858(const u8* p, const Vec* v) { return nw4r::math::FSqrt(fn_8049427C(*(u8**)(p + 0x64), v)); }

BOOL fn_804AE834() { return *(s32*)(lbl_806F5838 + 0x18) + 1 >= 3; }

BOOL fn_804AE800() {
    return *(s32*)(lbl_806F5838 + 0x18) + 1 >= (lbl_806F5924[0x18] ? 3 : 4);
}

}  // extern "C"
