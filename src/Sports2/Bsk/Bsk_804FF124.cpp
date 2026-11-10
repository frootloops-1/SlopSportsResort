// Basketball (Resort-only). First pass; not a full match.
// Generated first pass: leaf accessors, setters, constant getters, empty virtuals and tail calls
// only; fn_ names are Resort addresses, struct offsets raw (layouts not recovered).

#include <types.h>

extern "C" {

void fn_80357150(void* p); // base ctor
void* fn_80507E90(void* p, int i);
void* fn_8053F7F4(void* p, int i);
void* fn_80523BE4(void* p, u32 a);
extern void* lbl_806E0120[];
extern u8* lbl_806F5AC0;
struct UnkVObjAt38 { u8 _00[0x38]; virtual void vf08(); virtual void vf0C(); virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C(); virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C(); virtual void vf30(); virtual void vf34(); virtual void vf38(); };
void fn_804FC1EC(void* p);
extern void* lbl_806F59E4; // GraphManager instance
void* fn_804FF354(u8* p) {
    fn_80357150(p);
    *(void**)p = lbl_806E0120;
    p[0x1C] = 0;
    if (*(s32*)(lbl_806F5AC0 + 0x14) == 0) {
        void* o = operator new(0x348);
        if (o != NULL) {
            o = fn_80507E90(o, 6);
        }
        *(void**)(p + 0x14) = o;
        o = operator new(0x144);
        if (o != NULL) {
            o = fn_8053F7F4(o, 0);
        }
        *(void**)(p + 0x18) = o;
    } else if (*(s32*)(lbl_806F5AC0 + 0x14) == 1) {
        void* o = operator new(0x2A8);
        if (o != NULL) {
            o = fn_80523BE4(o, *(u32*)(lbl_806F5AC0 + 0x48));
        }
        *(void**)(p + 0x14) = o;
        o = operator new(0x144);
        if (o != NULL) {
            o = fn_8053F7F4(o, 1);
        }
        *(void**)(p + 0x18) = o;
    }
    *(void**)(*(u8**)(p + 0x14) + 0x108) = *(void**)(p + 0x18);
    return p;
}

void fn_804FF2B4(u8* p) { (*(UnkVObjAt38**)(p + 0x14))->vf18(); }

void fn_804FF2A0(u8* p) { (*(UnkVObjAt38**)(p + 0x14))->vf1C(); }

void fn_804FF248(u8* p) {
    (*(UnkVObjAt38**)(p + 0x14))->vf20();
    (*(UnkVObjAt38**)(p + 0x18))->vf18();
    p[0x1C] = 0;
}

int fn_804FF1A4(u8* p) {
    if (!p[0x1C]) {
        (*(UnkVObjAt38**)(p + 0x14))->vf24();
        (*(UnkVObjAt38**)(p + 0x14))->vf28();
        (*(UnkVObjAt38**)(p + 0x14))->vf2C();
        fn_804FC1EC(lbl_806F59E4);
    }
    (*(UnkVObjAt38**)(p + 0x18))->vf1C();
    (*(UnkVObjAt38**)(p + 0x14))->vf30();
    return 0;
}

int fn_804FF170(u8* p) {
    (*(UnkVObjAt38**)(p + 0x14))->vf38();
    return 0;
}

void fn_804FF124(u8* p, u8 v) { p[0x1c] = v; }

} // extern "C"
