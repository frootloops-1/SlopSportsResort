# fn_802C698C (RPGol_802c68a4): conversion temp always coloured before n in inlined restart (99.8 nogain)

- status: fails
- tags: rpgol,802c698c,colouring,restart,nogain
- source: worker gol-c698c 2026-10-31

symptom: 99.8%, 10 lines: retail n=r0, s16->float conversion=r3, a=r4; ours conversion=r0, n=r3
cause: three short-lived overlapping values n (arg->idx for s->idx), the lha/xoris/stw conversion temp, a (anim ptr, base reg); the conversion is always coloured first; first-in-IR of n/a is coloured first
fix: Dead: decl order of a/n (conv r0, a r3, n r4), unnamed a (99.7), s->idx=arg->idx before restart (scheduler sinks stw, 97.6-98.7) or after (lwz not hoisted), s32 n, early int n, reuse j, static inline (s,k,idx) flat, helper (s,a,idx) 99.7, GolFrameCtrl* field-sequence 99.7, self->slot[i] 99.4, self->slot[i].idx 96.3, version sweep flat, permuter 8 min no gain (PERMUTER_DIR=~/Downloads/decomp-permuter --name fn_802C698C). Untried: compare unit cflags with the library flag block.
