// Field: Resort Archery unit 0x8055B52C-0x8055CD2C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "Field" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8055C9A8(void* p); // ctor
extern void* lbl_806F5B50;
extern void* lbl_806F5B54;

void fn_8055CB58(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B50 == NULL && lbl_806F5B54 == NULL, "Field");
    lbl_806F5B54 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x108, pHeap, 4);
        if (p != NULL) {
            p = fn_8055C9A8(p);
        }
        lbl_806F5B50 = p;
    } else {
        void* p = operator new(0x108);
        if (p != NULL) {
            p = fn_8055C9A8(p);
        }
        lbl_806F5B50 = p;
    }
}

void fn_8055CB48() {
    lbl_806F5B50 = NULL;
    lbl_806F5B54 = NULL;
}

void fn_8055C318() {}

void fn_8055C314() {}

void fn_8055C0E4() {}

void fn_8055C0E0() {}

void fn_8055C0DC() {}

void fn_8055C0D8() {}

u8* fn_8055C0D0(u8* p) { return p + 0x48; }

int fn_8055C0C0() { return 0x80; }

}  // extern "C"
