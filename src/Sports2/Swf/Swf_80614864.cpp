// Swf_80614864: Resort Swordplay unit 0x80614864-0x80615154 (Resort-only, no Wii Sports twin).
// "CPUステートコントローラ" (CPU state controller): vtable 0x806ED420, name 0x806ED438, state enter/update
// pointer-to-member tables 0x806ED3F0/0x806ED408.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_PtmfHost {};
typedef void (Unk_PtmfHost::*Unk_StateFn)();

extern "C" {

void fn_80614E30(u8*);
void fn_80614CE8(u8*);
void fn_80614FD0(u8*, s32);
BOOL fn_805F388C(void*);
void fn_8060F630(void*, s32);
s32 fn_80615218(void*);
s32 fn_80615154(void*);
void fn_8032349C(u8*);
extern u8* lbl_806F5FF0;
extern Unk_StateFn lbl_806ED3F0[];
extern Unk_StateFn lbl_806ED408[];
extern u8 lbl_806ED420[];
extern char lbl_806ED438[];

char* fn_80615148() { return lbl_806ED438; }

void* fn_80615108(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806150C4(u8* p, void* a) {
    fn_8032349C(p);
    PTR(p, 0x8) = a;
    *(u8**)p = lbl_806ED420;
    return p;
}

void fn_80615074(u8* p) {
    F32(p, 0x10) = 0.0f;
    S32(p, 0x14) = 0;
    S32(p, 0x18) = 0;
    S32(p, 0x1c) = 0;
    fn_80614E30(p);
    fn_80614FD0(p, 0);
}

void fn_80615028(u8* p) {
    F32(p, 0x10) += F32(lbl_806F5FF0, 0x1bc);
    (((Unk_PtmfHost*)p)->*lbl_806ED408[S32(p, 0xc)])();
}

// MATCH-PENDING (R17) #19: dont_inline region keeps this callee out of line
#pragma push
#pragma dont_inline on
void fn_80614FD0(u8* p, s32 n) {
    (((Unk_PtmfHost*)p)->*lbl_806ED3F0[n])();
    S32(p, 0xc) = n;
    F32(p, 0x10) = 0.0f;
}
#pragma pop

void fn_80614CE4() {}

void fn_80614B6C(u8* p) {
    S32(p, 0x14) = fn_80615218(PTR(PTR(p, 0x8), 0x60));
    S32(p, 0x1c) = fn_80615154(PTR(PTR(p, 0x8), 0x60));
    S32(p, 0x18) = 0;
    fn_8060F630(PTR(p, 0x8), 1);
}

void fn_80614B68() {}

void fn_80614AEC(u8* p) {
    if (S32(p, 0x14) == 2) {
        S32(p, 0x18) = S32(p, 0x18) + 1;
        if (S32(p, 0x18) < S32(PTR(PTR(PTR(p, 0x8), 0x60), 0x8), 0xc)) {
            fn_8060F630(PTR(p, 0x8), 5);
            return;
        }
    }
    fn_80614E30(p);
    fn_80614FD0(p, 0);
}

void fn_80614A90(u8* p) {
    if (fn_805F388C(PTR(PTR(p, 0x8), 0x8))) {
        fn_80614CE8(p);
    } else {
        fn_80614E30(p);
    }
    fn_80614FD0(p, 0);
}

void fn_8061489C(u8* p) {
    fn_80614CE8(p);
    fn_80614FD0(p, 0);
}

void fn_80614864(u8* p) {
    fn_80614E30(p);
    fn_80614FD0(p, 0);
}

}  // extern "C"
