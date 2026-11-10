# SpMdlSetB 98.5 -> 99.8: idx*4 coloured first once mgr/anm/j are inline-helper vregs (numbered above idx*4)

- status: open
- tags: inline-param,colour,ctor,color_sim,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: idx*4 pushed in sweep 1 (deg 30 minus the lower-numbered j/anm/mgr neighbours < K=29) so coloured late
cause: named locals get the lowest vreg numbers; inline-helper locals/params are @ temps numbered above optimizer temps
fix: SpLoadResFile for mgr/res + static inline SpMdlSetBLoadAnms(self, anm, res, names, idx) with 's32 j; const s32* tbl = lbl_80387E88;' inside. Left: lbl_803C29F8 base r29 vs r28; scratch csim shows it needs a vreg between res/mgr and anm (an @ temp created between the two inlines). Same helper on SpMdlSet (outer i loop) 99.6 -> worse (54-96 lines)
