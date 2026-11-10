// Swf_80638D40: Resort Swordplay unit 0x80638D40-0x806394F8 (Resort-only, no Wii Sports twin).
// dynamic Mii object (動的Miiオブジェクト) and dynamic Mii generator (動的Mii生成機).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
struct Unk_VtAt0_8_p { virtual void vf(u8*); };

extern "C" {

void* fn_8063949C(void*, int);
void fn_80638FE0(u8*, int);
extern u8 lbl_806EE45C[];
extern u8 lbl_806EE4A0[];
void fn_8024BCC0(u8*, u8*);

void fn_806394F0(u8* p, int a) {
    fn_80638FE0(p - 0x8, a);
}

void* fn_806394E8(u8* p, int del) {
    return fn_8063949C(p - 0x8, del);
}

u8* fn_806394DC() {
    return lbl_806EE4A0;
}

// Deleting destructor of a class without a base destructor.
void* fn_8063949C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80638FD4() {
    return lbl_806EE45C;
}

void fn_80638DBC(u8* p) {
    *(u32*)(p + 0x14) |= 2;
}

BOOL fn_80638D94(u8* p) {
    if (*(s32*)(p + 0x10) != 2) {
        return FALSE;
    }
    return !(*(u32*)(p + 0x14) & 2);
}

void fn_80638D64(u8* p) {
    Unk_VtAt0_8_p* o = *(Unk_VtAt0_8_p**)(p + 0x1c);
    *(s32*)(p + 0x10) = 2;
    if (o != NULL) {
        o->vf(p);
    }
}

void fn_80638D54(u8* p) {
    fn_8024BCC0(*(u8**)(p + 0x8) + 0x8, p + 0x18);
}

BOOL fn_80638D40(u8* p) {
    return *(s32*)(p + 0x138) != 10;
}

}  // extern "C"
