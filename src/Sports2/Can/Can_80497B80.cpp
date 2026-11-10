// Canoeing (Resort-only), .text 0x80497B80-0x80497D94. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80277E90(u8* p, f32 a, f32 b);
s16 fn_8027B258(u8* p, s32 i);
void fn_80277E34(u8*, s32);
void fn_80489D84(u8*);
void fn_80489DDC(u8*);
void fn_80489E14(u8*);
void fn_80489E4C(u8*);
void fn_80489E84(u8*);
void fn_804B8D24(u8*);
extern u8 lbl_806DBE20[];

s32 fn_80497D50(const u8* p) { return *(s32*)(p + 0x18) - fn_8027B258(*(u8**)(*(u8**)(p + 0x10) + 0xc), 4); }

void fn_80497D48(u8* p) { fn_80489E84(*(u8**)(p + 0x10)); }

void fn_80497D40(u8* p) { fn_80489E4C(*(u8**)(p + 0x10)); }

void fn_80497D38(u8* p) { fn_80489D84(*(u8**)(p + 0x10)); }

void fn_80497D30(u8* p) { fn_80489E14(*(u8**)(p + 0x10)); }

void fn_80497D28(u8* p) { fn_80489DDC(*(u8**)(p + 0x10)); }

// Deleting destructor of a class without a base destructor.
void* fn_80497CE8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80497CA8(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_80497C58(u8* p, u8* a1) {
    fn_804B8D24(p);
    *(u8**)(p + 0xc) = a1;
    *(u8**)(p) = lbl_806DBE20;
    fn_80277E34(*(u8**)(a1 + 0x1154), 0);
    return p;
}

void fn_80497C44(u8* p) { fn_80277E90(*(u8**)(*(u8**)(p + 0xc) + 0x1154), 0.03f, 0.4f); }

u8* fn_80497C38(u8* p) { return *(u8**)(p + 0x8) + 0xd8; }

}  // extern "C"
