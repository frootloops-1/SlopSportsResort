// Canoeing (Resort-only), .text 0x804A8754-0x804A95B8: layout 65500_can_PointCount. First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>
#include <Sports2/Unk_StateMachine.h>

// Owner of a state machine (placeholder: polymorphic, layout unknown here).
class Unk_806DC580 {
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
void fn_8026F7FC(u8*, u32, u32, s32, s32, s32, u32, s32);
void fn_8026FEF0(u8*, s32, s32);
void fn_802700EC(u8*);
void fn_802A609C(u8*);
void fn_804A9088(u8*, s32, s32, s32, u32);
char* strncpy(char* dst, const char* src, unsigned long n);
extern u8 __ptmf_null[];
extern u8 lbl_80680640[];
extern u8 lbl_806DC2D0[];
extern u8 lbl_806DC310[];

void fn_804A9264() {}

void fn_804A8F30(u8* p) {
    fn_802700EC(p + 0x94);
    fn_802A609C(p);
}

u8* fn_804A8E38(u8* p) { return p + 0x64; }

u8* fn_804A8E30(u8* p) { return p + 0x64; }

void fn_804A8DDC(u8* p) {
    ((Unk_VtAt30*)(p))->vf64();
    ((Unk_StateMachine<Unk_806DC580>*)(p + 0x64))->calc();
    ((Unk_VtAt30*)(p))->vf68();
}

u8* fn_804A8DD4(u8* p) { return p + 0x64; }

u8* fn_804A8DCC(u8* p) { return p + 0x64; }

u8* fn_804A8B78(u8* p, u32 a1) {
    fn_804A9088(p, 3, 5, 0, a1);
    const char* nm = (const char*)(lbl_80680640 + 0x79);
    *(u8**)(p + 0x30) = lbl_806DC310;
    *(u8**)(p + 0x18) = lbl_806DC310 + 0x8;
    *(u8**)(p + 0x94) = lbl_806DC310 + 0x78;
    *(u8**)(p + 0x98) = lbl_806DC310 + 0x88;
    strncpy((char*)(p + 0x34), nm, 32);
    ((Unk_StateMachine<Unk_806DC580>*)(p + 0x64))->setState(*(Unk_StateMachine<Unk_806DC580>::StateFn*)__ptmf_null, *(Unk_StateMachine<Unk_806DC580>::StateFn*)lbl_806DC2D0, 0);
    ((Unk_StateMachine<Unk_806DC580>*)(p + 0x64))->setState(*(Unk_StateMachine<Unk_806DC580>::StateFn*)(lbl_806DC2D0 + 0xc), *(Unk_StateMachine<Unk_806DC580>::StateFn*)(lbl_806DC2D0 + 0x18), 1);
    ((Unk_StateMachine<Unk_806DC580>*)(p + 0x64))->setState(*(Unk_StateMachine<Unk_806DC580>::StateFn*)(lbl_806DC2D0 + 0x24), *(Unk_StateMachine<Unk_806DC580>::StateFn*)(lbl_806DC2D0 + 0x30), 2);
    *(u32*)(p + 0x104) = 0;
    return p;
}

void fn_804A8964() {}

void fn_804A8864(u8* p) {
    fn_8026FEF0(p + 0x94, 1, 1);
    u8* t1 = fn_8026F6AC(p + 0x94, 1);
    fn_8025EC94(t1);
}

void fn_804A87CC(u8* p) {
    fn_8026FEF0(p + 0x94, 2, 0);
    u8* t1 = fn_8026F6AC(p + 0x94, 2);
    fn_8025EC94(t1);
}

void fn_804A8754(u8* p) { ((Unk_StateMachineBase*)(p + 0x64))->request(0); }

}  // extern "C"

// MATCH-PENDING (R17) #28: explicit instantiation stands in for unwritten callers of the state machine.
template Unk_StateMachine<Unk_806DC580>::Unk_StateMachine(Unk_806DC580*, s32, EGG::Heap*);
template void Unk_StateMachine<Unk_806DC580>::setState(const StateFn&, const StateFn&, const StateFn&, s32);
