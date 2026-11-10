// Swf_80629B98: Resort Swordplay unit 0x80629B98-0x8062AA6C (Resort-only, no Wii Sports twin).
// "対戦フィールド" (versus field): vtable 0x806ED9B0, name 0x806EDA20; swf_umikage1, WS2_swf_avatarA/B.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

// @vt-begin
struct Unk_Vt78 {
    u8 pad[0x78];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38(s32, u16, f32, f32);
};
// @vt-end
#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_Words3 {
    u32 w0, w1, w2;
};

extern "C" {

void fn_80370BD4(BOOL, const char*);
u8 fn_8026BBC8(void*);
void fn_802A7AF0(void*, u8*, s32);
void fn_80328248(void*);
void fn_80328240(void*);
void fn_8028FD8C(u8*);
void fn_8037ED18(void*, s32);
extern u8* lbl_806F4EB4;
extern char lbl_806B5344[];
extern u8* lbl_806F5FF0;
extern f32 lbl_807D0318[3];
extern f32 lbl_806F3A88;
extern f32 lbl_806F3A90;
extern char lbl_806EDA20[];

Unk_Words3 fn_8062AA40(const u8* src) { return *(const Unk_Words3*)(src + 0x94); }

char* fn_8062AA34() { return lbl_806EDA20; }

void* fn_8062A9F4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80629C74(u8* p, s32 n);

void fn_8062A148(u8* p) {
    fn_8037ED18(PTR(lbl_806F5FF0, 0x158), 1);
    S32(p, 0x84) = 0;
    S32(p, 0x88) = 2;
    S32(p, 0x8c) = 0;
    fn_80629C74(p, 0);
    S32(p, 0x90) = 0;
    F32(p, 0x94) = lbl_807D0318[0];
    F32(p, 0x98) = lbl_807D0318[1];
    F32(p, 0x9c) = lbl_807D0318[2];
    F32(p, 0xa0) = lbl_807D0318[0];
    F32(p, 0xa4) = lbl_807D0318[1];
    F32(p, 0xa8) = lbl_807D0318[2];
}

void fn_80629FC4(u8* p) {
    if (--S32(p, 0x84) < 0) {
        S32(p, 0x84) = 0;
        fn_80629C74(p, S32(p, 0x8c) != 0);
        S32(p, 0x8c) = 0;
    }
    fn_80328248(PTR(p, 0x60));
    fn_80328240(PTR(p, 0x60));
    fn_80328248(PTR(p, 0x68));
    fn_80328240(PTR(p, 0x68));
    fn_8028FD8C(p);
}

f32 fn_80629D68(u8* p) {
    if (S32(p, 0x90) == 0) {
        return lbl_806F3A88;
    }
    return 17.0f;
}

void fn_80629D50(u8* p) {
    if (S32(p, 0x90) == 0) {
        S32(p, 0x90) = 1;
    }
}

void fn_80629D28(u8* p) {
    if (S32(p, 0x90) == 1 || S32(p, 0x90) == 2) {
        S32(p, 0x90) = 3;
        F32(p, 0x98) = -lbl_806F3A90;
    }
}

void fn_80629CE4(u8* p) {
    F32(p, 0x94) = lbl_807D0318[0];
    F32(p, 0x98) = lbl_807D0318[1];
    F32(p, 0x9c) = lbl_807D0318[2];
    F32(p, 0xa0) = lbl_807D0318[0];
    F32(p, 0xa4) = lbl_807D0318[1];
    F32(p, 0xa8) = lbl_807D0318[2];
    S32(p, 0x90) = 0;
}

void fn_80629C74(u8* p, s32 n) {
    if (n != S32(p, 0x88)) {
        void* obj = PTR(PTR(PTR(p, 0x68), 0x8), 0x40);
        ((Unk_Vt78*)(obj))->v38(0, n, 30.0f, 0.0f);
        S32(p, 0x88) = n;
    }
}

void fn_80629C3C(u8* p) {
    fn_80629C74(p, 2);
    S32(p, 0x84) = 90;
}

void fn_80629B98(u8* p) {
    u8* obj;
    fn_80370BD4(lbl_806F4EB4 != NULL, lbl_806B5344);
    obj = lbl_806F4EB4;
    fn_802A7AF0(PTR(p, 0x64), (u8*)PTR(obj, 0x54) + fn_8026BBC8(obj) * 0x138, 0);
    fn_80370BD4(lbl_806F4EB4 != NULL, lbl_806B5344);
    obj = lbl_806F4EB4;
    fn_802A7AF0(PTR(p, 0x6c), (u8*)PTR(obj, 0x54) + fn_8026BBC8(obj) * 0x138, 0);
}

}  // extern "C"
