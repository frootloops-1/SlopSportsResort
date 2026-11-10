// Canoeing (Resort-only), .text 0x80489D84-0x8048BC4C: avatar (WS2_can_ava_*, .sdata "Avatar"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Pack/RPKernel/RPSysEffectBase.h>

extern "C" {

struct Vec3Copy { u32 x, y, z; }; // 12-byte block, copied word by word
u8* fn_8048C82C(u8*, u32);

// Deleting destructor of a class without a base destructor.
void* fn_8048BB94(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

const char* fn_8048BB8C() {
    static char sName[] = "Avatar";
    return sName;
}

void fn_8048B460(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xa8)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0xac)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0xb0)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0xb4)))->forceKill();
    ((RPSysEffect*)(*(u8**)(p + 0xb8)))->forceKill();
}

void fn_8048B458(u8* p) { ((RPSysEffect*)(*(u8**)(p + 0xa8)))->followFade(); }

Vec3Copy fn_80489EBC(const u8* p) {
    u8* q = *(u8**)(p + 0x18);
    u8* r = fn_8048C82C(*(u8**)(q + 0x10), *(u32*)q);
    return *(Vec3Copy*)(r + 0x24);
}

void fn_80489E84(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xac)))->create();
    ((RPSysEffect*)(*(u8**)(p + 0xb0)))->forceKill();
}

void fn_80489E4C(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xb0)))->create();
    ((RPSysEffect*)(*(u8**)(p + 0xac)))->forceKill();
}

void fn_80489E14(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xb4)))->create();
    ((RPSysEffect*)(*(u8**)(p + 0xb8)))->forceKill();
}

void fn_80489DDC(u8* p) {
    ((RPSysEffect*)(*(u8**)(p + 0xb8)))->create();
    ((RPSysEffect*)(*(u8**)(p + 0xb4)))->forceKill();
}

bool fn_80489D84(const u8* p) { return ((RPSysEffect*)*(u8**)(p + 0xb0))->isAlive(); }

}  // extern "C"
