// Swf_8063F630: Resort Swordplay unit 0x8063F630-0x806419C4 (Resort-only, no Wii Sports twin).
// player movement fields (プレイヤー移動フィールド, 組み手用/試合用 variants).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_806418AC(u8*);
extern u8 lbl_806EE758[];
extern u8 lbl_806EE77C[];
extern u8 lbl_806EE79C[];
extern void* lbl_806EE6C8[];
extern void* lbl_806EE6F8[];
void fn_8063F828(u8*);
extern u8* lbl_806F5FF0;
void fn_8063D16C(u8*);
void fn_8063C9CC(u8*, u32, f32);

u8* fn_806419B8() {
    return lbl_806EE758;
}

u8* fn_806419AC() {
    return lbl_806EE77C;
}

u8* fn_806419A0() {
    return lbl_806EE79C;
}

// Deleting destructor of a class without a base destructor.
void* fn_80641960(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80641920(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_806418A8() {}

void fn_80641754() {}

void fn_8064124C() {}

int fn_80641244() {
    return 0;
}

u8* fn_80640B78(u8* p) {
    fn_806418AC(p);
    *(void**)p = lbl_806EE6F8;
    return p;
}

void fn_80640980(u8*, f32* out, const f32* in) {
    out[0] = in[0];
    out[1] = *(f32*)(*(u8**)(lbl_806F5FF0 + 0x160) + 0x24);
    out[2] = in[2];
}

// Deleting destructor of a class without a base destructor.
void* fn_80640700(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806406C4(u8* p) {
    fn_806418AC(p);
    *(void**)p = lbl_806EE6C8;
    return p;
}

void fn_80640600(u8* p) {
    fn_8063D16C(*(u8**)(p + 0x90));
    fn_8063C9CC(*(u8**)(p + 0x90), *(u32*)(*(u8**)(lbl_806F5FF0 + 0x184) + 0x34), 0.0f);
    *(f32*)(p + 0x94) = 0.0f;
}

void fn_8063F81C(u8* p, u32 a, u32 b) {
    *(u32*)(p + 0x88) = a;
    *(u32*)(p + 0x8c) = b;
    fn_8063F828(p);
}

}  // extern "C"
