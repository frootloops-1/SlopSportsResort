// Swf_8061204C: Resort Swordplay unit 0x8061204C-0x806121F0 (Resort-only, no Wii Sports twin).
// layout with T_start_00 (vtable 0x806ECDD8).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_80370BD4(BOOL, const char*);
void* fn_8026F968(u8*, void*);
void fn_8026F8C0(u8*, void*, s32, s32, ...);
void fn_8035FB88(u8*, u8*, u8*, s32, s32, s32, u8*, u8*);
extern u8* lbl_806F4E98; // StaticMem instance
extern char lbl_806B56A8[];
extern void* lbl_806F3990[2];
extern u8 lbl_8068AC50[];
extern u8 lbl_806ECDD8[];

u8* fn_80612100(u8* p) {
    fn_8035FB88(p, lbl_8068AC50 + 0x16, lbl_8068AC50 + 0x23, 1, 0, 0, lbl_8068AC50 + 0x33, lbl_8068AC50 + 0x39);
    *(u8**)(p + 0x30) = lbl_806ECDD8;
    *(u8**)(p + 0x18) = lbl_806ECDD8 + 0x8;
    *(u8**)(p + 0x94) = lbl_806ECDD8 + 0x78;
    *(u8**)(p + 0x98) = lbl_806ECDD8 + 0x88;
    return p;
}

void fn_8061204C(u8* p) {
    s32 x;
    fn_80370BD4(lbl_806F4E98 != NULL, lbl_806B56A8);
    s32 v = *(s32*)(lbl_806F4E98 + 0x18);
    if (v == 5) {
        x = 50;
    } else {
        x = (v == 6) ? 51 : 52;
    }
    fn_8026F8C0(p + 0x94, fn_8026F968(p + 0x94, lbl_806F3990[0]), x, 0);
    fn_8026F8C0(p + 0x94, fn_8026F968(p + 0x94, lbl_806F3990[1]), x, 0);
}

}  // extern "C"
