# fn_80275810: const-declared .sdata globals (section pragma) so loads float

- status: works
- tags: const,sdata,declspec,fn_80275810,R17,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_80275710
- source: step2 2026-11-01

symptom: 96.8%: 1.6 lfs above the prologue stw, 120 load placement and r0/r7 swap
cause: only const-qualified loads float above stores; data must stay in writable .sdata
fix: extern const decls at top, defined at file end with __declspec(section .sdata) const (R17 row 63); store order f28,f24,state,count,timer; 3.6f*(6.0f*speed) gives pool order without an unused local. Note: const can also hurt (fn_802CDFC0) - always test both directions. A (const f32*)& cast at the use site does not float the load
