// Camera: Resort Archery unit 0x8055567C-0x8055B52C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "Camera" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E3708 {
public:
    virtual void vf8();
};
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8055AB98(void* p); // ctor
extern void* lbl_806F5B40;
extern void* lbl_806F5B44;

void fn_8055AD38(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B40 == NULL && lbl_806F5B44 == NULL, "Camera");
    lbl_806F5B44 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x33F30, pHeap, 4);
        if (p != NULL) {
            p = fn_8055AB98(p);
        }
        lbl_806F5B40 = p;
    } else {
        void* p = operator new(0x33F30);
        if (p != NULL) {
            p = fn_8055AB98(p);
        }
        lbl_806F5B40 = p;
    }
}

void fn_8055AD28() {
    lbl_806F5B40 = NULL;
    lbl_806F5B44 = NULL;
}

void fn_8055A6E4(u8* p) { ((Unk_StateMachine<Unk_806E3708>*)(p + 0x1c8))->calc(); }

u8 fn_80559080(u8* p) { return *(u8*)(p + 0x5dc); }

void fn_80558CB4() {}

void fn_80558CB0() {}

u8* fn_80558CA8(u8* p) { return p + 0xc8; }

void fn_80558948() {}

void fn_80558944() {}

void fn_80558134() {}

u8 fn_80558114(u8* p) { return *(u8*)(p + 0x339); }

void fn_80556F40(u8* p) { *(u8*)(p + 0x6348) = 0x1; }

void fn_80556D5C() {}

void fn_80556D58() {}

f32 fn_80556D50(u8* p) { return *(f32*)(p + 0x2e8); }

void fn_80556A4C() {}

void fn_80556A48() {}

u32 fn_80556544(u8* p) { return *(u32*)(p + 0x5e0); }

void fn_8055653C(u8* p, u8 v) { *(u8*)(p + 0x15a) = v; }

void fn_80556238() {}

u32 fn_80555EA8(u8* p) { return *(u32*)(p + 0x14); }

void fn_80555E4C() {}

void fn_80555DCC() {}

void fn_80555DC8() {}

void fn_80555DC4() {}

void fn_80555DC0() {}

int fn_80555684() { return 0x14; }

int fn_8055567C() { return 0xa; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E3708>::Unk_StateMachine(Unk_806E3708*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E3708>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
