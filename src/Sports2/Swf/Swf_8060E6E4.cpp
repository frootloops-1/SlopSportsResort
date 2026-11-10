// Swf_8060E6E4: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_80612A24(u8*);
void fn_80612A40(u8*);
void fn_8061489C(u8*);
void fn_806148D4(u8*);
void fn_806149C0(u8*);
extern u8 lbl_806EC514[];

f32 fn_8060FC18(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x60) + 0x8) + 0x24); }

f32 fn_8060FC08(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x60) + 0x8) + 0x60); }

f32 fn_8060FBF8(u8* p) { return *(f32*)(*(u8**)(*(u8**)(p + 0x60) + 0x8) + 0x6c); }

u8* fn_8060FBEC() { return lbl_806EC514; }

void* fn_8060FBAC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_8060F81C(u8* p) { return *(s32*)(p + 0x84); }

s32 fn_8060F7F4(u8* p) { return *(s32*)(p + 0x88); }

void fn_8060F7EC(u8* p) { fn_806149C0(*(u8**)(p + 0x5c)); }

void fn_8060F7E4(u8* p) { fn_806148D4(*(u8**)(p + 0x5c)); }

void fn_8060F7DC(u8* p) { fn_8061489C(*(u8**)(p + 0x5c)); }

void fn_8060F62C() {}

void fn_8060F628() {}

void fn_8060E8A0(u8* p) { fn_80612A40(*(u8**)(p + 0x58)); }

void fn_8060E850(u8* p) { fn_80612A24(*(u8**)(p + 0x58)); }


// ---- hand-written (first pass) ----
void fn_80614864(u8*);
void fn_8060F630(u8*, s32);

void fn_8060E858(u8* p) {
    if (*(s32*)(*(u8**)(p + 0x58) + 0x174) != 0) {
        fn_8060F630(p, *(s32*)(p + 0x68));
        *(s32*)(p + 0x68) = -1;
    }
}

void fn_8060E834(u8* p) {
    if (*(s32*)(*(u8**)(p + 0x58) + 0x178) != 0) {
        fn_80614864(*(u8**)(p + 0x5c));
    }
}

u8* fn_8060E748(u8* p) {
    if (*(s32*)(p + 0x7c) == 0) {
        return *(u8**)(*(u8**)(*(u8**)(p + 0x60) + 0x8) + 0x8);
    }
    return 0;
}

}  // extern "C"
