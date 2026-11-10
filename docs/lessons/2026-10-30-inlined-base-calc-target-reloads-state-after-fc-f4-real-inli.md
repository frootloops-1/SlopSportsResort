# Inlined base calc: target reloads state after fC=f4; real inline still CSEs it (801f1d4c)

- status: open
- tags: 801f1d4c,cse,inline,volatile,auto_inline
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c

symptom: Target loads f4 twice after the base-calc join (fC=f4 and switch(f4)); ours reuses one load
cause: Unknown. #pragma auto_inline on around fn_801F4C88 or an in-class member inline does inline it, but MWCC still CSEs the load (and colours req r0 vs r4, 98.5)
fix: MATCH-PENDING switch(*(volatile s32*)&self->f4) plus 4C88's compare shape (if (f4 != fC) { f14 = f18 = 0; f10 = fC; }) -> 4A98 100. Failed: u32-typed store, store-before-frame order, cast-pointer inline
