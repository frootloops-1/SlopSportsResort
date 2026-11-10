// Resort Power Cruising (jsk) file 0x8058D034-0x8058DBD4: float/buoy object, vtable 0x806E58C0 (jsk_float, WS2_jsk_bouy).
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>

// placeholder for an object called through its vtable (vptr at 0xC, slot = offset in the vtable)
struct Unk_PadC {
    u8 pad[0xC];
};

struct Unk_VC : Unk_PadC {
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
};

extern "C" {

void fn_8058DBD0() {}

void fn_8058DBCC() {}

void fn_8058D04C(u8* p) { (*(Unk_VC**)(p + 0x20))->vf0C(); }

void fn_8058D038(u8* p) { (*(Unk_VC**)(p + 0x20))->vf10(); }

void fn_8058D034() {}

}  // extern "C"
