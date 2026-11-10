// Canoeing (Resort-only), .text 0x8049B30C-0x804A3BC0: singleton "FieldMgr" (WS2_can_field, course maps). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>

extern "C" {

u8* fn_802969E0(u8* p, s32 i);
void fn_804A58FC(u8* p);
extern u8* lbl_806F5838; // Config instance
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_804A37AC(u8* p); // ctor
extern void* lbl_806F58A0; // instance
extern void* lbl_806F58A4; // heap
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
};

u8* fn_8026E014(u8*, u32);
u8* fn_8026E0F0(u8*, u32);
u8* fn_8026E104(u8*, u32);
void fn_8028BDF4(u8*);
void fn_80359908(u8*);
void fn_8035A0D8(u8*);
void fn_8049D020(u8*, u8*, u8*, u32, u32, u32, u32);
u8 fn_8049D61C(u8*, u8*, u8*, s32, s32);
void fn_8049DE00(u8*, u32, u32, s32);
void fn_8049F7E4(u8*, u8*, u8*, u8*, u32, u32, f32);
void fn_8049F8C8(u8*, u32, u32, u32, u32, f32);
void fn_804A0954(u8*, u32);
void fn_804A1568(u8*, u8*, s32);
u32 fn_804A15D0(u8*, u32, s32, s32, u32);
void fn_804A1C08(u8*);
u32 fn_804A411C(u8*);
u32 fn_804A4A78(u8*);
u32 fn_804A5680(u8*);
void fn_804A58CC(u8*);
void fn_804A58E4(u8*);
void fn_804A6038(u8*);
void fn_804A64A8(u8*);
void fn_804A6C88(u8*);
void fn_804A6FB8(u8*);
void fn_804A6FD8(u8*);
void fn_804A7018(u8*, u32, u32, s32, u32);
u32 fn_804B9CA0(u8*);
u32 fn_804BA968(u8*);
extern u8* lbl_806F4EB4;
extern u8* lbl_806F4FB0;
extern u8 lbl_806DBF68[];

void fn_804A39DC(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F58A0 == NULL && lbl_806F58A4 == NULL, "FieldMgr");
    lbl_806F58A4 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x44e0, pHeap, 4);
        if (p != NULL) {
            p = fn_804A37AC((u8*)p);
        }
        lbl_806F58A0 = p;
    } else {
        void* p = operator new(0x44e0);
        if (p != NULL) {
            p = fn_804A37AC((u8*)p);
        }
        lbl_806F58A0 = p;
    }
}

void fn_804A39CC() {
    lbl_806F58A0 = NULL;
    lbl_806F58A4 = NULL;
}

// Deleting destructor of a class without a base destructor.
void* fn_804A3948(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804A3944() {}

void fn_804A31DC(u8* p) {
    u8* t0 = fn_8026E014(lbl_806F4EB4, *(u32*)(p + 0x20));
    ((Unk_VtAt0*)(t0))->vf50();
    u8* t2 = fn_8026E014(lbl_806F4EB4, *(u32*)(p + 0x24));
    ((Unk_VtAt0*)(t2))->vf50();
    u8* t4 = fn_8026E104(lbl_806F4EB4, *(u32*)(p + 0x18));
    ((Unk_VtAt0*)(t4))->vf50();
    u8* t6 = fn_8026E0F0(lbl_806F4EB4, *(u32*)(p + 0x1c));
    ((Unk_VtAt0*)(t6))->vf50();
}

void fn_804A3144(u8* p) {
    u8* t0 = fn_8026E014(lbl_806F4EB4, *(u32*)(p + 0x20));
    ((Unk_VtAt0*)(t0))->vf54();
    u8* t2 = fn_8026E014(lbl_806F4EB4, *(u32*)(p + 0x24));
    ((Unk_VtAt0*)(t2))->vf54();
    u8* t4 = fn_8026E104(lbl_806F4EB4, *(u32*)(p + 0x18));
    ((Unk_VtAt0*)(t4))->vf54();
    u8* t6 = fn_8026E0F0(lbl_806F4EB4, *(u32*)(p + 0x1c));
    ((Unk_VtAt0*)(t6))->vf54();
}

void fn_804A2834(u8* p) {
    fn_80359908(*(u8**)(p));
    fn_80359908(*(u8**)(p + 0x4));
    fn_80359908(*(u8**)(p + 0x8));
    fn_80359908(*(u8**)(p + 0xc));
    fn_80359908(*(u8**)(p + 0x10));
}

// Deleting destructor of a class without a base destructor.
void* fn_804A2520(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_804A247C(u8* p) {
    fn_8035A0D8(p);
    *(u8**)(p) = lbl_806DBF68;
    return p;
}

void fn_804A168C(u8* p, u8* a1) {
    u32 t0 = fn_804A411C(a1);
    u32 t1 = fn_804A15D0(p, *(u32*)(p + 0x2940), 156, 200, t0);
    *(u32*)(p + 0x2944) = t1;
    u32 t2 = fn_804A5680(a1);
    u32 t3 = fn_804A15D0(p, *(u32*)(p + 0x29e0), 0x114, 200, t2);
    *(u32*)(p + 0x29e4) = t3;
    u32 t4 = fn_804A4A78(a1);
    u32 t5 = fn_804A15D0(p, *(u32*)(p + 0x2a18), 164, 200, t4);
    *(u32*)(p + 0x2a1c) = t5;
    u32 t6 = fn_804B9CA0(a1);
    u32 t7 = fn_804A15D0(p, *(u32*)(p + 0x2a50), 156, 20, t6);
    *(u32*)(p + 0x2a54) = t7;
    u32 t8 = fn_804BA968(a1);
    u32 t9 = fn_804A15D0(p, *(u32*)(p + 0x2ca0), 228, 20, t8);
    *(u32*)(p + 0x2ca4) = t9;
    fn_804A1568(p + 0x2910, a1, 200);
    fn_804A1568(p + 0x2948, a1, 0x320);
    fn_804A1568(p + 0x2978, a1, 0x320);
    fn_804A1568(p + 0x29b0, a1, 200);
    fn_804A1568(p + 0x29e8, a1, 200);
    fn_804A1568(p + 0x2a20, a1, 20);
    fn_804A1568(p + 0x2b48, a1, 20);
    fn_804A1568(p + 0x2c70, a1, 20);
    fn_804A64A8(a1);
    fn_804A6038(a1);
}

void fn_8049F96C(u8* p, f32 fa1) {
    fn_8049F7E4(p, p + 0x2e98, p + 0x2e9c, p + 0x2ea8, *(u32*)(p + 0x2948), *(u32*)(p + 0x294c), fa1);
    fn_8049F7E4(p, p + 0x2ea0, p + 0x2ea4, p + 0x2eac, *(u32*)(p + 0x2978), *(u32*)(p + 0x297c), fa1);
}

void fn_8049F904(u8* p, u32 a1, u32 a2) {
    fn_8049F8C8(p, *(u32*)(p + 0x2e98), *(u32*)(p + 0x2e9c), *(u32*)(p + 0x2948), a1, *(f32*)(p + 0x2ea8));
    fn_8049F8C8(p, *(u32*)(p + 0x2ea0), *(u32*)(p + 0x2ea4), *(u32*)(p + 0x2978), a2, *(f32*)(p + 0x2eac));
}

u8* fn_8049F0D0(u8* p) { return p + 0x4c; }

u8* fn_8049F0C8(u8* p) { return p + 0x58; }

f32 fn_8049F0C0() { return -1349.050048828125f; }

void fn_8049F0B0(u8* p, u32 a1, u32 a2, u32 a3) { fn_804A7018(*(u8**)(p + 0x9c), a1, a2, 0, a3); }

void fn_8049F0A8(u8* p) { fn_804A6C88(*(u8**)(p + 0x9c)); }

void fn_8049F0A0(u8* p) { fn_804A6FD8(*(u8**)(p + 0x9c)); }

void fn_8049F098(u8* p) { fn_804A6FB8(*(u8**)(p + 0x9c)); }

void fn_8049EA8C() { fn_804A58FC(fn_802969E0(lbl_806F4FB0, *(s32*)(lbl_806F5838 + 0x40) + 1)); }

void fn_8049EA80() { fn_802969E0(lbl_806F4FB0, 0); }

f32 fn_8049EA74(u8* p) { return *(f32*)(*(u8**)(p + 0x9c) + 0x10); }

BOOL fn_8049E7D0(const u8* p, s32 i) { return (*(u8**)(p + 0x14))[i] != 0; }

void fn_8049E274(u8* p) { fn_8028BDF4(*(u8**)(p + 0x28)); }

void fn_8049DE78(u8* p) { ((Unk_VtAt0*)(p))->vf38(); }

void fn_8049DDB0(u8*, u8* a1) {
    fn_8049DE00(a1, *(u32*)(a1 + 0xc), *(u32*)(a1 + 0x8), 0);
    fn_8049DE00(a1, *(u32*)(a1 + 0x10), *(u32*)(a1 + 0x14), 0);
}

void fn_8049DDA8(u8* p, u32 a1) { *(u32*)(p + 0x68) = a1; }

void fn_8049D590(u8*, u8* a1) {
    u8 t0 = fn_8049D61C(a1, a1 + 0x1c, a1 + 0x20, 0, 0);
    *(u8*)(a1 + 0x24) = t0;
}

void fn_8049D290(u8* p) {
    if (p[0x20b0] == 0) {
        *(u32*)(*(u8**)(p + 0x290c) + 0x18) = *(u32*)(p + 0x294c);
    }
    *(u32*)(*(u8**)(p + 0x290c) + 0x28) = *(u32*)(p + 0x297c);
}

void fn_8049D1E8(u8* p) { *(u32*)(*(u8**)(p + 0x290c) + 0x38) = *(u32*)(p + 0x29b4); }

void fn_8049D1CC(u8* p, u32 a1, u32 a2, u32 a3) {
    fn_8049D020(p, p + 0x29b0, *(u8**)(p + 0x290c) + 0x30, a1, a2, a3, *(u32*)(p + 0x290c));
}

void fn_8049D1BC(u8* p) { *(u32*)(*(u8**)(p + 0x290c) + 0x48) = *(u32*)(p + 0x29ec); }

void fn_8049D1A0(u8* p, u32 a1, u32 a2, u32 a3) {
    fn_8049D020(p, p + 0x29e8, *(u8**)(p + 0x290c) + 0x40, a1, a2, a3, *(u32*)(p + 0x290c));
}

void fn_8049D190(u8* p) { *(u32*)(*(u8**)(p + 0x290c) + 0x58) = *(u32*)(p + 0x2a24); }

void fn_8049D174(u8* p, u32 a1, u32 a2, u32 a3) {
    fn_8049D020(p, p + 0x2a20, *(u8**)(p + 0x290c) + 0x50, a1, a2, a3, *(u32*)(p + 0x290c));
}

void fn_8049D164(u8* p) { *(u32*)(*(u8**)(p + 0x290c) + 0x68) = *(u32*)(p + 0x2b4c); }

void fn_8049D148(u8* p, u32 a1, u32 a2, u32 a3) {
    fn_8049D020(p, p + 0x2b48, *(u8**)(p + 0x290c) + 0x60, a1, a2, a3, *(u32*)(p + 0x290c));
}

void fn_8049D138(u8* p) { *(u32*)(*(u8**)(p + 0x290c) + 0x78) = *(u32*)(p + 0x2c74); }

void fn_8049D11C(u8* p, u32 a1, u32 a2, u32 a3) {
    fn_8049D020(p, p + 0x2c70, *(u8**)(p + 0x290c) + 0x70, a1, a2, a3, *(u32*)(p + 0x290c));
}

void fn_8049C984(u32 p, u8* a1) { fn_804A0954(a1, p); }

void fn_8049C980(u8* p) { fn_804A58E4(p); }

void fn_8049C97C(u8* p) { fn_804A58CC(p); }

void fn_8049B6A8(u8* p) {
    fn_804A1C08(p + 0x2910);
    fn_804A1C08(p + 0x2948);
    fn_804A1C08(p + 0x2978);
    fn_804A1C08(p + 0x29b0);
    fn_804A1C08(p + 0x29e8);
    fn_804A1C08(p + 0x2a20);
    fn_804A1C08(p + 0x2b48);
    fn_804A1C08(p + 0x2c70);
}

f32 fn_8049B6A0() { return 1000.0f; }

}  // extern "C"
