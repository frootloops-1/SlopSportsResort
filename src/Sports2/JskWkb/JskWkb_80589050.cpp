// Resort shared Power Cruising/Wakeboarding engine file 0x80589050-0x8058ACDC: player/object class vtable 0x806E57F8 (factory-created; calls jsk and wkb code).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

// placeholder for an object called through its vtable (vptr at 0x0, slot = offset in the vtable)
struct Unk_V0 {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C();
    virtual void vf30();
};

extern "C" {

void fn_80586440(u8*);
void fn_80597574(u8*);
void fn_8059BADC(u8*);

void fn_80589F74(u8* p) { (*(Unk_V0**)(p + 0x3c))->vf30(); }

void fn_8058965C(u8* p) { fn_80586440(*(u8**)(p + 0x44)); }

void fn_805894C0() {}

void fn_80589488(u8* p) {
    fn_8059BADC(*(u8**)(p + 0x4c));
    fn_80597574(*(u8**)(p + 0x48));
}

void fn_80589404(u8* p, u8 v) { *(u8*)(p + 0x19) = v; }

void fn_80589050() {}

}  // extern "C"
