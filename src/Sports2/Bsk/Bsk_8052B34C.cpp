// Resort Basketball (bsk) file 0x8052B34C-0x8052F2A4: class with vtables 0x806E14D8/0x806E1628/0x806E16C0 (ctor 0x8052E674).
// First pass (generated from the asm, checked with objdiff): only straight-line functions (accessors, setters,
// empty functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

struct Unk_VtAt38 {
    u8 unk0[0x38];
    virtual void vf8();
    virtual void vfC();
};

void fn_80357194(u8*, u8*);
void fn_803571BC(u8*, u8*);
void fn_804FE06C(u8*);
void fn_80509E5C(u8*);
void fn_80509EAC(u8*, s32);
void fn_80509F10(u8*, s32);
void fn_8050E020(u8*);
void fn_8050ED10(u8*, s32);
void fn_8050F3A8(u8*, s32, s32);
void fn_8050F430(u8*, s32, s32);
void fn_8050F640(u8*, s32);
void fn_80513A0C(u8*);

void fn_8052E5B4(u8* p, u8* a1) {
    *(u8**)(p + 0x278) = a1;
    *(u32*)(p + 0x284) = *(u32*)(a1 + 0x158);
    *(u32*)(p + 0x288) = *(u32*)(a1 + 0x15c);
    *(u32*)(p + 0x28c) = *(u32*)(a1 + 0x160);
    *(u32*)(p + 0x290) = *(u32*)(a1 + 0x164);
}

void fn_8052E5A8(u8* p, u32 a1, u32 a2) {
    *(u32*)(p + 0x27c) = a1;
    *(u32*)(p + 0x280) = a2;
}

void fn_8052E4D0(u8* p) { ((Unk_VtAt38*)(p))->vfC(); }

void fn_8052E2E8(u8* p, u32 a1) {
    if (a1 != 0) {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x8;
    } else {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) & ~0x8;
    }
}

void fn_8052E2C0(u8* p, u32 a1) {
    if (a1 != 0) {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x10;
    } else {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) & ~0x10;
    }
}

void fn_8052E298(u8* p, u32 a1) {
    if (a1 != 0) {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x20;
    } else {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) & ~0x20;
    }
}

void fn_8052E270(u8* p, u32 a1) {
    if (a1 != 0) {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x80;
    } else {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) & ~0x80;
    }
}

void fn_8052E220(u8* p, u32 a1) {
    if (a1 != 0) {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x4;
    } else {
        *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) & ~0x4;
    }
}

s32 fn_8052DFE0(u8* p) {
    fn_80357194(p, p + 0x1c8);
    fn_8050F430(*(u8**)(p + 0x290), 0, 0);
    fn_8050F3A8(*(u8**)(p + 0x290), 0, 0);
    fn_804FE06C(*(u8**)(p + 0x278));
    *(u32*)(p + 0x24c) = *(u32*)(p + 0x24c) | 0x60;
    return 1;
}

s32 fn_8052DE4C(u8* p) {
    fn_80357194(p, p + 0x220);
    return 1;
}

s32 fn_8052DE10(u8* p) {
    fn_80357194(p, p + 0x3c);
    fn_80513A0C(*(u8**)(p + 0x28c));
    return 1;
}

void fn_8052DCF0(u8* p) { fn_803571BC(p, p + 0x3c); }

void fn_8052DCE8(u8* p) { fn_803571BC(p, p + 0x68); }

void fn_8052DCE0(u8* p) { fn_803571BC(p, p + 0xc0); }

void fn_8052DCD8(u8* p) { fn_803571BC(p, p + 0x144); }

void fn_8052DCD0(u8* p) { fn_803571BC(p, p + 0xec); }

void fn_8052DBD0() {}

void fn_8052DBCC() {}

void fn_8052D83C(u8* p) {
    fn_8050F640(*(u8**)(p + 0x290), 1);
    fn_80509F10(*(u8**)(p + 0x288), 1);
    fn_80509EAC(*(u8**)(p + 0x288), 1);
    *(u32*)(p + 0x250) = 0;
}

void fn_8052CB08() {}

void fn_8052C48C(u8* p) {
    fn_8050ED10(*(u8**)(p + 0x290), 1);
    *(u32*)(p + 0x258) = 0;
}

void fn_8052C388(u8* p) {
    fn_80509E5C(*(u8**)(p + 0x288));
    fn_8050E020(*(u8**)(p + 0x290));
}

void fn_8052C384() {}

void fn_8052C37C(u8* p) { fn_80509E5C(*(u8**)(p + 0x288)); }

}  // extern "C"
