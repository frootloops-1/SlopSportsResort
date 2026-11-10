// Swf_805FAEB0: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
struct Unk_VtAt0 {
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
};

extern "C" {


extern u8 lbl_806EBBAC[];

f32 fn_805FB194() { return 1.0f; }

u8* fn_805FB188() { return lbl_806EBBAC; }

void* fn_805FB148(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805FB0E8() {}

void fn_805FB0D8(Unk_VtAt0* p) { p->vf14(); }

void fn_805FB0D4() {}

void fn_805FB050() {}

void fn_805FAF04() {}

void fn_805FAF00() {}

s32 fn_805FAED8() { return 0x0; }

void fn_805FAEC8(Unk_VtAt0* p) { p->vf28(); }

s32 fn_805FAEC0() { return 0x0; }

void fn_805FAEB0(Unk_VtAt0* p) { p->vf30(); }


// ---- hand-written (first pass) ----
extern void* lbl_806EBB58[];
void fn_8032349C(u8*);
void __ct__Q34nw4r4math4VEC3Fv(u8*);

u8* fn_805FB0EC(u8* p, u8* a) {
    fn_8032349C(p);
    *(void***)p = lbl_806EBB58;
    __ct__Q34nw4r4math4VEC3Fv(p + 0x18);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x24);
    __ct__Q34nw4r4math4VEC3Fv(p + 0x30);
    *(u8**)(p + 0x8) = a;
    return p;
}

}  // extern "C"
