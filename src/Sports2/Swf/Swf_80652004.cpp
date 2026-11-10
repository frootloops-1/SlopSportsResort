// Swf_80652004: Resort Swordplay unit 0x80652004-0x80652274 (Resort-only, no Wii Sports twin).
// layout 65040_trueFalse_Jp / 65041_trueFalse_UsEu.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

extern "C" {

void fn_803715C0(u8*, s32, s32);
void fn_806521FC(u8*, int);
extern u8 lbl_806EFA38[];
u8* fn_8026F6AC(u8*, s32);
BOOL fn_8025EAF8(u8*);
void fn_801ED220(u8*);

void fn_8065226C(u8* p, int a) {
    fn_806521FC(p - 0x94, a);
}

void fn_80652264(u8* p, int a) {
    fn_806521FC(p - 0x18, a);
}

u8* fn_806521A0(u8* p) {
    fn_803715C0(p, 2, 0);
    *(u8**)(p + 0x30) = lbl_806EFA38;
    *(u8**)(p + 0x18) = lbl_806EFA38 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EFA38 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EFA38 + 0x88;
    return p;
}

void fn_80652050(u8* p, const f32* v) {
    u8* o = *(u8**)(p + 0x118);
    *(f32*)(o + 0x2c) = v[0];
    *(f32*)(o + 0x30) = v[1];
    *(f32*)(o + 0x34) = v[2];
}

void fn_8065204C() {}

void fn_80652004(u8* p) {
    if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 0))) {
        fn_801ED220(p);
    }
}

}  // extern "C"
