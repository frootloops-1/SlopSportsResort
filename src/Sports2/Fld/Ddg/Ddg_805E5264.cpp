// Ddg_805E5264: Resort Frisbee Dog unit 0x805E5264-0x805E60CC (Resort-only, no Wii Sports twin).
// disk model: WS2_fld_disk.brres (vtable 0x806EABB8).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
};

void PSMTXIdentity(u8*);

void fn_802ABB5C(u8*, s32);

// Deleting destructor of a class without a base destructor.
void* fn_805E6068(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805E6054(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x2c)))->vf8(); }

s32 fn_805E604C() { return 1; }

s32 fn_805E6044() { return 1; }

u8* fn_805E6008(u8* p) {
    *(u32*)(p) = 0;
    PSMTXIdentity(p + 0x4);
    return p;
}

u8* fn_805E5FC4(u8* p) {
    *(void**)p = operator new(0x4);
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    return p;
}

void fn_805E5F14(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

u8* fn_805E5EF8(u8* p) {
    u8* h = *(u8**)(p + 0x1c);
    if (h != NULL) {
        *(u8**)(p + 0x1c) = *(u8**)(h + 0x4);
    }
    return h;
}

void fn_805E5EEC(u8* p, u32 a1) { *(u32*)(*(u8**)(p)) = a1; }

void fn_805E5EC8(u8* list, u8* node) {
    *(u8**)(node + 0x4) = *(u8**)(list + 0x4);
    *(u8**)(node + 0x8) = list;
    if (*(u8**)(list + 0x4) != NULL) {
        *(u8**)(*(u8**)(list + 0x4) + 0x8) = node;
    }
    *(u8**)(list + 0x4) = node;
}

void fn_805E586C() {}

void fn_805E5868() {}

void fn_805E57B4(u8* p) {
    u8* e = *(u8**)(p + 0x4);
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x20) = 0;
    *(u8**)(p + 0x1c) = e;
    for (; e + 0xc < *(u8**)(p + 0x8); e += 0xc) {
        *(u8**)(e + 0x4) = e + 0xc;
    }
    *(u32*)(e + 0x4) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
}

void fn_805E571C(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

u32 fn_805E5670(u8* p) { return *(u32*)(p + 0x4); }

u32 fn_805E5664(u8* p) { return *(u32*)(*(u8**)(p)); }

void fn_805E5390(u8* p) {
    if (*(u8*)(p + 0xd8) != 0) {
        fn_802ABB5C(*(u8**)(p + 0x100), 1);
    }
}

}  // extern "C"
