// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>
#include <egg/core.h>

extern "C" {

void fn_80357060();
void* fn_804FC780(u8* p);
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void fn_80357150(void* p);         // base ctor
void* fn_80511810(void* p, int i);   // Bsk_80511554 ctor
void __ct__Q23EGG8DisposerFv(void* p);
extern void* lbl_806DFF90[];
extern void* lbl_806DFFB8[];
extern u32 lbl_806F59E0;
extern void* lbl_806F59E4; // instance
extern void* lbl_806F59E8; // heap
extern u32 lbl_806F2508;

// Environment resource paths, three courts x six files (light, light map, bloom, depth of field, fog, env).
const char* lbl_806DFF48[] = {
    "Env/WS2_bsk0/WS2_bsk0.plight",       "Env/WS2_bsk0/WS2_bsk0_Lmap.plmap", "Env/WS2_bsk0/WS2_bsk0.pblm",
    "Env/WS2_bsk0/WS2_bsk0.pdof",         "",                                 "Env/WS2_bsk0/WS2_bsk0_Env.penv",
    "Env/WS2_bsk2/WS2_bsk2_Light.plight", "Env/WS2_bsk2/WS2_bsk2_Lmap.plmap", "Env/WS2_bsk2/WS2_bsk2_Bloom.pblm",
    "Env/WS2_bsk2/WS2_bsk2_dof.pdof",     "Env/WS2_bsk2/WS2_bsk2_fog.pfog",   "Env/WS2_bsk2/WS2_bsk2_Env.penv",
    "Env/WS2_bsk3/WS2_bsk3.plight",       "Env/WS2_bsk3/WS2_bsk3_Lmap.plmap", "Env/WS2_bsk2/WS2_bsk2_Bloom.pblm",
    "Env/WS2_bsk2/WS2_bsk2_dof.pdof",     "Env/WS2_bsk2/WS2_bsk2_fog.pfog",   "Env/WS2_bsk2/WS2_bsk2_Env.penv",
};

void fn_804FC8D8(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F59E4 == NULL && lbl_806F59E8 == NULL, "GraphManager");
    lbl_806F59E8 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x58, pHeap, 4);
        if (p != NULL) {
            p = fn_804FC780((u8*)p);
        }
        lbl_806F59E4 = p;
    } else {
        void* p = operator new(0x58);
        if (p != NULL) {
            p = fn_804FC780((u8*)p);
        }
        lbl_806F59E4 = p;
    }
}

void fn_804FC8C8() {
    lbl_806F59E4 = NULL;
    lbl_806F59E8 = NULL;
}

void* fn_804FC780(u8* p) {
    fn_80357150(p);
    *(void**)p = lbl_806DFF90;
    u8* d = p + 0x14;
    __ct__Q23EGG8DisposerFv(d);
    *(void**)d = lbl_806DFFB8;
    *(u32*)(p + 0x24) = 0;
    *(f32*)(p + 0x28) = 0.0f;
    *(u32*)(p + 0x2C) = 0;
    p[0x30] = 1;
    *(f32*)(p + 0x48) = 1.0f;
    *(f32*)(p + 0x4C) = 1.0f;
    *(u32*)(p + 0x38) = 0;
    *(u32*)(p + 0x34) = 0;
    *(u32*)(p + 0x44) = 0;
    *(u32*)(p + 0x40) = 0;
    *(u32*)(p + 0x3C) = 0;
    void* o = operator new(0x68);
    if (o != NULL) {
        o = fn_80511810(o, 0);
    }
    *(void**)(p + 0x34) = o;
    o = operator new(0x68);
    if (o != NULL) {
        o = fn_80511810(o, 1);
    }
    *(void**)(p + 0x38) = o;
    lbl_806F59E0 = 0;
    lbl_806F2508 = 1;
    return p;
}

int fn_804FC1E4() { return 0; }

void fn_804FC1E0(void* p) { ((void (*)(void*))fn_80357060)(p); }

} // extern "C"
