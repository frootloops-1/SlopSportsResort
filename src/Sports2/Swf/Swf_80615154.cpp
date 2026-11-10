// Swf_80615154: Resort Swordplay unit 0x80615154-0x80615BEC (Resort-only, no Wii Sports twin).
// "CPUパラメータ" (CPU parameter): loads Cpu/Sp2SwfCpuData.exbin; vtable 0x806ED450, name 0x806ED464.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

extern "C" {

void fn_806157F8(u8*);
void* fn_80328970(void*, const char*, s32);
void fn_8032349C(u8*);
extern u8* lbl_806F5FF0;
extern u8* lbl_806F6008;
extern char lbl_8068ADD0[];
extern u8 lbl_806ED450[];
extern char lbl_806ED464[];

char* fn_80615BE0() { return lbl_806ED464; }

void* fn_80615BA0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_806157B0(u8* p) {
    fn_8032349C(p);
    *(u8**)p = lbl_806ED450;
    S32(p, 0xc) = 0;
    PTR(p, 0x8) = NULL;
    return p;
}

void fn_8061577C() { lbl_806F6008 = (u8*)fn_80328970(lbl_806F5FF0, lbl_8068ADD0, 0); }

void fn_80615760(u8* p, s32 n) {
    S32(p, 0xc) = n;
    PTR(p, 0x8) = lbl_806F6008 + n * 0xdc + 0x10;
    fn_806157F8(p);
}

}  // extern "C"
