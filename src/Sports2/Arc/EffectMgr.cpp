// EffectMgr: Resort Archery unit 0x80576C7C-0x8057750C (Resort-only, no Wii Sports twin).
// File name from the singleton name string "EffectMgr" passed to the instance check (fn_80370BD8);
// the namespace and the real member names are unknown.
// First pass: only small accessor/stub functions are written; fn_ names are Resort addresses,
// struct offsets are raw (layouts not recovered yet). NonMatching.

#include <types.h>
#include <egg/core.h>

extern "C" {

// Effect name tables (.data/.sdata); defined first so the string pool order matches.
const char* lbl_806E4430[] = {
    "WS2_arc_shot_arrow",
    "WS2_arc_hit_leaf",
    "WS2_arc_hit_soil",
    "WS2_arc_hit_sand",
    "WS2_arc_hit_water",
    "WS2_arc_hit_spark",
    "WS2_arc_hit_wood",
    "WS2_arc_hit_lava",
    "WS2_arc_hit_waterfall",
    "WS2_arc_tree_conifer",
    "WS2_arc_tree_leaf",
    "WS2_arc_palmtree_leaf",
    "WS2_arc_hit_melon",
    "WS2_arc_hit_orange",
    "WS2_arc_hit_watermelon",
    "WS2_arc_hit_cake",
    "WS2_arc_hit_bread",
    "WS2_arc_hit_monitor",
    "WS2_arc_monitor_lightning",
    NULL,
};

const char* lbl_806E4480[] = {
    "WS2_arc_hit",
    "WS2_arc_hit_center",
    "WS2_arc_goldenarrow_kira",
    "WS2_arc_goldenarrow_light",
    "WS2_arc_goldenarrow_kira_hit",
    "WS2_arc_target_kirakira",
};

const char* lbl_806F2DE8[] = {
    "WS2_arc_concentration",
    "WS2_arc_wind",
};

const char* lbl_806F2DF0[] = {
    "WS2_arc_arrow_tail",
    NULL,
};


void fn_80370BD8(BOOL, const char*); // instance check (empty in release)
void* fn_8057730C(void* p); // ctor
extern void* lbl_806F5BAC;
extern void* lbl_806F5BB0;

void fn_80577400(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5BAC == NULL && lbl_806F5BB0 == NULL, "EffectMgr");
    lbl_806F5BB0 = pHeap;
    if (pHeap != NULL) {
        void* p = operator new(0x40, pHeap, 4);
        if (p != NULL) {
            p = fn_8057730C(p);
        }
        lbl_806F5BAC = p;
    } else {
        void* p = operator new(0x40);
        if (p != NULL) {
            p = fn_8057730C(p);
        }
        lbl_806F5BAC = p;
    }
}

void fn_805773F0() {
    lbl_806F5BAC = NULL;
    lbl_806F5BB0 = NULL;
}

void fn_80577090() {}

void fn_8057708C() {}

void fn_80577088() {}

void fn_80577084() {}

void fn_80577080() {}

void fn_8057707C() {}

void fn_80577078() {}

void fn_80577074() {}

}  // extern "C"
