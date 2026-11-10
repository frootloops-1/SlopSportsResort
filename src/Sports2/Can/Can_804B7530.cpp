// Canoeing (Resort-only), .text 0x804B7530-0x804B888C: layout 65501_can_caution. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806DCF00 {
public:
    virtual void vf8();
};

extern "C" {

struct Unk_VtAt30 {
    u8 unk0[0x30];
    virtual void vf8();
    virtual void vfC();
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
};

void fn_8025EC94(u8*);
u8* fn_8026F6AC(u8*, s32);
void fn_8026FEF0(u8*, s32, s32);
void fn_8026FFE0(u8*);
void fn_802700EC(u8*);
void fn_8027765C(u8*, u8, s32);
void fn_80277724(u8*);
void fn_802A609C(u8*);

void fn_804B8530() {}

void fn_804B84BC() {}

void fn_804B8298(u8* p) {
    fn_8027765C(p + 0x94, *(u8*)(p + 0xd0), 1);
    fn_8026FFE0(p + 0x94);
    ((Unk_StateMachineBase*)(p + 0x64))->request(*(s32*)(p + 0xfc) + 3);
}

void fn_804B81EC(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

void fn_804B8154(u8* p) { fn_80277724(p + 0x94); }

u8* fn_804B80EC(u8* p) { return p + 0x64; }

u8* fn_804B80E4(u8* p) { return p + 0x64; }

void fn_804B8090(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806DCF00>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_804B8088(u8* p) { return p + 0x64; }

u8* fn_804B8080(u8* p) { return p + 0x64; }

void fn_804B7BD8() {}

void fn_804B7B88(u8* p) {
    fn_8026FEF0(p + 0x94, 1, 0);
    u8* t1 = fn_8026F6AC(p + 0x94, 1);
    fn_8025EC94(t1);
    *(u16*)(p + 0x12c) = 0;
}

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806DCF00>::Unk_StateMachine(Unk_806DCF00*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806DCF00>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
