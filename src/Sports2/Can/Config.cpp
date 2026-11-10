// Canoeing (Resort-only), .text 0x8048BC4C-0x8048BF10: singleton "Config". First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_8048BCCC(u8* p); // ctor
extern void* lbl_806F5838; // instance
extern void* lbl_806F583C; // heap

void fn_8048BE08(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5838 == NULL && lbl_806F583C == NULL, "Config");
    lbl_806F583C = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x4c, pHeap, 4);
        if (p != NULL) {
            p = fn_8048BCCC((u8*)p);
        }
        lbl_806F5838 = p;
    } else {
        void* p = operator new(0x4c);
        if (p != NULL) {
            p = fn_8048BCCC((u8*)p);
        }
        lbl_806F5838 = p;
    }
}

void fn_8048BDF8() {
    lbl_806F5838 = NULL;
    lbl_806F583C = NULL;
}

void fn_8048BC74(u8* p, u32 a1) { *(u32*)(p + 0x44) = a1; }

void fn_8048BC4C(u8* p, u32 a1, u8* a2, u32 a3, u32 a4, u32 a5) {
    *(u32*)(p) = a1;
    *(u8**)(p + 0x4) = a2;
    *(u32*)(p + 0x8) = *(u32*)(a2 + 0x10);
    *(u32*)(p + 0xc) = *(u32*)(*(u8**)(a2 + 0x10) + 0x24);
    *(u32*)(p + 0x10) = a3;
    *(u32*)(p + 0x14) = a4;
    *(u32*)(p + 0x18) = a5;
}

}  // extern "C"
