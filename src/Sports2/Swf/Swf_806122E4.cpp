// Swf_806122E4: Resort Swordplay unit 0x806122E4-0x806124AC (Resort-only, no Wii Sports twin).
// layout with N_roundDis_00..03 (vtable 0x806ED018).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_802B7138(s32);
void fn_802B70F8(s32);
void* fn_8026F970(u8*, void*);
void fn_8035FB88(u8*, u8*, u8*, s32, s32, s32, u8*, u8*);
extern s32 lbl_806F3998;
extern void* lbl_806ED008[];
extern u8 lbl_8068ACC8[];
extern u8 lbl_806ED018[];

u8* fn_806123BC(u8* p) {
    fn_8035FB88(p, lbl_8068ACC8 + 0x38, lbl_8068ACC8 + 0x45, 1, 0, 0, lbl_8068ACC8 + 0x58, lbl_8068ACC8 + 0x5e);
    *(u8**)(p + 0x30) = lbl_806ED018;
    *(u8**)(p + 0x18) = lbl_806ED018 + 0x8;
    *(u8**)(p + 0x94) = lbl_806ED018 + 0x78;
    *(u8**)(p + 0x98) = lbl_806ED018 + 0x88;
    return p;
}

void fn_80612308(u8* p, s32 n) {
    u8* pane;
    pane = (u8*)fn_8026F970(p + 0x94, lbl_806ED008[0]);
    pane[0xbb] = pane[0xbb] & 0xFE;
    pane = (u8*)fn_8026F970(p + 0x94, lbl_806ED008[1]);
    pane[0xbb] = pane[0xbb] & 0xFE;
    pane = (u8*)fn_8026F970(p + 0x94, lbl_806ED008[2]);
    pane[0xbb] = pane[0xbb] & 0xFE;
    pane = (u8*)fn_8026F970(p + 0x94, lbl_806ED008[3]);
    pane[0xbb] = pane[0xbb] & 0xFE;
    pane = (u8*)fn_8026F970(p + 0x94, lbl_806ED008[n]);
    pane[0xbb] = (pane[0xbb] & 0xFE) | 1;
}

void fn_80612300() { fn_802B70F8(0x17); }

void fn_806122E4(u8* p) {
    if (lbl_806F3998 == *(s32*)(p + 0x74)) {
        fn_802B7138(0x17);
    }
}

}  // extern "C"
