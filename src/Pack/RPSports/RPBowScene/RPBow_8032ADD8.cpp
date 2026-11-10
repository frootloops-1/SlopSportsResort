// RPBow_8032ADD8: Resort Bowling unit (Resort rewrite of ogws RPBow_8032ADD8 + layout UI).
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

void fn_804F5E84() {}

void fn_804F69E0(u8* p) { (*(LytPart**)(p + 0xe4))->VF_16(); }

void fn_804F69F4(u8* p) { (*(LytPart**)(p + 0xe4))->VF_60(); }

u8 fn_804F6A08(u8* p) { return (*(u8**)(p + 0xe4))[0xd0]; }

void fn_804F6A14(u8* p) { (*(LytPart**)(p + 0xe4))->VF_59(); }

void fn_804F6A44(u8* p) { (*(LytPart**)(p + 0xdc))->VF_17(); }

void fn_804F6A58(u8* p) { (*(LytPart**)(p + 0xdc))->VF_16(); }

void fn_804F6A6C(u8* p) { (*(LytPart**)(p + 0xdc))->VF_60(); }

u8 fn_804F6A80(u8* p) { return (*(u8**)(p + 0xdc))[0xd0]; }

void fn_804F6A8C(u8* p) { (*(LytPart**)(p + 0xdc))->VF_59(); }

void fn_804F6AA0(u8* p) { (*(LytPart**)(p + 0xd8))->VF_17(); }

void fn_804F6AB4(u8* p) { (*(LytPart**)(p + 0xd8))->VF_16(); }

void fn_804F6AC8(u8* p) { (*(LytPart**)(p + 0xd8))->VF_60(); }

u8 fn_804F6ADC(u8* p) { return (*(u8**)(p + 0xd8))[0xd0]; }

void fn_804F6AFC(LytPart* p) { p->VF_16(); }

void fn_804F6BA4(u8* p) { (*(LytPart**)(p + 0xc0))->VF_16(); }

u8 fn_804F6BC4(u8* p) { return (*(u8**)(p + 0xc0))[0xd0]; }

void fn_804F6C24(u8* p) { (*(LytPart**)(p + 0xd0))->VF_16(); }

void fn_804F6C38(u8* p) { (*(LytPart**)(p + 0xd0))->VF_60(); }

u8 fn_804F6C4C(u8* p) { return (*(u8**)(p + 0xd0))[0xd0]; }

void fn_804F6C78(u8* p) { (*(LytPart**)(p + 0xcc))->VF_16(); }

void fn_804F6C8C(u8* p) { (*(LytPart**)(p + 0xcc))->VF_60(); }

u8 fn_804F6CA0(u8* p) { return (*(u8**)(p + 0xcc))[0xd0]; }

void fn_804F6CC0(u8* p) { (*(LytPart**)(p + 0xc8))->VF_16(); }

void fn_804F6CD4(u8* p) { (*(LytPart**)(p + 0xc8))->VF_60(); }

u8 fn_804F6CE8(u8* p) { return (*(u8**)(p + 0xc8))[0xd0]; }

void fn_804F6CF4(u8* p) { (*(LytPart**)(p + 0xc8))->VF_59(); }

void fn_804F6D08(u8* p) { (*(LytPart**)(p + 0xc4))->VF_16(); }

void fn_804F6D80(u8* p, u8* q) {
    *(u8**)(p + 0xb8) = q;
    *(u32*)(p + 0x94) = *(u32*)(q + 0x8);
}

void* fn_804F7464(u8* p) { return p + 0x64; }

void* fn_804F746C(u8* p) { return p + 0x64; }

}  // extern "C"
