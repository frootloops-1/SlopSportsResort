// Swf_8062AA6C: Resort Swordplay unit 0x8062AA6C-0x8062B23C (Resort-only, no Wii Sports twin).
// "薪割りフィールド" (Speed Slice field): vtable 0x806EDA30, name 0x806EDA80; Map/WS2_swf_island_T.pmp.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

extern "C" {

void fn_8062AA6C(u8*);
void SinCosFIdx__Q24nw4r4mathFPfPff(f32*, f32*, f32);
void PSVECCrossProduct(const void*, const void*, void*);
void UpdateFrame__10RPGrpModelFv(void*);
void Calc__10RPGrpModelFv(void*);
void Entry__10RPGrpModelFv(void*);
extern f32 lbl_807D0330[3];
extern char lbl_806EDA80[];

char* fn_8062B20C() { return lbl_806EDA80; }

void* fn_8062B1CC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8062AEC4(u8* p) { fn_8062AA6C(p); }

void fn_8062AE84(u8* p) {
    UpdateFrame__10RPGrpModelFv(PTR(p, 0x80));
    Calc__10RPGrpModelFv(PTR(p, 0x80));
    Entry__10RPGrpModelFv(PTR(p, 0x80));
}

void fn_8062AE14(u8* p) {
    SinCosFIdx__Q24nw4r4mathFPfPff((f32*)(p + 0x74), (f32*)(p + 0x7c), 0.0f);
    F32(p, 0x78) = 0.0f;
    F32(p, 0x68) = lbl_807D0330[0];
    F32(p, 0x6c) = lbl_807D0330[1];
    F32(p, 0x70) = lbl_807D0330[2];
    PSVECCrossProduct(p + 0x68, p + 0x74, p + 0x5c);
}

}  // extern "C"
