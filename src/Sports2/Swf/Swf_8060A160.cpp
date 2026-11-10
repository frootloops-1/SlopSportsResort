// Swf_8060A160: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
struct Unk_VtAt0 {
    virtual void vf8(); virtual void vfC(); virtual void vf10(); virtual void vf14(); virtual void vf18();
    virtual void vf1C();
};

extern "C" {


void fn_802B0014(u8*);
void fn_802B976C(u8*);
void fn_80328488(u8*);
extern u8 lbl_806EBFCC[];
extern void* lbl_806EBF90[];

u8* fn_8060A69C() { return lbl_806EBFCC; }

void* fn_8060A65C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8060A350(u8* p) { fn_802B0014(*(u8**)(p + 0x10)); }

void fn_8060A160(u8* p) { fn_802B976C(*(u8**)(p + 0x10)); }


// ---- hand-written (first pass) ----
void fn_802B220C(u8*);
void fn_8060A168(u8*);

void fn_8060A574(u8* p) {
    fn_8060A168(p);
    (*(Unk_VtAt0**)(p + 0x10))->vf10();
}

void fn_8060A530(u8* p) {
    (*(Unk_VtAt0**)(p + 0x10))->vf1C();
    fn_802B220C(*(u8**)(p + 0x14));
}

}  // extern "C"
