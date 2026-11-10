// Swf_80642EB8: Resort Swordplay unit 0x80642EB8-0x80643A54 (Resort-only, no Wii Sports twin).
// player shadow and shadow manager (プレイヤー影, プレイヤー影マネージャ).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

struct Unk_SwfFlags6C {
    u16 pad : 11;
    u16 b4 : 1;
    u16 low : 4;
};
struct Unk_VtAt0_10 { virtual void v0(); virtual void v1(); virtual void vf(); };

extern "C" {

extern u8 lbl_806EE808[];
extern u8 lbl_806EE820[];
void fn_802ABF88(u8*);
void fn_8064321C(u8*);
void fn_8032349C(u8*);
extern void* lbl_806EE7F4[];

u8* fn_80643A48() {
    return lbl_806EE808;
}

u8* fn_80643A3C() {
    return lbl_806EE820;
}

// Deleting destructor of a class without a base destructor.
void* fn_806439FC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806439B4(u8* p) {
    fn_8032349C(p);
    *(void**)p = lbl_806EE7F4;
    *(u32*)(p + 0x8) = 0;
    *(u32*)(p + 0x18) = 0;
    return p;
}

void fn_806436A0(u8* p) {
    *(u32*)(p + 0x8) = 0;
    (*(Unk_VtAt0_10**)(p + 0xc))->vf();
    ((Unk_SwfFlags6C*)(*(u8**)(p + 0xc) + 0x6c))->b4 = 0;
}

// Deleting destructor of a class without a base destructor.
void* fn_806431DC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80642EB8(u8* p) {
    fn_802ABF88(p);
    for (u8* q = p + 0x48; q != NULL; q = *(u8**)(q + 0x30)) {
        fn_8064321C(q);
    }
}

}  // extern "C"
