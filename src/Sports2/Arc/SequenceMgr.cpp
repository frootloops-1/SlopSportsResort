// SequenceMgr: Resort Archery unit 0x8056911C-0x8056FC00 (Resort-only, no Wii Sports twin).
// File name from the singleton name string "SequenceMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E3F50 {
public:
    virtual void vf8();
};
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void fn_8054CB14(void* p);
void fn_8054CD44(void* p);
void* fn_8056F434(void* p); // ctor
extern void* lbl_806F5B7C;
extern void* lbl_806F5B80;
// placeholder for an object called through its vtable (slot = offset in the vtable)
struct Unk_Virtual {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
};

void fn_8056F740(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B7C == NULL && lbl_806F5B80 == NULL, "SequenceMgr");
    lbl_806F5B80 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x342C, pHeap, 4);
        if (p != NULL) {
            p = fn_8056F434(p);
        }
        lbl_806F5B7C = p;
    } else {
        void* p = operator new(0x342C);
        if (p != NULL) {
            p = fn_8056F434(p);
        }
        lbl_806F5B7C = p;
    }
}

void fn_8056F730() {
    lbl_806F5B7C = NULL;
    lbl_806F5B80 = NULL;
}

void fn_8056ECE4(u8* p) { ((Unk_StateMachine<Unk_806E3F50>*)(p + 0x128))->calc(); }

void fn_8056ECDC(u8* p, f32 v) { *(f32*)(p + 0x2e8) = v; }

void fn_8056ECD4(u8* p, f32 v) { *(f32*)(p + 0x2ec) = v; }

void fn_8056ECCC(u8* p, f32 v) { *(f32*)(p + 0x300) = v; }

void fn_8056E0A8() {}

void fn_8056E088(u8* p) { (*(Unk_Virtual**)(p + 0x5e0))->vf18(); }

void fn_8056DB44() {}

u8 fn_8056DB3C(u8* p) { return *(u8*)(p + 0x5dd); }

void fn_8056DB30(u8* p) { *(u8*)(p + 0x5dd) = 0x1; }

void fn_8056D1A0() {}

void fn_8056CF04() {}

void fn_8056C680() {}

void fn_8056C3D8(u8* p) { fn_8054CB14(*(u8**)(p + 0x5e0)); }

void fn_8056B18C() {}

void fn_8056AABC() {}

int fn_8056AAB4() { return 0x4; }

int fn_8056AAAC() { return 0x3; }

u32 fn_8056A9A0(u8* p) { return *(u32*)(p + 0x98); }

f32 fn_8056A208() { return 8.0f; }

void fn_80569470(u8* p) { fn_8054CD44(*(u8**)(p + 0x5e0)); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E3F50>::Unk_StateMachine(Unk_806E3F50*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E3F50>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
