// Scene: Resort Frisbee Dog unit 0x805C1AB0-0x805C29FC (Resort-only, no Wii Sports twin).
// Sp2::Fld::Ddg::Scene: singleton create fn_805C28D0 passes "Sp2::Fld::Ddg::Scene" to the instance check (fn_80370BD8); instance lbl_806F5F80, size 0xF0, ctor 0x805C27D8 and dtor 0x805C2970 renamed, vtable 0x806E8CC0; draw-pass names Draw/DrawShadow/DrawXLU/Draw2D.
// Namespace Sp2::Fld::Ddg is proven by the scene singleton name string; other class names are unknown.
// First pass: straight-line functions only; fn_ names are Resort addresses, offsets are raw. NonMatching.

#include <types.h>
#include <egg/core.h>

namespace Sp2 {
namespace Fld {
namespace Ddg {

// Layout not recovered: base class at 0x0 (ctor fn_80335910), EGG::Disposer-derived holder at 0x34
// (vtable 0x806E8D04), size 0xF0.
class Scene {
public:
    Scene();
    virtual ~Scene();

private:
    u8 unk4[0xF0 - 0x4];
};

} // namespace Ddg
} // namespace Fld
} // namespace Sp2

extern "C" {

u8* GetModelScene__17RPGrpModelManagerFUc(u8*, s32);
void fn_805C70D0(u8*);
void fn_805DEB10(u8*);
extern Sp2::Fld::Ddg::Scene* lbl_806F5F80;
extern void* lbl_806F5F84;
extern u8* spCurrent__17RPGrpModelManager;
void fn_80370BD8(BOOL, const char*); // instance check (empty in release)

void fn_805C28D0(EGG::Heap* pHeap) {
    fn_80370BD8(lbl_806F5F80 == NULL && lbl_806F5F84 == NULL, "Sp2::Fld::Ddg::Scene");
    lbl_806F5F84 = pHeap;
    if (pHeap != NULL) {
        lbl_806F5F80 = new (pHeap, 4) Sp2::Fld::Ddg::Scene();
    } else {
        lbl_806F5F80 = new Sp2::Fld::Ddg::Scene();
    }
}

void fn_805C28C0() {
    lbl_806F5F80 = NULL;
    lbl_806F5F84 = NULL;
}

void fn_805C20B0(u8* p) {
    u8* t0 = GetModelScene__17RPGrpModelManagerFUc(spCurrent__17RPGrpModelManager, 0);
    fn_805C70D0(t0);
    fn_805DEB10(*(u8**)(p + 0x74));
}

void fn_805C1E34() {}

void fn_805C1E30() {}

void fn_805C1CF4() {}

s32 fn_805C1B04(u8* p) {
    static const s32 cTable[] = {0, 2};
    if (*(s32*)(p + 0xdc) == 4) {
        return cTable[*(s32*)(p + 0xec)];
    }
    return *(s32*)(p + 0xdc);
}

}  // extern "C"
