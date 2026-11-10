// Ddg_805CFBAC: Resort Frisbee Dog unit 0x805CFBAC-0x805D2944 (Resort-only, no Wii Sports twin).
// player throw logic (const tables 0x806896E0..0x80689710).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806EA3E4 {
public:
    virtual void vf8();
};

// 3 floats + flag, copied member-wise
struct Unk_Vec3Flag {
    f32 x, y, z;
    u8 flag;
};

struct Unk_Pair8 {
    u32 m0;
    u32 m4;
};

struct Unk_Pair16 {
    Unk_Pair8 m0;
    Unk_Pair8 m8;
};

extern "C" {

void fn_805D225C(u8*);

extern f32* lbl_806EA3B0[];

// Deleting destructor of a class without a base destructor.
void* fn_805D28C4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805D28BC() { return 1; }

f32 fn_805D252C(s32 i) { return *lbl_806EA3B0[i]; }

f32 fn_805D2524() { return 30.0f; }

f32 fn_805D251C() { return -20.0f; }

u8* fn_805D24D8(u8* p) {
    *(void**)p = operator new(0x10);
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    return p;
}

void fn_805D248C(u8* p) {
    u8* e = *(u8**)(p + 0x4);
    *(u32*)(p + 0x10) = 0;
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x20) = 0;
    *(u8**)(p + 0x1c) = e;
    for (; e + 0xc < *(u8**)(p + 0x8); e += 0xc) {
        *(u8**)(e + 0x4) = e + 0xc;
    }
    *(u32*)(e + 0x4) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
}

void fn_805D2008(u8* p) { fn_805D225C(p); }

void fn_805D1FF8(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

void fn_805D1FF0(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

u32 fn_805CFD08(u8* p) { return *(u32*)(p + 0x4); }

void fn_805CFCE0(Unk_Pair16* p, Unk_Pair16** a1) { *p = **a1; }

void fn_805CFC64(u8* n) {
    if (*(u8**)(n + 0x4) != NULL) {
        *(u8**)(*(u8**)(n + 0x4) + 0x8) = *(u8**)(n + 0x8);
    }
    if (*(u8**)(n + 0x8) != NULL) {
        *(u8**)(*(u8**)(n + 0x8) + 0x4) = *(u8**)(n + 0x4);
    }
}

void fn_805CFC40(u8* p, u8* node) {
    u8* h = *(u8**)(p + 0x28);
    if (node == h) {
        *(u8**)(p + 0x28) = *(u8**)(h + 0x4);
    }
    *(u8**)(node + 0x4) = *(u8**)(p + 0x1c);
    *(u8**)(p + 0x1c) = node;
}

u8* fn_805CFC24(u8* p) {
    u8* h = *(u8**)(p + 0x1c);
    if (h != NULL) {
        *(u8**)(p + 0x1c) = *(u8**)(h + 0x4);
    }
    return h;
}

void fn_805CFBFC(u8* p, u8* a1) {
    *(f32*)(*(u8**)(p)) = *(f32*)(a1);
    *(f32*)(*(u8**)(p) + 0x4) = *(f32*)(a1 + 0x4);
    *(f32*)(*(u8**)(p) + 0x8) = *(f32*)(a1 + 0x8);
    *(u8*)(*(u8**)(p) + 0xc) = *(u8*)(a1 + 0xc);
}

void fn_805CFBD8(u8* list, u8* node) {
    *(u8**)(node + 0x4) = *(u8**)(list + 0x4);
    *(u8**)(node + 0x8) = list;
    if (*(u8**)(list + 0x4) != NULL) {
        *(u8**)(*(u8**)(list + 0x4) + 0x8) = node;
    }
    *(u8**)(list + 0x4) = node;
}

u32 fn_805CFBD0(u8* p) { return *(u32*)(p + 0x8); }

void fn_805CFBAC(Unk_Vec3Flag* p, const Unk_Vec3Flag* a1) { *p = *a1; }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806EA3E4>::Unk_StateMachine(Unk_806EA3E4*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806EA3E4>::setState(const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806EA3E4>::calc();
