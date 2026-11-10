// Analyzer: Resort Archery unit 0x805489C0-0x80549568 (Resort-only, no Wii Sports twin).
// File name from the singleton name string "Analyzer" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_805493DC(void* p); // ctor
extern void* lbl_806F5B28;
extern void* lbl_806F5B2C;

void fn_80549460(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B28 == NULL && lbl_806F5B2C == NULL, "Analyzer");
    lbl_806F5B2C = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x84, pHeap, 4);
        if (p != NULL) {
            p = fn_805493DC(p);
        }
        lbl_806F5B28 = p;
    } else {
        void* p = operator new(0x84);
        if (p != NULL) {
            p = fn_805493DC(p);
        }
        lbl_806F5B28 = p;
    }
}

void fn_80549450() {
    lbl_806F5B28 = NULL;
    lbl_806F5B2C = NULL;
}

void fn_80548F18() {}

void fn_80548F14() {}

void fn_80548F10() {}

void fn_80548F0C() {}

void fn_80548F08() {}

void fn_80548F04() {}

void fn_80548F00() {}

}  // extern "C"
