// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVObjAt38 { u8 _00[0x38]; virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C(); virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C(); virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C(); virtual void vf50(); virtual void* vf54(); virtual void* vf58(); };
struct UnkVec3f { f32 x, y, z; };
void fn_80357194(void* p, void* state);
BOOL fn_803571BC(void* p, void* state);
void fn_804FD2D4(void* a, int b, int c, void* d);
void fn_8050F430(void* p, int a, int b);
void fn_8050F3A8(void* p, int a, int b);
void fn_8050F214(void* p, int a, int b);
void fn_8050F640(void* p, int a);
UnkVObjAt38* fn_80504C60();
BOOL fn_80532938(void* p, void* a);
void fn_80532D84(void* p, void* a);
void fn_8051C0F4(void* p, void* a);
void fn_8052AF7C(void* p);
BOOL fn_8052536C(void* p, void* a);
void fn_8051DAE8(void* p);
BOOL fn_8052DCE8(void* p);
void* fn_80512944(void* p);
void fn_8051E2D0(void* p, void* a, void* b, BOOL c);
void fn_80546880(void* p, void* a);
BOOL fn_8051B20C(void* p, void* a, BOOL b);
void fn_8051B6E4(void* p);
void fn_8051B774(void* p);
void fn_80519DBC(void* p, void* a);
void fn_805269D0(void* p);
BOOL fn_8051A098(void* p);
BOOL fn_8050BB68(void* p);
void fn_80512B20(void* p);
void fn_80512A30(void* p);
extern u8* lbl_806F5AC0;

void fn_80515010() {}

// Deleting destructor of a class without a base destructor.
void* fn_805142B4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_805141C0() {}

void fn_805141BC() {}

void fn_80513F30(u8* p) {
    fn_80512B20(p);
    fn_80512A30(p);
}

void fn_80513E50(u8* p, const UnkVec3f* v) {
    p[0x28C] = 1;
    *(UnkVec3f*)(p + 0x2A8) = *v;
}

void fn_80513E2C(u8* p, const UnkVec3f* v) {
    p[0x2B4] = 1;
    *(UnkVec3f*)(p + 0x2B8) = *v;
}

BOOL fn_80513DDC(u8* p) {
    if (!fn_803571BC(p, p + 0x3C)) {
        fn_80357194(p, p + 0x3C);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80513CE0(u8* p) {
    if (*(void**)(p + 0x25C) != NULL && !fn_803571BC(p, p + 0x144)) {
        fn_80357194(p, p + 0x144);
        return TRUE;
    }
    return FALSE;
}

int fn_80513C94(u8* p) {
    fn_804FD2D4(*(void**)(p + 0x254), 0, 0, NULL);
    fn_80357194(p, p + 0x3C);
    return 1;
}

BOOL fn_80513C44(u8* p) {
    if (!fn_803571BC(p, p + 0x1C8)) {
        fn_80357194(p, p + 0x19C);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80513BE4(u8* p) {
    if (fn_803571BC(p, p + 0xC0) && fn_8051A098(*(void**)(p + 0x264))) {
        fn_80357194(p, p + 0xEC);
        return TRUE;
    }
    return FALSE;
}

int fn_80513B08(u8* p, u8 b, const UnkVec3f* v) {
    (*(u8**)(p + 0x27C))[0x1C] = b;
    *(UnkVec3f*)(*(u8**)(p + 0x27C) + 0x20) = *v;
    fn_80357194(p, p + 0x68);
    return 1;
}

int fn_80513AAC(u8* p, void* a, u32 b) {
    *(void**)(p + 0x258) = a;
    (*(u8**)(p + 0x280))[0x1C] = fn_8050BB68(*(void**)(*(u8**)(p + 0x254) + 0x158));
    *(u32*)(*(u8**)(p + 0x280) + 0x18) = b;
    fn_80357194(p, p + 0x1C8);
    return 1;
}

BOOL fn_80513A5C(u8* p) {
    if (fn_803571BC(p, p + 0x3C)) {
        fn_80357194(p, p + 0x1F4);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80513A0C(u8* p) {
    if (!fn_803571BC(p, p + 0x220)) {
        fn_80357194(p, p + 0x220);
        return TRUE;
    }
    return FALSE;
}

void fn_80513A04(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x3c); }

void fn_805139FC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x94); }

void fn_805139F4(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0xc0); }

void fn_805139EC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0xec); }

void fn_805139E4(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x118); }

void fn_805139DC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x144); }

void fn_805139D4(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x170); }

void fn_805139CC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x1f4); }

void fn_805139C4(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x19c); }

void fn_805139BC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x220); }

BOOL fn_80513968(u8* p) {
    if (fn_803571BC(p, p + 0x170) && *(u32*)(*(u8**)(p + 0x278) + 0x34) <= 2) {
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80513914(u8* p) {
    if (fn_803571BC(p, p + 0x1C8) && *(s32*)(*(u8**)(p + 0x280) + 0x18) == 1) {
        return TRUE;
    }
    return FALSE;
}

void fn_80513908(u8* p) { *(u32*)(p + 0x258) = 0; }

void fn_80513904() {}

void fn_805138AC(u8* p) {
    fn_805269D0(*(void**)(p + 0x27C));
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_805137E8(u8* p) {
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_805137E4() {}

void fn_805137E0() {}

void fn_80513790(u8* p) {
    fn_8051B774(*(void**)(p + 0x268));
    fn_804FD2D4(*(void**)(p + 0x254), 1, 0, *(void**)(p + 0x25C));
    fn_80519DBC(*(void**)(p + 0x264), *(void**)(p + 0x25C));
}

void fn_80513720(u8* p) {
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    *(s32*)(p + 0x288) = -1;
    *(f32*)(p + 0x290) = 0.0f;
}

void fn_805136C8(u8* p) {
    fn_8051B6E4(*(void**)(p + 0x268));
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 1, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 1, 0);
}

void fn_80513670(u8* p) {
    if (fn_8051B20C(*(void**)(p + 0x268), *(void**)(p + 0x25C), *(u32*)(lbl_806F5AC0 + 0x3C) == 0)) {
        fn_80357194(p, p + 0x3C);
    }
}

void fn_80513620(u8* p) {
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_805135D8(u8* p) {
    fn_804FD2D4(*(void**)(p + 0x254), 1, 0, *(void**)(p + 0x25C));
    fn_80546880(*(void**)(p + 0x26C), *(void**)(p + 0x25C));
}

void fn_805134FC(u8* p) {
    *(u32*)(p + 0x24C) = 0;
    BOOL b = fn_8052DCE8(*(void**)(*(u8**)(p + 0x254) + 0x150));
    fn_8051E2D0(*(void**)(p + 0x274), *(void**)(p + 0x25C), fn_80512944(p), b);
}

void fn_805132FC(u8* p) {
    fn_8051DAE8(*(void**)(p + 0x274));
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_805131D0(u8* p) {
    if (fn_8052536C(*(void**)(p + 0x278), *(void**)(p + 0x25C))) {
        fn_80357194(p, p + 0x3C);
    }
}

void fn_80513180(u8* p) {
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_80513170(u8* p) {
    *(u32*)(p + 0x24C) = 0;
    fn_8052AF7C(*(void**)(p + 0x280));
}

void fn_80512FC8(u8* p) {
    fn_8050F214(*(void**)(*(u8**)(p + 0x254) + 0x164), 1, 0);
    fn_8050F640(*(void**)(*(u8**)(p + 0x254) + 0x164), 1);
    *(s32*)(p + 0x288) = -1;
    *(f32*)(p + 0x290) = 0.0f;
}

void fn_80512F10(u8* p) { fn_8051C0F4(*(void**)(p + 0x270), fn_80504C60()->vf54()); }

void fn_80512EC0(u8* p) {
    fn_8050F430(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
    fn_8050F3A8(*(void**)(*(u8**)(p + 0x254) + 0x164), 0, 0);
}

void fn_80512E78(u8* p) { fn_80532D84(*(void**)(p + 0x284), fn_80504C60()->vf58()); }

void fn_80512E1C(u8* p) {
    if (fn_80532938(*(void**)(p + 0x284), fn_80504C60()->vf58())) {
        fn_80357194(p, p + 0x94);
    }
}

void fn_80512E18() {}

void fn_80512DC4(u8* p) {
    fn_804FD2D4(*(void**)(p + 0x254), 0, 0, *(void**)(p + 0x25C));
    *(s32*)(p + 0x288) = -1;
    *(f32*)(p + 0x290) = 0.0f;
    *(u32*)(p + 0x258) = 0;
}

void fn_80512DC0() {}

} // extern "C"
