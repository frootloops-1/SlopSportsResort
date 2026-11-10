// Swf_805F1F8C: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

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
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
};

extern "C" {


extern u8 lbl_806EB980[];

f32 fn_805F21C4() { return 0.0f; }

u8* fn_805F21B8() { return lbl_806EB980; }

void* fn_805F2178(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805F2038() {}

void fn_805F2028(Unk_VtAt0* p) { p->vf3C(); }

void fn_805F2024() {}

void fn_805F2014(Unk_VtAt0* p) { p->vf40(); }

void fn_805F2010() {}

void fn_805F2000(Unk_VtAt0* p) { p->vf44(); }

void fn_805F1FFC() {}

void fn_805F1FEC(Unk_VtAt0* p) { p->vf48(); }

f32 fn_805F1F8C() { return 43.0f; }

}  // extern "C"
