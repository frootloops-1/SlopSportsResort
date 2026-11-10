// Swf_8063269C: Resort Swordplay unit 0x8063269C-0x8063348C (Resort-only, no Wii Sports twin).
// 65010_swf_explain layout and its manager (state-machine template copies).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
struct Unk_VtAt30_48_r { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual int vf(); };
struct Unk_VtAt30_4C { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void vf(); };

extern "C" {

void fn_80632B28(u8*, int);
void fn_80632B8C(u8*, int);
void fn_80632C34(u8*, int);
void fn_80632EB0(u8*, int);
void fn_802700EC(u8*);
void fn_802A609C(u8*);
void fn_802777A8(u8*);
void fn_80277808(u8*);
u8* fn_8026F6AC(u8*, s32);
BOOL fn_8025EAF8(u8*);

void fn_80633474(u8* p, int a) {
    fn_80632C34(p - 0x94, a);
}

void fn_8063346C(u8* p, int a) {
    fn_80632EB0(p - 0x94, a);
}

void fn_80633464(u8* p, int a) {
    fn_80632C34(p - 0x18, a);
}

void fn_8063345C(u8* p, int a) {
    fn_80632B28(p - 0x94, a);
}

void fn_80633454(u8* p, int a) {
    fn_80632B28(p - 0x18, a);
}

void fn_8063344C(u8* p, int a) {
    fn_80632B8C(p - 0x18, a);
}

void fn_80633148() {}

void fn_80632E78(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_80632E30(u8* p) {
    if (((Unk_VtAt30_48_r*)p)->vf() == 0) {
        fn_80277808(p + 0x94);
    }
}

void fn_80632DE8(u8* p) {
    if (((Unk_VtAt30_48_r*)p)->vf() == 0) {
        fn_802777A8(p + 0x94);
    }
}

u8* fn_80632D80(u8* p) {
    return p + 0x64;
}

u8* fn_80632D78(u8* p) {
    return p + 0x64;
}

u8* fn_80632D1C(u8* p) {
    return p + 0x64;
}

u8* fn_80632D14(u8* p) {
    return p + 0x64;
}

// Deleting destructor of a class without a base destructor.
void* fn_80632BF4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_806327F0(u8* p) {
    *(u8*)(p + 0x100) = 1;
}

void fn_8063279C(u8* p) {
    if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 1))) {
        ((Unk_VtAt30_4C*)p)->vf();
    }
}

}  // extern "C"
