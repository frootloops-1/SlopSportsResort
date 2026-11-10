// Swf_806121F0: Resort Swordplay unit 0x806121F0-0x806122E4 (Resort-only, no Wii Sports twin).
// layout from the WS2_game_swf archive (vtable 0x806ECEF0).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

void fn_802B73BC(s32);
void fn_8035FB88(u8*, u8*, u8*, s32, s32, s32, u8*, u8*);
extern u8 lbl_8068AC98[];
extern u8 lbl_806ECEF0[];

u8* fn_806121F8(u8* p) {
    fn_8035FB88(p, lbl_8068AC98, lbl_8068AC98 + 0xd, 1, 0, 0, lbl_8068AC98 + 0x1d, lbl_8068AC98 + 0x23);
    *(u8**)(p + 0x30) = lbl_806ECEF0;
    *(u8**)(p + 0x18) = lbl_806ECEF0 + 0x8;
    *(u8**)(p + 0x94) = lbl_806ECEF0 + 0x78;
    *(u8**)(p + 0x98) = lbl_806ECEF0 + 0x88;
    return p;
}

void fn_806121F0() { fn_802B73BC(0x270); }

}  // extern "C"
