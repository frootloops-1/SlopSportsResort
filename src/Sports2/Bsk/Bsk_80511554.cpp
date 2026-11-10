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

void fn_80357604(void* p, void* a, u8 b);
void fn_80357630(void* p);
void fn_80524AB4(void* p);
void fn_805299D8(void* p);
void fn_803577C8(void* p, int del); // base dtor
void fn_80357870(void* p); // base ctor
extern void* lbl_806E0AB8[];
void fn_80357764();
void fn_805299CC();

void* fn_80511810(u8* p, u32 id) {
    fn_80357870(p);
    *(void**)p = lbl_806E0AB8;
    *(u32*)(p + 0x60) = id;
    p[0x64] = 1;
    return p;
}

// Deleting destructor: only the base destructor runs.
void* fn_805117C0(void* p, int del) {
    if (p != NULL) {
        fn_803577C8(p, 0);
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80511604(u8* p) { (*(UnkVObj**)(p + 0x5c))->vf1C(); }

void fn_80511600(void* p) { ((void (*)(void*))fn_80357764)(p); }

void fn_805115C8(u8* p) {
    fn_80524AB4(*(void**)(p + 0x54));
    fn_805299D8(*(void**)(p + 0x58));
}

void fn_805115BC(u8* p) { p[0x64] = 0; }

void fn_805115A8(u8* p) {
    if (p[0x64]) {
        fn_80357630(p);
    }
}

void fn_8051155C(u8* p, void* a, u8 b) {
    fn_80357604(p, a, b);
    (*(UnkVObj**)(p + 0x30))->vf0C();
    (*(u8**)(p + 0x30))[0x34] = b;
}

void fn_80511554(u8* p) { ((void (*)(void*))fn_805299CC)(*(void**)(p + 0x58)); }

} // extern "C"
