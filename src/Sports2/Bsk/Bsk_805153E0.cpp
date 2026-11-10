// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

// Placeholder for an object called through its vtable (slot = byte offset in the vtable).
struct UnkVObj {
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
};

extern "C" {

void fn_80515938(void* p, void* a);
void fn_8051558C(void* p, void* a);
void fn_805153E0(void* p, void* a);
void fn_80356CA0(void* p);
u32 lbl_806F26E8 = 0xB4;
// Deleting destructor of a class without a base destructor.
void* fn_80516820(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_8051655C(u8* p, u8 b) {
    p[0x3C] = b;
    (*(u8**)(p + 0x50))[0x98] = b;
    (*(u8**)(p + 0x58))[0x138] = b;
}

void fn_80515FD8(u8* p) {
    (*(u8**)(p + 0x8))[0x6E] = lbl_806F26E8;
    fn_80356CA0(*(void**)(p + 0x4));
    (*(UnkVObj**)(p + 0x50))->vf34();
}

void fn_80515FC4(u8* p) { (*(UnkVObj**)(p + 0x58))->vf34(); }

void fn_80515F70(u8* p, void* a) {
    if (p[0x3C]) {
        fn_80515938(p, a);
        fn_8051558C(p, a);
        fn_805153E0(p, a);
    }
}

int fn_80515B28() { return 0; }

} // extern "C"
