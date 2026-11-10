// Ddg_805D483C: Resort Frisbee Dog unit 0x805D483C-0x805D51B8 (Resort-only, no Wii Sports twin).
// avatar animations WS2_fld_ava_throw*/waitA_* (vtable 0x806EA4D0).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

extern "C" {

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
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6C();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8C();
};
extern u32 lbl_80689730[];

// Deleting destructor of a class without a base destructor.
void* fn_805D5178(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805D5170() { return 3; }

void fn_805D4F94(u8* p) { ((Unk_VtAt0*)(p))->vf8C(); }

void fn_805D4F40() {}

u32 fn_805D4F34(u8* p) { return *(u32*)(*(u8**)(p + 0x164) + 0x40); }

u32 fn_805D4F20(u8*, s32 i) { return lbl_80689730[i]; }

void fn_805D494C(u8* p) { *(u32*)(p + 0x158) = 1; }

}  // extern "C"
