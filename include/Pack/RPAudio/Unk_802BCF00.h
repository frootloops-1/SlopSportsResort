#ifndef RP_AUDIO_UNK_802BCF00_H
#define RP_AUDIO_UNK_802BCF00_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_audio
//! @{

/******************************************************************************
 *
 * Resort audio manager argument chain (placeholders)
 *
 * Every level has one virtual function returning the address of a static
 * type tag (base 0x802B6124, then 0x802B62A0, 0x802B6444, 0x802BD020); the
 * manager's initialize compares it to pick the argument kind.
 *
 ******************************************************************************/

//! Base argument, ctor 0x802B6608 (vtable 0x806BE78C)
class Unk_802B6608 {
public:
    Unk_802B6608();
    virtual void* Unk_08(); // at 0x8

public:
    EGG::Heap* mpHeap; // at 0x4
    u32 mUnk08;        // at 0x8 (0x8CA000 by default)
    s32 mUnk0C;        // at 0xC (4)
    s32 mUnk10;        // at 0x10 (3)
    u32 mUnk14;        // at 0x14
    u32 mUnk18;        // at 0x18
};

//! ctor 0x802B625C (vtable 0x806BE6C4)
class Unk_802B625C : public Unk_802B6608 {
public:
    Unk_802B625C();
    virtual void* Unk_08(); // at 0x8

public:
    u32 mUnk1C; // at 0x1C (1 by default)
};

//! ctor 0x802B6408 (vtable 0x806BE768)
class Unk_802B6408 : public Unk_802B625C {
public:
    Unk_802B6408();
    virtual void* Unk_08(); // at 0x8
};

//! Argument RPSysSystem::createEffectWork passes to the audio manager,
//! ctor 0x802BCFE4 (vtable 0x806BEAB8), size 0x20
class Unk_802BCFE4 : public Unk_802B6408 {
public:
    Unk_802BCFE4();
    virtual void* Unk_08(); // at 0x8
};

/******************************************************************************
 *
 * Resort audio manager (placeholder)
 *
 * Instance lbl_806F5088, created by 0x802BCF84 (0x6EC bytes, ctor 0x802BCF00,
 * vtable 0x806BEAA0). RPSysSystem stores it as the EGG audio manager without a
 * pointer adjustment.
 *
 ******************************************************************************/
//! Audio-side interface each RPSysScene keeps at 0x68 (Resort only)
class IRPSysSceneUnk68 {
public:
    virtual void VF_0x8();     // at 0x8
    virtual void VF_0xC(bool); // at 0xC
};

//! Object behind Unk_802BCF00+0x5F0 (placeholder)
class Unk_802BCF00_5F0 {
private:
    u8 UNK_0x0[0x4];

public:
    IRPSysSceneUnk68 mUnk04; // at 0x4
};

class Unk_802BCF00 {
public:
    virtual void* Unk_08();                       // at 0x8
    virtual void Unk_0C();                        // at 0xC
    virtual void initialize(Unk_802B6608* pArg);  // at 0x10
    virtual void Unk_14();                        // at 0x14

private:
    u8 UNK_0x4[0x5F0 - 0x4];

public:
    Unk_802BCF00_5F0* mUnk5F0; // at 0x5F0

private:
    u8 UNK_0x5F4[0x6EC - 0x5F4];
};

//! Resort audio manager instance (.sbss 0x806F5088)
extern Unk_802BCF00* lbl_806F5088;

//! @}

#endif
