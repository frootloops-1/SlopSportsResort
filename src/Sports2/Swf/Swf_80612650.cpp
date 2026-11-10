// Swf_80612650: Resort Swordplay unit 0x80612650-0x80612A24 (Resort-only, no Wii Sports twin).
// countdown layout from the WS2_game_swf archive (vtable 0x806ED248).
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// @vt-begin
struct Unk_Vt30 {
    u8 pad[0x30];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6C();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7C();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8C();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9C();
    virtual void vA0();
    virtual void vA4();
    virtual void vA8();
    virtual void vAC();
    virtual void vB0();
    virtual void vB4();
    virtual void vB8();
    virtual void vBC();
    virtual void vC0();
    virtual void vC4();
    virtual void vC8();
    virtual void vCC();
    virtual void vD0();
    virtual void vD4();
    virtual void vD8();
    virtual void vDC();
    virtual void vE0();
    virtual void vE4();
    virtual void vE8();
    virtual void vEC();
    virtual void vF0();
    virtual void vF4();
    virtual void vF8();
    virtual void vFC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
};
// @vt-end

extern "C" {

void fn_802B73BC(s32);
void* fn_8026F6AC(u8*, s32);
BOOL fn_8025EAF8(void*);
void fn_8025EC94(void*);
void fn_8025ED28(void*);
void fn_8025EBE8(void*, f32);
f32 fn_8025EA78(void*);
BOOL fn_8025EA80(void*, f32);
void fn_8026FEF0(u8*, s32, s32);
void fn_802703A8(u8*, u8*, u8*, s32, s32, s32);
void fn_8027035C(u8*, s32, u8*, u8*, s32);
void fn_803715C0(u8*, s32, s32);
void fn_8061265C(u8*, s32);
extern u8 lbl_8068AD88[];
extern u8 lbl_806ED248[];

u8* fn_80612950(u8* p) {
    fn_803715C0(p, 2, 0);
    *(u8**)(p + 0x30) = lbl_806ED248;
    *(u8**)(p + 0x18) = lbl_806ED248 + 0x8;
    *(u8**)(p + 0x94) = lbl_806ED248 + 0x78;
    *(u8**)(p + 0x98) = lbl_806ED248 + 0x88;
    return p;
}

void fn_806128D4(u8* p) {
    fn_802703A8(p + 0x94, lbl_8068AD88, lbl_8068AD88 + 0xd, 1, 0, 0);
    fn_8027035C(p + 0x94, 0, lbl_8068AD88 + 0x21, lbl_8068AD88 + 0x27, 0);
    fn_8027035C(p + 0x94, 1, lbl_8068AD88 + 0x32, lbl_8068AD88 + 0x36, 0);
}

void fn_80612850(u8* p) {
    fn_8026FEF0(p + 0x94, 0, 0);
    fn_8025EC94(fn_8026F6AC(p + 0x94, 0));
    fn_8026FEF0(p + 0x94, 1, 0);
    fn_8025ED28(fn_8026F6AC(p + 0x94, 1));
    p[0x110] = 0;
    ((Unk_Vt30*)(p))->v11C();
}

void fn_80612728(u8* p) {
    if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 0)) || fn_8025EAF8(fn_8026F6AC(p + 0x94, 1))) {
        ((Unk_Vt30*)(p))->v4C();
    }
    for (s32 i = 0; i <= 10; i++) {
        s32 n = 10 - i;
        f32 t = 60.0f * i + 60.0f;
        if (fn_8025EA80(fn_8026F6AC(p + 0x94, 0), t)) {
            fn_8061265C(p, n);
        }
    }
    if (fn_8025EA80(fn_8026F6AC(p + 0x94, 0), 640.0f)) {
        p[0x110] = 1;
    }
}

void fn_806126D4(u8* p) {
    if (0.0f == fn_8025EA78(fn_8026F6AC(p + 0x94, 1))) {
        fn_8025EC94(fn_8026F6AC(p + 0x94, 1));
    }
}

void fn_80612698(u8* p, f32 f) {
    fn_8025EBE8(fn_8026F6AC(p + 0x94, 0), f);
}

void fn_8061265C(u8*, s32 n) {
    switch (n) {
    case 10:
        fn_802B73BC(0x29f);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        fn_802B73BC(0x2a0);
        break;
    case 1:
    case 2:
    case 3:
        fn_802B73BC(0x2a1);
        break;
    }
}

f32 fn_80612650(f32 f) { return 640.0f / f; }

}  // extern "C"
