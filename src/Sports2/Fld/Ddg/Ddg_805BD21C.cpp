// Ddg_805BD21C: Resort Frisbee Dog unit 0x805BD21C-0x805C1AB0 (Resort-only, no Wii Sports twin).
// dog: WS2_fld_signA/B, WS2_fld_note1/2, WS2_fld_dog_body*, WS2_fld_dog_model (vtable 0x806E8C08, state table 0x806E8A98).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E8C08 {
public:
    virtual void vf8();
};

// 13-byte element (3 words + flag) copied member-wise
struct Unk_Pair8 {
    u32 m0;
    u32 m4;
};

struct Unk_Elem13 {
    Unk_Pair8 m0;
    u32 m8;
    u8 mC;
};

extern "C" {

struct Unk_VtAt48 {
    u8 unk0[0x48];
    virtual void vf8();
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28(u32, u32, s32);
};

void fn_802BB68C(u8*);
extern u32 lbl_806E8A98;
extern u8 lbl_807D05DC[];

void fn_802ABB5C(u8*, s32);
double ceil(double);
double floor(double);

// Deleting destructor of a class without a base destructor.
void* fn_805C19B4(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

s32 fn_805C19AC() { return 1; }

s32 fn_805C19A4() { return 1; }

u8* fn_805C1640(u8* p) {
    *(void**)p = operator new(0x10);
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    return p;
}

void fn_805C15F4(u8* p) {
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

u8* fn_805C15B0(u8* p) {
    *(void**)p = operator new(0x4);
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
    return p;
}

void fn_805C1564(u8* p) {
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

void fn_805C0EA8(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

void fn_805C0EA0(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

void fn_805C0E90(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u32*)(p + 0x8) = 0;
}

void fn_805C0E88(u8* p, u32 a1) { *(u32*)(p + 0x4) = a1; }

u8* fn_805C0E6C(u8* p) {
    u8* h = *(u8**)(p + 0x1c);
    if (h != NULL) {
        *(u8**)(p + 0x1c) = *(u8**)(h + 0x4);
    }
    return h;
}

void fn_805C0E60(u8* p, f32 fa1) { *(f32*)(*(u8**)(p)) = fa1; }

void fn_805C0E3C(u8* list, u8* node) {
    *(u8**)(node + 0x4) = *(u8**)(list + 0x4);
    *(u8**)(node + 0x8) = list;
    if (*(u8**)(list + 0x4) != NULL) {
        *(u8**)(*(u8**)(list + 0x4) + 0x8) = node;
    }
    *(u8**)(list + 0x4) = node;
}

void fn_805C04A8() {}

void fn_805C0414() {}

u32 fn_805C0260(u8* p) { return *(u32*)(p + 0x4); }

void fn_805C0238(Unk_Elem13* p, Unk_Elem13** a1) { *p = **a1; }

void fn_805C0214(Unk_Elem13* p, const Unk_Elem13* a1) { *p = *a1; }

u8* fn_805C0208() { return lbl_807D05DC; }

void fn_805BEFE4(u8* p) {
    if (*(u8*)(p + 0x1a8) != 0) {
        fn_802ABB5C(*(u8**)(p + 0x2f4), 1);
    }
}

void fn_805BEFE0() {}

void fn_805BEFDC() {}

f32 fn_805BDD0C(f32 x) { return floor(x); }

f32 fn_805BDCE8(f32 x) { return ceil(x); }

u8* fn_805BD7D8(u8* p) {
    u8* h = *(u8**)(p + 0x1c);
    if (h != NULL) {
        *(u8**)(p + 0x1c) = *(u8**)(h + 0x4);
    }
    return h;
}

void fn_805BD7B0(Unk_Elem13** p, const Unk_Elem13* a1) { **p = *a1; }

void fn_805BD78C(u8* list, u8* node) {
    *(u8**)(node + 0x4) = *(u8**)(list + 0x4);
    *(u8**)(node + 0x8) = list;
    if (*(u8**)(list + 0x4) != NULL) {
        *(u8**)(*(u8**)(list + 0x4) + 0x8) = node;
    }
    *(u8**)(list + 0x4) = node;
}

u32 fn_805BD390(u8* p) {
    *(u32*)(p + 0x188) = 3;
    ((Unk_StateMachineBase*)(p + 0xa0))->request(9);
    *(u16*)(p + 0x1aa) = *(u16*)(p + 0x1aa) | 0x80;
    *(u32*)(*(u8**)(p + 0x9c) + 0x8) = 4;
    return *(u16*)(p + 0x1aa) | 0x80;
}

void fn_805BD2DC(u8* p, s32 a1) {
    ((Unk_VtAt48*)(*(u8**)(p + 0x18c)))->vf28(lbl_806E8A98, *(u32*)(p + a1 * 4 + 0x190), 1);
}

void fn_805BD2D4(u8* p) { fn_802BB68C(*(u8**)(p + 0x2e4)); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E8C08>::Unk_StateMachine(Unk_806E8C08*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E8C08>::setState(const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806E8C08>::calc();
