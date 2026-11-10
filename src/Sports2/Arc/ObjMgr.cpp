// ObjMgr: Resort Archery unit 0x8056FC00-0x8056FDD4 (Resort-only, no Wii Sports twin).
// File name from the singleton name string "ObjMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8056FC00(void* p); // ctor
extern void* lbl_806F5B88;
extern void* lbl_806F5B8C;

void fn_8056FCCC(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B88 == NULL && lbl_806F5B8C == NULL, "ObjMgr");
    lbl_806F5B8C = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x9C, pHeap, 4);
        if (p != NULL) {
            p = fn_8056FC00(p);
        }
        lbl_806F5B88 = p;
    } else {
        void* p = operator new(0x9C);
        if (p != NULL) {
            p = fn_8056FC00(p);
        }
        lbl_806F5B88 = p;
    }
}

void fn_8056FCBC() {
    lbl_806F5B88 = NULL;
    lbl_806F5B8C = NULL;
}

}  // extern "C"
