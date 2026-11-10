# fn_8032F2B8: nested ctor inlines order vregs; hand vptr store

- status: works
- tags: inline-depth,vreg,vptr,fn_8032F2B8,R17,RPBow
- scope: Pack/RPSports/RPBowScene/RPBow_8032ADD8
- source: batch 2026-11-01

symptom: 99.5%: first new temp / i / b register order
cause: locals of deeper inline levels get lower vreg numbers; target needs player > T1 > i > b
fix: BowNpc3DCt / BowNpcBaseCt forwarding wrapper / BowNpcBaseCt2(void* p){u8* b=(u8*)p;} (R17 59) + hand vptr store lbl_803C3FF8 (R17 60). Dead: u8* b param folds into a+0x10 (93.8); separate depth-4 actor-base/handles inlines (95.9). Unit flips with .data 62.5 (lumped RPBow tables): DOL 0
