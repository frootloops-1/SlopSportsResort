#ifndef RP_KERNEL_EFFECT_BASE_H
#define RP_KERNEL_EFFECT_BASE_H
#include <Pack/types_pack.h>

#include <egg/core.h>
#include <egg/prim.h>

#include <nw4r/ef.h>
#include <nw4r/math.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Particle parameter overrides held by RPSysEffect (Resort only)
 * @details Resort: vtable 0x806B9908, ctor 0x8024B9A4, dtor 0x8024B944
 * (unit unk/sinit_8024B2C8). Each setter takes a mode word: bit 0 and bit 1
 * select which of the two flag words (0x4, 0x8) get the parameter's mask.
 */
class Unk_806B9908 {
public:
    Unk_806B9908();          // 0x8024B9A4
    virtual ~Unk_806B9908(); // at 0x8, 0x8024B944

    void fn_8024B3AC(); // reset

    void fn_8024B48C(const nw4r::math::VEC3& rVec, u32 mode);
    void fn_8024B4E8(const nw4r::math::VEC3& rVec, bool enable, u32 mode);
    void fn_8024B574(const nw4r::math::VEC2& rVec, u32 mode);
    void fn_8024B5C8(const nw4r::math::VEC2& rVec, u32 mode);
    void fn_8024B61C(u8 arg0, u8 arg1, int idx, u32 mode);
    void fn_8024B68C(const GXColor& rColor0, const GXColor& rColor1, int idx,
                     u32 mode);
    void fn_8024B720(const GXColor& rColor, u32 mode);
    void fn_8024B78C(f32 value, u32 mode);
    void fn_8024B7D8(f32 value, u32 mode);
    void fn_8024B838(u16 value, u32 mode);
    void fn_8024B878(u16 value, u32 mode);
    void fn_8024B8B8(f32 value, u32 mode);
    void fn_8024B904(u16 value, u32 mode);

    // Getters (unit unk/text_8024AA70; placeholder names). The mode argument
    // selects the parent-emitter (0) or child-emitter (1) settings.
    nw4r::math::VEC3* fn_8024B564();
    nw4r::math::VEC3* fn_8024B56C();
    nw4r::math::VEC2* fn_8024B5C0();
    nw4r::math::VEC2* fn_8024B614();
    u8 fn_8024B674(int idx, u32 mode);
    GXColor* fn_8024B708(int idx, u32 mode);
    GXColor* fn_8024B774();
    u16 fn_8024B93C();

    //! Whether any override is enabled
    bool isAnyEnable() const {
        return mFlags[0] != 0 || mFlags[1] != 0;
    }

    //! Tests an override flag of one mode
    bool isEnable(bool child, u32 mask) const {
        return mFlags[child].on(mask);
    }

private:
    EGG::TBitFlag<u32> mFlags[2];     // at 0x4
    u16 mUnk0C;                       // at 0xC
    u8 mUnk0E[0x44 - 0xE];            // at 0xE
    GXColor mUnk44;                   // at 0x44
    GXColor mUnk48[2][2];             // at 0x48 ([mode][idx])
    nw4r::math::VEC2 mUnk58;          // at 0x58
    nw4r::math::VEC2 mUnk60;          // at 0x60
    nw4r::math::VEC3 mUnk68;          // at 0x68
    nw4r::math::VEC3 mUnk74;          // at 0x74
    u8 mUnk80[0x98 - 0x80];           // at 0x80 (0x8024B3AC writes up to 0x94)
};

/**
 * @brief Effect instance type created by RPSysEffectMgr (Resort only)
 * @details Resort: 0x158 bytes, vtable 0x806B98E0 (unit unk/sinit_80249EB4).
 * The effect memory manager pools these instead of nw4r::ef::Effect. The
 * vtable overrides Initialize (0x8024B15C) and Calc (0x8024AF04) and adds a
 * virtual destructor.
 */
class Unk_806B98E0 : public nw4r::ef::Effect {
public:
    Unk_806B98E0();          // 0x8024B210
    virtual ~Unk_806B98E0(); // at 0x20, 0x8024B1B0

    void fn_8024AA70(int arg, bool flag);
    void fn_8024AAE8();
    void fn_8024AF40(); // reset (called by the constructor)
    void fn_8024AFDC(Unk_806B9908* pParam);

private:
    Unk_806B9908 mParam;         // at 0xA0
    u32 mUnk138;                 // at 0x138 (reset to 1)
    u32 mUnk13C;                 // at 0x13C
    u32 mUnk140;                 // at 0x140
    u32 mUnk144;                 // at 0x144 (reset to 0xF)
    nw4r::ut::Color mUnk148[4];  // at 0x148
};

/**
 * @brief Effect wrapper
 * @details Resort: only the destructor is virtual (vtable 0x806B93A8 has one
 * slot); the parameter setters forward to the Unk_806B9908 member at 0x80.
 */
class RPSysEffect {
public:
    RPSysEffect(const char* pName, u32 drawGroup); // 0x8023EA98
    RPSysEffect(const char* pName, u32 drawGroup,
                u32 drawScene); // 0x8023EA1C

    virtual ~RPSysEffect(); // at 0x8, 0x8023E9C8

    bool create();
    void fade();
    void followFade();
    void forceKill();

    void setDisableCalc(bool disable);
    void setDisableDraw(bool disable);
    void setDisableCalcDraw(bool disable);

    void setLife(u16 life, u32 mode);
    void setEmitRatio(f32 ratio, u32 mode);
    void setEmitInterval(u16 interval, u32 mode);
    void setEmitEmitDiv(u16 emitDiv, u32 mode);
    void setPowerRadiationDir(f32 power, u32 mode);
    void setPowerSpecDir(f32 power, u32 mode);

    void setVelocity(const nw4r::math::VEC3& rVelocity);

    void setColor(u8 r, u8 g, u8 b, u8 a, u32 mode);
    void setColor(u8 r, u8 g, u8 b, u32 mode);
    void setColor(u8 a, u32 mode);

    void fn_8023E52C(const GXColor& rColor0, const GXColor& rColor1, int idx,
                     u32 mode);
    void fn_8023E524(u8 arg0, u8 arg1, int idx, u32 mode);
    void fn_8023E51C(const nw4r::math::VEC2& rVec, u32 mode);
    void fn_8023E514(const nw4r::math::VEC2& rVec, u32 mode);
    void fn_8023E50C(const nw4r::math::VEC3& rVec, bool enable, u32 mode);
    void fn_8023E504(const nw4r::math::VEC3& rVec, u32 mode);

    void setScale(f32 scale);
    void setScale(const nw4r::math::VEC3& rScale);
    void setPos(const nw4r::math::VEC3& rPosition);
    void setMtx(const nw4r::math::MTX34& rTransform);

    void fn_8023E428(int arg);
    void update();
    u16 fn_8023E240() const;
    void reset();

    /**
     * @brief Tests whether this effect is attached to an instance
     */
    bool isValid() const {
        return mHandle.IsValid();
    }

    /**
     * @brief Tests whether this effect's instance is alive
     */
    bool isAlive() const {
        return mHandle.IsAlive();
    }

private:
    /**
     * @brief Effect state flags
     */
    enum {
        EFlag_PositionDirty,  //!< Effect position should be flushed
        EFlag_TransformDirty, //!< Effect transform should be flushed
        EFlag_ScaleDirty,     //!< Effect scale should be flushed
        EFlag_ColorDirty,     //!< Resort: set by setColor
        EFlag_Updated,        //!< Resort: set by update
    };

    //! Maximum effect name length
    static const u32 NAME_LENGTH = 32;

    Unk_806B98E0* getEffect() const {
        return static_cast<Unk_806B98E0*>(mHandle.GetPtr());
    }

private:
    //! Dummy effect handle
    static const nw4r::ef::Handle<nw4r::ef::Effect> INVALID_HANDLE;

    //! Effect name
    char mName[NAME_LENGTH]; // at 0x4

    //! Effect draw group
    u32 mDrawGroup; // at 0x24
    //! Effect draw scene
    u32 mDrawScene; // at 0x28

    //! Effect state flags
    EGG::TBitFlag<u32> mFlags; // at 0x2C

    //! Effect scale
    nw4r::math::VEC3 mScale; // at 0x30
    //! Effect position
    nw4r::math::VEC3 mPosition; // at 0x3C
    //! Effect transformation matrix
    nw4r::math::MTX34 mTransform; // at 0x48

    //! Effect handle
    nw4r::ef::Handle<nw4r::ef::Effect> mHandle; // at 0x78

    // Resort: 0x8023EA5C constructs it, 0x8023E504.. forward to it
    Unk_806B9908 mUnk80; // at 0x80
};

//! @}

#endif
