// Resort (RZTE01_01) port of Wii Sports RPBow_80330EBC.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

#include <Pack/RPKernel/IRPSysHostIOSocket.h>

extern "C" { extern u8 lbl_806DED20[]; extern float gLaneXOffsets__7Bowling[]; }
namespace Bowling {


// Inferred (name invented): per-lane object (Resort layout)
struct BowlingLaneObj {
    IRPSysHostIOSocket socket;  // offset 0x0
    u8 pad04[0x2DB8 - 4];

    inline BowlingLaneObj();
};

extern "C" {
void* fn_804C4788(void*);
void fn_804C4454(void*, int);
void* fn_804C4740(void*);
void fn_804C4494(void*, int);
void fn_804DE6E0(void*);
void* fn_804C457C(void*);
void __construct_array(void*, void* (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
}

inline BowlingLaneObj::BowlingLaneObj() {
    *(void**)this = lbl_806DED20;
    __construct_array(pad04 + 0x20, fn_804C4788, fn_804C4454, 0xE8, 16);
    __construct_array(pad04 + 0xEA4 - 4, fn_804C4740, fn_804C4494, 0x12C, 16);
    fn_804DE6E0(pad04 + 0x23BC - 4);
    fn_804C4740(pad04 + 0x2BEC - 4);
    fn_804C457C(pad04 + 0x2D18 - 4);
}

// Inferred (name invented): holder of seven lane object pointers at 0x4
struct BowlingLaneSet {
    u8 pad00[4];
    BowlingLaneObj* mpLanes[7];  // offset 0x4
};

extern "C" {

void fn_804DD6C0(BowlingLaneObj*, int, int, f32, int);
void fn_804DE6E0(void*) {}

void fn_804DE5EC(BowlingLaneSet* pThis, int* pSrc) {
    for (int i = 0; i < 7; i++) {
        BowlingLaneObj* pLane = new BowlingLaneObj;
        pThis->mpLanes[i] = pLane;
        fn_804DD6C0(pLane, 0, 10, gLaneXOffsets__7Bowling[i], pSrc[0xA8 / 4 + i]);
    }
}

}

}  // namespace Bowling
