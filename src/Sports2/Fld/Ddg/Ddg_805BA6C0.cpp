// Ddg_805BA6C0: Resort Frisbee Dog unit 0x805BA6C0-0x805BD21C (Resort-only, no Wii Sports twin).
// camera: fld_cam_op_*, fld_cam_miiIntro_00, fld_cam_end_00, fld_cam_gamePlay_00, WS2_fld_cam.brres (camera-state classes 0x806E88B0..0x806E8A30).
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E8A00 {
public:
    virtual void vf8();
};

extern "C" {

void PSMTXIdentity(u8*);
void fn_80330F08(u8*, u8*, u8*);
void fn_80334224(u8*);
void fn_803481D0(u8*);
extern u8 lbl_806E88B0[];
extern u8 lbl_806E88E0[];
extern u8 lbl_806E8910[];
extern u8 lbl_806E8940[];
extern u8 lbl_806E8970[];
extern u8 lbl_806E89A0[];
extern u8 lbl_806E89D0[];
extern u8 lbl_806E8A30[];
extern u8 lbl_807D5F44[];

extern u8* lbl_806F4E78;
u8* fn_80268F0C(u8*);
s32 fn_802699EC(u8*);

// Deleting destructor of a class without a base destructor.
void* fn_805BCBFC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCBBC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCB7C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCB3C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCAFC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCABC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCA7C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BCA3C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_805BC9FC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

u8* fn_805BC9C0(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E8A30;
    return p;
}

s32 fn_805BC83C(u8* p) {
    *(u32*)(p + 0xac) = 1;
    PSMTXIdentity(p + 0x7c);
    *(u32*)(p + 0x120) = -99;
    *(u32*)(p + 0x124) = -99;
    *(u8*)(p + 0x128) = 0;
    return -99;
}

void fn_805BC768(u8* p, u32 a1) {
    if (*(u8*)(p + 0x128) == 0) {
        *(u32*)(p + 0x120) = a1;
        *(u8*)(p + 0x128) = 1;
    }
}

BOOL fn_805BC738() { return fn_802699EC(fn_80268F0C(lbl_806F4E78)) != 0; }

void fn_805BC51C(u8* p) {
    fn_803481D0(*(u8**)(p + 0x120));
    ((Unk_StateMachine<Unk_806E8A00>*)(p + 0x124))->calc();
}

void fn_805BC4D4() {}

u8* fn_805BC2B0(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E89D0;
    return p;
}

void fn_805BC128(u8* p) {
    *(u8*)(p + 0x134) = 0;
    *(u8*)(p + 0x136) = 1;
}

u8* fn_805BBC94(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E89A0;
    return p;
}

f32 fn_805BBB8C(u8* p) {
    *(f32*)(p + 0xc) = *(f32*)(p + 0xb4);
    *(f32*)(p + 0x10) = *(f32*)(p + 0xb8);
    *(f32*)(p + 0x14) = *(f32*)(p + 0xbc);
    return *(f32*)(p + 0xb8);
}

void fn_805BBB78(u8* p) { fn_80330F08(p + 0x18, p + 0xfc, lbl_807D5F44); }

u8* fn_805BBB3C(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E8970;
    return p;
}

u8* fn_805BB824(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E8940;
    return p;
}

u8* fn_805BB4DC(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E8910;
    return p;
}

u8* fn_805BAF6C(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E88E0;
    *(u32*)(p + 0x158) = 0;
    return p;
}

u8* fn_805BA914(u8* p) {
    fn_80334224(p);
    *(u8**)(p) = lbl_806E88B0;
    return p;
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template void Unk_StateMachine<Unk_806E8A00>::setState(const StateFn&, const StateFn&, s32);
template Unk_StateMachine<Unk_806E8A00>::Unk_StateMachine(Unk_806E8A00*, s32, EGG::Heap*);
