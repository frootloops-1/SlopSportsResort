// Swf_80615BEC: Resort Swordplay unit 0x80615BEC-0x8061F194 (Resort-only, no Wii Sports twin).
// Speed Slice cuttable models: "切断できるモデル( 複数シェイプ )" (dividable model, multi-shape), "DividableModelバッファ",
// "切断できるモデル", "トライアングルバッファ" (triangle buffer), "投影データ" (projection data); vtables
// 0x806ED478-0x806ED504, name strings 0x806ED518-0x806ED580. Probably several source files sharing one
// .sdata2 pool would be impossible, so this is one file.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>

// MATCH-PENDING (R17) #18: file-scope auto_inline off keeps small same-file callees out of line
#pragma auto_inline off

#define F32(p, o) (*(f32*)((u8*)(p) + (o)))
#define S32(p, o) (*(s32*)((u8*)(p) + (o)))
#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define PTR(p, o) (*(void**)((u8*)(p) + (o)))

struct Unk_Node {
    Unk_Node* next;
    Unk_Node* prev;
};

struct Unk_Words4 {
    u32 w0, w1, w2, w3;
};

extern "C" {

void fn_8061AE08(void*);
s32 fn_80619C88(u8*);
void fn_8061C8E8(u8*, void*);
void fn_8061E944(u8*);
extern char lbl_806ED518[];
extern char lbl_806ED53C[];
extern char lbl_806ED554[];
extern char lbl_806ED568[];
extern char lbl_806ED580[];

char* fn_8061F170() { return lbl_806ED518; }

char* fn_8061F164() { return lbl_806ED53C; }

char* fn_8061F158() { return lbl_806ED554; }

char* fn_8061F14C() { return lbl_806ED568; }

char* fn_8061F140() { return lbl_806ED580; }

void* fn_8061F100(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8061F0C0(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8061F080(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_8061F040(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8061F03C() {}

f32 fn_8061EA64(u8* p) {
    f32 sum = 0.0f;
    for (s32 i = S32(p, 0x48); --i >= 0;) {
        sum += F32(((u8**)PTR(p, 0x40))[i], 0x60);
    }
    return sum;
}

void fn_8061EA3C(u8* p, f32 f) {
    for (s32 i = S32(p, 0x48); --i >= 0;) {
        F32(((u8**)PTR(p, 0x40))[i], 0x70) = f;
    }
}

void fn_8061EA14(u8* p, f32 f) {
    for (s32 i = S32(p, 0x48); --i >= 0;) {
        F32(((u8**)PTR(p, 0x40))[i], 0x74) = f;
    }
}

void fn_8061E910(u8* p) {
    fn_8061E944(p);
    S32(p, 0x48) = 0;
}

BOOL fn_8061E5A0(u8* p) {
    for (s32 i = S32(p, 0x48); --i >= 0;) {
        if (PTR(((u8**)PTR(p, 0x40))[i], 0x1ec) != NULL) {
            return FALSE;
        }
    }
    return TRUE;
}

u8* fn_8061E454(u8* p) { return p + 0xc; }

u8* fn_8061E388(u8* p) { return p + 0x18; }

void fn_8061BB6C(u8*, void*, void*);

void fn_8061DBAC(u8* p, s32 idx, u8* x) {
    u8* e = (u8*)PTR(PTR(PTR(p, 0x8), 0x18), 0xe8) + idx * 12;
    u8* found = NULL;
    for (s32 i = S32(p, 0x48); --i >= 0;) {
        u8* o = ((u8**)PTR(p, 0x40))[i];
        if (U8(e, 0x8) == S32(o, 0x90)) {
            found = o;
            break;
        }
    }
    fn_8061BB6C(x, e, found);
}

void fn_80616EC4(u8*);

void fn_8061DBA0(u8* p) { fn_80616EC4((u8*)PTR(PTR(p, 0x8), 0x18)); }

void fn_8061CE48(u8* p, const Unk_Words4* v) {
    *(Unk_Words4*)(p + 0x94) = *v;
    S32(p, 0xa4) = 1;
}

void fn_8061BB18(u8* p, u8** q);

void fn_8061BB6C(u8* p, void* a, void* b) {
    fn_8061C8E8(p, b);
    fn_8061BB18(p, (u8**)a);
}

void fn_8061AEC0(u8* p, u8* n);

void fn_8061BB18(u8* p, u8** q) {
    u8* cur;
    u8* n = *q;
    while ((cur = n) != NULL) {
        n = (u8*)PTR(cur, 0x7c);
        fn_8061AEC0(p, cur);
    }
    *q = NULL;
}

void fn_8061BAC4(u8* p, u8* q) {
    u8* cur;
    u8* n = (u8*)PTR(q, 0x1ec);
    while ((cur = n) != NULL) {
        n = (u8*)PTR(cur, 0x7c);
        fn_8061AEC0(p, cur);
    }
    PTR(q, 0x1ec) = NULL;
}

void fn_8061BA74(u8* p) {
    if (fn_80619C88(p) == 0) {
        fn_8061AE08(p);
    } else {
        S32(p, 0x208) = 1;
        S32(PTR(p, 0x1e8), 0x1c) = 1;
    }
}

void fn_8061AEC0(u8* p, u8* n) {
    PTR(n, 0x7c) = PTR(p, 0x1ec);
    PTR(p, 0x1ec) = n;
    S32(p, 0x1f8) = S32(p, 0x1f8) + 1;
}

void fn_80619C64(void*, f32* a, f32* b) {
    a[0] = -10.0f;
    a[1] = -10.0f;
    a[2] = -10.0f;
    b[0] = 10.0f;
    b[1] = 10.0f;
    b[2] = 10.0f;
}

void fn_80618F40(u16* p, u16 v) { *p |= v; }

u8* fn_80618584(u8* p, s32 k) {
    if (S32(p, 0x14) <= k) {
        return NULL;
    }
    u8* n = (u8*)PTR(p, 0x10);
    if (n == NULL) {
        return NULL;
    }
    PTR(p, 0x10) = PTR(n, 0x20);
    PTR(n, 0x20) = NULL;
    S32(p, 0x14) = S32(p, 0x14) - 1;
    return n;
}

void fn_80618538(u8* p, u8* n) {
    fn_8061AE08(n);
    PTR(n, 0x20) = PTR(p, 0x10);
    PTR(p, 0x10) = n;
    S32(p, 0x14) = S32(p, 0x14) + 1;
}

void fn_806172C0() {}

void fn_806172B4(u8* p) { *(u16*)(p + 0x90) = 0; }

void fn_806172B0() {}

void fn_80616EC4(u8* p) {
    for (u8* e = (u8*)PTR(p, 0xe8); e < (u8*)PTR(p, 0xec); e += 12) {
        u8* cur;
        u8* n = *(u8**)e;
        while ((cur = n) != NULL) {
            n = (u8*)PTR(cur, 0x7c);
            PTR(cur, 0x7c) = PTR(p, 0x14);
            PTR(p, 0x14) = cur;
        }
    }
    PTR(p, 0xec) = PTR(p, 0xe8);
}

void fn_80615C34(u8* p, Unk_Node* n);
void fn_80615BEC(u8* p, Unk_Node* n);

void fn_80616970(u8* p, u8* q) {
    if (U8(q, 0x3a) != 0) {
        fn_80615C34(p + 0x34, (Unk_Node*)q);
    } else {
        fn_80615BEC(p + 0x34, (Unk_Node*)q);
    }
}

u8* fn_80615EA4(u8* p, BOOL check) {
    if (check && S32(p, 0x18) <= S32(p, 0x30) * 2) {
        return NULL;
    }
    u8* n = (u8*)PTR(p, 0x10);
    if (n == NULL) {
        return NULL;
    }
    PTR(p, 0x10) = PTR(n, 0x7c);
    PTR(n, 0x7c) = NULL;
    S32(p, 0x18) = S32(p, 0x18) - 1;
    return n;
}

u8* fn_80615D80(u8* p) {
    u8* n = (u8*)PTR(p, 0xf8);
    if (n == NULL) {
        return NULL;
    }
    PTR(p, 0xf8) = PTR(n, 0xc);
    PTR(n, 0xc) = NULL;
    S32(p, 0xfc) = S32(p, 0xfc) - 1;
    return n;
}

void fn_80615D64(u8* p, u8* n) {
    PTR(n, 0xc) = PTR(p, 0xf8);
    PTR(p, 0xf8) = n;
    S32(p, 0xfc) = S32(p, 0xfc) + 1;
}

Unk_Node* fn_80615C7C(u8* p) {
    Unk_Node* n = *(Unk_Node**)(p + 0x78);
    *(Unk_Node**)(p + 0x78) = n->next;
    if (n->next != NULL) {
        n->next->prev = (Unk_Node*)(p + 0x78);
    }
    n->next = *(Unk_Node**)p;
    n->prev = (Unk_Node*)p;
    if (*(Unk_Node**)p != NULL) {
        (*(Unk_Node**)p)->prev = n;
    }
    *(Unk_Node**)p = n;
    return n;
}

void fn_80615C34(u8* p, Unk_Node* n) {
    n->prev->next = n->next;
    if (n->next != NULL) {
        n->next->prev = n->prev;
    }
    n->next = *(Unk_Node**)(p + 0x3c);
    n->prev = (Unk_Node*)(p + 0x3c);
    if (*(Unk_Node**)(p + 0x3c) != NULL) {
        (*(Unk_Node**)(p + 0x3c))->prev = n;
    }
    *(Unk_Node**)(p + 0x3c) = n;
}

void fn_80615BEC(u8* p, Unk_Node* n) {
    n->prev->next = n->next;
    if (n->next != NULL) {
        n->next->prev = n->prev;
    }
    n->next = *(Unk_Node**)(p + 0x78);
    n->prev = (Unk_Node*)(p + 0x78);
    if (*(Unk_Node**)(p + 0x78) != NULL) {
        (*(Unk_Node**)(p + 0x78))->prev = n;
    }
    *(Unk_Node**)(p + 0x78) = n;
}

}  // extern "C"
