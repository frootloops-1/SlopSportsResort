// Resort Basketball (bsk) file 0x80526CB0-0x80526FC0: probable Bsk::Config singleton (name string "Config"
// passed to the instance check fn_80370BD8), EGG::Disposer-derived, vtables 0x806E1290/0x806E129C.
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_80526CE4(void* p);          // ctor
extern void* lbl_806F5AC0;           // instance
extern void* lbl_806F5AC4;           // heap

void fn_80526EB8(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5AC0 == NULL && lbl_806F5AC4 == NULL, "Config");
    lbl_806F5AC4 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x4C, pHeap, 4);
        if (p != NULL) {
            p = fn_80526CE4(p);
        }
        lbl_806F5AC0 = p;
    } else {
        void* p = operator new(0x4C);
        if (p != NULL) {
            p = fn_80526CE4(p);
        }
        lbl_806F5AC0 = p;
    }
}

void fn_80526EA8() {
    lbl_806F5AC0 = 0;
    lbl_806F5AC4 = 0;
}

}  // extern "C"
