// Swf_80624988: Resort Swordplay unit 0x80624988-0x80624C50 (Resort-only, no Wii Sports twin).
// hit effect holder (WS2_swf_hit_red01 ...; vtable 0x806ED7F0).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

extern "C" {

void fn_803674C4(u8*);
void fn_803673C0(u8*, s32);
void fn_8036773C(u8*, f32);
void fn_8036759C(u8*);
void fn_80367E30(u8*, s32, s32, s32);
extern u8 lbl_806ED7F0[];

u8* fn_80624BE4(u8* p) {
    fn_80367E30(p, 600, 12, 0);
    PTR(p, 0x34) = lbl_806ED7F0;
    PTR(p, 0x30) = lbl_806ED7F0 + 0x8;
    u8* q = p;
    if (q != NULL) {
        q += 0x30;
    }
    PTR(p, 0x2c) = q;
    return p;
}

void fn_80624988(u8* p) {
    fn_803674C4(p);
    fn_803673C0(p, 0);
    fn_8036773C(p, -60.0f);
    F32(p, 0x20) = 0.5f;
    fn_8036759C(p);
}

}  // extern "C"
