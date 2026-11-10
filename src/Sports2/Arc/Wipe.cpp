// Wipe: Resort Archery unit 0x8056FDD4-0x80571BC8 (Resort-only, no Wii Sports twin).
// File name from the singleton name string "Wipe" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E418C {
public:
    virtual void vf8();
};
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8057148C(void* p); // ctor
extern void* lbl_806F5B90;
extern void* lbl_806F5B94;
void fn_80371B94(void*, int);
void* fn_80231780(int, int);
void* GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(void*, const char*, u32*);
extern void* spCurrent__20RPGrpModelResManager;
extern void* spCurrent__13RPGrpRenderer;
extern u32 sTVMode__Q23EGG6Screen;
u32 CreateData__20RPGrpModelResManagerFQ220RPGrpModelResManager4TypePvUlPUc(void*, int, void*, u32, u8*);
void* fn_8025A190(void*, u16, const char*, int, int, int, int);
void* __ct__19RPGrpCaptureTextureFP11RPGrpScreen9_GXTexFmtUl(void*, void*, int, u32);
void fn_8025A41C(void*, int);
extern u8 lbl_806E4058[];
extern u16 sTVModeInfo__Q23EGG6Screen[];
extern u8* lbl_806F4E78;

void fn_80571740(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B90 == NULL && lbl_806F5B94 == NULL, "Wipe");
    lbl_806F5B94 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x110, pHeap, 4);
        if (p != NULL) {
            p = fn_8057148C(p);
        }
        lbl_806F5B90 = p;
    } else {
        void* p = operator new(0x110);
        if (p != NULL) {
            p = fn_8057148C(p);
        }
        lbl_806F5B90 = p;
    }
}

void fn_80571730() {
    lbl_806F5B90 = NULL;
    lbl_806F5B94 = NULL;
}

// First pass: loads the wipe model data, creates the three wipe layers and the capture texture, and
// registers the wipe states.
void fn_805711C4(u8* p) {
    u8* tbl = lbl_806E4058;
    fn_80371B94(lbl_806F4E78 + 0x190, 2);
    void* arc = fn_80231780(-1, 0);
    u32 res = CreateData__20RPGrpModelResManagerFQ220RPGrpModelResManager4TypePvUlPUc(
        spCurrent__20RPGrpModelResManager, 0xc,
        GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(arc, "G3D/WS2_arc_wipe.brres", 0), 0, 0);
    void* q = operator new(0x34);
    if (q != NULL) {
        q = fn_8025A190(q, res, "WS2_arc_wipe", 0, 0, 1, 1);
    }
    *(void**)(p + 0x48) = q;
    q = operator new(0x34);
    if (q != NULL) {
        q = fn_8025A190(q, res, "WS2_arc_wipe02", 0, 0, 1, 1);
    }
    *(void**)(p + 0x4c) = q;
    q = operator new(0x34);
    if (q != NULL) {
        q = fn_8025A190(q, res, "WS2_arc_wipe03", 0, 0, 1, 1);
    }
    *(void**)(p + 0x50) = q;
    void* screen = *(void**)(*(u8**)(*(u8**)((u8*)spCurrent__13RPGrpRenderer + 0x18) + 0x10) + 0);
    q = operator new(0x14);
    if (q != NULL) {
        q = __ct__19RPGrpCaptureTextureFP11RPGrpScreen9_GXTexFmtUl(q, screen, 6, 0);
    }
    *(void**)(p + 0x54) = q;
    fn_8025A41C(q, 1);
    u8 color[4] = {0, 0, 0, 0};
    u8* tex = *(u8**)(*(u8**)(p + 0x54) + 4);
    tex[0x19] = color[0];
    tex[0x1a] = color[1];
    tex[0x1b] = color[2];
    tex[0x1c] = color[3];
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xc), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x18), 0);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x24), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x30), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x3c), 1);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x48), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x54), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x60), 2);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x6c), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x78), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x84), 3);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x90), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x9c), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xa8), 4);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xb4), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xc0), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xcc), 5);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xd8), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xe4), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xf0), 6);
    ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->setState(*(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0xfc), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x108), *(Unk_StateMachine<Unk_806E418C>::StateFn*)(tbl + 0x114), 11);
    *(f32*)(p + 0xb8) = (f32)sTVModeInfo__Q23EGG6Screen[sTVMode__Q23EGG6Screen * 6] / (f32)sTVModeInfo__Q23EGG6Screen[sTVMode__Q23EGG6Screen * 6 + 1];
    *(f32*)(p + 0xbc) = (f32)sTVModeInfo__Q23EGG6Screen[6] / (f32)sTVModeInfo__Q23EGG6Screen[sTVMode__Q23EGG6Screen * 6];
}

void fn_80571130(u8* p) { ((Unk_StateMachine<Unk_806E418C>*)(p + 0x18))->calc(); }

void fn_8057112C() {}

void fn_80570D24() {}

void fn_80570D20() {}

void fn_80570D1C() {}

void fn_80570D18() {}

u8 fn_805702A4(u8* p) { return *(u8*)(p + 0x74); }

void fn_8057008C() {}

void fn_80570024() {}

void fn_80570020() {}

void fn_8056FFDC() {}

void fn_8056FFD8() {}

void fn_8056FFD4() {}

void fn_8056FFD0() {}

void fn_8056FFCC() {}

void fn_8056FFC8() {}

void fn_8056FFC4() {}

void fn_8056FFC0() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E418C>::Unk_StateMachine(Unk_806E418C*, s32, EGG::Heap*);
