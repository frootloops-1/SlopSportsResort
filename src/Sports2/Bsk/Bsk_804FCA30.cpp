// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

struct UnkVObj { virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); };
struct UnkVObjAt38 { u8 _00[0x38]; virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); };
struct UnkVec3 { f32 x, y, z; };
BOOL fn_80509D4C(void* p, f32 f);
void fn_80513A0C(void* p);
BOOL fn_80530AB8(void* p);
void fn_80357194(void* p, void* state);
u8* fn_80504C60();
void fn_80501F6C(void* p, void* v);
BOOL fn_8052DCE0(void* p);
BOOL fn_8052DCE8(void* p);
void fn_8050DF40(void* p);
void fn_8050DDFC(void* p, void* a);
void fn_8052DE10(void* p);
void fn_80530AC0(void* p);
void fn_80530BC4(void* p);
void fn_8052DFE0(void* p);
void fn_80509E84(void* p, BOOL b);
void fn_8050EEA0(void* p, f32 f);
void fn_80510404(void* p);
void fn_8050F640(void* p, u8 b);
void fn_80509DC8(void* p);
void fn_8050455C(void* p);
f32 lbl_806F2538 = 0.0005f;
f32 lbl_806F253C = 0.0005f;
f32 lbl_806F2540 = 0.04f;
void fn_803571BC();
void fn_8050F8B4();

const char* fn_804FF0C4() {
    static char sName[] = "Player";
    return sName;
}

// Deleting destructor of a class without a base destructor.
void* fn_804FEA38(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804FE548(u8* p) {
    if (p[0x12C]) {
        (*(UnkVObj**)(p + 0x164))->vf24();
    }
}

UnkVec3 fn_804FE528(u8* p) { return *(UnkVec3*)(*(u8**)(p + 0x15C) + 0xC); }

void fn_804FE4B8(u8* p, u32 v) { *(u32*)(p + 0x158) = v; }

void fn_804FE1C4() { fn_8050455C(fn_80504C60()); }

f32 fn_804FE14C(u8* p) { return *(f32*)(p + 0x138); }

int fn_804FE018(u8* p) {
    fn_8050EEA0(*(void**)(p + 0x164), 0.0f);
    fn_80510404(*(void**)(p + 0x164));
    fn_8050F640(*(void**)(p + 0x164), 1);
    fn_80509DC8(*(void**)(p + 0x15C));
    return 1;
}

int fn_804FDFDC(u8* p, BOOL b) {
    if (b) {
        fn_80357194(p, p + 0x70);
    } else {
        fn_80357194(p, p + 0x44);
    }
    return 1;
}

int fn_804FDC0C(u8* p) {
    fn_8052DFE0(*(void**)(p + 0x150));
    fn_80509E84(*(void**)(p + 0x15C), FALSE);
    fn_80357194(p, p + 0x9C);
    return 1;
}

int fn_804FDBCC(u8* p) {
    fn_80530BC4(*(void**)(p + 0x154));
    fn_80357194(p, p + 0xC8);
    return 1;
}

int fn_804FDB90(u8* p) {
    fn_8052DE10(*(void**)(p + 0x150));
    fn_80530AC0(*(void**)(p + 0x154));
    return 1;
}

int fn_804FDB38(u8* p, BOOL b, void* a) {
    if (b) {
        fn_8050DF40(*(void**)(p + 0x164));
    } else {
        fn_8050DDFC(*(void**)(p + 0x164), a);
    }
    fn_80357194(p, p + 0xF4);
    return 1;
}

BOOL fn_804FDA20(u8* p) {
    if (fn_8052DCE0(*(void**)(p + 0x150)) || fn_8052DCE8(*(void**)(p + 0x150))) {
        return TRUE;
    }
    return FALSE;
}

void fn_804FD9E4(u8* p) {
    fn_80501F6C(*(void**)(fn_80504C60() + 0x3C), *(u8**)(p + 0x15C) + 0xC);
}

void fn_804FD9DC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x44); }

void fn_804FD9D4(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0x9c); }

void fn_804FD9CC(u8* p) { ((void (*)(void*,void*))fn_803571BC)(p, p + 0xc8); }

void fn_804FD7B0(u8* p) {
    *(f32*)(*(u8**)(p + 0x15C) + 0x114) = lbl_806F2538;
    *(f32*)(*(u8**)(p + 0x15C) + 0x118) = lbl_806F253C;
    *(f32*)(*(u8**)(p + 0x15C) + 0x11C) = lbl_806F2540;
}

void fn_804FD430(u8* p) { ((void (*)(void*))fn_8050F8B4)(*(void**)(p + 0x164)); }

void fn_804FD3AC(u8* p, f32 f) {
    *(u32*)(p + 0x130) |= 1;
    *(f32*)(*(u8**)(p + 0x164) + 0xB0) = f;
}

void fn_804FD384(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x130) |= 0x8;
    } else {
        *(u32*)(p + 0x130) &= ~0x8;
    }
}

void fn_804FD35C(u8* p, BOOL b) {
    if (b) {
        *(u32*)(p + 0x130) |= 0x10;
    } else {
        *(u32*)(p + 0x130) &= ~0x10;
    }
}

void fn_804FD34C(u8* p) { *(u32*)(p + 0x130) |= 0x4; }

void fn_804FCCDC() {}

void fn_804FCCD8() {}

void fn_804FCCCC(u8* p) { *(u32*)(p + 0x14c) = 0; }

void fn_804FCBA0() {}

void fn_804FCB44() {}

void fn_804FCAEC(u8* p) {
    (*(UnkVObjAt38**)(p + 0x154))->vf20();
    if (fn_80530AB8(*(void**)(p + 0x154))) {
        fn_80357194(p, p + 0x44);
    }
}

void fn_804FCA30(u8* p) {
    if (fn_80509D4C(*(void**)(p + 0x15C), 0.0f)) {
        fn_80513A0C(*(void**)(p + 0x160));
    }
}

} // extern "C"
