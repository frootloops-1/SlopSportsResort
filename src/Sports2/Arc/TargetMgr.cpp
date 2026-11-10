// TargetMgr: Resort Archery unit 0x8055CD2C-0x805618EC (Resort-only, no Wii Sports twin).
// File name from the singleton name string "TargetMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8055D164(void* p); // ctor
extern void* lbl_806F5B5C;
extern void* lbl_806F5B60;
void fn_80371B94(void*, int);
void* __construct_new_array(void* block, void* ctor, void* dtor, unsigned long size, unsigned long n);
void* fn_8056171C(void* p, int);
void* fn_8055D108(void* p);
void fn_80341EAC(void* p);
void* fn_8034740C(void* p);
void* fn_80231780(int, int);
void* GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(void*, const char*, u32*);
void fn_803473D8(void* p, void* file);
extern u8* lbl_806F4E78;

void fn_8055F4BC() {}

void fn_8055F4B8() {}

void fn_8055F384() {}

u8* fn_8055F35C(u8* p) { return *(u8**)(p + 0x1e8) + 0x8; }

u8* fn_8055F350(u8* p) { return *(u8**)(p + 0x1ec) + 0x8; }

u8* fn_8055F344(u8* p) { return *(u8**)(p + 0x1e8) + 0x20; }

u8* fn_8055F338(u8* p) { return *(u8**)(p + 0x1ec) + 0x20; }

u8* fn_8055F32C(u8* p) { return *(u8**)(p + 0x1ec) + 0x14; }

void fn_8055D258(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5B5C == NULL && lbl_806F5B60 == NULL, "TargetMgr");
    lbl_806F5B60 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x40, pHeap, 4);
        if (p != NULL) {
            p = fn_8055D164(p);
        }
        lbl_806F5B5C = p;
    } else {
        void* p = operator new(0x40);
        if (p != NULL) {
            p = fn_8055D164(p);
        }
        lbl_806F5B5C = p;
    }
}

void fn_8055D248() {
    lbl_806F5B5C = NULL;
    lbl_806F5B60 = NULL;
}

// First pass: allocates the target array and loads the four target collision files.
void fn_8055CF88(u8* p) {
    fn_80371B94(lbl_806F4E78 + 0x190, 2);
    void* arr = __construct_new_array(operator new[](0x348), (void*)fn_8056171C, (void*)fn_8055D108, 0x338, 1);
    *(void**)(p + 0x18) = arr;
    fn_80341EAC(arr);
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x30) = -1;
    fn_80371B94(lbl_806F4E78 + 0x190, 2);
    void* arc = fn_80231780(-1, 0);
    void* q = operator new(0x28);
    if (q != NULL) {
        q = fn_8034740C(q);
    }
    *(void**)(p + 0x1c) = q;
    fn_803473D8(*(void**)(p + 0x1c), GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(arc, "WS2_arc_target.kcl", 0));
    q = operator new(0x28);
    if (q != NULL) {
        q = fn_8034740C(q);
    }
    *(void**)(p + 0x20) = q;
    fn_803473D8(*(void**)(p + 0x20), GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(arc, "WS2_arc_target_piston.kcl", 0));
    q = operator new(0x28);
    if (q != NULL) {
        q = fn_8034740C(q);
    }
    *(void**)(p + 0x24) = q;
    fn_803473D8(*(void**)(p + 0x24), GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(arc, "WS2_arc_target_pole.kcl", 0));
    q = operator new(0x28);
    if (q != NULL) {
        q = fn_8034740C(q);
    }
    *(void**)(p + 0x28) = q;
    fn_803473D8(*(void**)(p + 0x28), GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(arc, "WS2_arc_target_tackle.kcl", 0));
}

void fn_8055CE4C() {}

f32 fn_8055CD3C() { return 10000.0f; }

f32 fn_8055CD34() { return 50.0f; }

f32 fn_8055CD2C() { return 13.698f; }

}  // extern "C"
