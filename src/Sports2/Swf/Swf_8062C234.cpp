// Swf_8062C234: Resort Swordplay unit 0x8062C234-0x8062CB80 (Resort-only, no Wii Sports twin).
// "薪割りルール" (Speed Slice rules): vtable 0x806EDBA8, name 0x806EDBF8, state table 0x806EDB80.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_PtmfHost {};
typedef void (Unk_PtmfHost::*Unk_StateFn)();

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
};

struct Unk_HeapScope {
    void* heap;
    u32 unk4;
};

extern "C" {

void fn_8062CD7C(void*, s32);
void fn_8062CB2C(u8*);
void fn_8062D020(void*);
void fn_8062D084(void*);
void fn_8062D1AC(void*);
void fn_8060E128(void*, f32);
void* fn_805F37A0();
void* fn_8027B130(void*);
BOOL fn_80292504(void*, s32);
void* fn_802924F0(void*, s32);
void* fn_80653F6C(s32);
void fn_8036A5B4(Unk_HeapScope*, void*);
BOOL fn_804564D8(Unk_HeapScope*);
void becomeCurrentHeap__Q23EGG4HeapFv(void*);
void fn_80643B0C(u8*);
void* fn_8062E7E0(void*);
void forceKill__11RPSysEffectFv(void*);
extern u8* lbl_806F5FF0;
extern Unk_StateFn lbl_806EDB80[];
extern u8 lbl_806EDBA8[];
extern char lbl_806EDBF8[];

void fn_8062CB2C(u8* p) {
    for (s32 i = 0; i < 2; i++) {
        PTR(p + i * 4, 0x88) = NULL;
        forceKill__11RPSysEffectFv(PTR(p + i * 4, 0x80));
    }
}

char* fn_8062CB20() { return lbl_806EDBF8; }

void* fn_8062CAE0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_8062CA8C(u8* p) {
    fn_80643B0C(p);
    *(u8**)p = lbl_806EDBA8;
    void* q = operator new(0xb8);
    if (q != NULL) {
        q = fn_8062E7E0(q);
    }
    PTR(p, 0x14) = q;
    return p;
}

void fn_8062CA24(u8* p) {
    Unk_HeapScope scope;
    fn_8036A5B4(&scope, fn_80653F6C(14));
    ((Unk_Vt0*)PTR(p, 0x14))->v14();
    if (fn_804564D8(&scope)) {
        becomeCurrentHeap__Q23EGG4HeapFv(scope.heap);
    }
}

void fn_8062C820(u8* p, s32 n);

void fn_8062C998(u8* p) {
    ((Unk_Vt0*)PTR(p, 0x14))->v1C();
    fn_8062C820(p, 0);
    S32(p, 0x20) = 0;
    for (s32 i = 0; i <= 1; i++) {
        S32(p + i * 4, 0x18) = 0;
        S32(p + i * 4, 0x24) = 0;
        S32(p + i * 4, 0x2c) = 0;
    }
    S32(p, 0x34) = 0;
    S32(p, 0x38) = 0;
    S32(p, 0x3c) = 0;
    U8(p, 0x40) = 0;
}

void fn_8062C940(u8* p) {
    (((Unk_PtmfHost*)p)->*lbl_806EDB80[S32(p, 0x10)])();
    ((Unk_Vt0*)PTR(p, 0x14))->v20();
}

void fn_8062C92C(u8* p) { ((Unk_Vt0*)PTR(p, 0x14))->v24(); }

void fn_8062C850(u8* p) { ((Unk_Vt0*)PTR(p, 0x14))->v30(); }

void fn_8062C83C(u8* p) { ((Unk_Vt0*)PTR(p, 0x14))->v34(); }

// MATCH-PENDING (R17) #19: dont_inline region keeps this callee out of line
#pragma push
#pragma dont_inline on
void fn_8062C820(u8* p, s32 n) {
    if (n == 2) {
        S32(PTR(p, 0x14), 0x4c) = 0;
    }
    S32(p, 0x10) = n;
}
#pragma pop

void fn_8062C81C() {}

void fn_8062C818() {}

void fn_8062C814() {}

void fn_8062C78C(u8* p) {
    fn_8062C820(p, 1);
    fn_8062D1AC(PTR(p, 0x14));
    if (S32(PTR(PTR(lbl_806F5FF0, 0x170), 0x20), 0xd0) == 0) {
        void* x = fn_8027B130(fn_805F37A0());
        if (fn_80292504(x, 0)) {
            PTR(p, 0x34) = fn_802924F0(x, 0);
        } else {
            PTR(p, 0x34) = NULL;
        }
    }
}

static inline u8* pickObj(u8* q) {
    if (PTR(q, 0x4) != NULL) {
        return (u8*)PTR(q, 0x4);
    }
    if (PTR(q, 0x8) != NULL) {
        return (u8*)PTR(q, 0x8);
    }
    return NULL;
}

void fn_8062C72C(u8* p, s32 i, u8* q) {
    u8* obj = pickObj(q);
    if (obj == NULL) {
        return;
    }
    if (S32(obj, 0x114) == 1) {
        if (++S32(p + i * 4, 0x24) > 999) {
            S32(p + i * 4, 0x24) = 999;
            fn_8062D084(PTR(p, 0x14));
        }
    }
}

void fn_8062C724(u8* p) { fn_8062D020(PTR(p, 0x14)); }

void fn_8062C6AC(u8* p, f32 f) {
    S32(p, 0x20) = S32(p, 0x20) + 1;
    for (s32 i = 0; i < 2; i++) {
        void* x = PTR(PTR((u8*)PTR(lbl_806F5FF0, 0x170) + i * 4, 0x20), 0xdc);
        if (x != NULL) {
            fn_8060E128(x, f);
        }
    }
}

BOOL fn_8062C5DC(u8* p) { return S32(p, 0x18) < S32(p, 0x1c); }

s32 fn_8062C5CC(u8* p, s32 i) { return S32(p + i * 4, 0x18); }

void fn_8062C44C(u8* p, s32 i) {
    S32(PTR((u8*)PTR(lbl_806F5FF0, 0x188) + i * 4, 0x34), 0x4) = 2;
    S32(p + i * 4, 0x2c) = S32(p + i * 4, 0x2c) + 1;
}

void fn_8062C444(u8* p) { fn_8062CB2C((u8*)PTR(p, 0x14)); }

BOOL fn_8062C260(u8* p, s32 i) { return S32(p + i * 4, 0x18) == 9; }

void fn_8062C258(u8* p, s32 v) { fn_8062CD7C(PTR(p, 0x14), v); }

void fn_8062C248(u8* p) { S32(PTR(p, 0x14), 0x4c) = 0; }

void fn_8062C234(u8* p, s32 a) {
    if (a == 0) {
        S32(p, 0x3c) = 1;
    }
}

}  // extern "C"
