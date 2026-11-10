// Bsk::Scene: Resort Basketball scene (Resort-only, no Wii Sports twin).
// Class name from the string "root ( Bsk::Scene )" (fn_804FBCB8) and the vtable at 0x806DFE80,
// which derives from RPSysScene through an unnamed intermediate scene class.
// First pass: the scene virtuals are written as extern "C" functions on raw offsets; the dtor and
// its thunk (__dt__Q23Bsk5SceneFv, @48@...) need the scene class hierarchy and are not written.
// fn_804FBAE8/fn_804FBEE0/fn_804FBEE8 are weak virtuals of other Basketball classes emitted here.

#include <types.h>

// Placeholders for objects called through their vtables (slot = byte offset in the vtable).
struct UnkVObj {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
};

struct UnkVObj148 {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14(void* p, int i);
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
};

// Object returned by fn_80504C60; its vtable pointer sits at 0x38.
struct UnkVObjAt38 {
    u8 _00[0x38];
    virtual void vf08();
    virtual void vf0C();
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
    virtual void vf3C(void* p);
};

extern "C" {

void fn_80356F18();
void fn_80356F0C();
void fn_80356F74(void* p);
void fn_80356FF8();
void fn_80357048(void* p);
void fn_80357088(void* p, int flags, int i);
UnkVObjAt38* fn_80504C60();
extern UnkVObj* lbl_806F59E4; // GraphManager instance
extern u32 lbl_806F59D8;
void fn_80370BD4(BOOL, const char*); // instance check (empty in release)
extern char lbl_806B56A8[];          // "StaticMem" (weak name string)
extern u8* lbl_806F4E98;             // StaticMem instance
extern u8* lbl_806F4CD8;
int Unk_8022F30C__10RPSysSceneFv(void* scene, int flags, int i);
u32 fn_80276A5C(int, u32, u32);
void* fn_80235850(void*, int);
void* fn_80235B2C(void*);
void* fn_80261BA8(void*, u8, int);
u32 fn_80261ADC(void*);
s16 fn_80261BF8(void*, int, u8);
int fn_8027B718(u16, BOOL);

int fn_804FBEE8() { return 2; }

int fn_804FBEE0() { return 0; }

void fn_804FBC54(u8* p) {
    lbl_806F59E4->vf10();
    (*(UnkVObj**)(p + 0x144))->vf10();
    (*(UnkVObj**)(p + 0x148))->vf10();
}

void fn_804FBBC4(u8* p) {
    fn_80357048(*(void**)(p + 0x140));
    fn_80356FF8();
    (*(UnkVObj**)(p + 0x144))->vf14();
    fn_80357088(*(void**)(p + 0x144), 0x4000, 0);
    lbl_806F59E4->vf14();
    fn_80357088(lbl_806F59E4, 0x3FFD, 0);
    (*(UnkVObj**)(p + 0x148))->vf18();
}

void fn_804FBB60(u8* p) {
    fn_80356F74(p);
    (*(UnkVObj148**)(p + 0x148))->vf14(*(void**)(*(u8**)((u8*)lbl_806F59E4 + 0x34) + 4), 0);
    (*(UnkVObj148**)(p + 0x148))->vf20();
}

void fn_804FBB5C(void* p) { ((void (*)(void*))fn_80356F18)(p); }

void fn_804FBAEC(u8* p) {
    (*(UnkVObj**)(p + 0x144))->vf24();
    lbl_806F59E4->vf24();
    fn_80356F0C();
    (*(UnkVObj148**)(p + 0x148))->vf1C();
    lbl_806F59D8 = 0;
}

void fn_804FBAE8() {}

int fn_804FB984(void* scene) {
    fn_80370BD4(lbl_806F4E98 != NULL, lbl_806B56A8);
    u8* sm = lbl_806F4E98;
    int n = *(int*)(lbl_806F4CD8 + 8);
    if (*(int*)(sm + 0x18) == 5) {
        for (int i = 0; i < n; i++) {
            if (Unk_8022F30C__10RPSysSceneFv(scene, 0x100, i)) {
                return 2;
            }
        }
    }
    if (n == 1 && *(int*)(sm + 0x18) == 5) {
        u32 a = fn_80276A5C(1, *(u32*)(sm + 0x14), *(u32*)(sm + 0x18));
        void* x = fn_80235B2C(fn_80235850(lbl_806F4CD8, 0));
        u32 b = fn_80261ADC(fn_80261BA8(x, a, 0));
        u32 c = fn_80276A5C(0, *(u32*)(sm + 0x14), *(u32*)(sm + 0x18));
        if (!fn_8027B718(b, fn_80261BF8(x, 5, c) != 0)) {
            return 2;
        }
    }
    return 3;
}

void fn_804FBAA8(void*, void* arg) { fn_80504C60()->vf3C(arg); }

} // extern "C"
