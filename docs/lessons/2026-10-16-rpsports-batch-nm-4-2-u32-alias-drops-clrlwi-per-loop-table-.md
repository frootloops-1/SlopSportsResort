# RPSports batch nm-4/2: u32 alias drops clrlwi, per-loop table reset; stack/fold dead ends

- status: works
- tags: clrlwi,ret-mask,extern-C,loop,STACK-LAYOUT,REGALLOC
- source: claude/nm-4 2026-10-16 sonnet batch 2

symptom: fn_80208814, fn_802013D0, fn_80206370/670 near-misses
cause: u16 member return masked in u32 assignment; table ptr declared outside loop; wrong shift index / p-> vs copy
fix: fn_80208814 ->98.7: extern C u32 alias of the mangled getter for u32 assignments only; fn_802013D0 ->98.5: SpMsgEntry* e=tbl inside the outer for; fn_80206370 dst[j].d=dst[i].d; fn_80206670 switch on tmp.* copy. Dead ends: fn_8020D40C/D0EC u8 ca[4]/cb[4] stack slot order not moved by decl order; fn_801F9BA0 local tbl ptr still folded; fn_801E59FC per-inline zero regs; setMaterialInternal clrlwi comes from eggGXUtility.h getTexMtxID u8 return (header)
