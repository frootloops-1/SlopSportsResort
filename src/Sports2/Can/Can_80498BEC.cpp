// Canoeing (Resort-only), .text 0x80498BEC-0x80499CA4. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

BOOL fn_80497D38(u8* p);
extern u8* lbl_806F5838; // Config instance
void fn_80497D40(u8* p);
void fn_80497D48(u8* p);
void fn_80497EBC(u8* p);
void fn_8049855C(u8* p);
void fn_80498260(u8* p);
void fn_804982D4(u8* p);
void fn_80498438(u8* p);
void fn_80498524(u8* p);
void fn_80497D50(u8*);
void fn_80497D94(u8*, u32);
void fn_80498124(u8*);
void fn_80498130(u8*);
void fn_8049813C(u8*, u32, u32);
void fn_804981D4(u8*, u32, u32);
void fn_80498980(u8*);

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80499B3C(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80498524(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80499AE0(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80498438(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498FCC(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_804982D4(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498F70(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80498260(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498F14(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_8049855C(((u8**)(p + 0x18))[i]);
    }
}

void fn_80498F04(u8* p, s32 a1) { fn_80498130(*(u8**)(p + a1 * 4 + 0x18)); }

void fn_80498EF4(u8* p, s32 a1) { fn_80498124(*(u8**)(p + a1 * 4 + 0x18)); }

void fn_80498EE4(u8* p, s32 a1) { fn_80498980(*(u8**)(p + a1 * 4 + 0x18)); }

// Smallest value at 0x14 over the active players.
s32 fn_80498EA0(u8* p) {
    s32 min = 9999;
    for (s32 i = 0; i < *(s32*)(lbl_806F5838 + 0x18) + 1; i++) {
        u8* q = ((u8**)(p + 0x18))[i];
        if (*(s32*)(q + 0x14) < min) {
            min = *(s32*)(q + 0x14);
        }
    }
    return min;
}

// Smallest value at 0x18 over the active players.
s32 fn_80498E5C(u8* p) {
    s32 min = 9999;
    for (s32 i = 0; i < *(s32*)(lbl_806F5838 + 0x18) + 1; i++) {
        u8* q = ((u8**)(p + 0x18))[i];
        if (*(s32*)(q + 0x18) < min) {
            min = *(s32*)(q + 0x18);
        }
    }
    return min;
}

// Raises every active player's value at 0x18 to at least v.
void fn_80498E20(u8* p, s32 v) {
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (s32 i = 0; i < n; i++) {
        u8* q = ((u8**)(p + 0x18))[i];
        if (*(s32*)(q + 0x18) < v) {
            *(s32*)(q + 0x18) = v;
        }
    }
}

void fn_80498E10(u8* p, s32 a1) { fn_80497D50(*(u8**)(p + a1 * 4 + 0x18)); }

u32 fn_80498DFC(u8* p, s32 a1) { return *(u32*)(*(u8**)(p + a1 * 4 + 0x18) + 0x30); }

void fn_80498DE0(u8* p, s32 a1, u32 a2, u32 a3) { fn_804981D4(*(u8**)(p + a1 * 4 + 0x18), a2, a3); }

void fn_80498DC4(u8* p, s32 a1, u32 a2, u32 a3) { fn_8049813C(*(u8**)(p + a1 * 4 + 0x18), a2, a3); }

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498D68(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80497EBC(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498CF4(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80497D48(((u8**)(p + 0x18))[i]);
    }
}

// Calls the per-player function for every active player (player count from Config 0x18).
void fn_80498C98(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        fn_80497D40(((u8**)(p + 0x18))[i]);
    }
}

// TRUE if any active player's check succeeds.
BOOL fn_80498C28(u8* p) {
    s32 i;
    s32 n = *(s32*)(lbl_806F5838 + 0x18) + 1;
    for (i = 0; i < n; i++) {
        if (fn_80497D38(((u8**)(p + 0x18))[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

}  // extern "C"
