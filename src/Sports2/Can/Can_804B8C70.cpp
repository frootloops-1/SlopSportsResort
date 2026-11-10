// Canoeing (Resort-only), .text 0x804B8C70-0x804B9448: camera animations (WS2_can_cam_op/ed). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8036F03C(u8*, s32, s32);
void fn_803701C4(u8*);
void fn_80370644(u8*, u32);
void fn_8048880C(u8*, s32);
void fn_80488810(u8*);
void fn_804944D0(u8*);

s32 fn_804B9294(u8* p) {
    fn_804944D0(p);
    *(u32*)(p + 0x8c) = 7;
    *(u32*)(p + 0xac) = 0;
    *(u32*)(p + 0xb0) = 0;
    *(u32*)(p + 0xb4) = 0;
    *(u8*)(p + 0xb8) = 0;
    return 7;
}

void fn_804B8DF4(u8* p, u32 a1) {
    *(u32*)(p + 0x8c) = a1;
    *(u32*)(p + 0xac) = 0;
    *(u32*)(p + 0xb0) = 0;
    *(u32*)(p + 0xb4) = 0;
    *(u8*)(p + 0xb8) = 0;
}

void fn_804B8DD4(u8* p, u32 a1, u8* a2) {
    *(u32*)(p + 0x8c) = a1;
    *(u32*)(p + 0xac) = 0;
    *(u8**)(p + 0xb0) = a2;
    *(u32*)(p + 0xb4) = *(u32*)(a2 + 0x70);
    *(u8*)(p + 0xb8) = 0;
}

void fn_804B8DB4(u8* p, u32 a1) {
    *(u32*)(p + 0x8c) = a1;
    *(u32*)(p + 0xac) = 0;
    *(u32*)(p + 0xb0) = 0;
    *(u32*)(p + 0xb4) = 0;
    *(u8*)(p + 0xb8) = 1;
}

BOOL fn_804B8D8C(const u8* p) {
    return *(s32*)(p + 0xac) >= ((s32*)(p + 0x90))[*(s32*)(p + 0x8c)];
}

void fn_804B8CE8(u8* p) {
    fn_80488810(p);
    fn_8036F03C(*(u8**)(p + 0x8), 0, 1);
}

void fn_804B8CA8(u8* p, u32 a1) {
    fn_8048880C(p, 0);
    fn_80370644(*(u8**)(p + 0x8), a1);
}

void fn_804B8CA0(u8* p) { fn_803701C4(*(u8**)(p + 0x8)); }

u8* fn_804B8C94(u8* p) { return *(u8**)(p + 0x8) + 0x10; }

u8* fn_804B8C88(u8* p) { return *(u8**)(p + 0x8) + 0x68; }

u8* fn_804B8C7C(u8* p) { return *(u8**)(p + 0x8) + 0x8c; }

u8* fn_804B8C70(u8* p) { return *(u8**)(p + 0x8) + 0x98; }

}  // extern "C"
