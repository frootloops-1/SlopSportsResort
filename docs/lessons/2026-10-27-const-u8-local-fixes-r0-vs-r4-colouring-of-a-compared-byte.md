# const u8 local fixes r0 vs r4 colouring of a compared byte

- status: works
- tags: mwcc,register,const-local
- source: RPUtl_801C9E7C

symptom: originX lbz in r4 (target r0), slwi temp in r0 (target r3)
cause: non-const local / member reread coloured earlier
fix: const u8 originX = sel.originX; after the pane load (u8/u32/s32/int did not work): fn_801CA18C 99.6 -> 100
