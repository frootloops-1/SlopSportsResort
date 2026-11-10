#ifndef EGG_GFXE_I_SCN_PROC_H
#define EGG_GFXE_I_SCN_PROC_H
#include <egg/types_egg.h>

#include <egg/gfxe/eggIDrawGX.h>

#include <egg/prim.h>

#include <nw4r/g3d.h>

#include <revolution/MEM.h>

namespace EGG {

class IScnProc : public IDrawGX {
public:
    struct ProcData {
        IScnProc* mpThis;              // at 0x0
        nw4r::g3d::ScnProc* mpScnProc; // at 0x4
        u16 mStep;                     // at 0x8
        bool mOpa;                     // at 0xA
    };

    // Resort: members precede the vtable pointer (at 0x8); MWCC places it
    // after the data members declared before the first virtual.
private:
    ProcData* mpDataSet; // at 0x0
    u16 mNumScnProc;     // at 0x4

public:
    // Resort: inlined in RPGrpDrawPathManager and ScnRenderer ctors (no
    // out-of-line __ct__Q23EGG8IScnProcFv).
    IScnProc() : mpDataSet(NULL), mNumScnProc(0) {}

    // Resort: the IScnProc vtable (lbl_806B4B28) is {pure, dtor}.
    virtual void scnProcDraw(u16 idx) = 0; // at 0x8
    virtual ~IScnProc();                   // at 0xC

    void createScnProc(u16 procNum, MEMAllocator* pAllocator);
    void setPriorityScnProc(u16 procIndex, u8 priority, bool opa);

    void pushBackToScnGroup(nw4r::g3d::ScnGroup* pScnGroup);
    void removeFromScnGroup(nw4r::g3d::ScnGroup* pScnGroup);

    ProcData* getData(u16 procIndex) {
#line 86
        EGG_ASSERT(procIndex < getNumScnProc());
        return &mpDataSet[procIndex];
    }
    u16 getNumScnProc() const {
        return mNumScnProc;
    }

private:
    static void drawProcFunc(nw4r::g3d::ScnProc* pScnProc, bool opa);

};

} // namespace EGG

#endif
