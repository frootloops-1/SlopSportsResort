// RPBow_8032F514: Resort Bowling unit (Resort rewrite of ogws RPBow_8032F514 + layout UI).
// First pass: only the small accessor/stub functions are written; fn_ names are Resort
// addresses, struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>

#define LYT_VF(n) virtual void VF_##n();

// Inferred (name invented): layout part object, vtable pointer at 0x30
struct LytPart {
    u8 pad_0x0[0x30];
    LYT_VF(0) LYT_VF(1) LYT_VF(2) LYT_VF(3) LYT_VF(4) LYT_VF(5) LYT_VF(6) LYT_VF(7) LYT_VF(8) LYT_VF(9)
    LYT_VF(10) LYT_VF(11) LYT_VF(12) LYT_VF(13) LYT_VF(14) LYT_VF(15) LYT_VF(16) LYT_VF(17) LYT_VF(18) LYT_VF(19)
    LYT_VF(20) LYT_VF(21) LYT_VF(22) LYT_VF(23) LYT_VF(24) LYT_VF(25) LYT_VF(26) LYT_VF(27) LYT_VF(28) LYT_VF(29)
    LYT_VF(30) LYT_VF(31) LYT_VF(32) LYT_VF(33) LYT_VF(34) LYT_VF(35) LYT_VF(36) LYT_VF(37) LYT_VF(38) LYT_VF(39)
    LYT_VF(40) LYT_VF(41) LYT_VF(42) LYT_VF(43) LYT_VF(44) LYT_VF(45) LYT_VF(46) LYT_VF(47) LYT_VF(48) LYT_VF(49)
    LYT_VF(50) LYT_VF(51) LYT_VF(52) LYT_VF(53) LYT_VF(54) LYT_VF(55) LYT_VF(56) LYT_VF(57) LYT_VF(58) LYT_VF(59)
    LYT_VF(60) LYT_VF(61) LYT_VF(62) LYT_VF(63)
};
extern "C" {

u32 fn_804EC188(u8* p, int i) { return ((u32*)(p + 0x20))[i]; }

u32 fn_804EC1D4(u8* p, int i) { return ((u32*)(p + 0x10))[i]; }

void fn_804EC248(u8* p, int i, u32 a, u32 b) {
    ((u32*)(p + 0x10))[i] = a;
    ((u32*)(p + 0x20))[i] = b;
}

void fn_804ED780() {}

void fn_804ED784() {}

void fn_804EDCA8(u8* p, int i, u32 a, u32 b) {
    ((u32*)(p + 0x98))[i] = a;
    ((u32*)(p + 0xa8))[i] = b;
}

void fn_804EDCBC(u8* p) { (*(LytPart**)(p + 0xc8))->VF_16(); }

void fn_804EDCD0(u8* p) { (*(LytPart**)(p + 0xc8))->VF_60(); }

u8 fn_804EDCE4(u8* p) { return (*(u8**)(p + 0xc8))[0xd0]; }

void fn_804EDEF8(u8* p, u8* q) {
    *(u8**)(p + 0xb8) = q;
    *(u32*)(p + 0x94) = *(u32*)(q + 0x8);
}

void* fn_804EE30C(u8* p) { return p + 0x64; }

void* fn_804EE314(u8* p) { return p + 0x64; }

}  // extern "C"
