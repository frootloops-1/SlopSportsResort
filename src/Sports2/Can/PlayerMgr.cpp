// Canoeing (Resort-only), .text 0x80499CA4-0x80499F7C: singleton "PlayerMgr". First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_80499DA8(u8* p); // ctor
extern void* lbl_806F5898; // instance
extern void* lbl_806F589C; // heap
void __ct__Q23EGG8DisposerFv(u8*);
void fn_8035D6C8(u8*);
extern u8 lbl_806DBEF0[];
extern u8 lbl_806DBF04[];

void fn_80499E74(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5898 == NULL && lbl_806F589C == NULL, "PlayerMgr");
    lbl_806F589C = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x148, pHeap, 4);
        if (p != NULL) {
            p = fn_80499DA8((u8*)p);
        }
        lbl_806F5898 = p;
    } else {
        void* p = operator new(0x148);
        if (p != NULL) {
            p = fn_80499DA8((u8*)p);
        }
        lbl_806F5898 = p;
    }
}

void fn_80499E64() {
    lbl_806F5898 = NULL;
    lbl_806F589C = NULL;
}

u8* fn_80499DA8(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DBEF0;
    __ct__Q23EGG8DisposerFv(p + 0x8);
    *(u8**)(p + 0x8) = lbl_806DBF04;
    return p;
}

}  // extern "C"
