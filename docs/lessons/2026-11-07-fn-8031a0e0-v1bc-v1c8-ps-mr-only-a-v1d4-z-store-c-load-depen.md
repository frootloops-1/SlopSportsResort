# fn_8031A0E0 v1BC/v1C8 ps_mr: only a v1D4.z-store -> c-load dependence fixes it; no source makes that edge

- status: fails
- tags: scheduler,ps_mr,alias,fn_8031A0E0,RPBow_80319C98
- scope: RPBow_80319C98/fn_8031A0E0
- source: claude/bow-80319C98-1105 round 6

symptom: Two ps_mr in the v1BC/v1C8 approach block (forwarded sub1 load interferes with the z ps_sub; mul2 reload forwarded)
cause: Modelled exactly: z sub issues in the cycle the forwarded load issues (muls0 waits 2 cycles); every statement order with v1BC first fails, v1C8-first gives a mirrored retail shape. Adding edge stfs v1D4.z -> lfs prm->pC4 (or a few other single edges) gives retail
fix: Dead (graph unchanged or worse): volatile c, u8* casts on prm/c/v1D4.z, const prm, prm via cast, const f32& c (traced: same graph), VEC3 struct copy with dead z store, kept scale fmr, separate z vregs in VEC3Sub (306), v=v+... (326-374). Park.
