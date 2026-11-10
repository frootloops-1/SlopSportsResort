#ifndef RVL_SDK_GX_MISC_H
#define RVL_SDK_GX_MISC_H
#include <types.h>

#include <revolution/GX/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXDrawDoneCallback)(void);
typedef void (*GXDrawSyncCallback)(u16 token);

typedef enum {
    GX_MT_NULL,
    GX_MT_XF_FLUSH,
    GX_MT_DL_SAVE_CONTEXT,
    GX_MT_ABORT_WAIT_COPYOUT
} GXMiscToken;

typedef enum { GX_READ_00, GX_READ_FF, GX_READ_NONE } GXAlphaReadMode;

void GXSetMisc(GXMiscToken token, u32 val);
void GXFlush(void);
void GXResetWriteGatherPipe(void);

void GXAbortFrame(void);
void __GXAbort(void);
void __GXPEInit(void);

void GXSetDrawSync(u16 token);

void GXDrawDone(void);
void GXPixModeSync(void);

void GXPokeAlphaMode(GXCompare func, u8 threshold);
void GXPokeAlphaRead(GXAlphaReadMode mode);
void GXPokeAlphaUpdate(GXBool update);
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src, GXBlendFactor dst,
                     GXLogicOp op);
void GXPokeColorUpdate(GXBool update);
void GXPokeDstAlpha(GXBool enable, u8 alpha);
void GXPokeDither(GXBool dither);
void GXPokeZMode(GXBool compare, GXCompare func, GXBool update);

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback);

#ifdef __cplusplus
}
#endif
#endif
