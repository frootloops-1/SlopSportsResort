// Canoeing (Resort-only), .text 0x804A9C80-0x804AE800: singleton "SequenceMgr". First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_804A9C80(u8* p, s32 a, u32 b, u32 c);
BOOL fn_804AAC34(u8* p);
extern u8* lbl_806F5838; // Config instance
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
u8* fn_804AA09C(u8* p); // ctor
extern void* lbl_806F58E4; // heap
void fn_8035D6C8(u8*);
void fn_804A9DC4(u8* p);
void fn_804A9DD0(u8* p);
void fn_804AA7A0(u8* p);
extern u8* lbl_806F58E0;
extern u8 lbl_806DC8F8[];
extern u8 lbl_806DC910[];
extern u8 lbl_806DC940[];
extern u8 lbl_806DC950[];
extern u8 lbl_806DC960[];
extern u8 lbl_806DC970[];
extern u8 lbl_806DC980[];
extern u8 lbl_806DC990[];
extern u8 lbl_806DC9A0[];
extern u8 lbl_806DC9B0[];
extern u8 lbl_806DC9C0[];
extern u8 lbl_806DC9D0[];
extern u8 lbl_806DC9E0[];
extern u8 lbl_806DC9F0[];
extern u8 lbl_806DCA00[];
extern u8 lbl_806DCA10[];
extern u8 lbl_806DCA20[];

void fn_804AAB3C(u8* p) {
    fn_804A9DD0(p);
    fn_804A9DC4(p);
}

u8* fn_804AA900(u8* p) {
    fn_8035D6C8(p);
    *(u8**)(p) = lbl_806DC8F8;
    return p;
}

void fn_804AA8F0(u8* p) { *(u8**)(p) = lbl_806DC960; }

void fn_804AA8E0(u8* p) { *(u8**)(p) = lbl_806DC950; }

void fn_804AA8D0(u8* p) { *(u8**)(p) = lbl_806DC940; }

void fn_804AA8C0(u8* p) { *(u8**)(p) = lbl_806DCA20; }

void fn_804AA8B0(u8* p) { *(u8**)(p) = lbl_806DCA10; }

void fn_804AA7EC(u8* p) { *(u8**)(p) = lbl_806DC9D0; }

void fn_804AA7A0(u8* p) { *(u8**)(p) = lbl_806DC910; }

void fn_804AA754(u8* p) { *(u8**)(p) = lbl_806DC9A0; }

void fn_804AA744(u8* p) { *(u8**)(p) = lbl_806DC990; }

void fn_804AA734(u8* p) { *(u8**)(p) = lbl_806DC980; }

void fn_804AA724(u8* p) { *(u8**)(p) = lbl_806DC970; }

// Deleting destructor of a class without a base destructor.
void* fn_804AA67C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804AA000(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F58E0 == NULL && lbl_806F58E4 == NULL, "SequenceMgr");
    lbl_806F58E4 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x28, pHeap, 4);
        if (p != NULL) {
            p = fn_804AA09C((u8*)p);
        }
        lbl_806F58E0 = (u8*)p;
    } else {
        void* p = operator new(0x28);
        if (p != NULL) {
            p = fn_804AA09C((u8*)p);
        }
        lbl_806F58E0 = (u8*)p;
    }
}

void fn_804A9FF0() {
    lbl_806F58E0 = NULL;
    lbl_806F58E4 = NULL;
}

void fn_804A9F88() {}

void fn_804A9F7C(u32 p) { *(u32*)(lbl_806F58E0 + 0x24) = p; }

BOOL fn_804A9F4C() {
    BOOL r = FALSE;
    if (*(s32*)(lbl_806F5838 + 0x14) == 0 && (*(u8**)(lbl_806F58E0 + 0x1c))[0x146] != 0) {
        r = TRUE;
    }
    return r;
}

BOOL fn_804A9F1C() {
    BOOL r = FALSE;
    if (*(s32*)(lbl_806F5838 + 0x14) == 0 && (*(u8**)(lbl_806F58E0 + 0x1c))[0x147] != 0) {
        r = TRUE;
    }
    return r;
}

BOOL fn_804A9EC8() {
    BOOL r = FALSE;
    if (*(s32*)(lbl_806F5838 + 0x14) == 0 && fn_804AAC34(*(u8**)(lbl_806F58E0 + 0x1c))) {
        r = TRUE;
    }
    return r;
}

BOOL fn_804A9E98() {
    BOOL r = FALSE;
    if (*(s32*)(lbl_806F5838 + 0x14) == 0 && (*(u8**)(lbl_806F58E0 + 0x1c))[0x128] != 0) {
        r = TRUE;
    }
    return r;
}

// Deleting destructor of a class without a base destructor.
void* fn_804A9DFC(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_804A9DE8(u8* p) {
    *(u32*)(p + 0x8) = 0;
    *(u8*)(p + 0xe) = 1;
}

void fn_804A9DD0(u8* p) {
    *(u32*)(p + 0x4) = 0;
    *(u8*)(p + 0xc) = 0;
    *(u8*)(p + 0xd) = 0;
    *(u8*)(p + 0x14) = 0;
}

void fn_804A9DC4(u8* p) { *(u8*)(p + 0x14) = 1; }

BOOL fn_804A9DAC(const u8* p) { return *(s32*)(p + 0x4) == *(s32*)(p + 0x8); }

BOOL fn_804A9D6C(u8* p) {
    if ((*(s32*)(p + 0x4))++ == *(s32*)(p + 0x8)) {
        BOOL first = p[0xd] == 0;
        p[0xd] = 1;
        p[0xc] = first;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_804A9D3C(u8* p) {
    if (p[0xc] != 0) {
        p[0xe] = 1;
        (*(s32*)(p + 0x8))++;
        return TRUE;
    }
    return FALSE;
}

void fn_804A9D30(u8* p, u32 a1, u32 a2) { fn_804A9C80(p, a1, 1, a2); }

void fn_804A9D1C(u8* p, u32 b, u32 c) { fn_804A9C80(p, 0x7fffffff, b, c); }

}  // extern "C"
