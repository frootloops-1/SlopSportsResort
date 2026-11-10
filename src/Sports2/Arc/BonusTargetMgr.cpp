// BonusTargetMgr: Resort Archery unit 0x8057C8B8-0x8057DE9C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "BonusTargetMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8057D1E0(void* p); // ctor
extern void* lbl_806F5BC0;
extern void* lbl_806F5BC4;

void fn_8057DD60() {}

void fn_8057D8C8() {}

void fn_8057D8C4() {}

void fn_8057D738() {}

void fn_8057D734() {}

void fn_8057D6EC() {}

void fn_8057D6E0(u8* p) { *(u32*)(p + 0x8) = 0x0; }

void fn_8057D364(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5BC0 == NULL && lbl_806F5BC4 == NULL, "BonusTargetMgr");
    lbl_806F5BC4 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x48, pHeap, 4);
        if (p != NULL) {
            p = fn_8057D1E0(p);
        }
        lbl_806F5BC0 = p;
    } else {
        void* p = operator new(0x48);
        if (p != NULL) {
            p = fn_8057D1E0(p);
        }
        lbl_806F5BC0 = p;
    }
}

void fn_8057D354() {
    lbl_806F5BC0 = NULL;
    lbl_806F5BC4 = NULL;
}

void fn_8057CCB0() {}

void fn_8057CC8C() {}

}  // extern "C"
