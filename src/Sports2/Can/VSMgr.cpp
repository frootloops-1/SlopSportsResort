// Canoeing (Resort-only), .text 0x804BFB30-0x804C17A8: singleton "VSMgr" (WS2_can_checkpoint_tape). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>
#include <egg/core.h>

extern "C" {

struct Vec3f { f32 x, y, z; };
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_804C1368(u8* p); // ctor
extern void* lbl_806F5924; // instance
extern void* lbl_806F5928; // heap
void fn_804BFD3C(u8*, u32);
void fn_804C1668(u8*);
void fn_804C161C(u8* p);

u8* fn_804C16CC(u8* p) {
    fn_804C1668(p + 0x20);
    fn_804C1668(p + 0x160);
    fn_804C161C(p);
    return p;
}

void fn_804C161C(u8* p) {
    *(u8*)(p) = 0;
    *(u8*)(p + 0x1) = 0;
    ((RPSysEffect*)(p + 0x44))->forceKill();
    *(u8*)(p + 0x15c) = 0;
    ((RPSysEffect*)(p + 0x184))->forceKill();
    *(u8*)(p + 0x29c) = 0;
}

void fn_804C15D0(u8* p, const Vec3f* pos, u32 v, u8 on, u8 big) {
    p[0x1] = 1;
    if (on) {
        *(Vec3f*)(p + 0x8) = *pos;
        *(u32*)(p + 0x14) = v;
        p[0x19] = big;
    }
    p[0x18] = on;
    *(s32*)(p + 0x1c) = big ? 45 : 15;
}

void fn_804C15A8(u8* p) {
    p[0x0] = 1;
    p[0x1] = 0;
    *(f32*)(p + 0x4) = 1.0f;
    p[0x15c] = 1;
    p[0x29c] = 1;
    p[0x1a] = 0;
}

void fn_804C1508(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5924 == NULL && lbl_806F5928 == NULL, "VSMgr");
    lbl_806F5928 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x74, pHeap, 4);
        if (p != NULL) {
            p = fn_804C1368((u8*)p);
        }
        lbl_806F5924 = p;
    } else {
        void* p = operator new(0x74);
        if (p != NULL) {
            p = fn_804C1368((u8*)p);
        }
        lbl_806F5924 = p;
    }
}

void fn_804C14F8() {
    lbl_806F5924 = NULL;
    lbl_806F5928 = NULL;
}

void fn_804BFD34(u8* p) { fn_804BFD3C(p, *(u32*)(p + 0x48)); }

void fn_804BFB30(u8* p) {
    fn_804C161C(*(u8**)(p + 0x64));
    fn_804C161C(*(u8**)(p + 0x64) + 0x2a0);
}

}  // extern "C"
