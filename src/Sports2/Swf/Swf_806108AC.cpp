// Swf_806108AC: Resort Swordplay unit 0x806108AC-0x80611D44 (Resort-only, no Wii Sports twin).
// result layout (N_1Pwin/N_2Pwin/N_draw, P_*mii panes); MI layout class with a state machine at +0x64.
// State-machine template copies left out: 0x806114AC, 0x80611550, 0x80611A04, 0x80611B24, 0x80611B80,
// 0x80611BE4, 0x80611C44, 0x80611CA4.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// @vt-begin
struct Unk_Vt0 {
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
};

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
    virtual BOOL v48();
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
    virtual u8* v100();
};
// @vt-end

extern "C" {

void fn_8027CB94(void*, u32);
void* fn_8026F970(u8*, void*);
void fn_8027CC74(void*, void*);
BOOL fn_80345718(u8*, s32);
void* fn_8026F6AC(u8*, s32);
BOOL fn_8025EAF8(void*);
void fn_8025EC94(void*);
void fn_803457B8(u8*, s32);
void fn_8026FEF0(u8*, s32, s32);
void fn_80610D2C(u8*);
void fn_80611B80(u8*);
BOOL fn_8026FF08(u8*);
void fn_802777A8(u8*);
void fn_80277808(u8*);
void fn_802700EC(u8*);
void fn_802A609C(u8*);
void fn_8027765C(u8*, s32, s32);
void fn_802704F8(u8*);
void fn_80277768(u8*);
void fn_8026FFE0(u8*);
void fn_802B73BC(s32);
extern void* lbl_806EC888[];

void fn_80611A00() {}

void fn_806119B0(u8* p) {
    fn_8027765C(p + 0x94, *(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    fn_803457B8(p + 0x64, *(s32*)(p + 0xfc) + 3);
}

void fn_80611954(u8* p) {
    fn_8027765C(p + 0x94, ((Unk_Vt30*)(p))->v48(), 0);
    fn_80277768(p + 0x94);
    fn_803457B8(p + 0x64, *(s32*)(p + 0xfc));
}

void fn_80611768(u8* p) {
    fn_8027765C(p + 0x94, *(p + 0xd1), 2);
    fn_802704F8(p + 0x94);
    fn_803457B8(((Unk_Vt30*)(p))->v100(), *(s32*)(p + 0xfc) + 1);
    ((Unk_Vt0*)(p + 0x94))->v6C();
}

void fn_80611730(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_806116E8(u8* p) {
    if (((Unk_Vt30*)(p))->v48() == 0) {
        fn_80277808(p + 0x94);
    }
}

void fn_806116A0(u8* p) {
    if (((Unk_Vt30*)(p))->v48() == 0) {
        fn_802777A8(p + 0x94);
    }
}

void fn_80611640(u8* p) {
    if (fn_8026FF08(p + 0x94)) {
        ((Unk_Vt30*)(p))->v4C();
        ((Unk_Vt0*)(p + 0x94))->v70();
    }
}

u8* fn_80611638(u8* p) { return p + 0x64; }

u8* fn_80611630(u8* p) { return p + 0x64; }

void fn_806115DC(u8* p) {
    ((Unk_Vt30*)(p))->v64();
    fn_80611B80(p + 0x64);
    ((Unk_Vt30*)(p))->v68();
}

u8* fn_806115D4(u8* p) { return p + 0x64; }

u8* fn_806115CC(u8* p) { return p + 0x64; }

void fn_80610C68(u8* p) {
    if (((Unk_Vt30*)(p))->v48()) {
        if (*(s32*)(p + 0x104) == 3 && *(p + 0x112) == 0) {
            fn_8026FEF0(p + 0x94, 1, 0);
            fn_8025EC94(fn_8026F6AC(p + 0x94, 1));
            fn_80610D2C(p);
            fn_803457B8(p + 0x64, 0);
            *(p + 0x112) = 1;
        } else {
            fn_8026FEF0(p + 0x94, 0, 1);
            fn_8025EC94(fn_8026F6AC(p + 0x94, 0));
            fn_803457B8(p + 0x64, 0);
        }
    }
}

void fn_80610BF8(u8* p) {
    if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 0)) || (*(p + 0x112) != 0 && fn_8025EAF8(fn_8026F6AC(p + 0x94, 1)))) {
        fn_803457B8(p + 0x64, 2);
    }
}

void fn_80610B54(u8* p) {
    if (fn_80345718(p + 0x64, 2)) {
        if (*(s32*)(p + 0x104) == 4 && *(p + 0x112) != 0) {
            fn_8026FEF0(p + 0x94, 3, 0);
            fn_8025EC94(fn_8026F6AC(p + 0x94, 3));
        } else {
            fn_8026FEF0(p + 0x94, 2, 0);
            fn_8025EC94(fn_8026F6AC(p + 0x94, 2));
        }
        fn_803457B8(p + 0x64, 1);
    }
}

void fn_80610AB8(u8* p) {
    if (*(s32*)(p + 0x104) == 4 && *(p + 0x112) != 0) {
        if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 3))) {
            ((Unk_Vt30*)(p))->v4C();
        }
    } else {
        if (fn_8025EAF8(fn_8026F6AC(p + 0x94, 2))) {
            ((Unk_Vt30*)(p))->v4C();
        }
    }
}

void fn_80610A20(u8* p) {
    if (*(p + 0x110) != 0) {
        s32 n = *(s32*)(p + 0x104);
        fn_8026FEF0(p + 0x94, n + (n == 3 ? 3 : 0) + 5, 0);
        n = *(s32*)(p + 0x104);
        fn_8025EC94(fn_8026F6AC(p + 0x94, n + (n == 3 ? 3 : 0) + 5));
        fn_803457B8(p + 0x64, 3);
        fn_802B73BC(0x278);
    }
}

void fn_8061097C(u8* p) {
    if (*(p + 0x111) != 0) {
        *(p + 0x111) = 0;
        return;
    }
    s32 n = *(s32*)(p + 0x104);
    if (fn_8025EAF8(fn_8026F6AC(p + 0x94, n + (n == 3 ? 3 : 0) + 5))) {
        if (*(s32*)(p + 0x104) < 4) {
            *(s32*)(p + 0x104) = *(s32*)(p + 0x104) + 1;
        }
        *(p + 0x110) = 0;
        if (*(p + 0x111) == 0) {
            fn_803457B8(p + 0x64, 2);
        }
    }
}

BOOL fn_80610928(u8* p) {
    BOOL ret = FALSE;
    if (fn_80345718(p + 0x64, 2) && *(p + 0x110) == 0) {
        ret = TRUE;
    }
    return ret;
}

void fn_806108AC(u8* p, u32 a, s32 b) {
    for (s32 i = 0; i < 14; i++) {
        s32 idx = i + b * 14;
        fn_8027CB94((*(void***)(p + 0x100))[idx], a);
        fn_8027CC74((*(void***)(p + 0x100))[idx], fn_8026F970(p + 0x94, lbl_806EC888[idx]));
    }
}

}  // extern "C"
