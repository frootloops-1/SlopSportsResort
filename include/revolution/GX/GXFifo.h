#ifndef RVL_SDK_GX_FIFO_H
#define RVL_SDK_GX_FIFO_H
#include <types.h>

#include <revolution/GX/GXInternal.h>

#include <revolution/OS.h>
#ifdef __cplusplus
extern "C" {
#endif

GX_PUBLIC_STRUCT_DECL(GXFifoObj, 128);

typedef void (*GXBreakPtCallback)(void);

void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle,
                   GXBool* cmdIdle, GXBool* brkpt);

void GXSetCPUFifo(const GXFifoObj*);
GXBool GXGetCPUFifo(GXFifoObj*);
GXBool GXGetGPFifo(GXFifoObj*);

void GXGetFifoPtrs(const GXFifoObj*, void** readPtr, void** writePtr);

u32 GXGetFifoCount(const GXFifoObj*);
u8 GXGetFifoWrap(const GXFifoObj*);

GXBool __GXIsGPFifoReady(void);
void __GXCleanGPFifo(void);

void GXEnableBreakPt(void* writePtr);
void GXDisableBreakPt(void);

OSThread* GXGetCurrentGXThread(void);

#ifdef __cplusplus
}
#endif
#endif
