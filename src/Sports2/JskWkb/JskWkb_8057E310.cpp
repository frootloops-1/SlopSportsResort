// Resort shared Power Cruising/Wakeboarding engine file 0x8057E310-0x8057FC50: scene (RPSysScene-derived vtable 0x806E5360, created for both jsk and wkb by the scene factory) + jsk_cam/wkb_cam tables.
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_80361414(u8*);
void fn_803616C8(u8*);
void fn_80361728(u8*);
void fn_80361848(u8*);
void fn_80361FF0(u8*);
extern u8 lbl_806F2EA0;
extern void* lbl_806E5220[];

void fn_8057F74C() {}

s32 fn_8057F568() { return 2; }

void* fn_8057F560() { return &lbl_806F2EA0; }

s32 fn_8057F40C() { return 195; }

u8* fn_8057EE98(u8* p) {
    fn_80361FF0(p);
    *(void**)(p + 0x62c) = lbl_806E5220;
    return p;
}

void fn_8057E718(u8* p) { fn_80361848(p); }

void fn_8057E714(u8* p) { fn_80361728(p); }

void fn_8057E710(u8* p) { fn_803616C8(p); }

void fn_8057E5F0(u8* p) { fn_80361414(p); }

}  // extern "C"
