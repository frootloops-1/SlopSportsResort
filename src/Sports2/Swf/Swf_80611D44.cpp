// Swf_80611D44: Resort Swordplay unit 0x80611D44-0x8061204C (Resort-only, no Wii Sports twin).
// layout with P_miiFace_00/01 and T_miiName_%02d panes (vtable 0x806ECCB8).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void* fn_8026F970(u8*, void*);
void* fn_8026F968(u8*, void*);
void fn_8026F8C0(u8*, void*, s32, s32, ...);
void fn_8027CB94(void*, u32);
void fn_8027CC74(void*, void*);
void* fn_8027CCC0(s32);
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, s32);
int snprintf(char*, unsigned long, const char*, ...);
extern void* lbl_806ECC90[];
extern void* lbl_806F3980[2];
extern const char* lbl_806F3988;
extern u8 lbl_8068ABA8[];
extern u8 lbl_806ECCB8[];

u8* fn_80611EF0(u8* p) {
    fn_80371668(p, 2, lbl_8068ABA8 + 0x89, lbl_8068ABA8 + 0x96, 1, 0, 0);
    *(u8**)(p + 0x30) = lbl_806ECCB8;
    *(u8**)(p + 0x18) = lbl_806ECCB8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806ECCB8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806ECCB8 + 0x88;
    *(void***)(p + 0x110) = NULL;
    *(void***)(p + 0x110) = (void**)operator new[](8);
    for (s32 i = 0; i < 2; i++) {
        (*(void***)(p + 0x110))[i] = NULL;
        (*(void***)(p + 0x110))[i] = fn_8027CCC0(0);
    }
    *(s32*)(p + 0x114) = 0;
    for (u8 i = 0; i < 4; i++) {
        p[0x118 + i] = 3;
    }
    return p;
}

void fn_80611E98(u8* p, u32 a, s32 i) {
    fn_8027CB94((*(void***)(p + 0x110))[i], a);
    fn_8027CC74((*(void***)(p + 0x110))[i], fn_8026F970(p + 0x94, lbl_806F3980[i]));
}

void fn_80611E2C(u8* p, s32 a, s32 b) {
    char buf[0x20];
    snprintf(buf, 0x20, lbl_806F3988, b);
    fn_8026F8C0(p + 0x94, fn_8026F968(p + 0x94, buf), 0x32, 1, a);
}

void fn_80611E14(u8* p, u8 v) {
    s32 n = *(s32*)(p + 0x114);
    p[0x118 + n] = v;
    *(s32*)(p + 0x114) = n + 1;
}

void fn_80611D44(u8* p) {
    for (s32 i = 0; i < 3; i++) {
        BOOL b;
        u8* pane;
        b = p[0x118 + i] == 0;
        pane = (u8*)fn_8026F970(p + 0x94, lbl_806ECC90[i * 3 + 0]);
        pane[0xbb] = (pane[0xbb] & 0xFE) | b;
        b = p[0x118 + i] == 1;
        pane = (u8*)fn_8026F970(p + 0x94, lbl_806ECC90[i * 3 + 1]);
        pane[0xbb] = (pane[0xbb] & 0xFE) | b;
        b = p[0x118 + i] == 2;
        pane = (u8*)fn_8026F970(p + 0x94, lbl_806ECC90[i * 3 + 2]);
        pane[0xbb] = (pane[0xbb] & 0xFE) | b;
    }
}

}  // extern "C"
