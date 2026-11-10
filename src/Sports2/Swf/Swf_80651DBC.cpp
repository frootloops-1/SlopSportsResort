// Swf_80651DBC: Resort Swordplay unit 0x80651DBC-0x80652004 (Resort-only, no Wii Sports twin).
// layout 65033_swf_tameshi_MatchPoint.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_80651DBC(u8*, int);
void fn_80651F84(u8*, int);
void fn_802B73BC(s32);

void fn_80651FFC(u8* p, int a) {
    fn_80651F84(p - 0x94, a);
}

void fn_80651FF4(u8* p, int a) {
    fn_80651DBC(p - 0x94, a);
}

void fn_80651FEC(u8* p, int a) {
    fn_80651F84(p - 0x18, a);
}

void fn_80651DC4(u8* p, s32 i, u8 v) {
    u8* o = (*(u8***)(p + 0x114))[i];
    o[0xbb] = (o[0xbb] & ~1) | v;
}

void fn_80651DBC(u8*, int) {
    fn_802B73BC(0x2ef);
}

}  // extern "C"
