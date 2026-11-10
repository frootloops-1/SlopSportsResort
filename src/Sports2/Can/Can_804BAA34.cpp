// Canoeing (Resort-only), .text 0x804BAA34-0x804BAFE0: layout 65505_can_poseCheck. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_801ED220(u8*);
u32 fn_8027CCC0(u8*);
void fn_80371668(u8*, s32, u8*, u8*, s32, s32, u8*);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 lbl_80680DC8[];
extern u8 lbl_806DD498[];

void fn_804BAF48(u8* p) {
    *(u16*)(p + 0x13c) = *(u16*)(p + 0x13c) & ~0x4;
    fn_801ED220(p);
}

void fn_804BAF44() {}

u8* fn_804BAEB0(u8* p, u8* a1) {
    fn_80371668(p, 1, lbl_80680DC8 + 0x70, lbl_80680DC8 + 0x7d, 1, 0, a1);
    const char* nm = (const char*)(lbl_80680DC8 + 0x91);
    *(u8**)(p + 0x30) = lbl_806DD498;
    *(u8**)(p + 0x18) = lbl_806DD498 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DD498 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DD498 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    u32 t2 = fn_8027CCC0(a1);
    *(u32*)(p + 0x128) = t2;
    return p;
}

void fn_804BABAC() {}

}  // extern "C"
