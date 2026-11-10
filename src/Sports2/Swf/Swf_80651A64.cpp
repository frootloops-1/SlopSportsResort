// Swf_80651A64: Resort Swordplay unit 0x80651A64-0x80651DBC (Resort-only, no Wii Sports twin).
// layout 65031_swf_tameshi_caution.
// Class descriptions are the Shift-JIS debug names returned by each class's name getter; no class or
// namespace name is proven, so functions keep their fn_ names. First pass, raw offsets. NonMatching.

#include <types.h>
struct Unk_VtAt30_11C { u8 pad[0x30]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void vf(); };

extern "C" {

void fn_803715C0(u8*, s32, s32);
void fn_80651D44(u8*, int);
extern u8 lbl_806EF7F0[];
void fn_8026FEF0(u8*, s32, s32);
u8* fn_8026F6AC(u8*, s32);
void fn_8025EC94(u8*);
void fn_8025ED28(u8*);

void fn_80651DB4(u8* p, int a) {
    fn_80651D44(p - 0x94, a);
}

void fn_80651DAC(u8* p, int a) {
    fn_80651D44(p - 0x18, a);
}

u8* fn_80651CD8(u8* p) {
    fn_803715C0(p, 2, 0);
    *(u8**)(p + 0x30) = lbl_806EF7F0;
    *(u8**)(p + 0x18) = lbl_806EF7F0 + 0x8;
    *(u8**)(p + 0x94) = lbl_806EF7F0 + 0x78;
    *(u8**)(p + 0x98) = lbl_806EF7F0 + 0x88;
    *(s32*)(p + 0x118) = 0;
    *(s32*)(p + 0x11c) = -1;
    return p;
}

void fn_80651BB8(u8* p) {
    fn_8026FEF0(p + 0x94, 0, 1);
    fn_8025EC94(fn_8026F6AC(p + 0x94, 0));
    fn_8026FEF0(p + 0x94, 1, 0);
    fn_8025ED28(fn_8026F6AC(p + 0x94, 1));
    *(s32*)(p + 0x11c) = 0xb4;
    ((Unk_VtAt30_11C*)p)->vf();
}

void fn_80651B70(u8* p) {
    fn_8026FEF0(p + 0x94, 1, 1);
    fn_8025EC94(fn_8026F6AC(p + 0x94, 1));
}

void fn_80651B50(u8* p, const f32* v) {
    u8* o = *(u8**)(p + 0x114);
    *(f32*)(o + 0x2c) = v[0];
    *(f32*)(o + 0x30) = v[1];
    *(f32*)(o + 0x34) = v[2];
}

}  // extern "C"
