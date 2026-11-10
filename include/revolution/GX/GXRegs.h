#ifndef RVL_SDK_GX_REGS_H
#define RVL_SDK_GX_REGS_H
#include <types.h>

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

#ifdef __cplusplus
extern "C" {
#endif

#define gx gxdt

#define PHY_ADDR_MASK ~((~0x3FFF) << 16)
#define GX_PHY_ADDR(a) ((u32)a & PHY_ADDR_MASK)

#define BP_SENT() gx->bpSentNot = GX_FALSE;
#define XF_SENT() gx->bpSentNot = GX_TRUE;

extern void __GXSetTmemConfig(u32);

extern void __GetImageTileCount(GXTexFmt fmt, u16 wd, u16 ht, u32* rowTiles,
                                u32* colTiles, u32* cmpTiles);

typedef struct __GXLightObjInt_struct {
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void* userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} GXTexObjInt;

typedef struct __GXTexRegionInt_struct {
    u32 image1;
    u32 image2;
    u16 sizeEven;
    u16 sizeOdd;
    u8 is32bMipmap;
    u8 isCached;
} GXTexRegionInt;

typedef struct __GXTlutObjInt_struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} GXTlutObjInt;

typedef struct __GXTlutRegionInt_struct {
    u32 loadTlut1;
    GXTlutObjInt tlutObj;
} GXTlutRegionInt;

#define GX_SETUP_LIGHT(l, p)                                                   \
    GXLightObjInt* l;                                                          \
    l = (GXLightObjInt*)p;

#define GX_SETUP_TEXOBJ(l, p) GXTexObjInt* l = (GXTexObjInt*)p;

#define GX_SETUP_ALL_TEXOBJS(l, p, m, q)                                       \
    GXTexObjInt* l = (GXTexObjInt*)p;                                          \
    GXTexRegionInt* m = (GXTexRegionInt*)q;

#define GX_SETUP_TLUTOBJ(l, p) GXTlutObjInt* l = (GXTlutObjInt*)p;

#define GX_SETUP_TREGOBJ(l, p) GXTexRegionInt* l = (GXTexRegionInt*)p;

#define GX_SETUP_TLUTREGOBJ(l, p) GXTlutRegionInt* l = (GXTlutRegionInt*)p;

#include <private/bp_reg.h>
#include <private/cp_reg.h>
#include <private/gen_reg.h>
#include <private/pe_reg.h>
#include <private/pi_reg.h>
#include <private/ras_reg.h>
#include <private/su_reg.h>
#include <private/tev_reg.h>
#include <private/tx_reg.h>
#include <revolution/GX/GXTypes.h>
#include <revolution/GX/GXHardware.h>
#include <revolution/GX/GXInit.h>
#include <revolution/GX/shortcut_bp_reg.h>
#include <revolution/GX/shortcut_cp_reg.h>
#include <revolution/GX/shortcut_gen_reg.h>
#include <revolution/GX/shortcut_pe_reg.h>
#include <revolution/GX/shortcut_pi_cp_reg.h>
#include <revolution/GX/shortcut_ras_reg.h>
#include <revolution/GX/shortcut_su_reg.h>
#include <revolution/GX/shortcut_tev_reg.h>

extern volatile u32 __PIRegs[] DECL_ADDRESS(0xCC003000);
extern volatile void* __piReg;
extern volatile void* __cpReg;
extern volatile void* __peReg;
extern volatile void* __memReg;

#define MEM_PE_REQCOUNTH_IDX 0x27
#define MEM_PE_REQCOUNTL_IDX 0x28

/* GX fifo write helpers */

#define GX_WRITE_U8(val) WGPIPE.uc = (u8)(val)

#define GX_WRITE_U16(val) WGPIPE.us = (u16)(val)

#define GX_WRITE_S16(val) WGPIPE.s = (s16)(val)

#define GX_WRITE_U32(val) WGPIPE.ui = (u32)(val)

#define GX_WRITE_F32(val) WGPIPE.f = (f32)(val);

#define GX_PI_REG_WRITE_U32(a, d) *(vu32*)((vu8*)__piReg + (a)) = (u32)(d)

#define GX_PI_REG_READ_U32(a) *(vu32*)((vu8*)__piReg + (a))

#define GX_CP_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__cpReg + (a)) = (u16)(d)

#define GX_CP_REG_READ_U16(a) *(vu16*)((vu16*)__cpReg + (a))

#define GX_CP_REG_WRITE_U32(a, d) *(vu32*)((vu16*)__cpReg + (a)) = (u32)(d)

#define GX_CP_REG_READ_U32(a) *(vu32*)((vu16*)__cpReg + (a))

#define GX_MEM_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__memReg + (a)) = (u16)(d)

#define GX_MEM_REG_READ_U16(a) *(vu16*)((vu16*)__memReg + (a))

#define GX_PE_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__peReg + (a)) = (u16)(d)

#define GX_PE_REG_READ_U16(a) *(vu16*)((vu16*)__peReg + (a))

#define GX_CP_IDLE_REG_READ_U16(a) GX_CP_REG_READ_U16(a)

#define GX_PI_REG_WRITE_U32(a, d) *(vu32*)((vu8*)__piReg + (a)) = (u32)(d)

#define GX_PI_REG_READ_U32(a) *(vu32*)((vu8*)__piReg + (a))

#define GX_CP_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__cpReg + (a)) = (u16)(d)

#define GX_CP_REG_READ_U16(a) *(vu16*)((vu16*)__cpReg + (a))

#define GX_CP_REG_WRITE_U32(a, d) *(vu32*)((vu16*)__cpReg + (a)) = (u32)(d)

#define GX_CP_REG_READ_U32(a) *(vu32*)((vu16*)__cpReg + (a))

#define GX_MEM_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__memReg + (a)) = (u16)(d)

#define GX_MEM_REG_READ_U16(a) *(vu16*)((vu16*)__memReg + (a))

#define GX_PE_REG_WRITE_U16(a, d) *(vu16*)((vu16*)__peReg + (a)) = (u16)(d)

#define GX_PE_REG_READ_U16(a) *(vu16*)((vu16*)__peReg + (a))

#define GX_CP_IDLE_REG_READ_U16(a) GX_CP_REG_READ_U16(a)

#define GX_WRITE_CP_STRM_REG(addr, vtxfmt, data)                                                                                                     \
    {                                                                                                                                                \
        GX_WRITE_U8(CP_OPCODE(0, 1));                                                                                                                \
        GX_WRITE_U8(CP_STREAM_REG((vtxfmt), (addr)));                                                                                                \
        GX_WRITE_U32((data));                                                                                                                        \
    }

#define GX_WRITE_XF_REG(addr, data, cnt)                                                                                                             \
    {                                                                                                                                                \
        GX_WRITE_U8(CP_OPCODE(0, 0x2));                                                                                                              \
        GX_WRITE_U32(CP_XF_LOADREGS((addr), (cnt)));                                                                                                 \
        GX_WRITE_U32((data));                                                                                                                        \
    }

#define GX_WRITE_XF_MEM_U32(addr, data) GX_WRITE_U32(data)
#define GX_WRITE_XF_MEM_F32(addr, data) GX_WRITE_F32(data)

#define GX_WRITE_RA_REG(reg)                                                                                                                         \
    {                                                                                                                                                \
        GX_WRITE_U8(CP_OPCODE(1, 0xC));                                                                                                              \
        GX_WRITE_U32((reg));                                                                                                                         \
    }

#ifdef __MWERKS__
#define GX_DEFINE_GX_READ_COUNTER(unit)                                                                                                              \
    inline u32 __GXRead##unit##CounterU32(u32 regAddrL, u32 regAddrH) {                                                                              \
        u32 ctrH0, ctrH1, ctrL;                                                                                                                      \
        ctrH0 = GX_##unit##_REG_READ_U16(regAddrH);                                                                                                  \
        do {                                                                                                                                         \
            ctrH1 = ctrH0;                                                                                                                           \
            ctrL = GX_##unit##_REG_READ_U16(regAddrL);                                                                                               \
            ctrH0 = GX_##unit##_REG_READ_U16(regAddrH);                                                                                              \
        } while (ctrH0 != ctrH1);                                                                                                                    \
        return ((ctrH0 << 16) | ctrL);                                                                                                               \
    }
#else
#define GX_DEFINE_GX_READ_COUNTER(unit)
#endif

GX_DEFINE_GX_READ_COUNTER(CP)
GX_DEFINE_GX_READ_COUNTER(PE)
GX_DEFINE_GX_READ_COUNTER(MEM)

#ifdef __MWERKS__
#define GX_CP_COUNTER_READ_U32(name) __GXReadCPCounterU32(name##L, name##H)

#define GX_PE_COUNTER_READ_U32(name) __GXReadPECounterU32(name##L_ID, name##H_ID)

#define GX_MEM_COUNTER_READ_U32(name) __GXReadMEMCounterU32(name##L_IDX, name##H_IDX)

#define FAST_FLAG_SET(regOrg, newFlag, shift, size)                                                                                                  \
    do {                                                                                                                                             \
        (regOrg) = (u32)__rlwimi((int)(regOrg), (int)(newFlag), (shift), (32 - (shift) - (size)), (31 - (shift)));                                   \
    } while (0);
#else
#define GX_CP_COUNTER_READ_U32(name)
#define GX_PE_COUNTER_READ_U32(name)
#define GX_MEM_COUNTER_READ_U32(name)
#define FAST_FLAG_SET(regOrg, newFlag, shift, size)
#endif

#ifdef __cplusplus
}
#endif

#endif  // GXREGS_H
