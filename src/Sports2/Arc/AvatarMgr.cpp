// AvatarMgr: Resort Archery unit 0x805618EC-0x8056911C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "AvatarMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E3B9C {
public:
    virtual void vf8();
};
#include <egg/core.h>

extern "C" {

// Name tables at the start of .data (the vtables follow them); defined first so the string pool order matches.
const char* lbl_806E3960[] = {
    "all_root",
    "skl_root",
    "chest",
    "clavicle_l",
    "arm_l1",
    "arm_l2",
    "wrist_l",
    "finger_l1",
    "finger_l2",
    "thumb_l1",
    "thumb_l2",
    "clavicle_r",
    "arm_r1",
    "arm_r2",
    "wrist_r",
    "finger_r1",
    "finger_r2",
    "thumb_r1",
    "thumb_r2",
    "head",
    "head_set",
    "hip",
    "leg_l1",
    "leg_l2",
    "ankle_l",
    "leg_r1",
    "leg_r2",
    "ankle_r",
};
int lbl_806E39D0[] = {0x100, 0, 0, 0x100, 0, 0, 0};
const char* lbl_806E39EC[] = {
    "INIT",
    "KNOCK",
    "WAIT",
    "SETUP",
    "DRAW",
    "RELEASE",
    "TIMEUP",
};

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_80564A48(void* p); // ctor
extern void* lbl_806F5B70;
extern void* lbl_806F5B74;
// placeholder for an object called through its vtable (slot = offset in the vtable)
struct Unk_Virtual {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
};

void fn_80567410(u8* p) { (*(Unk_Virtual**)(p + 0x5e0))->vf2C(); }

void fn_805669F4() {}

void fn_805669E0(u8* p) { (*(Unk_Virtual**)(p + 0x5e0))->vf40(); }

u8* fn_80565E20(u8* p) { return *(u8**)(p + 0x30) + 0x20; }

u8* fn_80565E14(u8* p) { return *(u8**)(p + 0x30) + 0x8; }

void fn_80564C00(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B70 == NULL && lbl_806F5B74 == NULL, "AvatarMgr");
    lbl_806F5B74 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x98, pHeap, 4);
        if (p != NULL) {
            p = fn_80564A48(p);
        }
        lbl_806F5B70 = p;
    } else {
        void* p = operator new(0x98);
        if (p != NULL) {
            p = fn_80564A48(p);
        }
        lbl_806F5B70 = p;
    }
}

void fn_80564BF0() {
    lbl_806F5B70 = NULL;
    lbl_806F5B74 = NULL;
}

void fn_80564590() {}

void fn_8056437C() {}

void fn_80564378() {}

void fn_80563F1C() {}

void fn_80562F44() {}

void fn_80562C54() {}

void fn_80562980() {}

void fn_805628A4() {}

void fn_805628A0() {}

void fn_805627A4() {}

void fn_805627A0() {}

void fn_80562520() {}

void fn_8056251C() {}

void fn_80562518() {}

void fn_80562514() {}

void fn_805624A8() {}

void fn_805624A4() {}

int fn_805618EC() { return 0x3c; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template void Unk_StateMachine<Unk_806E3B9C>::calc();
template void Unk_StateMachine<Unk_806E3B9C>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template Unk_StateMachine<Unk_806E3B9C>::Unk_StateMachine(Unk_806E3B9C*, s32, EGG::Heap*);
