// Swf_8064F2B0: Resort Swordplay unit 0x8064F2B0-0x80650440 (Resort-only, no Wii Sports twin).
// Speed Slice trainer and flags (WS2_swf_trainer, WS2_swf_flag), trainer animation (トレーナーアニメーション).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
struct Unk_VtAt48_50_i { u8 pad[0x48]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void vf(s32); };
#include <nw4r/g3d.h>

extern "C" {

extern u8 lbl_806EF548[];
void fn_8064F628(u8*, s32, s32, s32);
void fn_802B73BC(s32);
u8* fn_8033EF2C();
void fn_8036ECD0(u8*, u8*, s32);

u8* fn_80650434() {
    return lbl_806EF548;
}

// Deleting destructor of a class without a base destructor.
void* fn_806503F4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8064FB10(u8* p) {
    if (*(s32*)(p + 0xec) != 0) {
        fn_8036ECD0(*(u8**)(p + 0x18), fn_8033EF2C(), 1);
        nw4r::g3d::G3DState::Invalidate(0x7ff);
    }
}

s32 fn_8064F43C(u8*, u32 a, BOOL b) {
    s32 r = 0;
    switch (a) {
    case 0:
        r = 0;
        break;
    case 1:
        r = !b ? 1 : 4;
        break;
    case 2:
        r = !b ? 2 : 5;
        break;
    case 3:
        r = !b ? 3 : 6;
        break;
    case 4:
        r = 7;
        break;
    case 5:
        r = 8;
        break;
    case 6:
        r = 9;
        break;
    case 7:
        r = 10;
        break;
    case 8:
        r = 11;
        break;
    case 9:
        r = 12;
        break;
    }
    return r;
}

void fn_8064F374(u8* p) {
    (*(Unk_VtAt48_50_i**)(*(u8**)(p + 0x18) + 0x20))->vf(0x6);
}

void fn_8064F358(u8* p) {
    (*(Unk_VtAt48_50_i**)(*(u8**)(p + 0x18) + 0x20))->vf(0xe);
}

void fn_8064F348(u8* p) {
    fn_8064F628(p, 4, -1, 0);
}

void fn_8064F338(u8* p) {
    fn_8064F628(p, 6, -1, 0);
}

void fn_8064F2F0(u8* p, s32 a) {
    *(s32*)(p + 0xe8) = a;
    fn_802B73BC(0x2f0);
    fn_8064F628(p, 1, *(s32*)(p + 0xe8), 0);
}

void fn_8064F2D0(u8* p) {
    if (*(s32*)(p + 0x60) == 2) {
        fn_8064F628(p, 3, *(s32*)(p + 0xe8), 0);
    }
}

void fn_8064F2C0(u8* p) {
    fn_8064F628(p, 7, -1, 0);
}

void fn_8064F2B0(u8* p) {
    fn_8064F628(p, 9, -1, 0);
}

}  // extern "C"
