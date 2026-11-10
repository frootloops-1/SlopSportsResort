// Canoeing (Resort-only), .text 0x804A5880-0x804A6C88: buoys (WS2_can_p_bouy/VS_bouy, .sdata "Buoy"). First pass; not a full match.
// First pass (generated from the asm): only straight-line functions (accessors, setters, empty
// functions, direct and virtual calls) are written; offsets are raw, names are placeholders.

#include <types.h>

extern "C" {

void fn_8013C090(f32* out, const f32* a, const f32* b);
void fn_8013C050(f32* out, const f32* a, const f32* b);
void fn_804A6794(u8* p, f32 a, f32 b, f32 c, f32 d);
struct Unk_VtAtC {
    u8 unk0[0xC];
    virtual void vf8();
    virtual void vfC(s32);
    virtual void vf10(s32);
};

void fn_803596A8(u8*);
void fn_8035A0D8(u8*, u8*);
void fn_804A65E4(u8*);
extern u8* lbl_806F58C0;
extern u32 lbl_806F58C4;
extern f32 lbl_806F58C8;
extern f32 lbl_806F58CC;
extern u32 lbl_806F58D0;
extern f32 lbl_806F58D8;
extern u8 lbl_806DC110[];

void fn_804A6C84() {}

const char* fn_804A6C7C() {
    static char sName[] = "Buoy";
    return sName;
}

void fn_804A693C(void*, void*, void*, f32* m) {
    m[0] = -m[0];
    m[4] = -m[4];
    m[8] = -m[8];
}

f32 fn_804A6934() { return lbl_806F58D8; }

f32 fn_804A692C() { return 80.0f; }

f32 fn_804A6924() { return 60.0f; }

void fn_804A6918(u8* p, f32 a, f32 b) { fn_804A6794(p, a, b, 40.0f, 80.0f); }

void fn_804A690C(u8* p, f32 a, f32 b) { fn_804A6794(p, a, b, 20.0f, 60.0f); }

void fn_804A6678(u8* p) {
    *(u32*)(p + 0xb8) = lbl_806F58D0;
    fn_804A65E4(p);
}

void fn_804A65D4(u32 p, f32 fa1, f32 fa2) {
    lbl_806F58C8 = fa1;
    lbl_806F58CC = fa2;
    lbl_806F58D0 = p;
}

void fn_804A65C4() { *(u16*)(lbl_806F58C0 + 0x6) = lbl_806F58C4; }

void fn_804A649C() { lbl_806F58C4 = 0; }

u8* fn_804A621C(u8* p) {
    *(u8**)(p) = lbl_806DC110;
    fn_8035A0D8(p + 0x10, lbl_806DC110);
    fn_803596A8(p + 0x70);
    return p;
}

void fn_804A6034() {}

void fn_804A5C0C(u8* p) {
    f32* v = *(f32**)(p + 0xa8);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = v[4] = v[5] = 0.0f;
    v = *(f32**)(p + 0xac);
    v[0] = v[1] = v[2] = 0.0f;
    v[3] = v[4] = v[5] = 0.0f;
}

void fn_804A5998(u8* p) {
    *(u32*)(p + 0xb0) = 0;
    *(f32*)(p + 0x70) = 0.5f * *(f32*)(p + 0x50);
}

void fn_804A58E4() { ((Unk_VtAtC*)(lbl_806F58C0))->vfC(0); }

void fn_804A58CC() { ((Unk_VtAtC*)(lbl_806F58C0))->vf10(0); }

void fn_804A5880(u8* p, const f32* v) {
    f32* m = *(f32**)(p + 0xac);
    fn_8013C090(m, m, v);
    fn_8013C050(m + 3, m + 3, v);
}

}  // extern "C"
