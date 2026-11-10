# errno_name pragma stops cosf/sinf clobbering address-taken locals (no _copy workaround)

- status: works
- tags: regalloc,math,errno,GXDraw,sinf,cosf,workaround
- scope: src/revolution/GX/GXDraw.c
- source: doldecomp/forecast 0d6355d

symptom: GXDrawSphere needed a tex0_copy local to match; without it tex0 is reloaded after each sinf/cosf call (97.8%)
cause: Without errno_name, MWCC treats cos/sin as worst-case calls that may modify any local whose address was taken (tex0 passed to GXGetVtxDesc-style out param)
fix: #include <errno.h> + #pragma errno_name errno at top of the SDK unit, drop the copy local; GXDraw 100%, DOL 0 diff bytes. Source: doldecomp/forecast commit 0d6355d. Try on other units with cos/sin/pow and a *_copy local.
