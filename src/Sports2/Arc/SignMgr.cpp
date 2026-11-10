// SignMgr: Resort Archery unit 0x8057420C-0x80576C7C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "SignMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_805752D4(void* p); // ctor
extern void* lbl_806F5BA0;
extern void* lbl_806F5BA4;

void fn_80576C78() {}

void fn_805756F8() {}

void fn_805756F4() {}

void fn_80575650() {}

void fn_8057564C() {}

void fn_80575648() {}

void fn_8057552C() {}

void fn_80575528() {}

void fn_80575418(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5BA0 == NULL && lbl_806F5BA4 == NULL, "SignMgr");
    lbl_806F5BA4 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0xAFC, pHeap, 4);
        if (p != NULL) {
            p = fn_805752D4(p);
        }
        lbl_806F5BA0 = p;
    } else {
        void* p = operator new(0xAFC);
        if (p != NULL) {
            p = fn_805752D4(p);
        }
        lbl_806F5BA0 = p;
    }
}

void fn_80575408() {
    lbl_806F5BA0 = NULL;
    lbl_806F5BA4 = NULL;
}

void fn_80574490() {}

void fn_8057448C() {}

void fn_805743C0() {}

void fn_805743BC() {}

void fn_805743B8() {}

void fn_80574228() {}

}  // extern "C"
