// RingMgr: Resort Frisbee Dog unit 0x805EDAC0-0x805EF944 (Resort-only, no Wii Sports twin).
// singleton "RingMgr" (create fn_805EF338, instance lbl_806F5F98).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

struct Unk_VtAt0 {
    virtual void vf8();
};

extern void* lbl_806F5F98;
extern void* lbl_806F5F9C;
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_805EEF04(void* p); // ctor

void fn_805EF3E4(u8* p) { ((Unk_VtAt0*)(*(u8**)(p + 0x2c)))->vf8(); }

s32 fn_805EF3DC() { return 1; }

s32 fn_805EF3D4() { return 1; }

void fn_805EF338(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5F98 == NULL && lbl_806F5F9C == NULL, "RingMgr");
    lbl_806F5F9C = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x18C, pHeap, 4);
        if (p != NULL) {
            p = fn_805EEF04(p);
        }
        lbl_806F5F98 = p;
    } else {
        void* p = operator new(0x18C);
        if (p != NULL) {
            p = fn_805EEF04(p);
        }
        lbl_806F5F98 = p;
    }
}

void fn_805EF328() {
    lbl_806F5F98 = NULL;
    lbl_806F5F9C = NULL;
}

u8* fn_805EF2E4(u8* p) {
    *(void**)p = operator new(0x4);
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    return p;
}

void fn_805EF234(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

u8* fn_805EF218(u8* p) {
    u8* h = *(u8**)(p + 0x1c);
    if (h != NULL) {
        *(u8**)(p + 0x1c) = *(u8**)(h + 0x4);
    }
    return h;
}

void fn_805EF20C(u8* p, u32 a1) { *(u32*)(*(u8**)(p)) = a1; }

void fn_805EF1E8(u8* list, u8* node) {
    *(u8**)(node + 0x4) = *(u8**)(list + 0x4);
    *(u8**)(node + 0x8) = list;
    if (*(u8**)(list + 0x4) != NULL) {
        *(u8**)(*(u8**)(list + 0x4) + 0x8) = node;
    }
    *(u8**)(list + 0x4) = node;
}

void fn_805EDE10(u8* p) {
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

void fn_805EDE08(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

u32 fn_805EDC20(u8* p) { return *(u32*)(p + 0x4); }

u32 fn_805EDC14(u8* p) { return *(u32*)(*(u8**)(p)); }

}  // extern "C"
