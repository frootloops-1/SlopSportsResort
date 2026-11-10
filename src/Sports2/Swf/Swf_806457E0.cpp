// Swf_806457E0: Resort Swordplay unit 0x806457E0-0x806464DC (Resort-only, no Wii Sports twin).
// layout draw manager (LayoutDrawMgr string, state-machine template copies).
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>

struct Unk_VtAt30_48 {
    u8 pad[0x30];
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
    virtual void vf();
};

struct Unk_VtAt30_F4 {
    u8 pad[0x30];
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
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void vf();
};
struct Unk_VtAt30_4C { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void vf(); };
struct Unk_VtAt30_F8 { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void vf(); };
struct Unk_VtAt30_48_r { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual int vf(); };

extern "C" {

void fn_80645FE0(u8*, int);
void fn_806463EC(u8*, int);
void fn_8064CF28(u8*);
void fn_8064D440(u8*);
void fn_8064E568(u8*);
void fn_8064E1B8(u8*, u32);
void fn_8064E160(u8*, u32);
void fn_8064E0EC(u8*, u32);
void fn_802B73BC(s32);
void fn_8064CC58(u8*);
void fn_8064D2BC(u8*, u32);

void fn_806464D4(u8* p, int a) {
    fn_806463EC(p - 0x18, a);
}

void fn_806464CC(u8* p, int a) {
    fn_80645FE0(p - 0x18, a);
}

u8* fn_806460E4(u8* p) {
    return p + 0x64;
}

u8* fn_806460DC(u8* p) {
    return p + 0x64;
}

// Deleting destructor of a class without a base destructor.
void* fn_80646048(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80645C18(u8* p, u32 a, u32 b) {
    *(u32*)(p + 0x94) = a;
    *(u32*)(p + 0x98) = b;
}

void fn_80645C04(u8* p) {
    (*(Unk_VtAt30_F4**)(p + 0x9c))->vf();
}

void fn_80645BD4(u8* p, BOOL a) {
    if (a) {
        (*(Unk_VtAt30_4C**)(p + 0x9c))->vf();
    } else {
        (*(Unk_VtAt30_F8**)(p + 0x9c))->vf();
    }
}

void fn_80645BC8(u8* p, u32 a) {
    *(u32*)(*(u8**)(p + 0x9c) + 0x110) = a;
}

u8 fn_80645BBC(u8* p) {
    return (*(u8**)(p + 0x9c))[0xd0];
}

void fn_80645BA8(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0x9c))->vf();
}

void fn_80645B50(u8* p) {
    if ((*(Unk_VtAt30_48_r**)(p + 0xa0))->vf()) {
        (*(Unk_VtAt30_F4**)(p + 0xa0))->vf();
    }
}

void fn_80645A8C(u8* p, u32 a, u8 b) {
    fn_8064D2BC(*(u8**)(p + 0xa0), a);
    (*(u8**)(p + 0xa0))[0x110] = b;
}

void fn_80645A84(u8* p) {
    fn_8064D440(*(u8**)(p + 0xa0));
}

void fn_80645A7C(u8* p) {
    fn_8064CF28(*(u8**)(p + 0xa0));
}

void fn_80645A10(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xa0))->vf();
}

void fn_806459FC(u8* p) {
    (*(Unk_VtAt30_F4**)(p + 0xa4))->vf();
}

void fn_806459CC(u8* p, BOOL a) {
    if (a) {
        (*(Unk_VtAt30_4C**)(p + 0xa4))->vf();
    } else {
        (*(Unk_VtAt30_F8**)(p + 0xa4))->vf();
    }
}

void fn_806459AC(u8* p, int a) {
    u8* o = *(u8**)(p + 0xa4);
    o[0x110] = a;
    if ((u8)a > 3) {
        o[0x110] = 0;
    }
}

u8 fn_806459A0(u8* p) {
    return (*(u8**)(p + 0xa4))[0xd0];
}

void fn_8064598C(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xa4))->vf();
}

void fn_80645948(u8* p) {
    fn_8064CC58(*(u8**)(p + 0xa8));
    (*(Unk_VtAt30_F4**)(p + 0xa8))->vf();
}

void fn_80645934(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xa8))->vf();
}

void fn_80645918(u8* p, u32 a) {
    *(u32*)(*(u8**)(p + 0xac) + 0x114) = a;
    (*(Unk_VtAt30_F4**)(p + 0xac))->vf();
}

void fn_80645904(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xac))->vf();
}

void fn_806458AC(u8* p) {
    (*(Unk_VtAt30_F4**)(p + 0xb0))->vf();
    (*(Unk_VtAt30_F4**)(p + 0xb4))->vf();
    fn_802B73BC(0xce);
}

void fn_8064585C(u8* p) {
    (*(Unk_VtAt30_F8**)(p + 0xb4))->vf();
    (*(Unk_VtAt30_F8**)(p + 0xb0))->vf();
}

u8 fn_80645850(u8* p) {
    return (*(u8**)(p + 0xb0))[0xd0];
}

void fn_8064583C(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xb0))->vf();
}

void fn_806457E0(u8* p, u32, u32 a, u32 b) {
    fn_8064E568(*(u8**)(p + 0xb4));
    fn_8064E1B8(*(u8**)(p + 0xb0), a);
    fn_8064E160(*(u8**)(p + 0xb0), b);
    fn_8064E0EC(*(u8**)(p + 0xb0), *(u32*)(p + 0x98));
}

}  // extern "C"
