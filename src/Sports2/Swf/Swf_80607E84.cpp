// Swf_80607E84: Resort Swordplay unit (Resort-only, no Wii Sports twin). First pass: generated leaf/tail functions.

#include <types.h>

// placeholder: virtual call at vtable byte offset N is vfN (MWCC vtable header is 8 bytes).
extern "C" {


void fn_80643B0C(u8*);
extern u8 lbl_806EBEC8[];
extern void* lbl_806EBE78[];

u8* fn_806087D8() { return lbl_806EBEC8; }

void* fn_80608798(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void* fn_80608758(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

f32 fn_80607FCC() { return 1e+02f; }


// ---- hand-written (first pass) ----
extern u8* lbl_806F5FF0;

void fn_8060858C(u8* p) {
    if (*(s32*)(p + 0x10) != 1) {
        return;
    }
    if (*(s32*)(*(u8**)(lbl_806F5FF0 + 0x190) + 0x1c) != 2) {
        *(s32*)(p + 0x18) -= 1;
    }
    if (*(s32*)(p + 0x18) < 0) {
        *(s32*)(p + 0x10) = 2;
    }
}

void fn_80608544(u8* p, s32 b) {
    s32* e = (s32*)(p + 0x1c + *(s32*)(p + 0x14) * 4);
    if (*e == 3) {
        *e = b ^ 1;
    } else if (*e == b) {
        *e = 2;
    }
    *(s32*)(p + 0x3c + b * 4) = 1;
}

int fn_806084CC(u8* p) { return *(s32*)(p + 0x10) == 1; }

void fn_8060848C(u8* p, u8* q, s32, s32 c) {
    if (*(s32*)(p + 0x10) != 1) {
        return;
    }
    if (*(s32*)(q + 0xc) == 0) {
        if (c != 0) {
            *(s32*)(p + 0x50) = 0;
        }
    } else {
        if (c == 0) {
            *(s32*)(p + 0x50) = 0;
        }
    }
}

void fn_80608474(u8* p, u8* q) {
    if (*(s32*)(q + 0xc) == 0) {
        *(s32*)(p + 0x50) = 0;
    }
}

s32 fn_806082DC(u8* p, s32 b) {
    s32 n = 0;
    s32 v = b != 0;
    for (s32 i = 3; i >= 0; i--) {
        if (v == *(s32*)(p + 0x1c + i * 4)) {
            n++;
        }
    }
    return n;
}

int fn_80607F8C(u8*) {
    u8* s = *(u8**)(lbl_806F5FF0 + 0x170);
    for (s32 i = 1; i >= 0; i--) {
        if (*(s32*)(*(u8**)(s + 0x20 + i * 4) + 0xd0) == 1) {
            return 0;
        }
    }
    return 1;
}

void fn_80607F68(u8* p, s32 i, f32 f) {
    if (*(s32*)(p + 0x10) == 1) {
        *(f32*)(p + 0x2c + i * 4) += f;
    }
}


void fn_80643B0C(u8*);
int fn_80328904(u8*, s32);

u8* fn_806086E4(u8* p) {
    fn_80643B0C(p);
    *(void***)p = lbl_806EBE78;
    if (fn_80607F8C(p) && fn_80328904(lbl_806F5FF0, 4)) {
        *(s32*)(p + 0x44) = 1;
    } else {
        *(s32*)(p + 0x44) = 0;
    }
    return p;
}

}  // extern "C"
