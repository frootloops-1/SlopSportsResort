// Swf_80650440: Resort Swordplay unit 0x80650440-0x8065137C (Resort-only, no Wii Sports twin).
// Speed Slice layout manager (LayoutDrawMgr string, state-machine template copies).
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

struct Unk_VtAt30_F8 {
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
    virtual void v59();
    virtual void vf();
};
struct Unk_VtAt30_4C { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void vf(); };

extern "C" {

void fn_80650E80(u8*, int);
void fn_80651308(u8*, int);
void fn_806517AC(u8*);
void fn_8065235C(u8*);
void fn_806524D4(u8*);
void fn_80651DC4(u8*, s32, u8);
void fn_80651E60(u8*, u32, s32);
void fn_80651B50(u8*, const f32*);

void fn_80651374(u8* p, int a) {
    fn_80651308(p - 0x18, a);
}

void fn_8065136C(u8* p, int a) {
    fn_80650E80(p - 0x18, a);
}

u8* fn_80650F84(u8* p) {
    return p + 0x64;
}

u8* fn_80650F7C(u8* p) {
    return p + 0x64;
}

// Deleting destructor of a class without a base destructor.
void* fn_80650EE8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_806509A4(u8* p, u32 a, u32 b, s32 i) {
    ((u32*)(p + 0x94))[i] = a;
    ((u32*)(p + 0x9c))[i] = b;
}

void fn_8065081C(u8* p, BOOL a) {
    if (a) {
        (*(Unk_VtAt30_4C**)(p + 0xa4))->vf();
    } else {
        (*(Unk_VtAt30_F8**)(p + 0xa4))->vf();
    }
}

void fn_80650808(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xa4))->vf();
}

void fn_80650800(u8* p) {
    fn_806517AC(*(u8**)(p + 0xa4));
}

void fn_806507A8(u8* p, s32 i, const f32* v) {
    fn_80651B50(((u8**)(p + 0xa8))[i], v);
    *(s32*)(((u8**)(p + 0xa8))[i] + 0x118) = i;
    ((Unk_VtAt30_F4**)(p + 0xa8))[i]->vf();
}

void fn_8065078C(u8* p, s32 i) {
    ((Unk_VtAt30_F8**)(p + 0xa8))[i]->vf();
}

void fn_80650770(u8* p, s32 i) {
    ((Unk_VtAt30_48**)(p + 0xa8))[i]->vf();
}

void fn_80650714(u8* p) {
    fn_80651E60(*(u8**)(p + 0xb0), *(u32*)(p + 0x9c), 0);
    fn_80651E60(*(u8**)(p + 0xb0), *(u32*)(p + 0xa0), 1);
    (*(Unk_VtAt30_F4**)(p + 0xb0))->vf();
}

void fn_80650700(u8* p) {
    (*(Unk_VtAt30_F8**)(p + 0xb0))->vf();
}

void fn_806506B4(u8* p, u8 a, u8 b) {
    fn_80651DC4(*(u8**)(p + 0xb0), 0, a);
    fn_80651DC4(*(u8**)(p + 0xb0), 1, b);
}

u8 fn_806506A8(u8* p) {
    return (*(u8**)(p + 0xb0))[0xd0];
}

void fn_80650694(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xb0))->vf();
}

void fn_80650618(u8* p, s32 i) {
    ((Unk_VtAt30_48**)(p + 0xb4))[i]->vf();
}

void fn_806505A0(u8* p) {
    *(u8*)(p + 0xc8) = 1;
}

void fn_8065058C(u8* p) {
    (*(Unk_VtAt30_48**)(p + 0xc4))->vf();
}

void fn_806504CC(u8* p) {
    (*(Unk_VtAt30_F4**)(p + 0xbc))->vf();
}

void fn_80650448(u8* p) {
    fn_806524D4(*(u8**)(p + 0xc0));
}

void fn_80650440(u8* p) {
    fn_8065235C(*(u8**)(p + 0xc0));
}

}  // extern "C"
