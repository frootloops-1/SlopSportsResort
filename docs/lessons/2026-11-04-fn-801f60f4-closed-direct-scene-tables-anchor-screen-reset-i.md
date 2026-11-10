# fn_801F60F4 closed: direct scene tables (anchor), screen reset inline helper with screen/w/h params, typed self param

- status: works
- tags: anchor,inline-param,stack-slot,arg-order,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: size 724 vs 728 (missing addi r3,r23,0), width/height stack slots and Widths/Heights regs swapped, self/screen/ent colours wrong
cause: four static scene tables are addressed off ...rodata.0; args are evaluated right to left so the height conversion slot comes first; screen is an inline param; void* p + cast local renumbers self
fix: index sSceneStart0/End0/Start1/End1 directly; static inline SpScreenReset(Frustum*, f32 w, f32 h) incl. SetCanvasMode called with (*(Frustum**)(ent+0x10), GetSizeXMax(), GetSizeYMax()); fn_801F60F4(SpSceneMgr* self)
