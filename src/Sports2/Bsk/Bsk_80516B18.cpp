// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void* fn_80516C3C(void* p, int del); // base dtor (defined below)
void* fn_80516C7C(u8* p);
struct UnkMtx34 { u32 w[12]; };
extern UnkMtx34 lbl_807D1598; // identity matrix
extern void* lbl_806E0E08[];
extern void* lbl_806E0E30[];
void* fn_80516AEC(void* p, f32 f);
void fn_8013C650(void* p, void* a, void* b, void* c);
extern u8 lbl_807D1558[];
extern u8 lbl_807D1570[];
extern u8 lbl_807D1588[];
void fn_80356CA0();

void* fn_805177D8(u8* p) {
    fn_80516C7C(p);
    *(void**)p = lbl_806E0E30;
    *(u32*)(p + 0x94) = 0;
    p[0x98] = 0;
    void* o = operator new(0x1C);
    if (o != NULL) {
        o = fn_80516AEC(o, 0.0f);
    }
    *(void**)(p + 0x190) = o;
    fn_8013C650(p + 0x17C, lbl_807D1558, lbl_807D1570, lbl_807D1588);
    return p;
}

void fn_805174E8(u8* p) { ((void (*)(void*))fn_80356CA0)(*(void**)(p + 0x94)); }

f32 fn_80517314(u8* p) { return *(f32*)(p + 0x50); }

void* fn_80516C7C(u8* p) {
    *(void**)p = lbl_806E0E08;
    *(UnkMtx34*)(p + 0x4) = lbl_807D1598;
    *(UnkMtx34*)(p + 0x34) = lbl_807D1598;
    *(UnkMtx34*)(p + 0x64) = lbl_807D1598;
    return p;
}

// Deleting destructor of a class without a base destructor.
void* fn_80516C3C(void* p, int del) {
    if (p != NULL) {
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

void fn_80516C38() {}

} // extern "C"
