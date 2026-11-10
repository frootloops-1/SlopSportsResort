// Resort Power Cruising (jsk) file 0x805982C0-0x80598F80: jsk HUD helper: vtables 0x806E5C28, 0x806E5C90/0x806E5CC0/0x806E5D38.
// First pass (generated from the asm, checked with objdiff): only leaf accessors, setters, empty
// functions, tail calls and vtable calls are written; struct offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806E5D38 {
public:
    virtual void vf8();
};

// placeholder for an object called through its vtable (vptr at 0x30, slot = offset in the vtable)
struct Unk_Pad30 {
    u8 pad[0x30];
};

struct Unk_V30 : Unk_Pad30 {
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
    virtual void vf34();
    virtual void vf38();
    virtual void vf3C();
    virtual void vf40();
    virtual void vf44();
    virtual void vf48();
    virtual void vf4C();
    virtual void vf50();
    virtual void vf54();
    virtual void vf58();
    virtual void vf5C();
    virtual void vf60();
    virtual void vf64();
    virtual void vf68();
    virtual void vf6C();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
    virtual void vf80();
    virtual void vf84();
    virtual void vf88();
    virtual void vf8C();
    virtual void vf90();
    virtual void vf94();
    virtual void vf98();
    virtual void vf9C();
    virtual void vfA0();
    virtual void vfA4();
    virtual void vfA8();
    virtual void vfAC();
    virtual void vfB0();
    virtual void vfB4();
    virtual void vfB8();
    virtual void vfBC();
    virtual void vfC0();
    virtual void vfC4();
    virtual void vfC8();
    virtual void vfCC();
    virtual void vfD0();
    virtual void vfD4();
    virtual void vfD8();
    virtual void vfDC();
    virtual void vfE0();
    virtual void vfE4();
    virtual void vfE8();
    virtual void vfEC();
    virtual void vfF0();
    virtual void vfF4();
    virtual void vfF8();
};

extern "C" {

void fn_801ED220(u8*);
void fn_80360F3C(u8*);
void fn_805AFFB8(u8*);
void fn_805B0094(u8*);
extern void* lbl_806E5C28[];

u8* fn_80598B88(u8* p) { return p + 0x64; }

u8* fn_80598B80(u8* p) { return p + 0x64; }

void fn_805985FC(u8* p) { *(u8*)(p + 0xbd) = 1; }

void fn_805985E8(u8* p) { (*(Unk_V30**)(p + 0xa0))->vf28(); }

void fn_805984E0(u8* p) { (*(Unk_V30**)(p + 0xa8))->vfF4(); }

void fn_805984DC(u8* p) { fn_801ED220(p); }

void fn_805984C8(u8* p) { (*(Unk_V30**)(p + 0xa8))->vfF8(); }

u8 fn_805984BC(u8* p) { return *(u8*)(*(u8**)(p + 0xa8) + 0xd0); }

void fn_805984A8(u8* p) { (*(Unk_V30**)(p + 0xac))->vfF4(); }

void fn_80598494(u8* p) { (*(Unk_V30**)(p + 0xac))->vfF8(); }

void fn_8059848C(u8* p) { fn_805AFFB8(*(u8**)(p + 0xac)); }

void fn_80598410(u8* p) { fn_805B0094(*(u8**)(p + 0xac)); }

void fn_805983FC(u8* p) { (*(Unk_V30**)(p + 0xac))->vf48(); }

u8 fn_805983E0(u8* p) { return *(u8*)(*(u8**)(p + 0xb0) + 0x112); }

u8 fn_805983D4(u8* p) { return *(u8*)(*(u8**)(p + 0xb0) + 0x113); }

u8* fn_80598398(u8* p) {
    fn_80360F3C(p);
    *(void**)(p + 0x10) = lbl_806E5C28;
    return p;
}

void fn_80598354() {}

void fn_80598350() {}

void fn_8059834C() {}

void fn_805982D8() {}

void fn_805982D4() {}

void fn_805982D0() {}

void fn_805982CC() {}

void fn_805982C8() {}

void fn_805982C4() {}

void fn_805982C0() {}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806E5D38>::Unk_StateMachine(Unk_806E5D38*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806E5D38>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
template void Unk_StateMachine<Unk_806E5D38>::calc();
