# Flat [2][6] array + s32 base=j*3 local fixes frame size / IV set (801f1d4c 1D4C)

- status: works
- tags: 801f1d4c,iv,strength-reduction,frame-size,savegpr
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c

symptom: Target has int IVs j*0xC and j*3 (which index computed as (which+j*3)*4), one more saved GPR and +0x10 frame; ours had a pointer IV per j
cause: Original indexes a flat SpMdlObj* active[2][6] via a named s32 base=j*3; a 3D array or [j*3+k] spelled inline makes MWCC strength-reduce the stores into a separate pointer IV
fix: SpMdlObj* active[2][6]; s32 base=j*3 at the top of the j body; [i][base+k], [i][which+base]; second loop: model before index (IV increment order follows). 94.4 -> 98.4, savegpr_15/0x130 match
