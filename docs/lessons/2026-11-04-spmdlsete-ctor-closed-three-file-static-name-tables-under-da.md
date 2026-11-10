# SpMdlSetE ctor closed: three file-static name tables under ...data.0 plus loop body as inline helper with i param

- status: works
- tags: anchor,data,iv-init,inline-param,ctor,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: missing 'addi r26,r8,0x0' IV init (size 468 vs 472) and i/this colours swapped (i r23 vs r31)
cause: retail addresses files/anms/names off one ...data.0 anchor (3 TU-static objects); i is an inline-function param (numbered late, coloured first)
fix: split lbl_803C29B0[9] into static [3] arrays + symbols.txt ...data.0 label and three scope:local 0xC objects; static inline SpMdlSetELoad(SpMdlSetE*, s32 i) holding the body; 'RPGrpModelAnm* anm;' declared first in the helper fixes mgr r27->r28
