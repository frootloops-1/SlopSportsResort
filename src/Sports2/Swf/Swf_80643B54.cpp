// Swf_80643B54: Resort Swordplay unit 0x80643B54-0x80643ED4 (Resort-only, no Wii Sports twin).
// compat model (コンパチモデル).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
struct Unk_Mtx34 { f32 m[3][4]; };
#include "Pack/RPGraphics/RPGrpModel.h"

extern "C" {

extern u8 lbl_806EE8A4[];
void fn_8024DC78(u8*, BOOL);
void fn_8036C30C(u8*);

u8* fn_80643EC8() {
    return lbl_806EE8A4;
}

// Deleting destructor of a class without a base destructor.
void* fn_80643E88(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80643C14(u8* p, const char* name, u8 v) {
    u8* m = (u8*)(*(RPGrpModel**)(p + 0x8))->GetMaterial(name);
    m[0x41] = v;
    m[0x40] = 1;
    *(u16*)m |= 8;
}

void fn_80643BE8(u8* p, const Unk_Mtx34* m) {
    *(Unk_Mtx34*)(*(u8**)(p + 0xc) + 0x24) = *m;
}

u8* fn_80643BDC(u8* p) {
    return *(u8**)(p + 0xc) + 0x24;
}

void fn_80643B84(u8* p, BOOL a) {
    if (a) {
        (*(RPGrpModel**)(p + 0x8))->Unk_801E5D00((nw4r::math::MTX34*)(*(u8**)(p + 0xc) + 0x24));
        (*(RPGrpModel**)(p + 0x8))->Calc();
        (*(RPGrpModel**)(p + 0x8))->Entry();
    }
    fn_8036C30C(*(u8**)(p + 0xc));
}

void fn_80643B54(u8* p, u32 a) {
    fn_8024DC78(*(u8**)(p + 0x8), a != 0);
}

}  // extern "C"
