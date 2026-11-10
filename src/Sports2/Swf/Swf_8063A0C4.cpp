// Swf_8063A0C4: Resort Swordplay unit 0x8063A0C4-0x8063BD58 (Resort-only, no Wii Sports twin).
// Showdown base (組み手ベース); __sinit.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

struct Unk_VtAt0_6C {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void vf();
};
struct Unk_VtAt0_50_i { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void vf(s32); };
struct Unk_VtAt0_68 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void vf(); };
#include <revolution/MTX.h>

extern "C" {

extern u8 lbl_806EE66C[];
void fn_8063A81C(u8*);

u8* fn_8063BD2C() {
    return lbl_806EE66C;
}

void fn_8063B2D0() {}

void fn_8063B2B0(u8* p) {
    *(u32*)(p + 0x94) = *(u32*)(p + 0xcc);
    *(u32*)(p + 0xcc) = 0;
    ((Unk_VtAt0_68*)p)->vf();
}

void fn_8063B2A0(Unk_VtAt0_6C* p) {
    p->vf();
}

void fn_8063B254(u8* p, Vec* out, const Vec* in) {
    Vec t;
    PSVECCrossProduct((Vec*)(p + 0x88), in, &t);
    PSVECCrossProduct(&t, (Vec*)(p + 0x88), out);
}

void fn_8063A93C() {}

void fn_8063A91C(u8* p) {
    *(u32*)(p + 0xc8) &= ~1;
    ((Unk_VtAt0_50_i*)p)->vf(0xc);
}

u32 fn_8063A7EC(u8* p) {
    fn_8063A81C(p);
    return *(u32*)(p + 0x120);
}

}  // extern "C"
