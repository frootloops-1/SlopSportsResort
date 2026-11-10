// ObstacleMgr: Resort Archery unit 0x8057955C-0x8057AC9C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "ObstacleMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_80579B88(void* p); // ctor
extern void* lbl_806F5BB8;
extern void* lbl_806F5BBC;
void fn_80371B94(void*, int);
void* __construct_new_array(void* block, void* ctor, void* dtor, unsigned long size, unsigned long n);
void* fn_80579B48(void* p);
void* fn_8057ABAC(void* p, int);
void fn_80341EAC(void* p);
void* fn_8034740C(void* p);
void* fn_80231780(int, int);
void* GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(void*, const char*, u32*);
void fn_803473D8(void* p, void* file);
extern u8* lbl_806F4E78;

void fn_8057A2B4() {}

void fn_8057A2B0() {}

void fn_8057A2AC() {}

void fn_80579EF4() {}

void fn_80579EF0() {}

void fn_80579EEC() {}

void fn_80579EDC() {}

void fn_80579ED8() {}

void fn_80579C64(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5BB8 == NULL && lbl_806F5BBC == NULL, "ObstacleMgr");
    lbl_806F5BBC = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x2C, pHeap, 4);
        if (p != NULL) {
            p = fn_80579B88(p);
        }
        lbl_806F5BB8 = p;
    } else {
        void* p = operator new(0x2C);
        if (p != NULL) {
            p = fn_80579B88(p);
        }
        lbl_806F5BB8 = p;
    }
}

// First pass: allocates the 0x94-byte entry array and loads the board collision file.
void fn_80579A74(u8* p) {
    fn_80371B94(lbl_806F4E78 + 0x190, 2);
    int n = *(int*)(p + 0x20);
    *(void**)(p + 0x18) = __construct_new_array(operator new[](n * 0x94 + 0x10), (void*)fn_8057ABAC, (void*)fn_80579B48, 0x94, n);
    for (int i = 0; i < *(int*)(p + 0x20); i++) {
        fn_80341EAC(*(u8**)(p + 0x18) + i * 0x94);
    }
    void* q = operator new(0x28);
    if (q != NULL) {
        q = fn_8034740C(q);
    }
    *(void**)(p + 0x1c) = q;
    fn_803473D8(*(void**)(p + 0x1c), GetFileFromArchive__20RPSysResourceManagerFPQ23EGG7ArchivePCcPUl(fn_80231780(-1, 0), "WS2_arc_rectangle_board.kcl", 0));
}

void fn_80579C54() {
    lbl_806F5BB8 = NULL;
    lbl_806F5BBC = NULL;
}

void fn_805797FC() {}

void fn_805797F8() {}

void fn_80579784() {}

void fn_80579780() {}

void fn_80579778(u8* p, u32 v) { *(u32*)(p + 0x20) = v; }

f32 fn_80579564() { return 13.661f; }

f32 fn_8057955C() { return 9.444f; }

}  // extern "C"
